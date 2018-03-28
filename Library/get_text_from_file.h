#ifndef GET_TEXT_FROM_FILE_H
#define GET_TEXT_FROM_FILE_H

#include "logging.h"

#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QIcon>

QString get_text_from_file(const QString& path);

#endif // GET_TEXT_FROM_FILE_H
