#ifndef MOUSELOGGER_H
#define MOUSELOGGER_H

#include "mouseevent.h"

#include <QWidget>
#include <QString>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QTimer>

class MouseLogger : public QWidget
{
public:
    MouseLogger(QWidget *parent = nullptr);
    QList<MouseEvent*> mouseEvents;
    bool isEnable;
    Q_OBJECT
protected:
    void    mousePressEvent(QMouseEvent *event) override;
    void    mouseReleaseEvent(QMouseEvent *event) override;
    void    mouseDoubleClickEvent(QMouseEvent *event) override;
#if QT_CONFIG(wheelevent)
    void    wheelEvent(QWheelEvent * event) override;
#endif
    int     buttonByNumber(const Qt::MouseButton button);
    QString enumNameFromValue(const Qt::MouseButton button);
    QString enumNamesFromMouseButtons(const Qt::MouseButtons buttons);
private:
    void trackEvent(QString type, QString button, int posX, int posY, QDateTime dateTime);
};

#endif // MOUSELOGGER_H
