    #ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "menuprincipal.h"
#include "cadastro.h"
#include "esqueceusenha.h"

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
    void AbrirEsqueceuSenha();
    void mostrarSenha(bool checked);

private:
    Ui::MainWindow *ui;
    MenuPrincipal *_MenuPrin;
    Cadastro *_cad;
    EsqueceuSenha *_Esq;
};
#endif // MAINWINDOW_H
