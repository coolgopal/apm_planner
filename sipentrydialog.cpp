#include "sipentrydialog.h"
#include "ui_sipentrydialog.h"
#include "callmanager.h"

SIPEntryDialog::SIPEntryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SIPEntryDialog)
{
    ui->setupUi(this);

    ui->lineEditSIPAddress->setText(CallManager::getInstance()->getSIPAddress());
}

SIPEntryDialog::~SIPEntryDialog()
{
    delete ui;
}

void SIPEntryDialog::on_buttonBox_accepted()
{
//    qDebug() << "SIPEntryDialog::on_buttonBox_accepted";
}

void SIPEntryDialog::on_pushButton_ok_clicked()
{

    CallManager::getInstance()->setSIPAddress(strdup(ui->lineEditSIPAddress->text().toStdString().c_str()));
    emit sip_id_update(CallManager::getInstance()->getSIPAddress());
    CallManager::getInstance()->start_sip_call();
    this->close();
}
