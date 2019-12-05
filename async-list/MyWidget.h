#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

private:
    Ui::MyWidget *ui;
    QList<int> data;
};

#endif // MYWIDGET_H
