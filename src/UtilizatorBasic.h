#ifndef UTILIZATOR_BASIC_H
#define UTILIZATOR_BASIC_H
#include "Utilizator.h"

class UtilizatorBasic : public Utilizator
{
private:
    Abonament abonament;

public:
    UtilizatorBasic(string id, string nume, string prenume,
                    string contact, string parola,
                    int luniAb, int anStart, int lunaStart)
        : Utilizator(id, nume, prenume, contact, TipUtilizator::BASIC, parola),
          abonament("Basic", luniAb, 15.0, anStart, lunaStart)
    {
        adaugaEveniment(anStart, lunaStart, "Inscris ca utilizator Basic");
    }

    const Abonament& getAbonament() const { return abonament; }

    int    getLimitaImprumuturi()          const override { return 2; }
    double aplicaDiscountTaxe(double taxa) const override { return taxa; }
    string getTipNume()                    const override { return "BASIC"; }

    void afisareDetalii() const override
    {
        Utilizator::afisareDetalii();
        abonament.afisare();
    }
};

#endif // UTILIZATOR_BASIC_H