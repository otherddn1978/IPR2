#include "texteditor.h"
#include <QAbstractItemView>
#include <QCompleter>
#include <QKeyEvent>
#include <QScrollBar>

TextEditor::TextEditor(QCompleter *c, QWidget *parent) : QTextEdit(parent), comp(c)
{
    comp->setWidget(this);
    comp->setCompletionMode(QCompleter::PopupCompletion);
    comp->setCaseSensitivity(Qt::CaseInsensitive);
    QObject::connect(comp, SIGNAL(activated(QString)), this, SLOT(insertCompletion(QString)));
}

TextEditor::~TextEditor()
{
}

QCompleter *TextEditor::completer() const
{
    return comp;
}

void TextEditor::insertCompletion(const QString &completion)
{
    if (comp->widget() != this)
        return;

    QTextCursor tc = textCursor();
    int extra = completion.length() - comp->completionPrefix().length();
    tc.movePosition(QTextCursor::Left);
    tc.movePosition(QTextCursor::EndOfWord);
    tc.insertText(completion.right(extra));
    setTextCursor(tc);
}

void TextEditor::focusInEvent(QFocusEvent *e)
{
    comp->setWidget(this);
    QTextEdit::focusInEvent(e);
}

void TextEditor::keyPressEvent(QKeyEvent *e)
{
    if (comp->popup()->isVisible()) {
        // Следующие коды клавиш перенаправляются дополнителем виджету
        switch (e->key()) {
        case Qt::Key_Enter:
        case Qt::Key_Return:
        case Qt::Key_Escape:
        case Qt::Key_Tab:
        case Qt::Key_Backtab: e->ignore(); return; // позволим дополнителю поведение по умолчанию
        default: break;
        }
    }

    QTextEdit::keyPressEvent(e);

    QTextCursor tc = textCursor();
    tc.select(QTextCursor::WordUnderCursor);
    QString completionPrefix = tc.selectedText();

    if (completionPrefix.length() < 3) {
        comp->popup()->hide();
        return;
    }

    if (completionPrefix != comp->completionPrefix()) {
        comp->setCompletionPrefix(completionPrefix);
        comp->popup()->setCurrentIndex(comp->completionModel()->index(0, 0));
    }

    QRect cr = cursorRect();
    cr.setWidth(comp->popup()->sizeHintForColumn(0) + comp->popup()->verticalScrollBar()->sizeHint().width());
    comp->complete(cr); // выталкиваем его вверх!
}
