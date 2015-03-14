#include "MyWidget.h"
#include <QtGui\qapplication.h>
#include <QtCore\qrect.h>
#include <QtGui\qdesktopwidget.h>
#include <QtCore\qdebug.h>
#include <QtGui\qmenubar.h>
#include <QtCore\qelapsedtimer.h>
#include <QtGui\qvboxlayout>
#include <QtGui\qvboxlayout>
#include <QtGui\QPushButton>
#include <QtGui\QDialog>
#include <QtGui\qkeyevent>
#include <QtGui\qlabel.h>
#include <QtGui\QColorDialog>
#include <MyGLWindow.h>
#include <DebugSlider.h>
#include <QtCore\qtimer.h>
#include <QtCore\qdatetime.h>
#include <string>
#include <Utility.h>
#include <boost\algorithm\string\replace.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "boost/date_time/gregorian/gregorian.hpp"
#include <iostream>
#include <string>

using namespace boost::posix_time;
using namespace boost::gregorian;
using namespace boost;
 
MyWidget::MyWidget()
{
	// gather fps info to debugfile:
	savefpsTracing = false;

	myGlWindow = new MyGLWindow(&theModel);

	// fullscreen:
	QRect r = QApplication::desktop()->availableGeometry();
	//r.setLeft(r.center().x());
	resize(r.width(), r.height());
	move(r.topLeft());
	
	// labels:
	label = new QLabel(tr("FPS:"));
	sblabel = new QLabel(tr("triangles: "));
	numExtrLabel  = new QLabel(tr("Num of Extrudes: "));
	colorLabel = new QLabel( );
	colorLabel->setText("Color : " + QString::number(theModel.color.r) + ", " + QString::number(theModel.color.g) + ", " + QString::number(theModel.color.b));
	color.setRgbF((qreal)theModel.color.r, (qreal)theModel.color.g, (qreal)theModel.color.b);
	colorLabel->setPalette(QPalette(color));
	colorLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);


	cameraPositionLabel = new QLabel(tr("Camera: "));
	cameraposInfo = "Camera: " +
		QString::number(myGlWindow->camera.position.x) + ", " +
		QString::number(myGlWindow->camera.position.y) + ", " +
		QString::number(myGlWindow->camera.position.z); 
	cameraPositionLabel->setText(cameraposInfo);

	spinBox = new QSpinBox;
	spinBox->setRange(3, 130);
	spinBox->setMaximumWidth(100);
	spinBox->setValue(theModel.triangleCount);
	numExtrSpinBox = new QSpinBox;
	numExtrSpinBox->setRange(0, 130);
	numExtrSpinBox->setValue(theModel.extrudes);

	// layout
	centralWidget = new QWidget;
	setCentralWidget(centralWidget);

	QVBoxLayout* mainLayout;
	//setLayout(mainLayout = new QVBoxLayout);
	centralWidget->setLayout(mainLayout = new QVBoxLayout);
	
	QHBoxLayout* labelLayout;
	mainLayout->addLayout(labelLayout = new QHBoxLayout);
	labelLayout->addWidget(label);
	labelLayout->addStretch();
	labelLayout->addWidget(cameraPositionLabel);
	labelLayout->addWidget(colorLabel);
		
	labelLayout->addWidget(numExtrLabel);
	labelLayout->addWidget(numExtrSpinBox);
	labelLayout->addWidget(sblabel);
	labelLayout->addWidget(spinBox);
	controlsLayout = new QVBoxLayout;
	//mainLayout->addLayout(controlsLayout  );
	
	mainLayout->addWidget(myGlWindow);


	QHBoxLayout* extrScaleLayout;
	controlsLayout->addLayout(extrScaleLayout = new QHBoxLayout);

	extrudeRotationAngleStartSlider = new DebugSlider("Extr.RotaAngle Start", 0,10 );
	extrScaleLayout->addWidget(extrudeRotationAngleStartSlider);

	scaleUndlAmountX = new DebugSlider("Extr Scale Undul. X", theModel.scaleUndlAmountXSliderRange.x, theModel.scaleUndlAmountXSliderRange.y);
	extrScaleLayout->addWidget(scaleUndlAmountX);
	scaleUndlAmountZ = new DebugSlider("Extr Scale Undul. Z", theModel.scaleUndlAmountZSliderRange.x, theModel.scaleUndlAmountZSliderRange.y);
	extrScaleLayout->addWidget(scaleUndlAmountZ);
	scaleUndlRateX = new DebugSlider("Extr scale Undl RateX", theModel.scaleUndlRateXSliderRange.x, theModel.scaleUndlRateXSliderRange.y);
	extrScaleLayout->addWidget(scaleUndlRateX);
	scaleUndlRateZ = new DebugSlider("Extr scale Undl RateZ", theModel.scaleUndlRateZSliderRange.x, theModel.scaleUndlRateZSliderRange.y);
	extrScaleLayout->addWidget(scaleUndlRateZ);


	QHBoxLayout* extrTransLayout;
	controlsLayout->addLayout(extrTransLayout = new QHBoxLayout);
	extrTransLayout->addWidget(extrTransXSlider = new DebugSlider("Extr Trans X", 0.0, 1));
	extrTransLayout->addWidget(extrTransYSlider = new DebugSlider("Extr Trans Y", 0.0, 1));
	extrTransLayout->addWidget(extrTransZSlider = new DebugSlider("Extr Trans Z", 0.0, 1));
	
 
	QHBoxLayout* translateSlidersLayout;
	translateSlidersLayout = new QHBoxLayout;
	//controlsLayout->addLayout(translateSlidersLayout = new QHBoxLayout);
	translateSlidersLayout->addWidget(translateXSlider = new DebugSlider("Rota speed"));
	translateSlidersLayout->addWidget(translateYSlider = new DebugSlider("Y"));
	translateSlidersLayout->addWidget(translateZSlider = new DebugSlider("Z"));



	// initial values
	translateXSlider->setValue(-1.5f);
	translateYSlider->setValue(0);
	translateZSlider->setValue(0);
	saved = false;
	connect(scaleUndlAmountX, SIGNAL(valueChanged(float)), this, SLOT(exsliderValueChanged()));
	connect(scaleUndlAmountZ, SIGNAL(valueChanged(float)), this, SLOT(exsliderValueChanged()));
	connect(scaleUndlRateX, SIGNAL(valueChanged(float)), this, SLOT(exsliderValueChanged()));
	connect(scaleUndlRateZ, SIGNAL(valueChanged(float)), this, SLOT(exsliderValueChanged()));

	connect(extrTransXSlider, SIGNAL(valueChanged(float)), this, SLOT(exsTrliderValueChanged()));
	connect(extrTransYSlider, SIGNAL(valueChanged(float)), this, SLOT(exsTrliderValueChanged()));
	connect(extrTransZSlider, SIGNAL(valueChanged(float)), this, SLOT(exsTrliderValueChanged()));

	scaleUndlAmountX->setValue(theModel.undulatingAmountX);
	scaleUndlAmountZ->setValue(theModel.undulatingAmountZ);
	scaleUndlRateX->setValue(theModel.undulatingRateX);
	scaleUndlRateZ->setValue(theModel.undulatingRateZ);

	extrTransXSlider->setValue(0);
	extrTransYSlider->setValue(theModel.extrudetranslate1.y);
	extrTransZSlider->setValue(0);

	connect(translateXSlider, SIGNAL(valueChanged(float)), this, SLOT(sliderValueChanged()));
	connect(translateYSlider, SIGNAL(valueChanged(float)), this, SLOT(sliderValueChanged()));
	connect(translateZSlider, SIGNAL(valueChanged(float)), this, SLOT(sliderValueChanged()));
	connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(spinBValueChanged(int)));
	connect(numExtrSpinBox, SIGNAL(valueChanged(int)), this, SLOT(numExtrspinBValueChanged(int)));
	theModel.sliderPosition.x = translateXSlider->value();
	theModel.sliderPosition.y = translateYSlider->value();
	theModel.sliderPosition.z = translateZSlider->value();


	parametersDialog = new QDialog(this);
	//parametersDialog.setParent(this);
	parametersDialog->setModal(true);
	parametersDialog->setWindowTitle(tr("Extrusion parameters"));
	parametersDialog->setLayout(controlsLayout);

	translateDialog = new QDialog(this);
	translateDialog->setWindowTitle(tr("Translate object"));
	translateDialog->setLayout(translateSlidersLayout);

	createActions();
	createMenus();

	QTimer *timer = new QTimer(this);
	etimer.start();
	//connect(timer, SIGNAL(timeout()), native, SLOT(animate()));
	connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
	timer->start(1);
	elapsed=0;
	spinBox->clearFocus();
	myGlWindow->repaint();
	myGlWindow->setFocus();
}
void MyWidget::exsTrliderValueChanged()
{
	if (myGlWindow->pModel->ready2render) {
		myGlWindow->pModel->extrudetranslate1.x = extrTransXSlider->value();
		myGlWindow->pModel->extrudetranslate1.y = extrTransYSlider->value();
		myGlWindow->pModel->extrudetranslate1.z = extrTransZSlider->value();
		myGlWindow->pModel->rebuid();
	}
}
void MyWidget::exsliderValueChanged()
{
	if (myGlWindow->pModel->ready2render) {
	myGlWindow->pModel->undulatingAmountX = scaleUndlAmountX->value();
	myGlWindow->pModel->undulatingAmountZ = scaleUndlAmountZ->value();
	myGlWindow->pModel->undulatingRateX = scaleUndlRateX->value();
	myGlWindow->pModel->undulatingRateZ = scaleUndlRateZ->value();
	myGlWindow->pModel->rebuid();
	}
	std::cout << scaleUndlAmountX->value() << std::endl;
}

void MyWidget::numExtrspinBValueChanged(int newValue)
{
	myGlWindow->pModel->extrudes = newValue;
	myGlWindow->pModel->rebuid();
	myGlWindow->setFocus();
	std::cout << numExtrSpinBox->value() << std::endl;
}

void MyWidget::spinBValueChanged(int newValue)
{
	myGlWindow->pModel->setTriagleCount(newValue);
	myGlWindow->pModel->rebuid();
	myGlWindow->setFocus();
	std::cout << spinBox->value()   << std::endl;
}

void MyWidget::animate(){
	elapsed = etimer.elapsed(); //(elapsed + qobject_cast<QTimer*>(sender())->interval()) % 100000;
	double fps = 1000.0 / (elapsed - previousTime);
	QString fpsstr = "FPS:" + QString::number(fps); 
	label->setText(fpsstr);
	cameraposInfo = "Camera: " + 
		QString::number(myGlWindow->camera.position.x, 'f', 2) + ", " + 
		QString::number(myGlWindow->camera.position.y, 'f', 2) + ", " +
		QString::number(myGlWindow->camera.position.z, 'f', 2);
	cameraPositionLabel->setText(cameraposInfo);
 
	if (savefpsTracing){
		if (elapsed <60000) { // get data for 60 secs
			debugstr << elapsed << ":" << fps << "\n";
		}
		else if (!saved )
		{
			saveTrace(); 
		}
	}

	previousTime = elapsed;
	myGlWindow->update(elapsed);
	myGlWindow->repaint();
}

void MyWidget::saveTrace(){
	saved = true;
	date today = day_clock::local_day();
	ptime now = second_clock::local_time();
	std::string nowstr = to_simple_string(now);
	erase_all(nowstr, ":");
	std::string filename = "tracing/fpstrace" + nowstr + ".txt";
	Utility::SaveToFile(filename, debugstr.str());
}

MyWidget::~MyWidget(){

	if (!saved)
	{
		saveTrace();
	}
}

void MyWidget::sliderValueChanged()
{
	//qDebug() << "slider!!!" << translateXSlider->value();
	theModel.sliderPosition.x = translateXSlider->value();
	theModel.sliderPosition.y = translateYSlider->value();
	theModel.sliderPosition.z = translateZSlider->value();
	//myGlWindow->repaint();
}


void MyWidget::keyPressEvent(QKeyEvent* e)
{
	std::cout << "key event!" << std::endl;
	switch (e->key())
	{
	case Qt::Key::Key_W:
		myGlWindow->camera.moveForward();
		//std::cout << "forward" << std::endl;
		break;
	case Qt::Key::Key_S:
		myGlWindow->camera.moveBackwards();
		break;
	case Qt::Key::Key_A:
		myGlWindow->camera.strafeLeft();
		break;
	case Qt::Key::Key_D:
		myGlWindow->camera.strafeRight();
		break;
	case Qt::Key::Key_R:
		myGlWindow->camera.moveUp();
		break;
	case Qt::Key::Key_F:
		myGlWindow->camera.moveDown();
		break;
	default:
		break;
	}
	//myGlWindow->repaint();
}


void MyWidget::createActions()
{
	renderIntoPixmapAct = new QAction(tr("&Render into Pixmap..."), this);
	renderIntoPixmapAct->setShortcut(tr("Ctrl+R"));
	//connect(renderIntoPixmapAct, SIGNAL(triggered()),
		//this, SLOT(renderIntoPixmap()));

	 
	chooseColorAct = new QAction(tr("C&hoose Color"), this);
	chooseColorAct->setShortcut(tr("Ctrl+H"));
	connect(chooseColorAct, SIGNAL(triggered()), this, SLOT(setColor()));

	saveSettingsAct = new QAction(tr("Save S&ettings"), this);
	saveSettingsAct->setShortcut(tr("Ctrl+E"));
	//connect(saveSettingsAct, SIGNAL(triggered()),this, SLOT(saveSettings()));

	

	translateViewAct = new QAction(tr("&Translate View"), this);
	translateViewAct->setShortcut(tr("Ctrl+T"));
	connect(translateViewAct, SIGNAL(triggered()), this, SLOT(translate()));

	modelingParametersAct = new QAction(tr("&Modeling Parameters"), this);
	modelingParametersAct->setShortcut(tr("Ctrl+M"));
	connect(modelingParametersAct, SIGNAL(triggered()), this, SLOT(parameters()));

	saveModelDataToFileAct = new QAction(tr("Save Model&Data To File"), this);
	saveModelDataToFileAct->setShortcut(tr("Ctrl+D"));
	//connect(saveModelDataToFileAct, SIGNAL(triggered()), this, SLOT(saveModelDataToFile()));

	exitAct = new QAction(tr("E&xit"), this);
	exitAct->setShortcuts(QKeySequence::Quit);
	//connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

	aboutAct = new QAction(tr("&About"), this);
	connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

	aboutQtAct = new QAction(tr("About &Qt"), this);
	//connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MyWidget::parameters()
{
	//std::cout << "parameters" << std::endl;
 
	//QPushButton *quitButton = new QPushButton("OK");

	//connect(quitButton, SIGNAL(clicked()), &parametersDialog, SLOT(close()));

	parametersDialog->exec();
}

void MyWidget::translate(){
	std::cout << "translate" << std::endl;
	translateDialog->exec();
}

void MyWidget::about()
{
	QLabel *icon = new QLabel;
  

	QLabel *text = new QLabel;
	text->setWordWrap(true);
	text->setText( 
		"<p>User can manipulate simple mathematical rules that generate"
		" scaling, rotation and translation values for model generation extrusion steps."
		" </p>");

	QPushButton *quitButton = new QPushButton("OK");

	QHBoxLayout *topLayout = new QHBoxLayout;
	topLayout->setMargin(10);
	topLayout->setSpacing(10);
	topLayout->addWidget(icon);
	topLayout->addWidget(text);

	QHBoxLayout *bottomLayout = new QHBoxLayout;
	bottomLayout->addStretch();
	bottomLayout->addWidget(quitButton);
	bottomLayout->addStretch();

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(topLayout);
	mainLayout->addLayout(bottomLayout);

	QDialog about(this);
	about.setModal(true);
	about.setWindowTitle(tr("About Matrix Modeling App"));
	about.setLayout(mainLayout);

	connect(quitButton, SIGNAL(clicked()), &about, SLOT(close()));

	about.exec();
}

void MyWidget::setColor()
{
	
/*	if (native->isChecked())
		color = QColorDialog::getColor(Qt::green, this);
	else
		*/
	color = QColorDialog::getColor(Qt::green, this, "Select Color", QColorDialog::DontUseNativeDialog);
	qreal red;
	qreal green;
	qreal blue;
	color.getRgbF(&red, &green, &blue);
	int r, g, b;
	color.getRgb(&r, &g, &b);

	theModel.color = glm::vec3(red, green, blue);
	if (color.isValid()) {
		colorLabel->setText("Color : " + QString::number(red) + ", " + QString::number(green) + ", " + QString::number(blue)  );
		colorLabel->setPalette(QPalette(color));
		colorLabel->setAutoFillBackground(true);
	}

	myGlWindow->updateColor();
}

void MyWidget::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(renderIntoPixmapAct);

	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);

	fileMenu = menuBar()->addMenu(tr("&View"));
	fileMenu->addAction(translateViewAct);

	fileMenu = menuBar()->addMenu(tr("&Model"));
	fileMenu->addAction(modelingParametersAct);
	fileMenu->addAction(chooseColorAct);
	fileMenu->addAction(saveSettingsAct);
	fileMenu->addAction(saveModelDataToFileAct);

	helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(aboutAct);
	helpMenu->addAction(aboutQtAct);
}