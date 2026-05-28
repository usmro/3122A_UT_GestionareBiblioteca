#ifndef CARTE_TEHNICA_H
#define CARTE_TEHNICA_H
#include "Carte.h"

class CarteTehnica : public Carte
{
private:
    string domeniu;
    string nivelDificultate; // "Incepator", "Intermediar", "Avansat"
    bool   areResurseDigitale;

public:
    CarteTehnica(string isbn, string titlu,
                 vector<Autor*> autori, Editura* editura,
                 int an, LimbaCartii limba, TipCoperta coperta,
                 string dom, string dificultate, bool resurse,
                 int pagini = 0, double greutate = 0.0,
                 double pretCatalog = 0.0)
        : Carte(isbn, titlu, autori, editura, an, limba, coperta,
                pagini, greutate, "", 0, pretCatalog, dom),
          domeniu(dom), nivelDificultate(dificultate),
          areResurseDigitale(resurse)
    {}

    string getDomeniu()          const { return domeniu; }
    string getNivelDificultate() const { return nivelDificultate; }
    bool   getAreResurse()       const { return areResurseDigitale; }

    void afisareDetalii() const override
    {
        Carte::afisareDetalii();
        cout << "  [Tehnica] Domeniu: " << domeniu
             << " | Nivel: " << nivelDificultate;
        if (areResurseDigitale) cout << " | *Contine CD/Resurse digitale*";
        cout << "\n";
    }

    int    getTimpImprumut()    const override { return 28; }
    double getTaxaDeteriorare() const override { return 70.0; }
    double getTaxaIntarziere()  const override { return 2.0; }
    string getTipCarte()        const override { return "Tehnica"; }
};

#endif // CARTE_TEHNICA_H