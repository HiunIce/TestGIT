#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTimer"
#include "QPainter"
#include "MedicalRecordMaker.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_recorder = std::make_shared<MedicalRecordMaker>();
    m_recorder->print();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QImage&& img = m_recorder->getPaper();
    this->resize(img.size());
    QPainter p(this);
    p.drawImage(QRect(QPoint(0,0), img.size()), img);
}
