#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QVBoxLayout>

#include "MyWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto* pLayout = new QVBoxLayout(this);
    ui->centralwidget->setLayout(pLayout);
    pLayout->addWidget(new MyWidget(this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

