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

#include "SliderWidget.h"

SliderWidget::SliderWidget(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    spinvalue->setDecimals(0);
    connect(widget_Slider,&CustomSliderWidget::valueChanged,this,&SliderWidget::onDoubleSliderValChanged);
    widget_Slider->setValue(0);
}

SliderWidget::~SliderWidget()
{

}

void SliderWidget::setDecimals(int val)
{
    widget_Slider->setDecimals(val);
    spinvalue->setDecimals(val);
}

void SliderWidget::setUnit(QString val)
{
    spinvalue->setSuffix(" "+val);
}

void SliderWidget::setMinimum(double val)
{
    widget_Slider->setMinimum(val);
    spinvalue->setMinimum(val);
    labelMin->setText(QString::number(val,'f',widget_Slider->getDecimals()));
}

void SliderWidget::setMaximum(double val)
{
    widget_Slider->setMaximum(val);
    spinvalue->setMaximum(val);
    labelMax->setText(QString::number(val,'f',widget_Slider->getDecimals()));
}

void SliderWidget::setAllowedMinimum(double val)
{
    widget_Slider->setAllowedMinimum(val);
    spinvalue->setMinimum(val);
}

void SliderWidget::setAllowedMaximum(double val)
{
    widget_Slider->setAllowedMaximum(val);
    spinvalue->setMaximum(val);

}

void SliderWidget::setRange(double min, double max)
{
    widget_Slider->setRange(min,max);
    spinvalue->setRange(min,max);
    labelMax->setText(QString::number(max,'f',widget_Slider->getDecimals()));
    labelMin->setText(QString::number(min,'f',widget_Slider->getDecimals()));
}

void SliderWidget::setAllowedRange(double min, double max)
{
    widget_Slider->setAllowedRange(min,max);
    spinvalue->setRange(min,max);
}

void SliderWidget::setTickInterval(int val)
{
  widget_Slider->setTickInterval(val);
}

void SliderWidget::setStep(double val)
{
  widget_Slider->setStep(val);
  spinvalue->setSingleStep(val);
}

void SliderWidget::setTitle(QString val)
{
    titleLineEdit->setText(val);
}

void SliderWidget::setValue(double val)
{
   spinvalue->setValue(val);
}

double SliderWidget::value()
{
    return  spinvalue->value();
}

void SliderWidget::setWantedTiksNumber(int val)
{
    widget_Slider->setWantedTiksNumber(val);
}

void SliderWidget::on_spinvalue_valueChanged(double arg1)
{
    widget_Slider->setValue(arg1);
}

void SliderWidget::onDoubleSliderValChanged(double val)
{
    spinvalue->blockSignals(true);
    spinvalue->setValue(val);
    spinvalue->blockSignals(false);
}
