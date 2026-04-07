#ifndef MATERIALE_REFERINTA_H
#define MATERIALE_REFERINTA_H
#include "Carte.h"

// Nu se imprumuta - doar sala de lectura
class MaterialeReferinta : public Carte
{
private:
    string tipReferinta; // "Dictionar", "Atlas", "Enciclopedie"

public:
    MaterialeReferinta(string isbn, string titlu,
                       vector<Autor*> autori, Editura* editura,
                       int an, LimbaCartii limba, TipCoperta coperta,
                       string tip,
                       int pagini = 0, double greutate = 0.0,
                       double pretCatalog = 0.0)
        : Carte(isbn, titlu, autori, editura, an, limba, coperta,
                pagini, greutate, "", 0, pretCatalog),
          tipReferinta(tip)
    {}

    string getTipReferinta() const { return tipReferinta; }

    void afisareDetalii() const override
    {
        Carte::afisareDetalii();
        cout << "  [Referinta] Tip: " << tipReferinta
             << " | ATENTIE: Doar pentru sala de lectura!\n";
    }

    int    getTimpImprumut()    const override { return 0; }   // nu se imprumuta
    double getTaxaDeteriorare() const override { return 150.0; }
    double getTaxaIntarziere()  const override { return 5.0; }
    string getTipCarte()        const override { return "Referinta"; }
};

#endif // MATERIALE_REFERINTA_H