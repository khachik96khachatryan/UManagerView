#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QTableView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QAbstractItemModel>
#include <QShortcut>
#include "userstablemodel.h"
class Widget : public QWidget
{
    Q_OBJECT

    QLineEdit   *m_lineFind;
    QPushButton *m_btnFind;
    QPushButton *m_btnOpen;
    QTableView  *m_table;

    UsersTableModel *m_model;

    void modelView(QWidget *parent);
public:
    Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void openJsonFile();
    void findValueFromTable();
};

#endif // WIDGET_H
