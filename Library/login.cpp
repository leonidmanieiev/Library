#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent), ui(new Ui::Login),
    logged_in(false)
{
    ui->setupUi(this);
    const int wid = 185, hei = 105;
    this->setFixedSize(wid, hei);
}

Login::~Login()
{
    delete ui;
}

bool Login::check_user(const QString &username, const QString &password)
{
    QSqlQuery qry;

    if(qry.exec("SELECT * FROM Users WHERE username='"
                +username+"' AND password='"+password+"';"))
    {
        return qry.next();
    }

    write_log(QString(": check_user()::").append(qry.lastError().text()));
    QMessageBox::warning(this, "Error", "An error occurred. For more information check log.");
    return false;
}

bool Login::log_in()
{
    DB log_db;
    QString username(ui->line_edit_username->text());
    QString password(ui->line_edit_password->text());

    if(!log_db.open_connection("d:/Qt_projects/Library/user.db"))
    {
        log_db.ask_log_check();
        return false;
    }

    bool res_of_log_in(check_user(username, password));
    log_db.close_connection();

    return res_of_log_in;
}

bool Login::get_logged_in() const
{
    return logged_in;
}

void Login::on_btn_login_clicked()
{
    logged_in = log_in();
    this->accept();
}
