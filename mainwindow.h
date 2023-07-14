#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <Piece.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//定义棋盘的参数
const int Edge=1;//Edge倍的边长
const float Length=50;//网格边长 //一定要写成float 便于后续四舍五入
const int Scale=14;//14*14的规模
const int SizePiece=20;//15*15的规模

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void Board();//绘制棋盘
    void PieceOnBoard();//绘制棋盘上现有的棋子
    void PieceNow();//绘制当前所举棋子
    void Judge(QPoint pos);//判断游戏结束 和胜负赢家
    int CountEachDirection(QPoint pos,int dx,int dy);//8方向 各自计算相连的同色棋子个数
    void mousePressEvent(QMouseEvent *);//  重写虚函数
    void paintEvent(QPaintEvent *);//  重写虚函数
private:
    Ui::MainWindow *ui;
    QVector <Piece> vec;//存储所有下的棋子
    bool Cur_Round;//轮到黑子是true 白子false
};
#endif // MAINWINDOW_H
