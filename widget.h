#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include  <QDebug>
#include <QMouseEvent>
#include <QPushButton>
#include <QPalette>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:

    Ui::Widget *ui;


    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
};
#endif // WIDGET_H
