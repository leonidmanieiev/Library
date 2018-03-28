#include "get_text_from_file.h"

QString get_text_from_file(const QString& path)
{
    QFile in_file(path);

    if(!in_file.open(QFile::ReadOnly | QFile::Text))
        throw std::invalid_argument("get_text_from_file()::invalid file");

    QTextStream ts_in(&in_file);
    QString text = ts_in.readAll();

    in_file.close();
    return text;
}
