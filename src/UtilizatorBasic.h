#ifndef UTILIZATOR_BASIC_H
#define UTILIZATOR_BASIC_H
#include "Utilizator.h"

// -----------------------------------------------------------------------
// UtilizatorBasic — acces gratuit, limita 2 carti, fara discount taxe
// Diferentiere fata de Student: nu necesita legitimatie, limita mai mica
// -----------------------------------------------------------------------
class UtilizatorBasic : public Utilizator
{
public:
    UtilizatorBasic(string id, string nume, string prenume,
                    string contact, string parola,
                    int an = 2024, int luna = 1)
        : Utilizator(id, nume, prenume, contact, TipUtilizator::BASIC,
                     parola, an, luna)
    {
        adaugaEveniment(an, luna, "Inscris ca utilizator Basic");
    }

    int    getLimitaImprumuturi()          const override { return 2; }
    double aplicaDiscountTaxe(double taxa) const override { return taxa; }
    string getTipNume()                    const override { return "BASIC"; }

    void afisareDetalii() const override
    {
        Utilizator::afisareDetalii();
        cout << "  Tip: Basic | Gratuit | Limita: 2 carti\n";
    }
};

#endif // UTILIZATOR_BASIC_H