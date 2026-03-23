#ifndef CARTE_FICTIUNE_H
#define CARTE_FICTIUNE_H

#include "Carte.h"

class CarteFictiune : public Carte 
{ 
private:
    string genLiterar;
    int varstaMinima;

public:
    CarteFictiune(string t, string autor, string i, string ed, int an, TipCoperta c,string gen, int varsta) : Carte(t, autor, i, ed, an, c)
    {
        genLiterar = gen;
        varstaMinima = varsta;
    }

    void afisareDetalii() const override 
    {
        Carte::afisareDetalii();
        cout << "   [Fictiune] Gen: " << genLiterar << " | Varsta minima: " << varstaMinima << " ani\n";
    }

    int getTimpImprumut() const override 
    {
        return 14;
    }

    double getTaxaDeteriorare() const override 
    {
        return 35.0;
    }

    double getTaxaIntarziere() const override 
    {
        return 1.0;
    }
};

#endif // CARTE_FICTIUNE_H