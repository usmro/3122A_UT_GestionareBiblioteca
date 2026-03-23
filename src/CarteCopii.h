#ifndef CARTE_COPII_H
#define CARTE_COPII_H

#include "Carte.h"

class CarteCopii : public Carte 
{
private:
    int varstaRecomandata;
    string ilustrator;
    bool areElementeInteractive;

public:
    CarteCopii(string t, string autor, string i, string ed, int an, TipCoperta c, int varsta, string ilustr, bool interactiv) : Carte(t, autor, i, ed, an, c) 
    {
        varstaRecomandata = varsta;
        ilustrator = ilustr;
        areElementeInteractive = interactiv;
    }

    void afisareDetalii() const override 
    {
        Carte::afisareDetalii();
        cout << "   [Copii] Varsta: " << varstaRecomandata << "+ | Ilustrator: " << ilustrator;
        if (areElementeInteractive) {
            cout << " | *Contine elemente interactive/jucarii*";
        }
        cout << "\n";
    }

    int getTimpImprumut() const override 
    { 
        return 14; 
    }

    double getTaxaDeteriorare() const override 
    { 
        return 25.0; 
    }

    double getTaxaIntarziere() const override 
    { 
        return 0.5; 
    }
};

#endif // CARTE_COPII_H