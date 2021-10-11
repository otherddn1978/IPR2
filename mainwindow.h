#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class TextEditor;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

private slots:
    void fileOpen();
    void fileSave();

private:
    void createMenu();

    TextEditor *textEditor;
};

#endif // MAINWINDOW_H
