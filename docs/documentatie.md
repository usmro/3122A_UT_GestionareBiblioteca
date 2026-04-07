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

1. Cerința Proiectului
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

2. Arhitectura Generală
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

3. Concepte POO Implementate

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