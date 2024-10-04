#include <QMainWindow>
#include "MainWindow.h"
#include "qmenu.h"
#include "qmenubar.h"



// Constructor for main widget
MainWindow::MainWindow(QMainWindow* parent) :
    QMainWindow(parent)
{
    centralWidget = new MainViewWidget();

    QToolBar* toolbar = addToolBar("Main Toolbar");

    QAction* openAction = new QAction(QIcon("./icon/open.png"), "Open", this);
    QAction* saveAction = new QAction(QIcon("./icon/save.png"), "Save", this);
    QAction* deleteAction = new QAction(QIcon("./icon/delete.png"), "Delete", this);
    autoSAction = new QAction(QIcon("./icon/autosave.png"), "Auto Save", this);
    autoSAction->setCheckable(true);
    autoSAction->setChecked(true);
    connect(openAction, &QAction::triggered, this, &MainWindow::OnOpenClicked);
    connect(saveAction, &QAction::triggered, this, &MainWindow::OnSaveClicked);
    connect(autoSAction, &QAction::toggled, this, &MainWindow::OnAutoSaveToggled);
    connect(deleteAction, &QAction::triggered, this, &MainWindow::OnDeleteClicked);
    toolbar->addAction(openAction);
    toolbar->addAction(saveAction);
    toolbar->addAction(autoSAction);
    toolbar->addAction(deleteAction);

    setCentralWidget(centralWidget);
    setWindowTitle(tr("Labelling Tool"));
    LoadSettings();
}

// Destructor
MainWindow::~MainWindow()
{
}

void MainWindow::SaveSettings()
{
    QSettings settings("LabellingTools", "UserSettings");
    settings.setValue("windowSize", size());
    settings.setValue("windowPosition", pos());
    settings.setValue("autoSave", autoSAction->isChecked());
    settings.setValue("index", centralWidget->GetCurrentIndex());
    settings.setValue("filePath", QString::fromStdString(centralWidget->GetFilePath()));
}

void MainWindow::LoadSettings()
{
    QSettings settings("LabellingTools", "UserSettings");
    QSize windowSize = settings.value("windowSize").toSize();
    resize(windowSize);
    QPoint windowPos = settings.value("windowPosition").toPoint();
    move(windowPos);
    autoSAction->setChecked(settings.value("autoSave").toBool());

    if (!settings.value("filePath").toString().isEmpty())
    {
        if (centralWidget->ReadCSV(settings.value("filePath").toString().toStdString()))
            centralWidget->UpdateDisplay(settings.value("index").toInt());
    }
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    centralWidget->SavePage();
    centralWidget->SaveCSV();
    SaveSettings();

    // Ask the user if they really want to quit
    int result = QMessageBox::question(this, "Confirm Close", "Are you sure you want to exit?");
    if (result == QMessageBox::Yes) {
        event->accept();  // Accept the close event and allow the application to close
    }
    else {
        event->ignore();  // Ignore the close event and prevent the application from closing
    }
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_PageUp) {
        // Simulate left button click when the left arrow is pressed
        centralWidget->PreviousOnClick();
    }
    else if (event->key() == Qt::Key_PageDown) {
        // Simulate right button click when the right arrow is pressed
        centralWidget->NextOnClick();
    }
}

void MainWindow::OnSaveClicked()
{
    QString filepath = QFileDialog::getSaveFileName(
        this, tr("Open File"), "C://", "CSV files (*.csv)");
    if (!filepath.isEmpty()) {
        centralWidget->SaveCSVAs(filepath.toStdString());
    }
}

void MainWindow::OnAutoSaveToggled(bool checked)
{
    centralWidget->SetAutoSave(checked);
}

void MainWindow::OnDeleteClicked()
{
    int result = QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this record?");
    if (result == QMessageBox::Yes) {
        centralWidget->DeleteRecord();
    }
}

void MainWindow::OnOpenClicked()
{
    QString filepath = QFileDialog::getOpenFileName(
        this, tr("Open File"), "C://", "CSV files (*.csv)");
    if (!filepath.isEmpty()) {
        centralWidget->ReadCSV(filepath.toStdString());
    }
}
