#include "edit.h"
#include "ui_edit.h"

Edit::Edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Edit), saved(true)
{
    ui->setupUi(this);
    const int wid = 900, hei = 270;
    this->setFixedSize(wid, hei);

    if(!this->show_library())
        QMessageBox::warning(this, "Error", "An error occurred. For more information check log.");
}

bool Edit::show_library()
{
    DB lib_db;
    const quint8 column_cnt = 6;

    if(!lib_db.open_connection("d:/Qt_projects/Library/library.db"))
        return false;

    QSqlQuery qry;

    if(!qry.prepare("SELECT author, title, ISBN, publication_year, "
                    "print_length, about_book FROM Books;"))
    {
        write_log(QString(": show_library()::").append(qry.lastError().text()));
        return false;
    }

    if(!qry.exec())
    {
        write_log(QString(": show_library()::").append(qry.lastError().text()));
        return false;
    }

    ui->table_widget->setColumnCount(column_cnt);
    ui->table_widget->setColumnWidth(0, 185);
    ui->table_widget->setColumnWidth(1, 185);
    ui->table_widget->setColumnWidth(2, 90);
    ui->table_widget->setColumnWidth(3, 100);
    ui->table_widget->setColumnWidth(4, 75);
    ui->table_widget->setColumnWidth(5, 200);
    ui->table_widget->setHorizontalHeaderLabels(QStringList() << "author" << "title" << "ISBN" <<
                                                "publication_year" << "print_length" << "about_book");
    while(qry.next())
    {
        quint32 row_cnt = ui->table_widget->rowCount();
        ui->table_widget->insertRow(row_cnt);

        for(quint8 i = 0; i < column_cnt; ++i)
            ui->table_widget->setItem(row_cnt, i, new QTableWidgetItem(qry.value(i).toString()));
    }

    lib_db.close_connection();
    this->cells.clear();
    this->saved = true;

    return true;
}

bool Edit::save_changes()
{
    DB lib_db;

    if(!lib_db.open_connection("d:/Qt_projects/Library/library.db"))
        return false;

    QSqlQuery qry;

    foreach(const auto& cell, cells)
    {
        QString column_title = ui->table_widget->horizontalHeaderItem(cell->column())->text();

        if(!qry.prepare("UPDATE Books SET "+column_title+" = '"+cell->text()+
                        "' WHERE book_id = "+QString::number(cell->row()+1)+";"))
        {
            write_log(QString(": save_changes()::").append(qry.lastError().text()));
            return false;
        }

        if(!qry.exec())
        {
            write_log(QString(": save_changes()::").append(qry.lastError().text()));
            return false;
        }
    }

    lib_db.close_connection();
    this->saved = true;

    return true;
}

Edit::~Edit()
{
    delete ui;
}

void Edit::on_btn_back_clicked()
{
    if(!this->saved)
    {
        QMessageBox reply(QMessageBox::NoIcon, "Save",
                          "Would you like to save changes?");
        reply.setWindowIcon(QIcon(":/Files/Resources/Icons/library_icon.ico"));
        reply.addButton(QMessageBox::Yes);
        reply.addButton(QMessageBox::No);

        if(reply.exec() == QMessageBox::Yes)
        {
            if(!save_changes())
                QMessageBox::warning(this, "Error", "An error occurred. For more information check log.");
            else QMessageBox::information(this, "Status", "The changes have been saved");
        }
    }

    this->close();
    //Mainwindow* w = new Mainwindow;
    //w->show();
}

void Edit::on_btn_save_clicked()
{
    if(!this->saved)
    {
        if(!save_changes())
            QMessageBox::warning(this, "Error", "An error occurred. For more information check log.");
        else QMessageBox::information(this, "Status", "The changes have been saved");
    }
}

void Edit::on_table_widget_itemChanged(QTableWidgetItem *item)
{
    this->saved = false;
    this->cells.push_back(item);
}
