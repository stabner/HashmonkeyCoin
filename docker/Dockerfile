FROM debian:stretch
LABEL maintainer="HashmonkeyCoin Developers <dev@hashmonkeycoin.org>"
LABEL description="Dockerised HashmonkeyCoin Core, built from Travis"

RUN apt-get update && apt-get -y upgrade && apt-get clean && rm -fr /var/cache/apt/*

COPY bin/* /usr/bin/
