FROM ubuntu:19.10

RUN apt update && apt upgrade -y
RUN apt install -y build-essential cmake qt5-default libqt5sql5-sqlite

COPY . /source

RUN mkdir /source/build

WORKDIR /source/build
RUN cp ../src/database.db /
RUN cmake .. && make -j4 && cp src/auctionapp / && rm -r /source

ENTRYPOINT ["/auctionapp"]
