#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Stack.cpp"

/********Global Variables********/
QImage image(921,591,QImage::Format_RGB888);
QImage pallete(71,31,QImage::Format_RGB888);
QRgb white=qRgb(255,255,255);
QRgb black=qRgb(0,0,0);
QRgb boundColor;  
QRgb color=white;
int i=0,x1,y1,x2,y2,r,g,b;
int seedX,seedY;
bool flag=false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pallete.fill(color);
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label_3->setPixmap(QPixmap::fromImage(pallete));
    vertices=0;
    start=false;
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::mousePressEvent(QMouseEvent *events){
    int x,y;
    if(!start)return;
    if(i<vertices){
        if(events->button()==Qt::LeftButton){
            x=events->pos().x();
            y=events->pos().y();
            if(x>=15&&x<=925&&y>=32&&y<=613){
                coordinates[i][0]=x-10;
                coordinates[i][1]=y-30;
                plotPoint(x-10,y-30);
                i++;
            }
        }
    }
    else if(i==vertices){
        if(events->button()==Qt::RightButton){
            x=events->pos().x();
            y=events->pos().y();
            seedX=x-10;
            seedY=y-30;
            i++;
            plotPoint(seedX,seedY);
        }
    }
}
void MainWindow::on_plainTextEdit_textChanged()
{
    QString str=ui->plainTextEdit->toPlainText();
    vertices=str.toInt();
    start=true;
    i=0;
}

void MainWindow::on_pushButton_2_clicked()
{
    for(int i=0;i<vertices-1;i++){
        x1=coordinates[i][0];
        y1=coordinates[i][1];
        x2=coordinates[i+1][0];
        y2=coordinates[i+1][1];
        ddaLine(x1,y1,x2,y2);
    }
    x1=coordinates[0][0];
    y1=coordinates[0][1];
    ddaLine(x1,y1,x2,y2);
    boundColor=color;
    flag=true;
}
void MainWindow::ddaLine(int x1, int y1, int x2, int y2){
    float dx,dy,steps,xinc,yinc;
    dx=x2-x1;
    dy=y2-y1;

    steps=abs(dx)>abs(dy)?abs(dx):abs(dy);
    xinc=dx/steps;
    yinc=dy/steps;

    float x=x1;
    float y=y1;

    for(int i=0;i<=steps;i++){
        image.setPixel(x,y,color);
        x=x+xinc;
        y=y+yinc;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}

void MainWindow::plotPoint(int x, int y)
{
    for(int i=-1;i<=1;i++)
        for(int j=-1;j<=1;j++)
            image.setPixel(x+i,y+j,white);

    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}

void MainWindow::erasePoint(int x,int y)
{
    for(int i=-1;i<=1;i++)
        for(int j=-1;j<=1;j++)
            image.setPixel(x+i,y+j,black);

    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}
void MainWindow::on_verticalSlider_valueChanged(int value)
{
    r=value;
    color=qRgb(r,g,b);
    pallete.fill(color);
    if(flag)
        on_pushButton_2_clicked();
    ui->label_3->setPixmap(QPixmap::fromImage(pallete));
    ui->label_3->show();
}

void MainWindow::on_verticalSlider_2_valueChanged(int value)
{
    g=value;
    color=qRgb(r,g,b);
    pallete.fill(color);
    if(flag)
        on_pushButton_2_clicked();
    ui->label_3->setPixmap(QPixmap::fromImage(pallete));
    ui->label_3->show();
}

void MainWindow::on_verticalSlider_3_valueChanged(int value)
{
    b=value;
    color=qRgb(r,g,b);
    pallete.fill(color);
    if(flag)
        on_pushButton_2_clicked();
    ui->label_3->setPixmap(QPixmap::fromImage(pallete));
    ui->label_3->show();
}

void MainWindow::on_pushButton_clicked()
{
    image.fill(qRgb(0,0,0));
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    erasePoint(seedX,seedY);
    floodFillIterative(seedX,seedY,color);
//    floodFillRecursive(seedX,seedY,color);
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}

void MainWindow::floodFillRecursive(int x,int y,QRgb newColor){
    QRgb currentColor=image.pixel(x,y);
    if (x < 0 || x >= 921 || y < 0 || y >= 591)
        return;
    if(currentColor==newColor||currentColor==boundColor)
        return;
    image.setPixel(x,y,newColor);
    floodFillRecursive(x+1,y,newColor);
    floodFillRecursive(x-1,y,newColor);
    floodFillRecursive(x,y+1,newColor);
    floodFillRecursive(x,y-1,newColor);
}

void MainWindow::floodFillIterative(int x, int y, QRgb newColor)
{
   QRgb currentColor=image.pixel(x,y);
   Stack<QPoint> stack;
   QPoint point0(x,y),point1,point2,point3,point4;
   stack.push(point0);
   while(!stack.empty()){

       point0=stack.top();
       stack.pop();
       x=point0.x();
       y=point0.y();
       image.setPixel(x,y,newColor);
       currentColor=image.pixel(x+1,y);

       if(currentColor!=newColor&&currentColor!=boundColor){
           point1.setX(x+1);
           point1.setY(y);
           stack.push(point1);
       }

       currentColor=image.pixel(x-1,y);
       if(currentColor!=newColor&&currentColor!=boundColor){
           point2.setX(x-1);
           point2.setY(y);
           stack.push(point2);
       }

       currentColor=image.pixel(x,y+1);
       if(currentColor!=newColor&&currentColor!=boundColor){
           point3.setX(x);
           point3.setY(y+1);
           stack.push(point3);
       }

       currentColor=image.pixel(x,y-1);
       if(currentColor!=newColor&&currentColor!=boundColor){
           point4.setX(x);
           point4.setY(y-1);
           stack.push(point4);
       }
   }
}
