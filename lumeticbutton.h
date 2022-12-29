#ifndef LUMETICBUTTON_H
#define LUMETICBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QPalette>
#include <QColor>
#include <QDebug>
#include <math.h>
#include <QPropertyAnimation>
#include <QTimer>
#include <QPoint>
#include <QPointF>
#include <QMouseEvent>
#include <QVector>
#include <QString>
#include <QFont>
class animateProperty
{
public:
    double startTimer;
    double stopTimer;
    double circleSize;
    double circleOpacity;
    QPointF mousePosition;
    bool isOnStart;
    bool isOnEnd;
};

class LumeticButton : public QPushButton

{
    Q_OBJECT
public:
    explicit LumeticButton(QWidget *parent = nullptr);
    void setFPS(double newFPS);
    double getFPS();
    void setBackgroundColor(int r, int g, int b);
    void setTextColor(int r, int g, int b);
    void setHighlightColor(int r, int g, int b);
    void setTextHighlightColor(int r, int g, int b);
    QColor getBackgroundColor();
    QColor getTextColor();
    QColor getHighlightColor();
    QColor getTextHighlightColor();
    void setText(QString newText);
private:
    QColor backgroundColor,textColor,highlightColor,textHighlightColor;
    QString buttonText;
    void onTrigger();
    void outTrigger();
    void animate();
    QVector<animateProperty> animation;
    double fps=50;
    double easeInEaseOut(double t);

    QTimer *animationTimer = new QTimer(this);
    double duration=500.0;
signals:


    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);

    // QWidget interface
protected:
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // LUMETICBUTTON_H
