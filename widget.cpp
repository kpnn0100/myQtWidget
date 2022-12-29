#include "widget.h"
#include "ui_widget.h"
#include "lumeticbutton.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    LumeticButton * a = new LumeticButton(this);
       a->move(20,20);
       a->setFixedSize(100,30);
       a->setBackgroundColor(44, 116, 179);
       a->setHighlightColor(255,255,255);
       a->setTextColor(255,255,255);
       a->setTextHighlightColor(0,0,0);
       a->setText("My button");
       //a->setAutoFillBackground(true)
       a->update();

      QPushButton * b = new QPushButton(this);
      b-> move(20,60);
      b->setFixedSize(100,30);
      b->setText("Your button");
      QPalette pal = b->palette();
            b->setAutoFillBackground(true);
      pal.setColor(QPalette::Button, QColor(Qt::blue));

      b->setPalette(pal);
      b->update();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{

}

void Widget::mouseDoubleClickEvent(QMouseEvent *event)
{
    qDebug()<<"Mouse dbclick at (" <<event->pos();
}

