#ifndef AUTH_MANAGER_H
#define AUTH_MANAGER_H

#include <iostream>
#include <string>
#include <limits>
#include "Biblioteca.h"
#include "UtilizatorStaff.h"

using std::cout;
using std::cin;
using std::string;

// ===================================================================
// Sesiune activa dupa login
// ===================================================================
struct Sesiune
{
    Utilizator* utilizator = nullptr;
    bool        esteLogat  = false;

    bool esteStaff() const
    {
        return utilizator && utilizator->getTip() == TipUtilizator::STAFF;
    }

    RolStaff getRolStaff() const
    {
        if (!esteStaff()) return RolStaff::BIBLIOTECAR;
        return dynamic_cast<UtilizatorStaff*>(utilizator)->getRol();
    }

    bool esteAdministrator() const
    {
        return esteStaff() && getRolStaff() == RolStaff::ADMINISTRATOR;
    }

    bool esteBibliotecerSef() const
    {
        return esteStaff() && (getRolStaff() == RolStaff::BIBLIOTECAR_SEF ||
                                getRolStaff() == RolStaff::ADMINISTRATOR);
    }

    bool esteBibliotectar() const
    {
        return esteStaff() && (getRolStaff() == RolStaff::BIBLIOTECAR ||
                                getRolStaff() == RolStaff::BIBLIOTECAR_SEF ||
                                getRolStaff() == RolStaff::ADMINISTRATOR);
    }

    bool esteCasier() const
    {
        return esteStaff() && (getRolStaff() == RolStaff::CASIER ||
                                getRolStaff() == RolStaff::ADMINISTRATOR);
    }
};

// ===================================================================
// Namespace Culori (duplicate din Meniu.h pentru a nu depinde de el)
// ===================================================================
namespace Auth
{
    const string RESET    = "\033[0m";
    const string BOLD     = "\033[1m";
    const string ALB      = "\033[97m";
    const string ROSU     = "\033[91m";
    const string VERDE    = "\033[92m";
    const string GALBEN   = "\033[93m";
    const string ALBASTRU = "\033[94m";
    const string CYAN     = "\033[96m";
    const string GRI      = "\033[90m";
}

// ===================================================================
// Clasa AuthManager - gestioneaza ecranul de login
// ===================================================================
class AuthManager
{
public:
    // ---------------------------------------------------------------
    // Afiseaza ecranul de login si intoarce sesiunea
    // ---------------------------------------------------------------
    static Sesiune login(Biblioteca& bib)
    {
        while (true)
        {
            afiseazaEcranLogin();

            string id, parola;

            cout << Auth::CYAN << "  ID utilizator: " << Auth::RESET;
            std::getline(cin, id);

            cout << Auth::CYAN << "  Parola: " << Auth::RESET;
            parola = citesteParola();

            Utilizator* u = bib.gasesteUtilizator(id);

            if (!u)
            {
                afiseazaEroare("ID-ul '" + id + "' nu exista in sistem.");
                pauza();
                continue;
            }

            if (!u->verificaParola(parola))
            {
                afiseazaEroare("Parola incorecta.");
                pauza();
                continue;
            }

            // Login reusit
            Sesiune s;
            s.utilizator = u;
            s.esteLogat  = true;

            afiseazaSucesLogin(u);
            pauza();
            return s;
        }
    }

private:

    static void afiseazaEcranLogin()
    {
        cout << "\033[2J\033[H"; // curata ecranul

        cout << "\n";
        cout << Auth::ALBASTRU << Auth::BOLD;
        cout << "  ============================================================\n";
        cout << "  ***    BIBLIOTECA UNIVERSITARA SUCEAVA    ***\n";
        cout << "  ============================================================\n";
        cout << Auth::RESET;

        cout << "\n";
        cout << Auth::BOLD << Auth::ALB;
        cout << "  AUTENTIFICARE\n";
        cout << Auth::RESET;
        cout << Auth::GRI;
        cout << "  ────────────────────────────────────────────────────────────\n";
        cout << Auth::RESET;
        cout << "\n";
        cout << Auth::GRI
             << "  Folositi ID-ul contului (ex: STU-1001, STAFF-001, BAS-2001)\n"
             << Auth::RESET << "\n";
    }

    static void afiseazaEroare(const string& msg)
    {
        cout << "\n" << Auth::ROSU << "  [EROARE] " << msg << Auth::RESET << "\n";
    }

    static void afiseazaSucesLogin(Utilizator* u)
    {
        cout << "\n";
        cout << Auth::VERDE << Auth::BOLD;
        cout << "  [OK] Bun venit, " << u->getNumeComplet() << "!\n";
        cout << Auth::RESET;
        cout << Auth::GRI
             << "  Tip cont: " << u->getTipNume() << "\n"
             << Auth::RESET;
    }

    static void pauza()
    {
        cout << "\n" << Auth::GRI
             << "  Apasati Enter pentru a continua..."
             << Auth::RESET;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Citeste parola fara echo (ascunde caracterele)
    static string citesteParola()
    {
        string parola;
        // Pe Linux/WSL putem dezactiva echo
        system("stty -echo");
        std::getline(cin, parola);
        system("stty echo");
        cout << "\n";
        return parola;
    }
};

#endif // AUTH_MANAGER_H