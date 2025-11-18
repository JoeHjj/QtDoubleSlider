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

#include <QMainWindow>
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_spinBox_2_valueChanged(int arg1);

    void on_spinBox_3_valueChanged(int arg1);

    void on_spinBox_4_valueChanged(int arg1);

    void on_doubleSpinBox_2_valueChanged(double arg1);

    void on_spinBoxMin_valueChanged(int arg1);

    void on_spinBoxMax_valueChanged(int arg1);

    void on_spinBox_5_valueChanged(int arg1);

    void on_spinBox_6_valueChanged(int arg1);

    void on_doubleSpinBox_3_valueChanged(double arg1);

    void on_doubleSpinBox_4_valueChanged(double arg1);

    void on_doubleSpinBox_5_valueChanged(double arg1);

    void on_doubleSpinBox_6_valueChanged(double arg1);

private slots:

    void on_spinBox_10_valueChanged(int arg1);
    void on_doubleSpinBox_7_valueChanged(double arg1);
    void on_doubleSpinBox_9_valueChanged(double arg1);
    void on_doubleSpinBox_11_valueChanged(double arg1);
    void on_doubleSpinBox_10_valueChanged(double arg1);
    void on_doubleSpinBox_12_valueChanged(double arg1);
    void on_spinBox_valueChanged(int arg1);
    void on_spinBox_7_valueChanged(int arg1);
    void on_spinBox_8_valueChanged(int arg1);
};
