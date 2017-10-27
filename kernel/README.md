# kernel compile

## compiler
* arm-linux-gcc (Freescale MAD -- Linaro 2011.07 -- Built at 2011/08/10 09:20) 4.6.2 20110630 (prerelease)
* GNU Make 4.1

## compile steps
1. Decompress the kernel source.

    tar -xvf linux-2.6.35.tar.gz

2. Go to the linux-2.6.35 directory

    cd linux-2.6.35/

3. Find the default configure file for the target board

    ll ./arch/arm/configs/

4. After step 3, you should can see a file named x210ii_initrd_defconfig, copy the name, and do the follow command.

    export ARCH=arm<br/>
    make x210ii_initrd_defconfig

5. Check if the defconfig is that you want, and you can change it. do<br/>
    make menuconfig

6. Compile the kernel image.<br/>
    make -jn    
    (where 'n' means the num of thread of your host computer you want to use to compile the kernel image. usaully, we choose to use all our host computer threads to compile it to reduce the compiling time)

7. After step 6 success, the zImage in ./arch/arm/boot/ is the image that you make, and you will use.
