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
COPY ./ /src
RUN ls
RUN make clean
RUN rm -rf build
RUN rm -rf lib

RUN mkdir build
RUN mkdir lib

RUN git clone https://github.com/google/googletest/ lib/googletest

WORKDIR /src/build
RUN cmake ..
RUN make clean
RUN make all
