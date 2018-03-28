#include "book_search.h"
#include "ui_book_search.h"

Book_search::Book_search(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Book_search)
{
    ui->setupUi(this);
    const int wid = 900, hei = 270;
    this->setFixedSize(wid, hei);

    ui->combo_box_search_by->addItem("Author");
    ui->combo_box_search_by->addItem("Title");
    ui->combo_box_search_by->addItem("ISBN");
    ui->combo_box_search_by->addItem("Publication year");
    ui->combo_box_search_by->addItem("Print length");
    ui->combo_box_search_by->addItem("Content");
}

Book_search::~Book_search()
{
    delete ui;
}

QString Book_search::get_search_by() const
{
    QString search_by(ui->combo_box_search_by->currentText());

    if(!search_by.compare("Publication year"))
        search_by = "publication_year";
    else if(!search_by.compare("Print length"))
        search_by = "print_length";
    else if(!search_by.compare("Content"))
        search_by = "about_book";

    return search_by;
}

QString Book_search::create_sql_qry() const
{
    QString search_by(get_search_by());
    QString search_text(ui->line_edit_search_text->text());
    QString sql_qry("SELECT author, title, ISBN, publication_year, "
                    "print_length, about_book FROM Books WHERE "+search_by);

    if(!search_by.compare("Author") || !search_by.compare("Title") || !search_by.compare("about_book"))
        sql_qry.append(" LIKE '%"+search_text+"%';");
    else sql_qry.append("='"+search_text+"';");

    return sql_qry;
}

bool Book_search::show_search_result()
{
    DB lib_db;

    if(!lib_db.open_connection("d:/Qt_projects/Library/library.db"))
        return false;

    QSqlQueryModel* model = new QSqlQueryModel;
    QString sql_qry(create_sql_qry());
    QSqlQuery qry;

    if(!qry.prepare(sql_qry))
    {
        write_log(QString(": show_search_result()::").append(qry.lastError().text()));
        return false;
    }

    if(!qry.exec())
    {
        write_log(QString(": show_search_result()::").append(qry.lastError().text()));
        return false;
    }

    model->setQuery(qry);
    ui->table_view_result->setModel(model);
    ui->table_view_result->setColumnWidth(0, 185);
    ui->table_view_result->setColumnWidth(1, 185);
    ui->table_view_result->setColumnWidth(2, 90);
    ui->table_view_result->setColumnWidth(3, 100);
    ui->table_view_result->setColumnWidth(4, 75);
    ui->table_view_result->setColumnWidth(5, 200);

    lib_db.close_connection();
    return true;
}

void Book_search::on_btn_back_clicked()
{
    this->close();
    //Mainwindow* w = new Mainwindow;
    //w->show();
}

void Book_search::on_btn_search_clicked()
{
    if(!show_search_result())
        QMessageBox::warning(this, "Error", "An error occurred. For more information check log.");
}
