#include "MyWidget.h"
#include "ui_MyWidget.h"

#include <QTime>

#include "MyStringListModel.h"

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget),
    data()
{
    ui->setupUi(this);
    auto pModel = new MyStringListModel(this);
    ui->listView->setModel(pModel);

    connect(ui->lineEdit, &QLineEdit::textChanged,
            pModel, &MyStringListModel::setPattern);
}

MyWidget::~MyWidget()
{
    delete ui;
}
