#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include <QDialog>

namespace Ui { class MenuPrincipal; }
class MainWindow;

class MenuPrincipal : public QDialog
{
    Q_OBJECT

public:
    explicit MenuPrincipal(QWidget *parent = nullptr);
    ~MenuPrincipal();

private slots:
    void voltarLogin();

//Funções
private:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::MenuPrincipal *ui;
    MainWindow *Login;

};

#endif // MENUPRINCIPAL_H
