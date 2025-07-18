#include "menuprincipal.h"
#include "ui_menuprincipal.h"
#include "mainwindow.h"  // static_cast
#include <QCloseEvent>
#include <QIcon>
#include <QLineEdit>


MenuPrincipal::MenuPrincipal(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MenuPrincipal),
    Login(nullptr),
    Dep(nullptr),
    Saq(nullptr),
    Transf(nullptr),
    FatCred(nullptr),
    VerExtra(nullptr),
    EnceCont(nullptr),
    VerSald(nullptr),
    SolicCred(nullptr)
    {

        ui->setupUi(this);
        setWindowTitle("Menu Principal");
        setAttribute(Qt::WA_DeleteOnClose);

        ui->Nomelabel->setText(getConta()->getNome());
        ui->Nomelabel->setMinimumSize(ui->Nomelabel->sizeHint());
        ui->Nomelabel->adjustSize();

        ui->CPFlabel->setText(getConta()->getCPF());
        ui->CPFlabel->setMinimumSize(ui->CPFlabel->sizeHint());
        ui->CPFlabel->adjustSize();

        ConectaBotoesFuncoes();

    }

MenuPrincipal::~MenuPrincipal()
{
    delete ui;
}

Conta *MenuPrincipal::getConta()
{
    MainWindow* login = qobject_cast<MainWindow*>(parentWidget());
    return login->getConta();
}

void MenuPrincipal::closeEvent(QCloseEvent *event)
{
    Login = qobject_cast<MainWindow*>(parentWidget());
    if (Login) {
        Login->clearTexto();
        Login->show();  // Mostra a MainWindow
    }

    event->accept();  // Aceita o fechamento
}

void MenuPrincipal::ConectaBotoesFuncoes()
{
    connect(ui->Sair,SIGNAL(clicked()),this,SLOT(voltarLogin()));
    connect(ui->Deposito,SIGNAL(clicked()),this,SLOT(JanelaDeposito()));
    connect(ui->Saque,SIGNAL(clicked()),this,SLOT(JanelaSaque()));
    connect(ui->Transferencia,SIGNAL(clicked()),this,SLOT(JanelaTransf()));
    connect(ui->VerFatura,SIGNAL(clicked()),this,SLOT(JanelaFatCred()));
    connect(ui->VerExtrato,SIGNAL(clicked()),this,SLOT(JanelaVerExtrato()));
    connect(ui->EncerraButton,SIGNAL(clicked()),this,SLOT(JanelaEncerrarConta()));
    connect(ui->VerSaldo,SIGNAL(clicked()),this,SLOT(verSaldo()));
    connect(ui->SolicitarCredito,SIGNAL(clicked()),this,SLOT(JanelaSolicitarCredito()));
}
void MenuPrincipal::voltarLogin()
{
    // Recupera o ponteiro para a MainWindow
    /*if (auto mw = qobject_cast<MainWindow*>(parentWidget())) {
        mw->show();   // Reexibe a janela principal
    }
    this->close();    // Fecha o diálogo*/
    Login = qobject_cast<MainWindow*>(parentWidget());
    Login->clearTexto();
    Login->show();
    close();
}

void MenuPrincipal::JanelaDeposito()
{
    Dep = new FazerDeposito(this);
    Dep->show();
    hide();
}

void MenuPrincipal::JanelaSaque()
{
    Saq = new FazerSaque(this);
    Saq->show();
    hide();
}

void MenuPrincipal::JanelaTransf()
{
    Transf = new FazerTransferencia(this);
    Transf->show();
    hide();
}

void MenuPrincipal::JanelaFatCred()
{
    FatCred = new VerFaturaCredito(this);
    FatCred->show();
    hide();
}

void MenuPrincipal::JanelaVerExtrato()
{
    VerExtra = new VerExtrato(this);
    VerExtra->show();
    hide();
}

void MenuPrincipal::JanelaEncerrarConta()
{
    EnceCont = new EncerrarConta(this);
    EnceCont->show();
    hide();
}

void MenuPrincipal::verSaldo()
{
    VerSald = new VerSaldo(this);
    VerSald->show();
    hide();
}

void MenuPrincipal::JanelaSolicitarCredito()
{
    SolicCred = new SolicitarCredito(this);
    hide();
    SolicCred->exec();
}
