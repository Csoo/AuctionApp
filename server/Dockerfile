FROM ubuntu:19.10

EXPOSE 3000

RUN apt update && apt upgrade -y
RUN apt install -y build-essential cmake qt5-default libqt5sql5-sqlite

COPY . /source

RUN mkdir /source/build

WORKDIR /source/build
RUN cp ../src/database.db / && cp ../src/cpp_email/emailsender.py /
RUN cmake .. && make -j4 && cp src/auctionapp / && rm -r /source

ENTRYPOINT ["/auctionapp"]
