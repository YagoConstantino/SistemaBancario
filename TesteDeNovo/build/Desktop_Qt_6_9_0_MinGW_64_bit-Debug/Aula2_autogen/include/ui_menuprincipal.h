/********************************************************************************
** Form generated from reading UI file 'menuprincipal.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENUPRINCIPAL_H
#define UI_MENUPRINCIPAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MenuPrincipal
{
public:
    QLabel *label;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *Deposito;
    QPushButton *Saque;
    QPushButton *Transferencia;
    QPushButton *VerSaldo;
    QPushButton *VerFatura;
    QPushButton *VerExtrato;
    QPushButton *Sair;

    void setupUi(QDialog *MenuPrincipal)
    {
        if (MenuPrincipal->objectName().isEmpty())
            MenuPrincipal->setObjectName("MenuPrincipal");
        MenuPrincipal->resize(799, 441);
        label = new QLabel(MenuPrincipal);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 0, 91, 16));
        widget = new QWidget(MenuPrincipal);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(300, 100, 120, 206));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        Deposito = new QPushButton(widget);
        Deposito->setObjectName("Deposito");

        verticalLayout->addWidget(Deposito);

        Saque = new QPushButton(widget);
        Saque->setObjectName("Saque");

        verticalLayout->addWidget(Saque);

        Transferencia = new QPushButton(widget);
        Transferencia->setObjectName("Transferencia");

        verticalLayout->addWidget(Transferencia);

        VerSaldo = new QPushButton(widget);
        VerSaldo->setObjectName("VerSaldo");

        verticalLayout->addWidget(VerSaldo);

        VerFatura = new QPushButton(widget);
        VerFatura->setObjectName("VerFatura");

        verticalLayout->addWidget(VerFatura);

        VerExtrato = new QPushButton(widget);
        VerExtrato->setObjectName("VerExtrato");

        verticalLayout->addWidget(VerExtrato);

        Sair = new QPushButton(widget);
        Sair->setObjectName("Sair");

        verticalLayout->addWidget(Sair);

        QWidget::setTabOrder(Deposito, Saque);
        QWidget::setTabOrder(Saque, Transferencia);
        QWidget::setTabOrder(Transferencia, VerSaldo);
        QWidget::setTabOrder(VerSaldo, VerFatura);
        QWidget::setTabOrder(VerFatura, VerExtrato);

        retranslateUi(MenuPrincipal);

        QMetaObject::connectSlotsByName(MenuPrincipal);
    } // setupUi

    void retranslateUi(QDialog *MenuPrincipal)
    {
        MenuPrincipal->setWindowTitle(QCoreApplication::translate("MenuPrincipal", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("MenuPrincipal", "Menu Principal", nullptr));
        Deposito->setText(QCoreApplication::translate("MenuPrincipal", "Fazer Dep\303\263sito", nullptr));
        Saque->setText(QCoreApplication::translate("MenuPrincipal", "Fazer Saque", nullptr));
        Transferencia->setText(QCoreApplication::translate("MenuPrincipal", "Fazer Transfer\303\252ncia", nullptr));
        VerSaldo->setText(QCoreApplication::translate("MenuPrincipal", "Ver Saldo", nullptr));
        VerFatura->setText(QCoreApplication::translate("MenuPrincipal", "Ver Fatura de Cr\303\251dito", nullptr));
        VerExtrato->setText(QCoreApplication::translate("MenuPrincipal", "Ver Extrato", nullptr));
        Sair->setText(QCoreApplication::translate("MenuPrincipal", "Sair", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MenuPrincipal: public Ui_MenuPrincipal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUPRINCIPAL_H
