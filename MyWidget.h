#pragma once
#include <QtGui\qwidget.h>
#include <QtGui\qmainwindow.h>
#include <QtGui\qmenu.h>
#include <QtGui\qaction.h>
#include <QtCore\qelapsedtimer.h>
#include <QtGui\qlabel.h>
#include <QtGui\QVBoxLayout>
#include <QtGui\qspinbox.h>
#include <QtGui\QDialog>

#include <QtCore\QString>

#include <MyModel.h>
#include <sstream>
class DebugSlider;
class MyGLWindow; // forward declare
class MyWidget : public  QMainWindow
{
	Q_OBJECT
	DebugSlider * translateXSlider;
	DebugSlider * translateYSlider;
	DebugSlider * translateZSlider;

	
	DebugSlider * extrudeRotationAngleStartSlider;

	DebugSlider * scaleUndlAmountX;
	DebugSlider * scaleUndlAmountZ;
	DebugSlider * scaleUndlRateX;
	DebugSlider * scaleUndlRateZ;

	DebugSlider * extrTransXSlider;
	DebugSlider * extrTransYSlider;
	DebugSlider * extrTransZSlider;
 

	QLabel *label;
	QLabel *sblabel;
	QLabel *cameraPositionLabel;
	QSpinBox * spinBox;
    QSpinBox * numModelsSpinBox;
	QSpinBox * numExtrSpinBox;
	QLabel *numExtrLabel;

	QString cameraposInfo;

	MyGLWindow * myGlWindow;
	MyModel theModel;
	int elapsed;
	QElapsedTimer etimer;
	int previousTime;
	std::ostringstream debugstr;
	std::string currtimeStr;
	bool savefpsTracing;
	bool saved;
	void MyWidget::saveTrace();


	QWidget *centralWidget;
	void createActions();
	void createMenus();
	QMenu *fileMenu;
	QMenu *helpMenu;
	QAction *saveSettingsAct;
	QAction *chooseColorAct;
	QAction *modelingParametersAct;
	QAction *translateViewAct;
	QAction *renderIntoPixmapAct;
	QAction *saveModelDataToFileAct;
	QAction *exitAct;
	QAction *aboutAct;
	QAction *aboutQtAct;
	QVBoxLayout* controlsLayout;
	QDialog * parametersDialog;
	QDialog * translateDialog;
	QColor color;
	QLabel * colorLabel;

	private slots:
	void sliderValueChanged();
	void spinBValueChanged(int);
	void numExtrspinBValueChanged(int);
    void numModelsSpinBValueChanged(int);
    
	void exsliderValueChanged();
	void exsTrliderValueChanged();
	void  animate();
	void about();
	void parameters();
	void translate();
	void setColor();
protected:
	void keyPressEvent(QKeyEvent* e);
public:
	MyWidget();
	~MyWidget();
};

