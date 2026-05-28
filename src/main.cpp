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
#include "UtilizatorStaff.h"
#include "Exceptii.h"
#include "DataSeeder.h"
#include "Fisiere.h"
#include "Server.h"

int main()
{
    std::cout << "\033[1m\033[94m";
    std::cout << "\n  *** Biblioteca Universitara Suceava ***\n";
    std::cout << "\033[0m\n";

    Biblioteca bib("Biblioteca Universitara Suceava", 2024);

    if (Fisiere::existaDateSalvate())
    {
        std::cout << "  Se incarca datele salvate...\n";
        Fisiere::incarcaTot(bib);
    }
    else
    {
        std::cout << "  Prima pornire - se populeaza baza de date...\n";
        DataSeeder::populeaza(bib);
        Fisiere::salveazaTot(bib);
    }

    std::cout << "\033[92m  Titluri: " << bib.getNrCarti()
              << " | Utilizatori: " << bib.getNrUtilizatori()
              << "\033[0m\n";

    Server server(bib);
    server.porneste(8080);

    return 0;
}