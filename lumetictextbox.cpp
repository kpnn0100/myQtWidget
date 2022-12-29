#include "lumetictextbox.h"

LumeticTextBox::LumeticTextBox(QWidget *parent)
    : QWidget{parent}
{
    mainText = new QTextEdit(this);


}

void LumeticTextBox::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    paint.setBrush(Qt::black);
    paint.drawRoundedRect(0,0,this->size().width(),this->size().height(),((double)this->size().height())/2.0,((double)this->size().height())/2.0);
    paint.end();

}

