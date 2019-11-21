#include "SysInfoWidget.h"

#include <QVBoxLayout>

SysInfoWidget::SysInfoWidget(QWidget *parent, int startDelayMs, int updateSeriesDelayMs) :
    QWidget(parent),
    mChartView(this)
{
    // Initialization for QTimer.
    mRefreshTimer.setInterval(updateSeriesDelayMs);
    connect(&mRefreshTimer, &QTimer::timeout, this, &SysInfoWidget::updateSeries);
    mRefreshTimer.start(startDelayMs);

    mChartView.setRenderHint(QPainter::Antialiasing);
    mChartView.chart()->legend()->setVisible(false);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(&mChartView);
    setLayout(layout);
}

QtCharts::QChartView& SysInfoWidget::chartView()
{
    return mChartView;
}
