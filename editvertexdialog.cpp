#include "editvertexdialog.h"
#include "ui_editvertexdialog.h"

EditVertexDialog::EditVertexDialog(QWidget *parent) : QDialog(parent), ui(new Ui::EditVertexDialog)
{
    ui->setupUi(this);
}

EditVertexDialog::~EditVertexDialog()
{
    delete ui;
}

void EditVertexDialog::on_ApplyPushButton_clicked()
{
    m_pivot->AdjacencyMatrix[ui->lineEdit->text().toInt() -1][ui->lineEdit_2->text().toInt() - 1] = ui->lineEdit_3->text().toInt();
    m_pivot->AdjacencyMatrix[ui->lineEdit_2->text().toInt() -1][ui->lineEdit->text().toInt() - 1] = ui->lineEdit_4->text().toInt();

    m_widget->GetPresenter()->new_matrix();
    hide();
}

void EditVertexDialog::on_CancelPushButton_clicked()
{
    hide();
}

