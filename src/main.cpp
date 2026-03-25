#include <iostream>
#include <vector>
#include <string>

#include "CarteFictiune.h"
#include "CarteTehnica.h"
#include "CarteEducativa.h"
#include "CarteCopii.h"
#include "MaterialeReferinta.h"
#include "UtilizatorBasic.h"
#include "UtilizatorStudent.h"
#include "UtilizatorPremium.h"
#include "UtilizatorStaff.h"

using std::cout;
using std::string;
using std::vector;

int main() 
{
    cout << "=== TESTARE LIVRABIL 1: CLASE SI MOSTENIRE ===\n";

    // 1. Testăm Moștenirea pentru clasa CARTE
    cout << "=== 1. Testare ierarhie Carte ===\n\n";

    CarteFictiune carte1("Dune", "Frank Herbert", "ISBN-111", "Nemira", 2020, TipCoperta::BROSATA, "SF", 12);
    cout << "[Fictiune] Titlu: " << carte1.getTitlu() << "\n";
    cout << "[Fictiune] Autor: " << carte1.getAutori()[0] << "\n";//metode din baza
    cout << "[Fictiune] Taxa intarziere: " << carte1.getTaxaIntarziere() << " RON/zi\n\n";//metoda suprascrisa din clasa derivata

    vector<string> autoriTech = {"Robert C. Martin"};
    CarteTehnica carte2("Clean Code", autoriTech, "ISBN-222", "Prentice Hall", 2008, TipCoperta::BROSATA, "IT", "Avansat", false);
    cout << "[Tehnica] Titlu: " << carte2.getTitlu() << "\n"; // metoda din baza
    cout << "[Tehnica] Taxa intarziere: " << carte2.getTaxaIntarziere() << " RON/zi\n\n"; //metoda suprascrisa din clasa derivata

    MaterialeReferinta carte3("Atlas Geografic", "Ioan Popovici", "ISBN-333", "Didactica", 2019, TipCoperta::CARTONATA, "Atlas");
    cout << "[Referinta] Titlu: " << carte3.getTitlu() << "\n"; // metoda din baza
    cout << "[Referinta] Timp max de imprumut: " << carte3.getTimpImprumut() << " zile\n\n"; //metoda suprascrisa din clasa derivata

    // 2. Testăm Moștenirea pentru clasa UTILIZATOR
    cout << "=== 2. Testare ierarhie Utilizator ===\n\n";

    UtilizatorStudent student1("U-101", "Enescu", "Ana", "ana@student.usv.ro", 6, "FIESC", 2, "MAT123");
    cout << "[Student] Nume student: " << student1.getNume() << " " << student1.getPrenume() << "\n";
    student1.adaugaTaxa(15.5);
    cout << "[Student] Taxe acumulate: " << student1.getTaxeAcumulate() << " RON\n";//metode din baza
    cout << "[Student] Limita carti permise: " << student1.getLimitaImprumuturi() << " carti\n\n";//metoda metoda suprascrisa din clasa derivata

    UtilizatorPremium premium1("PR-001", "Popa", "Elena", "0747 826 408", 24);
    cout << "[Premium] Nume abonat: " << premium1.getNume() << " " << premium1.getPrenume() << "\n"; // metode din baza
    cout << "[Premium] Limita carti permise: " << premium1.getLimitaImprumuturi() << " carti\n\n"; // metoda din clasa derivata

    UtilizatorStaff staff1("STAFF-01", "Marin", "Andreea", "a.marin@usv.ro", "Bibliotecar Sef");
    cout << "[Staff] Nume angajat: " << staff1.getNume() << " " << staff1.getPrenume() << "\n"; // metode din baza
    cout << "[Staff] Discount taxe: o taxa de 10 RON devine " << staff1.aplicaDiscountTaxe(10.0) << " RON\n"; // metoda din clasa derivata
    cout << "[Staff] Are drept de admin?: " << (staff1.areDreptDeAdmin() ? "DA" : "NU") << "\n"; // metoda din clasa derivata

    cout << "\n============================================\n";

    return 0;
}