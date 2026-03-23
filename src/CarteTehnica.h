#ifndef CARTE_TEHNICA_H
#define CARTE_TEHNICA_H

#include "Carte.h"

class CarteTehnica : public Carte 
{
private:
    string domeniu;
    string nivelDificultate;
    bool areResurseDigitale;

public:
    CarteTehnica(string t, vector<string> autori, string i, string ed, int an, TipCoperta c, string dom, string dificultate, bool resurse) : Carte(t, autori, i, ed, an, c)
    {
        domeniu = dom;
        nivelDificultate = dificultate;
        areResurseDigitale = resurse;
    }

    void afisareDetalii() const override 
    {
        Carte::afisareDetalii();
        cout << "   [Tehnica] Domeniu: " << domeniu << " | Nivel: " << nivelDificultate;
        if (areResurseDigitale) 
        {
            cout << " | Contine CD/Resurse digitale";
        }
        cout << "\n";
    }

    int getTimpImprumut() const override 
    {
        return 28;
    }

    double getTaxaDeteriorare() const override 
    {
        return 70.0;
    }

    double getTaxaIntarziere() const override 
    {
        return 2;
    }
};

#endif // CARTE_TEHNICA_H