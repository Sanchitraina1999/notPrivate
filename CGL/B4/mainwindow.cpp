#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "XMatrix.cpp"
#include "QMouseEvent"
#include "QtMath"

/***********Global Variables**********/

QImage image(981,671,QImage::Format_RGB888);        //center:(490,335)

QRgb black=qRgb(0,0,0);
QRgb red=qRgb(255,0,0);
QRgb green=qRgb(0,255,0);
QRgb blue=qRgb(0,0,255);
QRgb white=qRgb(255,255,255);

int rx=490,ry=335,i=0;
int x01,y01,x02,y02;
float tx,ty,sx=1,sy=1,theta=0;
bool start,point;
XMatrix *polygon;
XMatrix r(3),t(3);
/************************************/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    image.fill(black);
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
    drawReflectionAxes();
    start=false;
    point=false;
    vertices=0;
    i=0;
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(false);

}

void MainWindow::on_textEdit_textChanged()
{
    QString str=ui->textEdit->toPlainText();
    vertices=str.toInt();
    start=true;
    i=0;
    polygon=new XMatrix(vertices);

}

void MainWindow::on_textEdit_2_textChanged()
{
    QString str=ui->textEdit_2->toPlainText();
    theta=str.toFloat();

}

void MainWindow::on_pushButton_clicked()        //X-Axis
{
    XMatrix reflect(3);

    reflect.matrix[0][0]=1,  reflect.matrix[0][1]=0,  reflect.matrix[0][2]=0;

    reflect.matrix[1][0]=0,  reflect.matrix[1][1]=-1,  reflect.matrix[1][2]=0;

    reflect.matrix[2][0]=0,  reflect.matrix[2][1]=0,  reflect.matrix[2][2]=1;

    QPoint reflectedG=reflectedCentroid(0,1,-335);
    float reflectedGx=reflectedG.x();
    float reflectedGy=reflectedG.y();

    (*polygon)=(*polygon)*reflect;
    XMatrixToCoordinates();
    initCentroid();

    setTranslationMatrix(-gx,-gy);
    (*polygon)=(*polygon)*t;

    setTranslationMatrix(reflectedGx,reflectedGy);
    (*polygon)=(*polygon)*t;

    XMatrixToCoordinates();
    initCentroid();
    drawPolygon();


}

void MainWindow::on_pushButton_2_clicked()      //Y-Axis
{
    XMatrix reflect(3);

    reflect.matrix[0][0]=-1,  reflect.matrix[0][1]=0,  reflect.matrix[0][2]=0;

    reflect.matrix[1][0]=0,  reflect.matrix[1][1]=1,  reflect.matrix[1][2]=0;

    reflect.matrix[2][0]=0,  reflect.matrix[2][1]=0,  reflect.matrix[2][2]=1;

    QPoint reflectedG=reflectedCentroid(1,0,-490);
    float reflectedGx=reflectedG.x();
    float reflectedGy=reflectedG.y();

    (*polygon)=(*polygon)*reflect;
    XMatrixToCoordinates();
    initCentroid();

    setTranslationMatrix(-gx,-gy);
    (*polygon)=(*polygon)*t;

    setTranslationMatrix(reflectedGx,reflectedGy);
    (*polygon)=(*polygon)*t;

    XMatrixToCoordinates();
    initCentroid();
    drawPolygon();
}

void MainWindow::on_pushButton_3_clicked()      //Line: X=Y
{
    XMatrix reflect(3);

    reflect.matrix[0][0]=0,  reflect.matrix[0][1]=-1,  reflect.matrix[0][2]=0;

    reflect.matrix[1][0]=-1,  reflect.matrix[1][1]=0,  reflect.matrix[1][2]=0;

    reflect.matrix[2][0]=0,  reflect.matrix[2][1]=0,   reflect.matrix[2][2]=1;

    QPoint reflectedG=reflectedCentroid(1,1,-825);
    float reflectedGx=reflectedG.x();
    float reflectedGy=reflectedG.y();

    (*polygon)=(*polygon)*reflect;
    XMatrixToCoordinates();
    initCentroid();

    setTranslationMatrix(-gx,-gy);
    (*polygon)=(*polygon)*t;

    setTranslationMatrix(reflectedGx,reflectedGy);
    (*polygon)=(*polygon)*t;

    XMatrixToCoordinates();
    initCentroid();
    drawPolygon();
}

void MainWindow::on_pushButton_4_clicked()      //Select Point
{
    point=true;
}

void MainWindow::on_pushButton_5_clicked()      //Rotate
{
    setTranslationMatrix(-rx,-ry);
    (*polygon)=(*polygon)*t;

    setRotationMatrix(theta);
    (*polygon)=(*polygon)*r;

    setTranslationMatrix(rx,ry);
    (*polygon)=(*polygon)*t;

    XMatrixToCoordinates();
    drawPolygon();
}

void MainWindow::on_pushButton_6_clicked()      //Clear
{
    image.fill(black);
    drawReflectionAxes();
    i=0;
    vertices=0;
    ui->textEdit->clear();
    ui->textEdit->clear();
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    start=point=false;
}

void MainWindow::mousePressEvent(QMouseEvent *events)
{
    int x,y;
//    int x=events->pos().x()-20;
//    int y=events->pos().y()-30;
    if(start==true){
        if(i<vertices){
            x=events->pos().x()-20;
            y=events->pos().y()-30;
            if(x>=0&&x<=981&&y>=0&&y<=671){
                coordinates[i][0]=x;
                coordinates[i][1]=y;
                image.setPixel(x,y,white);
                ui->label->setPixmap(QPixmap::fromImage(image));
                ui->label->show();
                i++;
            }
        }
        if(i==vertices){
            drawPolygon();
            initCentroid();
            drawPolygon();
            start=false;
            coordinatesToXMatrix();
            ui->pushButton->setEnabled(true);
            ui->pushButton_2->setEnabled(true);
            ui->pushButton_3->setEnabled(true);
            ui->pushButton_4->setEnabled(true);
            ui->pushButton_5->setEnabled(true);
        }
    }
    else if(point==true){
        x=events->pos().x()-20;
        y=events->pos().y()-30;
        if(x>=0&&x<=981&&y>=0&&y<=671){
            rx=x;
            ry=y;
            image.setPixel(x,y,white);
            ui->label->setPixmap(QPixmap::fromImage(image));
            ui->label->show();
            point=false;
        }
    }
}

void MainWindow::setTranslationMatrix(float tx, float ty)
{
    t.matrix[0][0]=1,   t.matrix[0][1]=0,   t.matrix[0][2]=0;

    t.matrix[1][0]=0,   t.matrix[1][1]=1,   t.matrix[1][2]=0;

    t.matrix[2][0]=tx,  t.matrix[2][1]=ty,  t.matrix[2][2]=1;
}

QPoint MainWindow::reflectedCentroid(int a, int b, int c)
{
    QPoint centroid;
    float x,y;
    x=(gx*(b*b-a*a)-2*a*(b*gy+c))/(a*a+b*b);
    y=(gy*(a*a-b*b)-2*b*(a*gx+c))/(a*a+b*b);
    centroid.setX(x);
    centroid.setY(y);
    return centroid;
}

void MainWindow::setRotationMatrix(float deg)
{
    float rad=qDegreesToRadians(deg);
    float cos=qCos(rad);
    float sin=qSin(rad);

    r.matrix[0][0]=cos,  r.matrix[0][1]=sin,  r.matrix[0][2]=0;

    r.matrix[1][0]=-sin, r.matrix[1][1]=cos,  r.matrix[1][2]=0;

    r.matrix[2][0]=0,    r.matrix[2][1]=0,    r.matrix[2][2]=1;

}

void MainWindow::ddaLine(int x01, int y01, int x02, int y02, QRgb color)
{
    float dx,dy,steps,xinc,yinc;
    dx=x02-x01;
    dy=y02-y01;

    steps=abs(dx)>abs(dy)?abs(dx):abs(dy);
    xinc=dx/steps;
    yinc=dy/steps;

    float x=x01;
    float y=y01;

    for(int i=0;i<=steps;i++){
        image.setPixel(x,y,color);
        x=x+xinc;
        y=y+yinc;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}

void MainWindow::drawPolygon()
{
    for(int i=0;i<vertices-1;i++){
        x01=coordinates[i][0];
        y01=coordinates[i][1];
        x02=coordinates[i+1][0];
        y02=coordinates[i+1][1];
        ddaLine(x01,y01,x02,y02,green);
    }
    x01=coordinates[0][0];
    y01=coordinates[0][1];
    ddaLine(x01,y01,x02,y02,green);
}

void MainWindow::drawReflectionAxes()
{
    ddaLine(0,335,980,335,white);
    ddaLine(490,0,490,670,white);
    ddaLine(155,670,825,0,white);
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}

void MainWindow::initCentroid()
{
    gx=0;
    gy=0;
    for(int i=0;i<vertices;i++){
        gx+=coordinates[i][0];
        gy+=coordinates[i][1];
    }
    gx/=vertices;
    gy/=vertices;
}

void MainWindow::coordinatesToXMatrix()
{
    for(int i=0;i<vertices;i++){
        polygon->matrix[i][0]=coordinates[i][0];
        polygon->matrix[i][1]=coordinates[i][1];
    }
}

void MainWindow::XMatrixToCoordinates()
{
    for(int i=0;i<vertices;i++){
        coordinates[i][0]=polygon->matrix[i][0];
        coordinates[i][1]=polygon->matrix[i][1];
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
