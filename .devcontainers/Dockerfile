FROM ubuntu:22.04

RUN echo 'APT::Install-Suggests "0";' >> /etc/apt/apt.conf.d/00-docker
RUN echo 'APT::Install-Recommends "0";' >> /etc/apt/apt.conf.d/00-docker

RUN DEBIAN_FONRTEND=non-interactive \
  apt-get update \
  && apt-get upgrade -y \
  && apt-get install build-essential -y \
  && apt-get install cmake -y  

EXPOSE 8080
