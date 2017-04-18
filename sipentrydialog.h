#ifndef SIPENTRYDIALOG_H
#define SIPENTRYDIALOG_H

#include <QDialog>

namespace Ui {
class SIPEntryDialog;
}

class SIPEntryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SIPEntryDialog(QWidget *parent = 0);
    ~SIPEntryDialog();

signals:
    void sip_id_update(const char* sip_id);

private slots:
    void on_buttonBox_accepted();

    void on_pushButton_ok_clicked();

private:
    Ui::SIPEntryDialog *ui;
};

#endif // SIPENTRYDIALOG_H
