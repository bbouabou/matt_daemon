FROM debian:latest

RUN apt-get update && apt-get install -y g++
RUN apt-get install -y vim
RUN mkdir /matt_daemon

WORKDIR /matt_daemon

ADD . /matt_daemon

EXPOSE 4242

RUN g++ *.cpp

CMD ["/bin/bash"]
