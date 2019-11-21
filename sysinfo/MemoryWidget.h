#ifndef MEMORYWIDGET_H
#define MEMORYWIDGET_H

#include "SysInfoWidget.h"

namespace QtCharts {
class QLineSeries;
}

class MemoryWidget : public SysInfoWidget
{
    Q_OBJECT

public:
    explicit MemoryWidget(QWidget *parent = nullptr);

protected slots:
    void updateSeries() override;

private:
    QtCharts::QLineSeries *mSeries;
    qint64 mPointPositionX;
};

#endif // MEMORYWIDGET_H
