#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardItemModel>
#include <QStandardItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    countOfItemsInTable = 0;

    mouseLogger = ui->mouseLoggerWidget;

    treeViewModel = new QStandardItemModel;

    QStringList horzHeaders;
    horzHeaders << "Тип події" <<
            "Час" <<
            "Координата X" <<
            "Координата Y" <<
            "Кнопка";
    treeViewModel->setHorizontalHeaderLabels(horzHeaders);

    ui->tableView->setModel(treeViewModel);
    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();

    timer = new QTimer();
    timer->setInterval(100);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTable()));
    timer->start();
}


void MainWindow::updateTable()
{
    if(mouseLogger->mouseEvents.isEmpty())
        return;

    int currentCountOfItems = mouseLogger->mouseEvents.count();
    if(currentCountOfItems == countOfItemsInTable)
        return;

    countOfItemsInTable = currentCountOfItems;

    auto mouseEvent = mouseLogger->mouseEvents.last();

    QList<QStandardItem *> anotherRow = prepareRow
    (
        mouseEvent->type,
        mouseEvent->dateTime.time().toString(),
        QString::number(mouseEvent->posX),
        QString::number(mouseEvent->posY),
        mouseEvent->button
    );

    treeViewModel->appendRow(anotherRow);
}

QList<QStandardItem *> MainWindow::prepareRow(const QString &first,
                                              const QString &second,
                                              const QString &third,
                                              const QString &forth,
                                              const QString &fifth) const
{
    return {new QStandardItem(first),
            new QStandardItem(second),
            new QStandardItem(third),
            new QStandardItem(forth),
            new QStandardItem(fifth)};
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Start_triggered()
{
    mouseLogger->isEnable = true;
}

void MainWindow::on_Pause_triggered()
{
    mouseLogger->isEnable = false;
}
