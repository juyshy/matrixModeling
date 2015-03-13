#include "DebugSlider.h"
#include <QtGui\qvboxlayout>
#include <QtGui\qslider>
#include <QtGui\qlabel>
#include <QtCore\qstring.h>

DebugSlider::DebugSlider(QString name, float min, float max, bool textOnLeft, float granularity)
{
	QLayout* layout;
	this->min = min;
	this->max = max;
	sliderGranularity = granularity;
	setLayout(layout = textOnLeft ? (QLayout*)new QHBoxLayout : new QVBoxLayout);
	layout->addWidget(nameLabel = new QLabel);
	layout->addWidget(label = new QLabel);
	label->setMinimumWidth(35);
	nameLabel->setText(name);
 
	layout->addWidget(slider = new QSlider);
	label->setAlignment(Qt::AlignCenter);
	slider->setOrientation(Qt::Horizontal);
	slider->setMinimum(0);
	slider->setMaximum(sliderGranularity);
	connect(slider, SIGNAL(valueChanged(int)), 
		this, SLOT(sliderValueChanged()));
	sliderValueChanged();
}

float DebugSlider::value() const
{
	return min + (max - min) * (slider->value() / sliderGranularity);
}

void DebugSlider::setValue(float newValue)
{
	float spot = (newValue - min) / (max - min);
	slider->setValue(spot * sliderGranularity);
}

void DebugSlider::sliderValueChanged()
{
	label->setText(QString::number(value()));
	emit valueChanged(value());
}
