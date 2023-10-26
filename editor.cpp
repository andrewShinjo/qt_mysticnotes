#include "editor.h"

Editor::Editor(QWidget *parent) : QTextEdit(parent)
{
    QTextBlockFormat blockFormat = textCursor().blockFormat();
    blockFormat.setLeftMargin(10);
    textCursor().setBlockFormat(blockFormat);
}

void Editor::keyPressEvent(QKeyEvent *event)
{
    int keyPressed = event->key();
    bool cursorOnList = this->textCursor().currentList() != nullptr;

    if(!cursorOnList)
    {
        if(keyPressed == Qt::Key_Space)
        {
            qDebug() << "Spaced pressed.";
            QString text = this->textCursor().block().text();

            if(text.compare("-") == 0)
            {
                QTextBlockFormat blockFormat = textCursor().blockFormat();
                blockFormat.setLeftMargin(20);
                textCursor().setBlockFormat(blockFormat);
                deleteLine();
                QTextListFormat listFormat;
                listFormat.setStyle(QTextListFormat::ListDisc);
                listFormat.setIndent(0);
                this->textCursor().insertList(listFormat);
            }
        }
        else
        {
            QTextEdit::keyPressEvent(event);
        }
    }
    else if(cursorOnList)    // cursor is on a bullet point
    {
        if(keyPressed == Qt::Key_Return || keyPressed == Qt::Key_Enter)
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

                // Case: 1 bullet point
                if(this->textCursor().currentList()->count() == 1)
                {
                    QTextEdit::keyPressEvent(event);
                }

                QString currentBlockText = this->textCursor().block().text();

                deleteLine();

                QTextCursor temp = this->textCursor();
                temp.movePosition(QTextCursor::Up);

                if(!isLineEmpty(temp))
                {
                    QTextEdit::keyPressEvent(event);
                }

                this->textCursor().deletePreviousChar();
                this->textCursor().insertText(currentBlockText);
            }
            else
            {
                QTextEdit::keyPressEvent(event);
            }
        }
        else if(keyPressed == Qt::Key_Tab)
        {
            qDebug() << "Tab pressed.";
        }
        else
        {
            QTextEdit::keyPressEvent(event);
        }
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
