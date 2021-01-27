#include "widget.h"

void Widget::modelView(QWidget *parent)
{
    m_table = new QTableView(parent);
    m_table->setModel(m_model);
    m_table->show();

    m_btnFind = new QPushButton("Find",parent);
    m_btnOpen = new QPushButton("Open File",parent);
    m_lineFind = new QLineEdit(parent);

    m_table->setMinimumHeight(650);
    m_table->setMinimumWidth(440);
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_btnFind->setShortcut(Qt::Key_Return);
    m_btnOpen->setShortcut(Qt::CTRL+Qt::Key_O);
    QHBoxLayout* hLayout = new QHBoxLayout();
    hLayout->addWidget(m_lineFind);
    hLayout->addWidget(m_btnFind);
    hLayout->addWidget(m_btnOpen);
    setLayout(new QVBoxLayout());
    layout()->addWidget(m_table);
    layout()->addItem(hLayout);
}
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_model = new UsersTableModel(parent);
    modelView(this);
    connect(m_btnOpen,SIGNAL(clicked(bool)),this,SLOT(openJsonFile()));
    connect(m_btnFind,SIGNAL(clicked(bool)),this,SLOT(findValueFromTable()));
}
Widget::~Widget()
{
    delete  m_model;
}

void Widget::openJsonFile()
{
    QString FileDir = QFileDialog::getOpenFileName(this,"Open Json File",QString(),"*json");
        if(FileDir.isEmpty()){
            return;
        }
    m_model->setFileDir(FileDir);
    m_model->updateData();
}
void Widget::findValueFromTable()
{
      m_model->findValue(m_lineFind->text());
      m_model->updateTable();
}

