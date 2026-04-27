#ifndef MENIU_H
#define MENIU_H

#include <iostream>
#include <string>
#include <vector>
#include <limits>
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

using std::cout;
using std::cin;
using std::string;

// ===================================================================
// Culori ANSI
// ===================================================================
namespace Culori {
    // Reset
    const string RESET   = "\033[0m";
    // Text
    const string ALB     = "\033[97m";
    const string GRI     = "\033[90m";
    const string ROSU    = "\033[91m";
    const string VERDE   = "\033[92m";
    const string GALBEN  = "\033[93m";
    const string ALBASTRU= "\033[94m";
    const string MAGENTA = "\033[95m";
    const string CYAN    = "\033[96m";
    // Bold
    const string BOLD    = "\033[1m";
    // Fundal
    const string BG_ALBASTRU  = "\033[44m";
    const string BG_VERDE     = "\033[42m";
    const string BG_ROSU      = "\033[41m";
    const string BG_GRI       = "\033[100m";
}

// ===================================================================
// Utilitare UI
// ===================================================================
class UI
{
public:
    static void golestEcranul()
    {
        cout << "\033[2J\033[H";
    }

    static void linie(char c = '-', int lungime = 60, const string& culoare = Culori::GRI)
    {
        cout << culoare;
        for (int i = 0; i < lungime; i++) cout << c;
        cout << Culori::RESET << "\n";
    }

    static void titlu(const string& text)
    {
        cout << "\n";
        linie('=', 60, Culori::ALBASTRU);
        cout << Culori::BOLD << Culori::ALBASTRU
             << "  " << text << "\n"
             << Culori::RESET;
        linie('=', 60, Culori::ALBASTRU);
    }

    static void subtitlu(const string& text)
    {
        cout << "\n" << Culori::BOLD << Culori::CYAN
             << "  >> " << text << "\n"
             << Culori::RESET;
        linie('-', 60, Culori::GRI);
    }

    static void succes(const string& msg)
    {
        cout << Culori::VERDE << "  [OK] " << msg << Culori::RESET << "\n";
    }

    static void eroare(const string& msg)
    {
        cout << Culori::ROSU << "  [EROARE] " << msg << Culori::RESET << "\n";
    }

    static void info(const string& msg)
    {
        cout << Culori::CYAN << "  [INFO] " << msg << Culori::RESET << "\n";
    }

    static void avertisment(const string& msg)
    {
        cout << Culori::GALBEN << "  [!] " << msg << Culori::RESET << "\n";
    }

    static void optiune(int nr, const string& text)
    {
        cout << "  " << Culori::BOLD << Culori::GALBEN
             << "[" << nr << "]"
             << Culori::RESET << " " << text << "\n";
    }

    static void optiuneSpeciala(const string& tasta, const string& text,
                                 const string& culoare = Culori::ROSU)
    {
        cout << "  " << Culori::BOLD << culoare
             << "[" << tasta << "]"
             << Culori::RESET << " " << text << "\n";
    }

    static int citesteOptiune(int min, int max)
    {
        int opt;
        while (true) {
            cout << "\n" << Culori::BOLD << Culori::ALB
                 << "  Alegeti optiunea: " << Culori::RESET;
            if (cin >> opt && opt >= min && opt <= max) {
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return opt;
            }
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            eroare("Optiune invalida. Introduceti un numar intre "
                   + std::to_string(min) + " si " + std::to_string(max) + ".");
        }
    }

    static string citesteString(const string& prompt)
    {
        cout << "  " << Culori::CYAN << prompt << ": " << Culori::RESET;
        string s;
        std::getline(cin, s);
        return s;
    }

    static int citesteInt(const string& prompt)
    {
        cout << "  " << Culori::CYAN << prompt << ": " << Culori::RESET;
        int v;
        cin >> v;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return v;
    }

    static double citesteDouble(const string& prompt)
    {
        cout << "  " << Culori::CYAN << prompt << ": " << Culori::RESET;
        double v;
        cin >> v;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return v;
    }

    static void pauza()
    {
        cout << "\n" << Culori::GRI
             << "  Apasati Enter pentru a continua..."
             << Culori::RESET;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    static void headerBiblioteca(const string& numeBib)
    {
        cout << "\n";
        linie('*', 60, Culori::ALBASTRU);
        cout << Culori::BOLD << Culori::BG_ALBASTRU << Culori::ALB;
        cout << "  *** BIBLIOTECA: " << numeBib << " ***\n";
        cout << Culori::RESET;
        linie('*', 60, Culori::ALBASTRU);
    }
};

// ===================================================================
// Clasa Meniu principala
// ===================================================================
class Meniu
{
private:
    Biblioteca& bib;

public:
    explicit Meniu(Biblioteca& b) : bib(b) {}

    // ---------------------------------------------------------------
    // Rulare meniu principal
    // ---------------------------------------------------------------
    void ruleaza()
    {
        while (true)
        {
            afiseazaMeniuPrincipal();
            int opt = UI::citesteOptiune(0, 5);
            switch (opt)
            {
                case 1: meniuCarti();       break;
                case 2: meniuUtilizatori(); break;
                case 3: meniuImprumuturi(); break;
                case 4: meniuCautare();     break;
                case 5: meniuStatistici();  break;
                case 0:
                    UI::golestEcranul();
                    cout << "\n" << Culori::BOLD << Culori::VERDE
                         << "  La revedere!\n" << Culori::RESET << "\n";
                    return;
            }
        }
    }

private:

    // ---------------------------------------------------------------
    // MENIU PRINCIPAL
    // ---------------------------------------------------------------
    void afiseazaMeniuPrincipal()
    {
        UI::golestEcranul();
        UI::headerBiblioteca(bib.getNume());

        cout << "\n";
        cout << Culori::BOLD << Culori::ALB
             << "  MENIU PRINCIPAL\n" << Culori::RESET;
        UI::linie('-', 60);

        UI::optiune(1, "Gestiune Carti");
        UI::optiune(2, "Gestiune Utilizatori");
        UI::optiune(3, "Imprumuturi & Returnari");
        UI::optiune(4, "Cautare & Filtrare");
        UI::optiune(5, "Statistici & Rapoarte");
        UI::linie('-', 60);
        UI::optiuneSpeciala("0", "Iesire", Culori::ROSU);
    }

    // ---------------------------------------------------------------
    // MENIU CARTI
    // ---------------------------------------------------------------
    void meniuCarti()
    {
        while (true)
        {
            UI::golestEcranul();
            UI::titlu("GESTIUNE CARTI");

            UI::optiune(1,  "Afiseaza toate cartile");
            UI::optiune(2,  "Cauta carte dupa ISBN");
            UI::optiune(3,  "Adauga carte noua - Fictiune");
            UI::optiune(4,  "Adauga carte noua - Tehnica");
            UI::optiune(5,  "Adauga carte noua - Educativa");
            UI::optiune(6,  "Adauga carte noua - Copii");
            UI::optiune(7,  "Adauga carte noua - Referinta");
            UI::optiune(8,  "Adauga carte noua - Religioasa");
            UI::optiune(9,  "Adauga carte noua - Periodic");
            UI::optiune(10, "Adauga carte noua - Manuscris Rar");
            UI::optiune(11, "Adauga exemplar fizic la carte");
            UI::optiune(12, "Afiseaza detalii complete carte");
            UI::optiune(13, "Afiseaza autori");
            UI::optiune(14, "Afiseaza edituri");
            UI::linie('-', 60);
            UI::optiuneSpeciala("0", "Inapoi la meniu principal");

            int opt = UI::citesteOptiune(0, 14);
            if (opt == 0) break;

            switch (opt)
            {
                case 1:  afiseazaToateCartile();      break;
                case 2:  cautaCarteDupaISBN();        break;
                case 3:  adaugaCarteFictiune();       break;
                case 4:  adaugaCarteTehnica();        break;
                case 5:  adaugaCarteEducativa();      break;
                case 6:  adaugaCarteCopii();          break;
                case 7:  adaugaCarteReferinta();      break;
                case 8:  adaugaCarteReligioasa();     break;
                case 9:  adaugaPeriodic();            break;
                case 10: adaugaManuscrisRar();        break;
                case 11: adaugaExemplarLaCarte();     break;
                case 12: afiseazaDetaliiCarte();      break;
                case 13: bib.afiseazaAutori();  UI::pauza(); break;
                case 14: afiseazaEdituri();           break;
            }
        }
    }

    // ---------------------------------------------------------------
    // MENIU UTILIZATORI
    // ---------------------------------------------------------------
    void meniuUtilizatori()
    {
        while (true)
        {
            UI::golestEcranul();
            UI::titlu("GESTIUNE UTILIZATORI");

            UI::optiune(1, "Afiseaza toti utilizatorii");
            UI::optiune(2, "Cauta utilizator dupa ID");
            UI::optiune(3, "Adauga utilizator Basic");
            UI::optiune(4, "Adauga utilizator Student");
            UI::optiune(5, "Adauga utilizator Premium");
            UI::optiune(6, "Adauga utilizator Staff");
            UI::optiune(7, "Afiseaza istoricul unui utilizator");
            UI::optiune(8, "Afiseaza imprumuturi active utilizator");
            UI::optiune(9, "Verifica parola utilizator");
            UI::linie('-', 60);
            UI::optiuneSpeciala("0", "Inapoi");

            int opt = UI::citesteOptiune(0, 9);
            if (opt == 0) break;

            switch (opt)
            {
                case 1: bib.afiseazaUtilizatori(); UI::pauza(); break;
                case 2: cautaUtilizatorDupaID();   break;
                case 3: adaugaUtilizatorBasic();   break;
                case 4: adaugaUtilizatorStudent(); break;
                case 5: adaugaUtilizatorPremium(); break;
                case 6: adaugaUtilizatorStaff();   break;
                case 7: afiseazaIstoricUtilizator(); break;
                case 8: afiseazaImprumututiUtilizator(); break;
                case 9: verificaParolaUtilizator(); break;
            }
        }
    }

    // ---------------------------------------------------------------
    // MENIU IMPRUMUTURI
    // ---------------------------------------------------------------
    void meniuImprumuturi()
    {
        while (true)
        {
            UI::golestEcranul();
            UI::titlu("IMPRUMUTURI & RETURNARI");

            UI::optiune(1, "Imprumuta carte");
            UI::optiune(2, "Returneaza carte");
            UI::optiune(3, "Incaseaza taxa utilizator");
            UI::optiune(4, "Verifica disponibilitate carte (ISBN)");
            UI::linie('-', 60);
            UI::optiuneSpeciala("0", "Inapoi");

            int opt = UI::citesteOptiune(0, 4);
            if (opt == 0) break;

            switch (opt)
            {
                case 1: imprumutaCarte();          break;
                case 2: returneazaCarte();         break;
                case 3: incaseazaTaxa();           break;
                case 4: verificaDisponibilitate(); break;
            }
        }
    }

    // ---------------------------------------------------------------
    // MENIU CAUTARE
    // ---------------------------------------------------------------
    void meniuCautare()
    {
        while (true)
        {
            UI::golestEcranul();
            UI::titlu("CAUTARE & FILTRARE");

            UI::optiune(1, "Cauta dupa titlu");
            UI::optiune(2, "Cauta dupa autor");
            UI::optiune(3, "Cauta dupa an aparitie");
            UI::optiune(4, "Cauta carte dupa ISBN");
            UI::optiune(5, "Cauta utilizator dupa ID");
            UI::linie('-', 60);
            UI::optiuneSpeciala("0", "Inapoi");

            int opt = UI::citesteOptiune(0, 5);
            if (opt == 0) break;

            switch (opt)
            {
                case 1: cautareDupaTitlu();  break;
                case 2: cautareDupaAutor();  break;
                case 3: cautareDupaAn();     break;
                case 4: cautaCarteDupaISBN(); break;
                case 5: cautaUtilizatorDupaID(); break;
            }
        }
    }

    // ---------------------------------------------------------------
    // MENIU STATISTICI
    // ---------------------------------------------------------------
    void meniuStatistici()
    {
        UI::golestEcranul();
        UI::titlu("STATISTICI & RAPOARTE");
        bib.afiseazaStatistici();
        UI::pauza();
    }

    // ===================================================================
    // IMPLEMENTARI ACTIUNI - CARTI
    // ===================================================================

    void afiseazaToateCartile()
    {
        UI::golestEcranul();
        UI::titlu("INVENTAR COMPLET");
        bib.afiseazaInventar();
        UI::pauza();
    }

    void cautaCarteDupaISBN()
    {
        UI::subtitlu("Cauta carte dupa ISBN");
        string isbn = UI::citesteString("ISBN");
        Carte* c = bib.gasesteCarte(isbn);
        if (c) {
            c->afisareDetalii();
        } else {
            UI::eroare("Cartea cu ISBN '" + isbn + "' nu a fost gasita.");
        }
        UI::pauza();
    }

    void afiseazaDetaliiCarte()
    {
        UI::subtitlu("Detalii complete carte");
        string isbn = UI::citesteString("ISBN");
        Carte* c = bib.gasesteCarte(isbn);
        if (c) {
            c->afisareDetalii();
        } else {
            UI::eroare("Cartea cu ISBN '" + isbn + "' nu a fost gasita.");
        }
        UI::pauza();
    }

    void adaugaCarteFictiune()
    {
        UI::subtitlu("Adauga carte Fictiune");
        try {
            string isbn  = UI::citesteString("ISBN");
            string titlu = UI::citesteString("Titlu");
            string numeA = UI::citesteString("Autor - Nume de familie");
            string prenA = UI::citesteString("Autor - Prenume");
            string nat   = UI::citesteString("Autor - Nationalitate");
            int    anA   = UI::citesteInt("Autor - An nastere");
            string numeE = UI::citesteString("Editura - Nume");
            string taraE = UI::citesteString("Editura - Tara");
            string orasE = UI::citesteString("Editura - Oras");
            int    an    = UI::citesteInt("An aparitie");
            string gen   = UI::citesteString("Gen literar");
            int    varsta= UI::citesteInt("Varsta minima recomandata");
            int    pagini= UI::citesteInt("Nr pagini");
            double pret  = UI::citesteDouble("Pret catalog (RON)");

            Autor*   a = bib.gasesteOrAdaugaAutor(numeA, prenA, nat, anA, true);
            Editura* e = bib.gasesteOrAdaugaEditura(numeE, taraE, orasE);

            auto* c = new CarteFictiune(isbn, titlu, {a}, e, an,
                LimbaCartii::ROMANA, TipCoperta::BROSATA, gen, varsta, pagini, 0.0, "", 0, pret);
            bib.adaugaCarte(c);
            UI::succes("Cartea '" + titlu + "' a fost adaugata cu succes!");

            char resp;
            cout << "  Adaugi un exemplar fizic acum? (d/n): ";
            cin >> resp;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (resp == 'd' || resp == 'D')
                adaugaExemplarPentru(isbn);

        } catch (const IsbnDuplicatException& e) {
            UI::eroare(e.what());
        } catch (...) {
            UI::eroare("Eroare la adaugarea cartii.");
        }
        UI::pauza();
    }

    void adaugaCarteTehnica()
    {
        UI::subtitlu("Adauga carte Tehnica");
        try {
            string isbn  = UI::citesteString("ISBN");
            string titlu = UI::citesteString("Titlu");
            string numeA = UI::citesteString("Autor - Nume de familie");
            string prenA = UI::citesteString("Autor - Prenume");
            string nat   = UI::citesteString("Autor - Nationalitate");
            int    anA   = UI::citesteInt("Autor - An nastere");
            string numeE = UI::citesteString("Editura - Nume");
            string taraE = UI::citesteString("Editura - Tara");
            string orasE = UI::citesteString("Editura - Oras");
            int    an    = UI::citesteInt("An aparitie");
            string dom   = UI::citesteString("Domeniu (ex: C++, Python, AI)");
            string niv   = UI::citesteString("Nivel (Incepator/Intermediar/Avansat)");
            int    pagini= UI::citesteInt("Nr pagini");
            double pret  = UI::citesteDouble("Pret catalog (RON)");

            Autor*   a = bib.gasesteOrAdaugaAutor(numeA, prenA, nat, anA, true);
            Editura* e = bib.gasesteOrAdaugaEditura(numeE, taraE, orasE);

            auto* c = new CarteTehnica(isbn, titlu, {a}, e, an,
                LimbaCartii::ENGLEZA, TipCoperta::CARTONATA, dom, niv, false, pagini, 0.0, pret);
            bib.adaugaCarte(c);
            UI::succes("Cartea tehnica '" + titlu + "' a fost adaugata!");

        } catch (const IsbnDuplicatException& e) {
            UI::eroare(e.what());
        } catch (...) {
            UI::eroare("Eroare la adaugarea cartii.");
        }
        UI::pauza();
    }

    void adaugaCarteEducativa()
    {
        UI::subtitlu("Adauga carte Educativa");
        try {
            string isbn  = UI::citesteString("ISBN");
            string titlu = UI::citesteString("Titlu");
            string numeE = UI::citesteString("Editura - Nume");
            string taraE = UI::citesteString("Editura - Tara");
            string orasE = UI::citesteString("Editura - Oras");
            int    an    = UI::citesteInt("An aparitie");
            string mat   = UI::citesteString("Materie");
            string prof  = UI::citesteString("Profil (Real/Uman/Economic)");
            int    cls   = UI::citesteInt("Clasa (0 = facultate)");
            int    pagini= UI::citesteInt("Nr pagini");
            double pret  = UI::citesteDouble("Pret catalog (RON)");

            auto* autor = bib.gasesteOrAdaugaAutor("Colectiv","Autori","Roman",2000,true);
            auto* ed    = bib.gasesteOrAdaugaEditura(numeE, taraE, orasE);

            auto* c = new CarteEducativa(isbn, titlu, {autor}, ed, an,
                LimbaCartii::ROMANA, TipCoperta::BROSATA, mat, prof, cls, pagini, 0.0, pret);
            bib.adaugaCarte(c);
            UI::succes("Manualul '" + titlu + "' a fost adaugat!");

        } catch (const IsbnDuplicatException& e) {
            UI::eroare(e.what());
        } catch (...) {
            UI::eroare("Eroare la adaugarea cartii.");
        }
        UI::pauza();
    }

    void adaugaCarteCopii()
    {
        UI::subtitlu("Adauga carte Copii");
        try {
            string isbn  = UI::citesteString("ISBN");
            string titlu = UI::citesteString("Titlu");
            string numeA = UI::citesteString("Autor - Nume de familie");
            string prenA = UI::citesteString("Autor - Prenume");
            string numeE = UI::citesteString("Editura - Nume");
            string taraE = UI::citesteString("Editura - Tara");
            string orasE = UI::citesteString("Editura - Oras");
            int    an    = UI::citesteInt("An aparitie");
            int    varsta= UI::citesteInt("Varsta recomandata");
            int    pagini= UI::citesteInt("Nr pagini");
            double pret  = UI::citesteDouble("Pret catalog (RON)");

            auto* a = bib.gasesteOrAdaugaAutor(numeA, prenA, "Roman", 1900, true);
            auto* e = bib.gasesteOrAdaugaEditura(numeE, taraE, orasE);

            auto* c = new CarteCopii(isbn, titlu, {a}, e, an,
                LimbaCartii::ROMANA, TipCoperta::CARTONATA, varsta, "Divers", false, pagini, 0.0, pret);
            bib.adaugaCarte(c);
            UI::succes("Cartea pentru copii '" + titlu + "' a fost adaugata!");

        } catch (const IsbnDuplicatException& e) {
            UI::eroare(e.what());
        } catch (...) {
            UI::eroare("Eroare la adaugarea cartii.");
        }
        UI::pauza();
    }

    void adaugaCarteReferinta()
    {
        UI::subtitlu("Adauga Material de Referinta");
        try {
            string isbn  = UI::citesteString("ISBN");
            string titlu = UI::citesteString("Titlu");
            string tip   = UI::citesteString("Tip (Dictionar/Atlas/Enciclopedie)");
            string numeE = UI::citesteString("Editura - Nume");
            string taraE = UI::citesteString("Editura - Tara");
            string orasE = UI::citesteString("Editura - Oras");
            int    an    = UI::citesteInt("An aparitie");
            int    pagini= UI::citesteInt("Nr pagini");
            double pret  = UI::citesteDouble("Pret catalog (RON)");

            auto* col = bib.gasesteOrAdaugaAutor("Colectiv","Autori","Roman",2000,true);
            auto* ed  = bib.gasesteOrAdaugaEditura(numeE, taraE, orasE);

            auto* c = new MaterialeReferinta(isbn, titlu, {col}, ed, an,
                LimbaCartii::ROMANA, TipCoperta::CARTONATA, tip, pagini, 0.0, pret);
            bib.adaugaCarte(c);
            UI::succes("Materialul de referinta '" + titlu + "' a fost adaugat!");

        } catch (const IsbnDuplicatException& e) {
            UI::eroare(e.what());
        } catch (...) {
            UI::eroare("Eroare la adaugarea.");
        }
        UI::pauza();
    }

    void adaugaCarteReligioasa()
    {
        UI::subtitlu("Adauga carte Religioasa");
        try {
            string isbn    = UI::citesteString("ISBN");
            string titlu   = UI::citesteString("Titlu");
            string religie = UI::citesteString("Religie (ex: Crestina)");
            string cult    = UI::citesteString("Cult (ex: Ortodoxa, Catolica)");
            string numeE   = UI::citesteString("Editura - Nume");
            string taraE   = UI::citesteString("Editura - Tara");
            string orasE   = UI::citesteString("Editura - Oras");
            int    an      = UI::citesteInt("An aparitie");
            int    pagini  = UI::citesteInt("Nr pagini");
            double pret    = UI::citesteDouble("Pret catalog (RON)");

            auto* col = bib.gasesteOrAdaugaAutor("Colectiv","Autori","Roman",2000,true);
            auto* ed  = bib.gasesteOrAdaugaEditura(numeE, taraE, orasE);

            auto* c = new CarteReligioasa(isbn, titlu, {col}, ed, an,
                LimbaCartii::ROMANA, TipCoperta::CARTONATA, religie, cult, pagini, pret);
            bib.adaugaCarte(c);
            UI::succes("Cartea religioasa '" + titlu + "' a fost adaugata!");

        } catch (const IsbnDuplicatException& e) {
            UI::eroare(e.what());
        } catch (...) {
            UI::eroare("Eroare la adaugarea.");
        }
        UI::pauza();
    }

    void adaugaPeriodic()
    {
        UI::subtitlu("Adauga Periodic (Ziar/Revista)");
        try {
            string issn    = UI::citesteString("ISSN");
            string titlu   = UI::citesteString("Titlu");
            string tip     = UI::citesteString("Tip (Ziar/Revista/Journal)");
            string domeniu = UI::citesteString("Domeniu");
            string numeE   = UI::citesteString("Editura - Nume");
            string taraE   = UI::citesteString("Editura - Tara");
            string orasE   = UI::citesteString("Editura - Oras");
            int    nrEd    = UI::citesteInt("Nr editie");
            int    luna    = UI::citesteInt("Luna aparitie (1-12)");
            int    an      = UI::citesteInt("An aparitie");
            int    pagini  = UI::citesteInt("Nr pagini");

            auto* col = bib.gasesteOrAdaugaAutor("Colectiv","Autori","Roman",2000,true);
            auto* ed  = bib.gasesteOrAdaugaEditura(numeE, taraE, orasE);

            auto* c = new Periodic(issn, titlu, {col}, ed, an,
                LimbaCartii::ROMANA, tip, nrEd, luna, an, domeniu, pagini);
            bib.adaugaCarte(c);
            UI::succes("Periodicul '" + titlu + "' a fost adaugat!");

        } catch (const IsbnDuplicatException& e) {
            UI::eroare(e.what());
        } catch (...) {
            UI::eroare("Eroare la adaugarea.");
        }
        UI::pauza();
    }

    void adaugaManuscrisRar()
    {
        UI::subtitlu("Adauga Manuscris Rar");
        try {
            string isbn     = UI::citesteString("ISBN");
            string titlu    = UI::citesteString("Titlu");
            string numeA    = UI::citesteString("Autor - Nume de familie");
            string prenA    = UI::citesteString("Autor - Prenume");
            int    anA      = UI::citesteInt("Autor - An nastere");
            string epoca    = UI::citesteString("Epoca (ex: Medievala, Renascentista)");
            string conditii = UI::citesteString("Conditii pastrare");
            int    an       = UI::citesteInt("An creare/publicare");
            double pret     = UI::citesteDouble("Valoare estimata (RON)");

            auto* a  = bib.gasesteOrAdaugaAutor(numeA, prenA, "Roman", anA, false);
            auto* ed = bib.gasesteOrAdaugaEditura("Minerva","Romania","Bucuresti");

            auto* c = new ManuscrisRar(isbn, titlu, {a}, ed, an,
                LimbaCartii::ROMANA, TipCoperta::PIELE, epoca, conditii, true, pret);
            bib.adaugaCarte(c);
            UI::succes("Manuscrisul '" + titlu + "' a fost adaugat!");

        } catch (const IsbnDuplicatException& e) {
            UI::eroare(e.what());
        } catch (...) {
            UI::eroare("Eroare la adaugarea.");
        }
        UI::pauza();
    }

    void adaugaExemplarPentru(const string& isbn)
    {
        string cladire  = UI::citesteString("Cladire");
        string camera   = UI::citesteString("Camera/Sala");
        string raft     = UI::citesteString("Raft");
        string sectiune = UI::citesteString("Sectiune");
        double pret     = UI::citesteDouble("Pret achizitie (RON)");

        try {
            string cod = bib.adaugaExemplarLaCarte(isbn, cladire, camera, raft, sectiune,
                ProvenientaCarte::CUMPARATA, pret);
            UI::succes("Exemplar adaugat cu codul: " + cod);
        } catch (const CarteLipsaException& e) {
            UI::eroare(e.what());
        }
    }

    void adaugaExemplarLaCarte()
    {
        UI::subtitlu("Adauga exemplar fizic");
        string isbn = UI::citesteString("ISBN carte");
        Carte* c = bib.gasesteCarte(isbn);
        if (!c) {
            UI::eroare("Cartea cu ISBN '" + isbn + "' nu exista in inventar.");
            UI::pauza();
            return;
        }
        cout << Culori::CYAN << "  Carte gasita: " << c->getTitlu()
             << Culori::RESET << "\n";
        adaugaExemplarPentru(isbn);
        UI::pauza();
    }

    void afiseazaEdituri()
    {
        UI::golestEcranul();
        UI::titlu("INDEX EDITURI");
        // Afisam prin inventar - extragem editurile unice
        UI::info("Edituri inregistrate in sistem (din inventar):");
        bib.afiseazaStatistici();
        UI::pauza();
    }

    // ===================================================================
    // IMPLEMENTARI ACTIUNI - UTILIZATORI
    // ===================================================================

    void cautaUtilizatorDupaID()
    {
        UI::subtitlu("Cauta utilizator dupa ID");
        string id = UI::citesteString("ID utilizator");
        Utilizator* u = bib.gasesteUtilizator(id);
        if (u) {
            u->afisareDetalii();
        } else {
            UI::eroare("Utilizatorul cu ID '" + id + "' nu a fost gasit.");
        }
        UI::pauza();
    }

    void adaugaUtilizatorBasic()
    {
        UI::subtitlu("Adauga utilizator Basic");
        string id    = UI::citesteString("ID (ex: BAS-100)");
        string nume  = UI::citesteString("Nume de familie");
        string pren  = UI::citesteString("Prenume");
        string cont  = UI::citesteString("Contact (email/telefon)");
        string parola= UI::citesteString("Parola");
        int    luni  = UI::citesteInt("Valabilitate abonament (luni)");
        int    an    = UI::citesteInt("An start abonament");
        int    luna  = UI::citesteInt("Luna start abonament (1-12)");

        try {
            bib.adaugaUtilizator(new UtilizatorBasic(id, nume, pren, cont, parola, luni, an, luna));
            UI::succes("Utilizatorul " + pren + " " + nume + " a fost inregistrat!");
        } catch (...) {
            UI::eroare("Eroare la adaugarea utilizatorului.");
        }
        UI::pauza();
    }

    void adaugaUtilizatorStudent()
    {
        UI::subtitlu("Adauga utilizator Student");
        string id    = UI::citesteString("ID (ex: STU-100)");
        string nume  = UI::citesteString("Nume de familie");
        string pren  = UI::citesteString("Prenume");
        string cont  = UI::citesteString("Contact");
        string parola= UI::citesteString("Parola");
        int    luni  = UI::citesteInt("Valabilitate abonament (luni)");
        int    an    = UI::citesteInt("An start");
        int    luna  = UI::citesteInt("Luna start (1-12)");
        string fac   = UI::citesteString("Facultate");
        int    anSt  = UI::citesteInt("An studiu (1-4)");
        string matr  = UI::citesteString("Nr matricol");

        try {
            bib.adaugaUtilizator(new UtilizatorStudent(id, nume, pren, cont, parola, luni, an, luna, fac, anSt, matr));
            UI::succes("Studentul " + pren + " " + nume + " a fost inregistrat!");
        } catch (...) {
            UI::eroare("Eroare la adaugarea studentului.");
        }
        UI::pauza();
    }

    void adaugaUtilizatorPremium()
    {
        UI::subtitlu("Adauga utilizator Premium");
        string id    = UI::citesteString("ID (ex: PRE-100)");
        string nume  = UI::citesteString("Nume de familie");
        string pren  = UI::citesteString("Prenume");
        string cont  = UI::citesteString("Contact");
        string parola= UI::citesteString("Parola");
        int    luni  = UI::citesteInt("Valabilitate abonament (luni)");
        int    an    = UI::citesteInt("An start");
        int    luna  = UI::citesteInt("Luna start (1-12)");

        try {
            bib.adaugaUtilizator(new UtilizatorPremium(id, nume, pren, cont, parola, luni, an, luna));
            UI::succes("Utilizatorul Premium " + pren + " " + nume + " a fost inregistrat!");
        } catch (...) {
            UI::eroare("Eroare la adaugarea utilizatorului.");
        }
        UI::pauza();
    }

    void adaugaUtilizatorStaff()
    {
        UI::subtitlu("Adauga utilizator Staff");
        string id    = UI::citesteString("ID (ex: STAFF-10)");
        string nume  = UI::citesteString("Nume de familie");
        string pren  = UI::citesteString("Prenume");
        string cont  = UI::citesteString("Contact");
        string parola= UI::citesteString("Parola");
        string dep   = UI::citesteString("Departament");

        cout << "  " << Culori::CYAN << "Rol:\n" << Culori::RESET;
        cout << "    1. Bibliotecar\n    2. Bibliotecar Sef\n"
             << "    3. Administrator\n    4. Casier\n    5. Arhivar\n";
        int rolOpt   = UI::citesteOptiune(1, 5);
        RolStaff rol = static_cast<RolStaff>(rolOpt - 1);

        double sal   = UI::citesteDouble("Salariu (RON)");
        int    anAng = UI::citesteInt("An angajare");
        int    lunAng= UI::citesteInt("Luna angajare (1-12)");

        try {
            bib.adaugaUtilizator(new UtilizatorStaff(id, nume, pren, cont, parola, dep, rol, sal, anAng, lunAng));
            UI::succes("Staff-ul " + pren + " " + nume + " a fost inregistrat!");
        } catch (...) {
            UI::eroare("Eroare la adaugarea staff-ului.");
        }
        UI::pauza();
    }

    void afiseazaIstoricUtilizator()
    {
        UI::subtitlu("Istoric utilizator");
        string id = UI::citesteString("ID utilizator");
        Utilizator* u = bib.gasesteUtilizator(id);
        if (u) {
            u->afisareIstoric();
        } else {
            UI::eroare("Utilizatorul cu ID '" + id + "' nu a fost gasit.");
        }
        UI::pauza();
    }

    void afiseazaImprumututiUtilizator()
    {
        UI::subtitlu("Imprumuturi active");
        string id = UI::citesteString("ID utilizator");
        Utilizator* u = bib.gasesteUtilizator(id);
        if (u) {
            cout << Culori::CYAN << "  " << u->getNumeComplet()
                 << " — " << u->getNrImprumuturi()
                 << "/" << u->getLimitaImprumuturi()
                 << " imprumuturi active\n" << Culori::RESET;
            cout << "  Taxe acumulate: " << Culori::ROSU
                 << u->getTaxeAcumulate() << " RON\n" << Culori::RESET;
        } else {
            UI::eroare("Utilizatorul cu ID '" + id + "' nu a fost gasit.");
        }
        UI::pauza();
    }

    void verificaParolaUtilizator()
    {
        UI::subtitlu("Verificare parola");
        string id     = UI::citesteString("ID utilizator");
        string parola = UI::citesteString("Parola");
        Utilizator* u = bib.gasesteUtilizator(id);
        if (u) {
            if (u->verificaParola(parola)) {
                UI::succes("Parola corecta pentru " + u->getNumeComplet());
            } else {
                UI::eroare("Parola incorecta!");
            }
        } else {
            UI::eroare("Utilizatorul cu ID '" + id + "' nu a fost gasit.");
        }
        UI::pauza();
    }

    // ===================================================================
    // IMPLEMENTARI ACTIUNI - IMPRUMUTURI
    // ===================================================================

    void imprumutaCarte()
    {
        UI::subtitlu("Imprumuta carte");
        string idUser = UI::citesteString("ID utilizator");
        string isbn   = UI::citesteString("ISBN carte");
        int    zi     = UI::citesteInt("Ziua curenta");
        int    luna   = UI::citesteInt("Luna curenta (1-12)");
        int    an     = UI::citesteInt("Anul curent");

        try {
            bib.imprumutaCarte(idUser, isbn, zi, luna, an);
            UI::succes("Imprumut inregistrat cu succes!");
        } catch (const CarteLipsaException& e) {
            UI::eroare(e.what());
        } catch (const LimitaDepastitaException& e) {
            UI::eroare(e.what());
        } catch (const UtilizatorInexistentException& e) {
            UI::eroare(e.what());
        } catch (...) {
            UI::eroare("Eroare la inregistrarea imprumutului.");
        }
        UI::pauza();
    }

    void returneazaCarte()
    {
        UI::subtitlu("Returneaza carte");
        string idUser    = UI::citesteString("ID utilizator");
        string codExemp  = UI::citesteString("Cod exemplar (BIB-YYYY-NNNNN)");
        int    zileIntarz = UI::citesteInt("Zile intarziere (0 daca la timp)");

        try {
            bib.returneazaCarte(idUser, codExemp, zileIntarz);
            UI::succes("Returnare inregistrata cu succes!");

            Utilizator* u = bib.gasesteUtilizator(idUser);
            if (u && u->getTaxeAcumulate() > 0) {
                UI::avertisment("Taxe acumulate: "
                    + std::to_string(u->getTaxeAcumulate()) + " RON");
            }
        } catch (const UtilizatorInexistentException& e) {
            UI::eroare(e.what());
        } catch (...) {
            UI::eroare("Eroare la returnare.");
        }
        UI::pauza();
    }

    void incaseazaTaxa()
    {
        UI::subtitlu("Incaseaza taxa");
        string idUser = UI::citesteString("ID utilizator");

        Utilizator* u = bib.gasesteUtilizator(idUser);
        if (!u) {
            UI::eroare("Utilizatorul nu a fost gasit.");
            UI::pauza();
            return;
        }

        cout << Culori::GALBEN << "  Taxe acumulate: "
             << u->getTaxeAcumulate() << " RON\n" << Culori::RESET;

        if (u->getTaxeAcumulate() <= 0) {
            UI::info("Utilizatorul nu are taxe de plata.");
            UI::pauza();
            return;
        }

        double suma = UI::citesteDouble("Suma de incasat (RON)");
        try {
            bib.incaseazaTaxa(idUser, suma);
            UI::succes("Taxa incasata cu succes!");
        } catch (const TaxaInvalidaException& e) {
            UI::eroare(e.what());
        } catch (...) {
            UI::eroare("Eroare la incasare.");
        }
        UI::pauza();
    }

    void verificaDisponibilitate()
    {
        UI::subtitlu("Verificare disponibilitate");
        string isbn = UI::citesteString("ISBN carte");
        Carte* c = bib.gasesteCarte(isbn);
        if (!c) {
            UI::eroare("Cartea cu ISBN '" + isbn + "' nu exista in inventar.");
        } else {
            int disp  = c->nrExemplareDisponibile();
            int total = c->nrExemplareTotal();
            cout << Culori::BOLD << "  " << c->getTitlu() << "\n" << Culori::RESET;
            cout << "  Exemplare disponibile: ";
            if (disp > 0)
                cout << Culori::VERDE << disp << "/" << total << Culori::RESET << "\n";
            else
                cout << Culori::ROSU << "0/" << total
                     << " (toate imprumutate)" << Culori::RESET << "\n";

            if (c->getTimpImprumut() == 0)
                UI::avertisment("Aceasta carte nu se imprumuta (doar sala de lectura).");
        }
        UI::pauza();
    }

    // ===================================================================
    // IMPLEMENTARI ACTIUNI - CAUTARE
    // ===================================================================

    void cautareDupaTitlu()
    {
        UI::subtitlu("Cautare dupa titlu");
        string fragment = UI::citesteString("Fragment titlu");
        auto rezultate = bib.cautaDupaTitlu(fragment);
        if (rezultate.empty()) {
            UI::info("Niciun rezultat pentru '" + fragment + "'.");
        } else {
            cout << Culori::VERDE << "  " << rezultate.size()
                 << " rezultate:\n" << Culori::RESET;
            for (Carte* c : rezultate)
                cout << "  " << *c << "\n";
        }
        UI::pauza();
    }

    void cautareDupaAutor()
    {
        UI::subtitlu("Cautare dupa autor");
        string numeAutor = UI::citesteString("Nume autor");
        auto rezultate = bib.cautaDupaAutor(numeAutor);
        if (rezultate.empty()) {
            UI::info("Niciun rezultat pentru autorul '" + numeAutor + "'.");
        } else {
            cout << Culori::VERDE << "  " << rezultate.size()
                 << " rezultate:\n" << Culori::RESET;
            for (Carte* c : rezultate)
                cout << "  " << *c << "\n";
        }
        UI::pauza();
    }

    void cautareDupaAn()
    {
        UI::subtitlu("Cautare dupa an aparitie");
        int an = UI::citesteInt("An aparitie");
        auto rezultate = bib.cautaDupaAn(an);
        if (rezultate.empty()) {
            UI::info("Nicio carte din anul " + std::to_string(an) + ".");
        } else {
            cout << Culori::VERDE << "  " << rezultate.size()
                 << " rezultate:\n" << Culori::RESET;
            for (Carte* c : rezultate)
                cout << "  " << *c << "\n";
        }
        UI::pauza();
    }
};

#endif // MENIU_H