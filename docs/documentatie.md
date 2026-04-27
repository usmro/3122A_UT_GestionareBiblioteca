Documentație Proiect: Sistem de Gestionare a unei Biblioteci
Grupa: 3122A
Student: Ursescu Timotei
Limbaj: C++
Mediu: WSL Ubuntu / VS Code
Repository branch: develop

Cuprins
1. Cerința Proiectului
2. Arhitectura Generală
3. Concepte POO Implementate
4. Descrierea Claselor
    4.1. Interfața IAfisabil
    4.2. Șablonul Colectie<T>
    4.3. Entitățile de bază: Autor și Editura
    4.4. Clasa Carte și ierarhia derivată
    4.5. ExemplarFizic și sistemul de coduri unice
    4.6. Clasa Utilizator și ierarhia derivată
    4.7. Abonament, Istoric, Securitate

--------------------------------
1. Cerința Proiectului
--------------------------------

Implementarea unui sistem pentru o bibliotecă virtuală cu clase pentru cărți, utilizatori și împrumuturi.
Cerințe obligatorii acoperite:
- Clase: Carte, Utilizator, Biblioteca:în Carte.h, Utilizator.h, Biblioteca.h
- Moștenire pentru tipuri de cărți: CarteFictiune.h, CarteTehnica.h, etc.
- Polimorfism — metode virtuale: afisareDetalii(), getTipCarte(), etc.
- Encapsulare — atribute private + getteri/setteri: Toate clasele
- Evenimente logate: împrumut/returnare: Biblioteca.h → biblioteca_log.txt
- Teste unitare pentru verificarea stocului: tests/
- Git: 5+ commit-uri, branch develop: Repository GitHub
Cerințe facultative acoperite:
- Șablon generic pentru stocare: Colectie<T> în Colectie.h
- Excepții personalizate: Exceptii.h

--------------------------------
2. Arhitectura Generală
--------------------------------

Aplicația este structurată în trei straturi:
[ main.cpp ]
      |
      v
[ Biblioteca ] — creierul aplicației
      |
      |--- Colectie<Carte>      — inventar titluri
      |--- Colectie<Utilizator> — utilizatori înregistrați
      |--- Colectie<Autor>      — index unic de autori
      |--- Colectie<Editura>    — index unic de edituri
      |--- vector<Imprumut>     — împrumuturi active
      |--- vector<Rezervare>    — rezervări
      |
[ Carte* ] ←—moștenire—→ [ CarteFictiune, CarteTehnica, ... ]
[ Utilizator* ] ←——————→ [ UtilizatorBasic, Student, ... ]
Toate clasele afișabile implementează interfața IAfisabil, iar stocarea omogenă a obiectelor polimorfice se face prin Colectie<T>.

--------------------------------
3. Concepte POO Implementate
--------------------------------

3.1 Encapsulare
Toate atributele claselor sunt declarate private sau protected. Accesul extern se face exclusiv prin metode get/set publice. Exemplu din Utilizator:

        private:
            string parolaHash;  // parola nu e niciodata in clar

        public:
            void   setParola(const string& parolaNoua);     // setter — face hash automat
            bool   verificaParola(const string& parola) const; // nu expune hash-ul

Parola nu poate fi citită direct din afara clasei — parolaHash e privat și nu există un getter pentru ea. Securitatea e încapsulată în clasa Securitate (namespace în Utilizator.h).

3.2 Moștenire

Există două ierarhii principale de moștenire:
Ierarhia Carte:
IAfisabil  (interfață pură)
    └── Carte  (clasă abstractă — getTimpImprumut(), getTaxaIntarziere() pure)
            ├── CarteFictiune
            ├── CarteTehnica
            ├── CarteEducativa
            ├── CarteCopii
            ├── MaterialeReferinta
            ├── CarteReligioasa
            ├── Periodic  (ziare, reviste — ISSN în loc de ISBN)
            └── ManuscrisRar  (acces restricționat, nu se împrumută)
Ierarhia Utilizator:
IAfisabil  (interfață pură)
    └── Utilizator  (clasă abstractă — getLimitaImprumuturi() pur)
            ├── UtilizatorBasic   (2 cărți, fără discount)
            ├── UtilizatorStudent (5 cărți, discount 20%)
            ├── UtilizatorPremium (10 cărți, discount 40%)
            └── UtilizatorStaff   (15 cărți, fără taxe, drepturi admin)

3.3 Polimorfism

Polimorfismul se manifestă în două locuri cheie:
La afișare — același apel afisareDetalii() produce output diferit în funcție de tipul real al obiectului:

        vector<Carte*> carti = { new CarteFictiune(...), new CarteTehnica(...) };
        for (Carte* c : carti)
            c->afisareDetalii();  // output diferit pentru fiecare tip

La calcul taxe — aplicaDiscountTaxe() e suprascrisă diferit în fiecare tip de utilizator, fără ca Biblioteca să știe cu ce tip lucrează:

        double taxaFinala = u->aplicaDiscountTaxe(taxaBruta);
        // Student → taxaBruta * 0.8
        // Premium → taxaBruta * 0.6
        // Staff   → 0.0 (scutit)

La calcul timp împrumut — getTimpImprumut() returnează valori diferite:
- CarteFictiune- 14
- CarteTehnica- 28
- CarteEducativa- 30
- CarteCopii- 14
- MaterialeReferinta- 0 doar sala de lectură
- Periodic- 0 doar sala de lectură
- ManuscrisRar- 0 acces restricționat

3.4 Abstractizare

Carte și Utilizator sunt clase abstracte — nu pot fi instanțiate direct. Conțin metode virtuale pure (= 0) care forțează clasele derivate să implementeze comportamentul specific:

        // In Carte.h
        virtual int    getTimpImprumut()    const = 0;  // fiecare tip știe regula sa
        virtual double getTaxaDeteriorare() const = 0;
        virtual double getTaxaIntarziere()  const = 0;
        virtual string getTipCarte()        const = 0;

3.5 Interfața IAfisabil

Separată de ierarhia de moștenire, IAfisabil este o interfață pură (clasă fără date, doar metode virtuale pure):

        class IAfisabil {
        public:
            virtual void afisareDetalii() const = 0;
            virtual ~IAfisabil() = default;
        };

Atât Carte cât și Utilizator, Autor, Editura o implementează — demonstrând că interfața e independentă de ierarhie.

3.6 Supraîncărcarea operatorilor

Operatorul << e supraîncărcat pentru afișare rapidă la Carte, Utilizator, Autor, Editura:

        friend std::ostream& operator<<(std::ostream& os, const Carte& c) {
            os << "[" << c.getTipCarte() << "] " << c.titlu << " (" << c.anAparitie << ")";
            return os;
        }

        // Utilizare:
        cout << *unaCarte << "\n";  // [Fictiune] Dune (2020) - ISBN: ISBN-001

3.7 Șabloane (Templates)

Colectie<T> este o clasă template generică ce înlocuiește vector<T*> brut din Biblioteca. Avantaje față de vector direct: gestionare automată a memoriei în destructor, interdicție copiere (prevent double-delete), validare null la adăugare, excepție la index invalid.

        Colectie<Carte>      inventar;      // stochează Carte*
        Colectie<Utilizator> utilizatori;   // stochează Utilizator*
        Colectie<Autor>      indexAutori;   // stochează Autor*

        // Iterare cu range-based for (begin/end implementate)
        for (auto* carte : inventar) {
            carte->afisareDetalii();
        }

--------------------------------
4. Descrierea Claselor
--------------------------------

4.1 Interfata IAfisabil

Fisier: src/IAfisabil.h

Clasa abstracta pura care defineste contractul de afisare. Orice entitate
care poate fi afisata o implementeaza.

Metode:
- afisareDetalii() — virtual pur, afiseaza informatiile complete ale obiectului

4.2 Sablonul Colectie<T>

Fisier: src/Colectie.h

Container generic pentru stocare si gestionare de pointeri polimorfici.

Atribute private:
- elemente — vector<T*>, vectorul intern de pointeri

Metode publice:
- adauga(T*) — adauga element, arunca invalid_argument daca e null
- elimina(T*) — sterge si dealoca elementul, returneaza bool succes
- get(int) — acces prin index, arunca out_of_range daca e invalid
- dimensiune() — numarul de elemente
- esteGoala() — verificare colectie vida
- begin() / end() — permite range-based for

Nota: constructorul de copiere si operatorul = sunt sterse (= delete) pentru a preveni dubla alocare a memoriei.

4.3 Entitatile de baza: Autor si Editura

Fisiere: src/Autor.h, src/Editura.h

Ambele sunt entitati independente cu ID auto-generat printr-un contor static.
Biblioteca mentine cate un Colectie<Autor> si Colectie<Editura> care garanteaza unicitatea — acelasi autor nu apare de doua ori in sistem.

Autor — atribute:
- id — int, auto-generat prin contor static
- nume, prenume — string
- nationalitate — string, tara de origine
- anNastere — int
- esteViu — bool, autor in viata sau decedat
- bio — string, scurta biografie
- linkProfil — string, link Wikipedia/Goodreads etc.

Metoda cheie in Biblioteca:
    Autor* gasesteOrAdaugaAutor(string nume, string prenume, ...);
    // Daca autorul exista  -> returneaza pointerul existent
    // Daca nu exista       -> il creeaza, il adauga in index, returneaza pointer

4.4 Clasa Carte si ierarhia derivata

Fisier: src/Carte.h si fisierele derivatelor

Carte — atribute protected:
- isbn — string, identificator international (acelasi la toate copiile)
- titlu — string
- autori — vector<Autor*>, referinte la entitatile din IndexAutori
- editura — Editura*, referinta la entitatea din IndexEdituri
- anAparitie — int
- limba — LimbaCartii enum: ROMANA, ENGLEZA, FRANCEZA, GERMANA, SPANIOLA, ITALIANA, ALTA
- coperta — TipCoperta enum: CARTONATA, BROSATA, PIELE, SPIRALATA
- nrPagini — int
- greutateGrame — double
- exemplare — vector<ExemplarFizic>, copiile fizice din biblioteca
- serie — string, numele seriei (ex: "Dune")
- nrVolum — int, numarul volumului (0 = carte standalone)
- pretCatalog — double, pretul de catalog al editurii (RON)

Metode virtuale pure implementate de fiecare derivata:
- getTimpImprumut() — numarul de zile permise
- getTaxaDeteriorare() — taxa daca e deteriorata (RON)
- getTaxaIntarziere() — taxa per zi de intarziere (RON)
- getTipCarte() — string descriptor: "Fictiune", "Tehnica", etc.

Tipuri derivate si specificul lor:
- CarteFictiune — genLiterar, varstaMinima — 14 zile — 1.0 RON/zi
- CarteTehnica — domeniu, nivelDificultate, areResurseDigitale — 28 zile — 2.0 RON/zi
- CarteEducativa — materie, profil, clasa — 30 zile — 1.5 RON/zi
- CarteCopii — varstaRecomandata, ilustrator, areElementeInteractive — 14 zile — 0.5 RON/zi
- MaterialeReferinta — tipReferinta — 0 zile (sala) — 5.0 RON/zi
- CarteReligioasa — religie, cult — 21 zile — 1.0 RON/zi
- Periodic — issn, tipPeriodic, nrEditie — 0 zile (sala) — 2.0 RON/zi
- ManuscrisRar — epoca, conditiiPastrare, necesitaSupervizare — 0 zile — 50.0 RON/zi

4.5 ExemplarFizic si sistemul de coduri unice

Definit in: src/Carte.h (struct)

ISBN-ul identifica titlul. codUnic identifica copia fizica individuala.

Format cod unic: BIB-YYYY-NNNNN (ex: BIB-2024-00001)
Generat automat de Biblioteca::genereazaCodExemplar() la fiecare apel
adaugaExemplarLaCarte(). Nu poate exista acelasi cod de doua ori.

Atributele ExemplarFizic:
- codUnic — string, identificator unic al copiei (BIB-YYYY-NNNNN)
- status — StatusCarte enum: DISPONIBILA, IMPRUMUTATA, REZERVATA, DETERIORATA, SCOASA_DIN_UZ
- locatieCladire — string
- locatieCamera — string
- locatieRaft — string
- locatieSectiune — string
- provenienta — ProvenientaCarte enum: CUMPARATA, DONATIE, SCHIMB, MOSTENIRE
- anIntrareColectie — int
- pretAchizitie — double, pretul platit de biblioteca (poate diferi de pretCatalog)
- observatii — string, notite despre stare (ex: "pagina 34 patata")

4.6 Clasa Utilizator si ierarhia derivata

Fisier: src/Utilizator.h si derivatele

Utilizator — atribute protected:
- id — string, identificator unic (ex: "U-101")
- nume, prenume — string
- contact — string, email sau telefon
- tip — TipUtilizator enum: BASIC, STUDENT, PREMIUM, STAFF
- taxeAcumulate — double, suma totala de plata (RON)
- parolaHash — string, parola stocata ca hash (nu in clar)
- istoric — vector<EvenimentIstoric>, istoricul evolutiei utilizatorului
- imprumututiCurente — vector<string>, codurile exemplarelor imprumutate activ

Metode virtuale pure:
- getLimitaImprumuturi() — limita de carti simultane
- aplicaDiscountTaxe(double) — aplica reducerea specifica tipului
- getTipNume() — returneaza "BASIC", "STUDENT", "PREMIUM" sau "STAFF"

Comparativ tipuri utilizatori:
- UtilizatorBasic   — limita 2 carti, discount 0%,   are taxe, fara admin
- UtilizatorStudent — limita 5 carti, discount 20%,  are taxe, fara admin
- UtilizatorPremium — limita 10 carti, discount 40%, are taxe, fara admin
- UtilizatorStaff   — limita 15 carti, scutit taxe,  fara taxe, are admin

4.7 Abonament, Istoric, Securitate

Abonament (struct in Utilizator.h):
Fiecare tip de utilizator cu abonament are pretul, durata si data de start.
Metoda esteActiv(anCurent, lunaCurenta) verifica daca abonamentul e valabil.

Preturi abonamente:
- Basic   — 15 RON/luna
- Student — 10 RON/luna
- Premium — 40 RON/luna

Istoric evolutie (struct EvenimentIstoric):
Fiecare utilizator are un vector de evenimente cu an, luna si descriere.
La fiecare apel adaugaEveniment(), vectorul este sortat automat cronologic
(dupa an, apoi luna) — indiferent de ordinea in care sunt adaugate
evenimentele, afisarea este intotdeauna corect ordonata. Permite urmarirea
evolutiei in timp (ex: inscris in scoala generala, liceu, facultate, angajat).

Securitate parole (namespace Securitate in Utilizator.h):
- Parola nu se stocheaza niciodata in clar
- La creare/modificare — hashParola() aplica std::hash<string> si returneaza
  reprezentarea hex pe 16 caractere
- Verificare — verificaParola() hasheaza parola introdusa si compara cu hash-ul stocat
- Parola nu are getter — parolaHash este privat si nu este expus

UtilizatorStaff are in plus:
- RolStaff enum: BIBLIOTECAR, BIBLIOTECAR_SEF, ADMINISTRATOR, CASIER, ARHIVAR
- ContractAngajare struct: salariu, data angajare, zile concediu total si ramase
- Metode de drepturi diferentiate: poateAdaugaCarte(), poateStergeCarte(), poateGestionaStaff()
- pensionare(an, luna) — marcheaza staff-ul pensionat si adauga eveniment in istoric

4.8 Clasa Biblioteca
 
Fisier: src/Biblioteca.h
 
Clasa centrala care orchestreaza toate operatiunile. Foloseste Colectie<T>
pentru toate colectiile interne.
 
Atribute private:
- nume — string, numele institutiei
- inventar — Colectie<Carte>, toate titlurile
- utilizatori — Colectie<Utilizator>, utilizatori inregistrati
- indexAutori — Colectie<Autor>, index unic de autori
- indexEdituri — Colectie<Editura>, index unic de edituri
- imprumuturi — vector<Imprumut>, istorice si active
- rezervari — vector<Rezervare>, rezervari active
- totalIncasari — double, suma totala colectata
- contorExemplare — int, contor pentru generare coduri unice
- logFile — ofstream, fisier log (biblioteca_log.txt)
 
Metode principale:
- gasesteOrAdaugaAutor(...) — asigura unicitatea autorilor in index
- gasesteOrAdaugaEditura(...) — asigura unicitatea editurilor in index
- adaugaCarte(Carte*) — verifica ISBN duplicat, adauga in inventar
- adaugaExemplarLaCarte(isbn, ...) — genereaza cod unic, adauga exemplar fizic
- imprumutaCarte(idUser, isbn, ...) — verifica limite, disponibilitate, actualizeaza status
- returneazaCarte(idUser, cod, zile) — actualizeaza status, calculeaza taxe cu discount
- incaseazaTaxa(idUser, suma) — scade din taxele utilizatorului, adauga la incasari
- cautaDupaTitlu(fragment) — cautare partiala in titlu
- cautaDupaAutor(numeAutor) — cautare dupa autor
- cautaDupaAn(an) — filtrare dupa an aparitie
- afiseazaStatistici() — raport general: carti, utilizatori, incasari
 
Logging: fiecare operatie importanta (adaugare, imprumut, returnare, incasare)
se inregistreaza automat in biblioteca_log.txt.
 
4.9 Exceptii custom
 
Fisier: src/Exceptii.h
 
Toate deriva din std::runtime_error.
 
CarteLipsaException — carte inexistenta, toate exemplarele ocupate, sau nu se imprumuta
LimitaDepastitaException — utilizatorul a atins limita de imprumuturi
IsbnDuplicatException — se incearca adaugarea unui ISBN deja existent
UtilizatorInexistentException — ID utilizator negasit
TaxaInvalidaException — suma negativa sau zero la incasare
 
Exemplu de utilizare:
    try {
        bib.imprumutaCarte("U-101", "ISBN-001", 7, 4, 2024);
    } catch (const LimitaDepastitaException& e) {
        cout << e.what();
    } catch (const CarteLipsaException& e) {
        cout << e.what();
    }
 
--------------------------------
5. Structura Fisierelor
--------------------------------
 
3122A_UT_GestionareBiblioteca/
    src/
        IAfisabil.h — interfata pura de afisare
        Colectie.h — sablon generic <T>
        Autor.h — entitate autor (unica in IndexAutori)
        Editura.h — entitate editura (unica in IndexEdituri)
        Exceptii.h — exceptii custom
        Carte.h — clasa abstracta de baza + ExemplarFizic
        CarteFictiune.h — derivata: gen literar, varsta minima
        CarteTehnica.h — derivata: domeniu, dificultate, resurse
        CarteEducativa.h — derivata: materie, profil, clasa
        CarteCopii.h — derivata: varsta, ilustrator, interactiv
        MaterialeReferinta.h — derivata: dictionar/atlas/enciclopedie
        TipuriSpeciale.h — CarteReligioasa, Periodic, ManuscrisRar
        Utilizator.h — clasa abstracta de baza + securitate
        UtilizatorBasic.h — derivata: 2 carti, fara discount
        UtilizatorStudent.h — derivata: 5 carti, discount 20%
        UtilizatorPremium.h — derivata: 10 carti, discount 40%
        UtilizatorStaff.h — derivata: 15 carti, roluri, contract
        Biblioteca.h — orchestratorul principal
        main.cpp — demonstratie completa si teste
    tests/
        TestStoc.cpp — teste stoc, exemplare, coduri unice, ISBN duplicat
        TestImprumuturi.cpp — teste limite, taxe, discounturi, exceptii
        TestPolimorfism.cpp — teste virtuale, template, interfata, operator<<
    docs/
        documentatie.md — acest fisier
    Makefile
    README.md

-------------------------------- 
6. Diagrama de Clase
--------------------------------

IAfisabil (interfata pura)
    + afisareDetalii()* : void
            |
            |----------------------------------------|
            |                                        |
    Carte (abstracta)                       Utilizator (abstracta)
    # isbn : string                         # id : string
    # titlu : string                        # parolaHash : string
    # autori : vector<Autor*>               # taxeAcumulate : double
    # exemplare : vector<ExemplarFizic>     # istoric : vector<EvenimentIstoric>
    + getTimpImprumut()* : int              + getLimitaImprumuturi()* : int
    + getTaxaIntarziere()* : double         + aplicaDiscountTaxe()* : double
    + afisareDetalii()* : void              + afisareDetalii()* : void
            |                                        |
    CarteFictiune                           UtilizatorBasic
    CarteTehnica                            UtilizatorStudent
    CarteEducativa                          UtilizatorPremium
    CarteCopii                              UtilizatorStaff
    MaterialeReferinta                          + RolStaff enum
    CarteReligioasa                             + ContractAngajare struct
    Periodic
    ManuscrisRar
 
Colectie<T> (template)
    - elemente : vector<T*>
    + adauga(T*) : void
    + elimina(T*) : bool
    + get(int) : T*
    + dimensiune() : int
 
Biblioteca
    - inventar : Colectie<Carte>
    - utilizatori : Colectie<Utilizator>
    - indexAutori : Colectie<Autor>
    - indexEdituri : Colectie<Editura>
    + imprumutaCarte() : void
    + returneazaCarte() : void
    + cautaDupaTitlu() : vector<Carte*>

--------------------------------
7. Compilare si Rulare
--------------------------------
 
Cerinte: g++ cu suport C++17, make, WSL Ubuntu sau Linux nativ.
 
Compilare completa:
    make
 
Compilare rapida (un singur pas):
    make quick
 
Compilare si rulare imediata:
    make run
 
Stergere fisiere generate:
    make clean
 
Rebuild complet:
    make rebuild
 
Manual fara Makefile:
    g++ -std=c++17 -Wall -I./src -o biblioteca_app src/main.cpp
    ./biblioteca_app
 
Output asteptat: aplicatia ruleaza prin 14 sectiuni de teste, demonstrand
toate conceptele POO implementate, si genereaza fisierul biblioteca_log.txt
cu evenimentele logate.

--------------------------------
8. Popularea cu date(DataSeeder)
--------------------------------

Fisier: src/DataSeeder.h

La pornirea aplicatiei, DataSeeder::populeaza(bib) incarca automat in
biblioteca o baza de date de test cu peste 1000 de titluri si 200 de
utilizatori, acoperind toate cele 8 tipuri de carti implementate.

Distributia titlurilor:
- CarteFictiune    - ~150 titluri: SF, Fantasy, Thriller, Clasici romani
                     si universali, literatura moderna
- CarteTehnica     - ~150 titluri: C++, Python, Java, AI, DevOps,
                     Cloud, Securitate, Algoritmi
- CarteEducativa   - ~175 titluri: manuale cls. 5-12, culegeri BAC,
                     cursuri universitare toate domeniile
- CarteCopii       - ~100 titluri: Harry Potter, basme, enciclopedii,
                     clasici internationali si romani
- MaterialeReferinta - ~50 titluri: dictionare, atlase, enciclopedii
- CarteReligioasa  - 15 titluri: Biblie, Filocalie, Coran
- Periodic         - 15 titluri: ziare si reviste curente
- ManuscrisRar     - 10 titluri: cronicari moldoveni, manuscrise medievale

Fiecare titlu primeste 1-3 exemplare fizice cu cod unic BIB-YYYY-NNNNN
generat automat si locatie fizica in biblioteca.

Utilizatori generati:
- 5 Staff (Bibliotecar, Bibliotecar Sef, Administrator, Casier, Arhivar)
- 30 Studenti (5 facultati, ani diferiti de studiu)
- 80 utilizatori Basic
- 80 utilizatori Premium

Toate parolele sunt stocate ca hash, nu in clar.

--------------------------------
9. Meniu Consola
--------------------------------

Fisier: src/Meniu.h

Meniul foloseste coduri ANSI pentru culori in terminal:
- Albastru  — titluri sectiuni
- Galben    — numerele optiunilor
- Verde     — mesaje de succes
- Rosu      — erori si iesire
- Cyan      — prompt-uri de input
- Gri       — linii separatoare

Structura meniu:

1. Gestiune Carti (14 optiuni)
   - Afisare inventar complet
   - Cautare dupa ISBN
   - Adaugare carte pentru fiecare tip: Fictiune, Tehnica, Educativa,
     Copii, Referinta, Religioasa, Periodic, Manuscris Rar
   - Adaugare exemplar fizic la carte existenta
   - Afisare detalii complete (toate exemplarele si locatiile)
   - Afisare index autori si edituri

2. Gestiune Utilizatori (9 optiuni)
   - Afisare toti utilizatorii
   - Cautare dupa ID
   - Adaugare utilizator: Basic, Student, Premium, Staff
   - Afisare istoric evolutie utilizator
   - Afisare imprumuturi active
   - Verificare parola (testeaza hash-ul fara a afisa parola)

3. Imprumuturi & Returnari (4 optiuni)
   - Inregistrare imprumut (verifica automat limita si disponibilitatea)
   - Inregistrare returnare cu calcul taxa de intarziere
   - Incasare taxa cu discount automat pe tip utilizator
   - Verificare disponibilitate carte

4. Cautare & Filtrare (5 optiuni)
   - Cautare partiala dupa titlu
   - Cautare dupa autor
   - Filtrare dupa an aparitie
   - Cautare dupa ISBN
   - Cautare utilizator dupa ID

5. Statistici & Rapoarte
   - Total titluri, utilizatori, autori unici, edituri unice
   - Total incasari biblioteca
   - Numar imprumuturi active

Toate actiunile sunt protejate cu tratare de exceptii — erorile sunt
afisate cu rosu fara a crapa aplicatia.

--------------------------------
10. Teste Unitare
--------------------------------
 
Testele sunt organizate in 3 fisiere separate in tests/, fiecare compilabil independent.
 
TestStoc.cpp — 8 teste pentru inventarul fizic:
    T01 — carte fara exemplare: nrExemplareTotal = 0, getPrimulDisponibil = nullptr
    T02 — adaugare exemplare: contorul creste corect dupa fiecare adaugare
    T03 — format cod unic BIB-2024-NNNNN, lungime 14 caractere, coduri diferite
    T04 — status exemplar devine IMPRUMUTATA la imprumut, DISPONIBILA la returnare
    T05 — disponibilitate corecta cu exemplare multiple si mai multi utilizatori
    T06 — MaterialeReferinta arunca CarteLipsaException la tentativa de imprumut
    T07 — ISBN duplicat arunca IsbnDuplicatException
    T08 — acelasi autor adaugat de 2 ori returneaza pointer identic (unicitate index)
 
TestImprumuturi.cpp — 10 teste pentru logica de imprumut:
    T01 — imprumut simplu: utilizatorul are cartea in lista activa
    T02 — limita Basic (2 carti): al 3-lea imprumut arunca LimitaDepastitaException
    T03 — limita Student (5 carti): al 6-lea imprumut arunca exceptie
    T04 — returnarea elibereaza slot: utilizatorul poate imprumuta din nou
    T05 — utilizator inexistent arunca UtilizatorInexistentException
    T06 — carte fara niciun exemplar adaugat arunca CarteLipsaException
    T07 — Staff: aplicaDiscountTaxe() returneaza 0.0 RON indiferent de suma
    T08 — discount Student 20%: 10 RON brut devine 8 RON, 25 RON brut devine 20 RON
    T09 — discount Premium 40%: 10 RON brut devine 6 RON, 50 RON brut devine 30 RON
    T10 — taxa acumulata corect dupa returnare cu intarziere, zero dupa plata
 
TestPolimorfism.cpp — 7 teste pentru concepte POO:
    T01 — getTipCarte() returneaza tipul corect pentru toate cele 8 derivate
    T02 — getTimpImprumut() diferit per tip prin pointer de baza Carte*
    T03 — getLimitaImprumuturi() diferit per tip prin pointer Utilizator*
    T04 — areDreptDeAdmin() false pentru Basic/Student/Premium, true pentru Staff
    T05 — Colectie<T>: dimensiune, get, out_of_range, invalid_argument la null
    T06 — IAfisabil*: afisareDetalii() functioneaza prin pointer de interfata
    T07 — operator << supraincarcata produce output nevid cu date corecte
 
Rulare teste:
    make tests              — toate 3 fisierele
    make test-stoc          — doar TestStoc
    make test-imprumuturi   — doar TestImprumuturi
    make test-polimorfism   — doar TestPolimorfism
 
--------------------------------
11. Cerinte Acoperite
--------------------------------
 
Cerinte obligatorii:
 
Clase Carte, Utilizator, Biblioteca — implementate complet cu atribute
private si metode publice.
 
Mostenire — 8 tipuri de carti si 4 tipuri de utilizatori, toti mostenind
din clase abstracte.
 
Polimorfism — afisareDetalii(), getTipCarte(), getLimitaImprumuturi(),
aplicaDiscountTaxe() toate virtuale cu suprascriere in derivate.
 
Encapsulare — toate atributele private/protected, accesate prin getteri/setteri.
Parola hash niciodata expusa direct.
 
Evenimente logate — imprumut/returnare/adaugare/incasare scrise in biblioteca_log.txt.
 
Git — minimum 5 commit-uri descriptive pe branch develop.
 
Cerinte facultative:
 
Sablon generic — Colectie<T> inlocuieste vector<T*> brut, cu gestionare
memorie automata si validare.
 
Exceptii — 5 clase de exceptii custom derivate din std::runtime_error.
 
Interfata consola — main.cpp demonstreaza toate functionalitatile cu
output structurat in 14 sectiuni.

--------------------------------
12. Decizii de Proiectare
--------------------------------
 
De ce Autor si Editura ca entitati, nu ca string?
Un string "Frank Herbert" apare in zeci de carti. Daca vrem sa actualizam
bio-ul sau sa adaugam un link, cu string ar trebui modificat in fiecare carte.
Cu entitate separata, modificam o singura data si toate cartile reflecta
automat schimbarea.
 
De ce ExemplarFizic separat de Carte?
ISBN-ul este acelasi pentru toate copiile unui titlu, dar fiecare copie fizica
are locatie proprie, stare proprie si cod propriu. Fara ExemplarFizic, nu putem
sti ca exemplarul de pe raftul A-3 este imprumutat dar cel de pe A-7 este disponibil.
 
De ce IAfisabil ca interfata separata?
Carte si Utilizator nu au o relatie de mostenire intre ele, dar ambele trebuie
sa se poata afisa. IAfisabil permite scrierea de functii generice care accepta
orice IAfisabil* fara sa stie daca e carte sau utilizator.
 
De ce Colectie<T> in loc de vector<T*>?
vector<T*> nu gestioneaza memoria — daca uiti delete, ai memory leak.
Colectie<T> face delete automat in destructor, interzice copierea accidentala
care ar face double-delete, si valideaza null-ul la adaugare.
 
De ce parola ca hash si nu in clar?
Daca fisierul de date sau memoria este citita de un atacator, parolele in clar
sunt compromise instant. Hash-ul nu permite recuperarea parolei originale —
verificarea se face comparand hash-uri, nu parole.
 
De ce istoricul este sortat automat la fiecare adaugaEveniment()?
Evenimentele pot fi adaugate in orice ordine — constructorul adauga inscrierea,
apoi programatorul adauga retroactiv evenimente din trecut. Fara sortare automata,
istoricul ar aparea in ordinea insertiei, nu cronologic. Sortand la fiecare
inserare garantam ca vectorul este mereu ordonat indiferent de cine si cand
adauga evenimente.