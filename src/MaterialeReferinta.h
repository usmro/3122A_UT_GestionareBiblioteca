#ifndef MATERIALE_REFERINTA_H
#define MATERIALE_REFERINTA_H

#include "Carte.h"

class MaterialeReferinta : public Carte 
{
private:
    string tipReferinta;

public:
    MaterialeReferinta(string t, string autor, string i, string ed, int an, TipCoperta c, string tip) : Carte(t, autor, i, ed, an, c) 
    {
        tipReferinta = tip;
    }

    void afisareDetalii() const override 
    {
        Carte::afisareDetalii();
        cout << "   [Referinta] Tip: " << tipReferinta << " (ATENTIE: Doar pentru sala de lectura!)\n";
    }

    int getTimpImprumut() const override 
    {
        return 0;
    }

    double getTaxaDeteriorare() const override 
    {
        return 150.0;
    }

    double getTaxaIntarziere() const override 
    {
        return 5.0;
    }
};

#endif // MATERIALE_REFERINTA_H