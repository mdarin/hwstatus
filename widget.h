#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QAbstractItemModel>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    void setModel(QAbstractItemModel *model);
    ~Widget();

public slots:
    void appendString(QString str);

signals:
    void manualUpdate();
    void autoUpdate(bool state);
    void updatePeriod(int seconds);
    
private slots:
    void mUpdate();
    void aUpdate(bool state);
    void uPeriod(int seconds);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
