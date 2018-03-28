#ifndef BOOK_H
#define BOOK_H

#include "mainwindow.h"
#include "db.h"

#include <QDialog>
#include <QStringList>
#include <QWidget>

namespace Ui {
class Book;
}

class Book : public QDialog
{
    Q_OBJECT

public:
    explicit Book(QWidget *parent = 0);
    QStringList pull_out_data(Ui::Book* ui) const;
    bool has_empty_field(const QStringList& data_list) const;
    bool bind_data(const QStringList& data_list);
    void reset_fields(Ui::Book* ui);
    ~Book();

private slots:
    void on_btn_add_book_clicked();
    void on_btn_back_clicked();

private:
    Ui::Book *ui;
};

#endif // BOOK_H
