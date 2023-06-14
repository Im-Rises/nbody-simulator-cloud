FROM matimoreyra/opencv

RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install -y mesa-utils
RUN apt-get install -y cmake
RUN apt-get install -y make
RUN apt-get install -y gcc
RUN apt-get install -y g++
RUN apt-get install -y build-essential
RUN apt-get install -y libglfw3-dev
RUN apt-get install -y libcurl4-openssl-dev
RUN apt-get install -y curl
RUN apt-get install -y xvfb

WORKDIR nbody

COPY . .

RUN cmake .
RUN make

ENTRYPOINT ["bash", "./run-opengl.sh"]
