#include "mylistwidget.h"
#include <QKeyEvent>

MyListWidget::MyListWidget()
{

}
void MyListWidget::keyPressEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_Backspace){
        emit backspaceKeyPressed();
    }
    else{
        QListWidget::keyPressEvent(event);
    }
}
