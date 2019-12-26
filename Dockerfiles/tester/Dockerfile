FROM alpine

RUN apk add g++
RUN apk add make cmake
RUN apk add git

WORKDIR /src

RUN mkdir lib
RUN mkdir build

WORKDIR /googletest
RUN git clone https://github.com/google/googletest/

WORKDIR /src
CMD make clean; \
rm -rf buid; \
rm -rf lib; \
mkdir build; \
mkdir lib; \
cp -r /googletest/* lib/; \
cd build; \
cmake ..; \
make clean; \
make all; \
./test/ExampleProject_test
