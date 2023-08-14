FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive
ENV LANG C.UTF-8
ENV LC_ALL C.UTF-8

RUN apt-get -y update && \
    apt-get -y upgrade && \
    apt-get -y dist-upgrade && \
    apt-get -y autoremove && \
    apt-get install -y build-essential gdb wget git libssl-dev clang-format && \
    mkdir ~/temp && cd ~/temp && \
    apt-get install -y cmake && \
    cd ~/temp &&  wget -q https://sourceforge.net/projects/boost/files/boost/1.81.0/boost_1_81_0.tar.gz && \
    tar -zxf boost_1_81_0.tar.gz && cd ~/temp/boost_1_81_0 && ./bootstrap.sh && ./b2 cxxflags="-std=c++11" --reconfigure --with-fiber --with-context --with-atomic --with-date_time --with-filesystem --with-url install && \
    cd ~/temp && git clone -b v1.15 https://github.com/linux-test-project/lcov.git && cd lcov && make install && cd .. && \
    apt-get install -y libperlio-gzip-perl libjson-perl && \
    rm -rf ~/temp/* && \
    apt-get autoremove -y &&\
    apt-get clean -y &&\
    rm -rf /var/lib/apt/lists/*

RUN apt-get -y update && \
    apt-get install -y libpq-dev libsqlite3-dev unzip && \
    cd ~/temp && \
    git clone https://github.com/jtv/libpqxx.git && cd libpqxx && \
    git checkout 7.6.1 && \
    mkdir build && cd build && \
    cmake .. -DPostgreSQL_TYPE_INCLUDE_DIR=/usr/include/postgresql/libpq && \
    make -j6 && make install && \
    cd ~/temp && \
    wget -q https://github.com/SOCI/soci/archive/refs/tags/v4.0.3.zip && \
    unzip v4.0.3.zip && \
    cd soci-4.0.3 && \
    mkdir build && cd build && \
    cmake .. -DSOCI_WITH_BOOST=ON -DSOCI_WITH_POSTGRESQL=ON -DSOCI_WITH_SQLITE3=ON -DCMAKE_CXX_STANDARD=11 -DSOCI_CXX11=ON && \
    make -j6 && make install && \
    rm -rf ~/temp/* && \
    apt-get autoremove -y &&\
    apt-get clean -y &&\
    rm -rf /var/lib/apt/lists/*

ARG DOCKER_TYPE

RUN mkdir /usr/local/libasyik
COPY . /usr/local/libasyik

# Install requirements
RUN apt-get update && apt-get install -y \
    # OpenCV dependencies
    build-essential cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev \
    python3-dev python3-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libdc1394-22-dev \
    libcanberra-gtk-module libcanberra-gtk3-module

# Clone, build and install OpenCV
RUN git clone https://github.com/opencv/opencv.git && \
    cd /opencv && mkdir build && cd build && \
    cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local .. && \
    make -j"$(nproc)" && \
    make install && \
    rm -rf /opencv

RUN cd ~ && \
    git clone https://github.com/okyfirmansyah/libasyik.git && \
    cd ~/libasyik && \
    git submodule update --init --recursive && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make -j4 && \
    make install

EXPOSE 8080