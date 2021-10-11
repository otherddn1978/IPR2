#include "mainwindow.h"
#include "texteditor.h"
#include <QAction>
#include <QApplication>
#include <QCompleter>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    createMenu();

    textEditor = new TextEditor();

    setCentralWidget(textEditor);
    resize(600, 600);
    setWindowTitle(tr("Тесктовый редактор"));
}

void MainWindow::createMenu()
{
    QAction *exit = new QAction(tr("Выход"), this);
    QAction *fileOpen = new QAction(tr("Открыть"), this);
    QAction *fileSave = new QAction(tr("Сохранить"), this);

    connect(exit, &QAction::triggered, qApp, &QApplication::quit);
    connect(fileOpen, &QAction::triggered, this, &MainWindow::fileOpen);
    connect(fileSave, &QAction::triggered, this, &MainWindow::fileSave);

    QMenu *fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(fileOpen);
    fileMenu->addAction(fileSave);
    fileMenu->addAction(exit);
}

void MainWindow::fileOpen()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "./",
                                                    tr("Files types (*.txt *.cpp *.h)"));

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox msgBox;
        msgBox.setText("Error open file.");
        msgBox.exec();
        return;
    }

    textEditor->setPlainText("");

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        textEditor->append(line);
    }
}

void MainWindow::fileSave()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Open File"), "./",
                                                    tr("Files types (*.txt *.cpp *.h)"));

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox msgBox;
        msgBox.setText("Error open file.");
        msgBox.exec();
        return;
    }

    if (file.write(textEditor->toPlainText().toStdString().c_str()) == -1) {
        QMessageBox msgBox;
        msgBox.setText("Error write in file.");
        msgBox.exec();
        return;
    }
}
