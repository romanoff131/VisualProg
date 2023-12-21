#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mainwindow.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtMath>
#include <QDebug>


#define height = 1000;
#define weight = 1000;

const int H = 1000;
const int W = 1000;


float PL(float f, float d){
    return 28 + 22 * log10(f) + 20* log10(d);
}
void kvadrant_init(int wall_posX1,int wall_posY1, int router_posX,int router_posY, std::vector<std::vector<int>>& vect1,int dx1,int dy1)
{



    if(wall_posX1 <= router_posX && wall_posY1 < router_posY)// 1 kvadrant
    {
        int x = wall_posX1;
        int y = wall_posY1;
        int i = 0;
        int size = 1;

        vect1.resize(size,std::vector<int>(2));//координаты    вектор

        while(x >= 0 || y >= 0)
        {
            x = x - dx1;
            y = y - dy1;
            vect1[i][0] = x;
            vect1[i][1] = y;
            size++;
            vect1.resize(size,std::vector<int>(2));//координаты    вектор
        }
        std::cout<<"size = "<<size<<"\n";
    }
    else if (wall_posX1 <= router_posX && wall_posY1 >= router_posY)//3 kvadrant
    {

        int x = wall_posX1;
        int y = wall_posY1;

        while(x >= 0 || y >= H)
        {
            x = x - dx1;
            y = y + dy1;
        }

    }
    else if (wall_posX1 >= router_posX && wall_posY1 <= router_posY)//2 kvadrant
    {

        int x = wall_posX1;
        int y = wall_posY1;

        while(x <= W || y >= 0)
        {
            x = x + dx1;
            y = y - dy1;
        }

    }
    else if (wall_posX1 >= router_posX && wall_posY1 >= router_posY)//4 kvadrant
    {

        int x = wall_posX1;
        int y = wall_posY1;

        while(x <= W || y <= H)
        {
            x = x + dx1;
            y = y + dy1;
        }

    }

}


void Wall_loss(int wall_posX1,int wall_posY1,int wall_posX2,int wall_posY2,int router_posX,int router_posY,std::vector<std::vector<int>>& Wall)
{
    int dx1 = 0;
    int dy1 = 0;

    int dx2 = 0;
    int dy2 = 0;

    dx1 = abs((wall_posX1-wall_posX2)/100); // 500-300 =200//// dx1 =2
    dy1 = abs((wall_posY1-wall_posY2)/100);// 500 - 300 = 200/// dy1 =2

    int wx1 = wall_posX1;
    int wy1 = wall_posX2;
    int rx = router_posX;
    int ry = router_posY;




    std::vector<std::vector<int>> vect1;
    std::vector<std::vector<int>> vect2;
    kvadrant_init(wx1,wy1,rx,ry,vect1,dx1,dy1);




}



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    struct router
    {
        int TxPower;
        int antGain;
        float freq;

        int cellPosX;
        int cellPosY;



    };

    struct wall
    {
        int cellPosX1;
        int cellPosX2;
        int cellPosY1;
        int cellPosY2;
        float material;
        float thickness;


    };






        QGraphicsScene* scene = new QGraphicsScene();
        int maxX = W;
        int maxY = H;

        int onePixDistance = 5; //[m]


        router r1;
        r1.TxPower = 23; // [dBm]
        r1.antGain = 12; // [dBi]
        r1.freq = 2.5; // [GHz]

        r1.cellPosX = 500;
        r1.cellPosY = 500;

        int color1 = 0;
        int color2 = 17;
        int color3 = 155;
        int kaf = 255;



        wall w1;
        w1.cellPosX1 = 300;
        w1.cellPosY1= 300;
        w1.cellPosX2 = 600;
        w1.cellPosY2 = 100;

        int dx = 0;
        int dy = 0;
        int targx = 0;
        int targy = 0;

        w1.cellPosX1 < w1.cellPosX2 ? targx = w1.cellPosX1 : targx = w1.cellPosX2;
        w1.cellPosY1 > w1.cellPosY2 ? targy = w1.cellPosY1 : targy = w1.cellPosY2;

        dx = abs((w1.cellPosX1-w1.cellPosX2)/100); // 300-600 =-300
        dy = abs((w1.cellPosY1-w1.cellPosY2)/100);// 300 - 100 = 200
        //std::cout<<dx<<"dx \t"<<dy<<"dy \n";

        int c = abs((w1.cellPosX1-w1.cellPosX2)/dx);
        std::cout<<c;


        std::vector<std::vector<int>> vect;
        vect.resize(310,std::vector<int>(2));//координаты стены

        std::vector<std::vector<int>> Lmap;
        vect.resize(1000,std::vector<int>(1000));//уровень сиггнала в каждой точке


        bool trig = true;
        for(int x = targx,y = targy,cx=0;
            trig;
            cx++)
        {

            vect[cx][0]=x;
            vect[cx][1]=y;

            cx < c ? x+=dx,y-=dy:trig = 0;
            //std::cout<<cx<<"\n";
            //std::cout<<x<<"dx \t"<<y<<"dy \n";
            //std::cout<<vect[cx][0]<<"\t";
            //std::cout<<vect[cx][1]<<"\n";
        }


//        for(int i = 0; i < 300; i++){


//           std::cout<<vect[i][0]<<"\t";
//           std::cout<<vect[i][1]<<"\n";

//        }









        QPixmap map(maxX, maxY); // создаем карту для рисования
        QPainter p(&map);
        //p.setPen(QColor(255, 0, 0, 255)); // <-- задание цвета




        for(int i = 0; i < maxX; i++){

            for(int j = 0; j < maxY; j++){




                float distance = 0;
                distance = sqrt(pow(abs(r1.cellPosX - i),2) + pow(abs(r1.cellPosY - j),2)); // [pix]
                distance *= onePixDistance; // [meters]
                float sigPower = r1.TxPower + r1.antGain - PL(r1.freq, distance);
                Lmap[i][j]=sigPower;


                //std::cout<< sigPower<<"\n";
                // - 64 -54 ,-54 -44, -44 -34, -34 -24, -24 -14, -14 -4

                int lPL = -80;
                int hPL = -70;
                int dist_kaf = 10;
                //std::cout<<sigPower<<"\n";

                sigPower < hPL && sigPower >= lPL ?
                            color1 = 156,color2 =0,color3 = 156:
                            hPL+=dist_kaf,
                            lPL+= dist_kaf;
                sigPower < hPL && sigPower >= lPL ?
                            color1 = 0,color2 =0,color3 = 156:
                            hPL+=dist_kaf, lPL+=dist_kaf;
                sigPower < hPL && sigPower >= lPL ?
                            color1 = 0,color2 =156,color3 = 156:
                            hPL+=dist_kaf, lPL+=dist_kaf;
                sigPower < hPL && sigPower >= lPL ?
                            color1 = 0,color2 =156,color3 = 0:
                            hPL+=dist_kaf, lPL+=dist_kaf;
                sigPower < hPL && sigPower >= lPL ?
                            color1 = 156,color2 =155,color3 = 0:
                            hPL+=dist_kaf, lPL+=dist_kaf;
                sigPower < hPL && sigPower >= lPL ?
                            color1 = 156,color2 =0,color3 = 0:
                            hPL+=dist_kaf, lPL+=dist_kaf;
                p.setPen(QColor(color1, color2, color3, kaf)); // <-- задание цвета
                p.drawPoint(i, j);





                //std::cout<< color1<<"\t"<<color2<<"\t"<<color3<<"\n";
            }


        }








        for(int i = 0; i < 300; i++){

            p.setPen(QColor(255, 255, 255, 255)); // <-- задание цвета
            p.drawPoint(vect[i][0], vect[i][1]);


        }


        for(int i = 0; i < maxX; i++){

            for(int j = 0; j < maxY; j++)
            {
            int deltax = abs(i - r1.cellPosX);
            int deltay = abs(j -r1.cellPosY);
            int d = sqrt(pow(deltax,2) + pow(deltay,2));
            //std::cout<<d<<"\n";



            std::vector<std::vector<int>> pef;
            pef.resize(d,std::vector<int>(2));


        }

}




        p.end();
        scene->addPixmap(map);
        QGraphicsView* view = new QGraphicsView(scene);
        setCentralWidget(view);



}

MainWindow::~MainWindow()
{
}

