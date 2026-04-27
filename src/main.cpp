#include <iostream>
#include <string>

#include "Biblioteca.h"
#include "CarteFictiune.h"
#include "CarteTehnica.h"
#include "CarteEducativa.h"
#include "CarteCopii.h"
#include "MaterialeReferinta.h"
#include "TipuriSpeciale.h"
#include "UtilizatorBasic.h"
#include "UtilizatorStudent.h"
#include "UtilizatorPremium.h"
#include "UtilizatorStaff.h"
#include "Exceptii.h"
#include "DataSeeder.h"
#include "Meniu.h"

using std::cout;
using std::string;

int main()
{
    // ====================================================================
    // Initializare si populare baza de date
    // ====================================================================
    cout << "\033[2J\033[H"; // Curata ecranul

    cout << "\033[1m\033[94m";
    cout << "\n  *** Biblioteca Universitara Suceava ***\n";
    cout << "\033[0m";
    cout << "\n  Se incarca baza de date...\n";

    Biblioteca bib("Biblioteca Universitara Suceava", 2024);
    DataSeeder::populeaza(bib);

    cout << "\033[92m  Baza de date incarcata!\033[0m\n";
    cout << "  Titluri: " << bib.getNrCarti()
         << " | Utilizatori: " << bib.getNrUtilizatori() << "\n";
    cout << "\n  Apasati Enter pentru a continua...";
    cin.ignore();

    // ====================================================================
    // Pornire meniu
    // ====================================================================
    Meniu meniu(bib);
    meniu.ruleaza();

    return 0;
}