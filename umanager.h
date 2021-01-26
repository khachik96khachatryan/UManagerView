#ifndef UMANAGER_H
#define UMANAGER_H

#include <QWidget>
#include <QtGui>
#include "intlistmodel.h"
#include "tablemodel.h"
#include <QTableView>
#include <QPushButton>
#include <QLineEdit>

class UManager : public QWidget
{
    Q_OBJECT

    QLineEdit   *m_lineFind;
    QPushButton *m_btnFind;
    QPushButton *m_btnOpen;
    QTableView  *m_table;

    TableModel  *m_model;

public:
    explicit UManager(QWidget *parent = nullptr);

public slots:
    void findValueFromTable();
    void openJsonFile();

signals:


};

#endif // UMANAGER_H
