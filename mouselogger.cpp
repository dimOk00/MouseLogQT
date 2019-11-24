#include "mouselogger.h"

#include <QDebug>
#include <QString>

MouseLogger::MouseLogger(QWidget *parent) : QWidget(parent)
{
    isEnable = false;
}

void MouseLogger::trackEvent(QString type, QString button, int posX, int posY, QDateTime dateTime)
{
    if(!isEnable)
        return;

    MouseEvent* mouseEvent= new MouseEvent();
    mouseEvent->type = type;
    mouseEvent->posX = posX;
    mouseEvent->posY = posY;
    mouseEvent->button = button;
    mouseEvent->dateTime = dateTime;

    mouseEvents.append(mouseEvent);

    QString result =  mouseEvent->type + " " +
                      QString::number(mouseEvent->posX) + " " +
                      QString::number(mouseEvent->posY) + " " +
                      mouseEvent->button + " " +
                      mouseEvent->dateTime.toString();

    qDebug() << result;
}

void MouseLogger::mousePressEvent(QMouseEvent *e)
{
    QString buttonsString = MouseLogger::enumNamesFromMouseButtons(e->buttons());
    trackEvent("Натискання", buttonsString, e->x(), e->y(), QDateTime::currentDateTime());
}

void MouseLogger::mouseReleaseEvent(QMouseEvent *e)
{
    QString buttonsString = MouseLogger::enumNamesFromMouseButtons(e->buttons());
    trackEvent("Відпускання", buttonsString, e->x(), e->y(), QDateTime::currentDateTime());

}

void MouseLogger::mouseDoubleClickEvent(QMouseEvent *e)
{
    QString buttonsString = MouseLogger::enumNamesFromMouseButtons(e->buttons());
    trackEvent("Подвійний клік", buttonsString, e->x(), e->y(), QDateTime::currentDateTime());
}

#if QT_CONFIG(wheelevent)
void MouseLogger::wheelEvent (QWheelEvent *e)
{
    if (e->delta() > 0) {

        if (e->orientation() == Qt::Vertical) {
            trackEvent("Прокрутка вверх", "колесо миші", e->x(), e->y(), QDateTime::currentDateTime());
        } else {
            trackEvent("Прокрутка вліво", "колесо миші", e->x(), e->y(), QDateTime::currentDateTime());
        }
    } else if (e->delta() < 0) {
        if (e->orientation() == Qt::Vertical) {
            trackEvent("Прокрутка вниз", "колесо миші", e->x(), e->y(), QDateTime::currentDateTime());
        } else {
            trackEvent("Прокрутка вправо", "колесо миші", e->x(), e->y(), QDateTime::currentDateTime());
        }
    }
}
#endif

int MouseLogger::buttonByNumber(const Qt::MouseButton button)
{
    if (button == Qt::NoButton)      return 0;
    if (button == Qt::LeftButton)    return 1;
    if (button == Qt::RightButton)   return 2;
    if (button == Qt::MiddleButton)  return 3;
    if (button == Qt::BackButton)    return 8;
    if (button == Qt::ForwardButton) return 9;
    if (button == Qt::TaskButton)    return 10;
    qDebug("QMouseShortcutEntry::addShortcut contained Invalid Qt::MouseButton value");
    return 0;
}

QString MouseLogger::enumNameFromValue(const Qt::MouseButton button)
{
    if (button == Qt::NoButton)      return "Без клавіши";
    if (button == Qt::LeftButton)    return "Ліва клавіша";
    if (button == Qt::RightButton)   return "Права клавіша";
    if (button == Qt::MiddleButton)  return "Центральна клавіша";
    if (button == Qt::BackButton)    return "Клавіша назад";
    if (button == Qt::ForwardButton) return "Клавіша вперед";
    if (button == Qt::TaskButton)    return "Клавіша задач";
    qDebug("QMouseShortcutEntry::addShortcut contained Invalid Qt::MouseButton value");
    return "NoButton";
}

QString MouseLogger::enumNamesFromMouseButtons(const Qt::MouseButtons buttons)
{
    QString returnText = "";
    if (buttons == Qt::NoButton)     return "Без клавіши";
    if (buttons & Qt::LeftButton)    returnText += "Ліва клавіша";
    if (buttons & Qt::RightButton)   returnText +=  "Права клавіша";
    if (buttons & Qt::MiddleButton)  returnText +=  "Центральна клавіша";
    if (buttons & Qt::BackButton)    returnText +=  "Клавіша назад";
    if (buttons & Qt::ForwardButton) returnText +=  "Клавіша вперед";
    if (buttons & Qt::TaskButton)    returnText +=  "Клавіша задач";
    return returnText;
}
