FROM alpine

RUN apk add g++
RUN apk add make cmake
RUN apk add git

WORKDIR /src

RUN mkdir lib
RUN mkdir build

WORKDIR /src/lib
RUN git clone https://github.com/google/googletest/

WORKDIR /src/build
CMD "cmake .. && make clean && make all && ./test/ExampleProject_test"
