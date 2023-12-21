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



void Brezenhem(int x0, int y0, int x1, int y1,std::vector<std::vector<int>>& Wall)
{
    int size = 5;
    int arr = 0;
    int A, B, sign;

    A = y1 - y0;
    B = x0 - x1;

    if (abs(A) > abs(B)) sign = 1;
    else sign = -1;

    int signa, signb;

    if (A < 0) signa = -1;
    else signa = 1;

    if (B < 0) signb = -1;
    else signb = 1;

  int f = 0;
  int x = x0, y = y0;

  if (sign == -1)
  {
    do {
      f += A*signa;
      if (f > 0)
      {
        f -= B*signb;
        y += signa;
      }
      x -= signb;
      Wall.resize(size,std::vector<int>(2));
      Wall[arr][0] = x;
      Wall[arr][1] = y;
      arr++;
      size++;
    } while (x != x1 || y != y1);
  }
  else
  {
    do {
      f += B*signb;
      if (f > 0) {
        f -= A*signa;
        x -= signb;
      }
      y += signa;
      Wall.resize(size,std::vector<int>(2));
      Wall[arr][0] = x;
      Wall[arr][1] = y;
      arr++;
      size++;
    } while (x != x1 || y != y1);
  }
}

void Brezenhem_for_vect(int x0, int y0, int x1, int y1,std::vector<std::vector<int>>& Wall)
{

    int size = 1;
    int arr = 0;
    int A, B, sign;

    A = y1 - y0;
    B = x0 - x1;

    if (abs(A) > abs(B)) sign = 1;
    else sign = -1;

    int signa, signb;

    if (A < 0) signa = -1;
    else signa = 1;

    if (B < 0) signb = -1;
    else signb = 1;

  int f = 0;
  int x = x0, y = y0;
  bool trig = false;

  if (sign == -1)
  {
    do {
      f += A*signa;
      if (f > 0)
      {
        f -= B*signb;
        y += signa;
      }
      x -= signb;
      x == x1 && y == y1 ? trig = true:1;
      if(trig == true)
      {
          Wall.resize(size,std::vector<int>(2));
          Wall[arr][0] = x;
          Wall[arr][1] = y;
          arr++;
          size++;

      }


    } while (x != 0 && y != 0);
  }
  else
  {
    do {
      f += B*signb;
      if (f > 0) {
        f -= A*signa;
        x -= signb;
      }
      y += signa;
      x == x1 && y == y1 ? trig = true:1;
      if(trig == true)
      {
          Wall.resize(size,std::vector<int>(2));
          Wall[arr][0] = x;
          Wall[arr][1] = y;
          arr++;
          size++;

      }
    } while (x != 0 && y != 0);

  }

}
void kvadrant_init(int wall_posX1,int wall_posY1, int router_posX,int router_posY, std::vector<std::vector<int>>& vect1,int dx1,int dy1)
{



    if(wall_posX1 <= router_posX && wall_posY1 <= router_posY)// 1 kvadrant
    {
        int x = wall_posX1;
        int y = wall_posY1;
        int i = 0;
        int size = 1;
        std::cout<<"x y  = "<<x<<" "<<y<<"\n";
        vect1.resize(size,std::vector<int>(2));//координаты    вектор

        while(x > 0 || y > 0)
        {
            x = x - dx1;
            y = y - dy1;
            vect1[i][0] = x;
            vect1[i][1] = y;
            size++;
            vect1.resize(size,std::vector<int>(2));//координаты    вектор
            //std::cout<<vect1[i][0]<<" "<<vect1[i][1]<<"\n";
            i++;
            //std::cout<<"size /= "<<size<<"\n";
        }
        //for(auto i:vect1) std::cout<<i[0]<<" "<<i[1]<<"\n";

        std::cout<<"size = "<<size<<"\n";
    }
    else if (wall_posX1 <= router_posX && wall_posY1 >= router_posY)//3 kvadrant
    {
        int x = wall_posX1;
        int y = wall_posY1;
        int i = 0;
        int size = 1;

        vect1.resize(size,std::vector<int>(2));//координаты    вектор

         while(x >= 0 || y >= H)
        {
             x = x - dx1;
             y = y + dy1;
            vect1[i][0] = x;
            vect1[i][1] = y;
            size++;
            vect1.resize(size,std::vector<int>(2));//координаты    вектор
        }
        std::cout<<"size 2 kv = "<<size<<"\n";




    }
    else if (wall_posX1 >= router_posX && wall_posY1 <= router_posY)//2 kvadrant
    {


        int x = wall_posX1;
        int y = wall_posY1;
        int i = 0;
        int size = 1;
        std::cout<<"x y  = "<<x<<" "<<y<<"\n";
        vect1.resize(size,std::vector<int>(2));//координаты    вектор

        while(x < W && y > 0)
        {
            x = x + dx1;
            y = y - dy1;
            vect1[i][0] = x;
            vect1[i][1] = y;
            size++;
            vect1.resize(size,std::vector<int>(2));//координаты    вектор
            //std::cout<<vect1[i][0]<<" "<<vect1[i][1]<<"\n";
            i++;
            //std::cout<<"size /= "<<size<<"\n";
        }
        for(auto i:vect1) std::cout<<i[0]<<" "<<i[1]<<"\n";

        std::cout<<"size = "<<size<<"\n";

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


void print_zone(std::vector<std::vector<int>>& vect,std::vector<std::vector<int>>& Wall)
{
    int iter = vect.size();

     int dcord = 0;
    for(int i = 0; i < iter; i++)
    {

        int y = vect[i][1];
        //Wall[vect[i][0]][vect[i][1]] = Wall[vect[i][0]][vect[i][1]] - 10;
        //std::cout<<vect[i][0]<<" "<<vect[i][1]<<"\n";
        //std::cout<<Wall[vect[i][0]][y]<<"\n";
        if(dcord != vect[i][0])
        {
            std::cout<<dcord<<"\n";
            while(y != 0)
            {

               //std::cout<<Wall[vect[i][0]][y]<<"\n"; //= Wall[vect[i][0]][y] - 10;
               Wall[vect[i][0]][y]= Wall[vect[i][0]][y] - 10;
                y--;
                dcord = vect[i][0];
            }

        }

    }
}


void Wall_loss(int wall_posX1,int wall_posY1,int wall_posX2,int wall_posY2,int router_posX,int router_posY,std::vector<std::vector<int>>& Wall,std::vector<std::vector<int>>& Lmap)//передаем координаты ху начала и конца стены,массив координат точек стены и координаты роутера
{
    std::vector<std::vector<int>> vect1;
    std::vector<std::vector<int>> vect2;

    int wx1 = wall_posX1;
    int wy1 = wall_posY1;

    int wx2 = wall_posX2;
    int wy2 = wall_posY2;

    int rx = router_posX;
    int ry = router_posY;
    std::cout<<"wxwy "<<wx2<<" "<<wy2<<"\n";

    Brezenhem_for_vect(rx,ry,wx1,wy1,vect1);
    Brezenhem_for_vect(rx,ry,wx2,wy2,vect2);

    std::cout<<"vect2: "<<vect2.size()<<"\n";


   print_zone(vect1,Lmap);
   print_zone(vect2,Lmap);
   print_zone(Wall,Lmap);
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

        struct Point {
        int x;
        int y;
    };

        struct wall
    {
        int cellPosX1;
        int cellPosX2;
        int cellPosY1;
        int cellPosY2;
        float material;
        float thickness;
        Point start;
        Point end;


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
        w1.start.x = 300;
        w1.start.y = 300;
        w1.end.x = 600;
        w1.end.y = 100;

        wall w2;
        w2.start.x = 250;
        w2.start.y = 450;
        w2.end.x = 450;
        w2.end.y = 350;

        std::vector<std::vector<int>> vect;
        std::vector<std::vector<int>> newall;

        std::vector<std::vector<int>> Lmap;
        Lmap.resize(1001,std::vector<int>(1001));//уровень сиггнала в каждой точке

        QPixmap map(maxX, maxY); // создаем карту для рисования
        QPainter p(&map);



         std::cout<<"Lmap "<<Lmap.size()<<"\n";
        for(int i = 0; i < maxX; i++){

            for(int j = 0; j < maxY; j++){
                float distance = 0;
                distance = sqrt(pow(abs(r1.cellPosX - i),2) + pow(abs(r1.cellPosY - j),2)); //[pix]
                distance *= onePixDistance; // [meters]
                float sigPower = r1.TxPower + r1.antGain - PL(r1.freq, distance);

                Lmap[i][j] = sigPower;
            }


        }

        Brezenhem(w1.start.x,w1.start.y,w1.end.x,w1.end.y,vect);
        Brezenhem(w2.start.x,w2.start.y,w2.end.x,w2.end.y,newall);
        //Brezenhem_for_vect(500,500,600,100,newall);



        Wall_loss(w1.start.x,w1.start.y,w1.end.x,w1.end.y,r1.cellPosX,r1.cellPosY,vect,Lmap);
        Wall_loss(w2.start.x,w2.start.y,w2.end.x,w2.end.y,r1.cellPosX,r1.cellPosY,newall,Lmap);

        for(int i = 0; i < maxX; i++)
        {
            for(int j = 0; j < maxY; j++)
            {

                int lPL = -100;
                int hPL = -90;
                int dist_kaf = 10;

                Lmap[i][j] < hPL && Lmap[i][j] >= lPL ?
                            color1 = 156,color2 =0,color3 = 156:
                            hPL+=dist_kaf,
                            lPL+= dist_kaf;
                Lmap[i][j] < hPL && Lmap[i][j] >= lPL ?
                            color1 = 0,color2 =0,color3 = 156:
                            hPL+=dist_kaf, lPL+=dist_kaf;
                Lmap[i][j] < hPL && Lmap[i][j] >= lPL ?
                            color1 = 0,color2 =156,color3 = 156:
                            hPL+=dist_kaf, lPL+=dist_kaf;
                Lmap[i][j] < hPL && Lmap[i][j] >= lPL ?
                            color1 = 0,color2 =156,color3 = 0:
                            hPL+=dist_kaf, lPL+=dist_kaf;
                Lmap[i][j] < hPL && Lmap[i][j] >= lPL ?
                            color1 = 156,color2 =155,color3 = 0:
                            hPL+=dist_kaf, lPL+=dist_kaf;
                Lmap[i][j] < hPL && Lmap[i][j] >= lPL ?
                            color1 = 156,color2 =0,color3 = 0:
                            hPL+=dist_kaf, lPL+=dist_kaf;
                p.setPen(QColor(color1, color2, color3, kaf)); // <-- задание цвета
                p.drawPoint(i, j);
            }


        }

        for(int i = 0; i < newall.size(); i++){//отрисовка 1 стены

            p.setPen(QColor(255, 255, 255, 255)); // <-- задание цвета
            p.drawPoint(newall[i][0], newall[i][1]);


        }
        for(int i = 0; i < vect.size(); i++){//отрисовка 1 стены

            p.setPen(QColor(255, 255, 255, 255)); // <-- задание цвета
            p.drawPoint(vect[i][0], vect[i][1]);


        }


        p.end();
        scene->addPixmap(map);
        QGraphicsView* view = new QGraphicsView(scene);
        setCentralWidget(view);



}

MainWindow::~MainWindow()
{
}

