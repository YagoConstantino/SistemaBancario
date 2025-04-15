#ifndef FAZERSAQUE_H
#define FAZERSAQUE_H

#include <QDialog>

namespace Ui {
class FazerSaque;
}

class MenuPrincipal;
class FazerSaque : public QDialog
{
    Q_OBJECT

public:
    explicit FazerSaque(QWidget *parent = nullptr);
    ~FazerSaque();

private:
    Ui::FazerSaque *ui;
    MenuPrincipal *MenuPrin;

private slots:
    void voltarMenu();

//Funções
private:
    void closeEvent(QCloseEvent *event) override;
};

#endif // FAZERSAQUE_H
