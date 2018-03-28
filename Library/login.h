#ifndef LOGIN_H
#define LOGIN_H

#include "db.h"

#include <QDialog>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    bool check_user(const QString& username,
                    const QString& password);
    bool log_in();
    bool get_logged_in() const;
    ~Login();

private slots:
    void on_btn_login_clicked();

private:
    Ui::Login *ui;
    bool logged_in;
};

#endif // LOGIN_H
