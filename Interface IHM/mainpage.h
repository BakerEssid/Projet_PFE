#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QMainWindow>
#include "module.h"
#include <QtWidgets/QMainWindow>
#include <QtGui>
#include <QStackedWidget>

namespace Ui {
class MainPage;
}

class MainPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainPage(QWidget *parent = nullptr);
    ~MainPage();

private slots:
    void showtime();                   // Affiche l'heure actuelle
    void on_Go_Sensor_clicked();       // Naviguer vers la page capteurs
    void on_Back_Sensor_clicked();     // Retour à la page précédente depuis capteurs
    void on_Go_Actuator_clicked();     // Naviguer vers la page actionneurs
    void on_Back_Actuator_clicked();   // Retour à la page précédente depuis actionneurs
    void on_Go_Central_clicked();      // Naviguer vers la page centrale
    void on_Back_Central_clicked();    // Retour depuis la page centrale
    void display_Tnfo();               // Affiche les informations (ex : capteurs ou actionneurs)
    void on_Buzzer_ON_clicked();       // Allume le buzzer
    void on_Buzzer_OFF_clicked();      // Éteint le buzzer
    void on_Fan_ON_clicked();          // Allume le ventilateur
    void on_Fan_OFF_clicked();         // Éteint le ventilateur
    void on_Wiper_ON_clicked();        // Allume les essuie-glaces
    void on_Wiper_OFF_clicked();       // Éteint les essuie-glaces
    void on_Quitter_clicked();         // Quitte l'application
    void on_Automatic_On_clicked();    // Active le mode automatique
    void on_Cloud_clicked();           // Accès aux fonctionnalités cloud

private:
    Ui::MainPage *ui;
    module M;          // Instance de la classe module pour la communication série
    QString port;      // Nom du port série
    QString PID;       // Identifiant du produit
    QString VID;       // Identifiant du vendeur
};

#endif // MAINPAGE_H
