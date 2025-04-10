#ifndef ESQUECEUSENHA_H
#define ESQUECEUSENHA_H

#include <QDialog>
#include <QString>
#include <QMessageBox>

namespace Ui {
class EsqueceuSenha;
}

class MainWindow;

class EsqueceuSenha : public QDialog
{
    Q_OBJECT

public:
    explicit EsqueceuSenha(QWidget *parent = nullptr);
    ~EsqueceuSenha();


private slots:
    void ConfirmarTrocaDeSenha();
    void VoltarLogin();
    void mostrarSenha(bool checked);

//Funções
private:
    int verificaDados();

private:
    Ui::EsqueceuSenha *ui;
    MainWindow *Login;

    QString _CPF;
    QString _NomeMae;
    QString _Senha;
    QString _ConfirmaSenha;
};

#endif // ESQUECEUSENHA_H
