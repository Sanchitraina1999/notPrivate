#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void mousePressEvent(QMouseEvent *events);
    void ddaLine(int,int,int,int);
    void initCentroid();
    void coordinatesToXMatrix();
    void XMatrixToCoordinates();
    void setTranslationMatrix(float,float);
    void setRotationMatrix(float);
    void setScalingMatrix(float,float);
    void drawPolygon();

private slots:
    void on_textEdit_textChanged();

    void on_textEdit_2_textChanged();

    void on_textEdit_3_textChanged();

    void on_textEdit_4_textChanged();

    void on_textEdit_5_textChanged();

    void on_textEdit_6_textChanged();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    int coordinates[100][2];
    int vertices;
    int gx,gy;
};

#endif // MAINWINDOW_H
