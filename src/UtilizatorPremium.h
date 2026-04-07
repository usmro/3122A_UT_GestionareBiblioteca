#ifndef UTILIZATOR_PREMIUM_H
#define UTILIZATOR_PREMIUM_H
#include "Utilizator.h"

class UtilizatorPremium : public Utilizator
{
private:
    Abonament abonament;

public:
    UtilizatorPremium(string id, string nume, string prenume,
                      string contact, string parola,
                      int luniAb, int anStart, int lunaStart)
        : Utilizator(id, nume, prenume, contact, TipUtilizator::PREMIUM, parola),
          abonament("Premium", luniAb, 40.0, anStart, lunaStart)
    {
        adaugaEveniment(anStart, lunaStart, "Inscris ca utilizator Premium");
    }

    int    getLimitaImprumuturi()          const override { return 10; }
    double aplicaDiscountTaxe(double taxa) const override { return taxa * 0.6; }
    string getTipNume()                    const override { return "PREMIUM"; }

    void afisareDetalii() const override
    {
        Utilizator::afisareDetalii();
        abonament.afisare();
    }
};

#endif // UTILIZATOR_PREMIUM_H