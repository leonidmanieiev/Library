#ifndef BOOK_SEARCH_H
#define BOOK_SEARCH_H

#include "db.h"
#include "mainwindow.h"

#include <QDialog>

namespace Ui {
class Book_search;
}

class Book_search : public QDialog
{
    Q_OBJECT

public:
    explicit Book_search(QWidget *parent = 0);
    QString get_search_by() const;
    QString create_sql_qry() const;
    bool show_search_result();
    ~Book_search();

private slots:
    void on_btn_back_clicked();
    void on_btn_search_clicked();

private:
    Ui::Book_search *ui;
};

#endif // BOOK_SEARCH_H
