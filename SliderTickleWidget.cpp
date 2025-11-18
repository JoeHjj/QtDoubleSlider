/*
    MIT License

    Copyright (c) 2025 Joseph Al Hajjar

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

#include "SliderTickleWidget.h"

SliderTickleWidget::SliderTickleWidget(QWidget *parent) : QFrame(parent)
{
    setMouseTracking(true);
    setIsTickMouvable(true);
    setStyleSheet("background-color:green");

}

void SliderTickleWidget::mousePressEvent(QMouseEvent *e)
{
    isMousePressed_ = true;
    startY_ = e->y();
    emit tickPressed();
}

void SliderTickleWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(false == isMousePressed_ ||
            isTickMouvable_ == false)
    {
        return;
    }

    float newY_ = pos().y()+ e->y() - startY_+ height()/2;

    QPoint p(0,newY_);

    if(newY_ >( -height()/2 -0.5) &&
            newY_ < (parentWidget()->height()-height()/2+0.5))
    {
        move(p);

        emit tickMoved(newY_);
    }
}

void SliderTickleWidget::mouseReleaseEvent(QMouseEvent *)
{
    isMousePressed_ = false;

    emit tickReleased();
}

bool SliderTickleWidget::isTickMouvable() const
{
    return isTickMouvable_;
}

void SliderTickleWidget::setIsTickMouvable(bool isTickMouvable)
{
    isTickMouvable_ = isTickMouvable;
}

void SliderTickleWidget::init()
{
    QPoint p(0,0);

    move(p);
}

void SliderTickleWidget::setPos(float val)
{
    val = val -height()/2+0.5;
    move(0,val);
    emit tickMoved(val);
}
