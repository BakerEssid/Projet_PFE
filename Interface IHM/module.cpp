#include "module.h"

module::module()
{
    d = "";               // Initialise le tampon à vide
    portname = "";        // Initialise le nom du port à vide
    available = false;    // Périphérique non disponible au départ
    portserie = new QSerialPort; // Crée un objet QSerialPort

}

int module::linkStm()
{
    // Parcours tous les ports série disponibles
    foreach (const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        if(info.hasVendorIdentifier() &&info.hasProductIdentifier())
        {
            qDebug() << "Product ID = " << info.productIdentifier();
            qDebug() << "Vendor ID = " << info.vendorIdentifier();
            qDebug() << "Port name = " << info.portName();

            // Si le périphérique correspond au VID et PID connus
            if(info.vendorIdentifier() == VID &&info.productIdentifier()==PID)
            {
                available = true;
                portname=info.portName(); // Sauvegarde le nom du port
            }
        }
    }

    // Si le périphérique est disponible
    if(available){
        portserie->setPortName(portname); // Définit le port
        if(portserie->open(QSerialPort::ReadWrite)) // Ouvre le port en lecture/écriture
        {
            // Configure le port série
            portserie->setBaudRate(QSerialPort::Baud115200);
            portserie->setDataBits(QSerialPort::Data8);
            portserie->setParity(QSerialPort::NoParity);
            portserie->setStopBits(QSerialPort::OneStop);
            portserie->setFlowControl(QSerialPort::NoFlowControl);
            return 0; // Connexion réussie
        }
        return 1; // Port trouvé mais non ouvert
    }
    return -1; // Périphérique non trouvé
}


void module::write_To_Stm(QByteArray d)
{
     // Vérifie si le port est écrivable
    if (portserie->isWritable())
    {
        portserie->write(d);  // Vérifie si le port est écrivable
    }
    else
    {
        qDebug() << "couldn't write to stm"; // Message d'erreur
    }
}

void module::writebyte_To_Stm(QByteArray d, QByteArray d1)
{
    if (portserie->isWritable())
    {
        QByteArray dataToWrite = d + d1;
        portserie->write(dataToWrite);
    }
    else
    {
        qDebug() << "couldn't write to stm";
    }
}

QByteArray module::read_From_Stm()
{
    // Vérifie si le port est lisible
    if(portserie->isReadable())
    {
        d=portserie->readAll(); // Lit toutes les données disponibles
    }
    return d;
}

/*QByteArray module::read_From_Stm()
{
    if(portserie->isReadable())
    {
        d=portserie->readAll();
        qDebug() << "Les valeur sont"<< d;
    }
    return d;
}*/

/*int module::readbyte_From_Stm(quint8 count)
{ QList<int>i;
    int tab1[4];
    if(portserie->isReadable())
    {
        value=portserie->read(4);
        qDebug() << "les valeur sont"<< value;
    }
    for (const QChar &ch :value )
    {
    i.append(ch.unicode());
    }
   qDebug() << "i " << i ;

    for (int j = 0; j < i.size(); ++j)
    {
       qDebug() << "Element " << j << ":" << i[j];
        tab1[j]=i[j];
        qDebug() << "Elementtab1 " << j << ":" << tab1[j];
    }
    qDebug() << "var" << i[count-1];
    return  i[count-1];
}*/

int* module::readbyte_From_Stm()
{
    QList<int> i;   // Liste temporaire pour stocker les caractères
    int* tab1 = new int[6]; // Tableau dynamique pour les valeurs numériques

    if (portserie->isReadable())
    {
        value = portserie->read(6); // Lit 6 octets depuis le port série
        qDebug() << "les valeur sont" << value;
    }


    // Convertit chaque caractère en entier et l'ajoute à la liste
    for (const QChar &ch : value)
    {
        i.append(ch.unicode());
    }
    qDebug() << "i " << i;

    // Copie les valeurs dans le tableau tab1
    for (int j = 0; j < i.size(); ++j)
    {
        qDebug() << "Element " << j << ":" << i[j];
        tab1[j] = i[j];
        qDebug() << "Element tab1 " << j << ":" << tab1[j];
    }
    return tab1; // Retourne le tableau des entiers
}

