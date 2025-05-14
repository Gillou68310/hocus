FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    ca-certificates \
    python-is-python3 \
    python3 \
    python3-pip \
    software-properties-common

RUN add-apt-repository -y ppa:dosemu2/ppa \
    && apt-get update \
    && apt-get install -y \
    make \
    dos2unix \
    unzip \
    curl \
    wget \
    dosemu2 \
    && rm -rf /var/lib/apt/lists/*

RUN wget "https://github.com/OmniBlade/binutils-gdb/releases/download/omf-build/omftools.tar.gz" \
    && tar xvzf omftools.tar.gz -C /usr/bin jwasm \
    && rm omftools.tar.gz \
    && wget "https://github.com/decompals/binutils-omf/releases/download/v0.3/omftools-linux-x86_64.tar.gz" \
    && tar xvzf omftools-linux-x86_64.tar.gz -C /usr/bin omf-nm omf-objdump \
    && rm omftools-linux-x86_64.tar.gz

RUN wget "https://github.com/decompme/compilers/releases/download/compilers/bcc3.1.tar.gz" \
    && mkdir /opt/bcpp31 \
    && tar xvzf bcc3.1.tar.gz -C /opt/bcpp31 \
    && chmod -R 755 /opt/bcpp31 \
    && rm bcc3.1.tar.gz

COPY requirements.txt /pip3/
COPY tools/tdinfo-parser/requirements.txt /pip3/tools/tdinfo-parser/
WORKDIR /pip3
RUN pip3 install -r requirements.txt --break-system-packages

RUN useradd -ms /bin/bash hocus
RUN mkdir /hocus
WORKDIR /hocus
USER hocus