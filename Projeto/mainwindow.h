#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSql>
#include <QSqlDatabase>
#include <QDebug>
#include <QFileInfo>
#include <QSqlError>
#include "menuprincipal.h"
#include "cadastro.h"
#include "esqueceusenha.h"
#include "conta.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool recuperarDadosConta();
    bool verificarDadosConta(QString login,QString senha);
    Conta* getConta();

private slots:
    void Menu_Principal();
    void AbrirCadastro();
    void AbrirEsqueceuSenha();
    void mostrarSenha(bool checked);
    bool verificaContaExiste();
    bool recuperaDadosBanco();

private:
    Ui::MainWindow *ui;
    MenuPrincipal *_MenuPrin;
    Cadastro *_cad;
    EsqueceuSenha *_Esq;
    QString _CPFlogin;
    QString _SenhaLogin;

    Conta contaAtual;
};
#endif // MAINWINDOW_H
