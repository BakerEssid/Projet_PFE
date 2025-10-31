#ifndef MODULE_H
#define MODULE_H

#include<QtSerialPort/QSerialPortInfo>
#include<QtSerialPort/QSerialPort>
#include<QDebug>
class module
{
private:
    static const quint16 VID = 1027;      // Vendor ID du périphérique USB
    static const quint16 PID = 24577;     // Product ID du périphérique USB
    QSerialPort * portserie;              // Pointeur vers le port série utilisé
    QString portname;                     // Nom du port série sélectionné
    bool available;                       // Indique si le périphérique est disponible
    QByteArray d;                         // Tampon de données temporaire
    QByteArray d1;                        // Deuxième tampon de données
    QByteArray value;                     // Données lues du périphérique
    int dd;                               // Variable entière temporaire
public:
    module();                             // Constructeur de la classe
    int linkStm();                         // méthode pour connecter le module STM
    void write_To_Stm(QByteArray);         // méthode pour ecrire des données sur STM
    void writebyte_To_Stm(QByteArray, QByteArray); // méthode pour ecrire des données brutes sur STM
    QByteArray read_From_Stm();            // méthode pour lire des données depuis STM
    int* readbyte_From_Stm();              // méthode pour lire des données brutes depuis STM
    QSerialPort* getSerial(){ return portserie; } // méthode pour retourne le port série utilisé
};

#endif // MODULE_H
