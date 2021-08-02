#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QGraphicsEffect>
#include <QGraphicsDropShadowEffect>
#include <QMessageBox>
#include <QRegExp>
#include <QRegExpValidator>
#include <windows.h>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int resc_num;
    int client_num;
    static const int max=30;
    int Alloc[max][max];
    int Avail[max];
    int resc[max];
    int Max[max][max];
    int Need[max][max];
    QVector<int> ans;        //安全队列
    int sum; //安全序列的个数

private slots:
    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void initialize();

    int checktable();

    bool SecureCheck();

    void SecureDFS(bool *security,int *temp,int k);

    void on_pushButton_4_clicked();

    void RescRequest();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    bool checkquest();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::MainWindow *ui;

    bool     m_pressed;
    QPoint   m_movePos;
};
#endif // MAINWINDOW_H
