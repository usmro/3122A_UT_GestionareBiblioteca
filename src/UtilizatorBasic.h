#ifndef UTILIZATOR_BASIC_H
#define UTILIZATOR_BASIC_H

#include "Utilizator.h"

class UtilizatorBasic : public Utilizator 
{
private:
    int luniValabilitateAbonament;

public:
    UtilizatorBasic(string _id, string _nume, string _prenume, string _contact, int _luniAbonament) : Utilizator(_id, _nume, _prenume, _contact, TipUtilizator::BASIC)
    {
        luniValabilitateAbonament = _luniAbonament;
    }

    int getLimitaImprumuturi() const override 
    { 
        return 2; 
    }

    double aplicaDiscountTaxe(double taxa) const override 
    { 
        return taxa; 
    }

    void afisareProfil() const override 
    {
        cout << "[BASIC - " << luniValabilitateAbonament << " luni] ";
        Utilizator::afisareProfil();
    }
};

#endif // UTILIZATOR_BASIC_H