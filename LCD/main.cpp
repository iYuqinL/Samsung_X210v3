//main.cpp
#include <stdlib.h>
#include <stdio.h>
#include "tftlcd.hpp"

int main()
{
    struct Point_t beg;
    struct Point_t end;
    beg.x=300;beg.y=20;
    end.x=600;end.y=200;
    struct Point_t point1(300,20),point2(600,20),point3(600,200),point4(300,200);
    lcddev_t lcd;
    lcddev_t lcd1((char*)"/dev/fb1");
    lcd.drawLine(point1,point3,Green);
    lcd.drawLine(point3,point1,Red);
    lcd.drawLine(point2,point4,Blue);
    lcd.drawLine(point4,point2,Green);
    //lcd.drawLine(1500,10,1500,420,Red);
    //lcd.drawLine(1700,10,1700,420,Red);
    lcd.drawCircle(end,100,White);
    lcd.drawRect(beg,end,Red);
    //lcd.drawAera(beg,end,White);
    //lcd.clearAeratoBlack(beg,end);
    //lcd.clearAll();
    lcd.showChar(400,200,'C',BIG,White);
    printf("lcd fbp start ADDR: %p\n",lcd.getfbp());
    lcd.mUnmap();
    printf("lcd xres: %d\n",lcd.getxres());
    printf("lcd yres: %d\n",lcd.getyres());
    printf("ScreenSize: %d\n",lcd.getScreenSize());
    printf("bits_per_pisel: %d\n",lcd.getbits_per_pixel());
    printf("lcd fbp start ADDR: %p\n",lcd.getfbp());
    return 0;
}
