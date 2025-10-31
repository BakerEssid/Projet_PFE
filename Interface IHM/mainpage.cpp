#include "mainpage.h"
#include "mainwindow.h"
#include "ui_mainpage.h"
#include <QDateTime>
#include <QTime>
#include <QDate>
#include <QTimer>
#include <QUrl>
#include <QDesktopServices>

// Constructeur de la page principale
MainPage::MainPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainPage)
{
    ui->setupUi(this);  // Initialise l'interface graphique

    // Tente de connecter au STM32 via le module série
    int rep = M.linkStm();
    switch (rep)
    {
    case (0) : qDebug() << "Device is available and connected";
        break;
    case (1) : qDebug() << "Device is available and not connected";
        break;
    case (-1) : qDebug() << "Device is not available and not connected"; break;
    }

    // Connecte le signal readyRead() du port série à la fonction display_Tnfo()
    QObject::connect(M.getSerial(), SIGNAL(readyRead()), this, SLOT(display_Tnfo()));

    // Timer pour mettre à jour l'heure chaque seconde
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showtime()));
    timer->start();

    // Affiche la date actuelle dans le label
    QDateTime date = QDateTime::currentDateTime();
    QString datetimetext = date.toString("dddd dd MMMM yyyy");
    ui->Date->setText(datetimetext);
}

// Destructeur
MainPage::~MainPage()
{
    delete ui; // Libère la mémoire de l'UI
}

// Affiche l'heure actuelle sur le LCD
void MainPage::showtime()
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm : ss");
    ui->Clock->setText(time_text);
}

// Navigation vers la page capteurs
void MainPage::on_Go_Sensor_clicked()
{
    QObject::connect(ui->Go_Sensor, SIGNAL(clicked()), this, SLOT(on_Back_Sensor_clicked()));
    ui->stackedWidget->setCurrentWidget(ui->page);
}

// Retour depuis la page capteurs
void MainPage::on_Back_Sensor_clicked()
{
    QObject::connect(ui->Back_Sensor, SIGNAL(clicked()), this, SLOT(on_Go_Sensor_clicked()));
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}

// Navigation vers la page actionneurs
void MainPage::on_Go_Actuator_clicked()
{
    QObject::connect(ui->Go_Actuator, SIGNAL(clicked()), this, SLOT(on_Back_Actuator_clicked()));
    ui->stackedWidget->setCurrentWidget(ui->page);
}

// Retour depuis la page actionneurs
void MainPage::on_Back_Actuator_clicked()
{
    QObject::connect(ui->Back_Actuator, SIGNAL(clicked()), this, SLOT(on_Go_Actuator_clicked()));
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}

// Navigation vers la page centrale
void MainPage::on_Go_Central_clicked()
{
    QObject::connect(ui->Go_Central, SIGNAL(clicked()), this, SLOT(on_Back_Central_clicked()));
    ui->stackedWidget->setCurrentWidget(ui->page);
}

// Retour depuis la page centrale
void MainPage::on_Back_Central_clicked()
{
    QObject::connect(ui->Back_Central, SIGNAL(clicked()), this, SLOT(on_Go_Central_clicked()));
    ui->stackedWidget->setCurrentWidget(ui->page_4);
}

// Affiche les informations reçues depuis STM32
void MainPage::display_Tnfo()
{
    int* data1;
    data1 = M.readbyte_From_Stm(); // Lire les données depuis STM32

    // Affichage des valeurs pour debug
    qDebug() << "data1[0]" << data1[0];
    qDebug() << "data1[1]" << data1[1];
    qDebug() << "data1[2]" << data1[2];
    qDebug() << "data1[3]" << data1[3];
    qDebug() << "data1[4]" << data1[4];

    // Calcul d'une valeur (ex: carburant ou autre capteur)
    quint16 data = (data1[4] * 2097) / 255;

    // Affichage des valeurs sur les LCD
    ui->lcdNumber->display(data1[0]);
    ui->lcdNumber_2->display(data1[1]);
    ui->lcdNumber_3->display(data1[2]);
    ui->lcdNumber_4->display(data1[3]);
    ui->lcdNumber_5->display(data);

    // Mise à jour des états des actionneurs selon la valeur reçue
    if (48 == data1[5])
    {
        ui->lineEdit->setText("Buzzer active");
        ui->lineEdit_4->setText("Automatic mode disabled");
    }
    if (49 == data1[5])
    {
        ui->lineEdit->setText("Buzzer disabled");
        ui->lineEdit_4->setText("Automatic mode disabled");
    }
    if (50 == data1[5])
    {
        ui->lineEdit_2->setText("Fan active");
        ui->lineEdit_4->setText("Automatic mode disabled");
    }
    if (51 == data1[5])
    {
        ui->lineEdit_2->setText("Fan disabled");
        ui->lineEdit_4->setText("Automatic mode disabled");
    }
    if (52 == data1[5])
    {
        ui->lineEdit_3->setText("Wiper active");
        ui->lineEdit_4->setText("Automatic mode disabled");
    }
    if (53 == data1[5])
    {
        ui->lineEdit_3->setText("Wiper disabled");
        ui->lineEdit_4->setText("Automatic mode disabled");
    }
    if (54 == data1[5])
    {
        ui->lineEdit_4->setText("Automatic mode activated");
    }
}

// Commandes actionneurs vers STM32
void MainPage::on_Buzzer_ON_clicked() // Allumer buzzer
{ M.writebyte_To_Stm("0","M"); }

void MainPage::on_Buzzer_OFF_clicked() // Éteindre buzzer
{ M.writebyte_To_Stm("1","M"); }

void MainPage::on_Fan_ON_clicked() // Allumer ventilateur
{ M.writebyte_To_Stm("2","M"); }

void MainPage::on_Fan_OFF_clicked() // Éteindre ventilateur
{ M.writebyte_To_Stm("3","M"); }

void MainPage::on_Wiper_ON_clicked() // Allumer essuie-glace
{ M.writebyte_To_Stm("4","M"); }

void MainPage::on_Wiper_OFF_clicked() // Éteindre essuie-glace
{ M.writebyte_To_Stm("5","M"); }


// Quitter la page et revenir à la fenêtre principale
void MainPage::on_Quitter_clicked()
{
    hide();
    MainWindow *mainwindow = new MainWindow();
    mainwindow->show();
}

// Activer le mode automatique
void MainPage::on_Automatic_On_clicked()
{
    M.writebyte_To_Stm("6","A");
}

// Ouvrir le lien cloud Thingspeak
void MainPage::on_Cloud_clicked()
{
    QString link = "https://thingspeak.com/channels/2542416/private_show";
    QDesktopServices::openUrl(QUrl(link));
}

