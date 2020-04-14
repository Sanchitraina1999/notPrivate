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
private slots:
    void mousePressEvent(QMouseEvent *events);
    void mouseReleaseEvent(QMouseEvent *events);
    void drawBox();
    void ddaLine(int,int,int,int);
    int computeCode(int,int);
    void cohenSutherlandClip(int);


    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    int coordinates[50][4];
};

#endif // MAINWINDOW_H
