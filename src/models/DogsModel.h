#pragma once

#include <QAbstractTableModel>
#include "../repository/Repository.h"

class DogsModel: public QAbstractTableModel {
private:
    Q_OBJECT;

    Repository& repository;

public:
    explicit DogsModel(Repository& repository);

    int rowCount(const QModelIndex& index) const override;
    int columnCount(const QModelIndex& index) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    signals:
        void data_changed_signal();
};
