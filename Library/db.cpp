#include "db.h"

bool DB::open_connection(const QString& db_path)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(db_path);

    if(!db.open())
    {
        write_log(": open_connection()::Faild to open database connection");
        return false;
    }

    return true;
}

void DB::close_connection()
{
    db.close();
    db.removeDatabase(QSqlDatabase::defaultConnection);
}

void DB::ask_log_check() const
{
    QMessageBox warn(QMessageBox::NoIcon, "Error", "An error occurred. For more information check log.",
                     QMessageBox::Ok);
    warn.setWindowIcon(QIcon(":/Files/Resources/Icons/library_icon.ico"));
    warn.exec();
}
