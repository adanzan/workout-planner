#include "mytreewidget.h"
#include <QKeyEvent>
#include <QDebug>
MyTreeWidget::MyTreeWidget() {


}
void MyTreeWidget::keyPressEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_Return){
        emit enterKeyPressed();
    }
    else{
        QTreeWidget::keyPressEvent(event);
    }
}
