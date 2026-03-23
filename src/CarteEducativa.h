#ifndef CARTE_EDUCATIVA_H
#define CARTE_EDUCATIVA_H

#include "Carte.h"

class CarteEducativa : public Carte 
{
private:
    string materie;
    string profil;
    int clasa;

public:
    CarteEducativa(string t, string autor, string i, string ed, int an, TipCoperta c, string mat, string prof, int cl) : Carte(t, autor, i, ed, an, c) 
    {
        materie = mat;
        profil = prof;
        clasa = cl;
    }

    void afisareDetalii() const override 
    {
        Carte::afisareDetalii();
        cout << "   [Educativa] Materie: " << materie 
             << " | Profil: " << profil 
             << " | Clasa: a " << clasa << "-a\n";
    }

    int getTimpImprumut() const override 
    {
        return 30;
    }

    double getTaxaDeteriorare() const override
    {
        return 40.0;
    }

    double getTaxaIntarziere() const override
    {
        return 1.5; 
    }
};

#endif // CARTE_EDUCATIVA_H