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
private:
    double duration=3000.0;
    double fps=50.0;

    QColor backgroundColor,textColor,highlightColor,textHighlightColor;
    QString buttonText;
    QVector<animateProperty> animation;
    QTimer *animationTimer = nullptr;

    double easeInEaseOut(double t);
    void onTrigger();
    void outTrigger();
    void animate();
public:
    explicit LumeticButton(QWidget *parent = nullptr);
    //get set method
    void setFPS(double newFPS);
    double getFPS();
    void setBackgroundColor(int r, int g, int b);
    QColor getBackgroundColor();
    void setTextColor(int r, int g, int b);
    QColor getTextColor();
    void setHighlightColor(int r, int g, int b);
    QColor getHighlightColor();
    void setTextHighlightColor(int r, int g, int b);
    QColor getTextHighlightColor();
    void setText(QString newText);

signals:


    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // LUMETICBUTTON_H
