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

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    this->setStyleSheet("QMainWindow{background-color: rgb(112,112,112);color:white;}");

    widgetIntSlider->setTitle("Zero decimals");
    widgetIntSlider->setStep(2);

    widgetIntSlider->setTickInterval(5);

    widgetIntSlider->setMaximum(100);
    widgetIntSlider->setMinimum(-100);

    widgetIntSlider->setAllowedMaximum(50);
    widgetIntSlider->setAllowedMinimum(-50);

    widgetDoubleSlider->setTitle("Two decimals");
    widgetDoubleSlider->setStep(0.01);
    widgetDoubleSlider->setDecimals(2);

    widgetDoubleSlider->setTickInterval(5);

    widgetDoubleSlider->setMaximum(1);
    widgetDoubleSlider->setMinimum(0);

    widgetDoubleSlider->setAllowedMaximum(0.5);
    widgetDoubleSlider->setAllowedMinimum(0.2);

    widgetfoudDecimalsDoubleSlider->setTitle("Four decimals");;
    widgetfoudDecimalsDoubleSlider->setDecimals(4);
    widgetfoudDecimalsDoubleSlider->setStep(0.0001);

    widgetfoudDecimalsDoubleSlider->setTickInterval(1);

    widgetfoudDecimalsDoubleSlider->setMaximum(0.001);
    widgetfoudDecimalsDoubleSlider->setMinimum(0);

    widgetfoudDecimalsDoubleSlider->setAllowedMaximum(0.0005);
    widgetfoudDecimalsDoubleSlider->setAllowedMinimum(0.0002);

}

MainWindow::~MainWindow()
{

}

void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    widgetIntSlider->setTickInterval(arg1);
}

void MainWindow::on_spinBox_3_valueChanged(int arg1)
{
    widgetIntSlider->setStep(arg1);
}

void MainWindow::on_spinBox_4_valueChanged(int arg1)
{
   widgetDoubleSlider->setTickInterval(arg1);
}

void MainWindow::on_doubleSpinBox_2_valueChanged(double arg1)
{
    widgetDoubleSlider->setStep(arg1);
}

void MainWindow::on_spinBoxMin_valueChanged(int arg1)
{
    widgetIntSlider->setMinimum(arg1);
}

void MainWindow::on_spinBoxMax_valueChanged(int arg1)
{
   widgetIntSlider->setMaximum(arg1);
}

void MainWindow::on_spinBox_5_valueChanged(int arg1)
{
     widgetIntSlider->setAllowedMinimum(arg1);
}

void MainWindow::on_spinBox_6_valueChanged(int arg1)
{
     widgetIntSlider->setAllowedMaximum(arg1);
}

void MainWindow::on_doubleSpinBox_3_valueChanged(double arg1)
{
    widgetDoubleSlider->setMinimum(arg1);
}

void MainWindow::on_doubleSpinBox_4_valueChanged(double arg1)
{
    widgetDoubleSlider->setMaximum(arg1);
}

void MainWindow::on_doubleSpinBox_5_valueChanged(double arg1)
{
   widgetDoubleSlider->setAllowedMinimum(arg1);
}

void MainWindow::on_doubleSpinBox_6_valueChanged(double arg1)
{
    widgetDoubleSlider->setAllowedMaximum(arg1);
}

void MainWindow::on_spinBox_10_valueChanged(int arg1)
{
    widgetfoudDecimalsDoubleSlider->setTickInterval(arg1);
}

void MainWindow::on_doubleSpinBox_7_valueChanged(double arg1)
{
    widgetfoudDecimalsDoubleSlider->setStep(arg1);
}

void MainWindow::on_doubleSpinBox_9_valueChanged(double arg1)
{
    widgetfoudDecimalsDoubleSlider->setMinimum(arg1);
}

void MainWindow::on_doubleSpinBox_11_valueChanged(double arg1)
{
    widgetfoudDecimalsDoubleSlider->setAllowedMinimum(arg1);
}

void MainWindow::on_doubleSpinBox_10_valueChanged(double arg1)
{
    widgetfoudDecimalsDoubleSlider->setMaximum(arg1);
}

void MainWindow::on_doubleSpinBox_12_valueChanged(double arg1)
{
    widgetfoudDecimalsDoubleSlider->setAllowedMaximum(arg1);
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    widgetIntSlider->setWantedTiksNumber(arg1);
}

void MainWindow::on_spinBox_7_valueChanged(int arg1)
{
    widgetDoubleSlider->setWantedTiksNumber(arg1);
}

void MainWindow::on_spinBox_8_valueChanged(int arg1)
{
    widgetfoudDecimalsDoubleSlider->setWantedTiksNumber(arg1);
}
