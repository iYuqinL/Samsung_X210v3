#ifndef _WINDOW_H_
#define _WINDOW_H_
#include "tftlcd.hpp"
//#include <vector>
#include <unordered_map>

const int MaxChildwinnum=10;
const int defChildwinnum=4;


class window_t
{
public:
    inline window_t();
    inline window_t(lcddev_t* target);
    inline window_t(const Point_t&LT,const Point_t&RB);
    inline window_t(lcddev_t* target,const Point_t&LT,const Point_t&RB);

    inline ~window_t();
public:
    inline int createChildwin(const Point_t&LT,const Point_t&RB);
    inline int deleteChildwin(const int& winID);
    
    inline int showString(const int&x,const int&y,char*str,const font_t&size=NORMAL,const Color_t& color=White);
    inline int showString(const int&x,const int&y,char*str,const font_t&size=NORMAL,const int& color_i=0xffffffff);
    inline int showString(const Point_t&pos,char* str,const font_t&size=NORMAL,const Color_t&color=White);
    inline int showString(const Point_t&pos,char* str,const font_t&size=NORMAL,const int&color_i=0xffffffff);

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

    inline int drawPoint(const int&x,const int&y,const Color_t&color);
    inline int drawPoint(const Point_t&pos,const Color_t&color);
    inline int drawPoint(const int&x,const int&y,const int& color_i);
    inline int drawPoint(const Point_t&pos,const int&color_i);

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

protected:
    lcddev_t* ptarget;
    Point_t leftTop;
    Point_t rightBot;
    int parentwinID;
    int winID;
    std::unordered_map<int,window_t*> Childwin;
private:
    inline bool isChildwinFull();
};

inline window_t::window_t()
{
    leftTop.x=0;
    leftTop.y=0;
    rightBot.x=0;
    rightBot.y=0;
    parentwinID=0;
    winID=0;
    ptarget=NULL;
}
    
inline window_t::window_t(lcddev_t* target)
{
    leftTop.x=0;
    leftTop.y=0;
    rightBot.x=(*target).getxres();
    rightBot.y=(*target).getyres();
    parentwinID=0;
    winID=0;
    ptarget=target;
}
inline window_t::window_t(const Point_t&LT,const Point_t&RB)
{
    leftTop.x=LT.x;
    leftTop.y=LT.y;
    rightBot.x=RB.x;
    rightBot.y=RB.y;
    parentwinID=0;
    winID=0;
    ptarget=NULL;
}
inline window_t::window_t(lcddev_t* target,const Point_t&LT,const Point_t&RB)
{
    leftTop.x=LT.x;
    leftTop.y=LT.y;
    rightBot.x=RB.x;
    rightBot.y=RB.y;
    parentwinID=0;
    winID=0;
    ptarget=target;
}

inline window_t::~window_t()
{
    for(auto x:Childwin)
        if(x.second!=NULL)
            delete x.second;
}

inline int window_t::createChildwin(const Point_t&LT,const Point_t&RB)
{
    if(isChildwinFull())
        return -1;
    if(LT.x<this->leftTop.x||LT.y<this->leftTop.y||RB.x>rightBot.x||RB.y>rightBot.y)
        return -2;
    window_t* newChildwin=new window_t(this->ptarget,LT,RB);
    (*newChildwin).parentwinID=this->winID;
    int i=1;        //除非是屏幕下的初始窗口，不然winID都不能是0，必须从1开始。
    for(i=1;i<MaxChildwinnum+1;i++)
        if(Childwin.find(i)==Childwin.end())
            break;
    (*newChildwin).winID=i;
    Childwin[(*newChildwin).winID]=newChildwin;
    return (*newChildwin).winID;
}
inline int window_t::deleteChildwin(const int& winID)
{
    
    //window_t *tmpwin=this->Childwin.find(tmp);
    window_t* tmpwin=this->Childwin[winID];
    if(tmpwin!=NULL)
        delete tmpwin;
    Childwin.erase(winID);
    return winID;
}

inline int window_t::showString(const int&x,const int&y,char* str,const font_t&size,const Color_t& color)
{
    int tmpx=x;
    int tmpy=y;
    char* tmpstr=str;
    if(x<leftTop.x)
        tmpx=leftTop.x;
    if(y<leftTop.y)
        tmpy=leftTop.y;
    while((*tmpstr<='~')&&(*tmpstr>=' '))//判断是不是非法字符!
    {       
        if(tmpx>=rightBot.x){tmpx=leftTop.x;tmpy+=size;}
        if(tmpy>=rightBot.y)break;//退出
        showChar(tmpx,tmpy,*tmpstr,size,color);
        tmpx+=size/2;
        tmpstr++;
    }
    return 0;
}
inline int window_t::showString(const int&x,const int&y,char*str,const font_t&size,const int& color_i)
{
    int tmpx=x;
    int tmpy=y;
    char* tmpstr=str;
    if(x<leftTop.x)
        tmpx=leftTop.x;
    if(y<leftTop.y)
        tmpy=leftTop.y;
    while((*tmpstr<='~')&&(*tmpstr>=' '))//判断是不是非法字符!
    {       
        if(tmpx>=rightBot.x){tmpx=leftTop.x;tmpy+=size;}
        if(tmpy>=rightBot.y)break;//退出
        showChar(tmpx,tmpy,*tmpstr,size,color_i);
        tmpx+=size/2;
        tmpstr++;
    }
    return 0;

}
inline int window_t::showString(const Point_t&pos,char* str,const font_t&size,const Color_t&color)
{
    int tmpx=pos.x;
    int tmpy=pos.y;
    char* tmpstr=str;
    if(pos.x<leftTop.x)
        tmpx=leftTop.x;
    if(pos.y<leftTop.y)
        tmpy=leftTop.y;
    while((*tmpstr<='~')&&(*tmpstr>=' '))//判断是不是非法字符!
    {       
        if(tmpx>=rightBot.x){tmpx=leftTop.x;tmpy+=size;}
        if(tmpy>=rightBot.y)break;//退出
        showChar(tmpx,tmpy,*tmpstr,size,color);
        tmpx+=size/2;
        tmpstr++;
    }
    return 0;

}
inline int window_t::showString(const Point_t&pos,char* str,const font_t&size,const int&color_i)
{
    int tmpx=pos.x;
    int tmpy=pos.y;
    char* tmpstr=str;
    if(pos.x<leftTop.x)
        tmpx=leftTop.x;
    if(pos.y<leftTop.y)
        tmpy=leftTop.y;
    while((*tmpstr<='~')&&(*tmpstr>=' '))//判断是不是非法字符!
    {       
        if(tmpx>=rightBot.x){tmpx=leftTop.x;tmpy+=size;}
        if(tmpy>=rightBot.y)break;//退出
        showChar(tmpx,tmpy,*tmpstr,size,color_i);
        tmpx+=size/2;
        tmpstr++;
    }
    return 0;

}


inline int window_t::showChar(const int&x,const int& y,const char Char,const font_t& size,const Color_t& color)
{
    if(ptarget==NULL)
        return -1;
    if((x+size/2)>rightBot.x||x<leftTop.x||(y+size)>rightBot.y||y<leftTop.y)
        return -2;
    return (*ptarget).showChar(x,y,Char,size,color);
    
}
inline int window_t::showChar(const Point_t& pos,const char Char,const font_t& size,const Color_t& color)
{
    if(ptarget==NULL)
        return -1;
    if(pos.x<leftTop.x||(pos.x+size/2)>rightBot.x||pos.y<leftTop.y||(pos.y+size)>rightBot.y)
        return -2;
    return (*ptarget).showChar(pos,Char,size,color);
}
inline int window_t::showChar(const int&x,const int&y,const char Char,const font_t& size,const int& color_i)
{
    if(ptarget==NULL)
        return -1;
    if((x+size/2)>rightBot.x||x<leftTop.x||(y+size)>rightBot.y||y<leftTop.y)
        return -2;
    return (*ptarget).showChar(x,y,Char,size,color_i);

}
inline int window_t::showChar(const Point_t& pos,const char Char,const font_t& size,const int& color_i)
{
    if(ptarget==NULL)
        return -1;
    if(pos.x<leftTop.x||(pos.x+size/2)>rightBot.x||pos.y<leftTop.y||(pos.y+size)>rightBot.y)
        return -2;
    return (*ptarget).showChar(pos,Char,size,color_i);

}

inline int window_t:: drawCircle(const Point_t& center,const unsigned int& r,const Color_t& color)
{
   return (drawCircle(center.x,center.y,r,color));
}
inline int window_t::drawCircle(const Point_t& center,const unsigned int& r,const unsigned int& color_i)
{
    Color_t color;
    color.A=(unsigned char)(color_i>>24)&0xff;
    color.R=(unsigned char)(color_i>>16)&0xff;
    color.G=(unsigned char)(color_i>>8)&0xff;
    color.B=(unsigned char)(color_i)&0xff;
    return (drawCircle(center.x,center.y,r,color));

}
inline int window_t::drawCircle(const unsigned int& x_center,const unsigned int& y_center,const unsigned int& r,\
                    const Color_t& color)
{
    int xPos=0;
    int yPos=0;
    for(float theda=0;theda<=2*Pi;theda+=0.01)
    {
        xPos=(int)((float)r*cosf(theda)+x_center);
        yPos=(int)((float)r*sinf(theda)+y_center);
        if(xPos<leftTop.x)
            xPos=leftTop.x;
        else if(xPos>rightBot.x)
            xPos=rightBot.x;
        if(yPos<leftTop.y)
            yPos=leftTop.y;
        else if(yPos>rightBot.y)
            yPos=rightBot.y;
        if(drawPoint((unsigned int)xPos,(unsigned int)yPos,color)<0)
            return -1;
    }
    return 0;

}
inline int window_t::drawCircle(const unsigned int& x_center,const unsigned int& y_center,const unsigned int& r,\
                    const unsigned int& color_i)
{
    Color_t color;
    color.A=(unsigned char)(color_i>>24)&0xff;
    color.R=(unsigned char)(color_i>>16)&0xff;
    color.G=(unsigned char)(color_i>>8)&0xff;
    color.B=(unsigned char)(color_i)&0xff;
    return (drawCircle(x_center,y_center,r,color));

}
    
inline int window_t::drawRect(const Point_t& LeftTop,const Point_t& RightBot,const Color_t& color,\
                    const unsigned int& width)
{
    return (drawRect(LeftTop.x,LeftTop.y,RightBot.x,RightBot.y,color,width));
}
inline int window_t::drawRect(const Point_t& LeftTop,const Point_t& RightBot,const unsigned int& color_i,\
                    const unsigned int& width)
{
    Color_t color;
    color.A=(unsigned char)(color_i>>24)&0xff;
    color.R=(unsigned char)(color_i>>16)&0xff;
    color.G=(unsigned char)(color_i>>8)&0xff;
    color.B=(unsigned char)(color_i)&0xff;
    return (drawRect(LeftTop.x,LeftTop.y,RightBot.x,RightBot.y,color,width));
}
inline int window_t::drawRect(const unsigned int& x_LeftTop,const unsigned int& y_LeftTop,const unsigned int& x_RightBot,\
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
inline int window_t::drawRect(const unsigned int& x_LeftTop,const unsigned int& y_LeftTop,const unsigned int& x_RightBot,\
                    const unsigned int& y_RightBot,const unsigned int& color_i,const unsigned int& width)
{
    Color_t color;
    color.A=(unsigned char)(color_i>>24)&0xff;
    color.R=(unsigned char)(color_i>>16)&0xff;
    color.G=(unsigned char)(color_i>>8)&0xff;
    color.B=(unsigned char)(color_i)&0xff;

    return (drawRect(x_LeftTop,y_LeftTop,x_RightBot,y_RightBot,color,width));

}

inline int window_t::drawLine(const Point_t& beg,const Point_t& end,const Color_t& color,\
                    const unsigned int& width)
{
    return (drawLine(beg.x,beg.y,end.x,end.y,color,width));
}
inline int window_t::drawLine(const Point_t& beg,const Point_t& end,const unsigned int& color_i,\
                    const unsigned int& width)
{
    Color_t color;
    color.A=(unsigned char)(color_i>>24)&0xff;
    color.R=(unsigned char)(color_i>>16)&0xff;
    color.G=(unsigned char)(color_i>>8)&0xff;
    color.B=(unsigned char)(color_i)&0xff;
    return (drawLine(beg.x,beg.y,end.x,end.y,color,width));
}
inline int window_t::drawLine(const unsigned int& x_beg,const unsigned int& y_beg,const unsigned int& x_end,\
        const unsigned int& y_end,const Color_t& color,const unsigned int& width)
{
    if(ptarget==NULL)
        return -1;
    //对于是否超出区域范围，交于drawPoint函数来判断处理
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
inline int window_t::drawLine(const unsigned int& x_beg,const unsigned int& y_beg,const unsigned int& x_end,\
        const unsigned int& y_end,const unsigned int& color_i,const unsigned int& width)
{
    Color_t color;
    color.A=(unsigned char)(color_i>>24)&0xff;
    color.R=(unsigned char)(color_i>>16)&0xff;
    color.G=(unsigned char)(color_i>>8)&0xff;
    color.B=(unsigned char)(color_i)&0xff;
    return (drawLine(x_beg,y_beg,x_end,y_end,color,width));
}

inline int window_t::drawAera(const Point_t& LeftTop,const Point_t&RightBot,const Color_t& color)
{
    if(ptarget==NULL)
        return -1;
    for(int row=LeftTop.y;row<=RightBot.y;row++)
        for(int col=LeftTop.x;col<=RightBot.x;col++)
            if(drawPoint(col,row,color)<0)
                return -1;
    return 0;
}
inline int window_t::drawAera(const Point_t& LeftTop,const Point_t&RightBot,const unsigned int& color_i)
{    
    if(ptarget==NULL)
        return -1;

    for(int row=LeftTop.y;row<=RightBot.y;row++)
        for(int col=LeftTop.x;col<=RightBot.x;col++)
            if(drawPoint(col,row,color_i)<0)
                return -1;
    return 0;
}
inline int window_t::drawAera(const unsigned int& x_LeftTop,const unsigned int& y_LeftTop,const unsigned int& x_RightBot,\
            const unsigned int& y_RightBot,const Color_t& color)
{    
    if(ptarget==NULL)
        return -1;

    for(unsigned int row=y_LeftTop;row<=y_RightBot;row++)
        for(unsigned int col=x_LeftTop;col<=x_RightBot;col++)
            if(drawPoint(col,row,color)<0)
                return -1;
    return 0;
}
inline int window_t::drawAera(const unsigned int& x_LeftTop,const unsigned int& y_LeftTop,const unsigned int& x_RightBot,\
            const unsigned int& y_RightBot,const unsigned int& color_i)
{    
    if(ptarget==NULL)
        return -1;

    for(unsigned int row=y_LeftTop;row<=y_RightBot;row++)
        for(unsigned int col=x_LeftTop;col<=x_RightBot;col++)
            if(drawPoint(col,row,color_i)<0)
                return -1;
    return 0;

}

inline int window_t::clearAeratoWhite(const Point_t& LeftTop,const Point_t&RightBot)
{
    if(ptarget==NULL)
        return -1;
    Point_t tmpleft,tmpright;
    tmpleft.x=LeftTop.x;
    tmpleft.y=LeftTop.y;
    tmpright.x=RightBot.x;
    tmpright.y=RightBot.y;
    if(LeftTop.x<leftTop.x)
        tmpleft.x=leftTop.x;
    if(LeftTop.y<leftTop.y)
        tmpleft.y=leftTop.y;
    if(RightBot.x>rightBot.x)
        tmpright.x=rightBot.x;
    if(RightBot.y>rightBot.y)
        tmpright.y=rightBot.y;
    return (*ptarget).clearAeratoWhite(tmpleft,tmpright);
}
inline int window_t::clearAeratoWhite(const unsigned int& x_LeftTop,const unsigned int& y_LeftTop,const unsigned int& x_RightBot,\
            const unsigned int& y_RightBot)
{
    if(ptarget==NULL)
        return -1;
    unsigned int tmpxleft=x_LeftTop;
    unsigned int tmpxright=x_RightBot;
    unsigned int tmpyleft=y_LeftTop;
    unsigned int tmpyright=y_RightBot;
    if(x_LeftTop<(unsigned int)leftTop.x)
        tmpxleft=leftTop.x;
    if(y_LeftTop<(unsigned int)leftTop.y)
        tmpyleft=leftTop.y;
    if(x_RightBot>(unsigned int)rightBot.x)
        tmpxright=rightBot.x;
    if(y_RightBot>(unsigned int)rightBot.y)
        tmpyright=rightBot.y;
    return (*ptarget).clearAeratoWhite(x_LeftTop,y_LeftTop,x_RightBot,y_RightBot);
}

inline int window_t::clearAeratoBlack(const Point_t& LeftTop,const Point_t&RightBot)
{
    if(ptarget==NULL)
        return -1;
    Point_t tmpleft,tmpright;
    tmpleft.x=LeftTop.x;
    tmpleft.y=LeftTop.y;
    tmpright.x=RightBot.x;
    tmpright.y=RightBot.y;
    if(LeftTop.x<leftTop.x)
        tmpleft.x=leftTop.x;
    if(LeftTop.y<leftTop.y)
        tmpleft.y=leftTop.y;
    if(RightBot.x>rightBot.x)
        tmpright.x=rightBot.x;
    if(RightBot.y>rightBot.y)
        tmpright.y=rightBot.y;
    return (*ptarget).clearAeratoBlack(tmpleft,tmpright);

}
inline int window_t::clearAeratoBlack(const unsigned int& x_LeftTop,const unsigned int& y_LeftTop,const unsigned int& x_RightBot,\
            const unsigned int& y_RightBot)
{
    if(ptarget==NULL)
        return -1;
    unsigned int tmpxleft=x_LeftTop;
    unsigned int tmpxright=x_RightBot;
    unsigned int tmpyleft=y_LeftTop;
    unsigned int tmpyright=y_RightBot;
    if(x_LeftTop<(unsigned int)leftTop.x)
        tmpxleft=leftTop.x;
    if(y_LeftTop<(unsigned int)leftTop.y)
        tmpyleft=leftTop.y;
    if(x_RightBot>(unsigned int)rightBot.x)
        tmpxright=rightBot.x;
    if(y_RightBot>(unsigned int)rightBot.y)
        tmpyright=rightBot.y;
    return (*ptarget).clearAeratoBlack(x_LeftTop,y_LeftTop,x_RightBot,y_RightBot);
}

inline int window_t::clearAlltoWhite()
{
   if(ptarget==NULL)
       return -1;
   return (*ptarget).clearAeratoWhite(leftTop,rightBot);
}
inline int window_t::clearAlltoBlack()
{
    if(ptarget==NULL)
        return -1;
    return (*ptarget).clearAeratoBlack(leftTop,rightBot);
}
inline int window_t::clearAll()
{
    return clearAlltoBlack();
}

inline int  window_t::drawPoint(const int&x,const int&y,const Color_t&color)
{
    if(ptarget==NULL)
        return -1;
    if(x>rightBot.x||x<leftTop.x||y<leftTop.y||y>rightBot.y)
        return -2;
    return (*ptarget).drawPoint(x,y,color);
}
inline int  window_t::drawPoint(const Point_t&pos,const Color_t&color)
{
    if(ptarget==NULL)
        return -1;
    if(pos.x<leftTop.x||pos.x>rightBot.x||pos.y<leftTop.y||pos.y>rightBot.y)
        return -2;
    return (*ptarget).drawPoint(pos,color);
}
inline int window_t::drawPoint(const int&x,const int&y,const int&color_i)
{
    if(ptarget==NULL)
        return -1;
    if(x>rightBot.x||x<leftTop.x||y<leftTop.y||y>rightBot.y)
        return -2;
    return (*ptarget).drawPoint(x,y,color_i);

}
inline int window_t::drawPoint(const Point_t&pos,const int&color_i)
{
    if(ptarget==NULL)
        return -1;
    if(pos.x<leftTop.x||pos.x>rightBot.x||pos.y<leftTop.y||pos.y>rightBot.y)
        return -2;
    return (*ptarget).drawPoint(pos,color_i);

}


inline bool window_t::isChildwinFull()
{
    if(Childwin.size()>MaxChildwinnum)
        return false;
    else
        return true;
}
#endif

