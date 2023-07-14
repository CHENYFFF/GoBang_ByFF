#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"
#include "qevent.h"
#include "qpoint.h"
#include "qmessagebox.h"
#include <QDebug>
#include <QtMath>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("自娱自乐五子棋"));//设置软件标题

    resize((Scale + 2)*Length ,(Scale + 2)*Length);

    Cur_Round = true;//初始化为黑子先行
}

MainWindow::~MainWindow()
{
    delete ui;
}

//更新绘制界面
void MainWindow::paintEvent(QPaintEvent *e){
    Board();
    PieceOnBoard();
    PieceNow();

    update();
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    qDebug()<<"mousePressEvent"<<endl;
    //获取点击处坐标和映射到棋盘上的行列索引
    int xIndex=qRound(e->pos().x()/Length);
    int yIndex=qRound(e->pos().y()/Length);

    qDebug()<<"x"<<xIndex<<endl;
    qDebug()<<"y"<<yIndex<<endl;
    QPoint point(xIndex,yIndex);

    //判断此处是否已经存在棋子
    for(int i=0;i<vec.size();i++){
        QPoint pos=vec[i].position;
        if(pos==point){
            return;//已存在 退出函数
        }
    }
    //没有退出函数体 说明点击处无棋子 创建棋子并push进vec

    Piece newpiece(point,Cur_Round);//新建棋子颜色与当前举棋方一致
    vec.push_back(newpiece);

    //判断是否结束战局
    Judge(point);
}


//绘制棋盘
void MainWindow::Board() {
//    qDebug()<<"Board()"<<endl;
    QPainter painter(this);

    painter.setRenderHint(QPainter::HighQualityAntialiasing, true); //这一行是干嘛的???
    painter.setBrush(Qt::gray);
    painter.setPen(Qt::black);

    //嵌套循环绘制网格矩形
    for(int i=0;i<Scale;i++){
        for(int j=0;j<Scale;j++){
            painter.drawRect((i+Edge)*Length,(j+Edge)*Length,Length,Length);
        }
    }
     painter.setBrush(Qt::black);
    //绘制天元和小星
    painter.drawEllipse((Edge+7)*Length-2,(Edge+7)*Length-2,5,5);
    painter.drawEllipse((Edge+3)*Length-2,(Edge+3)*Length-2,5,5);
    painter.drawEllipse((Edge+12)*Length-2,(Edge+11)*Length-2,5,5);
    painter.drawEllipse((Edge+3)*Length-2,(Edge+11)*Length-2,5,5);
    painter.drawEllipse((Edge+12)*Length-2,(Edge+3)*Length-2,5,5);
}

//绘制棋盘上现有的棋子
void MainWindow:: PieceOnBoard(){
//    qDebug()<<"PieceOnBoard()"<<endl;
    QPainter painter(this);
    painter.setPen(Qt::black);

    //绘制所有棋子
    for(int i=0;i<vec.size();i++){
         Piece piece=vec[i];
        //true代表黑子
        if(piece.isblack==true){
            painter.setBrush(Qt::black);
        }
       else{
             painter.setBrush(Qt::white);
        }
        QPoint p=piece.position;
        painter.drawEllipse(p*Length,SizePiece,SizePiece);
    }
}

//绘制当前所举棋子
void MainWindow::PieceNow(){
//    qDebug()<<"PieceNow()"<<endl;
    QPainter painter(this);

    //true代表当前轮到黑方
    if(Cur_Round==true){
        painter.setBrush(Qt::black);
    }
   else{
         painter.setBrush(Qt::white);
    }
    painter.setPen(Qt::black);


    QPoint globle_pos = QCursor::pos();

    QPoint windowPoint = this->mapFromGlobal(globle_pos);
    painter.drawEllipse(windowPoint,SizePiece,SizePiece);
}

//判断游戏结束 和胜负赢家
void MainWindow::Judge(QPoint pos){
     qDebug()<<"Judge"<<endl;
    //定义8个方向 顺时针从正右方向开始
    int count1=CountEachDirection(pos,1,0);
    int count2=CountEachDirection(pos,1,1);
    int count3=CountEachDirection(pos,0,1);
    int count4=CountEachDirection(pos,-1,1);
    int count5=CountEachDirection(pos,-1,0);
    int count6=CountEachDirection(pos,-1,-1);
    int count7=CountEachDirection(pos,0,-1);
    int count8=CountEachDirection(pos,1,-1);

    qDebug()<<count1<<count5<<count1+count5<<endl;
    qDebug()<<count2<<count6<<count2+count6<<endl;
    qDebug()<<count3<<count7<<count3+count7<<endl;
    qDebug()<<count4<<count8<<count4+count8<<endl;
    //两两配对 检查是否五子连线
    if(count1+count5>3||count2+count6>3||count3+count7>3||count4+count8>3){
        //信息对话框
        if(Cur_Round){
             QMessageBox::information(NULL,"OVER","黑方获胜", QMessageBox::Ok);
        }
        else{
             QMessageBox::information(NULL,"OVER","白方获胜", QMessageBox::Ok);
        }
        //战局结束之后  新开一局
        vec.clear();//清空所有棋子

        return;
    }

    //若没有结束
    Cur_Round=!Cur_Round;//交换棋权
}

int MainWindow::CountEachDirection(QPoint pos,int dx,int dy){
    QPoint nextPoint;
    nextPoint.setX(pos.x()+dx);
    nextPoint.setY(pos.y()+dy);

    int num=0;//此方向上的同色相邻棋子数
    bool nextExist;//此方向上的下一个点是否存在
    do{
        nextExist=false;
        for(int i=0;i<vec.size();i++)
        {
            if(vec[i].isblack==Cur_Round&&vec[i].position==nextPoint){
                num++;
                nextExist=true;
                break;//存在就可以跳出循环了
            }
        }
        nextPoint.setX(nextPoint.x()+dx);
        nextPoint.setY(nextPoint.y()+dy);
    }while(nextExist);
    return num;
}















