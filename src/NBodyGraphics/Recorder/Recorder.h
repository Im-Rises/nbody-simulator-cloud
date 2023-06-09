#ifndef NBODYSIMULATOR_RECORDER_H
#define NBODYSIMULATOR_RECORDER_H

#include <glad/glad.h>
#include <opencv2/opencv.hpp>

class Recorder {
private:
    GLuint fbo;
    GLuint texture;
    unsigned char* framebuffer;

    int width = 1280;
    int height = 720;
    int fps = 30;
    //    int frame_id = 0;
    cv::VideoWriter videoWriter;
    cv::Mat frame;

public:
    //    Recorder();
    explicit Recorder(int width, int heigh, float framerate);
    Recorder(const Recorder&) = delete;
    auto operator=(const Recorder&) -> Recorder& = delete;
    Recorder(Recorder&&) = delete;
    ~Recorder();

    void InitializeFBO();
    void InitializeVideoWriter();

    void SetWidthHeight(int width, int height);

    void StartCapture();

    void StopCapture();

    auto getTexture() -> unsigned int { return texture; }
};



#endif // NBODYSIMULATOR_RECORDER_H
