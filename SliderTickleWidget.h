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

#pragma once

#include <QFrame>
#include <QDebug>
#include <QMouseEvent>

class SliderTickleWidget : public QFrame
{
    Q_OBJECT
public:
    /**
     * @brief SliderTickleWidget
     * @param parent
     */
    explicit SliderTickleWidget(QWidget *parent = nullptr);
    /**
     * @brief init
     */
    void init();
    /**
     * @brief setPos set position in parent
     * @param val
     */
    void setPos(float val);
    /**
     * @brief isTickMouvable
     * @return
     */
    bool isTickMouvable() const;
    /**
     * @brief setIsTickMouvable
     * @param isTickMouvable
     */
    void setIsTickMouvable(bool isTickMouvable);

signals:
    /**
     * @brief tickPressed signal
     */
    void tickPressed();//on tick pressed
    /**
     * @brief tickMoved signal
     * @param y
     */
    void tickMoved(float y); // on tick moved
    /**
     * @brief tickReleased signal
     */
    void tickReleased(); // on tick released
protected:
    /**
     * @brief mousePressEvent
     */
    void mousePressEvent(QMouseEvent *) override;
    /**
     * @brief mouseMoveEvent
     */
    void mouseMoveEvent(QMouseEvent *) override;
    /**
     * @brief mouseReleaseEvent
     */
    void mouseReleaseEvent(QMouseEvent *) override;
signals:

private:

private:
    QRectF slidingRect_;
    bool isMousePressed_;
    double startY_;
    bool isTickMouvable_;

};

