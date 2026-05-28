#ifndef CARTE_FICTIUNE_H
#define CARTE_FICTIUNE_H
#include "Carte.h"

class CarteFictiune : public Carte
{
private:
    string genLiterar;
    int    varstaMinima;

public:
    CarteFictiune(string isbn, string titlu,
                  vector<Autor*> autori, Editura* editura,
                  int an, LimbaCartii limba, TipCoperta coperta,
                  string gen, int varsta,
                  int pagini = 0, double greutate = 0.0,
                  string serie = "", int volum = 0,
                  double pretCatalog = 0.0)
        : Carte(isbn, titlu, autori, editura, an, limba, coperta,
                pagini, greutate, serie, volum, pretCatalog, gen),
          genLiterar(gen), varstaMinima(varsta)
    {}

    string getGenLiterar()  const { return genLiterar; }
    int    getVarstaMinima() const { return varstaMinima; }

    void afisareDetalii() const override
    {
        Carte::afisareDetalii();
        cout << "  [Fictiune] Gen: " << genLiterar
             << " | Varsta min: " << varstaMinima << " ani\n";
    }

    int    getTimpImprumut()    const override { return 14; }
    double getTaxaDeteriorare() const override { return 35.0; }
    double getTaxaIntarziere()  const override { return 1.0; }
    string getTipCarte()        const override { return "Fictiune"; }
};

#endif // CARTE_FICTIUNE_H