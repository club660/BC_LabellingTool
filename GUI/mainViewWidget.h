#ifndef MAINVIEWWIDGET_H
#define MAINVIEWWIDGET_H

#include <qwidget.h>
#include <qpushbutton.h>
#include <qboxlayout.h>
#include <qlabel.h>
#include <qplaintextedit.h>
#include <qspinbox.h>
#include <string>
#include <qcheckbox.h>
#include <vector>

#include "labels.h"

class MainViewWidget :public QWidget
{
	Q_OBJECT
public:
	MainViewWidget(QWidget* parent = 0);
	~MainViewWidget();

	void InitializeCBGroup();
	void UpdateDisplay(int id);
	bool ReadCSV(std::string filepath);
	void SaveCSV();
	void SaveCSVAs(string filepath);
	void SavePage();
	void SetAutoSave(bool val);
	void DeleteRecord();

	int GetCurrentIndex();
	string GetFilePath();

	void ClearLayout(QLayout* layout);

public slots:
	void NextOnClick();
	void PreviousOnClick();
	void SpinBoxValueSet(int val);


private:
	Labels* file;

	QSpinBox* pageInput;
	QLabel* pageNum;
	QPlainTextEdit* display;
	vector<QCheckBox*> cbGroup;
	QVBoxLayout* labelLayout;

	int index = 0;
	bool autosave = true;
};


#endif // !MAINVIEWWIDGET_H