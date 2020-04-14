#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"
#include "iostream"
#include "QtMath"
#include "XMatrix.cpp"
using namespace std;

/**************Global Variables**************/
QImage image(931,701,QImage::Format_RGB888);
QRgb white=qRgb(255,255,255);
QRgb black=qRgb(0,0,0);
bool start=false;
int i=0,x01,x02,y01,y02;
float tx,ty,sx,sy,theta;
XMatrix *polygon;
XMatrix r(3),s(3),t(3);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setPixmap(QPixmap::fromImage(image));
    vertices=0;
    start=false;
    ddaLine(465,0,465,700);
    ddaLine(0,350,930,350);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *events){
    int x,y;
    if(!start)return;
    if(i<vertices){
        x=events->pos().x();
        y=events->pos().y();
        if(x>=15&&x<=931&&y>=32&&y<=701){
            coordinates[i][0]=x-10;
            coordinates[i][1]=y-30;
            image.setPixel(x-10,y-30,white);
            ui->label->setPixmap(QPixmap::fromImage(image));
            ui->label->show();
            i++;
        }
    }
    if(i==vertices){
        initCentroid();
        drawPolygon();
        start=false;
        coordinatesToXMatrix();
    }
}
void MainWindow::initCentroid(){
    gx=0;
    gy=0;
    for(int i=0;i<vertices;i++){
        gx+=coordinates[i][0];
        gy+=coordinates[i][1];
    }
    gx=gx/vertices;
    gy=gy/vertices;

}
void MainWindow::drawPolygon(){
    for(int i=0;i<vertices-1;i++){
        x01=coordinates[i][0];
        y01=coordinates[i][1];
        x02=coordinates[i+1][0];
        y02=coordinates[i+1][1];
        ddaLine(x01,y01,x02,y02);
    }
    x01=coordinates[0][0];
    y01=coordinates[0][1];
    ddaLine(x01,y01,x02,y02);
}

void MainWindow::ddaLine(int x01, int y01, int x02, int y02){
    float dx,dy,steps,xinc,yinc;
    dx=x02-x01;
    dy=y02-y01;

    steps=abs(dx)>abs(dy)?abs(dx):abs(dy);
    xinc=dx/steps;
    yinc=dy/steps;

    float x=x01;
    float y=y01;

    for(int i=0;i<=steps;i++){
        image.setPixel(x,y,white);
        x=x+xinc;
        y=y+yinc;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
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

void MainWindow::setTranslationMatrix(float tx, float ty)
{
    t.matrix[0][0]=1,   t.matrix[0][1]=0,   t.matrix[0][2]=0;

    t.matrix[1][0]=0,   t.matrix[1][1]=1,   t.matrix[1][2]=0;

    t.matrix[2][0]=tx,  t.matrix[2][1]=ty,  t.matrix[2][2]=1;
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

void MainWindow::setScalingMatrix(float sx, float sy)
{
    s.matrix[0][0]=sx,  s.matrix[0][1]=0,   s.matrix[0][2]=0;

    s.matrix[1][0]=0,   s.matrix[1][1]=sy,  s.matrix[1][2]=0;

    s.matrix[2][0]=0,   s.matrix[2][1]=0,   s.matrix[2][2]=1;
}

void MainWindow::on_textEdit_textChanged()  //No. of Points
{
    QString str=ui->textEdit->toPlainText();
    vertices=str.toInt();
    start=true;
    i=0;
    polygon=new XMatrix(vertices);
}

void MainWindow::on_textEdit_2_textChanged()    //Sx
{
    QString str=ui->textEdit_2->toPlainText();
    sx=str.toFloat();
}

void MainWindow::on_textEdit_3_textChanged()    //Sy
{
    QString str=ui->textEdit_3->toPlainText();
    sy=str.toFloat();
}

void MainWindow::on_textEdit_4_textChanged()    //Tx
{
    QString str=ui->textEdit_4->toPlainText();
    tx=str.toFloat();
}

void MainWindow::on_textEdit_5_textChanged()    //Ty
{
    QString str=ui->textEdit_5->toPlainText();
    ty=str.toFloat();
    ty*=-1;
}

void MainWindow::on_textEdit_6_textChanged()    //Angle
{
    QString str=ui->textEdit_6->toPlainText();
    theta=str.toFloat();
}

void MainWindow::on_pushButton_clicked()    //Scale
{
    setTranslationMatrix(-gx,-gy);
    (*polygon)=(*polygon)*t;

    setScalingMatrix(sx,sy);
    (*polygon)=(*polygon)*s;

    setTranslationMatrix(gx,gy);
    (*polygon)=(*polygon)*t;

    XMatrixToCoordinates();
    drawPolygon();
}

void MainWindow::on_pushButton_2_clicked()      //Translate
{
    setTranslationMatrix(tx,ty);
    (*polygon)=(*polygon)*t;
    XMatrixToCoordinates();
    initCentroid();
    drawPolygon();
}

void MainWindow::on_pushButton_5_clicked()      //Translate to (0,0)
{
    setTranslationMatrix(-gx+465,-gy+350);
    (*polygon)=(*polygon)*t;
    XMatrixToCoordinates();
    initCentroid();
    drawPolygon();
}

void MainWindow::on_pushButton_3_clicked()      //Rotate
{
    setTranslationMatrix(-gx,-gy);
    (*polygon)=(*polygon)*t;

    setRotationMatrix(theta);
    (*polygon)=(*polygon)*r;

    setTranslationMatrix(gx,gy);
    (*polygon)=(*polygon)*t;

    XMatrixToCoordinates();
    drawPolygon();
}

void MainWindow::on_pushButton_4_clicked()      //Clear
{
    i=0;
    polygon=NULL;
    image.fill(black);
    ddaLine(465,0,465,700);
    ddaLine(0,350,930,350);
    if(vertices)
        on_textEdit_textChanged();
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();

}

