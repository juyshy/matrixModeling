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

	// fullscreen:
	QRect r = QApplication::desktop()->availableGeometry();
	//r.setLeft(r.center().x());
	resize(r.width(), r.height());
	move(r.topLeft());
	
	// labels:
	label = new QLabel(tr("FPS:"));
	sblabel = new QLabel("triangles: ");

	spinBox = new QSpinBox;
	spinBox->setRange(3, 130);
	spinBox->setMaximumWidth(100);

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
	labelLayout->addWidget(sblabel);
	labelLayout->addWidget(spinBox);
	controlsLayout = new QVBoxLayout;
	//mainLayout->addLayout(controlsLayout  );
	myGlWindow = new MyGLWindow(&theModel);
	mainLayout->addWidget(myGlWindow);


	QHBoxLayout* extrScaleLayout;
	controlsLayout->addLayout(extrScaleLayout = new QHBoxLayout);
	extrScaleLayout->addWidget(extrScaleXSlider = new DebugSlider(-1.05f, 1));
	extrScaleLayout->addWidget(extrScaleYSlider = new DebugSlider(-1.05f, 1));
	extrScaleLayout->addWidget(extrScaleZSlider = new DebugSlider(-1.05f, 1));
	extrScaleLayout->addWidget(extrScaleWSlider = new DebugSlider(-1.05f, 1));


	QHBoxLayout* extrTransLayout;
	controlsLayout->addLayout(extrTransLayout = new QHBoxLayout);
	extrTransLayout->addWidget(extrTransXSlider = new DebugSlider(0.0, 1));
	extrTransLayout->addWidget(extrTransYSlider = new DebugSlider(0.0, 1));
	extrTransLayout->addWidget(extrTransZSlider = new DebugSlider(0.0, 1));
	
 
	QHBoxLayout* lightPositionLayout;
	controlsLayout->addLayout(lightPositionLayout = new QHBoxLayout);
	lightPositionLayout->addWidget(lightXSlider = new DebugSlider);
	lightPositionLayout->addWidget(lightYSlider = new DebugSlider);
	lightPositionLayout->addWidget(lightZSlider = new DebugSlider);



	// initial values
	lightXSlider->setValue(-1.5f);
	lightYSlider->setValue(0);
	lightZSlider->setValue(0);
	saved = false;
	connect(extrScaleXSlider, SIGNAL(valueChanged(float)), this, SLOT(exsliderValueChanged()));
	connect(extrScaleYSlider, SIGNAL(valueChanged(float)), this, SLOT(exsliderValueChanged()));
	connect(extrScaleZSlider, SIGNAL(valueChanged(float)), this, SLOT(exsliderValueChanged()));
	connect(extrScaleWSlider, SIGNAL(valueChanged(float)), this, SLOT(exsliderValueChanged()));

	connect(extrTransXSlider, SIGNAL(valueChanged(float)), this, SLOT(exsTrliderValueChanged()));
	connect(extrTransYSlider, SIGNAL(valueChanged(float)), this, SLOT(exsTrliderValueChanged()));
	connect(extrTransZSlider, SIGNAL(valueChanged(float)), this, SLOT(exsTrliderValueChanged()));

	extrScaleXSlider->setValue(0);
	extrScaleYSlider->setValue(0);
	extrScaleZSlider->setValue(0);
	extrScaleWSlider->setValue(0);

	extrTransXSlider->setValue(0);
	extrTransYSlider->setValue(0.2f);
	extrTransZSlider->setValue(0);

	connect(lightXSlider, SIGNAL(valueChanged(float)), this, SLOT(sliderValueChanged()));
	connect(lightYSlider, SIGNAL(valueChanged(float)), this, SLOT(sliderValueChanged()));
	connect(lightZSlider, SIGNAL(valueChanged(float)), this, SLOT(sliderValueChanged()));
	connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(spinBValueChanged(int)));
	theModel.sliderPosition.x = lightXSlider->value();
	theModel.sliderPosition.y = lightYSlider->value();
	theModel.sliderPosition.z = lightZSlider->value();


	parametersDialog = new QDialog(this);
	//parametersDialog.setParent(this);
	//parametersDialog.setModal(true);
	parametersDialog->setWindowTitle(tr("Extrusion parameters"));
	parametersDialog->setLayout(controlsLayout);

	createActions();
	createMenus();

	QTimer *timer = new QTimer(this);
	etimer.start();
	//connect(timer, SIGNAL(timeout()), native, SLOT(animate()));
	connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
	timer->start(1);
	elapsed=0;
	myGlWindow->repaint();
}
void MyWidget::exsTrliderValueChanged()
{
	if (myGlWindow->pModel.done) {
		myGlWindow->pModel.extrudetranslate1.x = extrTransXSlider->value();
		myGlWindow->pModel.extrudetranslate1.y = extrTransYSlider->value();
		myGlWindow->pModel.extrudetranslate1.z = extrTransZSlider->value();
		myGlWindow->pModel.rebuid();
	}
}
void MyWidget::exsliderValueChanged()
{
	if (myGlWindow->pModel.done) {
	myGlWindow->pModel.undulatingAmountX = extrScaleXSlider->value();
	myGlWindow->pModel.undulatingAmountZ = extrScaleYSlider->value();
	myGlWindow->pModel.undulatingRateX = extrScaleZSlider->value();
	myGlWindow->pModel.undulatingRateZ = extrScaleWSlider->value();
	myGlWindow->pModel.rebuid();
	}
	std::cout << extrScaleXSlider->value() << std::endl;
}
void MyWidget::spinBValueChanged(int newValue)
{
	myGlWindow->pModel.setTriagleCount(newValue);
	myGlWindow->pModel.rebuid();
	std::cout << spinBox->value()   << std::endl;
}

void MyWidget::animate(){
	elapsed = etimer.elapsed(); //(elapsed + qobject_cast<QTimer*>(sender())->interval()) % 100000;
	double fps = 1000.0 / (elapsed - previousTime);
	QString fpsstr = "FPS:" + QString::number(fps); 
	label->setText(fpsstr);

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
	//qDebug() << "slider!!!" << lightXSlider->value();
	theModel.sliderPosition.x = lightXSlider->value();
	theModel.sliderPosition.y = lightYSlider->value();
	theModel.sliderPosition.z = lightZSlider->value();
	//myGlWindow->repaint();
}


void MyWidget::keyPressEvent(QKeyEvent* e)
{
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

	saveSettingsAct = new QAction(tr("Save S&ettings"), this);
	saveSettingsAct->setShortcut(tr("Ctrl+E"));
	//connect(saveSettingsAct, SIGNAL(triggered()),this, SLOT(saveSettings()));

	
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

void MyWidget::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(renderIntoPixmapAct);

	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);

	fileMenu = menuBar()->addMenu(tr("&Model"));
	fileMenu->addAction(modelingParametersAct);
	fileMenu->addAction(saveSettingsAct);
	fileMenu->addAction(saveModelDataToFileAct);

	helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(aboutAct);
	helpMenu->addAction(aboutQtAct);
}