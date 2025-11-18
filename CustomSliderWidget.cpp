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

#include "CustomSliderWidget.h"

CustomSliderWidget::CustomSliderWidget(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    this->setStyleSheet("color:white;");

    step_ = 1;

    decimals_ = 0;

    value_ = 0;

    tickInterval_ = 1;

    wantedTiksNumber_ = 0;

    setMaximum(100);
    setMinimum(0);
    
    setAllowedMaximum(100);
    setAllowedMinimum(0);
    
    topSliderTickle->init();
    medSliderTickle->init();
    bottomSliderTickle->init();
    
    topSlider->setVisible(false);
    bottomSlider->setVisible(false);
    
    resizeTimer_.setInterval(20);
    resizeTimer_.setSingleShot(true);
    
    topSliderTickle->setIsTickMouvable(false);
    bottomSliderTickle->setIsTickMouvable(false);
    
    topSliderTickle->setVisible(false);
    bottomSliderTickle->setVisible(false);
    
    connect(&resizeTimer_,&QTimer::timeout,this,&CustomSliderWidget::evaluateMaxsMinsValues);
    
    connect(topSliderTickle,&SliderTickleWidget::tickPressed,this,&CustomSliderWidget::topSliderPressed);
    connect(medSliderTickle,&SliderTickleWidget::tickPressed,this,&CustomSliderWidget::sliderPressed);
    connect(bottomSliderTickle,&SliderTickleWidget::tickPressed,this,&CustomSliderWidget::bottomSliderPressed);
    
    connect(topSliderTickle,&SliderTickleWidget::tickReleased,this,&CustomSliderWidget::topSliderReleased);
    connect(medSliderTickle,&SliderTickleWidget::tickReleased,this,&CustomSliderWidget::sliderReleased);
    connect(bottomSliderTickle,&SliderTickleWidget::tickReleased,this,&CustomSliderWidget::bottomSliderReleased);
    
    connect(medSliderTickle,&SliderTickleWidget::tickMoved,this,&CustomSliderWidget::sliderTickMoved);
    
}

CustomSliderWidget::~CustomSliderWidget()
{
    
}

float CustomSliderWidget::AllowedMaximum() const
{
    return AllowedMaximum_;
}

void CustomSliderWidget::setAllowedMaximum(float AllowedMaximum)
{
    AllowedMaximum_ = AllowedMaximum;

    adaptSlidersSizes();
}

float CustomSliderWidget::AllowedMinimum() const
{
    return AllowedMinimum_;
}

void CustomSliderWidget::setAllowedMinimum(float Allowedinimum)
{
    AllowedMinimum_ = Allowedinimum;

    adaptSlidersSizes();
}

float CustomSliderWidget::maximum() const
{
    return maximum_;
}

void CustomSliderWidget::setMaximum(float maximum)
{
    maximum_ = maximum;

    adaptSlidersSizes();
}

float CustomSliderWidget::minimum() const
{
    return minimum_;
}

void CustomSliderWidget::setMinimum(float minimum)
{
    minimum_ = minimum;

    adaptSlidersSizes();
}

float CustomSliderWidget::step() const
{
    return step_;
}

void CustomSliderWidget::setStep(float step)
{
    step_ = step;
    
    /** Prefer call evaluate tickles on timer output, I think this is better,
     * at least we know that the size of widget had finished changing */
    if(resizeTimer_.isActive())
        resizeTimer_.stop();
    resizeTimer_.start();
}

void CustomSliderWidget::setRange(float min, float max)
{
    setMinimum(min);
    setMaximum(max);
    
    setAllowedMinimum(min);
    setAllowedMaximum(max);
}

void CustomSliderWidget::setAllowedRange(float min, float max)
{
    setAllowedMinimum(min);
    setAllowedMaximum(max);
}

void CustomSliderWidget::adaptSlidersSizes()
{
    emit AllowedRangeChanged(AllowedMinimum_,AllowedMaximum_);
    emit rangeChanged(minimum_,maximum_);
    
    if(resizeTimer_.isActive())
        resizeTimer_.stop();
    resizeTimer_.start();
}

void CustomSliderWidget::sliderTickMoved(float position)
{
    /** calculate value */
    float value =  AllowedMaximum_ - ((position+tickHeight_/2) * 1/ratioVMinVMaxMedH_);

    //    float value = AllowedMaximum_  -
    //    ((position+medSliderTickle->height()/2) * (AllowedMaximum_ - AllowedMinimum_)/medSliderHeight_);

    emit valueChanged(value);
}

std::tuple<bool,float, float, float, float> CustomSliderWidget::getvalueInInterval(const float &val)
{
    
    if(val > maximum_ || val < minimum_ || ticksValPosMap_.empty())
        return std::make_tuple(false,-1,-1,-1,-1);
    
    bool found = false;
    float topTickVal = 0;
    float topTickPos = 0;
    float bottomTickVal = 0;
    float bottomTickPos = 0;
    std::map<float,float>::iterator it = ticksValPosMap_.find(val);
    if(it != ticksValPosMap_.end())
    {
        found = true;
        topTickVal = val;
        topTickPos = it->second;
    }
    else
    {
        std::map<float,float>::iterator upperIndex =  ticksValPosMap_.upper_bound(val);
        std::map<float,float>::iterator bottomIndex =  ticksValPosMap_.lower_bound(val);
        
        topTickVal = upperIndex->first;
        topTickPos = upperIndex->second;
        
        bottomTickVal = bottomIndex->first;
        bottomTickPos = bottomIndex->second;
    }
    
    return  std::make_tuple(found,topTickVal,topTickPos,bottomTickVal,bottomTickPos);
}

float CustomSliderWidget::calculateValueSliderPosition(std::tuple<bool, float, float, float, float> tuple, float& value)
{
    bool found = false;
    float topTickVal = 0;
    float topTickPos = 0;
    float bottomTickVal = 0;
    float bottomTickPos = 0;
    
    std::tie(found,topTickVal,topTickPos,bottomTickVal,bottomTickPos) =tuple;
    
    /** invalid */
    if(topTickVal == -1 &&
            topTickPos == -1 &&
            bottomTickPos == -1 &&
            bottomTickVal == -1)
        return -1;
    
    float result = 0;
    
    /** value found in map, we take only top */
    if(true == found)
    {
        result = topTickPos;
    }
    else
    {
        /** Finalement pas besoin du bottom mais je l'utilise pour améliorer la précision:)  */
        float calc1 = value * topTickPos / topTickVal;
        float calc2 = value * bottomTickPos / bottomTickVal;
        result = (calc1+calc2)/2;
    }
    return  result;
}

float CustomSliderWidget::tickInterval() const
{
    return tickInterval_;
}

void CustomSliderWidget::setTickInterval(float tickInterval)
{
    tickInterval_ = tickInterval;

    adaptSlidersSizes();
}


void CustomSliderWidget::setTickPosition(float value)
{
    //    /** get value interval */
    //    std::tuple<bool,float, float, float, float> tuple = getvalueInInterval(value);

    //    /** get global position in parent */
    //    float pos = calculateValueSliderPosition( tuple, value);

    if(value_ > AllowedMaximum_)
    {
        topSliderTickle->setVisible(true);
        bottomSliderTickle->setVisible(false);

        float newPos = topSliderHeight_ - ((value - AllowedMaximum_) * ratioMaxVMaxTopH_ + tickHeight_/2 -0.5);
        //        if(newPos < 0)
        //            newPos = 0;

        topSliderTickle->move(0, newPos);
    }
    else if( value_ < AllowedMinimum_)
    {
        bottomSliderTickle->setVisible(true);
        topSliderTickle->setVisible(false);

        float newPos = bottomSliderHeight_ - ((value - minimum_) * ratioVMinMinBottomH_ + tickHeight_/2 -0.5);
        //        if(newPos < 0)
        //            newPos = 0;

        bottomSliderTickle->move(0,newPos);
    }
    else
    {
        topSliderTickle->setVisible(false);
        bottomSliderTickle->setVisible(false);

        float newPos = medSliderHeight_ - ((value - AllowedMinimum_) * ratioVMinVMaxMedH_ + tickHeight_/2 -0.5);

        //        if(newPos < 0)
        //            newPos = 0;

        medSliderTickle->move(0, newPos);
    }
}

float CustomSliderWidget::getWantedTiksNumber() const
{
    return wantedTiksNumber_;
}

void CustomSliderWidget::setWantedTiksNumber(float val)
{
    wantedTiksNumber_ = val;
    adaptSlidersSizes();
}

int CustomSliderWidget::getDecimals() const
{
    return decimals_;
}

void CustomSliderWidget::setDecimals(int decimals)
{
    decimals_ = decimals;
    adaptSlidersSizes();
}

float CustomSliderWidget::value() const
{
    return value_;
}

void CustomSliderWidget::setValue(float value)
{
    value_ = value;

    setTickPosition(value);

    valueChanged(value_);

}


void CustomSliderWidget::resizeEvent(QResizeEvent *e)
{
    if(resizeTimer_.isActive())
        resizeTimer_.stop();
    resizeTimer_.start();
    QWidget::resizeEvent(e);
}

void CustomSliderWidget::mousePressEvent(QMouseEvent *e)
{
    if((e->y() < (topSliderHeight_ + medSliderHeight_)) &&
            (e->y() > topSliderHeight_))
        medSliderTickle->setPos(e->y()-topSliderHeight_);

    QWidget::mousePressEvent(e);
}

void CustomSliderWidget::wheelEvent(QWheelEvent *event)
{
    QPoint numPixels = event->pixelDelta();

    if(!numPixels.isNull() )
    {
        if (numPixels.y() > 0 )
        {
            if(value() + step() <= AllowedMaximum())
                setValue(value() + step());
        }
        else
        {
            if(value() - step() >= AllowedMinimum())
                setValue(value()- step());
        }
    }

    QWidget::wheelEvent(event);
}


void CustomSliderWidget::evaluateMaxsMinsValues()
{
    widgetHeight_ = height();

    if((maximum_ == minimum_) || widgetHeight_ == 0)
    {
        medSlider->setVisible(false);
        bottomSlider->setVisible(false);
        topSlider->setVisible(false);
        return;
    }
    else
    {
        medSlider->setVisible(true);
    }

    ratioMinMaxH_        = widgetHeight_ / (maximum_ - minimum_);

    medSliderHeight_      = (AllowedMaximum_ - AllowedMinimum_) * ratioMinMaxH_;
    if(medSliderHeight_ < 0)
    {
        qDebug()<<QString("CustomSlider:: resizing med slider error VMin=%1 VMax=%2 Min=%3 Max=%4 ParenH=%5")
                  .arg(AllowedMinimum_).arg(AllowedMaximum_)
                  .arg(minimum_).arg(maximum_).arg(widgetHeight_);

        return;
    }
    medSlider->setFixedHeight(medSliderHeight_);
    
    bottomSliderHeight_   = (AllowedMinimum_ - minimum_) * ratioMinMaxH_;
    bottomSlider->setMaximumHeight(bottomSliderHeight_);

    topSliderHeight_      = (maximum_ - AllowedMaximum_) * ratioMinMaxH_;
    topSlider->setMaximumHeight(topSliderHeight_);
    
    topSliderStartY_      = bottomSliderHeight_ + medSliderHeight_ ;
    medSliderStartY_      = bottomSliderHeight_ ;

    ratioVMinVMaxMedH_   = medSliderHeight_ / (AllowedMaximum_ - AllowedMinimum_);
    ratioVMinMinBottomH_ = bottomSliderHeight_ / (AllowedMinimum_ - minimum_);
    ratioMaxVMaxTopH_    = topSliderHeight_ / (maximum_ - AllowedMaximum_) ;

    tickHeight_          = medSliderTickle->height();

    nombreTickTotal      = (maximum_ - minimum_) / step_;
    tickStep_            = widgetHeight_ / nombreTickTotal  ;
    
    if(ticksValPosMap_.empty() == false)
    {
        ticksValPosMap_.clear();
    }

    evaluateTicklesValues();
    
    for (float i = 0;i <= nombreTickTotal;i = i + step_)
    {
        float tickleVal = step_*i;
        float ticklePos = tickStep_*i;
        
        ticksValPosMap_.insert(std::make_pair(tickleVal,ticklePos));
    }

    if(minimum_ == AllowedMinimum_)
    {
        bottomSlider->setVisible(false);
    }
    else
    {
        if(AllowedMinimum_ < minimum_)
        {
            qDebug()<<QString("CustomSlider:: requested Allowed min %1 error. min value is %2").arg(AllowedMinimum_).arg(minimum_);
            //           exit(-1);
            bottomSlider->setVisible(false);
        }
        else
        {
            bottomSlider->setVisible(true);
        }
    }
    if(maximum_ == AllowedMaximum_)
    {
        topSlider->setVisible(false);
    }
    else
    {
        if(AllowedMaximum_ > maximum_)
        {
            qDebug()<<QString("CustomSlider:: requested Allowed max %1 error. max value is %2").arg(AllowedMaximum_).arg(maximum_);
            
            /** Do I exit app ?? , I think that I'll activate it only when debugging */
            //            exit(-1);
            
            topSlider->setVisible(false);
        }
        else
        {
            topSlider->setVisible(true);
        }
    }

    setValue(value_);
}

void CustomSliderWidget::evaluateTicklesValues()
{
    if(labelsVector_.isEmpty() == false)
    {
        qDeleteAll(labelsVector_.begin(), labelsVector_.end());
//        foreach (QLabel* label, labelsVector_)
//        {
//            delete label;
//        }
        labelsVector_.clear();
    }

    int decimalsNum = decimals_;

    int index = 0;
    if(wantedTiksNumber_ == 0 )
    {
        for (float i = 0 ;i < nombreTickTotal ; i++)
        {
            float tickleVal = minimum_ + i*step_;
            float ticklePos = tickStep_*i + tickHeight_/2 ;
            //        qDebug()<<tickleVal<<"++++"<<i;

            if(index % tickInterval_  != 0 )
            {
                index++;
                continue;
            }
            else
                index = 0;
            QString text = "-  " + QString::number(tickleVal,'f',decimalsNum);
            QLabel* label = new QLabel(text,labelsFrame);
            label->setAlignment( Qt::AlignVCenter);
            QFont font = label->font();
            font.setPointSize(8);
            label->setFont(font);
            labelsVector_.push_back(label);

            label->setVisible(true);

            label->move(0,tickStep_*nombreTickTotal - ticklePos );
            label->raise();
            index++;
        }
    }
    else
    {
        float step = (maximum_-minimum_) / wantedTiksNumber_;

        float tickstep =  step * ratioMinMaxH_;

        for (float i = 0 ;i <= wantedTiksNumber_ ; i++)
        {
            float tickleVal = minimum_ + i*step;
            float ticklePos = tickstep*i + tickHeight_/2 ;
            //        qDebug()<<tickleVal<<"++++"<<i;

            QString text = "-  " + QString::number(tickleVal,'f',decimalsNum);
            QLabel* label = new QLabel(text,labelsFrame);
            label->setAlignment( Qt::AlignVCenter);
            QFont font = label->font();
            font.setPointSize(8);
            label->setFont(font);
            labelsVector_.push_back(label);

            label->setVisible(true);

            label->move(0,widgetHeight_ - ticklePos );
            label->raise();
            index++;
        }
    }
    if(labelsVector_.isEmpty())
        return;

    delete labelsVector_.first();
    labelsVector_.removeFirst();

    if(labelsVector_.isEmpty())
        return;
    QString lastLebelTextVal = labelsVector_.last()->text().remove("- ");

    if(qFuzzyCompare(lastLebelTextVal.toFloat(),maximum()))
    {
        delete labelsVector_.last();
        labelsVector_.removeLast();
    }

    //max Label
    /*  QString text = QString::number(maximum_,'f',decimalsNum);
    QLabel* maxlabel = new QLabel(text,labelsFrame);
    maxlabel->setAlignment( Qt::AlignVCenter);
    QFont maxlabelfont = maxlabel->font();
    maxlabelfont.setBold(true);
    maxlabelfont.setPointSize(8);
    maxlabel->setFont(maxlabelfont);
    labelsVector_.push_back(maxlabel);
    maxlabel->setVisible(true);

    maxlabel->move(10,0);
    maxlabel->raise();

    // min label
    text = QString::number(minimum_,'f',decimalsNum);
    QLabel* label = new QLabel(text,labelsFrame);
    label->setAlignment( Qt::AlignVCenter);
    QFont font = label->font();
    font.setBold(true);
    font.setPointSize(8);
    label->setFont(font);
    labelsVector_.push_back(label);
    //        label->setFixedSize(70,20);
    label->setVisible(true);

    label->move(10,height() - 15);
    label->raise();
    */

}
