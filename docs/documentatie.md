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