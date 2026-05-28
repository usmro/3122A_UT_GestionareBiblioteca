#ifndef UTILIZATOR_STUDENT_H
#define UTILIZATOR_STUDENT_H
#include "Utilizator.h"

// -----------------------------------------------------------------------
// UtilizatorStudent — acces gratuit pe baza de legitimatie studenteasca
// Limita 5 carti, discount 20% la taxe de intarziere
// -----------------------------------------------------------------------
class UtilizatorStudent : public Utilizator
{
private:
    string facultate;
    int    anStudiu;
    string nrMatricol;

public:
    UtilizatorStudent(string id, string nume, string prenume,
                      string contact, string parola,
                      int an, int luna,
                      string fac, int anSt, string matr)
        : Utilizator(id, nume, prenume, contact, TipUtilizator::STUDENT,
                     parola, an, luna),
          facultate(fac), anStudiu(anSt), nrMatricol(matr)
    {
        adaugaEveniment(an, luna,
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
             << " | Matricol: " << nrMatricol
             << " | Gratuit | Discount taxe: 20%\n";
    }
};

#endif // UTILIZATOR_STUDENT_H