FROM debian:latest

RUN apt-get update && apt-get install -y g++

RUN mkdir /matt_daemon

WORKDIR /matt_daemon

ADD . /matt_daemon

EXPOSE 80

RUN g++ *.cpp

CMD ["/bin/bash"]
