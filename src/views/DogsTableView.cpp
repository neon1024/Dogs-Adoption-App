#include "DogsTableView.h"

DogsTableView::DogsTableView(QAbstractItemModel* model, QWidget* parent): model{model}, QTableView{parent} {
    setModel(this->model);
}
