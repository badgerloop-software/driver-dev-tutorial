rm -rf build
rm -rf out
rm -rf coverage
echo "clean finished"
mkdir build && cd build

if [ $(arch) == "aarch64" ]; then

    if [ ! -d /opt/gcc-arm-10.3-2021.07-aarch64-arm-none-linux-gnueabihf ]; then
wget -c \
    https://developer.arm.com/-/media/Files/downloads/gnu-a/10.3-2021.07/binrel/gcc-arm-10.3-2021.07-aarch64-arm-none-linux-gnueabihf.tar.xz \
    -P /tmp/
    if [ $? -ne 0 ]; then
        echo "Failure to get arm-linux-gnueabihf"
    fi
    sudo tar xf /tmp/gcc-arm-10.3-2021.07-aarch64-arm-none-linux-gnueabihf.tar.xz -C /opt/

    rm /tmp/gcc-arm-10.3-2021.07-aarch64-arm-none-linux-gnueabihf.tar.xz
fi
    toolchain='./toolchains/beaglebone_aarch64.cmake'

elif [ $(arch) == "x86_64" ]; then

    if [ ! -d /opt/gcc-linaro-6.5.0-2018.12-x86_64_arm-linux-gnueabihf ]; then
wget -c \
    https://releases.linaro.org/components/toolchain/binaries/6.5-2018.12/arm-linux-gnueabihf/gcc-linaro-6.5.0-2018.12-x86_64_arm-linux-gnueabihf.tar.xz \
    -P /tmp/
if [ $? -ne 0 ]; then
    echo "Failure to get arm-linux-gnueabihf"
fi
sudo tar xf /tmp/gcc-linaro-6.5.0-2018.12-x86_64_arm-linux-gnueabihf.tar.xz -C /opt/

rm /tmp/gcc-linaro-6.5.0-2018.12-x86_64_arm-linux-gnueabihf.tar.xz
    fi
    toolchain='./toolchains/beaglebone.cmake'
fi

cmake -DCMAKE_TOOLCHAIN_FILE=$toolchain ..
make