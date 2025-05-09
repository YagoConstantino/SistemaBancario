#ifndef CONFIRMARSENHA_H
#define CONFIRMARSENHA_H

#include <QDialog>

namespace Ui {
class ConfirmarSenha;
}

class ConfirmarSenha : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmarSenha(QWidget *parent = nullptr);
    ~ConfirmarSenha();

private:
    Ui::ConfirmarSenha *ui;

private slots:
    void senhaOk();
    void mostrarSenha(bool checked);
};

#endif // CONFIRMARSENHA_H
