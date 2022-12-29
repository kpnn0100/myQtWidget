#include "lumeticbutton.h"

LumeticButton::LumeticButton(QWidget *parent)
    : QPushButton{parent}
{
    this->setStyleSheet(QString("QPushButton {border: 0px;}"));
    this->setFlat(true);
    connect(this,&LumeticButton::pressed,this,&LumeticButton::onTrigger);
    connect(this,&LumeticButton::released,this,&LumeticButton::outTrigger);
    connect(animationTimer, &QTimer::timeout, this, &LumeticButton::animate);
    backgroundColor = QColor(Qt::white);
    textColor = QColor (Qt::black);
    highlightColor = QColor(Qt::black);
    textHighlightColor = QColor(Qt::white);
}

void LumeticButton::setFPS(double newFPS)
{
    fps=newFPS;
}

double LumeticButton::getFPS()
{
    return fps;
}

void LumeticButton::setBackgroundColor(int r, int g, int b)
{
    backgroundColor = QColor::fromRgb(r,g,b);
}

void LumeticButton::setTextColor(int r, int g, int b)
{
    textColor = QColor::fromRgb(r,g,b);
}

void LumeticButton::setHighlightColor(int r, int g, int b)
{
    highlightColor = QColor::fromRgb(r,g,b);
}

void LumeticButton::setTextHighlightColor(int r, int g, int b)
{
    textHighlightColor = QColor::fromRgb(r,g,b);
}

QColor LumeticButton::getBackgroundColor()
{
    return backgroundColor;
}

QColor LumeticButton::getTextColor()
{
    return textColor;

}

QColor LumeticButton::getTextHighlightColor()
{
    return textHighlightColor;
}

void LumeticButton::setText(QString newText)
{
    buttonText= newText;
}

QColor LumeticButton::getHighlightColor()
{
    return highlightColor;
}
void LumeticButton::animate()
{
    bool isAllEnd=true;
    for (auto &a : animation)
    {
        if (a.isOnStart || a.isOnEnd)
        {
            isAllEnd= false;
        }
    }
    if (isAllEnd==true)
    {
        animationTimer->stop();
    }
    for (int i =0;i<animation.size();++i)
    {
        if (animation[i].isOnStart)
        {

            if (animation[i].startTimer<duration)
            {
                animation[i].startTimer+=(1000.0/fps);
                animation[i].circleSize=easeInEaseOut(animation[i].startTimer/duration)*((this->height()>this->width()?this->height():this->width()));
            }
            else
                if (animation[i].isOnEnd)
                    animation[i].isOnStart=false;

        }
        if (animation[i].isOnEnd)
        {
            animation[i].stopTimer+=(1000.0/fps);
            animation[i].circleOpacity = 1-easeInEaseOut(animation[i].stopTimer/duration);
            if (animation[i].stopTimer>duration)
            {
                animation[i].isOnEnd=false;
            }
        }
        if (!animation[i].isOnEnd && !animation[i].isOnStart)
        {
            animation.erase(animation.begin()+i);
            i--;
        }
    }


    this->repaint();
}
void LumeticButton::mousePressEvent(QMouseEvent *event)
{
    animation.push_back(animateProperty());
    animation.last().mousePosition = event->localPos();
    animation.last().isOnStart=true;
    qDebug()<<"pressed";
    animation.last().startTimer=0;
    animationTimer->setSingleShot(false);
    animationTimer->setInterval(1000.0/fps);
    animationTimer->start(1000.0/fps);
    animation.last().circleOpacity=1;
}

void LumeticButton::mouseReleaseEvent(QMouseEvent *event)
{
    animation.last().isOnEnd=true;
    qDebug()<<"released";
    animation.last().stopTimer=0;
    animationTimer->setSingleShot(false);
    animationTimer->setInterval(1000.0/fps);
    animationTimer->start(1000.0/fps);
}

void LumeticButton::onTrigger()
{



}

void LumeticButton::outTrigger()
{

}



double LumeticButton::easeInEaseOut(double t)
{
    double unit = t;
    if (unit<0.5)
        return 8.0*pow(unit,4);
    else
        return (1.0-8.0*pow(unit-1.0,4));

}

void LumeticButton::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    QPalette color(this->palette());
    paint.setPen(QColor::fromRgb(0,0,0,0));
    paint.setBrush(backgroundColor);
    paint.drawRect(0,0,this->width(),this->height());


    for (auto &a:animation)
    {
        QPainter circle(this);
        circle.setRenderHint(QPainter::Antialiasing);
        circle.setPen(QColor::fromRgb(0,0,0,0));
        QColor ofCircle = highlightColor;
        ofCircle.setAlpha(a.circleOpacity*255);
        circle.setBrush(ofCircle);
        circle.drawEllipse(a.mousePosition,a.circleSize,a.circleSize);
    }
    QPainter textDraw(this);

    QTextOption textRule;
    textRule.setAlignment(Qt::AlignHCenter);
    QFont buttonFont =QFont("Arial", 12);
    buttonFont.setBold(true);
    textDraw.setFont(buttonFont);
    double ratio=0;
    for (int i=animation.size()-1;i>=0;--i)
    {
        if (animation[i].isOnEnd==true)
        {
            if (ratio<1-animation[i].stopTimer/duration)
                ratio =1- animation[i].stopTimer/duration;
        }
    }
    for (int i=0;i<animation.size();++i)
    {
        if (animation[i].isOnStart==true)
        {
            if (ratio<animation[i].startTimer/duration)
                ratio = animation[i].startTimer/duration;
        }
    }
    double iRatio = 1-ratio;
    int red= textColor.red()*iRatio + textHighlightColor.red()*ratio;
    int green= textColor.green()*iRatio + textHighlightColor.green()*ratio;
    int blue= textColor.blue()*iRatio + textHighlightColor.blue()*ratio;
    QColor currentTextColor = QColor::fromRgb(red,green,blue);
    textDraw.setPen(currentTextColor);
    textDraw.drawText(QRectF(this->rect()),Qt::AlignCenter, buttonText );
}

