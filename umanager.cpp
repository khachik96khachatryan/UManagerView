#include "umanager.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
UManager::UManager(QWidget *parent) : QWidget(parent)
{

    m_model = new TableModel(1,1,this);

    m_table = new QTableView(this);
    m_lineFind = new QLineEdit(this);
    m_btnFind = new QPushButton("Find",this);
    m_btnOpen = new QPushButton("Open",this);

    QHBoxLayout *hLay = new QHBoxLayout();
    hLay->addWidget(m_lineFind);
    hLay->addWidget(m_btnFind);
    hLay->addWidget(m_btnOpen);
    setLayout(new QVBoxLayout);
    layout()->addWidget(m_table);
    layout()->addItem(hLay);
    m_table->setModel(m_model);
    m_table->setMinimumHeight(700);
    m_table->setMinimumWidth(500);
    connect(m_btnFind,SIGNAL(clicked(bool)),this,SLOT(findValueFromTable()));
    connect(m_btnOpen,SIGNAL(clicked(bool)),this,SLOT(openJsonFile()));

}

void UManager::findValueFromTable()
{
    QString find_Value = m_lineFind->text();
}

void UManager::openJsonFile()
{
    QString FileDir = QFileDialog::getOpenFileName(this,"Open Json File",QString(),"*json");
           if(FileDir.isEmpty()){ // Try Catch
               return;
        }
    m_model->setFileDir(FileDir);
}
