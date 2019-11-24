#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include <QString>
#include <QDateTime>

class MouseEvent
{
public:
    MouseEvent();

    QString type;
    QString button;
    int posX;
    int posY;
    QDateTime dateTime;
};

#endif // MOUSEEVENT_H
