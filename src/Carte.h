#ifndef CARTE_H
#define CARTE_H

#include <iostream>
#include <string>
#include <vector>
#include "IAfisabil.h"
#include "Autor.h"
#include "Editura.h"

using std::string;
using std::vector;
using std::cout;

// -----------------------------------------------------------------------
// Enum-uri
// -----------------------------------------------------------------------

enum class TipCoperta
{
    CARTONATA,
    BROSATA,
    PIELE,          // editii de lux
    SPIRALATA       // caiete, atlase
};

enum class StatusCarte
{
    DISPONIBILA,
    IMPRUMUTATA,
    REZERVATA,
    DETERIORATA,
    SCOASA_DIN_UZ   // retras din inventar activ
};

enum class LimbaCartii
{
    ROMANA,
    ENGLEZA,
    FRANCEZA,
    GERMANA,
    SPANIOLA,
    ITALIANA,
    ALTA
};

enum class ProvenientaCarte
{
    CUMPARATA,
    DONATIE,
    SCHIMB,
    MOSTENIRE
};

// -----------------------------------------------------------------------
// ExemplarFizic - fiecare copie fizica a unei carti
// -----------------------------------------------------------------------
// ISBN este acelasi pentru toate exemplarele aceleiasi carti.
// codUnic este diferit pentru fiecare exemplar fizic (ex: BIB-2024-00001).
// Asta permite inventarul fizic al bibliotecii.

struct ExemplarFizic
{
    string          codUnic;        // generat automat
    StatusCarte     status;
    string          locatieCladire;
    string          locatieCamera;
    string          locatieRaft;
    string          locatieSectiune;
    ProvenientaCarte provenienta;
    int             anIntrareColectie;
    double          pretAchizitie;  // pretul platit de biblioteca
    string          observatii;     // ex: "pagina 34 patata"

    ExemplarFizic(string cod, string cladire, string camera,
                  string raft, string sectiune,
                  ProvenientaCarte prov = ProvenientaCarte::CUMPARATA,
                  int an = 2024, double pret = 0.0)
        : codUnic(cod), status(StatusCarte::DISPONIBILA),
          locatieCladire(cladire), locatieCamera(camera),
          locatieRaft(raft), locatieSectiune(sectiune),
          provenienta(prov), anIntrareColectie(an),
          pretAchizitie(pret)
    {}

    void afisare() const
    {
        cout << "   Exemplar [" << codUnic << "] | "
             << locatieCladire << " > " << locatieCamera
             << " > Raft " << locatieRaft << " / " << locatieSectiune;
        cout << " | Status: ";
        switch (status)
        {
            case StatusCarte::DISPONIBILA:    cout << "Disponibil";    break;
            case StatusCarte::IMPRUMUTATA:    cout << "Imprumutat";    break;
            case StatusCarte::REZERVATA:      cout << "Rezervat";      break;
            case StatusCarte::DETERIORATA:    cout << "Deteriorat";    break;
            case StatusCarte::SCOASA_DIN_UZ:  cout << "Scos din uz";   break;
        }
        cout << "\n";
    }
    string getCod()     const { return codUnic; }
    string getLocatie() const { return locatieCladire + " / " + locatieCamera + " / Raft " + locatieRaft; }
};

// -----------------------------------------------------------------------
// Clasa de baza: Carte
// -----------------------------------------------------------------------

class Carte : public IAfisabil
{
protected:
    // Identificatori
    string              isbn;
    string              titlu;

    // Autori - pointeri catre entitati din IndexAutori global
    // (nu cream autori noi, doar referinte)
    vector<Autor*>      autori;

    // Editura - pointer catre entitate din registrul de edituri
    Editura*            editura;

    int                 anAparitie;
    LimbaCartii         limba;
    TipCoperta          coperta;

    // Dimensiuni fizice
    int                 nrPagini;
    double              greutateGrame;

    // Exemplare fizice (copii) ale acestei carti
    vector<ExemplarFizic> exemplare;

    // Serie / volum (optional)
    string              serie;
    int                 nrVolum;     // 0 = nu face parte dintr-o serie

    // Pret de catalog al editurii (diferit de pretul de achizitie al bibliotecii)
    double              pretCatalog;

    // Gen / categorie specifica (SF, Fantasy, Horror, C++, Matematica etc.)
    string              gen;

public:
    // Constructor principal
    Carte(string _isbn, string _titlu,
          vector<Autor*> _autori, Editura* _editura,
          int _an, LimbaCartii _limba,
          TipCoperta _coperta,
          int _pagini = 0, double _greutate = 0.0,
          string _serie = "", int _volum = 0,
          double _pretCatalog = 0.0,
          string _gen = "")
        : isbn(_isbn), titlu(_titlu),
          autori(_autori), editura(_editura),
          anAparitie(_an), limba(_limba),
          coperta(_coperta),
          nrPagini(_pagini), greutateGrame(_greutate),
          serie(_serie), nrVolum(_volum),
          pretCatalog(_pretCatalog),
          gen(_gen)
    {}

    virtual ~Carte() = default;

    // -----------------------------------------------------------------------
    // Getteri
    // -----------------------------------------------------------------------
    string          getIsbn()         const { return isbn; }
    string          getTitlu()        const { return titlu; }
    vector<Autor*>  getAutori()       const { return autori; }
    Editura*        getEditura()      const { return editura; }
    int             getAnAparitie()   const { return anAparitie; }
    LimbaCartii     getLimba()        const { return limba; }
    TipCoperta      getCoperta()      const { return coperta; }
    int             getNrPagini()     const { return nrPagini; }
    double          getGreutate()     const { return greutateGrame; }
    string          getSerie()        const { return serie; }
    int             getNrVolum()      const { return nrVolum; }
    double          getPretCatalog()  const { return pretCatalog; }
    string          getGen()          const { return gen; }
    void            setGen(const string& g) { gen = g; }

    const vector<ExemplarFizic>& getExemplare() const { return exemplare; }
    string getLocatieExemplar(const string& cod) const {
        for (const auto& ex : exemplare) {
            if (ex.getCod() == cod) return ex.getLocatie();
        }
        return "";
    }

    // -----------------------------------------------------------------------
    // Gestiune exemplare
    // -----------------------------------------------------------------------
    void adaugaExemplar(const ExemplarFizic& ex)
    {
        exemplare.push_back(ex);
    }

    int nrExemplareDisponibile() const
    {
        int count = 0;
        for (const auto& ex : exemplare)
            if (ex.status == StatusCarte::DISPONIBILA) count++;
        return count;
    }

    int nrExemplareTotal() const
    {
        return (int)exemplare.size();
    }

    // Returneaza primul exemplar disponibil sau nullptr
    ExemplarFizic* getPrimulDisponibil()
    {
        for (auto& ex : exemplare)
            if (ex.status == StatusCarte::DISPONIBILA)
                return &ex;
        return nullptr;
    }

    // -----------------------------------------------------------------------
    // Afisare - metoda virtuala (polimorfism)
    // -----------------------------------------------------------------------
    virtual void afisareDetalii() const override
    {
        cout << "===================================\n";
        cout << "Titlu : " << titlu;
        if (nrVolum > 0) cout << " (Vol." << nrVolum << " din " << serie << ")";
        cout << "\n";
        cout << "ISBN  : " << isbn << "\n";

        cout << "Autor : ";
        for (int i = 0; i < (int)autori.size(); i++)
        {
            if (i) cout << "; ";
            cout << autori[i]->getNumeComplet();
        }
        cout << "\n";

        if (editura) cout << "Ed.   : " << editura->getNume()
                          << " (" << anAparitie << ")\n";

        cout << "Limba : " << limbaToString() << " | ";
        cout << "Coperta: " << copertaToString() << "\n";

        if (nrPagini > 0)     cout << "Pagini: " << nrPagini << "\n";
        if (greutateGrame > 0) cout << "Greut.: " << greutateGrame << " g\n";

        cout << "Exemplare: " << nrExemplareDisponibile()
             << " disponibile / " << nrExemplareTotal() << " total\n";

        for (const auto& ex : exemplare)
            ex.afisare();
    }

    // -----------------------------------------------------------------------
    // Metode virtuale pure - implementate de fiecare tip de carte
    // -----------------------------------------------------------------------
    virtual int    getTimpImprumut()     const = 0;
    virtual double getTaxaDeteriorare()  const = 0;
    virtual double getTaxaIntarziere()   const = 0;
    virtual string getTipCarte()         const = 0; // ex: "Fictiune", "Tehnica"

    // -----------------------------------------------------------------------
    // Operator << supraincarcata
    // -----------------------------------------------------------------------
    friend std::ostream& operator<<(std::ostream& os, const Carte& c)
    {
        os << "[" << c.getTipCarte() << "] " << c.titlu
           << " (" << c.anAparitie << ") - ISBN: " << c.isbn;
        if (!c.gen.empty()) os << " [" << c.gen << "]";
        return os;
    }

private:
    string limbaToString() const
    {
        switch (limba)
        {
            case LimbaCartii::ROMANA:   return "Romana";
            case LimbaCartii::ENGLEZA:  return "Engleza";
            case LimbaCartii::FRANCEZA: return "Franceza";
            case LimbaCartii::GERMANA:  return "Germana";
            case LimbaCartii::SPANIOLA: return "Spaniola";
            case LimbaCartii::ITALIANA: return "Italiana";
            default:                    return "Alta";
        }
    }

    string copertaToString() const
    {
        switch (coperta)
        {
            case TipCoperta::CARTONATA:  return "Cartonata";
            case TipCoperta::BROSATA:    return "Brosata";
            case TipCoperta::PIELE:      return "Piele";
            case TipCoperta::SPIRALATA:  return "Spiralata";
            default:                     return "?";
        }
    }
};

#endif // CARTE_H