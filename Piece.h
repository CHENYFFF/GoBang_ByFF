#ifndef PIECE_H
#define PIECE_H

#pragma once
#include <QPoint>

//棋子类
class Piece
{
public:
    Piece(void);
    Piece(QPoint pt,bool isblk); //参数构造 便于后面新构建棋子
    ~Piece(void);

//    //重载操作符==，颜色和位置都相同
//    bool operator==(const Piece & another)const
//    {
//        return ((this->position == another.position) && (this->isblack == another.isblack));
//    }

    QPoint position;//棋子的落点位置
    bool isblack;//棋子是（否）为黑色
};



#endif // PIECE_H
