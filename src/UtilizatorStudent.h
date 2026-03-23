#ifndef UTILIZATOR_STUDENT_H
#define UTILIZATOR_STUDENT_H

#include "Utilizator.h"

class UtilizatorStudent : public Utilizator 
{
private:
    int luniValabilitateAbonament;
    string facultate;
    int anStudiu;
    string nrMatricol;

public:
    UtilizatorStudent(string _id, string _nume, string _prenume, string _contact, int _luniAb, string _fac, int _an, string _matr) : Utilizator(_id, _nume, _prenume, _contact, TipUtilizator::STUDENT) 
    {
        luniValabilitateAbonament = _luniAb;
        facultate = _fac;
        anStudiu = _an;
        nrMatricol = _matr;
    }

    int getLimitaImprumuturi() const override 
    { 
        return 5; 
    }

    double aplicaDiscountTaxe(double taxa) const override 
    { 
        return taxa * 0.8; 
    }

    void afisareProfil() const override 
    {
        cout << "[STUDENT - " << facultate << " | An " << anStudiu << " | Matr: " << nrMatricol << "] ";
        Utilizator::afisareProfil();
    }
};

#endif // UTILIZATOR_STUDENT_H