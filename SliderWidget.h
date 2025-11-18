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

#include <QWidget>
#include "ui_SliderWidget.h"


class SliderWidget : public QWidget, public Ui::SliderWidget
{
    Q_OBJECT

public:
    /**
     * @brief SliderWidget
     * @param parent
     */
    explicit SliderWidget(QWidget *parent = nullptr);
    ~SliderWidget();
    /**
     * @brief setDecimals
     * @param val
     */
    void setDecimals(int val);
    /**
     * @brief setMinimum
     * @param val
     */
    void setMinimum(double val);
    /**
     * @brief setMaximum
     * @param val
     */
    void setMaximum(double val);
    /**
     * @brief setAllowedMinimum
     * @param val
     */
    void setAllowedMinimum(double val);
    /**
     * @brief setAllowedMaximum
     * @param val
     */
    void setAllowedMaximum(double val);
    /**
     * @brief setRange
     * @param min
     * @param max
     */
    void setRange(double min,double max);
    /**
     * @brief setAllowedRange
     * @param min
     * @param max
     */
    void setAllowedRange(double min,double max);
    /**
     * @brief setTickInterval
     * @param val
     */
    void setTickInterval(int val);
    /**
     * @brief setStep
     * @param val
     */
    void setStep(double val);
    /**
     * @brief setTitle
     * @param val
     */
    void setTitle(QString val);
    /**
     * @brief setValue
     * @param val
     */
    void setValue(double val);
    /**
     * @brief value
     * @return
     */
    double value();
    /**
     * @brief setUnit
     * @param val
     */
    void setUnit(QString val);

    /**
     * @brief setWantedTiksNumber
     * @param val
     */
    void setWantedTiksNumber(int val);

private slots:
    /**
     * @brief on_spinvalue_valueChanged
     * @param arg1
     */
    void on_spinvalue_valueChanged(double arg1);
    /**
    * @brief onDoubleSliderValChanged
    * @param val
    */
   void onDoubleSliderValChanged(double val);
private:
};

