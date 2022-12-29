#ifndef LUMETICTEXTBOX_H
#define LUMETICTEXTBOX_H

#include <QWidget>
#include <QTextEdit>
#include <QPainter>
#include <QPen>
#include <QPalette>
#include <QDebug>
class LumeticTextBox : public QWidget
{
    Q_OBJECT
public:
    explicit LumeticTextBox(QWidget *parent = nullptr);

signals:


    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    QTextEdit * mainText;
    bool isStarting=false;
    bool isEnding=false;

    // QWidget interface
protected:


};

#endif // LUMETICTEXTBOX_H
