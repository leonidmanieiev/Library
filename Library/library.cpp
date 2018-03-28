#include "library.h"
#include "ui_library.h"
#include <QDesktopWidget>

Library::Library(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Library)
{
    ui->setupUi(this);
    const int wid = 900, hei = 305;
    this->setFixedSize(wid, hei);

    if(!this->show_library(get_defalut_sql_qry()))
        QMessageBox::warning(this, "Error", "An error occurred. "
                                            "For more information check log.");

    ui->combo_box_sort->addItem("Author");
    ui->combo_box_sort->addItem("Title");
    ui->combo_box_sort->addItem("ISBN");
    ui->combo_box_sort->addItem("Publication year");
    ui->combo_box_sort->addItem("Print length");
    ui->combo_box_sort->addItem("Content");

    ui->combo_box_order->addItem("ASC");
    ui->combo_box_order->addItem("DESC");
}

bool Library::show_library(const QString& sql_qry)
{
    DB lib_db;

    if(!lib_db.open_connection("d:/Qt_projects/Library/library.db"))
        return false;

    QSqlQueryModel* model = new QSqlQueryModel;
    QSqlQuery qry;

    if(!qry.prepare(sql_qry))
    {
        write_log(QString(": show_library()::").append(qry.lastError().text()));
        return false;
    }

    if(!qry.exec())
    {
        write_log(QString(": show_library()::").append(qry.lastError().text()));
        return false;
    }

    model->setQuery(qry);
    model->setHeaderData(0, Qt::Horizontal, "Author");
    model->setHeaderData(1, Qt::Horizontal, "Title");
    model->setHeaderData(2, Qt::Horizontal, "ISBN");
    model->setHeaderData(3, Qt::Horizontal, "Publication year");
    model->setHeaderData(4, Qt::Horizontal, "Print length");
    model->setHeaderData(5, Qt::Horizontal, "Content");
    ui->table_view->setModel(model);
    ui->table_view->setColumnWidth(0, 185);
    ui->table_view->setColumnWidth(1, 185);
    ui->table_view->setColumnWidth(2, 90);
    ui->table_view->setColumnWidth(3, 100);
    ui->table_view->setColumnWidth(4, 75);
    ui->table_view->setColumnWidth(5, 200);

    lib_db.close_connection();
    return true;
}

Library::~Library()
{
    delete ui;
}

QString Library::get_sort_by() const
{
    QString sort_by(ui->combo_box_sort->currentText());

    if(!sort_by.compare("Publication year"))
        sort_by = "publication_year";
    else if(!sort_by.compare("Print length"))
        sort_by = "print_length";
    else if(!sort_by.compare("Content"))
        sort_by = "about_book";

    return sort_by;
}

QString Library::get_defalut_sql_qry() const
{
    return "SELECT author, title, ISBN, publication_year, "
           "print_length, about_book FROM Books ORDER BY author ASC;";
}

void Library::on_btn_back_clicked()
{
    this->close();
    //Mainwindow* w = new Mainwindow;
    //w->show();
}

void Library::on_btn_sort_clicked()
{
    QString sql_qry("SELECT author, title, ISBN, publication_year, "
                    "print_length, about_book FROM Books ORDER BY ");
    sql_qry.append(get_sort_by()).append(" ");
    sql_qry.append(ui->combo_box_order->currentText()).append(";");

    if(!this->show_library(sql_qry))
        QMessageBox::warning(this, "Error", "An error occurred. "
                                            "For more information check log.");
}

void Library::on_table_view_pressed(const QModelIndex &index)
{
    const quint8 about_book_column = 5;
    if(index.column() == about_book_column)
    {
        QMessageBox about_book(QMessageBox::NoIcon, "Book content",
                               index.data().toString(), QMessageBox::Close);
        about_book.setWindowIcon(QIcon(":/Files/Resources/Icons/library_icon.ico"));
        about_book.exec();
    }
}
