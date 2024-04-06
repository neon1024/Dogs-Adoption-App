#include "DogsModel.h"

DogsModel::DogsModel(Repository &repository): repository{repository} {
}

int DogsModel::rowCount(const QModelIndex &index) const {
    return this->repository.get_size();
}

int DogsModel::columnCount(const QModelIndex &index) const {
    return 5;  // breed, name, age, photograph, id
}

QVariant DogsModel::headerData(int section, Qt::Orientation orientation, int role) const {
    switch(role) {
        case Qt::DisplayRole: {
            switch(orientation) {
                case Qt::Horizontal: {
                    switch(section) {
                        case 0:
                            return QString("breed");

                        case 1:
                            return QString("name");

                        case 2:
                            return QString("age");

                        case 3:
                            return QString("photograph");

                        case 4:
                            return QString("id");

                        default:
                            break;
                    }
                }

                case Qt::Vertical: {
                    return QString::number(section + 1);
                }

                default:
                    break;
            }
        }

        default:
            break;
    }

    return QVariant{};
}

QVariant DogsModel::data(const QModelIndex &index, int role) const {
    int column = index.column();
    int row = index.row();
    const auto& dog = this->repository.get_data()[row];

    switch(role) {
        case Qt::DisplayRole: case Qt::EditRole: {
            switch(column) {
                // breed
                case 0:
                    return QString::fromStdString(dog.get_breed());

                // name
                case 1:
                    return QString::fromStdString(dog.get_name());

                // age
                case 2:
                    return QString::number(dog.get_age());

                // photograph
                case 3:
                    return QString::fromStdString(dog.get_photograph());

                // id
                case 4:
                    return QString::fromStdString(dog.get_id());

                default:
                    break;
            }
        }

        default:
            break;
    }

    return QVariant{};
}

bool DogsModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (role != Qt::EditRole) {
        return false;
    }

    int row = index.row();
    int column = index.column();

    auto& dog = this->repository.get_data()[row];

    switch(column) {
        case 0: {
            std::string breed = value.toString().toStdString();
            dog.set_breed(breed);
            break;
        }

        case 1: {
            std::string name = value.toString().toStdString();
            dog.set_name(name);
            break;
        }

        case 2: {
            int age = value.toInt();
            dog.set_age(age);
            break;
        }

        case 3: {
            std::string photograph = value.toString().toStdString();
            dog.set_photograph(photograph);
            break;
        }

        default:
            break;
    }

    emit dataChanged(index, index);
    emit data_changed_signal();

    return false;
}

Qt::ItemFlags DogsModel::flags(const QModelIndex &index) const {
    int column = index.column();

    // don't allow id editing
    if(column == 4) {
        return Qt::ItemFlags{};
    }

    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}
