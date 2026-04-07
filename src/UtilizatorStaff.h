#ifndef UTILIZATOR_STAFF_H
#define UTILIZATOR_STAFF_H
#include "Utilizator.h"

enum class RolStaff
{
    BIBLIOTECAR,
    BIBLIOTECAR_SEF,
    ADMINISTRATOR,
    CASIER,
    ARHIVAR
};

struct ContractAngajare
{
    double salariu;
    int    anAngajare;
    int    lunaAngajare;
    int    zileConcediuAnual;
    int    zileConcediuRamase;

    ContractAngajare(double sal, int an, int luna, int concediu = 21)
        : salariu(sal), anAngajare(an), lunaAngajare(luna),
          zileConcediuAnual(concediu), zileConcediuRamase(concediu)
    {}

    void afisare() const
    {
        cout << "  Contract: " << salariu << " RON/luna"
             << " | Angajat: " << lunaAngajare << "/" << anAngajare
             << " | Concediu: " << zileConcediuRamase
             << "/" << zileConcediuAnual << " zile\n";
    }
};

class UtilizatorStaff : public Utilizator
{
private:
    string           departament;
    RolStaff         rol;
    ContractAngajare contract;
    bool             estePensionat;

public:
    UtilizatorStaff(string id, string nume, string prenume,
                    string contact, string parola,
                    string dep, RolStaff _rol,
                    double salariu, int anAng, int lunaAng)
        : Utilizator(id, nume, prenume, contact, TipUtilizator::STAFF, parola),
          departament(dep), rol(_rol),
          contract(salariu, anAng, lunaAng),
          estePensionat(false)
    {
        adaugaEveniment(anAng, lunaAng,
                        "Angajat ca " + rolToString() + " in " + dep);
    }

    string           getDepartament() const { return departament; }
    RolStaff         getRol()         const { return rol; }
    ContractAngajare getContract()    const { return contract; }
    bool             isPensionat()    const { return estePensionat; }

    void pensionare(int an, int luna)
    {
        estePensionat = true;
        adaugaEveniment(an, luna, "Pensionat din functia de " + rolToString());
    }

    bool luaConcediu(int zile)
    {
        if (contract.zileConcediuRamase >= zile)
        {
            contract.zileConcediuRamase -= zile;
            return true;
        }
        return false;
    }

    // Staff are drepturi diferite in functie de rol
    bool poateAdaugaCarte()   const { return rol != RolStaff::CASIER; }
    bool poateStergeCarte()   const { return rol == RolStaff::ADMINISTRATOR ||
                                             rol == RolStaff::BIBLIOTECAR_SEF; }
    bool poateGestionaStaff() const { return rol == RolStaff::ADMINISTRATOR; }

    int    getLimitaImprumuturi()          const override { return 15; }
    double aplicaDiscountTaxe(double)      const override { return 0.0; }
    bool   areDreptDeAdmin()               const override { return true; }
    string getTipNume()                    const override { return "STAFF"; }

    void afisareDetalii() const override
    {
        Utilizator::afisareDetalii();
        cout << "  Departament: " << departament
             << " | Rol: " << rolToString();
        if (estePensionat) cout << " [PENSIONAT]";
        cout << "\n";
        contract.afisare();
    }

private:
    string rolToString() const
    {
        switch (rol)
        {
            case RolStaff::BIBLIOTECAR:     return "Bibliotecar";
            case RolStaff::BIBLIOTECAR_SEF: return "Bibliotecar Sef";
            case RolStaff::ADMINISTRATOR:   return "Administrator";
            case RolStaff::CASIER:          return "Casier";
            case RolStaff::ARHIVAR:         return "Arhivar";
            default:                        return "Staff";
        }
    }
};

#endif // UTILIZATOR_STAFF_H