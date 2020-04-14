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
    void on_plainTextEdit_textChanged();

    void on_pushButton_2_clicked();

    void mousePressEvent(QMouseEvent *events); //Function Detects Mouse Press as MainWindow is Launched

    void ddaLine(int,int,int,int);

    void plotPoint(int,int);

    void erasePoint(int,int);

    void on_verticalSlider_valueChanged(int value);

    void on_verticalSlider_2_valueChanged(int value);

    void on_verticalSlider_3_valueChanged(int value);

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void floodFillRecursive(int,int,QRgb);

    void floodFillIterative(int,int,QRgb);

private:
    Ui::MainWindow *ui;
    int coordinates[100][2];
    int vertices;
    bool start;
};

#endif // MAINWINDOW_H
