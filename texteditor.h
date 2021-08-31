#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QTextEdit>

class QCompleter;

class TextEditor : public QTextEdit
{
    Q_OBJECT

public:
    TextEditor(QCompleter *c, QWidget *parent = 0);
    ~TextEditor();

    QCompleter *completer() const;

protected:
    void keyPressEvent(QKeyEvent *e);
    void focusInEvent(QFocusEvent *e);

private slots:
    void insertCompletion(const QString &completion);

private:
    QCompleter *comp;
};

#endif // TEXTEDITOR_H
