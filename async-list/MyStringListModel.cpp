#include "MyStringListModel.h"

#include <QDebug>
#include <QFont>
#include <QFuture>
#include <QFutureWatcher>
#include <QMutex>
#include <QMutexLocker>
#include <QtConcurrent>
#include <QtConcurrentFilter>
#include <QTime>

#include <atomic>

static std::atomic_bool isCancelled(false);

void MyStringListModel::filterData(const QList<int>& data, const QString& pattern) {
    futureWatcher.setFuture(QtConcurrent::run([&data, pattern]() {
        QList<int> result;
        for (int i = 0; !isCancelled && i < data.size(); i++) {
            if (QString("%1").arg(data[i]).contains(pattern)) {
                result << i;
            }
        }

        qDebug() << "Finished filterData" << qPrintable(pattern);
        return isCancelled ? QList<int>() : result;
    }));
}

void MyStringListModel::cancel() {
    if (futureWatcher.isStarted() && !futureWatcher.isFinished()) {
        isCancelled = true;
        while (!futureWatcher.isFinished()) {
        }
        isCancelled = false;
    }
}

MyStringListModel::MyStringListModel(QObject *parent)
    : QAbstractListModel(parent),
      m_RequestedNum(0),
      m_IndexList(),
      m_Data(),
      m_Pat(""),
      futureWatcher(parent)
{
    auto current = QTime::currentTime().msec();
    qsrand(static_cast<uint>(current));
    for (int i = 0; i < 100000; i++) {
        m_Data.push_back(qrand());
    }

    connect(&futureWatcher, &QFutureWatcher<QList<int>>::finished,
            this, &MyStringListModel::resetIndex);
}

int MyStringListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_RequestedNum;
}

QVariant MyStringListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    const int row = index.row();
    if (row > m_IndexList.size() || row >= m_IndexList.size()) {
        return QVariant();
    }

    switch (role) {
    case Qt::DisplayRole: {
        int rowData = m_Data[m_IndexList[row]];
        const auto target = QString("%1").arg(rowData);
        if (target.contains(m_Pat)) {
            return QVariant(rowData);
        } else {
            return QVariant();
        }
    }
    case Qt::FontRole: {
        QFont font;
        font.setBold(true);
        return font;
    }
    default: {
    }
    }

    return QVariant();
}

bool MyStringListModel::canFetchMore(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return false;
    }

    return m_RequestedNum < m_IndexList.size();
}

void MyStringListModel::fetchMore(const QModelIndex &parent)
{
    if (parent.isValid()) {
        return;
    }

    int remainder = m_IndexList.size() - m_RequestedNum;
    int itemsToFetch = qMin(10, remainder);

    if (itemsToFetch <= 0) {
        return;
    }

    beginInsertRows(QModelIndex(), m_RequestedNum, m_RequestedNum + itemsToFetch - 1);
    m_RequestedNum += itemsToFetch;

    endInsertRows();
}

void MyStringListModel::setPattern(const QString &pat)
{
    QtConcurrent::run([this, pat]{
        QMutexLocker lock(&mutex);
        qDebug("setPattern: %s", qPrintable(pat));
        cancel();
        filterData(m_Data, pat);
    });
}

void MyStringListModel::resetIndex()
{
    qDebug("resetIndex");
    beginResetModel();
    m_IndexList = futureWatcher.future().result();
    m_RequestedNum = 0;
    endResetModel();
}
