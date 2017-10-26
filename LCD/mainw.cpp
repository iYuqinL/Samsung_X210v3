//main.cpp
#include <stdlib.h>
#include <stdio.h>
#include "tftlcd.hpp"
#include "window.hpp"

int main()
{
    struct Point_t beg;
    struct Point_t end;
    beg.x=1500;beg.y=20;
    end.x=1700;end.y=200;
    struct Point_t point1(1500,20),point2(1700,20),point3(1700,200),point4(1500,200);
    lcddev_t lcd;
    window_t win(&lcd);
    //lcddev_t lcd1((char*)"/dev/fb1");
    win.drawLine(point1,point3,Green);
    win.drawLine(point3,point1,Red);
    win.drawLine(point2,point4,Blue);
    win.drawLine(point4,point2,Green);
    //lcd.drawLine(1500,10,1500,420,Red);
    //lcd.drawLine(1700,10,1700,420,Red);
    win.drawCircle(end,100,White);
    win.drawRect(beg,end,Red);
    //lcd.drawAera(beg,end,White);
    //lcd.clearAeratoBlack(beg,end);
    //lcd.clearAll();
    win.showChar(1500,150,'C',BIG,White);
    win.showString(1500,300,(char*)"I am yusnows!",BIG,White);
    printf("lcd fbp start ADDR: %p\n",lcd.getfbp());
    lcd.mUnmap();
    printf("lcd xres: %d\n",lcd.getxres());
    printf("lcd yres: %d\n",lcd.getyres());
    printf("ScreenSize: %d\n",lcd.getScreenSize());
    printf("lcd fbp start ADDR: %p\n",lcd.getfbp());
    return 0;
}
