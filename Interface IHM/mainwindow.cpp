#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Login_clicked()
{
    QString UserName = ui->lineEdit_User_Name->text(); // Récupère le nom d'utilisateur
    QString Password = ui->lineEdit_Password->text(); // Récupère le mot de passe

    // Vérifie les identifiants
    if (UserName == "baker" && Password == "123")
    {
        QMessageBox::information(this,"baker", "Login Success."); // Message de succès
        hide(); // Cache la fenêtre de login
        MainPage *mainpage = new MainPage(); // Crée la page principale
        mainpage->show(); // Affiche la page principale
    }
    else
    {
        QMessageBox::warning(this,"baker", "Please Enter Valid Username Or Password"); // Message d'erreur
    }
}


void MainWindow::on_pushButton_Cancel_clicked()
{
    QMessageBox::StandardButton reply;
    // Affiche une boîte de dialogue pour confirmer la fermeture
    reply = QMessageBox::question(this,"baker", "Are you sure to cluse the application?",QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        QApplication::quit(); // Ferme l'application
    }
}

