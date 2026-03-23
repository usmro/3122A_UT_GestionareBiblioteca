#ifndef UTILIZATOR_PREMIUM_H
#define UTILIZATOR_PREMIUM_H

#include "Utilizator.h"

class UtilizatorPremium : public Utilizator 
{
private:
    int luniValabilitateAbonament;

public:
    UtilizatorPremium(string _id, string _nume, string _prenume, string _contact, int _luniAbonament) : Utilizator(_id, _nume, _prenume, _contact, TipUtilizator::PREMIUM) 
    {
        luniValabilitateAbonament = _luniAbonament;
    }

    int getLimitaImprumuturi() const override
    { 
        return 10; 
    }

    double aplicaDiscountTaxe(double taxa) const override 
    { 
        return taxa * 0.6; 
    }

    void afisareProfil() const override
    {
        cout << "[PREMIUM - VIP " << luniValabilitateAbonament << " luni] ";
        Utilizator::afisareProfil();
    }
};

#endif // UTILIZATOR_PREMIUM_H