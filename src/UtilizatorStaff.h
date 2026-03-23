#ifndef UTILIZATOR_STAFF_H
#define UTILIZATOR_STAFF_H

#include "Utilizator.h"

class UtilizatorStaff : public Utilizator 
{
private:
    string departament;

public:
    UtilizatorStaff(string _id, string _nume, string _prenume, string _contact, string _dep) : Utilizator(_id, _nume, _prenume, _contact, TipUtilizator::STAFF) 
    {
        departament = _dep;
    }

    int getLimitaImprumuturi() const override
    { 
        return 15; 
    }

    double aplicaDiscountTaxe(double taxa) const override 
    { 
        return 0.0; 
    }

    bool areDreptDeAdmin() const override 
    { 
        return true; 
    }

    void afisareProfil() const override 
    {
        cout << "[STAFF - Dept: " << departament << "] ";
        Utilizator::afisareProfil();
    }
};

#endif // UTILIZATOR_STAFF_H