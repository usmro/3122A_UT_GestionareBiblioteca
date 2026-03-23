#ifndef UTILIZATOR_H
#define UTILIZATOR_H

#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;
using std::cout;

enum class TipUtilizator { BASIC, STUDENT, PREMIUM, STAFF };

class Utilizator 
{
protected:
    string id;
    string nume;
    string prenume;
    string contact;
    TipUtilizator tip;
    double taxeAcumulate;

public:
    Utilizator(string _id, string _nume, string _prenume, string _contact, TipUtilizator _tip) 
    {
        id = _id;
        nume = _nume;
        prenume = _prenume;
        contact = _contact;
        tip = _tip;
        taxeAcumulate = 0.0;
    }

    virtual ~Utilizator() = default;

    string getId() const 
    { 
        return id;
    }
    string getNume() const 
    { 
        return nume; 
    }

    double getTaxeAcumulate() const 
    { 
        return taxeAcumulate; 
    }

    void adaugaTaxa(double suma) 
    { 
        taxeAcumulate += suma; 
    }

    void platesteTaxa(double suma) 
    { 
        taxeAcumulate -= suma; 
        if(taxeAcumulate < 0) 
            taxeAcumulate = 0; 
    }

    virtual int getLimitaImprumuturi() const = 0;
    virtual double aplicaDiscountTaxe(double taxaCalculata) const = 0; 
    virtual bool areDreptDeAdmin() const 
    { 
        return false; 
    }

    virtual void afisareProfil() const 
    {
        cout << "ID: " << id << " | Nume: " << nume << " " << prenume 
             << " | Contact: " << contact << " | Taxe: " << taxeAcumulate << " RON\n";
    }
};

#endif // UTILIZATOR_H