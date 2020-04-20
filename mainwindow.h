#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "memory"
namespace Ui {
class MainWindow;
}

class MedicalRecordMaker;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void paintEvent(QPaintEvent *event);
private:
    std::shared_ptr<MedicalRecordMaker> m_recorder;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
