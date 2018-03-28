#include "logging.h"

void write_log(const QString& log)
{
    QDir log_dir;

    if(!log_dir.exists("Log/"))
        log_dir.mkdir("Log/");

    QFile log_file("Log/log.txt");

    if(!log_file.open(QFile::WriteOnly | QFile::Text | QFile::Append))
    {
        QMessageBox warn(QMessageBox::NoIcon, "Error", "Failed to open log file", QMessageBox::Ok);
        warn.setWindowIcon(QIcon(":/Files/Resources/Icons/library_icon.ico"));
        warn.exec();

        return;
    }

    QTextStream ts_log(&log_file);
    ts_log << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")
           << log << '\n';

    log_file.flush();
    log_file.close();
}
