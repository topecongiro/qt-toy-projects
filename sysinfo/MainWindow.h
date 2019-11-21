#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class CpuWidget;
class MemoryWidget;

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
    CpuWidget *mCpuWidget;
    MemoryWidget *mMemoryWidget;
};
#endif // MAINWINDOW_H
