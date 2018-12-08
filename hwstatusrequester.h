#ifndef HWSTATUSREQUESTER_H
#define HWSTATUSREQUESTER_H

#include <QObject>
#include <QTimer>

#include <hardware.hh>

class HWStatusRequester : public QObject
{
    Q_OBJECT
public:
    explicit HWStatusRequester(QObject *parent = 0);
    void setHWBroker(icore::HWBroker_ptr hwbroker);
    
signals:
    void printString(QString);
    
public slots:
    void requestStatus();
    void setAuto(bool state);
    void setRequestPeriod(int period);

private:
    void displayList(icore::DevicesList *list, int level=0);

    QTimer timer_;
    icore::HWBroker_ptr hwbroker_;
    class Widget *widget_;
    class TreeModel *model_;
    
};

#endif // HWSTATUSREQUESTER_H
