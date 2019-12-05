#ifndef MYSTRINGLISTMODEL_H
#define MYSTRINGLISTMODEL_H

#include <QAbstractListModel>
#include <QAbstractItemModel>
#include <QFutureWatcher>

class MyStringListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit MyStringListModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public:
    bool canFetchMore(const QModelIndex& parent) const override;
    void fetchMore(const QModelIndex& parent) override;

    void setPattern(const QString& pat);

public slots:
    void resetIndex();

private:
    void filterData(const QStringList& data, const QString& pattern);
    void cancel();

    int m_RequestedNum;
    // The index data. This is the model data.
    QList<int> m_IndexList;

    // This is the actual data.
    QStringList m_Data;
    QString m_Pat;

    QMutex mutex;
    QFutureWatcher<QList<int>> futureWatcher;
};

#endif // MYSTRINGLISTMODEL_H
