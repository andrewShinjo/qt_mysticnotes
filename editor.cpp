#include "editor.h"

Editor::Editor(QWidget *parent) : QTextEdit(parent)
{
    document()->setIndentWidth(20);
    setTabStopDistance(20);

    QTextCursor cursor = textCursor();
    QTextCharFormat format;

    QFont font;
    font.setPointSize(12);

    setFont(font);
}

void Editor::keyPressEvent(QKeyEvent *event)
{
    int keyPressed = event->key();
    bool cursorOnList = this->textCursor().currentList() != nullptr;

    if(!cursorOnList)
    {
        if(keyPressed == Qt::Key_Space)
        {
            qDebug() << "Key pressed: Space";
            QString text = this->textCursor().block().text();

            if(text.compare("-") == 0)
            {
                deleteLine();
                QTextListFormat listFormat;
                listFormat.setStyle(QTextListFormat::ListDisc);
                this->textCursor().insertList(listFormat);
            }
            else if(text.compare("#") == 0)
            {
                qDebug() << "H1";

                QTextEdit::keyPressEvent(event);
                changeFontSizeOfEntireLine(32);
            }
            else if(text.compare("##") == 0)
            {
                qDebug() << "H2";

                QTextEdit::keyPressEvent(event);
                changeFontSizeOfEntireLine(28);
            }
            else if(text.compare("###") == 0)
            {
                qDebug() << "H3";

                QTextEdit::keyPressEvent(event);
                changeFontSizeOfEntireLine(25);
            }
            else if(text.compare("####") == 0)
            {
                qDebug() << "H4";

                QTextEdit::keyPressEvent(event);
                changeFontSizeOfEntireLine(22);
            }
            else if(text.compare("#####") == 0)
            {
                qDebug() << "H5";

                QTextEdit::keyPressEvent(event);
                changeFontSizeOfEntireLine(18);
            }
            else if(text.compare("######") == 0)
            {
                qDebug() << "H6";

                QTextEdit::keyPressEvent(event);
                changeFontSizeOfEntireLine(15);
            }
            else
            {
                QTextEdit::keyPressEvent(event);
            }
        }
        else if(keyPressed == Qt::Key_Return || keyPressed == Qt::Key_Enter)
        {
            QTextCharFormat format;
            format.setFontPointSize(12);
            textCursor().insertText("\n", format);
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
            QTextEdit::keyPressEvent(event);
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
        else if(keyPressed == Qt::Key_Space)
        {

        }
        else if(keyPressed == Qt::Key_Tab)
        {
            /** Situation: If tab is pressed when the cursor is on a list:
             *  if the current bullet point is the top of the list, then do nothing
             *
             *
             **/

            qDebug() << "Tab pressed.";

            int currentIndent, previousIndent;

            currentIndent = textCursor().currentList()->format().indent();

            QTextCursor temp = textCursor();
            temp.movePosition(QTextCursor::PreviousBlock);
            QTextList* previousList = temp.currentList();

            if(previousList)
            {
                QTextListFormat listFormat = previousList->format();
                previousIndent = listFormat.indent();
            }
            else
            {
                return;
            }

            if(currentIndent == previousIndent)
            {
                QTextListFormat listFormat = textCursor().currentList()->format();
                listFormat.setIndent(currentIndent + 1);
                textCursor().currentList()->setFormat(listFormat);
            }
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

void Editor::changeFontSizeOfEntireLine(int fontSize)
{
    QTextCursor cursor = textCursor();
    QTextCharFormat format;
    format.setFontPointSize(fontSize);
    cursor.select(QTextCursor::LineUnderCursor);
    cursor.mergeCharFormat(format);
}
