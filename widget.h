#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSerialPort>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QSerialPort *m_serial;

private:
    Ui::Widget *ui;

private slots:
    void slotReadData();
    void slotSendData();
    void slotConnection();
};

#endif // WIDGET_H
