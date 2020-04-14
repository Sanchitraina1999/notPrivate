#include "mainwindow.h" 
#include "ui_mainwindow.h"
#include "QMouseEvent"
#include "iostream"
using namespace std;

/**************Global Variables**************/
#define INSIDE 0
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8

QImage image(941,621,QImage::Format_RGB888);
QRgb white=qRgb(255,255,255);
QRgb black=qRgb(0,0,0);
int xMin,xMax,yMin,yMax,n=0;
bool box=false,line=false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setPixmap(QPixmap::fromImage(image));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *events)
{
    if(box==true){
        if(events->button()==Qt::LeftButton){
            xMax=events->pos().x();
            yMax=events->pos().y();
        }
    }
    if(line==true){
        if(events->button()==Qt::LeftButton){
            coordinates[n][0]=events->pos().x();
            coordinates[n][1]=events->pos().y();
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *events)
{
    if(box==true){
        if(events->button()==Qt::LeftButton){
            xMin=events->pos().x();
            yMin=events->pos().y();
            drawBox();
        }
    }
    if(line==true){
        if(events->button()==Qt::LeftButton){
            coordinates[n][2]=events->pos().x();
            coordinates[n][3]=events->pos().y();
            ddaLine(coordinates[n][0],coordinates[n][1],coordinates[n][2],coordinates[n][3]);
            n++;
        }
    }
}

void MainWindow::drawBox()
{
    ddaLine(xMin,yMin,xMax,yMin);
    ddaLine(xMin,yMin,xMin,yMax);
    ddaLine(xMax,yMin,xMax,yMax);
    ddaLine(xMin,yMax,xMax,yMax);

    int x1=xMin;
    int y1=yMin;
    int x2=xMax;
    int y2=yMax;

    xMin=min(x1,x2);
    xMax=max(x1,x2);

    yMin=min(y1,y2);
    yMax=max(y1,y2);


    cout<<"\n"<<xMin<<","<<yMin;
    cout<<"\n"<<xMax<<","<<yMax;

    box=false;
}

void MainWindow::ddaLine(int x1, int y1, int x2, int y2)
{
    float dx,dy,steps,xinc,yinc;
    dx=x2-x1;
    dy=y2-y1;

    steps=abs(dx)>abs(dy)?abs(dx):abs(dy);
    xinc=dx/steps;
    yinc=dy/steps;

    float x=x1;
    float y=y1;

    for(int i=0;i<=steps;i++){
        image.setPixel(x,y,white);
        x=x+xinc;
        y=y+yinc;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}

int MainWindow::computeCode(int x, int y)
{
    int code=INSIDE;
    if(x<xMin)
        code=code|LEFT;
    if(x>xMax)
        code=code|RIGHT;
    if(y<yMin)
        code=code|BOTTOM;
    if(y>yMax)
        code=code|TOP;

    return code;
}

void MainWindow::cohenSutherlandClip(int i)
{
    int x1=coordinates[i][0];
    int y1=coordinates[i][1];
    int x2=coordinates[i][2];
    int y2=coordinates[i][3];

    int code1=computeCode(x1,y1);
    int code2=computeCode(x2,y2);

    bool clipped=false;

    while(true){
        if(code1==0 && code2==0){
            clipped=true;
            break;
        }
        else if(code1 & code2)
            break;
        else{
            int codeOut,x,y;

            if(code1)
                codeOut=code1;
            else
                codeOut=code2;

            if(codeOut & TOP){
                x=x1+(x2-x1)*(yMax-y1)/(y2-y1);
                y=yMax;
            }
            else if(codeOut & BOTTOM){
                x=x1+(x2-x1)*(yMin-y1)/(y2-y1);
                y=yMin;
            }
            else if(codeOut & RIGHT){
                x=xMax;
                y=y1+(y2-y1)*(xMax-x1)/(x2-x1);
            }
            else if(codeOut & LEFT){
                x=xMin;
                y=y1+(y2-y1)*(xMin-x1)/(x2-x1);
            }
            if(code1==codeOut){
                x1=x;
                y1=y;
                code1=computeCode(x1,y1);
            }
            else{
                x2=x;
                y2=y;
                code2=computeCode(x2,y2);
            }
        }
    }
    if(clipped){
        coordinates[i][0]=x1;
        coordinates[i][1]=y1;
        coordinates[i][2]=x2;
        coordinates[i][3]=y2;
        cout<<"\nClipped!";
    }
    else{
        coordinates[i][0]=0;
        coordinates[i][1]=0;
        coordinates[i][2]=0;
        coordinates[i][3]=0;
        cout<<"\nRejected";
    }
}

void MainWindow::on_pushButton_clicked()    //Box
{
    box=true;
    line=false;
}

void MainWindow::on_pushButton_2_clicked()      //Line
{
    line=true;
    box=false;
}

void MainWindow::on_pushButton_3_clicked()      //Clip
{
    for(int i=0;i<=n;i++)
        cohenSutherlandClip(i);
    image.fill(black);
    drawBox();
    for(int i=0;i<=n;i++)
        ddaLine(coordinates[i][0],coordinates[i][1],coordinates[i][2],coordinates[i][3]);
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}

void MainWindow::on_pushButton_4_clicked()      //Clear
{
    image.fill(black);
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
    n=0;
}
