#include "MemoryWidget.h"

#include <QtCharts/QLineSeries>
#include <QtCharts/QAreaSeries>
#include <QLinearGradient>
#include <QPen>

#include "SysInfo.h"

using namespace QtCharts;

constexpr const int CHART_X_RANGE_COUNT = 50;
constexpr const int CHART_X_RANGE_MAX   = CHART_X_RANGE_COUNT - 1;
constexpr const int COLOR_DARK_BLUE     = 0x209fdf;
constexpr const int COLOR_LIGHT_BLUE    = 0xbfdfef;
constexpr const int PEN_WIDTH = 3;

MemoryWidget::MemoryWidget(QWidget *parent) :
    SysInfoWidget(parent),
    mSeries(new QLineSeries(this)),
    mPointPositionX(0)
{
    QPen pen(COLOR_DARK_BLUE);
    pen.setWidth(PEN_WIDTH);

    QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
    gradient.setColorAt(1.0, COLOR_DARK_BLUE);
    gradient.setColorAt(0.0, COLOR_LIGHT_BLUE);
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);

    QAreaSeries *areaSeries = new QAreaSeries(mSeries);
    areaSeries->setPen(pen);
    areaSeries->setBrush(gradient);

    QChart *chart = chartView().chart();
    chart->addSeries(areaSeries);
    chart->setTitle("Memory used");

    // Create axes based on the series type. In this case, the type is
    // area series so X-axis and Y-axis will be created.
    chart->createDefaultAxes();

    const auto axisX = chart->axes(Qt::Horizontal).back();
    axisX->setVisible(false);
    axisX->setRange(0, CHART_X_RANGE_MAX);

    const auto axisY = chart->axes(Qt::Vertical).back();
    axisY->setRange(0, 100);
}

void MemoryWidget::updateSeries()
{
    const double memoryUsed = SysInfo::instance().memoryUsed();
    mSeries->append(mPointPositionX++, memoryUsed);
    if (mSeries->count() > CHART_X_RANGE_COUNT) {
        QChart *chart = chartView().chart();
        chart->scroll(chart->plotArea().width() / CHART_X_RANGE_MAX, 0);
        mSeries->remove(0);
    }
}
