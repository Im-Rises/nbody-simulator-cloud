#include <cmath>
#include <glm/glm.hpp>

#include <chrono>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>

#include <nlohmann/json.hpp>

#include <curl/curl.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <csignal>
#endif

const float GravityConstant = 1.0F;
const float ParticleMass = 50.0F;
const float FixedDeltaTime = 0.02F;
const float Softening = 10.0F;
const float Friction = 0.99F;
const float SpawnRadius = 3.0F;

bool exitMainLoopFlag = false;

void signalHandler(int signum) {
    if (signum == SIGINT)
    {
        exitMainLoopFlag = true;
    }
}

struct Particle {
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;

    Particle() : position(glm::vec3(0.0F)), velocity(glm::vec3(0.0F, 0.0F, 0.0F)) {}
};

void updatePhysics(std::vector<Particle>& particles, float deltaTime) {
    for (auto& particle : particles)
    {
        glm::vec3 sumForces(0.0F, 0.0F, 0.0F);
        for (auto& otherParticle : particles)
        {
            if (&particle != &otherParticle)
            {
                auto distance = glm::distance(particle.position, otherParticle.position);
                auto direction = glm::normalize(otherParticle.position - particle.position);

                auto force = GravityConstant * ParticleMass * ParticleMass / ((distance * distance) + Softening);
                sumForces += direction * force;
            }

            particle.acceleration = sumForces / ParticleMass;
        }
    }

    for (auto& particle : particles)
    {
        particle.position += (particle.velocity * deltaTime) + ((particle.acceleration * (deltaTime * deltaTime)) / 2.0F);
        particle.velocity += particle.acceleration * deltaTime;
        particle.velocity *= Friction;
    }
}

auto particlesToJson(const std::vector<Particle>& particles, int baseIndex) -> nlohmann::json {
    nlohmann::json json;
    json["particules"] = nlohmann::json::array();
    for (int i = 0; i < particles.size(); i++)
    {
        json["particules"].push_back(
            { { "index", 2 * i + baseIndex },
                { "position", { particles[i].position.x, particles[i].position.y, particles[i].position.z } },
                { "velocity", { particles[i].velocity.x, particles[i].velocity.y, particles[i].velocity.z } } });

    }
    return json;
}

size_t static DumpCallback(char* ptr, size_t size, size_t nmemb, void* userdata) {
    return size * nmemb;
}

void curlPostRequest(const std::string& url, const std::string& data) {
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, (url + "/api/").c_str());
        // Définition de l'en-tête "Content-Type: application/json"
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, DumpCallback);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L); // change to 1L to see verbose output
        std::cout << "Sending data to " << url << std::endl;
        res = curl_easy_perform(curl);
        std::cout << "Data sent" << std::endl;
        if (res != CURLE_OK)
            std::cout << "Error: " << curl_easy_strerror(res) << std::endl;


        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}

auto main(int argc, char* argv[]) -> int {

    // Check arguments
    if (argc < 4)
    {
        std::cout << "Usage: " << argv[0] << " <baseIndex> <numParticles> <addressPost> <particlesCountWork>" << std::endl;
        return 1;
    }

    std::cout << argv[1] << " " << argv[2] << " " << argv[3] << argv[4] << std::endl;

    // Get arguments
    auto baseIndex = std::atoi(argv[1]);
    auto numParticles = std::atoi(argv[2]);
    auto addressPost = std::string(argv[3]);
    // auto particlesCountWork = std::atoi(argv[4]);

    // Init random
    srand(static_cast<unsigned int>(time(nullptr)));

    // Set exit signals
    signal(SIGINT, signalHandler);

    /* Init */
    auto particles = std::vector<Particle>(numParticles);
    std::mt19937 randomEngine;
    std::uniform_real_distribution<float> randomFloats(0.0F, static_cast<float>(2.0F * M_PI));
    for (auto& particle : particles)
    {
        const float angle1 = randomFloats(randomEngine);
        const float angle2 = randomFloats(randomEngine);
        const float x = SpawnRadius * std::sin(angle1) * std::cos(angle2);
        const float y = SpawnRadius * std::sin(angle1) * std::sin(angle2);
        const float z = SpawnRadius * std::cos(angle1);
        particle.position = glm::vec3(x, y, z);
        particle.velocity = glm::vec3(0.0F, 0.0F, 0.0F);


        /*particle.position = glm::vec3(
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0F - 1.0F,
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0F - 1.0F,
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0F - 1.0F);*/
    }

    auto json = particlesToJson(particles, baseIndex);
    curlPostRequest(addressPost, json.dump());

    /* Loop*/
    //
    const float FixedDeltaTime = 0.02F;
    float accumulator = 0.0F;
    //
    auto previousTime = std::chrono::high_resolution_clock::now();
    float deltaTime = 0.0F;
    //
    while (!exitMainLoopFlag)
    {
        auto currentTime = std::chrono::high_resolution_clock::now();

        deltaTime = std::chrono::duration<float>(currentTime - previousTime).count();

        accumulator += deltaTime;
        while (accumulator >= FixedDeltaTime)
        {
            updatePhysics(particles, FixedDeltaTime);
            accumulator -= FixedDeltaTime;
            json = particlesToJson(particles, baseIndex);
            //curlPostRequest(addressPost, json.dump());
        }

        previousTime = currentTime;
    }

    std::cout << "Exiting..." << std::endl;

    return 0;
}
