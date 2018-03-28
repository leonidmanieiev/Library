#include "book.h"
#include "ui_book.h"

Book::Book(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Book)
{
    ui->setupUi(this);
    const int wid = 260, hei = 205;
    this->setFixedSize(wid, hei);
}

Book::~Book()
{
    delete ui;
}

QStringList Book::pull_out_data(Ui::Book* ui) const
{
    QStringList data_list;
    data_list << ui->line_edit_author->text() << ui->line_edit_title->text()
              << ui->line_edit_ISBN->text() << ui->line_edit_publ_year->text()
              << ui->line_edit_pr_len->text() << ui->text_edit_about_book->toPlainText();

    return data_list;
}

bool Book::has_empty_field(const QStringList& data_list) const
{
    foreach (const QString& str, data_list)
        if(str.isEmpty())
            return true;

    return false;
}

bool Book::bind_data(const QStringList& data_list)
{
    QSqlQuery qry;

    if(!qry.prepare("INSERT INTO Books (author, title, ISBN, publication_year, print_length, about_book) "
                "VALUES (:author, :title, :ISBN, :publication_year, :print_length, :about_book)"))
    {
        write_log(QString(": bind_data()::").append(qry.lastError().text()));
        return false;
    }

    qry.bindValue(":author", data_list.at(0));
    qry.bindValue(":title", data_list.at(1));
    qry.bindValue(":ISBN", data_list.at(2));
    qry.bindValue(":publication_year", data_list.at(3).toInt());
    qry.bindValue(":print_length", data_list.at(4).toInt());
    qry.bindValue(":about_book", data_list.at(5));

    if(!qry.exec())
    {
        write_log(QString(": bind_data()::").append(qry.lastError().text()));
        return false;
    }

    QMessageBox about(QMessageBox::NoIcon, "Info", "Book was successfully added", QMessageBox::Ok);
    about.setWindowIcon(QIcon(":/Files/Resources/Icons/library_icon.ico"));
    about.exec();

    return true;
}

void Book::reset_fields(Ui::Book* ui)
{
    ui->line_edit_author->setText("");
    ui->line_edit_title->setText("");
    ui->line_edit_ISBN->setText("");
    ui->line_edit_publ_year->setText("");
    ui->line_edit_pr_len->setText("");
    ui->text_edit_about_book->setText("");
}

void Book::on_btn_add_book_clicked()
{
    QStringList data_list(pull_out_data(ui));

    if(has_empty_field(data_list))
    {
        QMessageBox::warning(this, "Error", "All fields must be filled");
        return;
    }

    DB lib_db;

    if(!lib_db.open_connection("d:/Qt_projects/Library/library.db")
            || !bind_data(data_list))
    {
        lib_db.ask_log_check();
    }

    reset_fields(ui);
    lib_db.close_connection();
}

void Book::on_btn_back_clicked()
{
    this->close();
    //Mainwindow* w = new Mainwindow;
    //w->show();
}
