// A custom defined QTreeWidget used to modify the functionality of the return key
#ifndef MYTREEWIDGET_H
#define MYTREEWIDGET_H

#include <QTreeWidget>

class MyTreeWidget : public QTreeWidget {
Q_OBJECT
protected:
    void keyPressEvent(QKeyEvent *event) override;
public:
    MyTreeWidget();
signals:
    void enterKeyPressed();
};


#endif // MYTREEWIDGET_H
