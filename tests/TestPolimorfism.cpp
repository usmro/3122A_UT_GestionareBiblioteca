#include <iostream>
#include <string>
#include <vector>

#include "../src/IAfisabil.h"
#include "../src/Colectie.h"
#include "../src/Carte.h"
#include "../src/CarteFictiune.h"
#include "../src/CarteTehnica.h"
#include "../src/CarteEducativa.h"
#include "../src/CarteCopii.h"
#include "../src/MaterialeReferinta.h"
#include "../src/TipuriSpeciale.h"
#include "../src/Utilizator.h"
#include "../src/UtilizatorBasic.h"
#include "../src/UtilizatorStudent.h"
#include "../src/UtilizatorPremium.h"
#include "../src/UtilizatorStaff.h"
#include "../src/Autor.h"
#include "../src/Editura.h"

using std::cout;
using std::string;
using std::vector;

static int nrTeste   = 0;
static int nrTrecute = 0;

void check(bool conditie, const string& numTest)
{
    nrTeste++;
    if (conditie) { nrTrecute++; cout << "  [PASS] " << numTest << "\n"; }
    else          {              cout << "  [FAIL] " << numTest << "\n"; }
}

// -----------------------------------------------------------------------
// T01 — getTipCarte() returneaza tipul corect pentru fiecare derivata
// -----------------------------------------------------------------------
void test_tip_carte_polimorfic()
{
    cout << "\n[T01] getTipCarte() polimorfic\n";

    Autor*   a = new Autor("T","A","RO",1990,true);
    Editura* e = new Editura("Ed","RO","Iasi");

    vector<Carte*> carti = {
        new CarteFictiune ("ISBN-P01","F",{a},e,2020,LimbaCartii::ROMANA,TipCoperta::BROSATA,"SF",0),
        new CarteTehnica  ("ISBN-P02","T",{a},e,2020,LimbaCartii::ENGLEZA,TipCoperta::CARTONATA,"IT","Med",false),
        new CarteEducativa("ISBN-P03","E",{a},e,2020,LimbaCartii::ROMANA,TipCoperta::BROSATA,"Mat","Real",10),
        new CarteCopii    ("ISBN-P04","C",{a},e,2020,LimbaCartii::ROMANA,TipCoperta::BROSATA,5,"Il",false),
        new MaterialeReferinta("ISBN-P05","R",{a},e,2020,LimbaCartii::ROMANA,TipCoperta::CARTONATA,"Atlas"),
        new CarteReligioasa("ISBN-P06","Rel",{a},e,2020,LimbaCartii::ROMANA,TipCoperta::CARTONATA,"Ortodoxa","BOR"),
        new Periodic("ISSN-P01","Ziar",{},e,2024,LimbaCartii::ROMANA,"Ziar",1,4,2024),
        new ManuscrisRar("ISBN-P07","Man",{a},nullptr,1700,LimbaCartii::ROMANA,TipCoperta::PIELE,"Medieval","18C",true)
    };

    vector<string> tipuriAsteptate = {
        "Fictiune","Tehnica","Educativa","Copii",
        "Referinta","Religioasa","Periodic","ManuscrisRar"
    };

    for (int i = 0; i < (int)carti.size(); i++)
        check(carti[i]->getTipCarte() == tipuriAsteptate[i],
              "getTipCarte() = " + tipuriAsteptate[i]);

    for (auto* c : carti) delete c;
    delete a;
    delete e;
}

// -----------------------------------------------------------------------
// T02 — getTimpImprumut() diferit per tip (polimorfism)
// -----------------------------------------------------------------------
void test_timp_imprumut_polimorfic()
{
    cout << "\n[T02] getTimpImprumut() polimorfic\n";

    Autor*   a = new Autor("T","A","RO",1990,true);
    Editura* e = new Editura("Ed","RO","Iasi");

    CarteFictiune*     cf  = new CarteFictiune ("ISBN-TI1","",{a},e,2020,LimbaCartii::ROMANA,TipCoperta::BROSATA,"",0);
    CarteTehnica*      ct  = new CarteTehnica  ("ISBN-TI2","",{a},e,2020,LimbaCartii::ENGLEZA,TipCoperta::BROSATA,"","",false);
    CarteEducativa*    ce  = new CarteEducativa("ISBN-TI3","",{a},e,2020,LimbaCartii::ROMANA,TipCoperta::BROSATA,"","",0);
    CarteCopii*        cc  = new CarteCopii    ("ISBN-TI4","",{a},e,2020,LimbaCartii::ROMANA,TipCoperta::BROSATA,0,"",false);
    MaterialeReferinta* mr = new MaterialeReferinta("ISBN-TI5","",{a},e,2020,LimbaCartii::ROMANA,TipCoperta::CARTONATA,"");

    // Prin pointer de baza — polimorfism real
    vector<Carte*> carti = {cf, ct, ce, cc, mr};
    vector<int>    zile  = {14, 28, 30, 14, 0};

    for (int i = 0; i < (int)carti.size(); i++)
        check(carti[i]->getTimpImprumut() == zile[i],
              carti[i]->getTipCarte() + ": getTimpImprumut() = " + std::to_string(zile[i]));

    for (auto* c : carti) delete c;
    delete a; delete e;
}

// -----------------------------------------------------------------------
// T03 — getLimitaImprumuturi() diferit per tip utilizator
// -----------------------------------------------------------------------
void test_limita_polimorfic()
{
    cout << "\n[T03] getLimitaImprumuturi() polimorfic\n";

    vector<Utilizator*> useri = {
        new UtilizatorBasic  ("U1","A","B","c","p",6,2024,1),
        new UtilizatorStudent("U2","A","B","c","p",12,2024,1,"F",1,"M"),
        new UtilizatorPremium("U3","A","B","c","p",24,2024,1),
        new UtilizatorStaff  ("U4","A","B","c","p","Dep",RolStaff::BIBLIOTECAR,3000,2020,1)
    };
    vector<int> limite = {2, 5, 10, 15};

    for (int i = 0; i < (int)useri.size(); i++)
        check(useri[i]->getLimitaImprumuturi() == limite[i],
              useri[i]->getTipNume() + ": limita = " + std::to_string(limite[i]));

    for (auto* u : useri) delete u;
}

// -----------------------------------------------------------------------
// T04 — areDreptDeAdmin() polimorfic
// -----------------------------------------------------------------------
void test_admin_polimorfic()
{
    cout << "\n[T04] areDreptDeAdmin() polimorfic\n";

    Utilizator* basic   = new UtilizatorBasic  ("U1","A","B","c","p",6,2024,1);
    Utilizator* student = new UtilizatorStudent("U2","A","B","c","p",12,2024,1,"F",1,"M");
    Utilizator* premium = new UtilizatorPremium("U3","A","B","c","p",24,2024,1);
    Utilizator* staff   = new UtilizatorStaff  ("U4","A","B","c","p","Dep",RolStaff::ADMINISTRATOR,4000,2020,1);

    check(basic->areDreptDeAdmin()   == false, "Basic: fara drept admin");
    check(student->areDreptDeAdmin() == false, "Student: fara drept admin");
    check(premium->areDreptDeAdmin() == false, "Premium: fara drept admin");
    check(staff->areDreptDeAdmin()   == true,  "Staff: are drept admin");

    delete basic; delete student; delete premium; delete staff;
}

// -----------------------------------------------------------------------
// T05 — Colectie<T> template: dimensiune, get, exceptie out_of_range
// -----------------------------------------------------------------------
void test_colectie_template()
{
    cout << "\n[T05] Colectie<T> sablon generic\n";

    Colectie<Autor> col;
    check(col.esteGoala()    == true,  "colectie vida: esteGoala = true");
    check(col.dimensiune()   == 0,     "colectie vida: dimensiune = 0");

    col.adauga(new Autor("Ion","A","RO",1990,true));
    col.adauga(new Autor("Pop","B","RO",1985,true));
    check(col.dimensiune()   == 2,     "dupa 2 adaugari: dimensiune = 2");
    check(col.esteGoala()    == false,  "dupa adaugare: esteGoala = false");

    check(col.get(0)->getNume() == "Ion", "get(0) returneaza primul element");
    check(col.get(1)->getNume() == "Pop", "get(1) returneaza al doilea element");

    bool exceptiePrinsa = false;
    try { col.get(99); }
    catch (const std::out_of_range&) { exceptiePrinsa = true; }
    check(exceptiePrinsa, "get(99) arunca out_of_range");

    bool nullExceptie = false;
    try { col.adauga(nullptr); }
    catch (const std::invalid_argument&) { nullExceptie = true; }
    check(nullExceptie, "adauga(nullptr) arunca invalid_argument");
}

// -----------------------------------------------------------------------
// T06 — IAfisabil: pointer de interfata apeleaza metoda corecta
// -----------------------------------------------------------------------
void test_iafisabil_interfata()
{
    cout << "\n[T06] IAfisabil - pointer de interfata\n";

    // Ambele tipuri complet diferite implementeaza aceeasi interfata
    Autor*   a  = new Autor("Test","Autor","RO",1990,true);
    Editura* e  = new Editura("Ed","RO","Iasi");

    // Putem stoca Autor si Carte in acelasi vector de IAfisabil*
    // (demonstreaza ca interfata e independenta de ierarhie)
    IAfisabil* obj1 = new Autor("Eminescu","Mihai","RO",1850,false);
    IAfisabil* obj2 = new CarteFictiune(
        "ISBN-IA1","Test",{a},e,
        2020,LimbaCartii::ROMANA,TipCoperta::BROSATA,"SF",0);

    // Nu verificam output-ul, verificam ca apelul nu crapa
    bool ok = true;
    try {
        // Redirectam cout temporar ca sa nu murdaream outputul testelor
        std::streambuf* old = std::cout.rdbuf();
        std::cout.rdbuf(nullptr);
        obj1->afisareDetalii();
        obj2->afisareDetalii();
        std::cout.rdbuf(old);
    } catch (...) {
        ok = false;
    }
    check(ok, "afisareDetalii() prin IAfisabil* nu arunca exceptii");

    delete obj1; delete obj2;
    delete a; delete e;
}

// -----------------------------------------------------------------------
// T07 — Operator << supraincarcata pentru Carte si Utilizator
// -----------------------------------------------------------------------
void test_operator_stream()
{
    cout << "\n[T07] Operator << supraincarcata\n";

    Autor*   a = new Autor("Herbert","Frank","US",1920,false);
    Editura* e = new Editura("Nemira","RO","Bucuresti");

    CarteFictiune c("ISBN-OP1","Dune",{a},e,
                    2020,LimbaCartii::ROMANA,TipCoperta::BROSATA,"SF",0);

    UtilizatorBasic u("U-OP1","Enescu","Ana","a@a.ro","p",6,2024,1);

    // Capturam output-ul
    std::ostringstream oss1, oss2;
    oss1 << c;
    oss2 << u;

    check(!oss1.str().empty(), "operator<< Carte produce output nevid");
    check(!oss2.str().empty(), "operator<< Utilizator produce output nevid");
    check(oss1.str().find("Dune") != string::npos,
          "operator<< Carte contine titlul");
    check(oss2.str().find("Enescu") != string::npos,
          "operator<< Utilizator contine numele");

    delete a; delete e;
}

// -----------------------------------------------------------------------
// MAIN
// -----------------------------------------------------------------------
int main()
{
    cout << "============================================================\n";
    cout << "  TESTE UNITARE: POLIMORFISM, MOSTENIRE, TEMPLATE\n";
    cout << "============================================================\n";

    test_tip_carte_polimorfic();
    test_timp_imprumut_polimorfic();
    test_limita_polimorfic();
    test_admin_polimorfic();
    test_colectie_template();
    test_iafisabil_interfata();
    test_operator_stream();

    cout << "\n============================================================\n";
    cout << "  REZULTAT: " << nrTrecute << " / " << nrTeste << " teste trecute\n";
    cout << "============================================================\n";

    return (nrTrecute == nrTeste) ? 0 : 1;
}