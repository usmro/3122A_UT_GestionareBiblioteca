#ifndef CARTE_COPII_H
#define CARTE_COPII_H
#include "Carte.h"

class CarteCopii : public Carte
{
private:
    int    varstaRecomandata;
    string ilustrator;
    bool   areElementeInteractive;

public:
    CarteCopii(string isbn, string titlu,
               vector<Autor*> autori, Editura* editura,
               int an, LimbaCartii limba, TipCoperta coperta,
               int varsta, string ilustr, bool interactiv,
               int pagini = 0, double greutate = 0.0,
               double pretCatalog = 0.0)
        : Carte(isbn, titlu, autori, editura, an, limba, coperta,
                pagini, greutate, "", 0, pretCatalog),
          varstaRecomandata(varsta), ilustrator(ilustr),
          areElementeInteractive(interactiv)
    {}

    int    getVarsta()    const { return varstaRecomandata; }
    string getIlustrator() const { return ilustrator; }
    bool   areInteractiv() const { return areElementeInteractive; }

    void afisareDetalii() const override
    {
        Carte::afisareDetalii();
        cout << "  [Copii] Varsta: " << varstaRecomandata
             << "+ | Ilustrator: " << ilustrator;
        if (areElementeInteractive) cout << " | *Contine elemente interactive*";
        cout << "\n";
    }

    int    getTimpImprumut()    const override { return 14; }
    double getTaxaDeteriorare() const override { return 25.0; }
    double getTaxaIntarziere()  const override { return 0.5; }
    string getTipCarte()        const override { return "Copii"; }
};

#endif // CARTE_COPII_H