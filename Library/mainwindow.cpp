#include "mainwindow.h"
#include "ui_mainwindow.h"

Mainwindow::Mainwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Mainwindow)
{
    ui->setupUi(this);
    const int wid = 250, hei = 129;
    this->setFixedSize(wid, hei);
}

Mainwindow::~Mainwindow()
{
    delete ui;
}

void Mainwindow::on_action_exit_triggered()
{
    this->close();
}

void Mainwindow::on_action_about_triggered()
{
    QString about_text, about_text_path = ":/Files/Resources/Text/about.txt";

    try
    {
        about_text = get_text_from_file(about_text_path);
    }
    catch(const std::invalid_argument& ia)
    {
        QMessageBox::warning(this, "Error", "An error occurred. For more information check log.");
        write_log(QString(": on_action_about_triggered()::")+ia.what());
        return;
    }

    QMessageBox about_box(QMessageBox::NoIcon, "About Library", about_text, QMessageBox::Close, this);
    about_box.exec();
}

void Mainwindow::on_action_add_book_triggered()
{
    //this->close();
    Book book;
    book.setWindowFlags(book.windowFlags() &
                        ~Qt::WindowContextHelpButtonHint);
    book.exec();
}

void Mainwindow::on_action_show_library_triggered()
{
    //this->close();
    Library lib;
    lib.setWindowFlags(lib.windowFlags() &
                       ~Qt::WindowContextHelpButtonHint);
    lib.exec();
}

void Mainwindow::on_action_search_triggered()
{
    //this->close();
    Book_search b_serch;
    b_serch.setWindowFlags(b_serch.windowFlags() &
                           ~Qt::WindowContextHelpButtonHint);
    b_serch.exec();
}

void Mainwindow::on_action_edit_triggered()
{
    Login login;
    login.setWindowFlags(login.windowFlags() &
                         ~Qt::WindowContextHelpButtonHint);
    if(!login.exec())
        return;

    if(!login.get_logged_in())
    {
        QMessageBox::warning(this, "Error", "Permission denied");
        return;
    }

    //this->close();
    Edit edit;
    edit.setWindowFlags(edit.windowFlags() &
                        ~Qt::WindowContextHelpButtonHint);
    edit.exec();
}
