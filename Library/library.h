#ifndef LIBRARY_H
#define LIBRARY_H

#include "mainwindow.h"
#include "db.h"

#include <QDialog>

namespace Ui {
class Library;
}

class Library : public QDialog
{
    Q_OBJECT

public:
    explicit Library(QWidget *parent = 0);
    bool show_library(const QString& sql_qry);
    QString get_sort_by() const;
    QString get_defalut_sql_qry() const;
    ~Library();

private slots:
    void on_btn_back_clicked();
    void on_btn_sort_clicked();

    void on_table_view_pressed(const QModelIndex &index);

private:
    Ui::Library *ui;
};

#endif // LIBRARY_H
