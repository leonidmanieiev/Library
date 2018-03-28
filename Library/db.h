#ifndef DB_H
#define DB_H

#include "logging.h"

#include <QtSql>
#include <QStringList>

class DB
{
public:
    bool open_connection(const QString& db_path);
    void close_connection();
    void ask_log_check() const;
private:
    QSqlDatabase db;
};

#endif // DB_H
