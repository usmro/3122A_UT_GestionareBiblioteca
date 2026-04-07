#ifndef UTILIZATOR_STUDENT_H
#define UTILIZATOR_STUDENT_H
#include "Utilizator.h"

class UtilizatorStudent : public Utilizator
{
private:
    Abonament abonament;
    string    facultate;
    int       anStudiu;
    string    nrMatricol;

public:
    UtilizatorStudent(string id, string nume, string prenume,
                      string contact, string parola,
                      int luniAb, int anStart, int lunaStart,
                      string fac, int anSt, string matr)
        : Utilizator(id, nume, prenume, contact, TipUtilizator::STUDENT, parola),
          abonament("Student", luniAb, 10.0, anStart, lunaStart),
          facultate(fac), anStudiu(anSt), nrMatricol(matr)
    {
        adaugaEveniment(anStart, lunaStart,
                        "Inscris ca Student - " + fac + ", An " + std::to_string(anSt));
    }

    string getFacultate()  const { return facultate; }
    int    getAnStudiu()   const { return anStudiu; }
    string getNrMatricol() const { return nrMatricol; }

    void promoveazaAnSuperior()
    {
        anStudiu++;
        adaugaEveniment(2025, 9, "Promovat in anul " + std::to_string(anStudiu));
    }

    int    getLimitaImprumuturi()          const override { return 5; }
    double aplicaDiscountTaxe(double taxa) const override { return taxa * 0.8; }
    string getTipNume()                    const override { return "STUDENT"; }

    void afisareDetalii() const override
    {
        Utilizator::afisareDetalii();
        cout << "  Facultate: " << facultate
             << " | An: " << anStudiu
             << " | Matricol: " << nrMatricol << "\n";
        abonament.afisare();
    }
};

#endif // UTILIZATOR_STUDENT_H