#ifndef TIPURI_SPECIALE_H
#define TIPURI_SPECIALE_H
#include "Carte.h"

// -----------------------------------------------------------------------
// CarteReligioasa
// -----------------------------------------------------------------------
class CarteReligioasa : public Carte
{
private:
    string religie;   // "Ortodoxa", "Catolica", "Protestanta", "Islam", etc.
    string cult;

public:
    CarteReligioasa(string isbn, string titlu,
                    vector<Autor*> autori, Editura* editura,
                    int an, LimbaCartii limba, TipCoperta coperta,
                    string _religie, string _cult,
                    int pagini = 0, double pretCatalog = 0.0)
        : Carte(isbn, titlu, autori, editura, an, limba, coperta,
                pagini, 0.0, "", 0, pretCatalog, _religie),
          religie(_religie), cult(_cult)
    {}

    string getReligie() const { return religie; }
    string getCult()    const { return cult; }

    void afisareDetalii() const override
    {
        Carte::afisareDetalii();
        cout << "  [Religioasa] Religie: " << religie
             << " | Cult: " << cult << "\n";
    }

    int    getTimpImprumut()    const override { return 21; }
    double getTaxaDeteriorare() const override { return 50.0; }
    double getTaxaIntarziere()  const override { return 1.0; }
    string getTipCarte()        const override { return "Religioasa"; }
};

// -----------------------------------------------------------------------
// Periodic - ziare, reviste, jurnale stiintifice
// Foloseste ISSN in loc de ISBN.
// De regula nu se imprumuta - se citesc in sala.
// -----------------------------------------------------------------------
class Periodic : public Carte
{
private:
    string issn;            // International Standard Serial Number
    string tipPeriodic;     // "Ziar", "Revista", "Journal"
    int    nrEditie;
    int    luna;
    int    anEditie;
    string domeniu;

public:
    Periodic(string _issn, string titlu,
             vector<Autor*> autori, Editura* editura,
             int an, LimbaCartii limba,
             string tip, int nrEd, int _luna, int _an,
             string dom = "",
             int pagini = 0)
        : Carte(_issn, titlu, autori, editura, an, limba,
                TipCoperta::BROSATA, pagini, 0.0, "", 0, 0.0, tip),
          issn(_issn), tipPeriodic(tip),
          nrEditie(nrEd), luna(_luna), anEditie(_an),
          domeniu(dom)
    {}

    string getIssn()       const { return issn; }
    string getTipPeriodic() const { return tipPeriodic; }
    int    getNrEditie()    const { return nrEditie; }
    string getDomeniu()     const { return domeniu; }

    void afisareDetalii() const override
    {
        Carte::afisareDetalii();
        cout << "  [Periodic] " << tipPeriodic
             << " | Editia " << nrEditie
             << " | " << luna << "/" << anEditie;
        if (!domeniu.empty()) cout << " | Domeniu: " << domeniu;
        cout << " | ISSN: " << issn << "\n";
        cout << "  ATENTIE: Doar sala de lectura!\n";
    }

    int    getTimpImprumut()    const override { return 0; }
    double getTaxaDeteriorare() const override { return 20.0; }
    double getTaxaIntarziere()  const override { return 2.0; }
    string getTipCarte()        const override { return "Periodic"; }
};

// -----------------------------------------------------------------------
// ManuscrisRar - acces restrictionat, conditii speciale de conservare
// -----------------------------------------------------------------------
class ManuscrisRar : public Carte
{
private:
    string epoca;       // "Medieval", "Renascentist", "Modern timpuriu"
    string conditiiPastrare;
    bool   necesitaSupervizare; // trebuie bibliotecar prezent

public:
    ManuscrisRar(string isbn, string titlu,
                 vector<Autor*> autori, Editura* editura,
                 int an, LimbaCartii limba, TipCoperta coperta,
                 string _epoca, string conditii, bool supervizare,
                 double pretCatalog = 0.0)
        : Carte(isbn, titlu, autori, editura, an, limba, coperta,
                0, 0.0, "", 0, pretCatalog, _epoca),
          epoca(_epoca), conditiiPastrare(conditii),
          necesitaSupervizare(supervizare)
    {}

    string getEpoca()    const { return epoca; }
    bool   necesitaSupv() const { return necesitaSupervizare; }

    void afisareDetalii() const override
    {
        Carte::afisareDetalii();
        cout << "  [ManuscrisRar] Epoca: " << epoca
             << " | Conditii: " << conditiiPastrare;
        if (necesitaSupervizare) cout << " | *NECESITA SUPERVIZARE STAFF*";
        cout << "\n";
    }

    int    getTimpImprumut()    const override { return 0; }    // nu se imprumuta
    double getTaxaDeteriorare() const override { return 5000.0; }
    double getTaxaIntarziere()  const override { return 50.0; }
    string getTipCarte()        const override { return "ManuscrisRar"; }
};

#endif // TIPURI_SPECIALE_H