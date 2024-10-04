#include "mainViewWidget.h"

MainViewWidget::MainViewWidget(QWidget* parent)
{
	file = new Labels();

	QVBoxLayout* layout = new QVBoxLayout();

	QHBoxLayout* pageLayout = new QHBoxLayout();
	QSpacerItem* spacer1 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	QSpacerItem* spacer2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	QPushButton* previous = new QPushButton("Previous");
	QPushButton* next = new QPushButton("Next");
	connect(previous, &QPushButton::pressed, this, &MainViewWidget::PreviousOnClick);
	connect(next, &QPushButton::pressed, this, &MainViewWidget::NextOnClick);
	pageInput = new QSpinBox();
	pageInput->setMaximum(0);
	connect(pageInput, &QSpinBox::valueChanged, this, &MainViewWidget::SpinBoxValueSet);
	pageNum = new QLabel("0");
	pageLayout->addItem(spacer1);
	pageLayout->addWidget(previous);
	pageLayout->addWidget(pageInput);
	pageLayout->addWidget(pageNum);
	pageLayout->addWidget(next);
	pageLayout->addItem(spacer2);

	QHBoxLayout* mainLayout = new QHBoxLayout();
	display = new QPlainTextEdit();
	display->setMinimumHeight(500);
	display->setMinimumWidth(400);
	QWidget* label = new QWidget();
	label->setMinimumHeight(500);
	label->setMinimumWidth(200);

	// set labels toggle button
	labelLayout = new QVBoxLayout(label);
	//QCheckBox* cb1 = new QCheckBox("Hypertension");
	//QCheckBox* cb2 = new QCheckBox("Cholesterol");
	//QCheckBox* cb3 = new QCheckBox("Type 1 diabetes");
	//QCheckBox* cb4 = new QCheckBox("Type 2 diabetes");
	//QCheckBox* cb5 = new QCheckBox("Active smoker");
	//QCheckBox* cb6 = new QCheckBox("Ex-smoker");
	//QCheckBox* cb7 = new QCheckBox("Family history");
	//QCheckBox* cb8 = new QCheckBox("Atrial fibrillation");
	//QCheckBox* cb9 = new QCheckBox("HFpEF");
	//QCheckBox* cb10 = new QCheckBox("HFrEF");
	//QCheckBox* cb11 = new QCheckBox("IHD");
	//QCheckBox* cb12 = new QCheckBox("Non-obstructive coronary atherosclerosis");
	//cbGroup.push_back(cb1);
	//cbGroup.push_back(cb2);
	//cbGroup.push_back(cb3);
	//cbGroup.push_back(cb4);
	//cbGroup.push_back(cb5);
	//cbGroup.push_back(cb6);
	//cbGroup.push_back(cb7);
	//cbGroup.push_back(cb8);
	//cbGroup.push_back(cb9);
	//cbGroup.push_back(cb10);
	//cbGroup.push_back(cb11);
	//cbGroup.push_back(cb12);
	//labelLayout->addWidget(cb1);
	//labelLayout->addWidget(cb2);
	//labelLayout->addWidget(cb3);
	//labelLayout->addWidget(cb4);
	//labelLayout->addWidget(cb5);
	//labelLayout->addWidget(cb6);
	//labelLayout->addWidget(cb7);
	//labelLayout->addWidget(cb8);
	//labelLayout->addWidget(cb9);
	//labelLayout->addWidget(cb10);
	//labelLayout->addWidget(cb11);
	//labelLayout->addWidget(cb12);

	mainLayout->addWidget(display);
	mainLayout->addWidget(label);

	layout->addLayout(pageLayout);
	layout->addLayout(mainLayout);

	this->setLayout(layout);
}

MainViewWidget::~MainViewWidget()
{
}

void MainViewWidget::InitializeCBGroup()
{
	ClearLayout(labelLayout);
	cbGroup.clear();
	vector<string> attributes = file->GetAttributes();
	for (int i = 0; i < attributes.size(); i++)
	{
		QCheckBox* cb = new QCheckBox(QString::fromStdString(attributes[i]));
		cbGroup.push_back(cb);
		labelLayout->addWidget(cb);
	}
	QSpacerItem* sp = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
	labelLayout->addItem(sp);
}

void MainViewWidget::UpdateDisplay(int id)
{
	if (file->GetFilePath() != "")
	{
		index = id;
		//update spinbox
		pageInput->blockSignals(true);
		pageInput->setValue(id + 1);
		pageInput->blockSignals(false);

		//update content widget
		display->setPlainText(QString::fromStdString(file->GetContent(id)));

		// update labels
		string label = file->GetLabels(id);

		for (int i = 0; i < label.size(); i++)
		{
			cbGroup[i]->setChecked(label.substr(i, 1) == "1");
		}
	}
}

bool MainViewWidget::ReadCSV(std::string filepath)
{
	if (file->ReadCSV(filepath))
	{
		InitializeCBGroup();
		pageNum->setText(QString::number(file->GetSize()));
		pageInput->blockSignals(true);
		pageInput->setMinimum(1);
		pageInput->setMaximum(file->GetSize());
		pageInput->blockSignals(false);
		UpdateDisplay(0);
		return true;
	}
	else
	{
		/*pageNum->setText("0");
		pageInput->blockSignals(true);
		pageInput->setMinimum(0);
		pageInput->setMaximum(0);
		pageInput->blockSignals(false);
		display->setPlainText("");
		for (int i = 0; i < cbGroup.size(); i++)
		{
			cbGroup[i]->setChecked(false);
		}*/
		return false;
	}
}

void MainViewWidget::SaveCSV()
{
	if (file->GetFilePath() != "")
	{
		file->SaveCSV();
	}
}

void MainViewWidget::SaveCSVAs(string filepath)
{
	if (file->GetFilePath() != "")
	{
		file->SaveCSV(filepath);
	}
}

void MainViewWidget::SavePage()
{
	if (file->GetFilePath() != "")
	{
		file->SetContent(index, display->toPlainText().toStdString());
		string newLabel = "";
		for (int i = 0; i < cbGroup.size(); i++)
		{
			if (cbGroup[i]->isChecked())
				newLabel += "1";
			else
				newLabel += "0";
		}
		file->SetLabels(index, newLabel);
	}
}

void MainViewWidget::SetAutoSave(bool val)
{
	autosave = val;
}

void MainViewWidget::DeleteRecord()
{
	file->DeleteRecord(index);
	if (index - 1 < 0)
		index = 0;
	else
		index = index - 1;

	if (file->GetSize() > 0)
	{
		pageNum->setText(QString::number(file->GetSize()));
		pageInput->blockSignals(true);
		pageInput->setMinimum(1);
		pageInput->setMaximum(file->GetSize());
		pageInput->blockSignals(false);
		UpdateDisplay(index);
	}
	else
	{
		pageNum->setText("0");
		pageInput->blockSignals(true);
		pageInput->setMinimum(0);
		pageInput->setMaximum(0);
		pageInput->blockSignals(false);
		display->setPlainText("");
		for (int i = 0; i < cbGroup.size(); i++)
		{
			cbGroup[i]->setChecked(false);
		}
	}
}

int MainViewWidget::GetCurrentIndex()
{
	return index;
}

string MainViewWidget::GetFilePath()
{
	return file->GetFilePath();
}

void MainViewWidget::ClearLayout(QLayout* layout)
{
	if (layout == NULL)
		return;
	QLayoutItem* item;
	while ((item = layout->takeAt(0))) {
		if (item->layout()) {
			ClearLayout(item->layout());
			item->layout()->deleteLater();
		}
		if (item->widget()) {
			item->widget()->deleteLater();
		}
		delete item;
	}
}

void MainViewWidget::NextOnClick()
{
	pageInput->setValue(index + 2);
}

void MainViewWidget::PreviousOnClick()
{
	pageInput->setValue(index);
}

void MainViewWidget::SpinBoxValueSet(int val)
{
	SavePage();
	if(autosave)
		file->SaveCSV();
	UpdateDisplay(val - 1);
}


