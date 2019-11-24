#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mouselogger.h"

#include <QMainWindow>
#include <QStandardItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MouseLogger *mouseLogger;
    QTimer *timer;
    int countOfItemsInTable;
    QStandardItemModel *treeViewModel;

    QList<QStandardItem *> prepareRow(const QString &first,
                                      const QString &second,
                                      const QString &third,
                                      const QString &forth,
                                      const QString &fifth) const;

private slots:
    void updateTable();

    void on_Start_triggered();
    void on_Pause_triggered();
};
#endif // MAINWINDOW_H
