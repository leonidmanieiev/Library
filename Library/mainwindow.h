#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "get_text_from_file.h"
#include "logging.h"
#include "library.h"
#include "book.h"
#include "book_search.h"
#include "login.h"
#include "edit.h"

#include <QMainWindow>
#include <QCloseEvent>

namespace Ui {
class Mainwindow;
}

class Mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit Mainwindow(QWidget *parent = 0);
    ~Mainwindow();

private slots:
    void on_action_exit_triggered();
    void on_action_about_triggered();
    void on_action_add_book_triggered();
    void on_action_show_library_triggered();
    void on_action_search_triggered();
    void on_action_edit_triggered();

private:
    Ui::Mainwindow *ui;
};

#endif // MAINWINDOW_H
