#ifndef EDITOR_H
#define EDITOR_H

#include <QDebug>
#include <QKeyEvent>
#include <QTextCursor>
#include <QTextEdit>
#include <QTextList>
#include <QTextListFormat>

class Editor : public QTextEdit
{
    Q_OBJECT

public:
    Editor(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QTextCursor* cursor;
    QTextListFormat* text_list_format;
    void deleteLine();
    void gotoPreviousLine();
    bool isCursorAtStartOfLine(QTextCursor cursor);
    bool isLineEmpty(QTextCursor cursor);
};

#endif // EDITOR_H
