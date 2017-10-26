//lcd.cpp
#include "tftlcd.hpp"
#include <stdlib.h>

//int lcddev_t::count=0;
//char* lcddev_t::devfile_s[MaxlcdObjnum];
char* lcdObjCount::ObjDescrition[MaxlcdObjnum];
int lcdObjCount::numObjs=0;

/*lcddev_t::lcddev_t()
{
    isInit=0;
    fd =-1;
    numid=-1;
    ScreenSize=0;
    xres=0;
    yres=0;
    init_lcddev();
}*/
lcddev_t::lcddev_t(char*devfile_v):lcdObjCount(devfile_v)
{
    isInit=0;
    init_lcddev(devfile_v);
}
lcddev_t::~lcddev_t()
{
    lcddev_mUnmap();
/*    count--;
    devfile_s[count]=NULL;*/
}

int lcddev_t::getScreenSize() const
{
    return ScreenSize;
}
const unsigned char* lcddev_t::getfbp() const
{
    return (unsigned char*)fbp;
}


int lcddev_t::getfd() const
{
    return fd;
}
int lcddev_t::getxres() const
{
    return xres;
}
int lcddev_t::getyres() const
{
    return yres;
}
int lcddev_t::getbits_per_pixel() const
{
    return bits_per_pixel;
}

//危险公共借口，慎用，一般仅用于调试
int lcddev_t::mUnmap()
{
    return (lcddev_mUnmap());
}

int lcddev_t::mMap()
{
    return (lcddev_mMap());
}

int lcddev_t::getnumid()const
{
    return numid;
}

//init_lcddev(lcddev_t& lcd=deflcd,char* devfile_v=(char*)"/dev/fb0")
