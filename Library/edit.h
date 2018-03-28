#ifndef EDIT_H
#define EDIT_H

#include "mainwindow.h"

#include <QDialog>
#include <QVector>
#include <QTableWidgetItem>

namespace Ui {
class Edit;
}

class Edit : public QDialog
{
    Q_OBJECT

public:
    explicit Edit(QWidget *parent = 0);
    bool show_library();
    bool save_changes();
    ~Edit();

private slots:
    void on_btn_back_clicked();
    void on_btn_save_clicked();
    void on_table_widget_itemChanged(QTableWidgetItem *item);

private:
    Ui::Edit *ui;
    bool saved;
    QVector<QTableWidgetItem*> cells;
};

#endif // EDIT_H
