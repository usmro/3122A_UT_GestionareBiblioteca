#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <ctime>

#include "Colectie.h"
#include "Carte.h"
#include "Utilizator.h"
#include "Autor.h"
#include "Editura.h"
#include "Exceptii.h"

using std::string;
using std::cout;
using std::map;
using std::vector;

// -----------------------------------------------------------------------
// Helper: conversie la lowercase pentru cautare case-insensitive
// -----------------------------------------------------------------------
static string toLower(const string& s)
{
    string r = s;
    for (char& c : r) c = (char)std::tolower((unsigned char)c);
    return r;
}

// -----------------------------------------------------------------------
// Struct Imprumut
// -----------------------------------------------------------------------
struct Imprumut
{
    string   codExemplar;
    string   idUtilizator;
    string   isbnCarte;
    int      ziuaImprumut;
    int      lunaImprumut;
    int      anImprumut;
    int      zileLimita;
    bool     esteActiv;

    Imprumut(string cod, string uid, string isbn,
             int zi, int luna, int an, int zile)
        : codExemplar(cod), idUtilizator(uid), isbnCarte(isbn),
          ziuaImprumut(zi), lunaImprumut(luna), anImprumut(an),
          zileLimita(zile), esteActiv(true)
    {}
};

// -----------------------------------------------------------------------
// Struct Rezervare
// -----------------------------------------------------------------------
struct Rezervare
{
    string idUtilizator;
    string isbnCarte;
    int    ziua, luna, an;
    bool   esteActiva;

    Rezervare(string uid, string isbn, int z, int l, int a)
        : idUtilizator(uid), isbnCarte(isbn),
          ziua(z), luna(l), an(a), esteActiva(true)
    {}
};

// -----------------------------------------------------------------------
// Clasa Biblioteca
// -----------------------------------------------------------------------
class Biblioteca
{
private:
    string               nume;
    Colectie<Carte>      inventar;
    Colectie<Utilizator> utilizatori;
    Colectie<Autor>      indexAutori;
    Colectie<Editura>    indexEdituri;

    vector<Imprumut>     imprumuturi;
    vector<Rezervare>    rezervari;

    double               totalIncasari;
    int                  contorExemplare;
    int                  anCurent;
    std::ofstream        logFile;

public:
    // -----------------------------------------------------------------------
    // Constructor / Destructor
    // -----------------------------------------------------------------------
    Biblioteca(string _nume, int _an = 2024)
        : nume(_nume), totalIncasari(0.0),
          contorExemplare(0), anCurent(_an)
    {
        logFile.open("biblioteca_log.txt", std::ios::app);
        log("Biblioteca '" + nume + "' initiata.");
    }

    ~Biblioteca()
    {
        if (logFile.is_open())
        {
            log("Biblioteca '" + nume + "' inchisa.");
            logFile.close();
        }
    }

    // -----------------------------------------------------------------------
    // Getteri existenti
    // -----------------------------------------------------------------------
    string getNume()          const { return nume; }
    double getTotalIncasari() const { return totalIncasari; }
    int    getNrCarti()       const { return inventar.dimensiune(); }
    int    getNrUtilizatori() const { return utilizatori.dimensiune(); }

    // -----------------------------------------------------------------------
    // Getteri pentru Fisiere.h (acces la colectii)
    // -----------------------------------------------------------------------
    int         getNrAutori()        const { return indexAutori.dimensiune(); }
    int         getNrEdituri()       const { return indexEdituri.dimensiune(); }
    Autor*      getAutor(int i)      const { return indexAutori.get(i); }
    Editura*    getEditura(int i)    const { return indexEdituri.get(i); }
    Carte*      getCarte(int i)      const { return inventar.get(i); }
    Utilizator* getUtilizator(int i) const { return utilizatori.get(i); }

    const vector<Imprumut>& getImprumuturi() const { return imprumuturi; }

    // -----------------------------------------------------------------------
    // Adauga utilizator fara cout (folosit la incarcare din fisier)
    // -----------------------------------------------------------------------
    void adaugaUtilizatorSilent(Utilizator* u)
    {
        utilizatori.adauga(u);
    }

    // -----------------------------------------------------------------------
    // Adauga imprumut direct din fisier (fara logica de validare)
    // -----------------------------------------------------------------------
    void adaugaImprumutDirect(const string& cod, const string& uid,
                               const string& isbn,
                               int zi, int luna, int an, int zile, bool activ)
    {
        Imprumut imp(cod, uid, isbn, zi, luna, an, zile);
        imp.esteActiv = activ;
        imprumuturi.push_back(imp);
        if (activ)
        {
            Utilizator* u = gasesteUtilizator(uid);
            if (u) u->adaugaImprumut(cod);
        }
    }

    // -----------------------------------------------------------------------
    // Actualizeaza contorul de exemplare la incarcare din fisier
    // -----------------------------------------------------------------------
    void actualizeazaContorExemplare(const string& cod)
    {
        auto pos = cod.rfind('-');
        if (pos != string::npos)
        {
            try {
                int nr = std::stoi(cod.substr(pos + 1));
                if (nr > contorExemplare) contorExemplare = nr;
            } catch (...) {}
        }
    }

    // -----------------------------------------------------------------------
    // Generare cod unic exemplar: BIB-YYYY-NNNNN
    // -----------------------------------------------------------------------
    string genereazaCodExemplar()
    {
        contorExemplare++;
        std::ostringstream oss;
        oss << "BIB-" << anCurent << "-"
            << std::setw(5) << std::setfill('0') << contorExemplare;
        return oss.str();
    }

    // -----------------------------------------------------------------------
    // IndexAutori
    // -----------------------------------------------------------------------
    Autor* gasesteOrAdaugaAutor(string nume, string prenume,
                                 string nat, int anN, bool viu,
                                 string bio = "", string link = "")
    {
        for (int i = 0; i < indexAutori.dimensiune(); i++)
        {
            Autor* a = indexAutori.get(i);
            if (a->getNume() == nume && a->getPrenume() == prenume)
                return a;
        }
        Autor* nou = new Autor(nume, prenume, nat, anN, viu, bio, link);
        indexAutori.adauga(nou);
        log("Autor nou adaugat: " + prenume + " " + nume);
        return nou;
    }

    // -----------------------------------------------------------------------
    // IndexEdituri
    // -----------------------------------------------------------------------
    Editura* gasesteOrAdaugaEditura(string numeEd, string tara,
                                     string oras, int anInf = 0,
                                     string web = "")
    {
        for (int i = 0; i < indexEdituri.dimensiune(); i++)
        {
            Editura* e = indexEdituri.get(i);
            if (e->getNume() == numeEd) return e;
        }
        Editura* nou = new Editura(numeEd, tara, oras, anInf, web);
        indexEdituri.adauga(nou);
        return nou;
    }

    // -----------------------------------------------------------------------
    // Gestiune Carti
    // -----------------------------------------------------------------------
    void adaugaCarte(Carte* c)
    {
        for (int i = 0; i < inventar.dimensiune(); i++)
        {
            if (inventar.get(i)->getIsbn() == c->getIsbn())
                throw IsbnDuplicatException(c->getIsbn());
        }
        inventar.adauga(c);
        log("[Staff] Carte adaugata: " + c->getTitlu() + " [" + c->getIsbn() + "]");
        cout << "[Staff] Cartea '" << c->getTitlu() << "' a fost adaugata.\n";
    }

    string adaugaExemplarLaCarte(const string& isbn,
                                  const string& cladire, const string& camera,
                                  const string& raft, const string& sectiune,
                                  ProvenientaCarte prov = ProvenientaCarte::CUMPARATA,
                                  double pretAchizitie = 0.0)
    {
        Carte* c = gasesteCarte(isbn);
        if (!c) throw CarteLipsaException(isbn);

        string cod = genereazaCodExemplar();
        ExemplarFizic ex(cod, cladire, camera, raft, sectiune,
                         prov, anCurent, pretAchizitie);
        c->adaugaExemplar(ex);
        log("[Staff] Exemplar " + cod + " adaugat la '" + c->getTitlu() + "'");
        cout << "[Staff] Exemplar [" << cod << "] adaugat la '"
             << c->getTitlu() << "' -> "
             << cladire << " / " << camera << " / Raft " << raft << "\n";
        return cod;
    }

    // -----------------------------------------------------------------------
    // Gestiune Utilizatori
    // -----------------------------------------------------------------------
    void adaugaUtilizator(Utilizator* u)
    {
        utilizatori.adauga(u);
        log("[Staff] Utilizator inregistrat: " + u->getNumeComplet() +
            " [" + u->getId() + "]");
        cout << "[Staff] Utilizatorul " << u->getNumeComplet()
             << " a fost inregistrat.\n";
    }

    // -----------------------------------------------------------------------
    // Cautare
    // -----------------------------------------------------------------------
    Carte* gasesteCarte(const string& isbn)
    {
        for (int i = 0; i < inventar.dimensiune(); i++)
            if (inventar.get(i)->getIsbn() == isbn)
                return inventar.get(i);
        return nullptr;
    }

    Utilizator* gasesteUtilizator(const string& id)
    {
        for (int i = 0; i < utilizatori.dimensiune(); i++)
            if (utilizatori.get(i)->getId() == id)
                return utilizatori.get(i);
        return nullptr;
    }

    vector<Carte*> cautaDupaTitlu(const string& fragment)
    {
        vector<Carte*> rezultate;
        string fragLower = toLower(fragment);
        for (int i = 0; i < inventar.dimensiune(); i++)
        {
            Carte* c = inventar.get(i);
            if (toLower(c->getTitlu()).find(fragLower) != string::npos)
                rezultate.push_back(c);
        }
        return rezultate;
    }

    vector<Carte*> cautaDupaAutor(const string& numeAutor)
    {
        vector<Carte*> rezultate;
        string cautLower = toLower(numeAutor);
        for (int i = 0; i < inventar.dimensiune(); i++)
        {
            Carte* c = inventar.get(i);
            bool gasit = false;
            for (Autor* a : c->getAutori())
            {
                // Cauta in nume complet, nume sau prenume separat
                if (toLower(a->getNumeComplet()).find(cautLower) != string::npos ||
                    toLower(a->getNume()).find(cautLower) != string::npos ||
                    toLower(a->getPrenume()).find(cautLower) != string::npos)
                {
                    gasit = true;
                    break;
                }
            }
            if (gasit) rezultate.push_back(c);
        }
        return rezultate;
    }

    vector<Carte*> cautaDupaAn(int an)
    {
        vector<Carte*> rezultate;
        for (int i = 0; i < inventar.dimensiune(); i++)
        {
            Carte* c = inventar.get(i);
            if (c->getAnAparitie() == an)
                rezultate.push_back(c);
        }
        return rezultate;
    }

    // -----------------------------------------------------------------------
    // Imprumut
    // -----------------------------------------------------------------------
    void imprumutaCarte(const string& idUser, const string& isbn,
                         int zi, int luna, int an)
    {
        Utilizator* u = gasesteUtilizator(idUser);
        if (!u) throw UtilizatorInexistentException(idUser);

        Carte* c = gasesteCarte(isbn);
        if (!c) throw CarteLipsaException(isbn);

        if (!u->poateImprumuta())
            throw LimitaDepastitaException(u->getNumeComplet(),
                                           u->getLimitaImprumuturi());

        if (c->getTimpImprumut() == 0)
            throw CarteLipsaException(c->getTitlu() +
                                       " (nu se imprumuta - doar sala)");

        ExemplarFizic* ex = c->getPrimulDisponibil();
        if (!ex) throw CarteLipsaException(c->getTitlu() +
                                            " (toate exemplarele ocupate)");

        ex->status = StatusCarte::IMPRUMUTATA;
        u->adaugaImprumut(ex->codUnic);

        imprumuturi.emplace_back(ex->codUnic, idUser, isbn,
                                  zi, luna, an, c->getTimpImprumut());

        log("[Imprumut] " + u->getNumeComplet() + " -> '" +
            c->getTitlu() + "' [" + ex->codUnic + "]");

        cout << "[Imprumut] " << u->getNumeComplet()
             << " a imprumutat '" << c->getTitlu() << "' ["
             << ex->codUnic << "]\n";
        cout << "   -> De returnat in " << c->getTimpImprumut() << " zile.\n";
        cout << "   -> Locatie: " << ex->locatieCladire << " / "
             << ex->locatieCamera << " / Raft " << ex->locatieRaft << "\n";
    }

    // -----------------------------------------------------------------------
    // Returnare
    // -----------------------------------------------------------------------
    void returneazaCarte(const string& idUser, const string& codExemplar,
                          int zileIntarziere)
    {
        Utilizator* u = gasesteUtilizator(idUser);
        if (!u) throw UtilizatorInexistentException(idUser);

        for (auto& imp : imprumuturi)
        {
            if (imp.codExemplar == codExemplar &&
                imp.idUtilizator == idUser && imp.esteActiv)
            {
                imp.esteActiv = false;

                Carte* c = gasesteCarte(imp.isbnCarte);
                if (c)
                {
                    for (auto& ex : const_cast<vector<ExemplarFizic>&>(
                                        c->getExemplare()))
                    {
                        if (ex.codUnic == codExemplar)
                        {
                            ex.status = StatusCarte::DISPONIBILA;
                            break;
                        }
                    }
                    if (zileIntarziere > 0)
                    {
                        double taxaBruta  = zileIntarziere * c->getTaxaIntarziere();
                        double taxaFinala = u->aplicaDiscountTaxe(taxaBruta);
                        u->adaugaTaxa(taxaFinala);
                        cout << "[Returnare] INTARZIERE " << zileIntarziere
                             << " zile! Taxa: " << taxaFinala << " RON\n";
                    }
                }

                u->eliminaImprumut(codExemplar);
                log("[Returnare] " + u->getNumeComplet() +
                    " -> [" + codExemplar + "] intarziere: " +
                    std::to_string(zileIntarziere) + " zile");

                cout << "[Returnare] " << u->getNumeComplet()
                     << " a returnat [" << codExemplar << "]\n";
                return;
            }
        }
        cout << "[EROARE] Imprumut activ negasit pentru " << codExemplar << "\n";
    }

    // -----------------------------------------------------------------------
    // Incasare taxa
    // -----------------------------------------------------------------------
    void incaseazaTaxa(const string& idUser, double suma)
    {
        if (suma <= 0) throw TaxaInvalidaException(suma);
        Utilizator* u = gasesteUtilizator(idUser);
        if (!u) throw UtilizatorInexistentException(idUser);

        u->platesteTaxa(suma);
        totalIncasari += suma;
        log("[Casierie] " + std::to_string(suma) + " RON incasati de la " +
            u->getNumeComplet());
        cout << "[Casierie] S-au incasat " << suma << " RON de la "
             << u->getNumeComplet() << "\n";
    }

    // -----------------------------------------------------------------------
    // Afisare
    // -----------------------------------------------------------------------
    void afiseazaInventar() const
    {
        cout << "\n=== INVENTAR: " << nume << " ("
             << inventar.dimensiune() << " titluri) ===\n";
        for (int i = 0; i < inventar.dimensiune(); i++)
            inventar.get(i)->afisareDetalii();
    }

    void afiseazaUtilizatori() const
    {
        cout << "\n=== UTILIZATORI (" << utilizatori.dimensiune() << ") ===\n";
        for (int i = 0; i < utilizatori.dimensiune(); i++)
            utilizatori.get(i)->afisareDetalii();
    }

    void afiseazaAutori() const
    {
        cout << "\n=== INDEX AUTORI (" << indexAutori.dimensiune() << ") ===\n";
        for (int i = 0; i < indexAutori.dimensiune(); i++)
            indexAutori.get(i)->afisareDetalii();
    }

    void afiseazaRezultateCautare(const vector<Carte*>& rez) const
    {
        cout << "\n--- " << rez.size() << " rezultate ---\n";
        for (Carte* c : rez) cout << *c << "\n";
    }

    // -----------------------------------------------------------------------
    // Statistici
    // -----------------------------------------------------------------------
    void afiseazaStatistici() const
    {
        cout << "\n=== STATISTICI " << nume << " ===\n";
        cout << "Titluri: "         << inventar.dimensiune()    << "\n";
        cout << "Utilizatori: "     << utilizatori.dimensiune() << "\n";
        cout << "Autori unici: "    << indexAutori.dimensiune() << "\n";
        cout << "Edituri unice: "   << indexEdituri.dimensiune()<< "\n";
        cout << "Total incasari: "  << totalIncasari            << " RON\n";

        int imprActive = 0;
        for (const auto& imp : imprumuturi)
            if (imp.esteActiv) imprActive++;
        cout << "Imprumuturi active: " << imprActive << "\n";
    }

private:
    void log(const string& mesaj)
    {
        if (logFile.is_open())
            logFile << mesaj << "\n";
    }
};

#endif // BIBLIOTECA_H