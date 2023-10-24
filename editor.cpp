#include "editor.h"

Editor::Editor(QWidget *parent) : QTextEdit(parent)
{
    QTextListFormat list_format;
    list_format.setStyle(QTextListFormat::ListDisc);
    this->textCursor().insertList(list_format);
}

void Editor::keyPressEvent(QKeyEvent *event)
{
    int keyPressed = event->key();

    if((keyPressed == Qt::Key_Return || keyPressed == Qt::Key_Enter))
    {
        qDebug() << "Enter or return key pressed.";

        if(isLineEmpty(this->textCursor()))
        {
            this->textCursor().insertText("\n");
        }
        else if(!isLineEmpty(this->textCursor()))
        {
            QTextEdit::keyPressEvent(event);
        }
    }
    else if(keyPressed == Qt::Key_Backspace)
    {
        if(isCursorAtStartOfLine(this->textCursor()))
        {
            qDebug() << "Cursor is at the start of a line.";

            QString currentBlockText = this->textCursor().block().text();
            deleteLine();
            QTextEdit::keyPressEvent(event);
            gotoPreviousLine();
            this->textCursor().insertText(currentBlockText);


        }
        else
        {
            QTextEdit::keyPressEvent(event);
        }
    }
    else
    {
        QTextEdit::keyPressEvent(event);
    }
}

void Editor::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "Mouse pressed.";
    QTextEdit::mousePressEvent(event);
}

// private

void Editor::deleteLine()
{
    QTextCursor temp = this->textCursor();
    temp.movePosition(QTextCursor::StartOfLine);
    temp.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
    temp.removeSelectedText();
}

void Editor::gotoPreviousLine()
{
    QTextCursor temp = this->textCursor();
    temp.movePosition(QTextCursor::Up);
    temp.movePosition(QTextCursor::EndOfLine);
    this->setTextCursor(temp);
}

bool Editor::isCursorAtStartOfLine(QTextCursor cursor)
{
    return cursor.positionInBlock() == 0;
}

bool Editor::isLineEmpty(QTextCursor cursor)
{
    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
    return cursor.selectedText().trimmed().isEmpty();
}
