#ifndef DRIVER_H
#define DRIVER_H

#include <QMainWindow>

namespace Ui {
class Driver;
}

class Driver : public QMainWindow
{
    Q_OBJECT

public:
    explicit Driver(QWidget *parent = 0);
    ~Driver();

private:
    Ui::Driver *ui;
};

#endif // DRIVER_H
