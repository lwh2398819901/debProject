#ifndef ADDAPKS_H
#define ADDAPKS_H

#include <QWidget>

namespace Ui {
class AddApks;
}

class AddApks : public QWidget
{
    Q_OBJECT

public:
    explicit AddApks(QWidget *parent = nullptr);
    ~AddApks();

private:
    Ui::AddApks *ui;
};

#endif // ADDAPKS_H
