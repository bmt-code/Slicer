#include <QDebug>

#include "qCTKRangeSlider.h"

#include "qCTKDoubleRangeSlider.h"
#include <QHBoxLayout>


//-----------------------------------------------------------------------------
class qCTKDoubleRangeSliderPrivate: public qCTKPrivate<qCTKDoubleRangeSlider>
{
  public:
  qCTKDoubleRangeSliderPrivate();
  int toInt(double _value)const;
  double fromInt(int _value)const;
  void init();
  void updateOffset(double value);

  qCTKRangeSlider* Slider;
  double Minimum;
  double Maximum;
  double Offset;
  double SingleStep;
  double MinValue;
  double MaxValue;
};

// --------------------------------------------------------------------------
qCTKDoubleRangeSliderPrivate::qCTKDoubleRangeSliderPrivate() 
{
  this->Slider = 0;
  this->Minimum = 0.;
  this->Maximum = 99.;
  this->Offset = 0.;
  this->SingleStep = 1.;
  this->MinValue = 0.;
  this->MaxValue = 99.;
}
 
// --------------------------------------------------------------------------
void qCTKDoubleRangeSliderPrivate::init()
{
  QCTK_P(qCTKDoubleRangeSlider);
  this->Slider = new qCTKRangeSlider(p);
  QHBoxLayout* l = new QHBoxLayout(p);
  l->addWidget(this->Slider);
  l->setContentsMargins(0,0,0,0);
  
  this->Minimum = this->Slider->minimum();
  this->Maximum = this->Slider->maximum();
  this->MinValue = this->Slider->minimumValue();
  this->MaxValue = this->Slider->maximumValue();
  this->SingleStep = this->Slider->singleStep();

  p->connect(this->Slider, SIGNAL(minimumValueChanged(int)), p, SLOT(onMinValueChanged(int)));
  p->connect(this->Slider, SIGNAL(maximumValueChanged(int)), p, SLOT(onMaxValueChanged(int)));
  p->connect(this->Slider, SIGNAL(valuesChanged(int,int)), p, SLOT(onValuesChanged(int,int)));

  p->connect(this->Slider, SIGNAL(minimumPositionChanged(int)), p, SLOT(onMinPosChanged(int)));
  p->connect(this->Slider, SIGNAL(maximumPositionChanged(int)), p, SLOT(onMaxPosChanged(int)));
  p->connect(this->Slider, SIGNAL(positionsChanged(int,int)), p, SLOT(onPositionsChanged(int,int)));

  p->connect(this->Slider, SIGNAL(sliderPressed()), p, SIGNAL(sliderPressed()));
  p->connect(this->Slider, SIGNAL(sliderReleased()), p, SIGNAL(sliderReleased()));
}

// --------------------------------------------------------------------------
int qCTKDoubleRangeSliderPrivate::toInt(double doubleValue)const
{
  double tmp = doubleValue / this->SingleStep;
  int intValue = qRound(tmp);
  return intValue;
}

// --------------------------------------------------------------------------
double qCTKDoubleRangeSliderPrivate::fromInt(int intValue)const
{
  double doubleValue = this->SingleStep * (this->Offset + intValue) ;
  return doubleValue;
}

// --------------------------------------------------------------------------
void qCTKDoubleRangeSliderPrivate::updateOffset(double value)
{
  this->Offset = (value / this->SingleStep) - this->toInt(value);
}

// --------------------------------------------------------------------------
qCTKDoubleRangeSlider::qCTKDoubleRangeSlider(QWidget* _parent) : Superclass(_parent)
{
  QCTK_INIT_PRIVATE(qCTKDoubleRangeSlider);
  qctk_d()->init();
}

// --------------------------------------------------------------------------
qCTKDoubleRangeSlider::qCTKDoubleRangeSlider(Qt::Orientation _orientation, QWidget* _parent) 
  : Superclass(_parent)
{
  QCTK_INIT_PRIVATE(qCTKDoubleRangeSlider);
  qctk_d()->init();
  this->setOrientation(_orientation);
}

// --------------------------------------------------------------------------
void qCTKDoubleRangeSlider::setMinimum(double min)
{
  QCTK_D(qCTKDoubleRangeSlider);
  d->Minimum = min;
  if (d->Minimum >= d->MinValue)
    {// TBD: use same offset
    d->updateOffset(d->Minimum);
    }
  d->Slider->setMinimum(d->toInt(min));
}

// --------------------------------------------------------------------------
double qCTKDoubleRangeSlider::minimum()const
{
  QCTK_D(const qCTKDoubleRangeSlider);
  return d->Minimum;
}

// --------------------------------------------------------------------------
void qCTKDoubleRangeSlider::setMaximum(double max)
{
  QCTK_D(qCTKDoubleRangeSlider);
  d->Maximum = max;
  if (d->Maximum <= d->MaxValue)
    {// TBD: use same offset ?
    d->updateOffset(d->Maximum);
    }
  d->Slider->setMaximum(d->toInt(max));
}

// --------------------------------------------------------------------------
double qCTKDoubleRangeSlider::maximum()const
{
  QCTK_D(const qCTKDoubleRangeSlider);
  return d->Maximum;
}

// --------------------------------------------------------------------------
void qCTKDoubleRangeSlider::setRange(double min, double max)
{
  QCTK_D(qCTKDoubleRangeSlider);
  d->Minimum = min;
  d->Maximum = max;
  d->Slider->setRange(d->toInt(min), d->toInt(max));
}

// --------------------------------------------------------------------------
double qCTKDoubleRangeSlider::minimumPosition()const
{
  QCTK_D(const qCTKDoubleRangeSlider);
  return d->fromInt(d->Slider->minimumPosition());
}

// --------------------------------------------------------------------------
void qCTKDoubleRangeSlider::setMinimumPosition(double minPos)
{
  QCTK_D(qCTKDoubleRangeSlider);
  d->Slider->setMinimumPosition(d->toInt(minPos));
}

// --------------------------------------------------------------------------
double qCTKDoubleRangeSlider::maximumPosition()const
{
  QCTK_D(const qCTKDoubleRangeSlider);
  return d->fromInt(d->Slider->maximumPosition());
}

// --------------------------------------------------------------------------
void qCTKDoubleRangeSlider::setMaximumPosition(double maxPos)
{
  QCTK_D(qCTKDoubleRangeSlider);
  d->Slider->setMaximumPosition(d->toInt(maxPos));
}

// --------------------------------------------------------------------------
void qCTKDoubleRangeSlider::setPositions(double minPos, double maxPos)
{
  QCTK_D(qCTKDoubleRangeSlider);
  d->Slider->setPositions(d->toInt(minPos), d->toInt(maxPos));
}

// --------------------------------------------------------------------------
double qCTKDoubleRangeSlider::minimumValue()const
{
  QCTK_D(const qCTKDoubleRangeSlider);
  return d->MinValue;
}

// --------------------------------------------------------------------------
void qCTKDoubleRangeSlider::setMinimumValue(double newMinValue)
{
  QCTK_D(qCTKDoubleRangeSlider);
  d->updateOffset(newMinValue);
  int newIntValue = d->toInt(newMinValue);
  if (newIntValue != d->Slider->minimumValue())
    {
    // d->Slider will emit a minimumValueChanged signal that is connected to
    // qCTKDoubleSlider::onValueChanged
    d->Slider->setMinimumValue(newIntValue);
    }
  else
    {
    double oldValue = d->MinValue;
    d->MinValue = newMinValue;
    // don't emit a valuechanged signal if the new value is quite 
    // similar to the old value.
    if (qAbs(newMinValue - oldValue) > (d->SingleStep * 0.000000001))
      {
      emit this->minimumValueChanged(newMinValue);
      }
    }
}

// --------------------------------------------------------------------------
double qCTKDoubleRangeSlider::maximumValue()const
{
  QCTK_D(const qCTKDoubleRangeSlider);  
  return d->MaxValue;
}

// --------------------------------------------------------------------------
void qCTKDoubleRangeSlider::setMaximumValue(double newMaxValue)
{
  QCTK_D(qCTKDoubleRangeSlider);
  d->updateOffset(newMaxValue);
  int newIntValue = d->toInt(newMaxValue);
  if (newIntValue != d->Slider->maximumValue())
    {
    // d->Slider will emit a maximumValueChanged signal that is connected to
    // qCTKDoubleSlider::onValueChanged
    d->Slider->setMaximumValue(newIntValue);
    }
  else
    {
    double oldValue = d->MaxValue;
    d->MaxValue = newMaxValue;
    // don't emit a valuechanged signal if the new value is quite 
    // similar to the old value.
    if (qAbs(newMaxValue - oldValue) > (d->SingleStep * 0.000000001))
      {
      emit this->maximumValueChanged(newMaxValue);
      }
    }
}

// --------------------------------------------------------------------------
void qCTKDoubleRangeSlider::setValues(double newMinValue, double newMaxValue)
{
  this->setMinimumValue(newMinValue);
  this->setMaximumValue(newMaxValue);
}

// --------------------------------------------------------------------------
double qCTKDoubleRangeSlider::singleStep()const
{
  QCTK_D(const qCTKDoubleRangeSlider);
  return d->SingleStep;
}

// --------------------------------------------------------------------------
void qCTKDoubleRangeSlider::setSingleStep(double newStep)
{
  QCTK_D(qCTKDoubleRangeSlider);
  d->SingleStep = newStep;
  d->updateOffset(d->MinValue);
  // update the new values of the qCTKRangeSlider
  double _minvalue = d->MinValue;
  double _maxvalue = d->MaxValue;
  this->setMinimum(d->Minimum);
  this->setMaximum(d->Maximum);
  this->setMinimumValue(_minvalue);
  this->setMinimumPosition(_minvalue);
  this->setMaximumValue(_maxvalue);
  this->setMaximumPosition(_maxvalue);
}

// --------------------------------------------------------------------------
double qCTKDoubleRangeSlider::tickInterval()const
{
  QCTK_D(const qCTKDoubleRangeSlider);
  return d->fromInt(d->Slider->tickInterval());
}

// --------------------------------------------------------------------------
void qCTKDoubleRangeSlider::setTickInterval(double newTickInterval)
{
  QCTK_D(qCTKDoubleRangeSlider);
  d->Slider->setTickInterval(d->toInt(newTickInterval));
}

// --------------------------------------------------------------------------
bool qCTKDoubleRangeSlider::hasTracking()const
{
  QCTK_D(const qCTKDoubleRangeSlider);
  return d->Slider->hasTracking();
}

// --------------------------------------------------------------------------
void qCTKDoubleRangeSlider::setTracking(bool enable)
{
  QCTK_D(qCTKDoubleRangeSlider);
  d->Slider->setTracking(enable);
}

// --------------------------------------------------------------------------
void qCTKDoubleRangeSlider::triggerAction( QAbstractSlider::SliderAction action)
{
  QCTK_D(qCTKDoubleRangeSlider);
  d->Slider->triggerAction(action);
}

// --------------------------------------------------------------------------
void qCTKDoubleRangeSlider::setOrientation(Qt::Orientation newOrientation)
{
  QCTK_D(qCTKDoubleRangeSlider);
  d->Slider->setOrientation(newOrientation);
}

// --------------------------------------------------------------------------
Qt::Orientation qCTKDoubleRangeSlider::orientation()const
{
  QCTK_D(const qCTKDoubleRangeSlider);
  return d->Slider->orientation();
}

// --------------------------------------------------------------------------
void qCTKDoubleRangeSlider::onMinValueChanged(int newValue)
{
  QCTK_D(qCTKDoubleRangeSlider);
  double doubleNewValue = d->fromInt(newValue);
  if (d->MinValue == doubleNewValue)
    {
    return;
    }
  d->MinValue = doubleNewValue;
  emit this->minimumValueChanged(d->MinValue);
}

// --------------------------------------------------------------------------
void qCTKDoubleRangeSlider::onMaxValueChanged(int newValue)
{
  QCTK_D(qCTKDoubleRangeSlider);
  double doubleNewValue = d->fromInt(newValue);
  if (d->MaxValue == doubleNewValue)
    {
    return;
    }
  d->MaxValue = doubleNewValue;
  emit this->maximumValueChanged(d->MaxValue);
}

// --------------------------------------------------------------------------
void qCTKDoubleRangeSlider::onValuesChanged(int min, int max)
{
  QCTK_D(qCTKDoubleRangeSlider);
  emit this->valuesChanged(d->fromInt(min), d->fromInt(max));
}

// --------------------------------------------------------------------------
void qCTKDoubleRangeSlider::onMinPosChanged(int newPosition)
{
  QCTK_D(const qCTKDoubleRangeSlider);
  emit this->minimumPositionChanged(d->fromInt(newPosition));
}

// --------------------------------------------------------------------------
void qCTKDoubleRangeSlider::onMaxPosChanged(int newPosition)
{
  QCTK_D(const qCTKDoubleRangeSlider);
  emit this->maximumPositionChanged(d->fromInt(newPosition));
}
// --------------------------------------------------------------------------
void qCTKDoubleRangeSlider::onPositionsChanged(int min, int max)
{
  QCTK_D(const qCTKDoubleRangeSlider);
  emit this->positionsChanged(d->fromInt(min), d->fromInt(max));
}
