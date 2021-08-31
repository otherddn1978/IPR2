#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAbstractItemModel;
class QCompleter;
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
    QAbstractItemModel *modelForCompleter();

    QCompleter *completer;
    TextEditor *textEditor;
};

#endif // MAINWINDOW_H
