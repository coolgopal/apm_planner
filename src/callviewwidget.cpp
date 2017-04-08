#include "callviewwidget.h"
#include "ui_callviewwidget.h"

CallViewWidget::CallViewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CallViewWidget)
{
    ui->setupUi(this);
}

CallViewWidget::~CallViewWidget()
{
    delete ui;
}
