//lcd.h
#ifndef _TFTLCD_HPP_
#define _TFTLCD_HPP_
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <linux/fb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "font.h"

#ifndef Pi
#define Pi 3.1415926532
#endif

struct Point_t
{
    int x;
    int y;
    Point_t():x(0),y(0){}
    Point_t(int xval,int yval):x(xval),y(yval){}
};

struct Color_t
{
    unsigned char A;
    unsigned char R;
    unsigned char G;
    unsigned char B;
    Color_t():A(100),R(255),G(0),B(0){}
    Color_t(unsigned char Av,unsigned char Rv,unsigned char Gv,unsigned char Bv)
    {
        A=Av;
        R=Rv;
        G=Gv;
        B=Bv;
    }
};


const Color_t Black(125,0,0,0);
const Color_t White(125,255,255,255);
const Color_t Green(125,0,255,0);
const Color_t Red(125,255,0,0);
const Color_t Blue(125,0,0,255);

enum font_t
{
    NORMAL=24,
    SMALL=16,
    BIG=48,
};

const int MaxlcdObjnum=10;  //限制lcddev的创建最大数量

class lcdObjCount
{
public:
    class TooManyObj{};//抛出异常的类
    class ObjHad{};
    static int ObjCount()
    {
        return numObjs;
    }

protected:

    static int numObjs;
    static char* ObjDescrition[MaxlcdObjnum];
    lcdObjCount(char* desr=(char*)"/dev/fb0");
   // lcdObjCount(const lcdObjCount& rhs);
    ~lcdObjCount()
    {
        --numObjs;
    }

private:
    int init(char* desr=(char*)"/dev/fb0");
    bool isObjHad(char* desr=(char*)"/dev/fb0");
};

class lcddev_t:protected lcdObjCount
{
public:
    using lcdObjCount::ObjCount;
    using lcdObjCount::TooManyObj;
    using lcdObjCount::ObjHad;
    //lcddev_t();
    lcddev_t(char*devfile_v=(char*)"/dev/fb0");
    ~lcddev_t();
    int getScreenSize() const;
    const unsigned char* getfbp() const;
    int getfd() const;
    int getxres() const;
    int getyres() const;
    int getbits_per_pixel() const;
    int getnumid()const;

//危险公共借口，慎用，一般仅用于调试
    int mUnmap();
    int mMap();
/*
public:
    static int count;
    static char *devfile_s[10]; //最多仅支持10个不同的lcd设备；
*/
protected:
    int numid;
    char isInit;
    char isFbpMap;
    unsigned char *fbp;
    int fd;
    unsigned int ScreenSize;
    unsigned int xres;
    unsigned int yres;
    unsigned int bits_per_pixel;
    char* devfile;

public:

    inline int showChar(const int&x,const int& y,const char Char,const font_t& size=NORMAL,const Color_t& color=White);
    inline int showChar(const Point_t& pos,const char Char,const font_t& size=NORMAL,const Color_t& color=White);
    inline int showChar(const int&x,const int&y,const char Char,const font_t& size=NORMAL,const int& color_i=0xffffffff);
    inline int showChar(const Point_t& pos,const char Char,const font_t& size=NORMAL,const int& color_i=0xffffffff);

    inline int drawCircle(const Point_t& center,const unsigned int& r,const Color_t& color);
    inline int drawCircle(const Point_t& center,const unsigned int& r,const unsigned int& color_i);
    inline int drawCircle(const unsigned int& x_center,const unsigned int& y_center,const unsigned int& r,\
                    const Color_t& colo);
    inline int drawCircle(const unsigned int& x_center,const unsigned int& y_center,const unsigned int& r,\
                    const unsigned int& color_i);


    inline int drawRect(const Point_t& LeftTop,const Point_t& RightBot,const Color_t& color,\
                    const unsigned int& width=1);
    inline int drawRect(const Point_t& LeftTop,const Point_t& RightBot,const unsigned int& color_i,\
                    const unsigned int& width=1);
    inline int drawRect(const unsigned int& x_LeftTop,const unsigned int& y_LeftTop,const unsigned int& x_RightBot,\
                    const unsigned int& y_Right_Bot,const Color_t& color,const unsigned int& width=1);
    inline int drawRect(const unsigned int& x_LeftTop,const unsigned int& y_LeftTop,const unsigned int& x_RightBot,\
                    const unsigned int& y_Roght_Bot,const unsigned int& color_i,const unsigned int& width=1);

    inline int drawLine(const Point_t& beg,const Point_t& end,const Color_t& color,\
                    const unsigned int& width=1);
    inline int drawLine(const Point_t& beg,const Point_t& end,const unsigned int& color_i,\
                    const unsigned int& width=1);
    inline int drawLine(const unsigned int& x_beg,const unsigned int& y_beg,const unsigned int& x_end,const unsigned int& y_end,\
                    const Color_t& color,const unsigned int& width=1);
    inline int drawLine(const unsigned int& x_beg,const unsigned int& y_beg,const unsigned int& x_end,const unsigned int& y_end,\
                    const unsigned int& Color_i,const unsigned int& width=1);

    inline int drawPoint(const Point_t& pos,const Color_t& color);
    inline int drawPoint(const unsigned int& x,const unsigned int& y,const Color_t color);
    inline int drawPoint(const Point_t& pos,const unsigned int& color_i);
    inline int drawPoint(const unsigned int& x,const unsigned int& y,const unsigned int& color_i);

    inline int clearPoint(const Point_t& pos,const Color_t& color=Black);
    inline int clearPoint(const unsigned int& x,const unsigned int& y,const Color_t color=Black);
    inline int clearPoint(const Point_t& pos,const unsigned int& color_i=0);
    inline int clearPoint(const unsigned int& x,const unsigned int& y,const unsigned int& color_i=0);

    inline int drawAera(const Point_t& LeftTop,const Point_t&RightBot,const Color_t& color=White);
    inline int drawAera(const Point_t& LeftTop,const Point_t&RightBot,const unsigned int& color_i=0xffffffff);
    inline int drawAera(const unsigned int& x_LeftTop,const unsigned int& y_LeftTop,const unsigned int& x_RightBot,\
            const unsigned int& y_RightBot,const Color_t& color=White);
    inline int drawAera(const unsigned int& x_LeftTop,const unsigned int& y_LeftTop,const unsigned int& x_RightBot,\
            const unsigned int& y_RightBot,const unsigned int& color_i=0xffffffff);


    inline int clearAeratoWhite(const Point_t& LeftTop,const Point_t&RightBot);
    inline int clearAeratoWhite(const unsigned int& x_LeftTop,const unsigned int& y_LeftTop,const unsigned int& x_RightBot,\
            const unsigned int& y_RightBot);

    inline int clearAeratoBlack(const Point_t& LeftTop,const Point_t&RightBot);
    inline int clearAeratoBlack(const unsigned int& x_LeftTop,const unsigned int& y_LeftTop,const unsigned int& x_RightBot,\
            const unsigned int& y_RightBot);

    inline int clearAlltoWhite();
    inline int clearAlltoBlack();
    inline int clearAll();

private:
    inline int init_lcddev(char* devfile_v=(char*)"/dev/fb0");
    inline int lcddev_mMap();
    inline int lcddev_mUnmap();
    //inline bool islcddevHadCreated(char *devfile_v);

};

//const int lcdObjCount<lcddev_t>::maxnumObjs=10;
//创建对象接口，建议每次创建对象都调用此函数
//lcddev_t& Buildalcddev(char*devfile_v=(char*)"/dev/fb0");
//

inline int lcddev_t::showChar(const int&x,const int& y,const char Char,const font_t& size,const Color_t& color)
{
    unsigned char temp,t1,t;
	int16_t y0=y;
    int tmpx=x,tmpy=y;
	unsigned char csize=(size/8+((size%8)?1:0))*(size/2);		//得到字体一个字符对应点阵集所占的字节数
 	unsigned char num=Char-' ';//得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）
	for(t=0;t<csize;t++)
	{
		if(size==12)temp=asc2_1206[num][t]; 	 	//调用1206字体
		else if(size==16)temp=asc2_1608[num][t];	//调用1608字体
		else if(size==24)temp=asc2_2412[num][t];	//调用2412字体
		else if(size==48)temp=asc2_4824[num][t];	//调用4824字体
		else return -1;								//没有的字库
		for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)drawPoint(tmpx,tmpy,color);
			//else if(mode==0)drawPoint(x,y,color);
			temp<<=1;
			tmpy++;
			if(tmpy>=(int)yres)return -1;		//超区域了
			if((tmpy-y0)==size)
			{
				tmpy=y0;
				tmpx++;
				if(tmpx>=(int)xres)return -1;	//超区域了FFF
				break;
			}
		}
	}
    return 0;
}

inline int lcddev_t::showChar(const Point_t& pos,const char Char, const font_t& size,const Color_t& color)
{
    return showChar(pos.x,pos.y,Char,size,color);
}
inline int lcddev_t::showChar(const int&x,const int&y,const char Char, const font_t& size,const int& color_i)
{
    Color_t color;
    color.A=(unsigned char)(color_i>>24)&0xff;
    color.R=(unsigned char)(color_i>>16)&0xff;
    color.G=(unsigned char)(color_i>>8)&0xff;
    color.B=(unsigned char)(color_i)&0xff;
    return showChar(x,y,Char,size,color);
}
inline int lcddev_t::showChar(const Point_t& pos,const char Char, const font_t& size,const int& color_i)
{
    Color_t color;
    color.A=(unsigned char)(color_i>>24)&0xff;
    color.R=(unsigned char)(color_i>>16)&0xff;
    color.G=(unsigned char)(color_i>>8)&0xff;
    color.B=(unsigned char)(color_i)&0xff;
    return showChar(pos.x,pos.y,Char,size,color);
}

inline int lcddev_t::drawCircle(const Point_t& center,const unsigned int& r,const Color_t& color)
{
    return (drawCircle(center.x,center.y,r,color));
}

inline int lcddev_t::drawCircle(const Point_t& center,const unsigned int& r,const unsigned int& color_i)
{
    Color_t color;
    color.A=(unsigned char)(color_i>>24)&0xff;
    color.R=(unsigned char)(color_i>>16)&0xff;
    color.G=(unsigned char)(color_i>>8)&0xff;
    color.B=(unsigned char)(color_i)&0xff;
    return (drawCircle(center.x,center.y,r,color));
}

inline int lcddev_t::drawCircle(const unsigned int& x_center,const unsigned int& y_center,const unsigned int& r,\
                    const Color_t& color)
{
    int xPos=0;
    int yPos=0;
    for(float theda=0;theda<=2*Pi;theda+=0.01)
    {
        xPos=(int)((float)r*cosf(theda)+x_center);
        yPos=(int)((float)r*sinf(theda)+y_center);
        if(xPos<0)
            xPos=0;
        if(yPos<0)
            yPos=0;
        if(drawPoint((unsigned int)xPos,(unsigned int)yPos,color)<0)
            return -1;
    }
    return 0;
}

inline int lcddev_t::drawCircle(const unsigned int& x_center,const unsigned int& y_center,const unsigned int& r,\
                    const unsigned int& color_i)
{
    Color_t color;
    color.A=(unsigned char)(color_i>>24)&0xff;
    color.R=(unsigned char)(color_i>>16)&0xff;
    color.G=(unsigned char)(color_i>>8)&0xff;
    color.B=(unsigned char)(color_i)&0xff;

    return (drawCircle(x_center,y_center,r,color));
}


inline int lcddev_t::drawRect(const Point_t& LeftTop,const Point_t& RightBot,const Color_t& color,\
                    const unsigned int& width)
{

    return (drawRect(LeftTop.x,LeftTop.y,RightBot.x,RightBot.y,color,width));
}

inline int lcddev_t::drawRect(const Point_t& LeftTop,const Point_t& RightBot,const unsigned int& color_i,\
                    const unsigned int& width)
{
    Color_t color;
    color.A=(unsigned char)(color_i>>24)&0xff;
    color.R=(unsigned char)(color_i>>16)&0xff;
    color.G=(unsigned char)(color_i>>8)&0xff;
    color.B=(unsigned char)(color_i)&0xff;
    return (drawRect(LeftTop.x,LeftTop.y,RightBot.x,RightBot.y,color,width));
}

inline int lcddev_t::drawRect(const unsigned int& x_LeftTop,const unsigned int& y_LeftTop,const unsigned int& x_RightBot,\
                    const unsigned int& y_RightBot,const Color_t& color,const unsigned int& width)
{
    //draw top line;
    if(drawLine(x_LeftTop,y_LeftTop,x_RightBot,y_LeftTop,color,width)<0)
        return -1;
    //draw left line;
    if(drawLine(x_LeftTop,y_LeftTop,x_LeftTop,y_RightBot,color,width)<0)
        return -1;
    //draw bottom line;
    if(drawLine(x_LeftTop,y_RightBot,x_RightBot,y_RightBot,color,width)<0)
        return -1;
    //draw right line;
    if(drawLine(x_RightBot,y_LeftTop,x_RightBot,y_RightBot,color,width)<0)
        return -1;
    return 0;
}

inline int lcddev_t::drawRect(const unsigned int& x_LeftTop,const unsigned int& y_LeftTop,const unsigned int& x_RightBot,\
                    const unsigned int& y_RightBot,const unsigned int& color_i,const unsigned int& width)
{
    Color_t color;
    color.A=(unsigned char)(color_i>>24)&0xff;
    color.R=(unsigned char)(color_i>>16)&0xff;
    color.G=(unsigned char)(color_i>>8)&0xff;
    color.B=(unsigned char)(color_i)&0xff;

    return (drawRect(x_LeftTop,y_LeftTop,x_RightBot,y_RightBot,color,width));
}

inline int lcddev_t::drawLine(const unsigned int& x_beg,const unsigned int& y_beg,const unsigned int& x_end,\
                    const unsigned int& y_end,const Color_t& color,const unsigned int& width)
{
    if(x_beg>xres||x_end>xres||y_beg>yres||y_end>yres)
        return -1;
    int xLen=x_end-x_beg;
    int yLen=y_end-y_beg;
    unsigned int tmpxbeg=x_beg,tmpxend=x_end,tmpybeg=y_beg,tmpyend=y_end;
//    if(xLen<0||yLen<0)
//        return -1;
    if(xLen==0)         //竖线
    {
        if(y_beg>y_end)
        {
            tmpybeg=y_end;
            tmpyend=y_beg;
        }
        for(unsigned int y=tmpybeg;y<=tmpyend;y++)
        {
            for(unsigned int i=0;i<width;i++)
                if((drawPoint(tmpxbeg,y+i,color))<0)
                    return -1;

        }
    }
    else
    {
        float y2xRatio=((float)((float)yLen/(float)xLen));
        if(fabs(y2xRatio)>1)
        {
            y2xRatio=((float)((float)xLen/(float)yLen));
            if(y_beg>y_end)
            {
                tmpybeg=y_end;
                tmpyend=y_beg;
            }
            if(x_beg<x_end&&y2xRatio<0)
            {
                tmpxbeg=x_end;
                tmpxend=x_beg;
            }
            if(x_beg>x_end&&y2xRatio>0)
            {
                tmpxbeg=x_end;
                tmpxend=x_beg;
            }
            for(unsigned int y=tmpybeg;y<tmpyend;y++)
            {
                for(unsigned int i=0;i<width;i++)
                    if(drawPoint(y2xRatio*(y-tmpybeg)+tmpxbeg+i,y,color)<0)
                        return -1;
            }
        }
        else
        {
            if(x_beg>x_end)
            {
                tmpxbeg=x_end;
                tmpxend=x_beg;
            }
            if(y2xRatio<0&&y_beg<y_end)
            {
                tmpybeg=y_end;
                tmpyend=y_beg;
            }
            if(y2xRatio>0&&y_beg>y_end)
            {
                tmpybeg=y_end;
                tmpyend=y_beg;
            }
            for(unsigned int x=tmpxbeg;x<tmpxend;x++)
            {
                for(unsigned int i=0;i<width;i++)
                    if(drawPoint(x,y2xRatio*(x-tmpxbeg)+tmpybeg+i,color)<0)
                        return -1;
            }
        }
    }
    return 0;
}

inline int lcddev_t::drawLine(const unsigned int& x_beg,const unsigned int& y_beg,const unsigned int& x_end,\
        const unsigned int& y_end,const unsigned int& color_i,const unsigned int& width)
{
    Color_t color;
    color.A=(unsigned char)(color_i>>24)&0xff;
    color.R=(unsigned char)(color_i>>16)&0xff;
    color.G=(unsigned char)(color_i>>8)&0xff;
    color.B=(unsigned char)(color_i)&0xff;
    return (drawLine(x_beg,y_beg,x_end,y_end,color,width));
}

inline int lcddev_t::drawLine(const Point_t& beg,const Point_t& end,const Color_t& color,const unsigned int& width)
{
    return (drawLine(beg.x,beg.y,end.x,end.y,color,width));
}

inline int lcddev_t::drawLine(const Point_t& beg,const Point_t& end,const unsigned int& color_i,const unsigned int& width)
{
    Color_t color;
    color.A=(unsigned char)(color_i>>24)&0xff;
    color.R=(unsigned char)(color_i>>16)&0xff;
    color.G=(unsigned char)(color_i>>8)&0xff;
    color.B=(unsigned char)(color_i)&0xff;
    return (drawLine(beg.x,beg.y,end.x,end.y,color,width));
}


inline int lcddev_t::drawPoint(const Point_t& pos,const Color_t& color)
{
    return (drawPoint(pos.x,pos.y,color));
}

inline int lcddev_t::drawPoint(const unsigned int& x,const unsigned int& y,const Color_t color)
{
    if(isInit!=1)
       // if(init_lcddev()<0)
        return -1;
    if(!isFbpMap)
        if(lcddev_mMap()<0)
            return -1;
    if(x>xres||y>yres)
        return -2;
    int offset=0;
    if(bits_per_pixel==24)
    {
        offset=(y*(xres)+x)*(bits_per_pixel)/8;
        *(unsigned char *)(fbp+offset+0)=(unsigned char)color.B;
        *(unsigned char *)(fbp+offset+1)=(unsigned char)color.G;
        *(unsigned char *)(fbp+offset+2)=(unsigned char)color.R;
    }
    else if(bits_per_pixel==16)
    {
        offset=(y*xres+x)*(bits_per_pixel)/8;
        int color_i=(color.R<<11)|(color.G<<5)|(color.B&0x1f);
        *(unsigned char *)(fbp+offset+0)=(unsigned char)((color_i)&0xff);//(color_i>>8)&0xff);
        *(unsigned char *)(fbp+offset+1)=(unsigned char)((color_i>>8)&0xff);//((color_i)&0xff)
    }
    else if(bits_per_pixel==32)
    {
        offset=(y*xres+x)*(bits_per_pixel)/8;
        *(unsigned char *)(fbp+offset+0)=(unsigned char)color.B;
        *(unsigned char *)(fbp+offset+1)=(unsigned char)color.G;
        *(unsigned char *)(fbp+offset+2)=(unsigned char)color.R;
        *(unsigned char *)(fbp+offset+3)=(unsigned char)color.A;
    }
    return 0;
}

//color_i: A8R8G8B8
inline int lcddev_t::drawPoint(const Point_t& pos,const unsigned int& color_i)
{
    Color_t color;
    color.A=(unsigned char)(color_i>>24)&0xff;
    color.R=(unsigned char)(color_i>>16)&0xff;
    color.G=(unsigned char)(color_i>>8)&0xff;
    color.B=(unsigned char)(color_i)&0xff;
    return (drawPoint(pos.x,pos.y,color));
}

//color_i: A8R8G8B8
inline int lcddev_t::drawPoint(const unsigned int& x,const unsigned int& y,const unsigned int& color_i)
{
    Color_t color;
    color.A=(unsigned char)(color_i>>24)&0xff;
    color.R=(unsigned char)(color_i>>16)&0xff;
    color.G=(unsigned char)(color_i>>8)&0xff;
    color.B=(unsigned char)(color_i)&0xff;
    return (drawPoint(x,y,color));
}

inline int lcddev_t::clearPoint(const Point_t& pos,const Color_t& color)
{
    return drawPoint(pos,color);
}
inline int lcddev_t::clearPoint(const unsigned int& x,const unsigned int& y,const Color_t color)
{
    return drawPoint(x,y,color);
}
inline int lcddev_t::clearPoint(const Point_t& pos,const unsigned int& color_i)
{
    return drawPoint(pos,color_i);
}
inline int lcddev_t::clearPoint(const unsigned int& x,const unsigned int& y,const unsigned int& color_i)
{
    return drawPoint(x,y,color_i);
}


inline int lcddev_t::drawAera(const Point_t& LeftTop,const Point_t&RightBot,const Color_t& color)
{
    for(int row=LeftTop.y;row<=RightBot.y;row++)
        for(int col=LeftTop.x;col<=RightBot.x;col++)
            if(drawPoint(col,row,color)<0)
                return -1;
    return 0;
}
inline int lcddev_t::drawAera(const Point_t& LeftTop,const Point_t&RightBot,const unsigned int& color_i)
{
    for(int row=LeftTop.y;row<=RightBot.y;row++)
        for(int col=LeftTop.x;col<=RightBot.x;col++)
            if(drawPoint(col,row,color_i)<0)
                return -1;
    return 0;
}
inline int lcddev_t::drawAera(const unsigned int& x_LeftTop,const unsigned int& y_LeftTop,const unsigned int& x_RightBot,\
            const unsigned int& y_RightBot,const Color_t& color)
{
    for(unsigned int row=y_LeftTop;row<=y_RightBot;row++)
        for(unsigned int col=x_LeftTop;col<=x_RightBot;col++)
            if(drawPoint(col,row,color)<0)
                return -1;
    return 0;
}
inline int lcddev_t::drawAera(const unsigned int& x_LeftTop,const unsigned int& y_LeftTop,const unsigned int& x_RightBot,\
            const unsigned int& y_RightBot,const unsigned int& color_i)
{
    for(unsigned int row=y_LeftTop;row<=y_RightBot;row++)
        for(unsigned int col=x_LeftTop;col<=x_RightBot;col++)
            if(drawPoint(col,row,color_i)<0)
                return -1;
    return 0;

}


inline int lcddev_t::clearAeratoWhite(const Point_t& LeftTop,const Point_t&RightBot)
{
    return clearAeratoWhite(LeftTop.x,LeftTop.y,RightBot.x,RightBot.y);
}
inline int lcddev_t::clearAeratoWhite(const unsigned int& x_LeftTop,const unsigned int& y_LeftTop,const unsigned int& x_RightBot,\
            const unsigned int& y_RightBot)
{
    if(isInit!=1)
       // if(init_lcddev()<0)
        return -1;
    if(!isFbpMap)
        if(lcddev_mMap()<0)
            return -1;
    if(x_RightBot>xres||y_RightBot>yres||x_LeftTop>xres||y_LeftTop>yres)
        return -1;
    int rowSize=x_RightBot-x_LeftTop+1;

    int oneSize=rowSize*(bits_per_pixel/8);
    int offset=0;
    for(unsigned int row=y_LeftTop;row<=y_RightBot;row++)
    {
        offset=(row*xres+x_LeftTop)*(bits_per_pixel/8);
        memset(fbp+offset,0xff,oneSize);
    }
    return 0;
}

inline int lcddev_t::clearAeratoBlack(const Point_t& LeftTop,const Point_t&RightBot)
{
    return clearAeratoBlack(LeftTop.x,LeftTop.y,RightBot.x,RightBot.y);
}
inline int lcddev_t::clearAeratoBlack(const unsigned int& x_LeftTop,const unsigned int& y_LeftTop,const unsigned int& x_RightBot,\
            const unsigned int& y_RightBot)
{
    if(isInit!=1)
       // if(init_lcddev()<0)
        return -1;
    if(!isFbpMap)
        if(lcddev_mMap()<0)
            return -1;
    if(x_RightBot>xres||y_RightBot>yres||x_LeftTop>xres||y_LeftTop>yres)
        return -1;
    int rowSize=x_RightBot-x_LeftTop+1;

    int oneSize=rowSize*(bits_per_pixel/8);
    int offset=0;
    for(unsigned int row=y_LeftTop;row<=y_RightBot;row++)
    {
        offset=(row*xres+x_LeftTop)*(bits_per_pixel/8);
        memset(fbp+offset,0x00,oneSize);
    }
    return 0;
}
inline int lcddev_t::clearAlltoWhite()
{
    if(isInit!=1)
       // if(init_lcddev()<0)
        return -1;
    if(!isFbpMap)
        if(lcddev_mMap()<0)
            return -1;
    memset(fbp,0xff,ScreenSize);
    return 0;
}
inline int lcddev_t::clearAlltoBlack()
{
    if(isInit!=1)
        return -1;
    if(!isFbpMap)
        if(lcddev_mMap()<0)
            return -1;
    memset(fbp,0x00,ScreenSize);
    return 0;
}
inline int lcddev_t::clearAll()
{
    return clearAlltoBlack();
}

/*
char isInit;
char isFbpMap;
unsigned char *fbp;
int fd;
int ScreenSize;
int xres;
int yres;
int bits_per_pixel;
char* devfile;
*/
inline int lcddev_t::init_lcddev(char* devfile_v)
{
    if(isInit==1)
        return -1;
    /*if(!islcddevHadCreated(devfile_v))      //判断同一个lcddev是否已经创建
    {
        printf("the lcddev had been created\n");
        return -1;
    }*/
    /*if(count>10)
    {
        printf("lcddev that had been created has up on 10\n");
        return -1;
    }*/
    devfile=devfile_v;
    fd=open(devfile,O_RDWR);
    if(fd<0)
    {
        printf("can not open file: %s\n",devfile);
        return -1;
    }

    //count+=1;
    //devfile_s[count-1]=devfile_v;
    numid=numObjs;
    struct fb_var_screeninfo vinfo;
    ioctl(fd,FBIOGET_VSCREENINFO,&(vinfo));
    xres=vinfo.xres;
    yres=vinfo.yres;
    bits_per_pixel=vinfo.bits_per_pixel;
    ScreenSize=((xres)*(yres)*(bits_per_pixel))/8;
    isFbpMap=0;
    fbp=NULL;
    close(fd);
    fd=-1;
    isInit=1;
    return 0;
}

inline int lcddev_t::lcddev_mMap()
{
    if(!isInit)
        //if(init_lcddev()<0)
        return -1;
    isInit=1;
    if(isFbpMap==0)
    {
        fd=open(devfile,O_RDWR);
        if(fd<0)
            return -1;
        fbp=(unsigned char*)mmap(0,ScreenSize,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
        if(fbp==NULL)
            return -1;
        isFbpMap=1;
    }
    return 0;
}

inline int lcddev_t::lcddev_mUnmap()
{
    if(isFbpMap==1)
    {
        munmap(fbp,ScreenSize);
        isFbpMap=0;
        fbp=NULL;
        close(fd);
        fd=-1;
    }
    return 0;
}
/*
inline bool lcddev_t::islcddevHadCreated(char* devfile_v)
{
    for(int i=0;i<count;i++)
    {
        if(strcmp(devfile_v,devfile_s[i])==0)
        {
            return false;
        }
    }
    return true;
}
*/
inline lcdObjCount::lcdObjCount(char* desr)
{
    init(desr);
}
/*
template<typename T>
inline lcdObjCount<T>::lcdObjCount(const lcdObjCount&rhs)
{
    init();
}
*/
inline int lcdObjCount::init(char* desr)
{
    if(numObjs>MaxlcdObjnum)
        throw TooManyObj();
    if(isObjHad(desr))
        throw ObjHad();
    ++numObjs;
    ObjDescrition[numObjs-1]=desr;
    return 0;
}

inline bool lcdObjCount::isObjHad(char* desr)
{
    for(int i=0;i<numObjs;i++)
        if(strcmp(desr,ObjDescrition[i])==0)
            return true;
    return false;

}

#endif
