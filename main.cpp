#include "mainwindow.h"

#include <QApplication>
#include<QLabel>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    // 显示行列号 创建QLabel控件
    QString number[15]={"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15"};
    QString letters[15]={"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O"};


    QLabel *index1[15];
    //数字行号:
    for(int i=0;i<15;i++)
    {
        index1[i]=new QLabel(&w);
        index1[i]->setText(number[i]);
        index1[i]->setAlignment(Qt::AlignCenter);
        index1[i]->setGeometry(0,25+i*50,50,50); // 将QLabel添加到QWidget窗口中
    }

    QLabel *index2[15];
    //字母列号:
    for(int i=0;i<15;i++)
    {
        index2[i]=new QLabel(&w);
        index2[i]->setText(letters[i]);
        index2[i]->setAlignment(Qt::AlignCenter);
        index2[i]->setGeometry(25+i*50,0,50,50); // 将QLabel添加到QWidget窗口中
    }

//添加图片
//    QPixmap  img("D:/CodeField/Qt/FivePointsChess/J.png");
//    QLabel * image=new QLabel(&w);;
//    image->setPixmap(img);
//    image->setGeometry(750,50,500,700);
//    QLabel *word=new QLabel(&w);
//    word->setText("我滴夹王    无限猖狂");
//    word->setGeometry(850,0,200,50);

    w.show();
    return a.exec();
}
