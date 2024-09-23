#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qgridlayout.h>
#include <qtoolbar.h>
#include <qaction.h>
#include <qicon.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qsettings.h>

#include "mainViewWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QMainWindow* parent = 0); //Constructor
    ~MainWindow(); // Destructor

    void SaveSettings();
    void LoadSettings();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void OnOpenClicked();
    void OnSaveClicked();
    void OnAutoSaveToggled(bool checked);
    void OnDeleteClicked();
private:
    MainViewWidget* centralWidget;
    QAction* autoSAction;
};

#endif // MAINWIDGET_H