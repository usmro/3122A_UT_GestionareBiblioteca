#include <iostream>
#include <string>
#include <cassert>

#include "../src/Biblioteca.h"
#include "../src/CarteFictiune.h"
#include "../src/CarteTehnica.h"
#include "../src/MaterialeReferinta.h"
#include "../src/TipuriSpeciale.h"
#include "../src/UtilizatorBasic.h"
#include "../src/UtilizatorStudent.h"

using std::cout;
using std::string;

// -----------------------------------------------------------------------
// Utilitar: afiseaza rezultatul unui test
// -----------------------------------------------------------------------
static int nrTeste = 0;
static int nrTrecute = 0;

void check(bool conditie, const string& numTest)
{
    nrTeste++;
    if (conditie)
    {
        nrTrecute++;
        cout << "  [PASS] " << numTest << "\n";
    }
    else
    {
        cout << "  [FAIL] " << numTest << "\n";
    }
}

// -----------------------------------------------------------------------
// T01 — Carte fara exemplare: nrExemplareTotal = 0
// -----------------------------------------------------------------------
void test_stoc_initial_zero()
{
    cout << "\n[T01] Stoc initial zero\n";

    Biblioteca bib("Test", 2024);
    Autor* a = bib.gasesteOrAdaugaAutor("Test","Autor","RO",1990,true);
    Editura* e = bib.gasesteOrAdaugaEditura("TestEd","RO","Iasi");

    CarteFictiune* c = new CarteFictiune(
        "ISBN-T01", "Carte Test",
        {a}, e, 2020, LimbaCartii::ROMANA, TipCoperta::BROSATA,
        "SF", 12);

    bib.adaugaCarte(c);

    check(c->nrExemplareTotal()      == 0, "nrExemplareTotal = 0 fara exemplare");
    check(c->nrExemplareDisponibile() == 0, "nrExemplareDisponibile = 0 fara exemplare");
    check(c->getPrimulDisponibil()    == nullptr, "getPrimulDisponibil = nullptr");
}

// -----------------------------------------------------------------------
// T02 — Adaugare exemplare: contorul creste corect
// -----------------------------------------------------------------------
void test_adaugare_exemplare()
{
    cout << "\n[T02] Adaugare exemplare\n";

    Biblioteca bib("Test", 2024);
    Autor* a = bib.gasesteOrAdaugaAutor("Test","Autor","RO",1990,true);
    Editura* e = bib.gasesteOrAdaugaEditura("TestEd","RO","Iasi");

    CarteFictiune* c = new CarteFictiune(
        "ISBN-T02", "Carte Test 2",
        {a}, e, 2020, LimbaCartii::ROMANA, TipCoperta::BROSATA,
        "SF", 12);
    bib.adaugaCarte(c);

    bib.adaugaExemplarLaCarte("ISBN-T02", "Cladirea A", "Sala 1", "R01", "SF");
    check(c->nrExemplareTotal()       == 1, "dupa 1 exemplar: total = 1");
    check(c->nrExemplareDisponibile() == 1, "dupa 1 exemplar: disponibile = 1");

    bib.adaugaExemplarLaCarte("ISBN-T02", "Cladirea A", "Sala 1", "R01", "SF");
    check(c->nrExemplareTotal()       == 2, "dupa 2 exemplare: total = 2");
    check(c->nrExemplareDisponibile() == 2, "dupa 2 exemplare: disponibile = 2");

    bib.adaugaExemplarLaCarte("ISBN-T02", "Cladirea B", "Sala 2", "R05", "SF");
    check(c->nrExemplareTotal()       == 3, "dupa 3 exemplare: total = 3");
}

// -----------------------------------------------------------------------
// T03 — Cod unic generat corect (format BIB-YYYY-NNNNN)
// -----------------------------------------------------------------------
void test_cod_unic_format()
{
    cout << "\n[T03] Format cod unic exemplar\n";

    Biblioteca bib("Test", 2024);
    Autor* a = bib.gasesteOrAdaugaAutor("Test","Autor","RO",1990,true);
    Editura* e = bib.gasesteOrAdaugaEditura("TestEd","RO","Iasi");

    CarteFictiune* c = new CarteFictiune(
        "ISBN-T03", "Carte T03",
        {a}, e, 2020, LimbaCartii::ROMANA, TipCoperta::BROSATA, "SF", 0);
    bib.adaugaCarte(c);

    string cod1 = bib.adaugaExemplarLaCarte("ISBN-T03","A","S1","R1","X");
    string cod2 = bib.adaugaExemplarLaCarte("ISBN-T03","A","S1","R1","X");

    // Verifica prefix BIB-2024-
    check(cod1.substr(0, 8) == "BIB-2024", "cod1 incepe cu BIB-2024");
    check(cod2.substr(0, 8) == "BIB-2024", "cod2 incepe cu BIB-2024");

    // Verifica ca sunt diferite
    check(cod1 != cod2, "codurile sunt unice (diferite intre ele)");

    // Verifica lungimea: BIB-2024-00001 = 14 caractere
    check(cod1.length() == 14, "lungime cod = 14 caractere");
}

// -----------------------------------------------------------------------
// T04 — Status exemplar se schimba la imprumut/returnare
// -----------------------------------------------------------------------
void test_status_exemplar_imprumut()
{
    cout << "\n[T04] Status exemplar la imprumut si returnare\n";

    Biblioteca bib("Test", 2024);
    Autor* a = bib.gasesteOrAdaugaAutor("Test","Autor","RO",1990,true);
    Editura* e = bib.gasesteOrAdaugaEditura("TestEd","RO","Iasi");

    CarteFictiune* c = new CarteFictiune(
        "ISBN-T04", "Carte T04",
        {a}, e, 2020, LimbaCartii::ROMANA, TipCoperta::BROSATA, "SF", 0);
    bib.adaugaCarte(c);

    string cod = bib.adaugaExemplarLaCarte("ISBN-T04","A","S1","R1","X");

    UtilizatorBasic* u = new UtilizatorBasic(
        "U-T04","Test","User","test@test.ro","pass",6,2024,1);
    bib.adaugaUtilizator(u);

    check(c->nrExemplareDisponibile() == 1, "inainte de imprumut: 1 disponibil");

    bib.imprumutaCarte("U-T04", "ISBN-T04", 1, 4, 2024);
    check(c->nrExemplareDisponibile() == 0, "dupa imprumut: 0 disponibile");

    bib.returneazaCarte("U-T04", cod, 0);
    check(c->nrExemplareDisponibile() == 1, "dupa returnare: 1 disponibil");
}

// -----------------------------------------------------------------------
// T05 — Disponibilitate cu exemplare multiple
// -----------------------------------------------------------------------
void test_disponibilitate_exemplare_multiple()
{
    cout << "\n[T05] Disponibilitate cu exemplare multiple\n";

    Biblioteca bib("Test", 2024);
    Autor* a = bib.gasesteOrAdaugaAutor("Test","Autor","RO",1990,true);
    Editura* e = bib.gasesteOrAdaugaEditura("TestEd","RO","Iasi");

    CarteTehnica* c = new CarteTehnica(
        "ISBN-T05","Carte T05",{a},e,
        2020,LimbaCartii::ENGLEZA,TipCoperta::CARTONATA,
        "IT","Mediu",false);
    bib.adaugaCarte(c);

    string cod1 = bib.adaugaExemplarLaCarte("ISBN-T05","A","S1","R1","IT");
    string cod2 = bib.adaugaExemplarLaCarte("ISBN-T05","A","S1","R1","IT");
    string cod3 = bib.adaugaExemplarLaCarte("ISBN-T05","B","S2","R2","IT");

    UtilizatorStudent* u1 = new UtilizatorStudent(
        "U-T05A","Ion","Ana","a@b.ro","p",12,2024,1,"FIESC",1,"M001");
    UtilizatorStudent* u2 = new UtilizatorStudent(
        "U-T05B","Pop","Dan","d@b.ro","p",12,2024,1,"FIESC",2,"M002");
    bib.adaugaUtilizator(u1);
    bib.adaugaUtilizator(u2);

    bib.imprumutaCarte("U-T05A","ISBN-T05",1,4,2024);
    check(c->nrExemplareDisponibile() == 2, "dupa 1 imprumut din 3: 2 disponibile");

    bib.imprumutaCarte("U-T05B","ISBN-T05",1,4,2024);
    check(c->nrExemplareDisponibile() == 1, "dupa 2 imprumuturi din 3: 1 disponibil");

    bib.returneazaCarte("U-T05A", cod1, 0);
    check(c->nrExemplareDisponibile() == 2, "dupa 1 returnare: 2 disponibile");
}

// -----------------------------------------------------------------------
// T06 — MaterialeReferinta nu se imprumuta (getTimpImprumut = 0)
// -----------------------------------------------------------------------
void test_referinta_nu_se_imprumuta()
{
    cout << "\n[T06] MaterialeReferinta nu se imprumuta\n";

    Biblioteca bib("Test", 2024);
    Autor* a = bib.gasesteOrAdaugaAutor("Test","Autor","RO",1990,true);
    Editura* e = bib.gasesteOrAdaugaEditura("TestEd","RO","Iasi");

    MaterialeReferinta* ref = new MaterialeReferinta(
        "ISBN-T06","Atlas Test",{a},e,
        2020,LimbaCartii::ROMANA,TipCoperta::CARTONATA,"Atlas");
    bib.adaugaCarte(ref);
    bib.adaugaExemplarLaCarte("ISBN-T06","A","S1","R1","Referinta");

    UtilizatorBasic* u = new UtilizatorBasic(
        "U-T06","Test","User","t@t.ro","p",6,2024,1);
    bib.adaugaUtilizator(u);

    check(ref->getTimpImprumut() == 0, "getTimpImprumut = 0 pentru Referinta");

    bool exceptiePrinsa = false;
    try {
        bib.imprumutaCarte("U-T06","ISBN-T06",1,4,2024);
    } catch (const CarteLipsaException&) {
        exceptiePrinsa = true;
    }
    check(exceptiePrinsa, "imprumut Referinta arunca CarteLipsaException");
}

// -----------------------------------------------------------------------
// T07 — ISBN duplicat arunca exceptie
// -----------------------------------------------------------------------
void test_isbn_duplicat()
{
    cout << "\n[T07] ISBN duplicat\n";

    Biblioteca bib("Test", 2024);
    Autor* a = bib.gasesteOrAdaugaAutor("Test","Autor","RO",1990,true);
    Editura* e = bib.gasesteOrAdaugaEditura("TestEd","RO","Iasi");

    CarteFictiune* c1 = new CarteFictiune(
        "ISBN-DUP","Carte 1",{a},e,
        2020,LimbaCartii::ROMANA,TipCoperta::BROSATA,"SF",0);
    bib.adaugaCarte(c1);

    bool exceptiePrinsa = false;
    try {
        CarteFictiune* c2 = new CarteFictiune(
            "ISBN-DUP","Carte Duplicata",{a},e,
            2021,LimbaCartii::ROMANA,TipCoperta::BROSATA,"SF",0);
        bib.adaugaCarte(c2);
    } catch (const IsbnDuplicatException&) {
        exceptiePrinsa = true;
    }
    check(exceptiePrinsa, "ISBN duplicat arunca IsbnDuplicatException");
}

// -----------------------------------------------------------------------
// T08 — Autor unic in index (gasesteOrAdauga)
// -----------------------------------------------------------------------
void test_autor_unic()
{
    cout << "\n[T08] Unicitate autor in index\n";

    Biblioteca bib("Test", 2024);

    Autor* a1 = bib.gasesteOrAdaugaAutor("Ionescu","Mihai","RO",1980,true);
    Autor* a2 = bib.gasesteOrAdaugaAutor("Ionescu","Mihai","RO",1980,true);
    Autor* a3 = bib.gasesteOrAdaugaAutor("Popescu","Ion","RO",1975,true);

    check(a1 == a2, "acelasi autor returnat de doua ori e acelasi pointer");
    check(a1 != a3, "autori diferiti au pointeri diferiti");
}

// -----------------------------------------------------------------------
// MAIN
// -----------------------------------------------------------------------
int main()
{
    cout << "============================================================\n";
    cout << "  TESTE UNITARE: STOC SI INVENTAR\n";
    cout << "============================================================\n";

    test_stoc_initial_zero();
    test_adaugare_exemplare();
    test_cod_unic_format();
    test_status_exemplar_imprumut();
    test_disponibilitate_exemplare_multiple();
    test_referinta_nu_se_imprumuta();
    test_isbn_duplicat();
    test_autor_unic();

    cout << "\n============================================================\n";
    cout << "  REZULTAT: " << nrTrecute << " / " << nrTeste << " teste trecute\n";
    cout << "============================================================\n";

    return (nrTrecute == nrTeste) ? 0 : 1;
}