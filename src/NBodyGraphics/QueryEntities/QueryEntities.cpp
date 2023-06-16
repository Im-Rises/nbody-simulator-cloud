//
// Created by axelc on 13/06/2023.
//

#include "QueryEntities.h"
#include <string>
#include <array>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Callback function used to treat the response
size_t static CallbackRequest(char *ptr, size_t size, size_t nmemb, void *userdata) {
    auto *callbackParameter = static_cast<QueryCallbackParameter*>(userdata);

    // Store the response in the callbackParameter
    callbackParameter->response = ptr;

    // Call the callback function with the response parsed
    callbackParameter->CallbackFct(callbackParameter->Parse());
    return size * nmemb;
}

// Make the curl request
QueryEntities::QueryEntities() : curl(nullptr) {
     curl_global_init(CURL_GLOBAL_ALL);
     curl = curl_easy_init();

     if(!curl) {
         std::cout << "Error initializing curl" << std::endl;
     }

     curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8080/all/present");
     curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
     // Configuration de la fonction de rappel pour stocker la réponse
     curl_easy_setopt(curl, CURLOPT_WRITEDATA, &callbackParameter);
     curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CallbackRequest);

}

// Ask the server to get all the particles
void QueryEntities::AskGetAllParticles() {

     if(!curl) {
         std::cout << "Error while performing curl request : " << curl_easy_strerror(res) << std::endl;
     }
    res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
         std::cout << "Error while performing curl request : " << curl_easy_strerror(res) << std::endl;
    }
}
QueryEntities::~QueryEntities() {
    curl_easy_cleanup(curl);
    curl_global_cleanup();
}
