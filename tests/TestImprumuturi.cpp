#include <iostream>
#include <string>
#include <cassert>

#include "../src/Biblioteca.h"
#include "../src/CarteFictiune.h"
#include "../src/CarteTehnica.h"
#include "../src/UtilizatorBasic.h"
#include "../src/UtilizatorStudent.h"
#include "../src/UtilizatorPremium.h"
#include "../src/UtilizatorStaff.h"

using std::cout;
using std::string;

static int nrTeste   = 0;
static int nrTrecute = 0;

void check(bool conditie, const string& numTest)
{
    nrTeste++;
    if (conditie) { nrTrecute++; cout << "  [PASS] " << numTest << "\n"; }
    else          {              cout << "  [FAIL] " << numTest << "\n"; }
}

// Helper: creeaza o biblioteca cu o carte si un exemplar
struct SetupImprumut
{
    Biblioteca  bib;
    Autor*      autor;
    Editura*    editura;

    SetupImprumut() : bib("TestBib", 2024)
    {
        autor   = bib.gasesteOrAdaugaAutor("Test","Autor","RO",1990,true);
        editura = bib.gasesteOrAdaugaEditura("TestEd","RO","Iasi");
    }

    string adaugaCarte(const string& isbn, const string& titlu)
    {
        CarteFictiune* c = new CarteFictiune(
            isbn, titlu, {autor}, editura,
            2020, LimbaCartii::ROMANA, TipCoperta::BROSATA, "SF", 0);
        bib.adaugaCarte(c);
        return bib.adaugaExemplarLaCarte(isbn,"A","S1","R1","SF");
    }
};

// -----------------------------------------------------------------------
// T01 — Imprumut simplu: utilizatorul are cartea in lista
// -----------------------------------------------------------------------
void test_imprumut_simplu()
{
    cout << "\n[T01] Imprumut simplu\n";

    SetupImprumut s;
    s.adaugaCarte("ISBN-I01","Carte I01");

    UtilizatorBasic* u = new UtilizatorBasic(
        "U-I01","Test","User","t@t.ro","p",6,2024,1);
    s.bib.adaugaUtilizator(u);

    check(u->getNrImprumuturi() == 0, "inainte: 0 imprumuturi");
    s.bib.imprumutaCarte("U-I01","ISBN-I01",1,4,2024);
    check(u->getNrImprumuturi() == 1, "dupa imprumut: 1 imprumut");
    check(u->poateImprumuta()   == false, "Basic atins limita 1/2... poate inca");
}

// -----------------------------------------------------------------------
// T02 — Limita Basic (2 carti)
// -----------------------------------------------------------------------
void test_limita_basic()
{
    cout << "\n[T02] Limita imprumut Basic (2 carti)\n";

    SetupImprumut s;
    s.adaugaCarte("ISBN-B01","Carte B01");
    s.adaugaCarte("ISBN-B02","Carte B02");
    s.adaugaCarte("ISBN-B03","Carte B03");

    UtilizatorBasic* u = new UtilizatorBasic(
        "U-B01","Basic","User","b@b.ro","p",6,2024,1);
    s.bib.adaugaUtilizator(u);

    s.bib.imprumutaCarte("U-B01","ISBN-B01",1,4,2024);
    s.bib.imprumutaCarte("U-B01","ISBN-B02",1,4,2024);
    check(u->getNrImprumuturi() == 2, "Basic are 2 imprumuturi");
    check(u->poateImprumuta()   == false, "Basic nu mai poate imprumuta");

    bool exceptiePrinsa = false;
    try {
        s.bib.imprumutaCarte("U-B01","ISBN-B03",1,4,2024);
    } catch (const LimitaDepastitaException&) {
        exceptiePrinsa = true;
    }
    check(exceptiePrinsa, "al 3-lea imprumut arunca LimitaDepastitaException");
}

// -----------------------------------------------------------------------
// T03 — Limita Student (5 carti)
// -----------------------------------------------------------------------
void test_limita_student()
{
    cout << "\n[T03] Limita imprumut Student (5 carti)\n";

    SetupImprumut s;
    for (int i = 1; i <= 6; i++)
    {
        string isbn = "ISBN-S0" + std::to_string(i);
        string titlu = "Carte S0" + std::to_string(i);
        s.adaugaCarte(isbn, titlu);
    }

    UtilizatorStudent* u = new UtilizatorStudent(
        "U-S01","Student","User","s@s.ro","p",
        12,2024,1,"FIESC",1,"MAT001");
    s.bib.adaugaUtilizator(u);

    for (int i = 1; i <= 5; i++)
        s.bib.imprumutaCarte("U-S01","ISBN-S0"+std::to_string(i),1,4,2024);

    check(u->getNrImprumuturi() == 5, "Student are 5 imprumuturi");
    check(u->poateImprumuta()   == false, "Student nu mai poate imprumuta");

    bool exceptiePrinsa = false;
    try {
        s.bib.imprumutaCarte("U-S01","ISBN-S06",1,4,2024);
    } catch (const LimitaDepastitaException&) {
        exceptiePrinsa = true;
    }
    check(exceptiePrinsa, "al 6-lea imprumut Student arunca exceptie");
}

// -----------------------------------------------------------------------
// T04 — Returnare elibereaza slot pentru alt imprumut
// -----------------------------------------------------------------------
void test_returnare_elibereaza_slot()
{
    cout << "\n[T04] Returnare elibereaza slot\n";

    SetupImprumut s;
    string cod1 = s.adaugaCarte("ISBN-R01","Carte R01");
    s.adaugaCarte("ISBN-R02","Carte R02");
    s.adaugaCarte("ISBN-R03","Carte R03");

    UtilizatorBasic* u = new UtilizatorBasic(
        "U-R01","Return","User","r@r.ro","p",6,2024,1);
    s.bib.adaugaUtilizator(u);

    s.bib.imprumutaCarte("U-R01","ISBN-R01",1,4,2024);
    s.bib.imprumutaCarte("U-R01","ISBN-R02",1,4,2024);
    check(u->poateImprumuta() == false, "Basic la limita dupa 2 imprumuturi");

    s.bib.returneazaCarte("U-R01", cod1, 0);
    check(u->getNrImprumuturi() == 1, "dupa returnare: 1 imprumut activ");
    check(u->poateImprumuta()   == true, "dupa returnare: poate imprumuta din nou");

    // Poate imprumuta o noua carte
    s.bib.imprumutaCarte("U-R01","ISBN-R03",2,4,2024);
    check(u->getNrImprumuturi() == 2, "dupa nou imprumut: 2 active");
}

// -----------------------------------------------------------------------
// T05 — Utilizator inexistent arunca exceptie
// -----------------------------------------------------------------------
void test_utilizator_inexistent()
{
    cout << "\n[T05] Utilizator inexistent\n";

    SetupImprumut s;
    s.adaugaCarte("ISBN-UX1","Carte UX1");

    bool exceptiePrinsa = false;
    try {
        s.bib.imprumutaCarte("U-INEXISTENT","ISBN-UX1",1,4,2024);
    } catch (const UtilizatorInexistentException&) {
        exceptiePrinsa = true;
    }
    check(exceptiePrinsa, "utilizator inexistent arunca UtilizatorInexistentException");
}

// -----------------------------------------------------------------------
// T06 — Carte fara exemplare disponibile arunca exceptie
// -----------------------------------------------------------------------
void test_carte_fara_exemplare()
{
    cout << "\n[T06] Carte fara exemplare disponibile\n";

    SetupImprumut s;
    // Adaugam cartea DAR nu adaugam niciun exemplar
    CarteFictiune* c = new CarteFictiune(
        "ISBN-FE1","Fara Exemplare",{s.autor},s.editura,
        2020,LimbaCartii::ROMANA,TipCoperta::BROSATA,"SF",0);
    s.bib.adaugaCarte(c);

    UtilizatorBasic* u = new UtilizatorBasic(
        "U-FE1","Fara","Exemplare","fe@fe.ro","p",6,2024,1);
    s.bib.adaugaUtilizator(u);

    bool exceptiePrinsa = false;
    try {
        s.bib.imprumutaCarte("U-FE1","ISBN-FE1",1,4,2024);
    } catch (const CarteLipsaException&) {
        exceptiePrinsa = true;
    }
    check(exceptiePrinsa, "carte fara exemplare arunca CarteLipsaException");
}

// -----------------------------------------------------------------------
// T07 — Staff nu plateste taxe (aplicaDiscountTaxe = 0)
// -----------------------------------------------------------------------
void test_staff_fara_taxe()
{
    cout << "\n[T07] Staff scutit de taxe\n";

    UtilizatorStaff* staff = new UtilizatorStaff(
        "STAFF-TX","Marin","Ana","a@bib.ro","p",
        "Sectia A", RolStaff::BIBLIOTECAR, 4000.0, 2020, 1);

    double taxaBruta = 50.0;
    double taxaFinala = staff->aplicaDiscountTaxe(taxaBruta);

    check(taxaFinala == 0.0, "Staff: taxa finala = 0.0 RON");
    check(staff->areDreptDeAdmin() == true, "Staff are drept de admin");

    delete staff;
}

// -----------------------------------------------------------------------
// T08 — Discount student 20%
// -----------------------------------------------------------------------
void test_discount_student()
{
    cout << "\n[T08] Discount Student 20%\n";

    UtilizatorStudent* u = new UtilizatorStudent(
        "U-DS","Pop","Ion","i@i.ro","p",
        12,2024,1,"FIESC",1,"M001");

    double taxa = u->aplicaDiscountTaxe(10.0);
    check(taxa == 8.0, "Student: 10 RON brut -> 8 RON (20% discount)");

    taxa = u->aplicaDiscountTaxe(25.0);
    check(taxa == 20.0, "Student: 25 RON brut -> 20 RON (20% discount)");

    delete u;
}

// -----------------------------------------------------------------------
// T09 — Discount Premium 40%
// -----------------------------------------------------------------------
void test_discount_premium()
{
    cout << "\n[T09] Discount Premium 40%\n";

    UtilizatorPremium* u = new UtilizatorPremium(
        "U-DP","Popa","Elena","e@e.ro","p",24,2024,1);

    double taxa = u->aplicaDiscountTaxe(10.0);
    check(taxa == 6.0, "Premium: 10 RON brut -> 6 RON (40% discount)");

    taxa = u->aplicaDiscountTaxe(50.0);
    check(taxa == 30.0, "Premium: 50 RON brut -> 30 RON (40% discount)");

    delete u;
}

// -----------------------------------------------------------------------
// T10 — Taxa se adauga corect la utilizator
// -----------------------------------------------------------------------
void test_taxa_acumulata()
{
    cout << "\n[T10] Acumulare si plata taxe\n";

    SetupImprumut s;
    string cod = s.adaugaCarte("ISBN-TX1","Carte TX1");

    UtilizatorBasic* u = new UtilizatorBasic(
        "U-TX1","Taxa","Test","tx@tx.ro","p",6,2024,1);
    s.bib.adaugaUtilizator(u);

    s.bib.imprumutaCarte("U-TX1","ISBN-TX1",1,4,2024);
    // CarteFictiune: 1.0 RON/zi, Basic fara discount
    s.bib.returneazaCarte("U-TX1", cod, 5); // 5 zile intarziere

    check(u->getTaxeAcumulate() == 5.0, "5 zile * 1.0 RON = 5.0 RON acumulat");

    s.bib.incaseazaTaxa("U-TX1", 5.0);
    check(u->getTaxeAcumulate() == 0.0, "dupa plata: taxe = 0.0 RON");
}

// -----------------------------------------------------------------------
// MAIN
// -----------------------------------------------------------------------
int main()
{
    cout << "============================================================\n";
    cout << "  TESTE UNITARE: IMPRUMUTURI, LIMITE SI TAXE\n";
    cout << "============================================================\n";

    test_imprumut_simplu();
    test_limita_basic();
    test_limita_student();
    test_returnare_elibereaza_slot();
    test_utilizator_inexistent();
    test_carte_fara_exemplare();
    test_staff_fara_taxe();
    test_discount_student();
    test_discount_premium();
    test_taxa_acumulata();

    cout << "\n============================================================\n";
    cout << "  REZULTAT: " << nrTrecute << " / " << nrTeste << " teste trecute\n";
    cout << "============================================================\n";

    return (nrTrecute == nrTeste) ? 0 : 1;
}