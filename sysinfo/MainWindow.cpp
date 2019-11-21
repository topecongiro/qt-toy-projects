#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QHBoxLayout>

#include "CpuWidget.h"
#include "MemoryWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mCpuWidget(new CpuWidget(this))
    , mMemoryWidget(new MemoryWidget(this))
{
    ui->setupUi(this);
    ui->centralwidget->setLayout(new QHBoxLayout());
    ui->centralwidget->layout()->addWidget(mCpuWidget);
    ui->centralwidget->layout()->addWidget(mMemoryWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

