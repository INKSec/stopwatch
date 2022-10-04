#include <iostream>
#include <chrono>
#include <ctime>
#include <map>
#include <string>
#include <limits>

// Funktionen
void stoppuhr(std::map <std::string, std::chrono::time_point<std::chrono::system_clock>> &);
std::chrono::time_point<std::chrono::system_clock> zeitmessung();
void externerAufrufDerMessung(std::string &, std::map <std::string, std::chrono::time_point<std::chrono::system_clock>> &);

//Globale Variable zum Zaehlen der Messwerte
static int counter = 1;

int main() {
    std::map <std::string, std::chrono::time_point<std::chrono::system_clock>> zeitspeicherChrono;

    stoppuhr(zeitspeicherChrono);


    std::chrono::time_point<std::chrono::system_clock> tempMesswert;
    tempMesswert = std::chrono::system_clock::now();
    std::chrono::time_point<std::chrono::system_clock> tempMesswert2;
    tempMesswert2 = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = tempMesswert2 - tempMesswert;
    std::cout << elapsed_seconds.count() << std::endl;

    std::string a = "de";
    zeitspeicherChrono[a]=tempMesswert;

    return 0;
}

void stoppuhr(std::map <std::string, std::chrono::time_point<std::chrono::system_clock>> &zeitspeicher) {

    bool run = true;
    int decision;

    while(run) {
        std::cout << "Was moechtest du machen?" << std::endl;

        std::cout << "Press '1': Starte Messung" << std::endl;
        std::cout << "Press '2': Zeitnahme mit automatischer Namenvergabe" << std::endl;
        std::cout << "Press '3': Reset" << std::endl;
        std::cout << "Press '4': Auflistung aller Zeiten" << std::endl;
        std::cout << "Press '5': Abfrage Differenzen" << std::endl;
        std::cout << "Press '6': Programm beenden" << std::endl;

        std::cin >> decision;

        switch(decision) {
            case 1: {
                std::chrono::time_point<std::chrono::system_clock> startMessung = zeitmessung();
                std::string tempName = "1. Messwert";
                zeitspeicher[tempName]=startMessung;
                break;
            }
            // Zeitmessung mit automatischer Namensvergabe
            case 2: {
                counter++;
                // aktuelle Zeit
                std::chrono::time_point<std::chrono::system_clock> tempMesswert = zeitmessung();
                // Nummer des Counters, der die Messungen zaehlt
                std::string tempName = std::to_string(counter) + ". Messwert";
                // hinzufuegen zur map Name/Messwert
                zeitspeicher[tempName]=tempMesswert;
                std::cout << "Messwert gespeichert" << std::endl;
                break;
            }
            case 3: {
                std::map<std::string, std::chrono::time_point<std::chrono::system_clock>>::iterator it;
                std::cout << "Alle Messwerte wurden geloescht" << std::endl;
                for (it = zeitspeicher.begin(); it != zeitspeicher.end();) {
                    zeitspeicher.erase(it, zeitspeicher.end());
                    counter = 1;
                    break;
                }
            }
            case 4: {
                std::map<std::string, std::chrono::time_point<std::chrono::system_clock>>::iterator it;
                std::cout << "Alle erfassten Messwerte:" << std::endl;
                for (it = zeitspeicher.begin(); it != zeitspeicher.end(); ++it) {
                    std::cout << it->first << std::endl;
                    std::time_t test = std::chrono::system_clock::to_time_t(it->second);
                    std::cout << std::ctime(&test) << std::endl;
                    //std::cout << it->first << " => " << std::ctime(&it->second);

                }
                break;
            }
            case 5: {
                std::string messwertEins, messwertZwei;

                std::cout << "Waehle zwei Messwerte aus denen die zeitliche Differenz ermittelt werden soll." << std::endl;
                std::cout << "Messwert 1: ";
                std::cin >> messwertEins;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "Messwert 2: ";
                std::cin >> messwertZwei;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::map<std::string, std::chrono::time_point<std::chrono::system_clock>>::iterator it;
                std::map<std::string, std::chrono::time_point<std::chrono::system_clock>>::iterator it1;

                it = zeitspeicher.upper_bound(messwertEins);
                it1 = zeitspeicher.upper_bound(messwertZwei);

                if (it == zeitspeicher.end()) {
                    std::cout << "Wert eins nicht gefunden" << std::endl;
                    break;
                }
                if (it1 == zeitspeicher.end()) {
                    std::cout << "Wert zwei nicht gefunden" << std::endl;
                    break;
                }
                std::chrono::duration<double> elapsed_seconds = it1->second - it->second;
                std::cout << elapsed_seconds.count() << std::endl;
                /*
                // Funktioniert noch nicht -> Hinzufuegen
                if(elapsed_seconds.count() <0) {
                    elapsed_seconds = elapsed_seconds * -1;
                }
                 */

                std::cout << "Zwischen dem " << messwertEins << " Messwert und dem " << messwertZwei << "Messwert  sind "
                <<
                elapsed_seconds.count() << " Sekunden vergangen" << std::endl;
                break;
            }
            case 6: {
                run = false;
                std::cout << "Programm wurde beendet" << std::endl;
            }
        }
    }
};

std::chrono::time_point<std::chrono::system_clock> zeitmessung() {
    std::chrono::time_point<std::chrono::system_clock> tempMesswert;
    tempMesswert = std::chrono::system_clock::now();
    return tempMesswert;
}

void externerAufrufDerMessung(std::string& nameMesswert, std::map <std::string, std::chrono::time_point<std::chrono::system_clock>> &zeitspeicher) {
    std::chrono::time_point<std::chrono::system_clock> tempMesswert = zeitmessung();
    zeitspeicher[nameMesswert]=tempMesswert;
    counter++;
};
