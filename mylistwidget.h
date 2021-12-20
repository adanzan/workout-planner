#ifndef MYLISTWIDGET_H
#define MYLISTWIDGET_H

#include <QListWidget>

class MyListWidget : public QListWidget {
Q_OBJECT
protected:
    void keyPressEvent(QKeyEvent *event) override;
public:
    MyListWidget();
signals:
    void backspaceKeyPressed();
};

#endif // MYLISTWIDGET_H
