#include "hwstatusrequester.h"
#include "widget.h"
#include "treemodel.h"
#include <QTextCodec>

HWStatusRequester::HWStatusRequester(QObject *parent) :
    QObject(parent)
{
    timer_.setInterval(5000);
    widget_ = new Widget;
    model_ = new TreeModel(this);
    widget_->setModel(model_);
    connect(widget_, SIGNAL(manualUpdate()), SLOT(requestStatus()));
    connect(widget_, SIGNAL(autoUpdate(bool)), SLOT(setAuto(bool)));
    connect(widget_, SIGNAL(updatePeriod(int)), SLOT(setRequestPeriod(int)));
    connect(&timer_, SIGNAL(timeout()), SLOT(requestStatus()));
    connect(this, SIGNAL(printString(QString)), widget_, SLOT(appendString(QString)));

    widget_->show();
}

void HWStatusRequester::setHWBroker(icore::HWBroker_ptr hwbroker)
{
    hwbroker_ = icore::HWBroker::_duplicate(hwbroker);
}

void HWStatusRequester::requestStatus()
{
    //TODO: try..catch ?
    icore::DevicesList *list =  hwbroker_->getDevicesList();
//    icore::DevicesList *list =  hwbroker_->getFakeDevieList(true);
    displayList(list);
}

void HWStatusRequester::setAuto(bool state)
{
    if(state)
        timer_.start();
    else
        timer_.stop();
}

void HWStatusRequester::setRequestPeriod(int period)
{
    timer_.setInterval(period*1000);
}

void HWStatusRequester::displayList(icore::DevicesList *list, int level/*=0*/)
{
    QString f_s;
    f_s.fill('\t', level);

    for(int i=0; i<list->length(); i++){

        icore::Device device = list->operator [](i);

        qDebug(qPrintable(QString("%1%2").arg(f_s).arg(QString(device.type))));
        qDebug(qPrintable(QString("%1%2").arg(f_s).arg(QString(device.status ? "ok" : "bad"))));
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        QByteArray barr(device.status_description);
        QString st_desc = codec->toUnicode(barr);
        emit printString(st_desc);
        qDebug(qPrintable(QString("%1%2").arg(f_s).arg(st_desc)));
        displayList(&device.subdevices, 1+level);
        qDebug("");
    }

}
