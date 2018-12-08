#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->pushButtonManual, SIGNAL(clicked()), SLOT(mUpdate()));
    connect(ui->toolButtonAuto, SIGNAL(toggled(bool)), SLOT(aUpdate(bool)));
    connect(ui->spinBoxPeriod, SIGNAL(valueChanged(int)), SLOT(uPeriod(int)));
}

void Widget::setModel(QAbstractItemModel *model)
{
    ui->treeView->setModel(model);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::appendString(QString str)
{
    ui->plainTextEdit->appendPlainText(str);
}

void Widget::mUpdate()
{
    emit manualUpdate();
}

void Widget::aUpdate(bool state)
{
    emit autoUpdate(state);
    if(state)
        emit updatePeriod(ui->spinBoxPeriod->value());
}

void Widget::uPeriod(int seconds)
{
    emit updatePeriod(seconds);
}
