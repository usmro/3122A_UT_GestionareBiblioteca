#include <iostream>
#include <vector>
#include <string>

#include "Biblioteca.h"
#include "CarteFictiune.h"
#include "CarteTehnica.h"
#include "CarteEducativa.h"
#include "CarteCopii.h"
#include "MaterialeReferinta.h"
#include "TipuriSpeciale.h"
#include "UtilizatorBasic.h"
#include "UtilizatorStudent.h"
#include "UtilizatorPremium.h"
#include "UtilizatorStaff.h"
#include "Exceptii.h"

using std::cout;
using std::string;
using std::vector;

// -----------------------------------------------------------------------
// Helper afisare separator
// -----------------------------------------------------------------------
void separator(const string& titlu = "")
{
    cout << "\n============================================================\n";
    if (!titlu.empty()) cout << "  " << titlu << "\n";
    cout << "============================================================\n";
}

int main()
{
    separator("TESTARE LIVRABIL 1+2: CLASE, MOSTENIRE, POLIMORFISM");

    // ====================================================================
    // 1. Crearea Bibliotecii
    // ====================================================================
    separator("1. Initializare Biblioteca");
    Biblioteca bib("Biblioteca Universitara Suceava", 2024);
    cout << "Biblioteca '" << bib.getNume() << "' creata.\n";

    // ====================================================================
    // 2. Index Autori si Edituri (fara duplicare)
    // ====================================================================
    separator("2. Index Autori si Edituri");

    Autor* herbertFrank = bib.gasesteOrAdaugaAutor(
        "Herbert", "Frank", "American", 1920, false,
        "Autor SF celebru pentru seria Dune", "https://wikipedia.org/Frank_Herbert");

    Autor* martinRobert = bib.gasesteOrAdaugaAutor(
        "Martin", "Robert C.", "American", 1952, true,
        "Autor Clean Code, expert software craftsmanship");

    Autor* popoviciIoan = bib.gasesteOrAdaugaAutor(
        "Popovici", "Ioan", "Roman", 1960, true);

    // Acelasi autor adaugat din nou - nu se duplica
    Autor* herbertFrank2 = bib.gasesteOrAdaugaAutor(
        "Herbert", "Frank", "American", 1920, false);
    cout << "Autor duplicat evitat: "
         << (herbertFrank == herbertFrank2 ? "DA (corect)" : "NU (eroare)") << "\n";

    herbertFrank->afisareDetalii();
    martinRobert->afisareDetalii();

    Editura* nemira = bib.gasesteOrAdaugaEditura(
        "Nemira", "Romania", "Bucuresti", 1991, "www.nemira.ro");
    Editura* prenticHall = bib.gasesteOrAdaugaEditura(
        "Prentice Hall", "USA", "New Jersey", 1913);
    Editura* didactica = bib.gasesteOrAdaugaEditura(
        "Didactica si Pedagogica", "Romania", "Bucuresti", 1951);

    cout << *nemira << "\n";
    cout << *prenticHall << "\n";

    // ====================================================================
    // 3. Creare carti cu noua structura
    // ====================================================================
    separator("3. Creare carti (ierarhie Carte)");

    // CarteFictiune
    CarteFictiune* dune = new CarteFictiune(
        "ISBN-001", "Dune",
        {herbertFrank}, nemira,
        2020, LimbaCartii::ROMANA, TipCoperta::BROSATA,
        "SF", 12, 412, 320.0, "Dune", 1, 49.99);

    // CarteTehnica - autori multipli
    Autor* gamma = bib.gasesteOrAdaugaAutor("Gamma","Erich","German",1961,true);
    Autor* helm  = bib.gasesteOrAdaugaAutor("Helm","Richard","American",1960,true);
    CarteTehnica* designPatterns = new CarteTehnica(
        "ISBN-002", "Design Patterns",
        {gamma, helm}, prenticHall,
        1994, LimbaCartii::ENGLEZA, TipCoperta::CARTONATA,
        "Software Engineering", "Avansat", true, 395, 580.0, 89.99);

    // CarteEducativa
    CarteFictiune* ionCreanga = new CarteFictiune(
        "ISBN-003", "Amintiri din copilarie",
        {bib.gasesteOrAdaugaAutor("Creanga","Ion","Roman",1837,false)},
        didactica, 2019, LimbaCartii::ROMANA, TipCoperta::BROSATA,
        "Proza clasica", 8, 156, 110.0, "", 0, 18.99);

    // MaterialeReferinta
    MaterialeReferinta* atlas = new MaterialeReferinta(
        "ISBN-004", "Atlas Geografic Romania",
        {popoviciIoan}, didactica,
        2019, LimbaCartii::ROMANA, TipCoperta::CARTONATA,
        "Atlas", 240, 950.0, 75.00);

    // Periodic - ziar
    Periodic* evenimentul = new Periodic(
        "ISSN-001", "Evenimentul Zilei",
        {}, nemira,
        2024, LimbaCartii::ROMANA,
        "Ziar", 8745, 4, 2024, "Stiri", 24);

    // ManuscrisRar
    ManuscrisRar* manuscris = new ManuscrisRar(
        "ISBN-RARE-001", "Letopisetul Tarii Moldovei",
        {bib.gasesteOrAdaugaAutor("Costin","Miron","Roman",1633,false)},
        nullptr, 1675, LimbaCartii::ROMANA, TipCoperta::PIELE,
        "Epoca medievala", "Temperatura 18C, umiditate 45%", true, 15000.0);

    // ====================================================================
    // 4. Adaugare in biblioteca + exemplare fizice
    // ====================================================================
    separator("4. Adaugare carti in biblioteca + exemplare fizice");

    bib.adaugaCarte(dune);
    bib.adaugaCarte(designPatterns);
    bib.adaugaCarte(ionCreanga);
    bib.adaugaCarte(atlas);
    bib.adaugaCarte(evenimentul);
    bib.adaugaCarte(manuscris);

    // Adaugam exemplare cu cod unic auto-generat
    string codDune1 = bib.adaugaExemplarLaCarte("ISBN-001",
        "Cladirea A", "Sala Fictiune", "R-12", "SF",
        ProvenientaCarte::CUMPARATA, 35.0);
    string codDune2 = bib.adaugaExemplarLaCarte("ISBN-001",
        "Cladirea A", "Sala Fictiune", "R-12", "SF",
        ProvenientaCarte::DONATIE, 0.0);
    string codDP1 = bib.adaugaExemplarLaCarte("ISBN-002",
        "Cladirea B", "Sala Tehnica", "R-05", "Informatica",
        ProvenientaCarte::CUMPARATA, 62.0);
    bib.adaugaExemplarLaCarte("ISBN-003",
        "Cladirea A", "Sala Clasici", "R-03", "Literatura Romana",
        ProvenientaCarte::CUMPARATA, 14.0);
    bib.adaugaExemplarLaCarte("ISBN-004",
        "Cladirea A", "Sala Referinta", "R-01", "Atlase",
        ProvenientaCarte::CUMPARATA, 55.0);

    cout << "\nCoduri exemplare generate: "
         << codDune1 << ", " << codDune2 << ", " << codDP1 << "\n";

    // ====================================================================
    // 5. Afisare detalii (polimorfism - afisareDetalii() virtual)
    // ====================================================================
    separator("5. Polimorfism - afisareDetalii() virtual");

    // Apelam prin pointer de baza - demonstratie polimorfism
    vector<Carte*> cartiTest = {dune, designPatterns, atlas, evenimentul, manuscris};
    cout << "\n[Polimorfism] Afisare prin Carte*:\n";
    for (Carte* c : cartiTest)
    {
        cout << *c << "\n";  // operator << supraincarcata
    }

    cout << "\n[Detalii complete - Dune]:\n";
    dune->afisareDetalii();

    cout << "\n[Detalii complete - Design Patterns]:\n";
    designPatterns->afisareDetalii();

    // ====================================================================
    // 6. Creare utilizatori
    // ====================================================================
    separator("6. Creare utilizatori (ierarhie Utilizator)");

    UtilizatorStudent* student1 = new UtilizatorStudent(
        "U-101", "Enescu", "Ana", "ana@usv.ro", "parola123",
        12, 2024, 9,
        "FIESC", 2, "MAT2024001");
    // Adaugam istoricul cronologic (constructorul a adaugat deja inscrierea la facultate)
    student1->adaugaEveniment(2014, 9, "Inscris in scoala generala cls. I");
    student1->adaugaEveniment(2018, 9, "Inscris la liceu - Colegiul National");
    student1->adaugaEveniment(2022, 6, "Bacalaureat promovat");

    UtilizatorPremium* premium1 = new UtilizatorPremium(
        "PR-001", "Popa", "Elena", "0747826408", "premium2024",
        24, 2024, 1);

    UtilizatorBasic* basic1 = new UtilizatorBasic(
        "BAS-001", "Ionescu", "Mihai", "mihai@gmail.com", "basic123",
        6, 2024, 3);

    UtilizatorStaff* staff1 = new UtilizatorStaff(
        "STAFF-01", "Marin", "Andreea", "a.marin@usv.ro", "staff2024",
        "Sectia Tehnica", RolStaff::BIBLIOTECAR_SEF,
        4200.0, 2019, 3);
    // Constructorul a adaugat deja evenimentul de angajare
    staff1->adaugaEveniment(2022, 1, "Promovata Bibliotecar Sef");
    staff1->adaugaEveniment(2023, 6, "Responsabila sectia Tehnica si Referinta");

    bib.adaugaUtilizator(student1);
    bib.adaugaUtilizator(premium1);
    bib.adaugaUtilizator(basic1);
    bib.adaugaUtilizator(staff1);

    // Afisare prin polimorfism
    cout << "\n[Polimorfism] Afisare utilizatori prin Utilizator*:\n";
    vector<Utilizator*> useri = {student1, premium1, basic1, staff1};
    for (Utilizator* u : useri)
        u->afisareDetalii();

    // ====================================================================
    // 7. Verificare parole (securitate)
    // ====================================================================
    separator("7. Securitate - parole hashate");
    cout << "Verificare parola corecta pentru Ana: "
         << (student1->verificaParola("parola123") ? "OK" : "EROARE") << "\n";
    cout << "Verificare parola gresita pentru Ana: "
         << (student1->verificaParola("parolaGresita") ? "EROARE" : "OK") << "\n";
    cout << "Hash parola nu se afiseaza in clar - securitate respectata.\n";

    // ====================================================================
    // 8. Imprumuturi
    // ====================================================================
    separator("8. Gestiune imprumuturi");

    bib.imprumutaCarte("U-101", "ISBN-001", 7, 4, 2024);  // Ana imprumuta Dune
    bib.imprumutaCarte("PR-001", "ISBN-002", 7, 4, 2024); // Elena imprumuta Design Patterns

    cout << "\nDupa imprumuturi:\n";
    cout << "Exemplare Dune disponibile: "
         << dune->nrExemplareDisponibile() << "/"
         << dune->nrExemplareTotal() << "\n";

    // Returnare cu intarziere
    separator("9. Returnare cu taxa intarziere");
    bib.returneazaCarte("U-101", codDune1, 3); // 3 zile intarziere
    cout << "Taxe Ana dupa returnare: " << student1->getTaxeAcumulate() << " RON\n";
    cout << "(Discount student 20% aplicat automat)\n";
    bib.incaseazaTaxa("U-101", student1->getTaxeAcumulate());

    // ====================================================================
    // 9. Tratare exceptii
    // ====================================================================
    separator("10. Tratare exceptii custom");

    try {
        bib.adaugaCarte(new CarteFictiune(
            "ISBN-001", "Duplicat", {herbertFrank}, nemira,
            2020, LimbaCartii::ROMANA, TipCoperta::BROSATA, "SF", 0));
    } catch (const IsbnDuplicatException& e) {
        cout << "[Exceptie prinsa] " << e.what() << "\n";
    }

    try {
        bib.imprumutaCarte("U-999", "ISBN-001", 1, 1, 2024);
    } catch (const UtilizatorInexistentException& e) {
        cout << "[Exceptie prinsa] " << e.what() << "\n";
    }

    try {
        bib.imprumutaCarte("U-101", "ISBN-RARE-001", 1, 1, 2024);
    } catch (const CarteLipsaException& e) {
        cout << "[Exceptie prinsa] " << e.what() << "\n";
    }

    // ====================================================================
    // 10. Cautare
    // ====================================================================
    separator("11. Motor cautare");
    auto rez = bib.cautaDupaTitlu("Dune");
    cout << "Cautare 'Dune': "; bib.afiseazaRezultateCautare(rez);

    auto rezAutor = bib.cautaDupaAutor("Herbert");
    cout << "Cautare autor 'Herbert': "; bib.afiseazaRezultateCautare(rezAutor);

    auto rezAn = bib.cautaDupaAn(1994);
    cout << "Cautare an 1994: "; bib.afiseazaRezultateCautare(rezAn);

    // ====================================================================
    // 11. Colectie<T> template
    // ====================================================================
    separator("12. Sablon Colectie<T>");
    Colectie<Autor> testColectie;
    testColectie.adauga(new Autor("Ionescu","Radu","RO",1990,true));
    testColectie.adauga(new Autor("Popescu","Maria","RO",1985,true));
    cout << "Colectie<Autor> dimensiune: " << testColectie.dimensiune() << "\n";
    cout << "Autor[0]: " << *testColectie.get(0) << "\n";

    try {
        testColectie.get(99);
    } catch (const std::out_of_range& e) {
        cout << "[Exceptie std] " << e.what() << "\n";
    }

    // ====================================================================
    // 12. Istoric utilizator
    // ====================================================================
    separator("13. Istoric utilizator");
    student1->afisareIstoric();
    staff1->afisareIstoric();

    // ====================================================================
    // 13. Statistici finale
    // ====================================================================
    separator("14. Statistici finale");
    bib.afiseazaStatistici();

    separator("TOATE TESTELE FINALIZATE");
    return 0;
}