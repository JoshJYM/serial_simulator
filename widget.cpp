#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QSerialPortInfo>
#include <QSerialPort>



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);


    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        QStringList list;
        qDebug() << info.portName();
    }


    m_serial = new QSerialPort();
    connect(ui->pushButton,SIGNAL(released()),this,SLOT(slotConnection()));

}

Widget::~Widget()
{
    delete ui;
}


void Widget::slotReadData()
{
    const QByteArray data = m_serial->readAll();
    qDebug()<<data;
}

void Widget::slotSendData()
{
    m_serial->write(ui->lineEdit->text().toUtf8().constData(),20);
}

void Widget::slotConnection()
{
    m_serial->setPortName("tty.usbmodem1411");
    m_serial->setBaudRate(QSerialPort::Baud9600);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);
    if (m_serial->open(QIODevice::ReadWrite)) {
        connect(m_serial,SIGNAL(readyRead()),this,SLOT(slotReadData()));

    } else {
        qDebug()<<"FUCK";
    }


    connect(ui->pushButton_2,SIGNAL(released()),this,SLOT(slotSendData()));
}
