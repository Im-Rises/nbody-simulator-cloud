# nbody-simulator-cloud

<p align="center">
      <img src="https://user-images.githubusercontent.com/59691442/183268126-b3d19e66-8f2d-463a-805e-ae6ef7cc6c01.png" alt="cmakeLogo" style="height:60px;"/>
      <img src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="cppLogo" style="height:60px;"/>
      <img src="https://img.shields.io/badge/OpenGL-FFFFFF?style=for-the-badge&logo=opengl" alt="openglLogo" style="height:60px;"/>
      <img src="https://user-images.githubusercontent.com/59691442/190315147-ec9dc33f-0090-4f0d-98ab-514eb1463e01.png" alt="glfwLogo" style="height:60px;"/>
</p>

## Description

This is a simple nbody simulator made with OpenGL and C++ with the help of the ImGui library for the UI.

## Images

## Videos

## Features

## Dependencies

- OpenGL version: 4.6.0
- OpenCV version: ???
- GLSL version: 4.60
- GLFW version: 3.3.8
- Glad version: 0.1.36
- ImGui version: 1.89.4 WIP
- GLM version: 0.9.8

## Architecture

```mermaid
flowchart LR
    subgraph Architecture
        subgraph Docker-Calculator
        docker1 & docker2 & docker...
        end
        docker1 & docker2 & docker... --> |UDP| api-redis
        api-redis --> |UDP| api-video-generator
        subgraph Docker-volume
        api-video-generator
        ffmpeg 
        end
        ffmpeg --> |UDP| site-web
    end
```

## Json data transfer

```json
{
  "particles": [
    {
      "index": 0,
      "position": [
        0,
        0,
        0
      ],
      "velocity": [
        0,
        0,
        0
      ]
    },
    {
      "index": 1,
      "position": [
        0,
        0,
        0
      ],
      "velocity": [
        0,
        0,
        0
      ]
    }
  ]
}
```

## Github-Actions

[![CodeQL](https://github.com/Im-Rises/NBodySimulator/actions/workflows/codeql.yml/badge.svg?branch=main)](https://github.com/Im-Rises/NBodySimulator/actions/workflows/codeql.yml)
[![CMake](https://github.com/Im-Rises/NBodySimulator/actions/workflows/cmake.yml/badge.svg?branch=main)](https://github.com/Im-Rises/NBodySimulator/actions/workflows/cmake.yml)
[![flawfinder](https://github.com/Im-Rises/NBodySimulator/actions/workflows/flawfinder.yml/badge.svg?branch=main)](https://github.com/Im-Rises/NBodySimulator/actions/workflows/flawfinder.yml)
[![cpp-linter](https://github.com/Im-Rises/NBodySimulator/actions/workflows/cpp-linter.yml/badge.svg?branch=main)](https://github.com/Im-Rises/NBodySimulator/actions/workflows/cpp-linter.yml)

The project is set with a set of different scripts:

- CodeQL: This script is used to check the code for security issues.
- CMake: This script is used to build the project.
- Flawfinder: This script is used to check the code for security issues.
- Cpp Linter: This script is used to check the code for security issues.

## Libraries

glfw:  
<https://www.glfw.org/docs/latest/>

glm:  
<https://glm.g-truc.net/0.9.9/index.html>

glad:  
<https://glad.dav1d.de/>

OpenGL:  
<https://www.opengl.org/>

Json:  
<https://github.com/nlohmann/json>

libcurl:  
<https://curl.se/libcurl/>

## Contributors

Axel COURMONT:

- @Alshkor
- <https://github.com/Alshkor>

Alexis ROVILLE:

- @Fromiel
- <https://github.com/Fromiel>

Quentin MOREL:

- @Im-Rises
- <https://github.com/Im-Rises>

[![GitHub contributors](https://contrib.rocks/image?repo=Im-Rises/NBodySimulator)](https://github.com/Im-Rises/NBodySimulator/graphs/contributors)
