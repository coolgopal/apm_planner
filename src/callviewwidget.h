#ifndef CALLVIEWWIDGET_H
#define CALLVIEWWIDGET_H

#include <QWidget>

namespace Ui {
class CallViewWidget;
}

class CallViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CallViewWidget(QWidget *parent = 0);
    ~CallViewWidget();

private:
    Ui::CallViewWidget *ui;
};

#endif // CALLVIEWWIDGET_H
