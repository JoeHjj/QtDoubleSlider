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
#include <QTimer>
#include <QMap>
#include <QLabel>
#include <iostream>
#include <tuple>
#include "ui_CustomSliderWidget.h"


class CustomSliderWidget : public QWidget, public Ui::CustomSliderWidget
{
    Q_OBJECT

public:
    /**
     * @brief CustomSliderWidget Constructor  a vertical double slider
     * @param parent
     */
    explicit CustomSliderWidget(QWidget *parent = nullptr);
    /**
     * @brief ~CustomSliderWidget Destructor
     * @return
     */
    ~CustomSliderWidget();
    /**
     * @brief AllowedMaximum
     * @return
     */
    float AllowedMaximum() const;
    /**
     * @brief setAllowedMaximum set allowed maximum
     * @param AllowedMaximum
     */
    void setAllowedMaximum(float AllowedMaximum);
    /**
     * @brief AllowedMinimum
     * @return
     */
    float AllowedMinimum() const;
    /**
     * @brief setAllowedMinimum set allowed minimum
     * @param Allowedinimum
     */
    void setAllowedMinimum(float Allowedinimum);
    /**
     * @brief maximum
     * @return
     */
    float maximum() const;
    /**
     * @brief setMaximum set global maximum
     * @param maximum
     */
    void setMaximum(float maximum);
    /**
     * @brief minimum
     * @return
     */
    float minimum() const;
    /**
     * @brief setMinimum set global minimum
     * @param minimum
     */
    void setMinimum(float minimum);
    /**
     * @brief step
     * @return
     */
    float step() const;
    /** @breif the step between two values
     * @param step
     **/
    void setStep(float step);

    /** @breif the global range of slider
     * @param min
     * @param max
     **/
    void setRange(float min, float max);

    /** @breif it's the allowed range, within it the value is accepted
     * @param min
     * @param max
     **/
    void setAllowedRange(float min, float max);

    /**
     * @brief value
     * @return
     */
    float value() const;

    /** @breif set usable value
     * @param value
     **/
    void setValue(float value);

    /**
     * @brief tickInterval
     * @return
     */
    float tickInterval() const;

    /** @breif number of ticks shown.
     * be careful, when you create a very big slider, example
     * [0-100] with step 0.0001 and interval 1, this will freeze your PC
     * cause you have a for loop of 100000 that will create and move tick labels
     * on each resize event or range changed...
     * in this case choose a very big tick interval
     * @param tickInterval
     **/
    void setTickInterval(float tickInterval);

    /**
     * @brief getDecimals
     * @return
     */
    int getDecimals() const;

    /** @breif number of decimals to be shown
     * @param decimals
     **/
    void setDecimals(int decimals);
    /**
     * @brief getWantedTiksNumber
     * @return
     */
    float getWantedTiksNumber() const;
    /**
     * @brief setNombreTickVoulu, nombre de tick voulu pour etre afficher
     *  s'il est different que 0, j'ignore le tick interval
     * @param nombreTickVoulu
     */
    void setWantedTiksNumber(float val);

protected slots:

    /** @breif called whenever max, min, Allowed max or Allowed min values changed
     * In order to recalculate ranges and sizes/ visibility of sliders
     **/
    void evaluateMaxsMinsValues();

    /** @brief called on step value change
     * In order to recalculate tickles number and values
     **/
    void evaluateTicklesValues();

    /** @breif tick position to usable value, called on tick position changed
     * @param position
     **/
    void sliderTickMoved(float position);

    /** @brief to find the interval of a value requested in order to set the tickle position,
     * it return a tuple that have as values, bottom tick value, bootm tick position
     * top tick value, top tick position
     * if the value is found in the QMap of tickles, than the first bool will be false to indicate that it is not an interval
     * and will take only the first two values (top tick value, top tick position
     * @deprecated for performance issues
     **/
    std::tuple<bool, float, float, float, float> getvalueInInterval(const float& val);

    /** @brief to find tick position from a tuple interval
     * @deprecated for performance issues
     **/
    float calculateValueSliderPosition(std::tuple<bool, float, float, float, float> tuple, float &value);


protected:
    /**
     * @brief resizeEvent
     */
    void resizeEvent(QResizeEvent *) override;
    /**
     * @brief mousePressEvent
     */
    void mousePressEvent(QMouseEvent *) override;
    /**
     * @brief wheelEvent
     */
    void wheelEvent(QWheelEvent *) override;

    /** @breif request adapt sizes, this function will launch the resizing Timer
     **/
    void adaptSlidersSizes();

    /** @breif usable value to tick position
     * @param value
     **/
    void setTickPosition(float value);



signals:
    /**
     * @brief valueChanged signal
     * @param value
     */
    void valueChanged(float value);
    /**
     * @brief topSliderValueChanged signal
     * @param value
     */
    void topSliderValueChanged(float value);
    /**
     * @brief bottomSliderValueChanged signal
     * @param value
     */
    void bottomSliderValueChanged(float value);
    /**
     * @brief sliderPressed signal
     */
    void sliderPressed();//on tick pressed
    /**
     * @brief sliderReleased signal
     */
    void sliderReleased(); // on tick released
    /**
     * @brief topSliderPressed signal
     */
    void topSliderPressed();//on top tick pressed
    /**
     * @brief topSliderReleased signal
     */
    void topSliderReleased(); // on top tick released

    void bottomSliderPressed();//on bottom tick pressed
    /**
     * @brief bottomSliderReleased signal
     */
    void bottomSliderReleased(); // on bottom tick released
    /**
     * @brief rangeChanged signal
     * @param min
     * @param max
     */
    void rangeChanged(float min, float max);
    /**
     * @brief AllowedRangeChanged signal
     * @param AllowedMin
     * @param AllowedMax
     */
    void AllowedRangeChanged(float AllowedMin, float AllowedMax);

private:

    float step_;
    int decimals_;
    float value_;

    float widgetHeight_;
    float maximum_;
    float minimum_;

    float medSliderHeight_;
    float AllowedMaximum_;
    float AllowedMinimum_;

    /** @brief widgetHeight_/(maximum_-minimum_)
    **/
    float ratioMinMaxH_;

    /** @brief medSliderHeight_/(AllowedMaximum_-AllowedMinimum_)
    **/
    float ratioVMinVMaxMedH_;

    float bottomSliderHeight_;
    /** @brief bottomSliderHeight_/(AllowedMinimum_-minimum_)
    **/
    float ratioVMinMinBottomH_;

    float topSliderHeight_;
    /** @brief topSliderHeight_/(maximum_-AllowedMaximum_)
    **/
    float ratioMaxVMaxTopH_;

    /** @brief tick height
    **/
    float tickHeight_;

    QTimer resizeTimer_;

    int tickInterval_;

    /** @brief nombre de tick total compris entre max et min
    **/
    float nombreTickTotal;

    /** @brief nombre de tick voulu pour etre afficher
     *  s'il est different que 0, j'ignore le tick interval
    **/
    float wantedTiksNumber_;

    /** @brief bottom slider start at 0
    **/
    float medSliderStartY_;
    float topSliderStartY_;
    /**  @brief le step delta y, c'est la distance entre deux tick
    **/
    float tickStep_;

    /** @brief c'est une map qui a comme premier parametre la valeur d'un tick et en second sa position y
     * utilisée pour simplifier le positionnement des tick
    **/

    std::map<float,float> ticksValPosMap_;

    QVector <QLabel*> labelsVector_;
};

