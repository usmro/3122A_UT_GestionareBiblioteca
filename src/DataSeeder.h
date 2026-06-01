#ifndef DATA_SEEDER_H
#define DATA_SEEDER_H

#include "Biblioteca.h"
#include "CarteFictiune.h"
#include "CarteTehnica.h"
#include "CarteEducativa.h"
#include "CarteCopii.h"
#include "MaterialeReferinta.h"
#include "TipuriSpeciale.h"
#include "UtilizatorBasic.h"
#include "UtilizatorStudent.h"
#include "UtilizatorStaff.h"
#include <vector>

class DataSeeder
{
public:
    static void populeaza(Biblioteca& bib)
    {
        seedEdituri(bib);
        seedCartiFictiune(bib);
        seedCartiTehnica(bib);
        seedCartiEducativa(bib);
        seedCartiCopii(bib);
        seedMaterialeReferinta(bib);
        seedCartiReligioase(bib);
        seedPeriodicale(bib);
        seedManuscrise(bib);
        seedUtilizatori(bib);
    }

private:

    // Adauga N exemplare intr-o locatie
    static void adaugaExemplare(Biblioteca& bib, const string& isbn,
                                 const string& cladire, const string& camera,
                                 const string& raft, const string& sectiune,
                                 int n, double pretUnitar)
    {
        for (int i = 0; i < n; i++) {
            try {
                bib.adaugaExemplarLaCarte(isbn, cladire, camera, raft, sectiune,
                    ProvenientaCarte::CUMPARATA, pretUnitar);
            } catch(...) {}
        }
    }

    static void seedEdituri(Biblioteca& bib)
    {
        bib.gasesteOrAdaugaEditura("Nemira","Romania","Bucuresti",1991,"www.nemira.ro");
        bib.gasesteOrAdaugaEditura("Humanitas","Romania","Bucuresti",1990,"www.humanitas.ro");
        bib.gasesteOrAdaugaEditura("Polirom","Romania","Iasi",1995,"www.polirom.ro");
        bib.gasesteOrAdaugaEditura("RAO","Romania","Bucuresti",1994,"www.raobooks.com");
        bib.gasesteOrAdaugaEditura("Corint","Romania","Bucuresti",1991,"www.corint.ro");
        bib.gasesteOrAdaugaEditura("Didactica si Pedagogica","Romania","Bucuresti",1951);
        bib.gasesteOrAdaugaEditura("Art","Romania","Bucuresti",2003,"www.edituraart.ro");
        bib.gasesteOrAdaugaEditura("Litera","Romania","Bucuresti",1990,"www.litera.ro");
        bib.gasesteOrAdaugaEditura("O'Reilly Media","USA","Sebastopol",1978,"www.oreilly.com");
        bib.gasesteOrAdaugaEditura("Prentice Hall","USA","New Jersey",1913);
        bib.gasesteOrAdaugaEditura("Addison-Wesley","USA","Boston",1942);
        bib.gasesteOrAdaugaEditura("Manning Publications","USA","Shelter Island",1990);
        bib.gasesteOrAdaugaEditura("Packt Publishing","UK","Birmingham",2004);
        bib.gasesteOrAdaugaEditura("No Starch Press","USA","San Francisco",1994);
        bib.gasesteOrAdaugaEditura("Adevarul Holding","Romania","Bucuresti",2008);
        bib.gasesteOrAdaugaEditura("Curtea Veche","Romania","Bucuresti",1997);
        bib.gasesteOrAdaugaEditura("Minerva","Romania","Bucuresti",1969);
        bib.gasesteOrAdaugaEditura("Pandora M","Romania","Bucuresti",2000);
        bib.gasesteOrAdaugaEditura("Trei","Romania","Bucuresti",1994);
    }

    // Helper: adauga carte fictiune cu nr exemplare specificat
    static void adaugaCF(Biblioteca& bib, const string& isbn, const string& titlu,
                          Autor* autor, Editura* ed, int an, const string& gen,
                          int varsta, int pagini, double pret, int nrEx,
                          const string& serie = "", int vol = 0)
    {
        auto* c = new CarteFictiune(isbn,titlu,{autor},ed,an,
            LimbaCartii::ROMANA,TipCoperta::BROSATA,gen,varsta,pagini,0.0,serie,vol,pret);
        try { bib.adaugaCarte(c); } catch(...){ delete c; return; }
        adaugaExemplare(bib, isbn, "Cladirea A","Sala Fictiune","R-F1","Fictiune", nrEx, pret*0.7);
    }

    static void adaugaCT(Biblioteca& bib, const string& isbn, const string& titlu,
                          Autor* autor, Editura* ed, int an, const string& dom,
                          const string& niv, int pagini, double pret, int nrEx = 3)
    {
        auto* c = new CarteTehnica(isbn,titlu,{autor},ed,an,
            LimbaCartii::ENGLEZA,TipCoperta::CARTONATA,dom,niv,false,pagini,0.0,pret);
        try { bib.adaugaCarte(c); } catch(...){ delete c; return; }
        adaugaExemplare(bib, isbn, "Cladirea B","Sala Tehnica","R-T1","Informatica", nrEx, pret*0.65);
    }

    static void adaugaCE(Biblioteca& bib, const string& isbn, const string& titlu,
                          const string& materie, const string& profil, int clasa,
                          int an, int pagini, double pret, int nrEx = 4)
    {
        auto* autor = bib.gasesteOrAdaugaAutor("Colectiv","Autori","Roman",2000,true);
        auto* ed    = bib.gasesteOrAdaugaEditura("Didactica si Pedagogica","Romania","Bucuresti");
        auto* c = new CarteEducativa(isbn,titlu,{autor},ed,an,
            LimbaCartii::ROMANA,TipCoperta::BROSATA,materie,profil,clasa,pagini,0.0,pret);
        try { bib.adaugaCarte(c); } catch(...){ delete c; return; }
        adaugaExemplare(bib, isbn, "Cladirea C","Sala Educativa","R-E1","Educational", nrEx, pret*0.6);
    }

    static void adaugaCC(Biblioteca& bib, const string& isbn, const string& titlu,
                          Autor* autor, Editura* ed, int an, int varsta,
                          bool interactiv, int pagini, double pret, int nrEx = 3)
    {
        auto* c = new CarteCopii(isbn,titlu,{autor},ed,an,
            LimbaCartii::ROMANA,TipCoperta::CARTONATA,varsta,"Divers",interactiv,pagini,0.0,pret);
        try { bib.adaugaCarte(c); } catch(...){ delete c; return; }
        adaugaExemplare(bib, isbn, "Cladirea A","Sala Copii","R-K1","Copii", nrEx, pret*0.6);
    }

    static void adaugaRef(Biblioteca& bib, const string& isbn, const string& titlu,
                           const string& tip, int an, int pagini, double pret, int nrEx = 1)
    {
        auto* col = bib.gasesteOrAdaugaAutor("Colectiv","Autori","Roman",2000,true);
        auto* ed  = bib.gasesteOrAdaugaEditura("Corint","Romania","Bucuresti");
        auto* c = new MaterialeReferinta(isbn,titlu,{col},ed,an,
            LimbaCartii::ROMANA,TipCoperta::CARTONATA,tip,pagini,0.0,pret);
        try { bib.adaugaCarte(c); } catch(...){ delete c; return; }
        adaugaExemplare(bib, isbn, "Cladirea A","Sala Referinta","R-REF","Referinta", nrEx, pret*0.7);
    }

    // ===================================================================
    // CARTI FICTIUNE
    // ===================================================================
    static void seedCartiFictiune(Biblioteca& bib)
    {
        auto* nemira    = bib.gasesteOrAdaugaEditura("Nemira","Romania","Bucuresti");
        auto* rao       = bib.gasesteOrAdaugaEditura("RAO","Romania","Bucuresti");
        auto* humanitas = bib.gasesteOrAdaugaEditura("Humanitas","Romania","Bucuresti");
        auto* litera    = bib.gasesteOrAdaugaEditura("Litera","Romania","Bucuresti");
        auto* corint    = bib.gasesteOrAdaugaEditura("Corint","Romania","Bucuresti");
        auto* minerva   = bib.gasesteOrAdaugaEditura("Minerva","Romania","Bucuresti");
        auto* trei      = bib.gasesteOrAdaugaEditura("Trei","Romania","Bucuresti");
        auto* pandora   = bib.gasesteOrAdaugaEditura("Pandora M","Romania","Bucuresti");

        // Autori
        auto* herbert   = bib.gasesteOrAdaugaAutor("Herbert","Frank","American",1920,false);
        auto* tolkien   = bib.gasesteOrAdaugaAutor("Tolkien","J.R.R.","Britanic",1892,false);
        auto* orwell    = bib.gasesteOrAdaugaAutor("Orwell","George","Britanic",1903,false);
        auto* huxley    = bib.gasesteOrAdaugaAutor("Huxley","Aldous","Britanic",1894,false);
        auto* asimov    = bib.gasesteOrAdaugaAutor("Asimov","Isaac","American",1920,false);
        auto* clarke    = bib.gasesteOrAdaugaAutor("Clarke","Arthur C.","Britanic",1917,false);
        auto* dick      = bib.gasesteOrAdaugaAutor("Dick","Philip K.","American",1928,false);
        auto* lequin    = bib.gasesteOrAdaugaAutor("Le Guin","Ursula K.","Americana",1929,false);
        auto* bradbury  = bib.gasesteOrAdaugaAutor("Bradbury","Ray","American",1920,false);
        auto* gibson    = bib.gasesteOrAdaugaAutor("Gibson","William","Canadian",1948,true);
        auto* gaiman    = bib.gasesteOrAdaugaAutor("Gaiman","Neil","Britanic",1960,true);
        auto* pratchett = bib.gasesteOrAdaugaAutor("Pratchett","Terry","Britanic",1948,false);
        auto* adams     = bib.gasesteOrAdaugaAutor("Adams","Douglas","Britanic",1952,false);
        auto* king      = bib.gasesteOrAdaugaAutor("King","Stephen","American",1947,true);
        auto* martin_g  = bib.gasesteOrAdaugaAutor("Martin","George R.R.","American",1948,true);
        auto* sanderson = bib.gasesteOrAdaugaAutor("Sanderson","Brandon","American",1975,true);
        auto* rothfuss  = bib.gasesteOrAdaugaAutor("Rothfuss","Patrick","American",1973,true);
        auto* abercrom  = bib.gasesteOrAdaugaAutor("Abercrombie","Joe","Britanic",1974,true);
        auto* jordan    = bib.gasesteOrAdaugaAutor("Jordan","Robert","American",1948,false);
        auto* hugo      = bib.gasesteOrAdaugaAutor("Hugo","Victor","Francez",1802,false);
        auto* dumas     = bib.gasesteOrAdaugaAutor("Dumas","Alexandre","Francez",1802,false);
        auto* verne     = bib.gasesteOrAdaugaAutor("Verne","Jules","Francez",1828,false);
        auto* camus     = bib.gasesteOrAdaugaAutor("Camus","Albert","Francez",1913,false);
        auto* kafka     = bib.gasesteOrAdaugaAutor("Kafka","Franz","Ceh",1883,false);
        auto* hesse     = bib.gasesteOrAdaugaAutor("Hesse","Hermann","German",1877,false);
        auto* remarque  = bib.gasesteOrAdaugaAutor("Remarque","Erich Maria","German",1898,false);
        auto* zweig     = bib.gasesteOrAdaugaAutor("Zweig","Stefan","Austrian",1881,false);
        auto* dostoev   = bib.gasesteOrAdaugaAutor("Dostoevsky","Fyodor","Rus",1821,false);
        auto* tolstoy   = bib.gasesteOrAdaugaAutor("Tolstoy","Leo","Rus",1828,false);
        auto* hemingway = bib.gasesteOrAdaugaAutor("Hemingway","Ernest","American",1899,false);
        auto* eco       = bib.gasesteOrAdaugaAutor("Eco","Umberto","Italian",1932,false);
        auto* murakami  = bib.gasesteOrAdaugaAutor("Murakami","Haruki","Japonez",1949,true);
        auto* marquez   = bib.gasesteOrAdaugaAutor("Garcia Marquez","Gabriel","Columbian",1927,false);
        auto* coelho    = bib.gasesteOrAdaugaAutor("Coelho","Paulo","Brazilian",1947,true);
        auto* dickens   = bib.gasesteOrAdaugaAutor("Dickens","Charles","Britanic",1812,false);
        auto* austen    = bib.gasesteOrAdaugaAutor("Austen","Jane","Britanica",1775,false);
        auto* wilde     = bib.gasesteOrAdaugaAutor("Wilde","Oscar","Irlandez",1854,false);
        auto* grisham   = bib.gasesteOrAdaugaAutor("Grisham","John","American",1955,true);
        auto* christie  = bib.gasesteOrAdaugaAutor("Christie","Agatha","Britanica",1890,false);
        auto* brown_d   = bib.gasesteOrAdaugaAutor("Brown","Dan","American",1964,true);
        auto* larsson   = bib.gasesteOrAdaugaAutor("Larsson","Stieg","Suedez",1954,false);
        auto* child_l   = bib.gasesteOrAdaugaAutor("Child","Lee","Britanic",1954,true);
        auto* eminescu  = bib.gasesteOrAdaugaAutor("Eminescu","Mihai","Roman",1850,false);
        auto* creanga   = bib.gasesteOrAdaugaAutor("Creanga","Ion","Roman",1837,false);
        auto* caragiale = bib.gasesteOrAdaugaAutor("Caragiale","Ion Luca","Roman",1852,false);
        auto* rebreanu  = bib.gasesteOrAdaugaAutor("Rebreanu","Liviu","Roman",1885,false);
        auto* sadoveanu = bib.gasesteOrAdaugaAutor("Sadoveanu","Mihail","Roman",1880,false);
        auto* preda     = bib.gasesteOrAdaugaAutor("Preda","Marin","Roman",1922,false);
        auto* cartarescu= bib.gasesteOrAdaugaAutor("Cartarescu","Mircea","Roman",1956,true);
        auto* blaga     = bib.gasesteOrAdaugaAutor("Blaga","Lucian","Roman",1895,false);
        auto* eliade    = bib.gasesteOrAdaugaAutor("Eliade","Mircea","Roman",1907,false);
        auto* petrescu  = bib.gasesteOrAdaugaAutor("Petrescu","Camil","Roman",1894,false);
        auto* steinhardt= bib.gasesteOrAdaugaAutor("Steinhardt","Nicolae","Roman",1912,false);

        // SF si Fantasy (popularitate = nr exemplare 5-40)
        adaugaCF(bib,"ISBN-F001","Dune",herbert,nemira,2020,"SF",14,412,49.99,35,"Dune",1);
        adaugaCF(bib,"ISBN-F002","Dune Messia",herbert,nemira,2021,"SF",14,380,45.99,20,"Dune",2);
        adaugaCF(bib,"ISBN-F003","Children of Dune",herbert,nemira,2021,"SF",14,410,45.99,15,"Dune",3);
        adaugaCF(bib,"ISBN-F004","Dune God Emperor",herbert,nemira,2022,"SF",14,454,45.99,10,"Dune",4);
        adaugaCF(bib,"ISBN-F005","Stapanul Inelelor: Fratia Inelului",tolkien,rao,2019,"Fantasy",12,423,55.99,40,"LOTR",1);
        adaugaCF(bib,"ISBN-F006","Stapanul Inelelor: Cele Doua Turnuri",tolkien,rao,2019,"Fantasy",12,352,55.99,35,"LOTR",2);
        adaugaCF(bib,"ISBN-F007","Stapanul Inelelor: Intoarcerea Regelui",tolkien,rao,2019,"Fantasy",12,416,55.99,35,"LOTR",3);
        adaugaCF(bib,"ISBN-F008","Hobbitul",tolkien,rao,2018,"Fantasy",10,310,39.99,45);
        adaugaCF(bib,"ISBN-F009","Silmarillion",tolkien,rao,2020,"Fantasy",14,365,45.99,15);
        adaugaCF(bib,"ISBN-F010","1984",orwell,humanitas,2021,"Distopie",16,328,35.99,50);
        adaugaCF(bib,"ISBN-F011","Ferma Animalelor",orwell,humanitas,2020,"Satira",14,128,25.99,40);
        adaugaCF(bib,"ISBN-F012","Minunata Lume Noua",huxley,humanitas,2019,"SF",16,311,34.99,30);
        adaugaCF(bib,"ISBN-F013","Foundation",asimov,nemira,2020,"SF",14,244,39.99,25,"Foundation",1);
        adaugaCF(bib,"ISBN-F014","Foundation and Empire",asimov,nemira,2020,"SF",14,247,39.99,18,"Foundation",2);
        adaugaCF(bib,"ISBN-F015","Second Foundation",asimov,nemira,2021,"SF",14,210,39.99,15,"Foundation",3);
        adaugaCF(bib,"ISBN-F016","I Robot",asimov,nemira,2019,"SF",14,253,35.99,22);
        adaugaCF(bib,"ISBN-F017","2001 A Space Odyssey",clarke,rao,2020,"SF",14,221,35.99,20);
        adaugaCF(bib,"ISBN-F018","Rendezvous with Rama",clarke,rao,2021,"SF",14,243,35.99,12);
        adaugaCF(bib,"ISBN-F019","Do Androids Dream of Electric Sheep",dick,nemira,2019,"SF",16,210,32.99,18);
        adaugaCF(bib,"ISBN-F020","The Man in the High Castle",dick,nemira,2020,"SF",16,259,35.99,12);
        adaugaCF(bib,"ISBN-F021","Fahrenheit 451",bradbury,nemira,2018,"Distopie",14,158,29.99,35);
        adaugaCF(bib,"ISBN-F022","Neuromancer",gibson,nemira,2021,"Cyberpunk",16,271,34.99,15);
        adaugaCF(bib,"ISBN-F023","American Gods",gaiman,rao,2019,"Fantasy",16,465,45.99,22);
        adaugaCF(bib,"ISBN-F024","Good Omens",gaiman,rao,2020,"Comedie",14,288,39.99,20);
        adaugaCF(bib,"ISBN-F025","The Colour of Magic",pratchett,humanitas,2019,"Comedie",12,243,35.99,18,"Discworld",1);
        adaugaCF(bib,"ISBN-F026","Guards Guards",pratchett,humanitas,2020,"Comedie",12,288,35.99,15,"Discworld",8);
        adaugaCF(bib,"ISBN-F027","Hitchhikers Guide to the Galaxy",adams,humanitas,2019,"SF Comedie",12,193,32.99,28,"HHGTTG",1);
        adaugaCF(bib,"ISBN-F028","The Shining",king,litera,2020,"Horror",18,447,45.99,25);
        adaugaCF(bib,"ISBN-F029","It",king,litera,2019,"Horror",18,1138,65.99,20);
        adaugaCF(bib,"ISBN-F030","Pet Sematary",king,litera,2020,"Horror",18,374,39.99,18);
        adaugaCF(bib,"ISBN-F031","Misery",king,litera,2021,"Horror",18,310,35.99,15);
        adaugaCF(bib,"ISBN-F032","The Stand",king,litera,2021,"Horror",18,1152,65.99,8);
        adaugaCF(bib,"ISBN-F033","A Game of Thrones",martin_g,rao,2020,"Fantasy",16,694,55.99,45,"ASOIAF",1);
        adaugaCF(bib,"ISBN-F034","A Clash of Kings",martin_g,rao,2020,"Fantasy",16,768,55.99,35,"ASOIAF",2);
        adaugaCF(bib,"ISBN-F035","A Storm of Swords",martin_g,rao,2021,"Fantasy",16,992,59.99,30,"ASOIAF",3);
        adaugaCF(bib,"ISBN-F036","The Final Empire",sanderson,nemira,2021,"Fantasy",14,541,49.99,28,"Mistborn",1);
        adaugaCF(bib,"ISBN-F037","The Well of Ascension",sanderson,nemira,2021,"Fantasy",14,590,49.99,20,"Mistborn",2);
        adaugaCF(bib,"ISBN-F038","The Hero of Ages",sanderson,nemira,2022,"Fantasy",14,572,49.99,18,"Mistborn",3);
        adaugaCF(bib,"ISBN-F039","The Way of Kings",sanderson,nemira,2022,"Fantasy",16,1007,65.99,22,"Stormlight",1);
        adaugaCF(bib,"ISBN-F040","The Name of the Wind",rothfuss,nemira,2020,"Fantasy",16,662,55.99,30,"Kingkiller",1);
        adaugaCF(bib,"ISBN-F041","The Wise Mans Fear",rothfuss,nemira,2021,"Fantasy",16,994,59.99,22,"Kingkiller",2);
        adaugaCF(bib,"ISBN-F042","The Blade Itself",abercrom,humanitas,2020,"Fantasy",16,515,45.99,15,"First Law",1);
        adaugaCF(bib,"ISBN-F043","Before They Are Hanged",abercrom,humanitas,2021,"Fantasy",16,543,45.99,12,"First Law",2);
        adaugaCF(bib,"ISBN-F044","The Eye of the World",jordan,rao,2019,"Fantasy",14,782,55.99,20,"Wheel of Time",1);
        adaugaCF(bib,"ISBN-F045","Enders Game",bib.gasesteOrAdaugaAutor("Card","Orson Scott","American",1951,true),nemira,2020,"SF",12,324,39.99,25);
        adaugaCF(bib,"ISBN-F046","The Martian",bib.gasesteOrAdaugaAutor("Weir","Andy","American",1972,true),rao,2020,"SF",14,369,42.99,30);
        adaugaCF(bib,"ISBN-F047","Project Hail Mary",bib.gasesteOrAdaugaAutor("Weir","Andy","American",1972,true),rao,2022,"SF",14,476,45.99,22);
        adaugaCF(bib,"ISBN-F048","Hyperion",bib.gasesteOrAdaugaAutor("Simmons","Dan","American",1948,true),nemira,2020,"SF",16,481,49.99,18,"Hyperion",1);
        adaugaCF(bib,"ISBN-F049","Snow Crash",bib.gasesteOrAdaugaAutor("Stephenson","Neal","American",1959,true),nemira,2021,"Cyberpunk",18,440,45.99,12);
        // Clasici francezi si europeni
        adaugaCF(bib,"ISBN-F050","Les Miserables",hugo,humanitas,2019,"Roman social",14,1463,59.99,15);
        adaugaCF(bib,"ISBN-F051","Notre-Dame de Paris",hugo,humanitas,2020,"Roman gotic",14,512,42.99,12);
        adaugaCF(bib,"ISBN-F052","Cei trei muschetari",dumas,litera,2019,"Aventuri",12,576,45.99,25);
        adaugaCF(bib,"ISBN-F053","Contele de Monte Cristo vol 1",dumas,litera,2019,"Aventuri",14,512,45.99,20,"Monte Cristo",1);
        adaugaCF(bib,"ISBN-F054","Contele de Monte Cristo vol 2",dumas,litera,2019,"Aventuri",14,498,45.99,18,"Monte Cristo",2);
        adaugaCF(bib,"ISBN-F055","20000 de leghe sub mari",verne,corint,2019,"SF Aventuri",10,368,35.99,20);
        adaugaCF(bib,"ISBN-F056","Ocolul pamantului in 80 de zile",verne,corint,2019,"Aventuri",10,256,29.99,22);
        adaugaCF(bib,"ISBN-F057","Strainul",camus,humanitas,2019,"Roman existentialist",16,160,22.99,30);
        adaugaCF(bib,"ISBN-F058","Ciuma",camus,humanitas,2020,"Roman",16,320,32.99,20);
        adaugaCF(bib,"ISBN-F059","Procesul",kafka,humanitas,2019,"Roman",18,224,25.99,18);
        adaugaCF(bib,"ISBN-F060","Metamorfoza",kafka,humanitas,2019,"Nuvela",16,96,15.99,25);
        adaugaCF(bib,"ISBN-F061","Siddhartha",hesse,humanitas,2019,"Roman filozofic",14,152,22.99,20);
        adaugaCF(bib,"ISBN-F062","Lupul de stepa",hesse,humanitas,2020,"Roman",16,288,28.99,15);
        adaugaCF(bib,"ISBN-F063","Pe frontul de vest nimic nou",remarque,humanitas,2019,"Roman razboi",16,296,29.99,22);
        adaugaCF(bib,"ISBN-F064","Arc de triumf",remarque,humanitas,2020,"Roman",16,432,35.99,12);
        adaugaCF(bib,"ISBN-F065","Scrisoare catre o necunoscuta",zweig,humanitas,2019,"Nuvela",14,112,18.99,18);
        adaugaCF(bib,"ISBN-F066","Crime and Punishment",dostoev,humanitas,2019,"Roman clasic",16,671,45.99,20);
        adaugaCF(bib,"ISBN-F067","The Brothers Karamazov",dostoev,humanitas,2020,"Roman clasic",16,824,55.99,12);
        adaugaCF(bib,"ISBN-F068","War and Peace",tolstoy,humanitas,2021,"Roman clasic",16,1225,69.99,8);
        adaugaCF(bib,"ISBN-F069","Anna Karenina",tolstoy,humanitas,2020,"Roman clasic",16,864,55.99,10);
        adaugaCF(bib,"ISBN-F070","Batranul si marea",hemingway,humanitas,2019,"Nuvela",14,128,19.99,28);
        adaugaCF(bib,"ISBN-F071","Adio arme",hemingway,humanitas,2020,"Roman razboi",16,352,34.99,15);
        adaugaCF(bib,"ISBN-F072","Numele trandafirului",eco,humanitas,2019,"Roman mister",16,502,42.99,18);
        adaugaCF(bib,"ISBN-F073","Norvegia Forest",murakami,humanitas,2019,"Roman",18,296,32.99,20);
        adaugaCF(bib,"ISBN-F074","1Q84 vol 1",murakami,humanitas,2020,"Roman",18,496,42.99,15,"1Q84",1);
        adaugaCF(bib,"ISBN-F075","Suta de ani de singuratate",marquez,rao,2019,"Realism magic",16,417,39.99,25);
        adaugaCF(bib,"ISBN-F076","Alchimistul",coelho,humanitas,2019,"Roman filozofic",14,192,22.99,35);
        adaugaCF(bib,"ISBN-F077","David Copperfield",dickens,humanitas,2019,"Roman",14,880,55.99,10);
        adaugaCF(bib,"ISBN-F078","Oliver Twist",dickens,humanitas,2019,"Roman",12,448,35.99,15);
        adaugaCF(bib,"ISBN-F079","Mandrie si prejudecata",austen,humanitas,2019,"Roman romantic",14,432,35.99,22);
        adaugaCF(bib,"ISBN-F080","Dorian Gray",wilde,humanitas,2019,"Roman",16,254,25.99,20);
        // Thriller si mister
        adaugaCF(bib,"ISBN-F081","The Firm",grisham,litera,2019,"Thriller",16,421,35.99,18);
        adaugaCF(bib,"ISBN-F082","The Client",grisham,litera,2020,"Thriller",16,422,35.99,15);
        adaugaCF(bib,"ISBN-F083","A Time to Kill",grisham,litera,2019,"Thriller",16,515,39.99,12);
        adaugaCF(bib,"ISBN-F084","And Then There Were None",christie,litera,2019,"Mister",14,245,29.99,25);
        adaugaCF(bib,"ISBN-F085","Murder on the Orient Express",christie,litera,2020,"Mister",14,212,28.99,22);
        adaugaCF(bib,"ISBN-F086","The Da Vinci Code",brown_d,rao,2020,"Thriller",16,454,39.99,30);
        adaugaCF(bib,"ISBN-F087","The Girl with the Dragon Tattoo",larsson,litera,2019,"Thriller",18,465,42.99,20,"Millennium",1);
        adaugaCF(bib,"ISBN-F088","Killing Floor",child_l,litera,2020,"Thriller",16,424,35.99,15,"Jack Reacher",1);
        adaugaCF(bib,"ISBN-F089","Gone Girl",bib.gasesteOrAdaugaAutor("Flynn","Gillian","Americana",1971,true),litera,2021,"Thriller",18,415,39.99,18);
        adaugaCF(bib,"ISBN-F090","The Silent Patient",bib.gasesteOrAdaugaAutor("Michaelides","Alex","Cipriot",1977,true),litera,2022,"Thriller",18,325,35.99,20);
        // Literatura romana
        adaugaCF(bib,"ISBN-F091","Poezii",eminescu,minerva,2018,"Poezie",12,312,25.99,30);
        adaugaCF(bib,"ISBN-F092","Amintiri din Copilarie",creanga,minerva,2018,"Proza",8,156,15.99,35);
        adaugaCF(bib,"ISBN-F093","O Scrisoare Pierduta",caragiale,humanitas,2018,"Teatru",14,128,15.99,25);
        adaugaCF(bib,"ISBN-F094","Ion",rebreanu,humanitas,2020,"Roman",16,448,35.99,20);
        adaugaCF(bib,"ISBN-F095","Padurea Spanzuratilor",rebreanu,humanitas,2019,"Roman",16,352,32.99,15);
        adaugaCF(bib,"ISBN-F096","Baltagul",sadoveanu,minerva,2018,"Roman",14,245,25.99,18);
        adaugaCF(bib,"ISBN-F097","Morometii vol 1",preda,humanitas,2020,"Roman",16,312,32.99,22,"Morometii",1);
        adaugaCF(bib,"ISBN-F098","Morometii vol 2",preda,humanitas,2020,"Roman",16,298,32.99,18,"Morometii",2);
        adaugaCF(bib,"ISBN-F099","Nostalgia",cartarescu,humanitas,2019,"Proza",18,312,39.99,15);
        adaugaCF(bib,"ISBN-F100","Solenoid",cartarescu,humanitas,2021,"Roman",18,860,65.99,10);
        adaugaCF(bib,"ISBN-F101","Poemele luminii",blaga,minerva,2019,"Poezie",14,96,14.99,20);
        adaugaCF(bib,"ISBN-F102","Maitreyi",eliade,humanitas,2019,"Roman",16,224,24.99,18);
        adaugaCF(bib,"ISBN-F103","Ultima noapte de dragoste",petrescu,humanitas,2019,"Roman",16,288,28.99,20);
        adaugaCF(bib,"ISBN-F104","Jurnalul fericirii",steinhardt,bib.gasesteOrAdaugaEditura("Polirom","Romania","Iasi"),2019,"Jurnal",16,448,39.99,12);
        adaugaCF(bib,"ISBN-F105","Micul Print",bib.gasesteOrAdaugaAutor("Saint-Exupery","Antoine de","Francez",1900,false),humanitas,2019,"Basm filozofic",8,96,15.99,40);
        // TITLURI NOI - Fictiune suplimentara
        auto* gabaldon  = bib.gasesteOrAdaugaAutor("Gabaldon","Diana","Americana",1952,true);
        auto* meyer     = bib.gasesteOrAdaugaAutor("Meyer","Stephenie","Americana",1973,true);
        auto* collins   = bib.gasesteOrAdaugaAutor("Collins","Suzanne","Americana",1962,true);
        auto* riordan   = bib.gasesteOrAdaugaAutor("Riordan","Rick","American",1964,true);
        auto* picoult   = bib.gasesteOrAdaugaAutor("Picoult","Jodi","Americana",1966,true);
        auto* zusak     = bib.gasesteOrAdaugaAutor("Zusak","Markus","Australian",1975,true);
        auto* hosseini  = bib.gasesteOrAdaugaAutor("Hosseini","Khaled","Afgan-American",1965,true);
        auto* lehane    = bib.gasesteOrAdaugaAutor("Lehane","Dennis","American",1965,true);
        auto* mccormac  = bib.gasesteOrAdaugaAutor("McCarthy","Cormac","American",1933,true);
        auto* atwood    = bib.gasesteOrAdaugaAutor("Atwood","Margaret","Canadiana",1939,true);
        auto* ishiguro  = bib.gasesteOrAdaugaAutor("Ishiguro","Kazuo","Japonez-Britanic",1954,true);
        auto* le_carre  = bib.gasesteOrAdaugaAutor("le Carre","John","Britanic",1931,false);
        auto* follett   = bib.gasesteOrAdaugaAutor("Follett","Ken","Britanic",1949,true);
        auto* cornwell  = bib.gasesteOrAdaugaAutor("Cornwell","Bernard","Britanic",1944,true);
        auto* fforde    = bib.gasesteOrAdaugaAutor("Fforde","Jasper","Britanic",1961,true);
        auto* proulx    = bib.gasesteOrAdaugaAutor("Proulx","Annie","Americana",1935,true);
        auto* auster    = bib.gasesteOrAdaugaAutor("Auster","Paul","American",1947,true);
        auto* pamuk     = bib.gasesteOrAdaugaAutor("Pamuk","Orhan","Turc",1952,true);
        auto* grass     = bib.gasesteOrAdaugaAutor("Grass","Gunter","German",1927,false);
        auto* moravia   = bib.gasesteOrAdaugaAutor("Moravia","Alberto","Italian",1907,false);
        auto* calvino   = bib.gasesteOrAdaugaAutor("Calvino","Italo","Italian",1923,false);
        auto* bukowski  = bib.gasesteOrAdaugaAutor("Bukowski","Charles","American",1920,false);
        auto* kerouac   = bib.gasesteOrAdaugaAutor("Kerouac","Jack","American",1922,false);
        auto* salinger  = bib.gasesteOrAdaugaAutor("Salinger","J.D.","American",1919,false);
        auto* fitzgerald= bib.gasesteOrAdaugaAutor("Fitzgerald","F. Scott","American",1896,false);
        auto* faulkner  = bib.gasesteOrAdaugaAutor("Faulkner","William","American",1897,false);
        auto* steinbeck = bib.gasesteOrAdaugaAutor("Steinbeck","John","American",1902,false);
        auto* orhan     = bib.gasesteOrAdaugaAutor("Pamuk","Orhan","Turc",1952,true);
        auto* dosto2    = dostoev;
        // Distopie si SF aditional
        adaugaCF(bib,"ISBN-F106","The Handmaid Tale",atwood,humanitas,2020,"Distopie",18,311,34.99,25);
        adaugaCF(bib,"ISBN-F107","Alias Grace",atwood,humanitas,2021,"Roman",18,460,38.99,12);
        adaugaCF(bib,"ISBN-F108","Never Let Me Go",ishiguro,humanitas,2021,"SF",16,288,32.99,18);
        adaugaCF(bib,"ISBN-F109","The Remains of the Day",ishiguro,humanitas,2020,"Roman",16,245,28.99,15);
        adaugaCF(bib,"ISBN-F110","The Road",mccormac,pandora,2020,"Distopie",18,287,30.99,20);
        adaugaCF(bib,"ISBN-F111","No Country for Old Men",mccormac,pandora,2021,"Thriller",18,309,30.99,12);
        adaugaCF(bib,"ISBN-F112","The Spy Who Came in from the Cold",le_carre,rao,2019,"Thriller spionaj",16,216,26.99,15);
        adaugaCF(bib,"ISBN-F113","Tinker Tailor Soldier Spy",le_carre,rao,2020,"Thriller spionaj",16,388,32.99,10);
        adaugaCF(bib,"ISBN-F114","The Pillars of the Earth",follett,litera,2020,"Roman istoric",14,973,55.99,18,"Kingsbridge",1);
        adaugaCF(bib,"ISBN-F115","World Without End",follett,litera,2021,"Roman istoric",14,1024,55.99,12,"Kingsbridge",2);
        // Fantasy aditional
        adaugaCF(bib,"ISBN-F116","Outlander",gabaldon,rao,2020,"Fantasy romantic",18,850,55.99,15,"Outlander",1);
        adaugaCF(bib,"ISBN-F117","Dragonfly in Amber",gabaldon,rao,2021,"Fantasy romantic",18,752,52.99,10,"Outlander",2);
        adaugaCF(bib,"ISBN-F118","Twilight",meyer,rao,2020,"Fantasy romantic",14,498,39.99,30,"Twilight",1);
        adaugaCF(bib,"ISBN-F119","New Moon",meyer,rao,2020,"Fantasy romantic",14,563,39.99,25,"Twilight",2);
        adaugaCF(bib,"ISBN-F120","Eclipse",meyer,rao,2021,"Fantasy romantic",14,629,39.99,20,"Twilight",3);
        adaugaCF(bib,"ISBN-F121","The Hunger Games",collins,nemira,2020,"SF Distopie",14,374,35.99,45,"Hunger Games",1);
        adaugaCF(bib,"ISBN-F122","Catching Fire",collins,nemira,2020,"SF Distopie",14,391,35.99,35,"Hunger Games",2);
        adaugaCF(bib,"ISBN-F123","Mockingjay",collins,nemira,2021,"SF Distopie",14,390,35.99,28,"Hunger Games",3);
        adaugaCF(bib,"ISBN-F124","The Lightning Thief",riordan,rao,2020,"Fantasy Mitologie",10,377,35.99,30,"Percy Jackson",1);
        adaugaCF(bib,"ISBN-F125","Sea of Monsters",riordan,rao,2020,"Fantasy Mitologie",10,279,32.99,22,"Percy Jackson",2);
        adaugaCF(bib,"ISBN-F126","The Titan Curse",riordan,rao,2021,"Fantasy Mitologie",10,312,32.99,18,"Percy Jackson",3);
        // Horror suplimentar
        adaugaCF(bib,"ISBN-F127","Dracula",bib.gasesteOrAdaugaAutor("Stoker","Bram","Irlandez",1847,false),nemira,2019,"Horror",16,418,35.99,25);
        adaugaCF(bib,"ISBN-F128","Frankenstein",bib.gasesteOrAdaugaAutor("Shelley","Mary","Britanica",1797,false),humanitas,2020,"Horror",16,232,24.99,20);
        adaugaCF(bib,"ISBN-F129","The Call of Cthulhu",bib.gasesteOrAdaugaAutor("Lovecraft","H.P.","American",1890,false),nemira,2019,"Horror",18,204,22.99,15);
        adaugaCF(bib,"ISBN-F130","Haunting of Hill House",bib.gasesteOrAdaugaAutor("Jackson","Shirley","Americana",1916,false),nemira,2021,"Horror",18,246,28.99,10);
        adaugaCF(bib,"ISBN-F131","We Need to Talk About Kevin",bib.gasesteOrAdaugaAutor("Shriver","Lionel","Americana",1957,true),litera,2021,"Thriller psihologic",18,400,35.99,12);
        adaugaCF(bib,"ISBN-F132","Behind Closed Doors",bib.gasesteOrAdaugaAutor("Paris","B.A.","Britanica",1957,true),litera,2022,"Thriller psihologic",18,294,28.99,15);
        // Roman contemporan
        adaugaCF(bib,"ISBN-F133","The Kite Runner",hosseini,rao,2019,"Roman",16,371,34.99,30);
        adaugaCF(bib,"ISBN-F134","A Thousand Splendid Suns",hosseini,rao,2020,"Roman",16,372,34.99,25);
        adaugaCF(bib,"ISBN-F135","The Thief of Always",bib.gasesteOrAdaugaAutor("Barker","Clive","Britanic",1952,true),litera,2021,"Fantasy Horror",14,245,24.99,8);
        adaugaCF(bib,"ISBN-F136","The Book Thief",zusak,humanitas,2020,"Roman",14,550,39.99,25);
        adaugaCF(bib,"ISBN-F137","My Sisters Keeper",picoult,litera,2020,"Roman contemporan",16,432,35.99,18);
        adaugaCF(bib,"ISBN-F138","Change of Heart",picoult,litera,2021,"Roman contemporan",16,447,35.99,12);
        adaugaCF(bib,"ISBN-F139","Mystic River",lehane,litera,2020,"Thriller",16,401,35.99,15);
        adaugaCF(bib,"ISBN-F140","Gone Baby Gone",lehane,litera,2021,"Thriller",16,397,34.99,10);
        // Clasici americani
        adaugaCF(bib,"ISBN-F141","The Great Gatsby",fitzgerald,humanitas,2019,"Roman clasic",16,192,22.99,28);
        adaugaCF(bib,"ISBN-F142","The Catcher in the Rye",salinger,humanitas,2020,"Roman",16,277,25.99,22);
        adaugaCF(bib,"ISBN-F143","On the Road",kerouac,humanitas,2019,"Roman",18,307,27.99,15);
        adaugaCF(bib,"ISBN-F144","Post Office",bukowski,humanitas,2020,"Roman",18,208,22.99,12);
        adaugaCF(bib,"ISBN-F145","Ham on Rye",bukowski,humanitas,2021,"Autobiografic",18,320,25.99,10);
        adaugaCF(bib,"ISBN-F146","The Grapes of Wrath",steinbeck,humanitas,2020,"Roman social",16,464,37.99,12);
        adaugaCF(bib,"ISBN-F147","Of Mice and Men",steinbeck,humanitas,2019,"Nuvela",14,105,15.99,20);
        adaugaCF(bib,"ISBN-F148","East of Eden",steinbeck,humanitas,2021,"Roman",16,601,45.99,8);
        adaugaCF(bib,"ISBN-F149","The Sound and the Fury",faulkner,humanitas,2020,"Roman",18,326,28.99,7);
        adaugaCF(bib,"ISBN-F150","To Kill a Mockingbird",bib.gasesteOrAdaugaAutor("Lee","Harper","Americana",1926,false),humanitas,2019,"Roman clasic",14,281,26.99,30);
        // Cyberpunk si SF modern
        adaugaCF(bib,"ISBN-F151","Ready Player One",bib.gasesteOrAdaugaAutor("Cline","Ernest","American",1972,true),rao,2021,"SF Cyberpunk",14,374,35.99,25);
        adaugaCF(bib,"ISBN-F152","All Systems Red",bib.gasesteOrAdaugaAutor("Wells","Martha","Americana",1964,true),nemira,2022,"SF",14,156,24.99,15,"Murderbot",1);
        adaugaCF(bib,"ISBN-F153","Leviathan Wakes",bib.gasesteOrAdaugaAutor("Corey","James S.A.","American",1969,true),nemira,2021,"SF",16,561,45.99,18,"Expanse",1);
        adaugaCF(bib,"ISBN-F154","Caliban War",bib.gasesteOrAdaugaAutor("Corey","James S.A.","American",1969,true),nemira,2022,"SF",16,595,45.99,12,"Expanse",2);
        adaugaCF(bib,"ISBN-F155","Old Mans War",bib.gasesteOrAdaugaAutor("Scalzi","John","American",1969,true),nemira,2021,"SF",16,351,39.99,15);
        adaugaCF(bib,"ISBN-F156","The Long Way to a Small Angry Planet",bib.gasesteOrAdaugaAutor("Chambers","Becky","Americana",1985,true),nemira,2022,"SF",14,404,39.99,12);
        adaugaCF(bib,"ISBN-F157","Annihilation",bib.gasesteOrAdaugaAutor("VanderMeer","Jeff","American",1968,true),nemira,2022,"SF Mister",16,195,28.99,10);
        // Roman gotic si atmospheric
        adaugaCF(bib,"ISBN-F158","Jane Eyre",bib.gasesteOrAdaugaAutor("Bronte","Charlotte","Britanica",1816,false),humanitas,2020,"Roman gotic",14,507,35.99,18);
        adaugaCF(bib,"ISBN-F159","Wuthering Heights",bib.gasesteOrAdaugaAutor("Bronte","Emily","Britanica",1818,false),humanitas,2019,"Roman gotic",16,352,28.99,15);
        adaugaCF(bib,"ISBN-F160","Rebecca",bib.gasesteOrAdaugaAutor("du Maurier","Daphne","Britanica",1907,false),humanitas,2021,"Roman gotic",16,449,32.99,20);
        adaugaCF(bib,"ISBN-F161","The Picture of Dorian Gray",wilde,humanitas,2020,"Roman gotic",16,254,25.99,20);
        adaugaCF(bib,"ISBN-F162","Perfume Story of a Murderer",bib.gasesteOrAdaugaAutor("Suskind","Patrick","German",1949,true),litera,2019,"Roman",16,248,26.99,15);
        // Realism magic
        adaugaCF(bib,"ISBN-F163","Like Water for Chocolate",bib.gasesteOrAdaugaAutor("Esquivel","Laura","Mexicana",1950,true),litera,2021,"Realism magic",16,245,25.99,12);
        adaugaCF(bib,"ISBN-F164","The House of the Spirits",bib.gasesteOrAdaugaAutor("Allende","Isabel","Chiliana",1942,true),litera,2020,"Realism magic",16,433,34.99,15);
        adaugaCF(bib,"ISBN-F165","Love in the Time of Cholera",marquez,rao,2020,"Roman",16,384,37.99,15);
        // Satira si comedie
        adaugaCF(bib,"ISBN-F166","Catch-22",bib.gasesteOrAdaugaAutor("Heller","Joseph","American",1923,false),humanitas,2021,"Satira",18,453,35.99,12);
        adaugaCF(bib,"ISBN-F167","Slaughterhouse Five",bib.gasesteOrAdaugaAutor("Vonnegut","Kurt","American",1922,false),humanitas,2020,"SF Satira",18,215,24.99,15);
        adaugaCF(bib,"ISBN-F168","The Hitchhikers Guide Restaurant End Universe",adams,humanitas,2020,"SF Comedie",12,193,30.99,20,"HHGTTG",2);
        adaugaCF(bib,"ISBN-F169","Life the Universe and Everything",adams,humanitas,2021,"SF Comedie",12,224,30.99,15,"HHGTTG",3);
        // Literatura romana contemporana
        adaugaCF(bib,"ISBN-F170","Orbitor Aripa Stanga",cartarescu,humanitas,2020,"Roman",18,412,49.99,8,"Orbitor",1);
        adaugaCF(bib,"ISBN-F171","Orbitor Corpul",cartarescu,humanitas,2021,"Roman",18,456,49.99,6,"Orbitor",2);
        adaugaCF(bib,"ISBN-F172","Evenimentul",bib.gasesteOrAdaugaAutor("Tataru","Claudiu","Roman",1973,true),humanitas,2022,"Roman",18,280,32.99,5);
        adaugaCF(bib,"ISBN-F173","Viata si Opiniile lui Zacharias Lichter",bib.gasesteOrAdaugaAutor("Calinescu","Matei","Roman",1934,false),humanitas,2019,"Roman",18,207,24.99,8);
        adaugaCF(bib,"ISBN-F174","Groapa",bib.gasesteOrAdaugaAutor("Eugen","Barbu","Roman",1924,false),minerva,2020,"Roman",16,430,30.99,10);
        adaugaCF(bib,"ISBN-F175","Patul lui Procust",petrescu,humanitas,2021,"Roman",18,312,28.99,12);
    }

    // ===================================================================
    // CARTI TEHNICA
    // ===================================================================
    static void seedCartiTehnica(Biblioteca& bib)
    {
        auto* oreilly  = bib.gasesteOrAdaugaEditura("O'Reilly Media","USA","Sebastopol");
        auto* prentice = bib.gasesteOrAdaugaEditura("Prentice Hall","USA","New Jersey");
        auto* addison  = bib.gasesteOrAdaugaEditura("Addison-Wesley","USA","Boston");
        auto* manning  = bib.gasesteOrAdaugaEditura("Manning Publications","USA","Shelter Island");
        auto* packt    = bib.gasesteOrAdaugaEditura("Packt Publishing","UK","Birmingham");
        auto* nostarch = bib.gasesteOrAdaugaEditura("No Starch Press","USA","San Francisco");

        auto* martin_r  = bib.gasesteOrAdaugaAutor("Martin","Robert C.","American",1952,true);
        auto* gamma     = bib.gasesteOrAdaugaAutor("Gamma","Erich","German",1961,true);
        auto* fowler    = bib.gasesteOrAdaugaAutor("Fowler","Martin","Britanic",1963,true);
        auto* knuth     = bib.gasesteOrAdaugaAutor("Knuth","Donald","American",1938,true);
        auto* stroustrup= bib.gasesteOrAdaugaAutor("Stroustrup","Bjarne","Danez",1950,true);
        auto* kernighan = bib.gasesteOrAdaugaAutor("Kernighan","Brian","Canadian",1942,true);
        auto* tanenbaum = bib.gasesteOrAdaugaAutor("Tanenbaum","Andrew","American",1944,true);
        auto* cormen    = bib.gasesteOrAdaugaAutor("Cormen","Thomas","American",1956,true);
        auto* meyers    = bib.gasesteOrAdaugaAutor("Meyers","Scott","American",1959,true);
        auto* hunt      = bib.gasesteOrAdaugaAutor("Hunt","Andrew","American",1964,true);
        auto* lutz      = bib.gasesteOrAdaugaAutor("Lutz","Mark","American",1956,true);
        auto* evans     = bib.gasesteOrAdaugaAutor("Evans","Eric","American",1963,true);

        // C++ - foarte cerut de studenti
        adaugaCT(bib,"ISBN-T001","Clean Code",martin_r,prentice,2008,"Software Engineering","Avansat",431,89.99,20);
        adaugaCT(bib,"ISBN-T002","The C++ Programming Language",stroustrup,addison,2013,"C++","Avansat",1368,125.99,15);
        adaugaCT(bib,"ISBN-T003","The C Programming Language",kernighan,prentice,1988,"C","Intermediar",274,79.99,18);
        adaugaCT(bib,"ISBN-T004","Effective C++",meyers,addison,2005,"C++","Intermediar",320,79.99,12);
        adaugaCT(bib,"ISBN-T005","Effective Modern C++",meyers,oreilly,2014,"C++","Avansat",334,85.99,10);
        adaugaCT(bib,"ISBN-T006","C++ Primer Plus",bib.gasesteOrAdaugaAutor("Prata","Stephen","American",1948,true),addison,2011,"C++","Incepator",1200,85.99,25);
        adaugaCT(bib,"ISBN-T007","C++ Concurrency in Action",bib.gasesteOrAdaugaAutor("Williams","Anthony","Britanic",1972,true),manning,2019,"C++","Avansat",592,79.99,8);
        adaugaCT(bib,"ISBN-T008","Modern C++ Design",bib.gasesteOrAdaugaAutor("Alexandrescu","Andrei","Roman",1975,true),addison,2001,"C++","Avansat",352,89.99,8);
        adaugaCT(bib,"ISBN-T009","More Effective C++",meyers,addison,1996,"C++","Avansat",336,79.99,7);
        adaugaCT(bib,"ISBN-T010","Functional Programming in C++",bib.gasesteOrAdaugaAutor("Cukic","Ivan","Serbian",1981,true),manning,2018,"C++","Avansat",320,69.99,5);
        adaugaCT(bib,"ISBN-T011","C++ Templates The Complete Guide",bib.gasesteOrAdaugaAutor("Vandevoorde","David","Belgian",1966,true),addison,2017,"C++","Avansat",840,99.99,4);
        adaugaCT(bib,"ISBN-T012","Beginning C++ Through Game Programming",bib.gasesteOrAdaugaAutor("Dawson","Michael","American",1974,true),addison,2015,"C++","Incepator",390,55.99,20);
        // Python
        adaugaCT(bib,"ISBN-T013","Learning Python",lutz,oreilly,2013,"Python","Incepator",1540,99.99,20);
        adaugaCT(bib,"ISBN-T014","Fluent Python",bib.gasesteOrAdaugaAutor("Ramalho","Luciano","Brazilian",1967,true),oreilly,2015,"Python","Avansat",792,89.99,10);
        adaugaCT(bib,"ISBN-T015","Automate the Boring Stuff",bib.gasesteOrAdaugaAutor("Sweigart","Al","American",1985,true),nostarch,2019,"Python","Incepator",580,49.99,25);
        adaugaCT(bib,"ISBN-T016","Python Cookbook",bib.gasesteOrAdaugaAutor("Beazley","David","American",1967,true),oreilly,2013,"Python","Intermediar",706,85.99,8);
        adaugaCT(bib,"ISBN-T017","Python for Everybody",bib.gasesteOrAdaugaAutor("Severance","Charles","American",1961,true),addison,2016,"Python","Incepator",244,45.99,28);
        adaugaCT(bib,"ISBN-T018","Python Tricks",bib.gasesteOrAdaugaAutor("Bader","Dan","German",1988,true),addison,2017,"Python","Intermediar",302,49.99,15);
        adaugaCT(bib,"ISBN-T019","Head First Python",bib.gasesteOrAdaugaAutor("Barry","Paul","Irlandez",1967,true),oreilly,2016,"Python","Incepator",624,65.99,18);
        adaugaCT(bib,"ISBN-T020","Python Machine Learning",bib.gasesteOrAdaugaAutor("Raschka","Sebastian","German",1988,true),packt,2019,"Python",  "Intermediar",770,79.99,12);
        // Algoritmi si structuri de date
        adaugaCT(bib,"ISBN-T021","Introduction to Algorithms",cormen,addison,2009,"Algoritmi","Avansat",1292,125.99,15);
        adaugaCT(bib,"ISBN-T022","The Art of Computer Programming vol 1",knuth,addison,2011,"Algoritmi","Avansat",672,120.99,5);
        adaugaCT(bib,"ISBN-T023","The Art of Computer Programming vol 2",knuth,addison,2014,"Algoritmi","Avansat",784,120.99,4);
        adaugaCT(bib,"ISBN-T024","The Algorithm Design Manual",bib.gasesteOrAdaugaAutor("Skiena","Steven","American",1961,true),addison,2020,"Algoritmi","Intermediar",800,89.99,10);
        adaugaCT(bib,"ISBN-T025","Cracking the Coding Interview",bib.gasesteOrAdaugaAutor("McDowell","Gayle","Americana",1982,true),addison,2015,"Algoritmi","Intermediar",696,55.99,30);
        adaugaCT(bib,"ISBN-T026","Competitive Programming",bib.gasesteOrAdaugaAutor("Halim","Steven","Singaporean",1983,true),addison,2013,"Algoritmi","Avansat",433,75.99,8);
        // Java
        adaugaCT(bib,"ISBN-T027","Effective Java",bib.gasesteOrAdaugaAutor("Bloch","Joshua","American",1961,true),addison,2018,"Java","Avansat",412,89.99,12);
        adaugaCT(bib,"ISBN-T028","Head First Java",bib.gasesteOrAdaugaAutor("Sierra","Kathy","Americana",1957,true),oreilly,2005,"Java","Incepator",688,75.99,20);
        adaugaCT(bib,"ISBN-T029","Java The Complete Reference",bib.gasesteOrAdaugaAutor("Schildt","Herbert","American",1952,true),addison,2018,"Java","Intermediar",1248,99.99,10);
        adaugaCT(bib,"ISBN-T030","Spring in Action",bib.gasesteOrAdaugaAutor("Walls","Craig","American",1967,true),manning,2018,"Java","Intermediar",520,79.99,8);
        // Machine Learning si AI
        adaugaCT(bib,"ISBN-T031","Hands-On Machine Learning",bib.gasesteOrAdaugaAutor("Geron","Aurelien","Francez",1975,true),oreilly,2019,"Machine Learning","Intermediar",856,95.99,15);
        adaugaCT(bib,"ISBN-T032","Deep Learning",bib.gasesteOrAdaugaAutor("Goodfellow","Ian","Canadian",1985,true),addison,2016,"Machine Learning","Avansat",800,119.99,8);
        adaugaCT(bib,"ISBN-T033","Pattern Recognition and ML",bib.gasesteOrAdaugaAutor("Bishop","Christopher","Britanic",1959,true),addison,2006,"Machine Learning","Avansat",738,115.99,6);
        adaugaCT(bib,"ISBN-T034","Reinforcement Learning",bib.gasesteOrAdaugaAutor("Sutton","Richard","Canadian",1956,true),addison,2018,"AI","Avansat",526,89.99,5);
        adaugaCT(bib,"ISBN-T035","Python for Data Analysis",bib.gasesteOrAdaugaAutor("McKinney","Wes","American",1985,true),oreilly,2017,"Data Science","Intermediar",544,85.99,12);
        adaugaCT(bib,"ISBN-T036","Data Science from Scratch",bib.gasesteOrAdaugaAutor("Grus","Joel","American",1980,true),oreilly,2019,"Data Science","Incepator",406,65.99,15);
        adaugaCT(bib,"ISBN-T037","Natural Language Processing",bib.gasesteOrAdaugaAutor("Bird","Steven","Australian",1968,true),oreilly,2009,"NLP","Intermediar",504,75.99,8);
        adaugaCT(bib,"ISBN-T038","Speech and Language Processing",bib.gasesteOrAdaugaAutor("Jurafsky","Daniel","American",1962,true),prentice,2022,"NLP","Avansat",632,99.99,5);
        adaugaCT(bib,"ISBN-T039","Computer Vision",bib.gasesteOrAdaugaAutor("Szeliski","Richard","American",1958,true),addison,2022,"Computer Vision","Avansat",932,109.99,4);
        adaugaCT(bib,"ISBN-T040","TensorFlow in Action",bib.gasesteOrAdaugaAutor("Madhavan","Thushan","Sri Lankan",1988,true),manning,2022,"TensorFlow","Intermediar",424,69.99,10);
        // Software Engineering
        adaugaCT(bib,"ISBN-T041","Design Patterns",gamma,prentice,1994,"Software Engineering","Avansat",395,95.99,15);
        adaugaCT(bib,"ISBN-T042","Refactoring",fowler,addison,1999,"Software Engineering","Intermediar",448,89.99,12);
        adaugaCT(bib,"ISBN-T043","Clean Architecture",martin_r,prentice,2017,"Software Engineering","Avansat",432,89.99,15);
        adaugaCT(bib,"ISBN-T044","The Pragmatic Programmer",hunt,addison,2019,"Software Engineering","Intermediar",352,79.99,18);
        adaugaCT(bib,"ISBN-T045","Domain-Driven Design",evans,addison,2003,"Software Engineering","Avansat",560,89.99,8);
        adaugaCT(bib,"ISBN-T046","Code Complete",bib.gasesteOrAdaugaAutor("McConnell","Steve","American",1962,true),addison,2004,"Software Engineering","Intermediar",960,95.99,10);
        adaugaCT(bib,"ISBN-T047","Head First Design Patterns",bib.gasesteOrAdaugaAutor("Freeman","Eric","American",1965,true),oreilly,2020,"OOP","Intermediar",672,75.99,15);
        adaugaCT(bib,"ISBN-T048","Test Driven Development",bib.gasesteOrAdaugaAutor("Beck","Kent","American",1961,true),addison,2002,"Software Engineering","Intermediar",240,75.99,10);
        // Retele si sisteme
        adaugaCT(bib,"ISBN-T049","Modern Operating Systems",tanenbaum,prentice,2014,"Sisteme de Operare","Avansat",1136,115.99,10);
        adaugaCT(bib,"ISBN-T050","Computer Networks",tanenbaum,prentice,2010,"Retele","Intermediar",960,110.99,10);
        adaugaCT(bib,"ISBN-T051","TCP/IP Illustrated vol 1",bib.gasesteOrAdaugaAutor("Stevens","W. Richard","American",1951,false),addison,2011,"Retele","Avansat",1032,89.99,6);
        adaugaCT(bib,"ISBN-T052","The Linux Command Line",bib.gasesteOrAdaugaAutor("Shotts","William","American",1962,true),nostarch,2019,"Linux","Incepator",480,65.99,20);
        adaugaCT(bib,"ISBN-T053","Linux Kernel Development",bib.gasesteOrAdaugaAutor("Love","Robert","American",1981,true),addison,2010,"Linux","Avansat",440,89.99,5);
        // DevOps si Cloud
        adaugaCT(bib,"ISBN-T054","Building Microservices",bib.gasesteOrAdaugaAutor("Newman","Sam","Britanic",1978,true),oreilly,2021,"Microservicii","Avansat",640,85.99,10);
        adaugaCT(bib,"ISBN-T055","Kubernetes in Action",bib.gasesteOrAdaugaAutor("Luksa","Marko","Slovenian",1979,true),manning,2017,"Cloud","Intermediar",624,89.99,8);
        adaugaCT(bib,"ISBN-T056","Docker Deep Dive",bib.gasesteOrAdaugaAutor("Poulton","Nigel","Britanic",1981,true),packt,2020,"Cloud","Incepator",260,65.99,15);
        adaugaCT(bib,"ISBN-T057","Site Reliability Engineering",bib.gasesteOrAdaugaAutor("Beyer","Betsy","Americana",1983,true),oreilly,2016,"DevOps","Avansat",552,95.99,6);
        adaugaCT(bib,"ISBN-T058","The Phoenix Project",bib.gasesteOrAdaugaAutor("Kim","Gene","American",1971,true),oreilly,2013,"DevOps","Incepator",432,69.99,12);
        adaugaCT(bib,"ISBN-T059","Pro Git",bib.gasesteOrAdaugaAutor("Chacon","Scott","American",1980,true),addison,2014,"Git","Incepator",440,55.99,22);
        adaugaCT(bib,"ISBN-T060","AWS in Action",bib.gasesteOrAdaugaAutor("Wittig","Andreas","German",1983,true),manning,2019,"AWS","Intermediar",528,79.99,7);
        // Baze de date
        adaugaCT(bib,"ISBN-T061","Designing Data-Intensive Applications",bib.gasesteOrAdaugaAutor("Kleppmann","Martin","German",1984,true),oreilly,2017,"Baze de Date","Avansat",616,99.99,12);
        adaugaCT(bib,"ISBN-T062","Database System Concepts",bib.gasesteOrAdaugaAutor("Silberschatz","Abraham","American",1952,true),addison,2019,"Baze de Date","Intermediar",1376,115.99,10);
        adaugaCT(bib,"ISBN-T063","High Performance MySQL",bib.gasesteOrAdaugaAutor("Schwartz","Baron","Canadian",1978,true),oreilly,2012,"MySQL","Avansat",828,89.99,5);
        adaugaCT(bib,"ISBN-T064","MongoDB The Definitive Guide",bib.gasesteOrAdaugaAutor("Chodorow","Kristina","Americana",1983,true),oreilly,2019,"MongoDB","Intermediar",514,75.99,6);
        // Securitate
        adaugaCT(bib,"ISBN-T065","Hacking The Art of Exploitation",bib.gasesteOrAdaugaAutor("Erickson","Jon","American",1980,true),nostarch,2008,"Securitate","Avansat",488,79.99,8);
        adaugaCT(bib,"ISBN-T066","Applied Cryptography",bib.gasesteOrAdaugaAutor("Schneier","Bruce","American",1963,true),addison,2015,"Criptografie","Avansat",784,89.99,6);
        adaugaCT(bib,"ISBN-T067","Penetration Testing",bib.gasesteOrAdaugaAutor("Georgia","Weidman","Americana",1984,true),nostarch,2014,"Securitate","Intermediar",528,79.99,8);
        adaugaCT(bib,"ISBN-T068","The Web Application Hackers Handbook",bib.gasesteOrAdaugaAutor("Stuttard","Dafydd","Britanic",1975,true),addison,2011,"Securitate","Avansat",912,89.99,5);
        // Web si JavaScript
        adaugaCT(bib,"ISBN-T069","JavaScript The Good Parts",bib.gasesteOrAdaugaAutor("Crockford","Douglas","American",1955,true),oreilly,2008,"JavaScript","Intermediar",172,59.99,15);
        adaugaCT(bib,"ISBN-T070","Eloquent JavaScript",bib.gasesteOrAdaugaAutor("Haverbeke","Marijn","Olandez",1982,true),nostarch,2018,"JavaScript","Intermediar",472,65.99,18);
        adaugaCT(bib,"ISBN-T071","Learning React",bib.gasesteOrAdaugaAutor("Banks","Alex","American",1978,true),oreilly,2020,"React","Intermediar",312,69.99,12);
        adaugaCT(bib,"ISBN-T072","HTML and CSS Design and Build",bib.gasesteOrAdaugaAutor("Duckett","Jon","Britanic",1974,true),addison,2011,"Web","Incepator",490,55.99,20);
        adaugaCT(bib,"ISBN-T073","Node.js Design Patterns",bib.gasesteOrAdaugaAutor("Casciaro","Mario","Italian",1984,true),packt,2020,"Node.js","Avansat",660,79.99,7);
        adaugaCT(bib,"ISBN-T074","TypeScript Quickly",bib.gasesteOrAdaugaAutor("Fain","Yakov","American",1962,true),manning,2020,"TypeScript","Intermediar",464,69.99,8);
        adaugaCT(bib,"ISBN-T075","Vue.js in Action",bib.gasesteOrAdaugaAutor("Hanchett","Erik","American",1978,true),manning,2018,"Vue.js","Intermediar",304,65.99,6);
        adaugaCT(bib,"ISBN-T076","Angular in Action",bib.gasesteOrAdaugaAutor("Wilken","Jeremy","American",1982,true),manning,2018,"Angular","Intermediar",296,65.99,6);
        // Game Dev si altele
        adaugaCT(bib,"ISBN-T077","Game Engine Architecture",bib.gasesteOrAdaugaAutor("Gregory","Jason","American",1971,true),prentice,2018,"Game Dev","Avansat",1042,109.99,4);
        adaugaCT(bib,"ISBN-T078","Real Time Rendering",bib.gasesteOrAdaugaAutor("Akenine-Moller","Tomas","Suedez",1971,true),prentice,2018,"Game Dev","Avansat",1198,115.99,3);
        adaugaCT(bib,"ISBN-T079","Programming Arduino",bib.gasesteOrAdaugaAutor("Monk","Simon","Britanic",1957,true),addison,2016,"Arduino","Incepator",208,45.99,15);
        adaugaCT(bib,"ISBN-T080","Raspberry Pi Cookbook",bib.gasesteOrAdaugaAutor("Monk","Simon","Britanic",1957,true),oreilly,2016,"Raspberry Pi","Incepator",412,55.99,10);
        // Rust si Go
        adaugaCT(bib,"ISBN-T081","Programming Rust",bib.gasesteOrAdaugaAutor("Blandy","Jim","American",1972,true),oreilly,2021,"Rust","Intermediar",622,79.99,8);
        adaugaCT(bib,"ISBN-T082","The Rust Programming Language",bib.gasesteOrAdaugaAutor("Klabnik","Steve","American",1986,true),nostarch,2022,"Rust","Incepator",560,55.99,12);
        adaugaCT(bib,"ISBN-T083","The Go Programming Language",bib.gasesteOrAdaugaAutor("Donovan","Alan","American",1967,true),addison,2015,"Go","Intermediar",380,65.99,10);
        adaugaCT(bib,"ISBN-T084","Programming Go",bib.gasesteOrAdaugaAutor("Calvert","Charles","American",1963,true),manning,2021,"Go","Intermediar",400,69.99,7);
        // Cariera si management
        adaugaCT(bib,"ISBN-T085","The Mythical Man Month",bib.gasesteOrAdaugaAutor("Brooks","Fred","American",1931,false),addison,1995,"Management","Intermediar",336,69.99,8);
        adaugaCT(bib,"ISBN-T086","Soft Skills",bib.gasesteOrAdaugaAutor("Sonmez","John","American",1980,true),manning,2014,"Cariera","Incepator",470,55.99,12);
        adaugaCT(bib,"ISBN-T087","The Managers Path",bib.gasesteOrAdaugaAutor("Fournier","Camille","Americana",1981,true),oreilly,2017,"Management","Intermediar",244,55.99,8);
        adaugaCT(bib,"ISBN-T088","An Elegant Puzzle",bib.gasesteOrAdaugaAutor("Larson","Will","American",1983,true),addison,2019,"Engineering Management","Intermediar",280,55.99,6);
        adaugaCT(bib,"ISBN-T089","System Design Interview",bib.gasesteOrAdaugaAutor("Xu","Alex","Chinese-American",1985,true),addison,2020,"Interviuri","Intermediar",309,49.99,25);
        adaugaCT(bib,"ISBN-T090","A Philosophy of Software Design",bib.gasesteOrAdaugaAutor("Ousterhout","John","American",1954,true),addison,2018,"Software Engineering","Intermediar",190,45.99,10);
        // Arhitectura calculator
        adaugaCT(bib,"ISBN-T091","Computer Architecture",bib.gasesteOrAdaugaAutor("Patterson","David","American",1947,true),addison,2017,"Arhitectura","Avansat",800,115.99,6);
        adaugaCT(bib,"ISBN-T092","Computer Organization and Design",bib.gasesteOrAdaugaAutor("Patterson","David","American",1947,true),addison,2020,"Arhitectura","Avansat",864,99.99,6);
        adaugaCT(bib,"ISBN-T093","Digital Design and Computer Architecture",bib.gasesteOrAdaugaAutor("Harris","David","American",1970,true),addison,2012,"Hardware","Intermediar",712,89.99,5);
        adaugaCT(bib,"ISBN-T094","Structure and Interpretation of Programs",bib.gasesteOrAdaugaAutor("Abelson","Harold","American",1947,true),addison,1996,"Algoritmi","Avansat",657,95.99,5);
        // Big Data si streaming
        adaugaCT(bib,"ISBN-T095","Kafka The Definitive Guide",bib.gasesteOrAdaugaAutor("Shapira","Gwen","Israeliana",1979,true),oreilly,2021,"Streaming","Avansat",302,75.99,6);
        adaugaCT(bib,"ISBN-T096","Spark The Definitive Guide",bib.gasesteOrAdaugaAutor("Chambers","Bill","American",1990,true),oreilly,2018,"Big Data","Avansat",610,89.99,5);
        adaugaCT(bib,"ISBN-T097","Hadoop The Definitive Guide",bib.gasesteOrAdaugaAutor("White","Tom","Britanic",1972,true),oreilly,2015,"Big Data","Intermediar",758,89.99,4);
        adaugaCT(bib,"ISBN-T098","Elasticsearch in Action",bib.gasesteOrAdaugaAutor("Hinman","Matthew","American",1980,true),manning,2015,"Search","Intermediar",482,69.99,5);
        // Microcontrollere si embedded
        adaugaCT(bib,"ISBN-T099","Making Embedded Systems",bib.gasesteOrAdaugaAutor("White","Elecia","Americana",1973,true),oreilly,2011,"Embedded","Intermediar",330,65.99,6);
        adaugaCT(bib,"ISBN-T100","Computer Security Art and Science",bib.gasesteOrAdaugaAutor("Bishop","Matt","American",1956,true),addison,2018,"Securitate","Avansat",1136,115.99,4);
        // Titluri noi tehnica - 2024
        adaugaCT(bib,"ISBN-T101","ChatGPT Prompt Engineering for Developers",bib.gasesteOrAdaugaAutor("Wulfken","Moritz","German",1990,true),oreilly,2023,"AI","Incepator",220,55.99,20);
        adaugaCT(bib,"ISBN-T102","Building LLM Powered Applications",bib.gasesteOrAdaugaAutor("Ozturk","Valentina","Italiana",1988,true),packt,2024,"AI","Intermediar",312,69.99,15);
        adaugaCT(bib,"ISBN-T103","Generative Deep Learning",bib.gasesteOrAdaugaAutor("Foster","David","Britanic",1989,true),oreilly,2023,"Machine Learning","Avansat",456,89.99,8);
        adaugaCT(bib,"ISBN-T104","Practical MLOps",bib.gasesteOrAdaugaAutor("Gift","Noah","American",1972,true),oreilly,2021,"Machine Learning","Intermediar",422,75.99,6);
        adaugaCT(bib,"ISBN-T105","Platform Engineering",bib.gasesteOrAdaugaAutor("Butcher","Matt","American",1978,true),manning,2023,"DevOps","Intermediar",350,69.99,8);
        adaugaCT(bib,"ISBN-T106","Software Architecture Patterns",fowler,oreilly,2023,"Software Engineering","Intermediar",280,45.99,12);
        adaugaCT(bib,"ISBN-T107","Quantum Computing An Applied Approach",bib.gasesteOrAdaugaAutor("Hidary","Jack","American",1968,true),addison,2021,"Quantum","Avansat",422,89.99,3);
        adaugaCT(bib,"ISBN-T108","Blockchain Basics",bib.gasesteOrAdaugaAutor("Drescher","Daniel","German",1971,true),addison,2017,"Blockchain","Incepator",255,55.99,7);
        adaugaCT(bib,"ISBN-T109","Web3 Development",bib.gasesteOrAdaugaAutor("Antonopoulos","Andreas","Grec",1972,true),oreilly,2022,"Blockchain","Intermediar",380,69.99,5);
        adaugaCT(bib,"ISBN-T110","iOS Programming The Big Nerd Ranch",bib.gasesteOrAdaugaAutor("Conway","Joe","American",1972,true),addison,2020,"iOS","Intermediar",576,79.99,6);
        adaugaCT(bib,"ISBN-T111","Android Programming The Big Nerd Ranch",bib.gasesteOrAdaugaAutor("Hardy","Bill","American",1975,true),addison,2019,"Android","Intermediar",576,79.99,8);
        adaugaCT(bib,"ISBN-T112","Flutter in Action",bib.gasesteOrAdaugaAutor("Windmill","Eric","American",1985,true),manning,2020,"Flutter","Intermediar",368,65.99,10);
        adaugaCT(bib,"ISBN-T113","Microservices Patterns",bib.gasesteOrAdaugaAutor("Richardson","Chris","American",1962,true),manning,2018,"Microservicii","Avansat",520,79.99,8);
        adaugaCT(bib,"ISBN-T114","GraphQL in Action",bib.gasesteOrAdaugaAutor("Buna","Samer","Libanezo",1983,true),manning,2021,"GraphQL","Intermediar",392,69.99,6);
        adaugaCT(bib,"ISBN-T115","REST API Design Rulebook",bib.gasesteOrAdaugaAutor("Masse","Mark","American",1971,true),oreilly,2011,"API Design","Intermediar",116,45.99,8);
    }

    // ===================================================================
    // CARTI EDUCATIVA (cu exemplare variabile)
    // ===================================================================
    static void seedCartiEducativa(Biblioteca& bib)
    {
        // Matematica - manuale cls 5-12 (cerute mult - 8-15 ex)
        adaugaCE(bib,"ISBN-E001","Matematica cls 5","Matematica","Real",5,2022,224,25.99,12);
        adaugaCE(bib,"ISBN-E002","Matematica cls 6","Matematica","Real",6,2022,240,25.99,12);
        adaugaCE(bib,"ISBN-E003","Matematica cls 7","Matematica","Real",7,2022,256,27.99,12);
        adaugaCE(bib,"ISBN-E004","Matematica cls 8","Matematica","Real",8,2022,272,27.99,15);
        adaugaCE(bib,"ISBN-E005","Matematica cls 9","Matematica","Real",9,2022,288,29.99,15);
        adaugaCE(bib,"ISBN-E006","Matematica cls 10","Matematica","Real",10,2022,304,29.99,12);
        adaugaCE(bib,"ISBN-E007","Matematica cls 11","Matematica","Real",11,2022,320,32.99,10);
        adaugaCE(bib,"ISBN-E008","Matematica cls 12","Matematica","Real",12,2022,336,32.99,10);
        adaugaCE(bib,"ISBN-E009","Algebra liniara","Matematica","Real",0,2021,312,39.99,20);
        adaugaCE(bib,"ISBN-E010","Analiza matematica vol 1","Matematica","Real",0,2021,428,45.99,18);
        adaugaCE(bib,"ISBN-E011","Analiza matematica vol 2","Matematica","Real",0,2021,398,45.99,15);
        adaugaCE(bib,"ISBN-E012","Probabilitati si statistica","Matematica","Real",0,2022,312,39.99,15);
        adaugaCE(bib,"ISBN-E013","Culegere matematica cls 9-12","Matematica","Real",9,2023,512,45.99,20);
        adaugaCE(bib,"ISBN-E014","Bacalaureat matematica","Matematica","Real",12,2023,288,32.99,25);
        adaugaCE(bib,"ISBN-E015","Matematica pentru olimpici","Matematica","Real",9,2022,384,38.99,8);
        adaugaCE(bib,"ISBN-E016","Calcul diferential si integral","Matematica","Real",0,2021,448,52.99,12);
        adaugaCE(bib,"ISBN-E017","Ecuatii diferentiale","Matematica","Real",0,2020,368,45.99,10);
        adaugaCE(bib,"ISBN-E018","Statistica Aplicata","Statistica","Real",0,2021,416,50.99,10);
        adaugaCE(bib,"ISBN-E019","Geometrie diferentiala","Matematica","Real",0,2020,356,42.99,6);
        adaugaCE(bib,"ISBN-E020","Admitere Politehnica","Matematica","Real",0,2023,384,38.99,15);
        // Fizica
        adaugaCE(bib,"ISBN-E021","Fizica cls 6","Fizica","Real",6,2022,192,22.99,12);
        adaugaCE(bib,"ISBN-E022","Fizica cls 7","Fizica","Real",7,2022,208,24.99,12);
        adaugaCE(bib,"ISBN-E023","Fizica cls 8","Fizica","Real",8,2022,224,24.99,12);
        adaugaCE(bib,"ISBN-E024","Fizica cls 9","Fizica","Real",9,2022,240,26.99,12);
        adaugaCE(bib,"ISBN-E025","Fizica cls 10","Fizica","Real",10,2022,256,26.99,10);
        adaugaCE(bib,"ISBN-E026","Fizica cls 11","Fizica","Real",11,2022,272,28.99,8);
        adaugaCE(bib,"ISBN-E027","Fizica cls 12","Fizica","Real",12,2022,288,28.99,8);
        adaugaCE(bib,"ISBN-E028","Culegere Fizica cls 9-12","Fizica","Real",9,2023,448,39.99,15);
        adaugaCE(bib,"ISBN-E029","Fizica pentru olimpici","Fizica","Real",9,2022,368,37.99,5);
        adaugaCE(bib,"ISBN-E030","Mecanica clasica","Fizica","Real",0,2021,368,42.99,8);
        adaugaCE(bib,"ISBN-E031","Electromagnetism","Fizica","Real",0,2021,412,45.99,8);
        adaugaCE(bib,"ISBN-E032","Fizica cuantica","Fizica","Real",0,2020,448,49.99,6);
        // Chimie
        adaugaCE(bib,"ISBN-E033","Chimie cls 7","Chimie","Real",7,2022,176,22.99,10);
        adaugaCE(bib,"ISBN-E034","Chimie cls 8","Chimie","Real",8,2022,192,22.99,10);
        adaugaCE(bib,"ISBN-E035","Chimie cls 9","Chimie","Real",9,2022,208,24.99,12);
        adaugaCE(bib,"ISBN-E036","Chimie cls 10","Chimie","Real",10,2022,224,24.99,10);
        adaugaCE(bib,"ISBN-E037","Chimie organica cls 11","Chimie","Real",11,2022,256,27.99,8);
        adaugaCE(bib,"ISBN-E038","Chimie anorganica cls 12","Chimie","Real",12,2022,240,27.99,8);
        adaugaCE(bib,"ISBN-E039","Culegere Chimie","Chimie","Real",9,2023,384,38.99,12);
        // Biologie
        adaugaCE(bib,"ISBN-E040","Biologie cls 5","Biologie","Real",5,2022,160,20.99,10);
        adaugaCE(bib,"ISBN-E041","Biologie cls 6","Biologie","Real",6,2022,176,20.99,10);
        adaugaCE(bib,"ISBN-E042","Biologie cls 7","Biologie","Real",7,2022,192,22.99,10);
        adaugaCE(bib,"ISBN-E043","Biologie cls 8","Biologie","Real",8,2022,208,22.99,12);
        adaugaCE(bib,"ISBN-E044","Biologie cls 9","Biologie","Real",9,2022,224,24.99,12);
        adaugaCE(bib,"ISBN-E045","Biologie cls 10","Biologie","Real",10,2022,240,24.99,10);
        adaugaCE(bib,"ISBN-E046","Biologie cls 11","Biologie","Real",11,2022,256,26.99,8);
        adaugaCE(bib,"ISBN-E047","Biologie cls 12","Biologie","Real",12,2022,272,26.99,8);
        adaugaCE(bib,"ISBN-E048","Admitere Medicina","Biologie","Real",0,2023,448,42.99,15);
        // Informatica - ceruta mult la USV
        adaugaCE(bib,"ISBN-E049","Informatica cls 9 C++","Informatica","Real",9,2020,256,32.99,20);
        adaugaCE(bib,"ISBN-E050","Informatica cls 10 C++","Informatica","Real",10,2021,272,32.99,20);
        adaugaCE(bib,"ISBN-E051","Informatica cls 11 C++","Informatica","Real",11,2022,288,32.99,18);
        adaugaCE(bib,"ISBN-E052","Informatica cls 12 C++","Informatica","Real",12,2022,304,34.99,18);
        adaugaCE(bib,"ISBN-E053","Bacalaureat Informatica","Informatica","Real",12,2023,320,35.99,25);
        adaugaCE(bib,"ISBN-E054","Informatica pentru olimpici","Informatica","Real",9,2021,352,36.99,8);
        adaugaCE(bib,"ISBN-E055","Structuri de date si algoritmi","Informatica","Real",0,2021,480,55.99,15);
        adaugaCE(bib,"ISBN-E056","Programare orientata obiect","Informatica","Real",0,2022,416,50.99,18);
        adaugaCE(bib,"ISBN-E057","Baze de date","Informatica","Real",0,2022,368,45.99,15);
        adaugaCE(bib,"ISBN-E058","Retele de calculatoare","Informatica","Real",0,2021,448,52.99,12);
        adaugaCE(bib,"ISBN-E059","Sisteme de operare","Informatica","Real",0,2021,384,48.99,10);
        adaugaCE(bib,"ISBN-E060","Inteligenta Artificiala","Informatica","Real",0,2022,512,58.99,10);
        adaugaCE(bib,"ISBN-E061","Securitate Informatica","Informatica","Real",0,2022,448,54.99,8);
        adaugaCE(bib,"ISBN-E062","Cloud Computing","Informatica","Real",0,2022,384,48.99,6);
        adaugaCE(bib,"ISBN-E063","Internet of Things","Informatica","Real",0,2022,416,50.99,6);
        adaugaCE(bib,"ISBN-E064","Criptografie","Informatica","Real",0,2022,352,45.99,8);
        adaugaCE(bib,"ISBN-E065","Ingineria Programarii","Informatica","Real",0,2021,448,52.99,12);
        adaugaCE(bib,"ISBN-E066","Procesarea Imaginilor","Informatica","Real",0,2022,448,54.99,6);
        adaugaCE(bib,"ISBN-E067","Grafica pe Calculator","Informatica","Real",0,2021,416,50.99,8);
        adaugaCE(bib,"ISBN-E068","Sisteme Expert","Informatica","Real",0,2020,320,42.99,5);
        // Romana si Limbi
        adaugaCE(bib,"ISBN-E069","Limba Romana cls 5","Romana","Uman",5,2022,176,19.99,10);
        adaugaCE(bib,"ISBN-E070","Limba Romana cls 6","Romana","Uman",6,2022,192,19.99,10);
        adaugaCE(bib,"ISBN-E071","Limba Romana cls 7","Romana","Uman",7,2022,208,21.99,10);
        adaugaCE(bib,"ISBN-E072","Limba Romana cls 8","Romana","Uman",8,2022,224,21.99,12);
        adaugaCE(bib,"ISBN-E073","Limba si Literatura Romana cls 9","Romana","Uman",9,2022,240,24.99,12);
        adaugaCE(bib,"ISBN-E074","Limba si Literatura Romana cls 10","Romana","Uman",10,2022,256,24.99,10);
        adaugaCE(bib,"ISBN-E075","Limba si Literatura Romana cls 11","Romana","Uman",11,2022,272,26.99,8);
        adaugaCE(bib,"ISBN-E076","Limba si Literatura Romana cls 12","Romana","Uman",12,2022,288,26.99,8);
        adaugaCE(bib,"ISBN-E077","Bacalaureat Romana","Romana","Uman",12,2023,312,32.99,25);
        adaugaCE(bib,"ISBN-E078","Engleza pentru avansati","Engleza","Uman",0,2021,320,34.99,15);
        adaugaCE(bib,"ISBN-E079","IELTS Academic","Engleza","Uman",0,2022,448,45.99,12);
        adaugaCE(bib,"ISBN-E080","Franceza pentru incepatori","Franceza","Uman",0,2020,256,28.99,8);
        adaugaCE(bib,"ISBN-E081","Germana pentru incepatori","Germana","Uman",0,2020,272,29.99,8);
        adaugaCE(bib,"ISBN-E082","Spaniola pentru incepatori","Spaniola","Uman",0,2021,256,28.99,8);
        adaugaCE(bib,"ISBN-E083","Limba Engleza cls 9","Engleza","Uman",9,2022,208,26.99,12);
        adaugaCE(bib,"ISBN-E084","Limba Engleza cls 10","Engleza","Uman",10,2022,216,26.99,10);
        // Istorie si Geografie
        adaugaCE(bib,"ISBN-E085","Istorie cls 5","Istorie","Uman",5,2022,160,18.99,10);
        adaugaCE(bib,"ISBN-E086","Istorie cls 6","Istorie","Uman",6,2022,176,18.99,10);
        adaugaCE(bib,"ISBN-E087","Istoria Romanilor cls 11","Istorie","Uman",11,2022,256,24.99,10);
        adaugaCE(bib,"ISBN-E088","Bacalaureat Istorie","Istorie","Uman",12,2023,288,30.99,15);
        adaugaCE(bib,"ISBN-E089","Geografie Romania cls 9","Geografie","Uman",9,2022,224,22.99,10);
        adaugaCE(bib,"ISBN-E090","Bacalaureat Geografie","Geografie","Uman",12,2023,264,28.99,15);
        // Drept si Economie (15-25 ex - cerute de student FSEAP)
        adaugaCE(bib,"ISBN-E091","Drept Civil vol 1","Drept","Juridic",0,2021,512,65.99,15);
        adaugaCE(bib,"ISBN-E092","Drept Penal general","Drept","Juridic",0,2021,480,62.99,12);
        adaugaCE(bib,"ISBN-E093","Drept Constitutional","Drept","Juridic",0,2022,512,62.99,12);
        adaugaCE(bib,"ISBN-E094","Drept Administrativ","Drept","Juridic",0,2021,480,59.99,10);
        adaugaCE(bib,"ISBN-E095","Procedura Civila","Drept","Juridic",0,2022,576,68.99,10);
        adaugaCE(bib,"ISBN-E096","Procedura Penala","Drept","Juridic",0,2022,544,65.99,8);
        adaugaCE(bib,"ISBN-E097","Contabilitate generala","Economie","Economic",0,2022,448,55.99,18);
        adaugaCE(bib,"ISBN-E098","Macroeconomie","Economie","Economic",0,2020,412,52.99,15);
        adaugaCE(bib,"ISBN-E099","Microeconomie","Economie","Economic",0,2020,396,50.99,15);
        adaugaCE(bib,"ISBN-E100","Management general","Economie","Economic",0,2021,416,50.99,15);
        adaugaCE(bib,"ISBN-E101","Marketing","Economie","Economic",0,2022,384,47.99,12);
        adaugaCE(bib,"ISBN-E102","Admitere ASE","Matematica","Economic",0,2023,320,35.99,12);
        adaugaCE(bib,"ISBN-E103","Finante publice","Economie","Economic",0,2021,448,52.99,10);
        adaugaCE(bib,"ISBN-E104","Drept Commercial","Drept","Juridic",0,2022,448,56.99,8);
        // Medicina (8-15 ex)
        adaugaCE(bib,"ISBN-E105","Anatomie umana vol 1","Medicina","Medical",0,2021,672,85.99,12);
        adaugaCE(bib,"ISBN-E106","Anatomie umana vol 2","Medicina","Medical",0,2021,688,85.99,10);
        adaugaCE(bib,"ISBN-E107","Fiziologie","Medicina","Medical",0,2020,768,92.99,10);
        adaugaCE(bib,"ISBN-E108","Biochimie medicala","Medicina","Medical",0,2021,624,79.99,8);
        adaugaCE(bib,"ISBN-E109","Farmacologie","Medicina","Medical",0,2021,864,98.99,8);
        adaugaCE(bib,"ISBN-E110","Microbiologie","Medicina","Medical",0,2020,592,75.99,8);
        adaugaCE(bib,"ISBN-E111","Patologie generala","Medicina","Medical",0,2022,712,88.99,6);
        adaugaCE(bib,"ISBN-E112","Nutritie si Dietetica","Medicina","Medical",0,2022,416,50.99,8);
        // Stiinte sociale
        adaugaCE(bib,"ISBN-E113","Psihologie generala","Psihologie","Uman",0,2021,384,48.99,12);
        adaugaCE(bib,"ISBN-E114","Pedagogie","Pedagogie","Pedagogic",0,2021,416,50.99,10);
        adaugaCE(bib,"ISBN-E115","Filosofie","Filosofie","Uman",0,2020,448,52.99,10);
        adaugaCE(bib,"ISBN-E116","Sociologie generala","Sociologie","Uman",0,2022,384,47.99,10);
        adaugaCE(bib,"ISBN-E117","Comunicare si Relatii Publice","Comunicare","Uman",0,2022,368,46.99,8);
        adaugaCE(bib,"ISBN-E118","Relatii Internationale","Stiinte Politice","Uman",0,2022,448,52.99,8);
        adaugaCE(bib,"ISBN-E119","Psihologie sociala","Psihologie","Uman",0,2020,368,46.99,8);
        adaugaCE(bib,"ISBN-E120","Asistenta Sociala","Sociologie","Uman",0,2021,384,47.99,6);
        adaugaCE(bib,"ISBN-E121","Jurnalism","Comunicare","Uman",0,2021,320,42.99,6);
        adaugaCE(bib,"ISBN-E122","Stiinte Politice","Stiinte Politice","Uman",0,2021,416,50.99,6);
        // Tehnica inginereasca
        adaugaCE(bib,"ISBN-E123","Electrotehnica","Electrica","Real",0,2020,512,58.99,8);
        adaugaCE(bib,"ISBN-E124","Electronica digitala","Electronica","Real",0,2020,448,52.99,8);
        adaugaCE(bib,"ISBN-E125","Robotica","Automatizari","Real",0,2022,384,48.99,6);
        adaugaCE(bib,"ISBN-E126","Rezistenta Materialelor","Constructii","Tehnic",0,2022,512,62.99,6);
        adaugaCE(bib,"ISBN-E127","Mecanica Fluidelor","Mecanica","Real",0,2021,416,51.99,5);
        adaugaCE(bib,"ISBN-E128","Constructii Civile","Constructii","Tehnic",0,2021,512,62.99,5);
        adaugaCE(bib,"ISBN-E129","Calcul Numeric","Matematica","Real",0,2021,368,46.99,8);
        adaugaCE(bib,"ISBN-E130","Econometrie","Economie","Economic",0,2022,384,47.99,8);
        adaugaCE(bib,"ISBN-E131","Matematici Financiare","Matematica","Economic",0,2022,320,42.99,8);
        adaugaCE(bib,"ISBN-E132","Automatizari Industriale","Automatizari","Real",0,2021,448,54.99,5);
        adaugaCE(bib,"ISBN-E133","Calcul Paralel","Informatica","Real",0,2021,416,50.99,5);
        adaugaCE(bib,"ISBN-E134","Recunoastere Forme","Informatica","Real",0,2021,384,48.99,5);
        // BAC - 20-30 exemplare
        adaugaCE(bib,"ISBN-E135","100 teste BAC Romana","Romana","Uman",12,2023,288,28.99,30);
        adaugaCE(bib,"ISBN-E136","100 teste BAC Matematica","Matematica","Real",12,2023,256,28.99,30);
        adaugaCE(bib,"ISBN-E137","100 teste BAC Fizica","Fizica","Real",12,2023,240,26.99,20);
        adaugaCE(bib,"ISBN-E138","100 teste BAC Chimie","Chimie","Real",12,2023,224,25.99,18);
        adaugaCE(bib,"ISBN-E139","100 teste BAC Biologie","Biologie","Real",12,2023,208,24.99,18);
        adaugaCE(bib,"ISBN-E140","100 teste BAC Engleza","Engleza","Uman",12,2023,272,27.99,20);
        adaugaCE(bib,"ISBN-E141","Bacalaureat Informatica","Informatica","Real",12,2023,320,35.99,25);
    }

    // ===================================================================
    // CARTI COPII (cu exemplare variabile)
    // ===================================================================
    static void seedCartiCopii(Biblioteca& bib)
    {
        auto* corint  = bib.gasesteOrAdaugaEditura("Corint","Romania","Bucuresti");
        auto* art     = bib.gasesteOrAdaugaEditura("Art","Romania","Bucuresti");
        auto* rao     = bib.gasesteOrAdaugaEditura("RAO","Romania","Bucuresti");
        auto* litera  = bib.gasesteOrAdaugaEditura("Litera","Romania","Bucuresti");

        auto* rowling  = bib.gasesteOrAdaugaAutor("Rowling","J.K.","Britanica",1965,true);
        auto* dahl     = bib.gasesteOrAdaugaAutor("Dahl","Roald","Britanic",1916,false);
        auto* lewis    = bib.gasesteOrAdaugaAutor("Lewis","C.S.","Britanic",1898,false);
        auto* andersen = bib.gasesteOrAdaugaAutor("Andersen","Hans Christian","Danez",1805,false);
        auto* grimm    = bib.gasesteOrAdaugaAutor("Grimm","Jacob","German",1785,false);
        auto* ispirescu= bib.gasesteOrAdaugaAutor("Ispirescu","Petre","Roman",1830,false);
        auto* milne    = bib.gasesteOrAdaugaAutor("Milne","A.A.","Britanic",1882,false);
        auto* lindgren = bib.gasesteOrAdaugaAutor("Lindgren","Astrid","Suedeza",1907,false);
        auto* kipling  = bib.gasesteOrAdaugaAutor("Kipling","Rudyard","Britanic",1865,false);
        auto* carroll  = bib.gasesteOrAdaugaAutor("Carroll","Lewis","Britanic",1832,false);
        auto* col      = bib.gasesteOrAdaugaAutor("Colectiv","Autori","Roman",2000,true);

        // Harry Potter - foarte popular, 15-40 ex
        adaugaCC(bib,"ISBN-C001","Harry Potter si Piatra Filozofala",rowling,rao,2019,8,false,320,39.99,40);
        adaugaCC(bib,"ISBN-C002","Harry Potter si Camera Secretelor",rowling,rao,2019,8,false,352,39.99,35);
        adaugaCC(bib,"ISBN-C003","Harry Potter si Prizonierul din Azkaban",rowling,rao,2020,8,false,384,42.99,30);
        adaugaCC(bib,"ISBN-C004","Harry Potter si Pocalul de Foc",rowling,rao,2020,10,false,624,49.99,25);
        adaugaCC(bib,"ISBN-C005","Harry Potter si Ordinul Phoenix",rowling,rao,2020,10,false,816,55.99,20);
        adaugaCC(bib,"ISBN-C006","Harry Potter si Printul Semisange",rowling,rao,2021,10,false,607,49.99,18);
        adaugaCC(bib,"ISBN-C007","Harry Potter si Talismanele Mortii",rowling,rao,2021,10,false,607,49.99,15);
        // Roald Dahl
        adaugaCC(bib,"ISBN-C008","Charlie si Fabrica de Ciocolata",dahl,art,2019,6,false,176,25.99,25);
        adaugaCC(bib,"ISBN-C009","James si Piersica Uriasa",dahl,art,2020,6,false,144,22.99,18);
        adaugaCC(bib,"ISBN-C010","Matilda",dahl,art,2020,7,false,240,27.99,22);
        adaugaCC(bib,"ISBN-C011","The BFG",dahl,art,2021,6,false,208,25.99,15);
        adaugaCC(bib,"ISBN-C012","Vulpea Doamna",dahl,art,2021,5,false,96,15.99,12);
        // Narnia
        adaugaCC(bib,"ISBN-C013","Leul Vrajitoarea si Dulapul",lewis,rao,2019,7,false,160,22.99,20);
        adaugaCC(bib,"ISBN-C014","Printul Caspian",lewis,rao,2020,8,false,195,22.99,15);
        adaugaCC(bib,"ISBN-C015","Calatoria pe Apa Zorilor",lewis,rao,2020,8,false,176,22.99,12);
        adaugaCC(bib,"ISBN-C016","Calul si Baiatul",lewis,rao,2020,8,false,192,22.99,10);
        adaugaCC(bib,"ISBN-C017","Ultima Batalie",lewis,rao,2021,9,false,184,22.99,8);
        // Andersen
        adaugaCC(bib,"ISBN-C018","Mica Sirena",andersen,corint,2019,5,true,64,15.99,20);
        adaugaCC(bib,"ISBN-C019","Degetarica",andersen,corint,2019,4,true,48,12.99,18);
        adaugaCC(bib,"ISBN-C020","Craiasa Zapezii",andersen,corint,2020,6,false,96,18.99,15);
        adaugaCC(bib,"ISBN-C021","Rata cea Urata",andersen,corint,2020,4,true,48,12.99,20);
        adaugaCC(bib,"ISBN-C022","Lebedele Salbatice",andersen,corint,2020,6,false,64,14.99,12);
        // Grimm
        adaugaCC(bib,"ISBN-C023","Frumoasa din Padurea Adormita",grimm,litera,2019,5,true,64,14.99,18);
        adaugaCC(bib,"ISBN-C024","Alba ca Zapada",grimm,litera,2019,5,true,64,14.99,20);
        adaugaCC(bib,"ISBN-C025","Scufita Rosie",grimm,litera,2020,4,true,48,12.99,22);
        adaugaCC(bib,"ISBN-C026","Cenusareasa",grimm,litera,2020,5,true,64,14.99,18);
        adaugaCC(bib,"ISBN-C027","Hansel si Gretel",grimm,litera,2019,5,true,48,12.99,15);
        adaugaCC(bib,"ISBN-C028","Rapunzel",grimm,litera,2019,4,true,40,10.99,12);
        // Basme romanesti
        adaugaCC(bib,"ISBN-C029","Harap Alb",ispirescu,corint,2019,7,false,96,18.99,20);
        adaugaCC(bib,"ISBN-C030","Praslea cel Voinic",ispirescu,corint,2020,7,false,80,16.99,15);
        adaugaCC(bib,"ISBN-C031","Fat Frumos din Lacrima",ispirescu,corint,2020,6,false,72,15.99,15);
        adaugaCC(bib,"ISBN-C032","Ileana Cosanzeana",ispirescu,corint,2019,6,false,80,16.99,12);
        adaugaCC(bib,"ISBN-C033","Basme romanesti vol 1",ispirescu,corint,2020,6,false,192,22.99,15);
        adaugaCC(bib,"ISBN-C034","Basme romanesti vol 2",ispirescu,corint,2021,6,false,192,22.99,12);
        // Altele populare
        adaugaCC(bib,"ISBN-C035","Winnie the Pooh",milne,art,2019,4,true,176,18.99,20);
        adaugaCC(bib,"ISBN-C036","Pippi Sosetica",lindgren,litera,2020,6,false,160,19.99,18);
        adaugaCC(bib,"ISBN-C037","Fratii Inimii",lindgren,litera,2019,8,false,256,25.99,10);
        adaugaCC(bib,"ISBN-C038","Cartea junglei",kipling,litera,2019,7,false,256,24.99,15);
        adaugaCC(bib,"ISBN-C039","Alice in Tara Minunilor",carroll,corint,2019,7,false,192,21.99,20);
        adaugaCC(bib,"ISBN-C040","Peter Pan",bib.gasesteOrAdaugaAutor("Barrie","J.M.","Scotian",1860,false),litera,2020,6,false,224,22.99,18);
        adaugaCC(bib,"ISBN-C041","Pinocchio",bib.gasesteOrAdaugaAutor("Collodi","Carlo","Italian",1826,false),corint,2019,6,false,192,18.99,15);
        adaugaCC(bib,"ISBN-C042","Heidi",bib.gasesteOrAdaugaAutor("Spyri","Johanna","Elvetiana",1827,false),litera,2020,8,false,256,24.99,12);
        adaugaCC(bib,"ISBN-C043","Robinson Crusoe",bib.gasesteOrAdaugaAutor("Defoe","Daniel","Britanic",1660,false),corint,2021,10,false,312,28.99,10);
        adaugaCC(bib,"ISBN-C044","Aventurile lui Tom Sawyer",bib.gasesteOrAdaugaAutor("Twain","Mark","American",1835,false),corint,2020,9,false,200,22.99,15);
        adaugaCC(bib,"ISBN-C045","Insula comorii",bib.gasesteOrAdaugaAutor("Stevenson","Robert Louis","Scotian",1850,false),corint,2019,10,false,224,22.99,12);
        adaugaCC(bib,"ISBN-C046","Don Quijote pentru copii",bib.gasesteOrAdaugaAutor("Cervantes","Miguel de","Spaniol",1547,false),corint,2020,10,false,224,23.99,8);
        adaugaCC(bib,"ISBN-C047","Gulliver in Tara Piticilor",bib.gasesteOrAdaugaAutor("Swift","Jonathan","Irlandez",1667,false),corint,2019,9,false,256,25.99,10);
        adaugaCC(bib,"ISBN-C048","Emil si Detectivii",bib.gasesteOrAdaugaAutor("Kastner","Erich","German",1899,false),litera,2020,7,false,176,20.99,12);
        adaugaCC(bib,"ISBN-C049","Omul Invizibil",bib.gasesteOrAdaugaAutor("Wells","H.G.","Britanic",1866,false),litera,2021,10,false,224,22.99,8);
        adaugaCC(bib,"ISBN-C050","Razboiul Lumilor",bib.gasesteOrAdaugaAutor("Wells","H.G.","Britanic",1866,false),litera,2020,10,false,192,20.99,8);
        // Enciclopedii si educative copii
        adaugaCC(bib,"ISBN-C051","Enciclopedia copiilor",col,corint,2021,6,true,256,45.99,10);
        adaugaCC(bib,"ISBN-C052","Atlasul lumii pentru copii",col,corint,2021,6,true,128,35.99,8);
        adaugaCC(bib,"ISBN-C053","Corpul uman pentru copii",col,corint,2022,7,true,128,32.99,8);
        adaugaCC(bib,"ISBN-C054","Sistemul solar pentru copii",col,corint,2021,7,true,96,24.99,10);
        adaugaCC(bib,"ISBN-C055","Dinozaurii uriasi",col,corint,2022,5,true,80,22.99,12);
        adaugaCC(bib,"ISBN-C056","Animale din Romania",col,corint,2021,6,true,112,29.99,8);
        adaugaCC(bib,"ISBN-C057","Mitologie Greaca pentru copii",col,corint,2021,8,false,256,28.99,8);
        adaugaCC(bib,"ISBN-C058","Mitologie Romana pentru copii",col,corint,2022,8,false,224,26.99,8);
        adaugaCC(bib,"ISBN-C059","Experimente stiintifice acasa",col,art,2022,8,true,144,29.99,6);
        adaugaCC(bib,"ISBN-C060","Romania pentru copii",col,corint,2021,7,true,128,28.99,8);
        // Educative
        adaugaCC(bib,"ISBN-C061","Abecedar",col,corint,2022,1,true,128,18.99,25);
        adaugaCC(bib,"ISBN-C062","Matematica distractiva cls 1",col,corint,2022,1,true,96,18.99,20);
        adaugaCC(bib,"ISBN-C063","Matematica distractiva cls 2",col,corint,2022,2,true,104,18.99,18);
        adaugaCC(bib,"ISBN-C064","Matematica distractiva cls 3",col,corint,2022,3,true,112,19.99,15);
        adaugaCC(bib,"ISBN-C065","Citim si scriem cls 1",col,corint,2022,1,true,96,16.99,20);
        adaugaCC(bib,"ISBN-C066","Citim si scriem cls 2",col,corint,2022,2,true,104,16.99,18);
        adaugaCC(bib,"ISBN-C067","Carte de colorat cu animale",col,art,2021,3,true,64,10.99,15);
        adaugaCC(bib,"ISBN-C068","Carte de colorat cu printese",col,art,2021,4,true,64,10.99,12);
        adaugaCC(bib,"ISBN-C069","Povesti de noapte buna",col,corint,2020,3,false,256,28.99,15);
        adaugaCC(bib,"ISBN-C070","Jurnalul unui pusti vol 1",bib.gasesteOrAdaugaAutor("Kinney","Jeff","American",1971,true),art,2021,8,false,224,29.99,25);
        adaugaCC(bib,"ISBN-C071","Jurnalul unui pusti vol 2",bib.gasesteOrAdaugaAutor("Kinney","Jeff","American",1971,true),art,2021,8,false,224,29.99,20);
        adaugaCC(bib,"ISBN-C072","Geronimo Stilton vol 1",bib.gasesteOrAdaugaAutor("Stilton","Geronimo","Italian",1969,true),litera,2020,6,true,128,18.99,15);
        adaugaCC(bib,"ISBN-C073","Micul Print pentru copii",bib.gasesteOrAdaugaAutor("Saint-Exupery","Antoine de","Francez",1900,false),bib.gasesteOrAdaugaEditura("Humanitas","Romania","Bucuresti"),2020,6,false,96,14.99,20);
        adaugaCC(bib,"ISBN-C074","Fetitele",bib.gasesteOrAdaugaAutor("Alcott","Louisa May","Americana",1832,false),litera,2021,9,false,544,38.99,8);
        adaugaCC(bib,"ISBN-C075","Singur pe lume",bib.gasesteOrAdaugaAutor("Malot","Hector","Francez",1830,false),litera,2020,9,false,416,34.99,8);
    }

    // ===================================================================
    // MATERIALE REFERINTA
    // ===================================================================
    static void seedMaterialeReferinta(Biblioteca& bib)
    {
        // Dictionare - 1-3 exemplare (doar sala)
        adaugaRef(bib,"ISBN-R001","Dictionarul Explicativ al Limbii Romane","Dictionar",2009,1192,120.99,2);
        adaugaRef(bib,"ISBN-R002","Dictionarul Ortografic DOOM3","Dictionar",2021,688,89.99,2);
        adaugaRef(bib,"ISBN-R003","Dictionarul de Sinonime","Dictionar",2019,512,55.99,1);
        adaugaRef(bib,"ISBN-R004","Dictionarul de Antonime","Dictionar",2019,384,49.99,1);
        adaugaRef(bib,"ISBN-R005","Dictionarul Englez-Roman","Dictionar",2020,1024,95.99,3);
        adaugaRef(bib,"ISBN-R006","Dictionarul Roman-Englez","Dictionar",2020,1024,95.99,3);
        adaugaRef(bib,"ISBN-R007","Dictionarul Francez-Roman","Dictionar",2019,896,89.99,2);
        adaugaRef(bib,"ISBN-R008","Dictionarul German-Roman","Dictionar",2019,912,89.99,2);
        adaugaRef(bib,"ISBN-R009","Dictionarul de Informatica","Dictionar",2020,512,65.99,2);
        adaugaRef(bib,"ISBN-R010","Dictionarul de Matematica","Dictionar",2018,448,55.99,1);
        adaugaRef(bib,"ISBN-R011","Dictionarul de Filosofie","Dictionar",2018,640,72.99,1);
        adaugaRef(bib,"ISBN-R012","Dictionarul de Psihologie","Dictionar",2019,512,62.99,1);
        adaugaRef(bib,"ISBN-R013","Dictionarul de Economie","Dictionar",2021,640,72.99,2);
        adaugaRef(bib,"ISBN-R014","Dictionarul Juridic","Dictionar",2022,768,85.99,2);
        adaugaRef(bib,"ISBN-R015","Dictionarul Medical","Dictionar",2021,896,95.99,2);
        adaugaRef(bib,"ISBN-R016","Dictionarul de Chimie","Dictionar",2019,512,62.99,1);
        adaugaRef(bib,"ISBN-R017","Dictionarul de Fizica","Dictionar",2020,480,59.99,1);
        adaugaRef(bib,"ISBN-R018","Dictionarul de Biologie","Dictionar",2019,544,65.99,1);
        adaugaRef(bib,"ISBN-R019","Dictionarul de Geografie","Dictionar",2020,512,62.99,1);
        adaugaRef(bib,"ISBN-R020","Dictionarul de Sociologie","Dictionar",2020,576,68.99,1);
        // Atlase
        adaugaRef(bib,"ISBN-R021","Atlas Geografic General","Atlas",2021,256,95.99,2);
        adaugaRef(bib,"ISBN-R022","Atlas Geografic Romania","Atlas",2020,128,65.99,3);
        adaugaRef(bib,"ISBN-R023","Atlas Geografic Europa","Atlas",2021,160,72.99,2);
        adaugaRef(bib,"ISBN-R024","Atlas Geografic Lumea","Atlas",2022,320,110.99,2);
        adaugaRef(bib,"ISBN-R025","Atlas Anatomic Uman","Atlas",2020,224,85.99,3);
        adaugaRef(bib,"ISBN-R026","Atlas Botanic","Atlas",2019,192,75.99,2);
        adaugaRef(bib,"ISBN-R027","Atlas Zoologic","Atlas",2020,208,78.99,2);
        adaugaRef(bib,"ISBN-R028","Atlas Astronomic","Atlas",2021,176,72.99,2);
        adaugaRef(bib,"ISBN-R029","Atlas Istoric Romania","Atlas",2019,192,75.99,2);
        adaugaRef(bib,"ISBN-R030","Atlas Istoric Universal","Atlas",2020,256,89.99,1);
        adaugaRef(bib,"ISBN-R031","Atlas Militar WW2","Atlas",2019,320,99.99,1);
        adaugaRef(bib,"ISBN-R032","Atlas Flora Romaniei","Atlas",2020,288,92.99,2);
        adaugaRef(bib,"ISBN-R033","Atlas Fauna Romaniei","Atlas",2021,304,95.99,2);
        adaugaRef(bib,"ISBN-R034","Atlas Geologic Romania","Atlas",2019,256,85.99,1);
        // Enciclopedii
        adaugaRef(bib,"ISBN-R035","Enciclopedia Universala Britanica vol 1","Enciclopedie",2010,512,145.99,1);
        adaugaRef(bib,"ISBN-R036","Enciclopedia Universala Britanica vol 2","Enciclopedie",2010,512,145.99,1);
        adaugaRef(bib,"ISBN-R037","Enciclopedia Romaniei","Enciclopedie",2015,1024,180.99,2);
        adaugaRef(bib,"ISBN-R038","Enciclopedia Stiintei","Enciclopedie",2019,512,120.99,2);
        adaugaRef(bib,"ISBN-R039","Enciclopedia Istoriei Lumii","Enciclopedie",2020,640,135.99,1);
        adaugaRef(bib,"ISBN-R040","Enciclopedia Medicinei","Enciclopedie",2020,1280,165.99,1);
        adaugaRef(bib,"ISBN-R041","Enciclopedia Dreptului","Enciclopedie",2021,1024,145.99,1);
        adaugaRef(bib,"ISBN-R042","Enciclopedia Economiei","Enciclopedie",2019,896,125.99,1);
        adaugaRef(bib,"ISBN-R043","Enciclopedia Tehnicii","Enciclopedie",2020,1152,155.99,1);
        adaugaRef(bib,"ISBN-R044","Enciclopedia Culturii Romane","Enciclopedie",2021,1536,195.99,2);
        adaugaRef(bib,"ISBN-R045","Enciclopedia Geografiei Romaniei","Enciclopedie",2019,768,115.99,1);
        adaugaRef(bib,"ISBN-R046","Enciclopedia Florei si Faunei","Enciclopedie",2020,896,125.99,1);
        adaugaRef(bib,"ISBN-R047","Enciclopedia Mitologiei Universale","Enciclopedie",2022,1024,145.99,2);
        adaugaRef(bib,"ISBN-R048","Enciclopedia Informaticii","Enciclopedie",2021,768,115.99,2);
        adaugaRef(bib,"ISBN-R049","Istoria Romanilor vol 1","Enciclopedie",2001,480,75.99,2);
        adaugaRef(bib,"ISBN-R050","Istoria literaturii romane","Enciclopedie",2020,1064,85.99,2);
    }

    // ===================================================================
    // CARTI RELIGIOASE
    // ===================================================================
    static void seedCartiReligioase(Biblioteca& bib)
    {
        auto* humanitas = bib.gasesteOrAdaugaEditura("Humanitas","Romania","Bucuresti");
        auto* col       = bib.gasesteOrAdaugaAutor("Colectiv","Autori","Roman",2000,true);
        struct R { string isbn,titlu,religie,cult; int an,pag,ex; double pret; };
        std::vector<R> v = {
            {"ISBN-REL001","Biblia editie integrala","Crestina","Ortodoxa",2018,1504,5,85.99},
            {"ISBN-REL002","Noul Testament","Crestina","Ortodoxa",2020,512,8,35.99},
            {"ISBN-REL003","Vechiul Testament","Crestina","Ortodoxa",2019,992,4,65.99},
            {"ISBN-REL004","Psaltirea","Crestina","Ortodoxa",2019,256,6,25.99},
            {"ISBN-REL005","Liturghierul","Crestina","Ortodoxa",2020,320,4,35.99},
            {"ISBN-REL006","Ceaslovul","Crestina","Ortodoxa",2020,448,4,42.99},
            {"ISBN-REL007","Viata Sfintilor vol 1","Crestina","Ortodoxa",2021,512,3,55.99},
            {"ISBN-REL008","Viata Sfintilor vol 2","Crestina","Ortodoxa",2021,528,3,55.99},
            {"ISBN-REL009","Viata Sfintilor vol 3","Crestina","Ortodoxa",2021,496,3,55.99},
            {"ISBN-REL010","Filocalia vol 1","Crestina","Ortodoxa",2018,480,2,65.99},
            {"ISBN-REL011","Filocalia vol 2","Crestina","Ortodoxa",2018,512,2,65.99},
            {"ISBN-REL012","Cararea Imparatiei","Crestina","Ortodoxa",2019,320,5,39.99},
            {"ISBN-REL013","Biblia Catolica","Crestina","Catolica",2019,1600,3,89.99},
            {"ISBN-REL014","Catehismul Bisericii Catolice","Crestina","Catolica",2020,896,2,72.99},
            {"ISBN-REL015","Coranul traducere comentata","Islamica","Islam",2018,608,2,55.99},
        };
        for (auto& d : v) {
            auto* c = new CarteReligioasa(d.isbn,d.titlu,{col},humanitas,d.an,
                LimbaCartii::ROMANA,TipCoperta::CARTONATA,d.religie,d.cult,d.pag,d.pret);
            try { bib.adaugaCarte(c); } catch(...){ delete c; continue; }
            adaugaExemplare(bib, d.isbn, "Cladirea D","Sala Religioasa","R-REL","Religios", d.ex, d.pret*0.6);
        }
    }

    // ===================================================================
    // PERIODICE
    // ===================================================================
    static void seedPeriodicale(Biblioteca& bib)
    {
        auto* adev = bib.gasesteOrAdaugaEditura("Adevarul Holding","Romania","Bucuresti");
        auto* col  = bib.gasesteOrAdaugaAutor("Colectiv","Autori","Roman",2000,true);
        struct P { string issn,titlu,tip,dom; int nr,luna,an,pag,ex; double pret; };
        std::vector<P> v = {
            {"ISSN-Z001","Adevarul","Ziar","Stiri",12458,4,2024,24,3,5.99},
            {"ISSN-Z002","Romania Libera","Ziar","Stiri",8745,4,2024,24,2,5.99},
            {"ISSN-Z003","Gazeta Sporturilor","Ziar","Sport",15678,4,2024,32,5,5.99},
            {"ISSN-Z004","Libertatea","Ziar","Stiri",9876,4,2024,24,3,5.99},
            {"ISSN-Z005","Jurnalul National","Ziar","Stiri",7654,4,2024,24,2,5.99},
            {"ISSN-R001","National Geographic Romania","Revista","Geografie",256,4,2024,128,4,22.99},
            {"ISSN-R002","Stiinta si Tehnica","Revista","Stiinta",412,4,2024,96,3,18.99},
            {"ISSN-R003","Historia","Revista","Istorie",189,4,2024,112,3,19.99},
            {"ISSN-R004","Computer World","Revista","IT",678,4,2024,80,3,15.99},
            {"ISSN-R005","Chips","Revista","IT",534,4,2024,88,2,14.99},
            {"ISSN-R006","Psychologies Romania","Revista","Psihologie",145,4,2024,96,3,18.99},
            {"ISSN-R007","Forbes Romania","Revista","Business",112,4,2024,104,2,22.99},
            {"ISSN-R008","Business Magazine","Revista","Business",256,4,2024,88,2,18.99},
            {"ISSN-R009","Auto Motor Sport","Revista","Auto",345,4,2024,96,2,16.99},
            {"ISSN-R010","Viva","Revista","Lifestyle",456,4,2024,112,2,14.99},
        };
        for (auto& d : v) {
            auto* c = new Periodic(d.issn,d.titlu,{col},adev,d.an,
                LimbaCartii::ROMANA,d.tip,d.nr,d.luna,d.an,d.dom,d.pag);
            try { bib.adaugaCarte(c); } catch(...){ delete c; continue; }
            adaugaExemplare(bib, d.issn, "Cladirea A","Sala Lectura","R-PER","Periodice", d.ex, d.pret);
        }
    }

    // ===================================================================
    // MANUSCRISE RARE (1 exemplar fiecare)
    // ===================================================================
    static void seedManuscrise(Biblioteca& bib)
    {
        auto* minerva = bib.gasesteOrAdaugaEditura("Minerva","Romania","Bucuresti");
        auto* costin  = bib.gasesteOrAdaugaAutor("Costin","Miron","Roman",1633,false);
        auto* ureche  = bib.gasesteOrAdaugaAutor("Ureche","Grigore","Roman",1590,false);
        auto* cantemir= bib.gasesteOrAdaugaAutor("Cantemir","Dimitrie","Roman",1673,false);
        struct M { string isbn,titlu,epoca; Autor* autor; int an; double pret; };
        std::vector<M> v = {
            {"ISBN-M001","Letopisetul Tarii Moldovei Miron Costin","Medievala",costin,1675,15000.0},
            {"ISBN-M002","Letopisetul Tarii Moldovei Grigore Ureche","Medievala",ureche,1640,18000.0},
            {"ISBN-M003","Cronica lui Stefan cel Mare","Medievala",bib.gasesteOrAdaugaAutor("Necunoscut","Cronicar","Roman",1500,false),1506,25000.0},
            {"ISBN-M004","Psaltirea Scheiana","Medievala",bib.gasesteOrAdaugaAutor("Necunoscut","Traducator","Roman",1450,false),1482,35000.0},
            {"ISBN-M005","Codicele Voronetean","Medievala",bib.gasesteOrAdaugaAutor("Necunoscut","Calugar","Roman",1450,false),1563,40000.0},
            {"ISBN-M006","Carte Romaneasca de Invatatura","Renascentista",bib.gasesteOrAdaugaAutor("Varlaam","Mitropolit","Roman",1590,false),1643,22000.0},
            {"ISBN-M007","Pravila lui Vasile Lupu","Medievala",bib.gasesteOrAdaugaAutor("Eustratie","Logofat","Roman",1600,false),1646,28000.0},
            {"ISBN-M008","Biblia de la Bucuresti 1688","Renascentista",bib.gasesteOrAdaugaAutor("Dosoftei","Mitropolit","Roman",1624,false),1688,50000.0},
            {"ISBN-M009","Divanul lui Cantemir","Iluminista",cantemir,1698,30000.0},
            {"ISBN-M010","Istoria Ieroglifica","Iluminista",cantemir,1705,32000.0},
        };
        for (auto& d : v) {
            auto* c = new ManuscrisRar(d.isbn,d.titlu,{d.autor},minerva,d.an,
                LimbaCartii::ROMANA,TipCoperta::PIELE,d.epoca,
                "Temperatura 18C, umiditate 45%",true,d.pret);
            try { bib.adaugaCarte(c); } catch(...){ delete c; continue; }
            adaugaExemplare(bib, d.isbn, "Cladirea E","Sala Arhiva","R-ARH","Manuscrise", 1, d.pret);
        }
    }

    // ===================================================================
    // UTILIZATORI (~200)
    // ===================================================================
    static void seedUtilizatori(Biblioteca& bib)
    {
        // Staff
        bib.adaugaUtilizator(new UtilizatorStaff("STAFF-001","Marin","Andreea","a.marin@bib.ro","staff001","Fictiune",RolStaff::BIBLIOTECAR_SEF,4200.0,2019,3));
        bib.adaugaUtilizator(new UtilizatorStaff("STAFF-002","Ionescu","Cristian","c.ionescu@bib.ro","staff002","Tehnica",RolStaff::BIBLIOTECAR,3500.0,2020,9));
        bib.adaugaUtilizator(new UtilizatorStaff("STAFF-003","Popescu","Elena","e.popescu@bib.ro","staff003","Educativa",RolStaff::BIBLIOTECAR,3500.0,2021,2));
        bib.adaugaUtilizator(new UtilizatorStaff("STAFF-004","Dumitrescu","Mihai","m.dumitrescu@bib.ro","staff004","Administrativ",RolStaff::ADMINISTRATOR,5500.0,2015,6));
        bib.adaugaUtilizator(new UtilizatorStaff("STAFF-005","Stanciu","Ana","a.stanciu@bib.ro","staff005","Casierie",RolStaff::CASIER,3200.0,2022,1));

        string fac[] = {"FIESC","FSEAP","FIG","FSE","FDSA"};
        string pren[] = {"Ana","Ion","Maria","Gheorghe","Elena","Mihai","Ioana","Alexandru","Andreea","Cristian",
                          "Daniela","Florin","Gabriela","Horia","Ileana","Iulian","Jana","Liviu","Monica","Nicolae",
                          "Octavia","Pavel","Raluca","Stefan","Teodora","Valentina","Vlad","Xenia","Zoran","Catalin"};
        string nm[] = {"Pop","Ionescu","Popa","Georgescu","Stan","Mihai","Constantin","Dumitrescu","Radu","Stoica",
                        "Marin","Florescu","Dima","Lazar","Moldovan","Nistor","Oprea","Petrescu","Rusu","Serban",
                        "Tudor","Ungureanu","Vasilescu","Zamfir","Antal","Barbu","Coman","Dobre","Enache","Florea"};
        int c = 1;
        for (int i = 0; i < 60; i++) {
            string id = "STU-" + std::to_string(1000 + c++);
            bib.adaugaUtilizator(new UtilizatorStudent(
                id, nm[i%30], pren[i%30],
                pren[i%30] + "." + nm[i%30] + "@usv.ro",
                "pass" + id,
                2024, (i%10)+1,
                fac[i%5], (i%4)+1,
                "MAT" + std::to_string(2024000+c)));
        }
        for (int i = 0; i < 135; i++) {
            string id = "BAS-" + std::to_string(2000 + c++);
            bib.adaugaUtilizator(new UtilizatorBasic(
                id, nm[(i+10)%30], pren[(i+5)%30],
                pren[(i+5)%30] + "@gmail.com",
                "pass" + id,
                2024, (i%12)+1));
        }
    }
};

#endif // DATA_SEEDER_H