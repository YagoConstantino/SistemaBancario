#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "menuprincipal.h"
#include "cadastro.h"

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

private slots:
    void Menu_Principal();
    void AbrirCadastro();
    void mostrarSenha(bool checked);

private:
    Ui::MainWindow *ui;
    MenuPrincipal *MenuPrin;
    Cadastro *cad;
};
#endif // MAINWINDOW_H
