#include <QTableView>

class DogsTableView: public QTableView {
private:
    QAbstractItemModel* model;

public:
    explicit DogsTableView(QAbstractItemModel* model, QWidget* parent = Q_NULLPTR);
};
