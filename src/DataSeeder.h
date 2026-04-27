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
#include "UtilizatorPremium.h"
#include "UtilizatorStaff.h"

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
    }

    static void adaugaCF(Biblioteca& bib, const string& isbn, const string& titlu,
                          Autor* autor, Editura* ed, int an, const string& gen,
                          int varsta, int pagini, double pret,
                          const string& serie = "", int vol = 0)
    {
        auto* c = new CarteFictiune(isbn,titlu,{autor},ed,an,
            LimbaCartii::ROMANA,TipCoperta::BROSATA,gen,varsta,pagini,0.0,serie,vol,pret);
        try { bib.adaugaCarte(c); } catch(...){ delete c; return; }
        try {
            bib.adaugaExemplarLaCarte(isbn,"Cladirea A","Sala Fictiune","R-F1","Fictiune",ProvenientaCarte::CUMPARATA,pret*0.7);
            bib.adaugaExemplarLaCarte(isbn,"Cladirea A","Sala Fictiune","R-F2","Fictiune",ProvenientaCarte::CUMPARATA,pret*0.7);
        } catch(...) {}
    }

    static void adaugaCT(Biblioteca& bib, const string& isbn, const string& titlu,
                          Autor* autor, Editura* ed, int an, const string& dom,
                          const string& niv, int pagini, double pret)
    {
        auto* c = new CarteTehnica(isbn,titlu,{autor},ed,an,
            LimbaCartii::ENGLEZA,TipCoperta::CARTONATA,dom,niv,false,pagini,0.0,pret);
        try { bib.adaugaCarte(c); } catch(...){ delete c; return; }
        try {
            bib.adaugaExemplarLaCarte(isbn,"Cladirea B","Sala Tehnica","R-T1","Informatica",ProvenientaCarte::CUMPARATA,pret*0.65);
            bib.adaugaExemplarLaCarte(isbn,"Cladirea B","Sala Tehnica","R-T2","Informatica",ProvenientaCarte::CUMPARATA,pret*0.65);
        } catch(...) {}
    }

    static void adaugaCE(Biblioteca& bib, const string& isbn, const string& titlu,
                          const string& materie, const string& profil, int clasa,
                          int an, int pagini, double pret)
    {
        auto* autor = bib.gasesteOrAdaugaAutor("Colectiv","Autori","Roman",2000,true);
        auto* ed    = bib.gasesteOrAdaugaEditura("Didactica si Pedagogica","Romania","Bucuresti");
        auto* c = new CarteEducativa(isbn,titlu,{autor},ed,an,
            LimbaCartii::ROMANA,TipCoperta::BROSATA,materie,profil,clasa,pagini,0.0,pret);
        try { bib.adaugaCarte(c); } catch(...){ delete c; return; }
        try {
            bib.adaugaExemplarLaCarte(isbn,"Cladirea C","Sala Educativa","R-E1","Educational",ProvenientaCarte::CUMPARATA,pret*0.6);
            bib.adaugaExemplarLaCarte(isbn,"Cladirea C","Sala Educativa","R-E2","Educational",ProvenientaCarte::CUMPARATA,pret*0.6);
        } catch(...) {}
    }

    static void adaugaCC(Biblioteca& bib, const string& isbn, const string& titlu,
                          Autor* autor, Editura* ed, int an, int varsta,
                          bool interactiv, int pagini, double pret)
    {
        auto* c = new CarteCopii(isbn,titlu,{autor},ed,an,
            LimbaCartii::ROMANA,TipCoperta::CARTONATA,varsta,"Divers",interactiv,pagini,0.0,pret);
        try { bib.adaugaCarte(c); } catch(...){ delete c; return; }
        try {
            bib.adaugaExemplarLaCarte(isbn,"Cladirea A","Sala Copii","R-K1","Copii",ProvenientaCarte::CUMPARATA,pret*0.6);
            bib.adaugaExemplarLaCarte(isbn,"Cladirea A","Sala Copii","R-K2","Copii",ProvenientaCarte::CUMPARATA,pret*0.6);
        } catch(...) {}
    }

    static void adaugaRef(Biblioteca& bib, const string& isbn, const string& titlu,
                           const string& tip, int an, int pagini, double pret)
    {
        auto* col = bib.gasesteOrAdaugaAutor("Colectiv","Autori","Roman",2000,true);
        auto* ed  = bib.gasesteOrAdaugaEditura("Corint","Romania","Bucuresti");
        auto* c = new MaterialeReferinta(isbn,titlu,{col},ed,an,
            LimbaCartii::ROMANA,TipCoperta::CARTONATA,tip,pagini,0.0,pret);
        try { bib.adaugaCarte(c); } catch(...){ delete c; return; }
        try { bib.adaugaExemplarLaCarte(isbn,"Cladirea A","Sala Referinta","R-REF","Referinta",ProvenientaCarte::CUMPARATA,pret*0.7); } catch(...) {}
    }

    // ===================================================================
    // CARTI FICTIUNE (~200 titluri)
    // ===================================================================
    static void seedCartiFictiune(Biblioteca& bib)
    {
        auto* nemira    = bib.gasesteOrAdaugaEditura("Nemira","Romania","Bucuresti");
        auto* rao       = bib.gasesteOrAdaugaEditura("RAO","Romania","Bucuresti");
        auto* humanitas = bib.gasesteOrAdaugaEditura("Humanitas","Romania","Bucuresti");
        auto* litera    = bib.gasesteOrAdaugaEditura("Litera","Romania","Bucuresti");
        auto* corint    = bib.gasesteOrAdaugaEditura("Corint","Romania","Bucuresti");
        auto* minerva   = bib.gasesteOrAdaugaEditura("Minerva","Romania","Bucuresti");

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
        auto* weeks     = bib.gasesteOrAdaugaAutor("Weeks","Brent","American",1977,true);
        auto* hugo      = bib.gasesteOrAdaugaAutor("Hugo","Victor","Francez",1802,false);
        auto* dumas     = bib.gasesteOrAdaugaAutor("Dumas","Alexandre","Francez",1802,false);
        auto* verne     = bib.gasesteOrAdaugaAutor("Verne","Jules","Francez",1828,false);
        auto* balzac    = bib.gasesteOrAdaugaAutor("Balzac","Honore de","Francez",1799,false);
        auto* camus     = bib.gasesteOrAdaugaAutor("Camus","Albert","Francez",1913,false);
        auto* kafka     = bib.gasesteOrAdaugaAutor("Kafka","Franz","Ceh",1883,false);
        auto* hesse     = bib.gasesteOrAdaugaAutor("Hesse","Hermann","German",1877,false);
        auto* remarque  = bib.gasesteOrAdaugaAutor("Remarque","Erich Maria","German",1898,false);
        auto* zweig     = bib.gasesteOrAdaugaAutor("Zweig","Stefan","Austrian",1881,false);
        auto* dostoev   = bib.gasesteOrAdaugaAutor("Dostoevsky","Fyodor","Rus",1821,false);
        auto* tolstoy   = bib.gasesteOrAdaugaAutor("Tolstoy","Leo","Rus",1828,false);
        auto* hemingway = bib.gasesteOrAdaugaAutor("Hemingway","Ernest","American",1899,false);
        auto* nabokov   = bib.gasesteOrAdaugaAutor("Nabokov","Vladimir","Rus-American",1899,false);
        auto* borges    = bib.gasesteOrAdaugaAutor("Borges","Jorge Luis","Argentinian",1899,false);
        auto* eco       = bib.gasesteOrAdaugaAutor("Eco","Umberto","Italian",1932,false);
        auto* murakami  = bib.gasesteOrAdaugaAutor("Murakami","Haruki","Japonez",1949,true);
        auto* marquez   = bib.gasesteOrAdaugaAutor("Garcia Marquez","Gabriel","Columbian",1927,false);
        auto* coelho    = bib.gasesteOrAdaugaAutor("Coelho","Paulo","Brazilian",1947,true);
        auto* dickens   = bib.gasesteOrAdaugaAutor("Dickens","Charles","Britanic",1812,false);
        auto* austen    = bib.gasesteOrAdaugaAutor("Austen","Jane","Britanica",1775,false);
        auto* wilde     = bib.gasesteOrAdaugaAutor("Wilde","Oscar","Irlandez",1854,false);
        auto* dante     = bib.gasesteOrAdaugaAutor("Dante","Alighieri","Italian",1265,false);
        auto* homer     = bib.gasesteOrAdaugaAutor("Homer","Antic","Grec",-800,false);
        auto* grisham   = bib.gasesteOrAdaugaAutor("Grisham","John","American",1955,true);
        auto* clancy    = bib.gasesteOrAdaugaAutor("Clancy","Tom","American",1947,false);
        auto* ludlum    = bib.gasesteOrAdaugaAutor("Ludlum","Robert","American",1927,false);
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
        auto* arghezi   = bib.gasesteOrAdaugaAutor("Arghezi","Tudor","Roman",1880,false);
        auto* ionesco   = bib.gasesteOrAdaugaAutor("Ionesco","Eugene","Roman-Francez",1909,false);
        auto* eliade    = bib.gasesteOrAdaugaAutor("Eliade","Mircea","Roman",1907,false);
        auto* petrescu  = bib.gasesteOrAdaugaAutor("Petrescu","Camil","Roman",1894,false);
        auto* steinhardt= bib.gasesteOrAdaugaAutor("Steinhardt","Nicolae","Roman",1912,false);

        // SF si Fantasy
        adaugaCF(bib,"ISBN-F001","Dune",herbert,nemira,2020,"SF",14,412,49.99,"Dune",1);
        adaugaCF(bib,"ISBN-F002","Dune Messia",herbert,nemira,2021,"SF",14,380,45.99,"Dune",2);
        adaugaCF(bib,"ISBN-F003","Children of Dune",herbert,nemira,2021,"SF",14,410,45.99,"Dune",3);
        adaugaCF(bib,"ISBN-F004","Dune God Emperor",herbert,nemira,2022,"SF",14,454,45.99,"Dune",4);
        adaugaCF(bib,"ISBN-F005","Stapanul Inelelor: Fratia Inelului",tolkien,rao,2019,"Fantasy",12,423,55.99,"LOTR",1);
        adaugaCF(bib,"ISBN-F006","Stapanul Inelelor: Cele Doua Turnuri",tolkien,rao,2019,"Fantasy",12,352,55.99,"LOTR",2);
        adaugaCF(bib,"ISBN-F007","Stapanul Inelelor: Intoarcerea Regelui",tolkien,rao,2019,"Fantasy",12,416,55.99,"LOTR",3);
        adaugaCF(bib,"ISBN-F008","Hobbitul",tolkien,rao,2018,"Fantasy",10,310,39.99,"",0);
        adaugaCF(bib,"ISBN-F009","Silmarillion",tolkien,rao,2020,"Fantasy",14,365,45.99,"",0);
        adaugaCF(bib,"ISBN-F010","1984",orwell,humanitas,2021,"Distopie",16,328,35.99,"",0);
        adaugaCF(bib,"ISBN-F011","Ferma Animalelor",orwell,humanitas,2020,"Satira",14,128,25.99,"",0);
        adaugaCF(bib,"ISBN-F012","Minunata Lume Noua",huxley,humanitas,2019,"SF",16,311,34.99,"",0);
        adaugaCF(bib,"ISBN-F013","Foundation",asimov,nemira,2020,"SF",14,244,39.99,"Foundation",1);
        adaugaCF(bib,"ISBN-F014","Foundation and Empire",asimov,nemira,2020,"SF",14,247,39.99,"Foundation",2);
        adaugaCF(bib,"ISBN-F015","Second Foundation",asimov,nemira,2021,"SF",14,210,39.99,"Foundation",3);
        adaugaCF(bib,"ISBN-F016","I Robot",asimov,nemira,2019,"SF",14,253,35.99,"",0);
        adaugaCF(bib,"ISBN-F017","2001 A Space Odyssey",clarke,rao,2020,"SF",14,221,35.99,"",0);
        adaugaCF(bib,"ISBN-F018","Rendezvous with Rama",clarke,rao,2021,"SF",14,243,35.99,"",0);
        adaugaCF(bib,"ISBN-F019","Do Androids Dream of Electric Sheep",dick,nemira,2019,"SF",16,210,32.99,"",0);
        adaugaCF(bib,"ISBN-F020","The Man in the High Castle",dick,nemira,2020,"SF",16,259,35.99,"",0);
        adaugaCF(bib,"ISBN-F021","The Left Hand of Darkness",lequin,humanitas,2020,"SF",16,286,34.99,"",0);
        adaugaCF(bib,"ISBN-F022","Fahrenheit 451",bradbury,nemira,2018,"Distopie",14,158,29.99,"",0);
        adaugaCF(bib,"ISBN-F023","Neuromancer",gibson,nemira,2021,"Cyberpunk",16,271,34.99,"",0);
        adaugaCF(bib,"ISBN-F024","American Gods",gaiman,rao,2019,"Fantasy",16,465,45.99,"",0);
        adaugaCF(bib,"ISBN-F025","Good Omens",gaiman,rao,2020,"Comedie",14,288,39.99,"",0);
        adaugaCF(bib,"ISBN-F026","The Colour of Magic",pratchett,humanitas,2019,"Comedie",12,243,35.99,"Discworld",1);
        adaugaCF(bib,"ISBN-F027","Guards Guards",pratchett,humanitas,2020,"Comedie",12,288,35.99,"Discworld",8);
        adaugaCF(bib,"ISBN-F028","Hitchhikers Guide to the Galaxy",adams,humanitas,2019,"SF Comedie",12,193,32.99,"HHGTTG",1);
        adaugaCF(bib,"ISBN-F029","The Shining",king,litera,2020,"Horror",18,447,45.99,"",0);
        adaugaCF(bib,"ISBN-F030","It",king,litera,2019,"Horror",18,1138,65.99,"",0);
        adaugaCF(bib,"ISBN-F031","Pet Sematary",king,litera,2020,"Horror",18,374,39.99,"",0);
        adaugaCF(bib,"ISBN-F032","Misery",king,litera,2021,"Horror",18,310,35.99,"",0);
        adaugaCF(bib,"ISBN-F033","The Stand",king,litera,2021,"Horror",18,1152,65.99,"",0);
        adaugaCF(bib,"ISBN-F034","A Game of Thrones",martin_g,rao,2020,"Fantasy",16,694,55.99,"ASOIAF",1);
        adaugaCF(bib,"ISBN-F035","A Clash of Kings",martin_g,rao,2020,"Fantasy",16,768,55.99,"ASOIAF",2);
        adaugaCF(bib,"ISBN-F036","A Storm of Swords",martin_g,rao,2021,"Fantasy",16,992,59.99,"ASOIAF",3);
        adaugaCF(bib,"ISBN-F037","The Final Empire",sanderson,nemira,2021,"Fantasy",14,541,49.99,"Mistborn",1);
        adaugaCF(bib,"ISBN-F038","The Well of Ascension",sanderson,nemira,2021,"Fantasy",14,590,49.99,"Mistborn",2);
        adaugaCF(bib,"ISBN-F039","The Hero of Ages",sanderson,nemira,2022,"Fantasy",14,572,49.99,"Mistborn",3);
        adaugaCF(bib,"ISBN-F040","The Way of Kings",sanderson,nemira,2022,"Fantasy",16,1007,65.99,"Stormlight",1);
        adaugaCF(bib,"ISBN-F041","The Name of the Wind",rothfuss,nemira,2020,"Fantasy",16,662,55.99,"Kingkiller",1);
        adaugaCF(bib,"ISBN-F042","The Wise Mans Fear",rothfuss,nemira,2021,"Fantasy",16,994,59.99,"Kingkiller",2);
        adaugaCF(bib,"ISBN-F043","The Blade Itself",abercrom,humanitas,2020,"Fantasy",16,515,45.99,"First Law",1);
        adaugaCF(bib,"ISBN-F044","Before They Are Hanged",abercrom,humanitas,2021,"Fantasy",16,543,45.99,"First Law",2);
        adaugaCF(bib,"ISBN-F045","The Eye of the World",jordan,rao,2019,"Fantasy",14,782,55.99,"Wheel of Time",1);
        adaugaCF(bib,"ISBN-F046","The Great Hunt",jordan,rao,2019,"Fantasy",14,599,52.99,"Wheel of Time",2);
        adaugaCF(bib,"ISBN-F047","The Dragon Reborn",jordan,rao,2020,"Fantasy",14,675,49.99,"Wheel of Time",3);
        adaugaCF(bib,"ISBN-F048","The Night Angel vol 1",weeks,nemira,2020,"Fantasy",16,645,49.99,"Night Angel",1);
        adaugaCF(bib,"ISBN-F049","The Night Angel vol 2",weeks,nemira,2021,"Fantasy",16,592,49.99,"Night Angel",2);
        adaugaCF(bib,"ISBN-F050","Enders Game",bib.gasesteOrAdaugaAutor("Card","Orson Scott","American",1951,true),nemira,2020,"SF",12,324,39.99,"",0);
        adaugaCF(bib,"ISBN-F051","The Martian",bib.gasesteOrAdaugaAutor("Weir","Andy","American",1972,true),rao,2020,"SF",14,369,42.99,"",0);
        adaugaCF(bib,"ISBN-F052","Project Hail Mary",bib.gasesteOrAdaugaAutor("Weir","Andy","American",1972,true),rao,2022,"SF",14,476,45.99,"",0);
        adaugaCF(bib,"ISBN-F053","Red Rising",bib.gasesteOrAdaugaAutor("Brown","Pierce","American",1988,true),nemira,2020,"SF",16,382,42.99,"Red Rising",1);
        adaugaCF(bib,"ISBN-F054","Hyperion",bib.gasesteOrAdaugaAutor("Simmons","Dan","American",1948,true),nemira,2020,"SF",16,481,49.99,"Hyperion",1);
        adaugaCF(bib,"ISBN-F055","Snow Crash",bib.gasesteOrAdaugaAutor("Stephenson","Neal","American",1959,true),nemira,2021,"Cyberpunk",18,440,45.99,"",0);
        // Clasici francezi
        adaugaCF(bib,"ISBN-F056","Les Miserables",hugo,humanitas,2019,"Roman social",14,1463,59.99,"",0);
        adaugaCF(bib,"ISBN-F057","Notre-Dame de Paris",hugo,humanitas,2020,"Roman gotic",14,512,42.99,"",0);
        adaugaCF(bib,"ISBN-F058","Cei trei muschetari",dumas,litera,2019,"Aventuri",12,576,45.99,"",0);
        adaugaCF(bib,"ISBN-F059","Contele de Monte Cristo vol 1",dumas,litera,2019,"Aventuri",14,512,45.99,"Monte Cristo",1);
        adaugaCF(bib,"ISBN-F060","Contele de Monte Cristo vol 2",dumas,litera,2019,"Aventuri",14,498,45.99,"Monte Cristo",2);
        adaugaCF(bib,"ISBN-F061","20000 de leghe sub mari",verne,corint,2019,"SF Aventuri",10,368,35.99,"",0);
        adaugaCF(bib,"ISBN-F062","Ocolul pamantului in 80 de zile",verne,corint,2019,"Aventuri",10,256,29.99,"",0);
        adaugaCF(bib,"ISBN-F063","Centrul Pamantului",verne,corint,2020,"SF Aventuri",10,256,29.99,"",0);
        adaugaCF(bib,"ISBN-F064","Pere Goriot",balzac,humanitas,2019,"Roman realist",16,334,34.99,"",0);
        adaugaCF(bib,"ISBN-F065","Strainul",camus,humanitas,2019,"Roman existentialist",16,160,22.99,"",0);
        adaugaCF(bib,"ISBN-F066","Ciuma",camus,humanitas,2020,"Roman",16,320,32.99,"",0);
        adaugaCF(bib,"ISBN-F067","Procesul",kafka,humanitas,2019,"Roman",18,224,25.99,"",0);
        adaugaCF(bib,"ISBN-F068","Metamorfoza",kafka,humanitas,2019,"Nuvela",16,96,15.99,"",0);
        adaugaCF(bib,"ISBN-F069","Siddhartha",hesse,humanitas,2019,"Roman filozofic",14,152,22.99,"",0);
        adaugaCF(bib,"ISBN-F070","Lupul de stepa",hesse,humanitas,2020,"Roman",16,288,28.99,"",0);
        adaugaCF(bib,"ISBN-F071","Pe frontul de vest nimic nou",remarque,humanitas,2019,"Roman razboi",16,296,29.99,"",0);
        adaugaCF(bib,"ISBN-F072","Arc de triumf",remarque,humanitas,2020,"Roman",16,432,35.99,"",0);
        adaugaCF(bib,"ISBN-F073","Scrisoare catre o necunoscuta",zweig,humanitas,2019,"Nuvela",14,112,18.99,"",0);
        adaugaCF(bib,"ISBN-F074","Crime and Punishment",dostoev,humanitas,2019,"Roman clasic",16,671,45.99,"",0);
        adaugaCF(bib,"ISBN-F075","The Brothers Karamazov",dostoev,humanitas,2020,"Roman clasic",16,824,55.99,"",0);
        adaugaCF(bib,"ISBN-F076","War and Peace",tolstoy,humanitas,2021,"Roman clasic",16,1225,69.99,"",0);
        adaugaCF(bib,"ISBN-F077","Anna Karenina",tolstoy,humanitas,2020,"Roman clasic",16,864,55.99,"",0);
        adaugaCF(bib,"ISBN-F078","Batranul si marea",hemingway,humanitas,2019,"Nuvela",14,128,19.99,"",0);
        adaugaCF(bib,"ISBN-F079","Adio arme",hemingway,humanitas,2020,"Roman razboi",16,352,34.99,"",0);
        adaugaCF(bib,"ISBN-F080","Lolita",nabokov,humanitas,2020,"Roman",18,336,34.99,"",0);
        adaugaCF(bib,"ISBN-F081","Ficciones",borges,humanitas,2019,"Proza",18,174,24.99,"",0);
        adaugaCF(bib,"ISBN-F082","Numele trandafirului",eco,humanitas,2019,"Roman mister",16,502,42.99,"",0);
        adaugaCF(bib,"ISBN-F083","Norvegia Forest",murakami,humanitas,2019,"Roman",18,296,32.99,"",0);
        adaugaCF(bib,"ISBN-F084","1Q84 vol 1",murakami,humanitas,2020,"Roman",18,496,42.99,"1Q84",1);
        adaugaCF(bib,"ISBN-F085","1Q84 vol 2",murakami,humanitas,2021,"Roman",18,512,42.99,"1Q84",2);
        adaugaCF(bib,"ISBN-F086","Suta de ani de singuratate",marquez,rao,2019,"Realism magic",16,417,39.99,"",0);
        adaugaCF(bib,"ISBN-F087","Alchimistul",coelho,humanitas,2019,"Roman filozofic",14,192,22.99,"",0);
        adaugaCF(bib,"ISBN-F088","David Copperfield",dickens,humanitas,2019,"Roman",14,880,55.99,"",0);
        adaugaCF(bib,"ISBN-F089","Oliver Twist",dickens,humanitas,2019,"Roman",12,448,35.99,"",0);
        adaugaCF(bib,"ISBN-F090","Mandrie si prejudecata",austen,humanitas,2019,"Roman romantic",14,432,35.99,"",0);
        adaugaCF(bib,"ISBN-F091","Dorian Gray",wilde,humanitas,2019,"Roman",16,254,25.99,"",0);
        adaugaCF(bib,"ISBN-F092","Infernul",dante,humanitas,2019,"Poem epic",14,288,28.99,"Divina Comedie",1);
        adaugaCF(bib,"ISBN-F093","Iliada",homer,humanitas,2019,"Epopee",14,544,39.99,"",0);
        adaugaCF(bib,"ISBN-F094","Odiseea",homer,humanitas,2020,"Epopee",14,432,37.99,"",0);
        // Thriller
        adaugaCF(bib,"ISBN-F095","The Firm",grisham,litera,2019,"Thriller",16,421,35.99,"",0);
        adaugaCF(bib,"ISBN-F096","The Client",grisham,litera,2020,"Thriller",16,422,35.99,"",0);
        adaugaCF(bib,"ISBN-F097","A Time to Kill",grisham,litera,2019,"Thriller",16,515,39.99,"",0);
        adaugaCF(bib,"ISBN-F098","The Hunt for Red October",clancy,rao,2020,"Thriller militar",16,497,39.99,"",0);
        adaugaCF(bib,"ISBN-F099","The Bourne Identity",ludlum,rao,2019,"Thriller spionaj",16,535,39.99,"",0);
        adaugaCF(bib,"ISBN-F100","And Then There Were None",christie,litera,2019,"Mister",14,245,29.99,"",0);
        adaugaCF(bib,"ISBN-F101","Murder on the Orient Express",christie,litera,2020,"Mister",14,212,28.99,"",0);
        adaugaCF(bib,"ISBN-F102","The Da Vinci Code",brown_d,rao,2020,"Thriller",16,454,39.99,"",0);
        adaugaCF(bib,"ISBN-F103","The Girl with the Dragon Tattoo",larsson,litera,2019,"Thriller",18,465,42.99,"Millennium",1);
        adaugaCF(bib,"ISBN-F104","Killing Floor",child_l,litera,2020,"Thriller",16,424,35.99,"Jack Reacher",1);
        adaugaCF(bib,"ISBN-F105","Die Trying",child_l,litera,2021,"Thriller",16,448,35.99,"Jack Reacher",2);
        // Literatura romana
        adaugaCF(bib,"ISBN-F106","Poezii",eminescu,minerva,2018,"Poezie",12,312,25.99,"",0);
        adaugaCF(bib,"ISBN-F107","Amintiri din Copilarie",creanga,minerva,2018,"Proza",8,156,15.99,"",0);
        adaugaCF(bib,"ISBN-F108","Povesti",creanga,corint,2019,"Proza",6,200,18.99,"",0);
        adaugaCF(bib,"ISBN-F109","O Scrisoare Pierduta",caragiale,humanitas,2018,"Teatru",14,128,15.99,"",0);
        adaugaCF(bib,"ISBN-F110","Ion",rebreanu,humanitas,2020,"Roman",16,448,35.99,"",0);
        adaugaCF(bib,"ISBN-F111","Padurea Spanzuratilor",rebreanu,humanitas,2019,"Roman",16,352,32.99,"",0);
        adaugaCF(bib,"ISBN-F112","Baltagul",sadoveanu,minerva,2018,"Roman",14,245,25.99,"",0);
        adaugaCF(bib,"ISBN-F113","Morometii vol 1",preda,humanitas,2020,"Roman",16,312,32.99,"Morometii",1);
        adaugaCF(bib,"ISBN-F114","Morometii vol 2",preda,humanitas,2020,"Roman",16,298,32.99,"Morometii",2);
        adaugaCF(bib,"ISBN-F115","Nostalgia",cartarescu,humanitas,2019,"Proza",18,312,39.99,"",0);
        adaugaCF(bib,"ISBN-F116","Orbitor Aripa Stanga",cartarescu,humanitas,2020,"Roman",18,412,49.99,"Orbitor",1);
        adaugaCF(bib,"ISBN-F117","Solenoid",cartarescu,humanitas,2021,"Roman",18,860,65.99,"",0);
        adaugaCF(bib,"ISBN-F118","Poemele luminii",blaga,minerva,2019,"Poezie",14,96,14.99,"",0);
        adaugaCF(bib,"ISBN-F119","Flori de mucigai",arghezi,minerva,2019,"Poezie",16,96,15.99,"",0);
        adaugaCF(bib,"ISBN-F120","Cantareata cheala",ionesco,humanitas,2019,"Teatru",16,128,18.99,"",0);
        adaugaCF(bib,"ISBN-F121","Maitreyi",eliade,humanitas,2019,"Roman",16,224,24.99,"",0);
        adaugaCF(bib,"ISBN-F122","Ultima noapte de dragoste",petrescu,humanitas,2019,"Roman",16,288,28.99,"",0);
        adaugaCF(bib,"ISBN-F123","Jurnalul fericirii",steinhardt,bib.gasesteOrAdaugaEditura("Polirom","Romania","Iasi"),2019,"Jurnal",16,448,39.99,"",0);
        adaugaCF(bib,"ISBN-F124","Jurnalul Annei Frank",bib.gasesteOrAdaugaAutor("Frank","Anne","Olandeza",1929,false),humanitas,2020,"Memorialistica",12,283,28.99,"",0);
        adaugaCF(bib,"ISBN-F125","Omul in cautarea sensului vietii",bib.gasesteOrAdaugaAutor("Frankl","Viktor","Austrian",1905,false),humanitas,2020,"Psihologie",16,157,21.99,"",0);
        adaugaCF(bib,"ISBN-F126","Micul Print",bib.gasesteOrAdaugaAutor("Saint-Exupery","Antoine de","Francez",1900,false),humanitas,2019,"Basm filozofic",8,96,15.99,"",0);
        adaugaCF(bib,"ISBN-F127","Old Mans War",bib.gasesteOrAdaugaAutor("Scalzi","John","American",1969,true),nemira,2021,"SF",16,351,39.99,"",0);
        adaugaCF(bib,"ISBN-F128","Elantris",sanderson,nemira,2021,"Fantasy",14,492,45.99,"",0);
        adaugaCF(bib,"ISBN-F129","Oathbringer",sanderson,nemira,2023,"Fantasy",16,1220,69.99,"Stormlight",3);
        adaugaCF(bib,"ISBN-F130","Ringworld",bib.gasesteOrAdaugaAutor("Niven","Larry","American",1938,true),nemira,2020,"SF",16,288,35.99,"",0);
        adaugaCF(bib,"ISBN-F131","The Fall of Hyperion",bib.gasesteOrAdaugaAutor("Simmons","Dan","American",1948,true),nemira,2021,"SF",16,517,49.99,"Hyperion",2);
        adaugaCF(bib,"ISBN-F132","Gardens of the Moon",bib.gasesteOrAdaugaAutor("Erikson","Steven","Canadian",1959,true),nemira,2021,"Fantasy",16,666,52.99,"Malazan",1);
        adaugaCF(bib,"ISBN-F133","Magician",bib.gasesteOrAdaugaAutor("Feist","Raymond E.","American",1945,true),nemira,2019,"Fantasy",14,681,49.99,"Riftwar",1);
        adaugaCF(bib,"ISBN-F134","Wizard First Rule",bib.gasesteOrAdaugaAutor("Goodkind","Terry","American",1948,true),nemira,2020,"Fantasy",16,836,52.99,"Sword of Truth",1);
        adaugaCF(bib,"ISBN-F135","The Bourne Supremacy",ludlum,rao,2020,"Thriller spionaj",16,597,39.99,"",0);
        adaugaCF(bib,"ISBN-F136","Patriot Games",clancy,rao,2020,"Thriller",16,540,39.99,"",0);
        adaugaCF(bib,"ISBN-F137","Angels and Demons",brown_d,rao,2019,"Thriller",16,430,39.99,"",0);
        adaugaCF(bib,"ISBN-F138","The Girl who Played with Fire",larsson,litera,2020,"Thriller",18,503,42.99,"Millennium",2);
        adaugaCF(bib,"ISBN-F139","Gone Girl",bib.gasesteOrAdaugaAutor("Flynn","Gillian","Americana",1971,true),litera,2021,"Thriller",18,415,39.99,"",0);
        adaugaCF(bib,"ISBN-F140","The Silent Patient",bib.gasesteOrAdaugaAutor("Michaelides","Alex","Cipriot",1977,true),litera,2022,"Thriller",18,325,35.99,"",0);
        adaugaCF(bib,"ISBN-F141","Mystic River",bib.gasesteOrAdaugaAutor("Lehane","Dennis","American",1965,true),litera,2020,"Thriller",16,401,35.99,"",0);
        adaugaCF(bib,"ISBN-F142","The Dispossessed",lequin,humanitas,2021,"SF",16,311,35.99,"",0);
        adaugaCF(bib,"ISBN-F143","Speaker for the Dead",bib.gasesteOrAdaugaAutor("Card","Orson Scott","American",1951,true),nemira,2021,"SF",14,360,39.99,"",0);
        adaugaCF(bib,"ISBN-F144","The Brothers Karamazov vol 2",dostoev,humanitas,2022,"Roman clasic",16,490,45.99,"",0);
        adaugaCF(bib,"ISBN-F145","Fratii Jderi",sadoveanu,minerva,2019,"Roman",14,580,45.99,"",0);
        adaugaCF(bib,"ISBN-F146","Cel mai iubit dintre pamanteni",preda,humanitas,2021,"Roman",18,896,65.99,"",0);
        adaugaCF(bib,"ISBN-F147","Parfumul",bib.gasesteOrAdaugaAutor("Suskind","Patrick","German",1949,true),litera,2019,"Roman",16,248,26.99,"",0);
        adaugaCF(bib,"ISBN-F148","Dragoste in vremea holerei",marquez,rao,2020,"Roman",16,384,37.99,"",0);
        adaugaCF(bib,"ISBN-F149","Zahir",coelho,humanitas,2020,"Roman",14,274,26.99,"",0);
        adaugaCF(bib,"ISBN-F150","Momente si Schite",caragiale,humanitas,2019,"Proza",14,246,22.99,"",0);
    }

    // ===================================================================
    // CARTI TEHNICA (~150 titluri)
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
        auto* alexandr  = bib.gasesteOrAdaugaAutor("Alexandrescu","Andrei","Roman",1975,true);
        auto* hunt      = bib.gasesteOrAdaugaAutor("Hunt","Andrew","American",1964,true);
        auto* lutz      = bib.gasesteOrAdaugaAutor("Lutz","Mark","American",1956,true);
        auto* evans     = bib.gasesteOrAdaugaAutor("Evans","Eric","American",1963,true);
        auto* newman    = bib.gasesteOrAdaugaAutor("Newman","Sam","Britanic",1978,true);

        adaugaCT(bib,"ISBN-T001","Clean Code",martin_r,prentice,2008,"Software Engineering","Avansat",431,89.99);
        adaugaCT(bib,"ISBN-T002","The Clean Coder",martin_r,prentice,2011,"Software Engineering","Avansat",210,79.99);
        adaugaCT(bib,"ISBN-T003","Clean Architecture",martin_r,prentice,2017,"Software Engineering","Avansat",432,89.99);
        adaugaCT(bib,"ISBN-T004","Design Patterns",gamma,prentice,1994,"Software Engineering","Avansat",395,95.99);
        adaugaCT(bib,"ISBN-T005","Refactoring",fowler,addison,1999,"Software Engineering","Intermediar",448,89.99);
        adaugaCT(bib,"ISBN-T006","The Art of Computer Programming vol 1",knuth,addison,2011,"Algoritmi","Avansat",672,120.99);
        adaugaCT(bib,"ISBN-T007","The Art of Computer Programming vol 2",knuth,addison,2014,"Algoritmi","Avansat",784,120.99);
        adaugaCT(bib,"ISBN-T008","The C++ Programming Language",stroustrup,addison,2013,"C++","Avansat",1368,125.99);
        adaugaCT(bib,"ISBN-T009","The C Programming Language",kernighan,prentice,1988,"C","Intermediar",274,79.99);
        adaugaCT(bib,"ISBN-T010","Modern Operating Systems",tanenbaum,prentice,2014,"Sisteme de Operare","Avansat",1136,115.99);
        adaugaCT(bib,"ISBN-T011","Computer Networks",tanenbaum,prentice,2010,"Retele","Intermediar",960,110.99);
        adaugaCT(bib,"ISBN-T012","Introduction to Algorithms",cormen,addison,2009,"Algoritmi","Avansat",1292,125.99);
        adaugaCT(bib,"ISBN-T013","Effective C++",meyers,addison,2005,"C++","Intermediar",320,79.99);
        adaugaCT(bib,"ISBN-T014","Effective Modern C++",meyers,oreilly,2014,"C++","Avansat",334,85.99);
        adaugaCT(bib,"ISBN-T015","Modern C++ Design",alexandr,addison,2001,"C++","Avansat",352,89.99);
        adaugaCT(bib,"ISBN-T016","The Pragmatic Programmer",hunt,addison,2019,"Software Engineering","Intermediar",352,79.99);
        adaugaCT(bib,"ISBN-T017","Learning Python",lutz,oreilly,2013,"Python","Incepator",1540,99.99);
        adaugaCT(bib,"ISBN-T018","Domain-Driven Design",evans,addison,2003,"Software Engineering","Avansat",560,89.99);
        adaugaCT(bib,"ISBN-T019","Building Microservices",newman,oreilly,2021,"Microservicii","Avansat",640,85.99);
        adaugaCT(bib,"ISBN-T020","Fluent Python",bib.gasesteOrAdaugaAutor("Ramalho","Luciano","Brazilian",1967,true),oreilly,2015,"Python","Avansat",792,89.99);
        adaugaCT(bib,"ISBN-T021","Hands-On Machine Learning",bib.gasesteOrAdaugaAutor("Geron","Aurelien","Francez",1975,true),oreilly,2019,"Machine Learning","Intermediar",856,95.99);
        adaugaCT(bib,"ISBN-T022","Deep Learning",bib.gasesteOrAdaugaAutor("Goodfellow","Ian","Canadian",1985,true),addison,2016,"Machine Learning","Avansat",800,119.99);
        adaugaCT(bib,"ISBN-T023","Effective Java",bib.gasesteOrAdaugaAutor("Bloch","Joshua","American",1961,true),addison,2018,"Java","Avansat",412,89.99);
        adaugaCT(bib,"ISBN-T024","Head First Java",bib.gasesteOrAdaugaAutor("Sierra","Kathy","Americana",1957,true),oreilly,2005,"Java","Incepator",688,75.99);
        adaugaCT(bib,"ISBN-T025","JavaScript The Good Parts",bib.gasesteOrAdaugaAutor("Crockford","Douglas","American",1955,true),oreilly,2008,"JavaScript","Intermediar",172,59.99);
        adaugaCT(bib,"ISBN-T026","Eloquent JavaScript",bib.gasesteOrAdaugaAutor("Haverbeke","Marijn","Olandez",1982,true),nostarch,2018,"JavaScript","Intermediar",472,65.99);
        adaugaCT(bib,"ISBN-T027","Database System Concepts",bib.gasesteOrAdaugaAutor("Silberschatz","Abraham","American",1952,true),addison,2019,"Baze de Date","Intermediar",1376,115.99);
        adaugaCT(bib,"ISBN-T028","Designing Data-Intensive Applications",bib.gasesteOrAdaugaAutor("Kleppmann","Martin","German",1984,true),oreilly,2017,"Baze de Date","Avansat",616,99.99);
        adaugaCT(bib,"ISBN-T029","The Phoenix Project",bib.gasesteOrAdaugaAutor("Kim","Gene","American",1971,true),oreilly,2013,"DevOps","Incepator",432,69.99);
        adaugaCT(bib,"ISBN-T030","Site Reliability Engineering",bib.gasesteOrAdaugaAutor("Beyer","Betsy","Americana",1983,true),oreilly,2016,"DevOps","Avansat",552,95.99);
        adaugaCT(bib,"ISBN-T031","Kubernetes in Action",bib.gasesteOrAdaugaAutor("Luksa","Marko","Slovenian",1979,true),manning,2017,"Cloud","Intermediar",624,89.99);
        adaugaCT(bib,"ISBN-T032","Hacking The Art of Exploitation",bib.gasesteOrAdaugaAutor("Erickson","Jon","American",1980,true),nostarch,2008,"Securitate","Avansat",488,79.99);
        adaugaCT(bib,"ISBN-T033","Applied Cryptography",bib.gasesteOrAdaugaAutor("Schneier","Bruce","American",1963,true),addison,2015,"Criptografie","Avansat",784,89.99);
        adaugaCT(bib,"ISBN-T034","TCP/IP Illustrated vol 1",bib.gasesteOrAdaugaAutor("Stevens","W. Richard","American",1951,false),addison,2011,"Retele","Avansat",1032,89.99);
        adaugaCT(bib,"ISBN-T035","The Linux Command Line",bib.gasesteOrAdaugaAutor("Shotts","William","American",1962,true),nostarch,2019,"Linux","Incepator",480,65.99);
        adaugaCT(bib,"ISBN-T036","The Algorithm Design Manual",bib.gasesteOrAdaugaAutor("Skiena","Steven","American",1961,true),addison,2020,"Algoritmi","Intermediar",800,89.99);
        adaugaCT(bib,"ISBN-T037","Cracking the Coding Interview",bib.gasesteOrAdaugaAutor("McDowell","Gayle","Americana",1982,true),addison,2015,"Interviuri","Intermediar",696,55.99);
        adaugaCT(bib,"ISBN-T038","System Design Interview",bib.gasesteOrAdaugaAutor("Xu","Alex","Chinese-American",1985,true),addison,2020,"Interviuri","Intermediar",309,49.99);
        adaugaCT(bib,"ISBN-T039","Programming Rust",bib.gasesteOrAdaugaAutor("Blandy","Jim","American",1972,true),oreilly,2021,"Rust","Intermediar",622,79.99);
        adaugaCT(bib,"ISBN-T040","The Go Programming Language",bib.gasesteOrAdaugaAutor("Donovan","Alan","American",1967,true),addison,2015,"Go","Intermediar",380,65.99);
        adaugaCT(bib,"ISBN-T041","Code Complete",bib.gasesteOrAdaugaAutor("McConnell","Steve","American",1962,true),addison,2004,"Software Engineering","Intermediar",960,95.99);
        adaugaCT(bib,"ISBN-T042","Test Driven Development",bib.gasesteOrAdaugaAutor("Beck","Kent","American",1961,true),addison,2002,"Software Engineering","Intermediar",240,75.99);
        adaugaCT(bib,"ISBN-T043","Working with Legacy Code",bib.gasesteOrAdaugaAutor("Feathers","Michael","American",1967,true),prentice,2004,"Software Engineering","Avansat",456,85.99);
        adaugaCT(bib,"ISBN-T044","Kafka The Definitive Guide",bib.gasesteOrAdaugaAutor("Shapira","Gwen","Israeliana",1979,true),oreilly,2021,"Streaming","Avansat",302,75.99);
        adaugaCT(bib,"ISBN-T045","Spark The Definitive Guide",bib.gasesteOrAdaugaAutor("Chambers","Bill","American",1990,true),oreilly,2018,"Big Data","Avansat",610,89.99);
        adaugaCT(bib,"ISBN-T046","Mastering Bitcoin",bib.gasesteOrAdaugaAutor("Antonopoulos","Andreas","Grec",1972,true),oreilly,2017,"Blockchain","Avansat",410,75.99);
        adaugaCT(bib,"ISBN-T047","Python Cookbook",bib.gasesteOrAdaugaAutor("Beazley","David","American",1967,true),oreilly,2013,"Python","Intermediar",706,85.99);
        adaugaCT(bib,"ISBN-T048","Automate the Boring Stuff",bib.gasesteOrAdaugaAutor("Sweigart","Al","American",1985,true),nostarch,2019,"Python","Incepator",580,49.99);
        adaugaCT(bib,"ISBN-T049","Pro Git",bib.gasesteOrAdaugaAutor("Chacon","Scott","American",1980,true),addison,2014,"Git","Incepator",440,55.99);
        adaugaCT(bib,"ISBN-T050","Continuous Delivery",bib.gasesteOrAdaugaAutor("Humble","Jez","Britanic",1978,true),addison,2010,"DevOps","Intermediar",512,89.99);
        adaugaCT(bib,"ISBN-T051","Docker Deep Dive",bib.gasesteOrAdaugaAutor("Poulton","Nigel","Britanic",1981,true),packt,2020,"Cloud","Incepator",260,65.99);
        adaugaCT(bib,"ISBN-T052","Terraform Up and Running",bib.gasesteOrAdaugaAutor("Brikman","Yevgeniy","American",1983,true),oreilly,2022,"Infrastructure","Intermediar",476,75.99);
        adaugaCT(bib,"ISBN-T053","MongoDB The Definitive Guide",bib.gasesteOrAdaugaAutor("Chodorow","Kristina","Americana",1983,true),oreilly,2019,"MongoDB","Intermediar",514,75.99);
        adaugaCT(bib,"ISBN-T054","High Performance MySQL",bib.gasesteOrAdaugaAutor("Schwartz","Baron","Canadian",1978,true),oreilly,2012,"MySQL","Avansat",828,89.99);
        adaugaCT(bib,"ISBN-T055","Node.js Design Patterns",bib.gasesteOrAdaugaAutor("Casciaro","Mario","Italian",1984,true),packt,2020,"Node.js","Avansat",660,79.99);
        adaugaCT(bib,"ISBN-T056","RESTful Web APIs",bib.gasesteOrAdaugaAutor("Richardson","Leonard","American",1972,true),oreilly,2013,"API Design","Intermediar",448,65.99);
        adaugaCT(bib,"ISBN-T057","Soft Skills",bib.gasesteOrAdaugaAutor("Sonmez","John","American",1980,true),manning,2014,"Cariera","Incepator",470,55.99);
        adaugaCT(bib,"ISBN-T058","The Managers Path",bib.gasesteOrAdaugaAutor("Fournier","Camille","Americana",1981,true),oreilly,2017,"Management","Intermediar",244,55.99);
        adaugaCT(bib,"ISBN-T059","C++ Concurrency in Action",bib.gasesteOrAdaugaAutor("Williams","Anthony","Britanic",1972,true),manning,2019,"C++","Avansat",592,79.99);
        adaugaCT(bib,"ISBN-T060","Computer Architecture",bib.gasesteOrAdaugaAutor("Patterson","David","American",1947,true),addison,2017,"Arhitectura","Avansat",800,115.99);
        adaugaCT(bib,"ISBN-T061","Game Engine Architecture",bib.gasesteOrAdaugaAutor("Gregory","Jason","American",1971,true),prentice,2018,"Game Dev","Avansat",1042,109.99);
        adaugaCT(bib,"ISBN-T062","Programming PyTorch",bib.gasesteOrAdaugaAutor("Pointer","Ian","Britanic",1975,true),oreilly,2019,"PyTorch","Intermediar",246,65.99);
        adaugaCT(bib,"ISBN-T063","Head First Design Patterns",bib.gasesteOrAdaugaAutor("Freeman","Eric","American",1965,true),oreilly,2020,"OOP","Intermediar",672,75.99);
        adaugaCT(bib,"ISBN-T064","Enterprise Integration Patterns",bib.gasesteOrAdaugaAutor("Hohpe","Gregor","German",1967,true),addison,2003,"Architecture","Avansat",736,89.99);
        adaugaCT(bib,"ISBN-T065","Implementing Domain-Driven Design",bib.gasesteOrAdaugaAutor("Vernon","Vaughn","American",1967,true),addison,2013,"Software Engineering","Avansat",656,89.99);
        adaugaCT(bib,"ISBN-T066","Structure and Interpretation of Programs",bib.gasesteOrAdaugaAutor("Abelson","Harold","American",1947,true),addison,1996,"Algoritmi","Avansat",657,95.99);
        adaugaCT(bib,"ISBN-T067","Learn You a Haskell",bib.gasesteOrAdaugaAutor("Lipovaca","Miran","Croat",1987,true),nostarch,2011,"Haskell","Incepator",400,49.99);
        adaugaCT(bib,"ISBN-T068","The Rust Programming Language",bib.gasesteOrAdaugaAutor("Klabnik","Steve","American",1986,true),nostarch,2022,"Rust","Incepator",560,55.99);
        adaugaCT(bib,"ISBN-T069","Hadoop The Definitive Guide",bib.gasesteOrAdaugaAutor("White","Tom","Britanic",1972,true),oreilly,2015,"Big Data","Intermediar",758,89.99);
        adaugaCT(bib,"ISBN-T070","Ansible for DevOps",bib.gasesteOrAdaugaAutor("Geerling","Jeff","American",1984,true),addison,2020,"Automatizare","Intermediar",436,69.99);
        adaugaCT(bib,"ISBN-T071","AWS in Action",bib.gasesteOrAdaugaAutor("Wittig","Andreas","German",1983,true),manning,2019,"AWS","Intermediar",528,79.99);
        adaugaCT(bib,"ISBN-T072","Prometheus Up and Running",bib.gasesteOrAdaugaAutor("Brazil","Brian","Irlandez",1980,true),oreilly,2018,"Monitoring","Intermediar",358,69.99);
        adaugaCT(bib,"ISBN-T073","GraphQL in Action",bib.gasesteOrAdaugaAutor("Buna","Samer","Libanezo",1983,true),manning,2021,"GraphQL","Intermediar",392,69.99);
        adaugaCT(bib,"ISBN-T074","TypeScript Quickly",bib.gasesteOrAdaugaAutor("Fain","Yakov","American",1962,true),manning,2020,"TypeScript","Intermediar",464,69.99);
        adaugaCT(bib,"ISBN-T075","Spring in Action",bib.gasesteOrAdaugaAutor("Walls","Craig","American",1967,true),manning,2018,"Java","Intermediar",520,79.99);
        adaugaCT(bib,"ISBN-T076","Python for Data Analysis",bib.gasesteOrAdaugaAutor("McKinney","Wes","American",1985,true),oreilly,2017,"Data Science","Intermediar",544,85.99);
        adaugaCT(bib,"ISBN-T077","Natural Language Processing",bib.gasesteOrAdaugaAutor("Bird","Steven","Australian",1968,true),oreilly,2009,"NLP","Intermediar",504,75.99);
        adaugaCT(bib,"ISBN-T078","Reinforcement Learning",bib.gasesteOrAdaugaAutor("Sutton","Richard","Canadian",1956,true),addison,2018,"AI","Avansat",526,89.99);
        adaugaCT(bib,"ISBN-T079","Patterns of Enterprise Application",fowler,addison,2002,"Software Engineering","Avansat",560,89.99);
        adaugaCT(bib,"ISBN-T080","The Mythical Man Month",bib.gasesteOrAdaugaAutor("Brooks","Fred","American",1931,false),addison,1995,"Management","Intermediar",336,69.99);
        adaugaCT(bib,"ISBN-T081","Release It",bib.gasesteOrAdaugaAutor("Nygard","Michael","American",1968,true),addison,2018,"Software Engineering","Avansat",376,69.99);
        adaugaCT(bib,"ISBN-T082","Growing Object Oriented Software",bib.gasesteOrAdaugaAutor("Freeman","Steve","Britanic",1966,true),addison,2009,"OOP","Avansat",384,79.99);
        adaugaCT(bib,"ISBN-T083","Redis in Action",bib.gasesteOrAdaugaAutor("Carlson","Josiah","American",1984,true),manning,2013,"Redis","Intermediar",320,65.99);
        adaugaCT(bib,"ISBN-T084","SQL Antipatterns",bib.gasesteOrAdaugaAutor("Karwin","Bill","American",1963,true),addison,2010,"SQL","Intermediar",352,65.99);
        adaugaCT(bib,"ISBN-T085","Making Embedded Systems",bib.gasesteOrAdaugaAutor("White","Elecia","Americana",1973,true),oreilly,2011,"Embedded","Intermediar",330,65.99);
        adaugaCT(bib,"ISBN-T086","Programming Arduino",bib.gasesteOrAdaugaAutor("Monk","Simon","Britanic",1957,true),addison,2016,"Arduino","Incepator",208,45.99);
        adaugaCT(bib,"ISBN-T087","Accelerate",bib.gasesteOrAdaugaAutor("Forsgren","Nicole","Americana",1978,true),oreilly,2018,"DevOps","Avansat",288,55.99);
        adaugaCT(bib,"ISBN-T088","A Philosophy of Software Design",bib.gasesteOrAdaugaAutor("Ousterhout","John","American",1954,true),addison,2018,"Software Engineering","Intermediar",190,45.99);
        adaugaCT(bib,"ISBN-T089","Clean Agile",martin_r,prentice,2019,"Software Engineering","Intermediar",240,75.99);
        adaugaCT(bib,"ISBN-T090","More Effective C++",meyers,addison,1996,"C++","Avansat",336,79.99);
        adaugaCT(bib,"ISBN-T091","Effective STL",meyers,addison,2001,"C++","Avansat",260,69.99);
        adaugaCT(bib,"ISBN-T092","C++ Primer Plus",bib.gasesteOrAdaugaAutor("Prata","Stephen","American",1948,true),addison,2011,"C++","Incepator",1200,85.99);
        adaugaCT(bib,"ISBN-T093","Functional Programming in C++",bib.gasesteOrAdaugaAutor("Cukic","Ivan","Serbian",1981,true),manning,2018,"C++","Avansat",320,69.99);
        adaugaCT(bib,"ISBN-T094","Microservices Patterns",bib.gasesteOrAdaugaAutor("Richardson","Chris","American",1962,true),manning,2018,"Microservicii","Avansat",520,79.99);
        adaugaCT(bib,"ISBN-T095","Designing Distributed Systems",bib.gasesteOrAdaugaAutor("Burns","Brendan","American",1979,true),oreilly,2018,"Distributed Systems","Intermediar",166,55.99);
        adaugaCT(bib,"ISBN-T096","Vue.js in Action",bib.gasesteOrAdaugaAutor("Hanchett","Erik","American",1978,true),manning,2018,"Vue.js","Intermediar",304,65.99);
        adaugaCT(bib,"ISBN-T097","Angular in Action",bib.gasesteOrAdaugaAutor("Wilken","Jeremy","American",1982,true),manning,2018,"Angular","Intermediar",296,65.99);
        adaugaCT(bib,"ISBN-T098","Learning React",bib.gasesteOrAdaugaAutor("Banks","Alex","American",1978,true),oreilly,2020,"React","Intermediar",312,69.99);
        adaugaCT(bib,"ISBN-T099","Elasticsearch in Action",bib.gasesteOrAdaugaAutor("Hinman","Matthew","American",1980,true),manning,2015,"Search","Intermediar",482,69.99);
        adaugaCT(bib,"ISBN-T100","Python Machine Learning",bib.gasesteOrAdaugaAutor("Raschka","Sebastian","German",1988,true),packt,2019,"Machine Learning","Intermediar",770,79.99);
        adaugaCT(bib,"ISBN-T101","Quantum Computing",bib.gasesteOrAdaugaAutor("Hidary","Jack","American",1968,true),addison,2021,"Quantum","Avansat",422,89.99);
        adaugaCT(bib,"ISBN-T102","Blockchain Basics",bib.gasesteOrAdaugaAutor("Drescher","Daniel","German",1971,true),addison,2017,"Blockchain","Incepator",255,55.99);
        adaugaCT(bib,"ISBN-T103","Python Tricks",bib.gasesteOrAdaugaAutor("Bader","Dan","German",1988,true),addison,2017,"Python","Intermediar",302,49.99);
        adaugaCT(bib,"ISBN-T104","Head First Python",bib.gasesteOrAdaugaAutor("Barry","Paul","Irlandez",1967,true),oreilly,2016,"Python","Incepator",624,65.99);
        adaugaCT(bib,"ISBN-T105","Data Science from Scratch",bib.gasesteOrAdaugaAutor("Grus","Joel","American",1980,true),oreilly,2019,"Data Science","Incepator",406,65.99);
        adaugaCT(bib,"ISBN-T106","The Art of Computer Programming vol 3",knuth,addison,2011,"Algoritmi","Avansat",780,120.99);
        adaugaCT(bib,"ISBN-T107","Competitive Programming",bib.gasesteOrAdaugaAutor("Halim","Steven","Singaporean",1983,true),addison,2013,"Algoritmi","Avansat",433,75.99);
        adaugaCT(bib,"ISBN-T108","Programming Kotlin",bib.gasesteOrAdaugaAutor("Jemerov","Dmitry","Rus",1984,true),addison,2017,"Kotlin","Intermediar",436,75.99);
        adaugaCT(bib,"ISBN-T109","Programming Scala",bib.gasesteOrAdaugaAutor("Wampler","Dean","American",1961,true),oreilly,2021,"Scala","Intermediar",622,89.99);
        adaugaCT(bib,"ISBN-T110","Swift Programming",bib.gasesteOrAdaugaAutor("Mathias","Matthew","American",1975,true),addison,2016,"Swift","Intermediar",624,75.99);
        adaugaCT(bib,"ISBN-T111","Object Design Style Guide",bib.gasesteOrAdaugaAutor("Noback","Matthias","Olandez",1984,true),manning,2019,"OOP","Intermediar",312,65.99);
        adaugaCT(bib,"ISBN-T112","Applying UML and Patterns",bib.gasesteOrAdaugaAutor("Larman","Craig","Canadian",1959,true),prentice,2004,"OOP","Intermediar",736,85.99);
        adaugaCT(bib,"ISBN-T113","The Web Application Hackers Handbook",bib.gasesteOrAdaugaAutor("Stuttard","Dafydd","Britanic",1975,true),addison,2011,"Securitate","Avansat",912,89.99);
        adaugaCT(bib,"ISBN-T114","Penetration Testing",bib.gasesteOrAdaugaAutor("Georgia","Weidman","Americana",1984,true),nostarch,2014,"Securitate","Intermediar",528,79.99);
        adaugaCT(bib,"ISBN-T115","Unix Network Programming",bib.gasesteOrAdaugaAutor("Stevens","W. Richard","American",1951,false),addison,2003,"Retele","Avansat",1024,95.99);
        adaugaCT(bib,"ISBN-T116","Cassandra The Definitive Guide",bib.gasesteOrAdaugaAutor("Hewitt","Eben","American",1971,true),oreilly,2022,"Cassandra","Avansat",344,69.99);
        adaugaCT(bib,"ISBN-T117","PostgreSQL Up and Running",bib.gasesteOrAdaugaAutor("Obe","Regina","Americana",1972,true),oreilly,2017,"PostgreSQL","Intermediar",334,65.99);
        adaugaCT(bib,"ISBN-T118","Learning MySQL",bib.gasesteOrAdaugaAutor("Dyer","Russel","American",1965,true),oreilly,2007,"MySQL","Incepator",388,59.99);
        adaugaCT(bib,"ISBN-T119","Peopleware",bib.gasesteOrAdaugaAutor("DeMarco","Tom","American",1940,true),addison,2013,"Management","Intermediar",264,65.99);
        adaugaCT(bib,"ISBN-T120","An Elegant Puzzle",bib.gasesteOrAdaugaAutor("Larson","Will","American",1983,true),addison,2019,"Engineering Management","Intermediar",280,55.99);
        adaugaCT(bib,"ISBN-T121","C++ Templates The Complete Guide",bib.gasesteOrAdaugaAutor("Vandevoorde","David","Belgian",1966,true),addison,2017,"C++","Avansat",840,99.99);
        adaugaCT(bib,"ISBN-T122","Digital Design and Computer Architecture",bib.gasesteOrAdaugaAutor("Harris","David","American",1970,true),addison,2012,"Hardware","Intermediar",712,89.99);
        adaugaCT(bib,"ISBN-T123","OpenGL Programming Guide",bib.gasesteOrAdaugaAutor("Shreiner","Dave","American",1963,true),addison,2013,"OpenGL","Intermediar",936,99.99);
        adaugaCT(bib,"ISBN-T124","TensorFlow in Action",bib.gasesteOrAdaugaAutor("Madhavan","Thushan","Sri Lankan",1988,true),manning,2022,"TensorFlow","Intermediar",424,69.99);
        adaugaCT(bib,"ISBN-T125","Real Time Rendering",bib.gasesteOrAdaugaAutor("Akenine-Moller","Tomas","Suedez",1971,true),prentice,2018,"Game Dev","Avansat",1198,115.99);
        adaugaCT(bib,"ISBN-T126","Pattern Recognition and ML",bib.gasesteOrAdaugaAutor("Bishop","Christopher","Britanic",1959,true),addison,2006,"Machine Learning","Avansat",738,115.99);
        adaugaCT(bib,"ISBN-T127","Speech and Language Processing",bib.gasesteOrAdaugaAutor("Jurafsky","Daniel","American",1962,true),prentice,2022,"NLP","Avansat",632,99.99);
        adaugaCT(bib,"ISBN-T128","Computer Vision",bib.gasesteOrAdaugaAutor("Szeliski","Richard","American",1958,true),addison,2022,"Computer Vision","Avansat",932,109.99);
        adaugaCT(bib,"ISBN-T129","The Staff Engineers Path",bib.gasesteOrAdaugaAutor("Reilly","Tanya","Irlandeza",1979,true),oreilly,2022,"Cariera","Avansat",422,65.99);
        adaugaCT(bib,"ISBN-T130","Raspberry Pi Cookbook",bib.gasesteOrAdaugaAutor("Monk","Simon","Britanic",1957,true),oreilly,2016,"Raspberry Pi","Incepator",412,55.99);
        adaugaCT(bib,"ISBN-T131","Linux Kernel Development",bib.gasesteOrAdaugaAutor("Love","Robert","American",1981,true),addison,2010,"Linux","Avansat",440,89.99);
        adaugaCT(bib,"ISBN-T132","Python for Everybody",bib.gasesteOrAdaugaAutor("Severance","Charles","American",1961,true),addison,2016,"Python","Incepator",244,45.99);
        adaugaCT(bib,"ISBN-T133","The Elements of Statistical Learning",bib.gasesteOrAdaugaAutor("Hastie","Trevor","American",1953,true),addison,2017,"Machine Learning","Avansat",768,110.99);
        adaugaCT(bib,"ISBN-T134","AWS Lambda in Action",bib.gasesteOrAdaugaAutor("Poccia","Danilo","Italian",1980,true),manning,2016,"Serverless","Intermediar",338,65.99);
        adaugaCT(bib,"ISBN-T135","Kubernetes Patterns",bib.gasesteOrAdaugaAutor("Ibryam","Bilgin","Bulgarian",1980,true),oreilly,2019,"Cloud","Avansat",260,65.99);
        adaugaCT(bib,"ISBN-T136","Cloud Native Patterns",bib.gasesteOrAdaugaAutor("Davis","Cornelia","Americana",1967,true),manning,2019,"Cloud","Intermediar",400,75.99);
        adaugaCT(bib,"ISBN-T137","RabbitMQ in Action",bib.gasesteOrAdaugaAutor("Videla","Alvaro","Argentinian",1977,true),manning,2012,"Mesagerie","Intermediar",312,65.99);
        adaugaCT(bib,"ISBN-T138","Computer Security Art and Science",bib.gasesteOrAdaugaAutor("Bishop","Matt","American",1956,true),addison,2018,"Securitate","Avansat",1136,115.99);
        adaugaCT(bib,"ISBN-T139","Programming Go",bib.gasesteOrAdaugaAutor("Calvert","Charles","American",1963,true),manning,2021,"Go","Intermediar",400,69.99);
        adaugaCT(bib,"ISBN-T140","Programming Haskell",bib.gasesteOrAdaugaAutor("Hutton","Graham","Britanic",1968,true),prentice,2016,"Haskell","Intermediar",299,65.99);
        adaugaCT(bib,"ISBN-T141","Beginning C++ Through Game Programming",bib.gasesteOrAdaugaAutor("Dawson","Michael","American",1974,true),addison,2015,"C++","Incepator",390,55.99);
        adaugaCT(bib,"ISBN-T142","Continuous Delivery",bib.gasesteOrAdaugaAutor("Humble","Jez","Britanic",1978,true),addison,2010,"DevOps","Intermediar",512,89.99);
        adaugaCT(bib,"ISBN-T143","Java The Complete Reference",bib.gasesteOrAdaugaAutor("Schildt","Herbert","American",1952,true),addison,2018,"Java","Intermediar",1248,99.99);
        adaugaCT(bib,"ISBN-T144","HTML and CSS Design and Build",bib.gasesteOrAdaugaAutor("Duckett","Jon","Britanic",1974,true),addison,2011,"Web","Incepator",490,55.99);
        adaugaCT(bib,"ISBN-T145","Google Cloud Platform in Action",bib.gasesteOrAdaugaAutor("Geewax","JJ","American",1982,true),manning,2018,"GCP","Intermediar",408,75.99);
        adaugaCT(bib,"ISBN-T146","The Practice of Network Security",bib.gasesteOrAdaugaAutor("Bejtlich","Richard","American",1973,true),nostarch,2013,"Securitate","Intermediar",376,65.99);
        adaugaCT(bib,"ISBN-T147","Programming PyTorch for Deep Learning",bib.gasesteOrAdaugaAutor("Pointer","Ian","Britanic",1975,true),oreilly,2019,"PyTorch","Intermediar",246,65.99);
        adaugaCT(bib,"ISBN-T148","Mastering Ethereum",bib.gasesteOrAdaugaAutor("Antonopoulos","Andreas","Grec",1972,true),oreilly,2018,"Blockchain","Avansat",422,79.99);
        adaugaCT(bib,"ISBN-T149","Learning Elasticsearch",bib.gasesteOrAdaugaAutor("Gupta","Bharvi","Indian",1985,true),packt,2017,"Elasticsearch","Intermediar",394,65.99);
        adaugaCT(bib,"ISBN-T150","Computer Organization and Design",bib.gasesteOrAdaugaAutor("Patterson","David","American",1947,true),addison,2020,"Arhitectura","Avansat",864,99.99);
    }

    // ===================================================================
    // CARTI EDUCATIVA (~175 titluri)
    // ===================================================================
    static void seedCartiEducativa(Biblioteca& bib)
    {
        // Matematica
        adaugaCE(bib,"ISBN-E001","Matematica cls 5","Matematica","Real",5,2022,224,25.99);
        adaugaCE(bib,"ISBN-E002","Matematica cls 6","Matematica","Real",6,2022,240,25.99);
        adaugaCE(bib,"ISBN-E003","Matematica cls 7","Matematica","Real",7,2022,256,27.99);
        adaugaCE(bib,"ISBN-E004","Matematica cls 8","Matematica","Real",8,2022,272,27.99);
        adaugaCE(bib,"ISBN-E005","Matematica cls 9","Matematica","Real",9,2022,288,29.99);
        adaugaCE(bib,"ISBN-E006","Matematica cls 10","Matematica","Real",10,2022,304,29.99);
        adaugaCE(bib,"ISBN-E007","Matematica cls 11","Matematica","Real",11,2022,320,32.99);
        adaugaCE(bib,"ISBN-E008","Matematica cls 12","Matematica","Real",12,2022,336,32.99);
        adaugaCE(bib,"ISBN-E009","Algebra liniara","Matematica","Real",0,2021,312,39.99);
        adaugaCE(bib,"ISBN-E010","Analiza matematica vol 1","Matematica","Real",0,2021,428,45.99);
        adaugaCE(bib,"ISBN-E011","Analiza matematica vol 2","Matematica","Real",0,2021,398,45.99);
        adaugaCE(bib,"ISBN-E012","Probabilitati si statistica","Matematica","Real",0,2022,312,39.99);
        adaugaCE(bib,"ISBN-E013","Culegere matematica cls 9-12","Matematica","Real",9,2023,512,45.99);
        adaugaCE(bib,"ISBN-E014","Bacalaureat matematica","Matematica","Real",12,2023,288,32.99);
        adaugaCE(bib,"ISBN-E015","Matematica pentru olimpici","Matematica","Real",9,2022,384,38.99);
        adaugaCE(bib,"ISBN-E016","Calcul diferential si integral","Matematica","Real",0,2021,448,52.99);
        adaugaCE(bib,"ISBN-E017","Ecuatii diferentiale","Matematica","Real",0,2020,368,45.99);
        adaugaCE(bib,"ISBN-E018","Statistica Aplicata","Statistica","Real",0,2021,416,50.99);
        adaugaCE(bib,"ISBN-E019","Cercetari Operationale","Matematica","Economic",0,2021,448,52.99);
        adaugaCE(bib,"ISBN-E020","Admitere Politehnica","Matematica","Real",0,2023,384,38.99);
        // Fizica
        adaugaCE(bib,"ISBN-E021","Fizica cls 6","Fizica","Real",6,2022,192,22.99);
        adaugaCE(bib,"ISBN-E022","Fizica cls 7","Fizica","Real",7,2022,208,24.99);
        adaugaCE(bib,"ISBN-E023","Fizica cls 8","Fizica","Real",8,2022,224,24.99);
        adaugaCE(bib,"ISBN-E024","Fizica cls 9","Fizica","Real",9,2022,240,26.99);
        adaugaCE(bib,"ISBN-E025","Fizica cls 10","Fizica","Real",10,2022,256,26.99);
        adaugaCE(bib,"ISBN-E026","Fizica cls 11","Fizica","Real",11,2022,272,28.99);
        adaugaCE(bib,"ISBN-E027","Fizica cls 12","Fizica","Real",12,2022,288,28.99);
        adaugaCE(bib,"ISBN-E028","Culegere Fizica cls 9-12","Fizica","Real",9,2023,448,39.99);
        adaugaCE(bib,"ISBN-E029","Mecanica clasica","Fizica","Real",0,2021,368,42.99);
        adaugaCE(bib,"ISBN-E030","Electromagnetism","Fizica","Real",0,2021,412,45.99);
        adaugaCE(bib,"ISBN-E031","Fizica cuantica","Fizica","Real",0,2020,448,49.99);
        adaugaCE(bib,"ISBN-E032","Termodinamica tehnica","Fizica","Real",0,2021,416,50.99);
        // Chimie
        adaugaCE(bib,"ISBN-E033","Chimie cls 7","Chimie","Real",7,2022,176,22.99);
        adaugaCE(bib,"ISBN-E034","Chimie cls 8","Chimie","Real",8,2022,192,22.99);
        adaugaCE(bib,"ISBN-E035","Chimie cls 9","Chimie","Real",9,2022,208,24.99);
        adaugaCE(bib,"ISBN-E036","Chimie cls 10","Chimie","Real",10,2022,224,24.99);
        adaugaCE(bib,"ISBN-E037","Chimie organica cls 11","Chimie","Real",11,2022,256,27.99);
        adaugaCE(bib,"ISBN-E038","Chimie anorganica cls 12","Chimie","Real",12,2022,240,27.99);
        adaugaCE(bib,"ISBN-E039","Culegere Chimie","Chimie","Real",9,2023,384,38.99);
        // Biologie
        adaugaCE(bib,"ISBN-E040","Biologie cls 5","Biologie","Real",5,2022,160,20.99);
        adaugaCE(bib,"ISBN-E041","Biologie cls 6","Biologie","Real",6,2022,176,20.99);
        adaugaCE(bib,"ISBN-E042","Biologie cls 7","Biologie","Real",7,2022,192,22.99);
        adaugaCE(bib,"ISBN-E043","Biologie cls 8","Biologie","Real",8,2022,208,22.99);
        adaugaCE(bib,"ISBN-E044","Biologie cls 9","Biologie","Real",9,2022,224,24.99);
        adaugaCE(bib,"ISBN-E045","Biologie cls 10","Biologie","Real",10,2022,240,24.99);
        adaugaCE(bib,"ISBN-E046","Biologie cls 11","Biologie","Real",11,2022,256,26.99);
        adaugaCE(bib,"ISBN-E047","Biologie cls 12","Biologie","Real",12,2022,272,26.99);
        adaugaCE(bib,"ISBN-E048","Admitere Medicina","Biologie","Real",0,2023,448,42.99);
        // Informatica
        adaugaCE(bib,"ISBN-E049","Informatica cls 9 C++","Informatica","Real",9,2020,256,32.99);
        adaugaCE(bib,"ISBN-E050","Informatica cls 10 C++","Informatica","Real",10,2021,272,32.99);
        adaugaCE(bib,"ISBN-E051","Informatica cls 11 C++","Informatica","Real",11,2022,288,32.99);
        adaugaCE(bib,"ISBN-E052","Informatica cls 12 C++","Informatica","Real",12,2022,304,34.99);
        adaugaCE(bib,"ISBN-E053","Bacalaureat Informatica","Informatica","Real",12,2023,320,35.99);
        adaugaCE(bib,"ISBN-E054","Informatica pentru olimpici","Informatica","Real",9,2021,352,36.99);
        adaugaCE(bib,"ISBN-E055","Sisteme de operare","Informatica","Real",0,2021,384,48.99);
        adaugaCE(bib,"ISBN-E056","Retele de calculatoare","Informatica","Real",0,2021,448,52.99);
        adaugaCE(bib,"ISBN-E057","Baze de date","Informatica","Real",0,2022,368,45.99);
        adaugaCE(bib,"ISBN-E058","Programare orientata obiect","Informatica","Real",0,2022,416,50.99);
        adaugaCE(bib,"ISBN-E059","Structuri de date si algoritmi","Informatica","Real",0,2021,480,55.99);
        adaugaCE(bib,"ISBN-E060","Inteligenta Artificiala","Informatica","Real",0,2022,512,58.99);
        adaugaCE(bib,"ISBN-E061","Securitate Informatica","Informatica","Real",0,2022,448,54.99);
        adaugaCE(bib,"ISBN-E062","Cloud Computing","Informatica","Real",0,2022,384,48.99);
        adaugaCE(bib,"ISBN-E063","Internet of Things","Informatica","Real",0,2022,416,50.99);
        adaugaCE(bib,"ISBN-E064","Criptografie","Informatica","Real",0,2022,352,45.99);
        // Romana si Limbi
        adaugaCE(bib,"ISBN-E065","Limba Romana cls 5","Romana","Uman",5,2022,176,19.99);
        adaugaCE(bib,"ISBN-E066","Limba Romana cls 6","Romana","Uman",6,2022,192,19.99);
        adaugaCE(bib,"ISBN-E067","Limba Romana cls 7","Romana","Uman",7,2022,208,21.99);
        adaugaCE(bib,"ISBN-E068","Limba Romana cls 8","Romana","Uman",8,2022,224,21.99);
        adaugaCE(bib,"ISBN-E069","Limba si Literatura Romana cls 9","Romana","Uman",9,2022,240,24.99);
        adaugaCE(bib,"ISBN-E070","Limba si Literatura Romana cls 10","Romana","Uman",10,2022,256,24.99);
        adaugaCE(bib,"ISBN-E071","Limba si Literatura Romana cls 11","Romana","Uman",11,2022,272,26.99);
        adaugaCE(bib,"ISBN-E072","Limba si Literatura Romana cls 12","Romana","Uman",12,2022,288,26.99);
        adaugaCE(bib,"ISBN-E073","Bacalaureat Romana","Romana","Uman",12,2023,312,32.99);
        adaugaCE(bib,"ISBN-E074","Engleza pentru avansati","Engleza","Uman",0,2021,320,34.99);
        adaugaCE(bib,"ISBN-E075","IELTS Academic","Engleza","Uman",0,2022,448,45.99);
        adaugaCE(bib,"ISBN-E076","Franceza pentru incepatori","Franceza","Uman",0,2020,256,28.99);
        adaugaCE(bib,"ISBN-E077","Germana pentru incepatori","Germana","Uman",0,2020,272,29.99);
        adaugaCE(bib,"ISBN-E078","Spaniola pentru incepatori","Spaniola","Uman",0,2021,256,28.99);
        // Istorie si Geografie
        adaugaCE(bib,"ISBN-E079","Istorie cls 5","Istorie","Uman",5,2022,160,18.99);
        adaugaCE(bib,"ISBN-E080","Istorie cls 6","Istorie","Uman",6,2022,176,18.99);
        adaugaCE(bib,"ISBN-E081","Istorie cls 7","Istorie","Uman",7,2022,192,20.99);
        adaugaCE(bib,"ISBN-E082","Istorie cls 8","Istorie","Uman",8,2022,208,20.99);
        adaugaCE(bib,"ISBN-E083","Istoria Romanilor cls 11","Istorie","Uman",11,2022,256,24.99);
        adaugaCE(bib,"ISBN-E084","Bacalaureat Istorie","Istorie","Uman",12,2023,288,30.99);
        adaugaCE(bib,"ISBN-E085","Geografie Romania cls 9","Geografie","Uman",9,2022,224,22.99);
        adaugaCE(bib,"ISBN-E086","Bacalaureat Geografie","Geografie","Uman",12,2023,264,28.99);
        // Facultate Drept si Economie
        adaugaCE(bib,"ISBN-E087","Drept Civil vol 1","Drept","Juridic",0,2021,512,65.99);
        adaugaCE(bib,"ISBN-E088","Drept Penal general","Drept","Juridic",0,2021,480,62.99);
        adaugaCE(bib,"ISBN-E089","Drept Constitutional","Drept","Juridic",0,2022,512,62.99);
        adaugaCE(bib,"ISBN-E090","Drept Administrativ","Drept","Juridic",0,2021,480,59.99);
        adaugaCE(bib,"ISBN-E091","Procedura Civila","Drept","Juridic",0,2022,576,68.99);
        adaugaCE(bib,"ISBN-E092","Procedura Penala","Drept","Juridic",0,2022,544,65.99);
        adaugaCE(bib,"ISBN-E093","Admitere Drept","Romana","Juridic",0,2023,288,32.99);
        adaugaCE(bib,"ISBN-E094","Contabilitate generala","Economie","Economic",0,2022,448,55.99);
        adaugaCE(bib,"ISBN-E095","Macroeconomie","Economie","Economic",0,2020,412,52.99);
        adaugaCE(bib,"ISBN-E096","Microeconomie","Economie","Economic",0,2020,396,50.99);
        adaugaCE(bib,"ISBN-E097","Management general","Economie","Economic",0,2021,416,50.99);
        adaugaCE(bib,"ISBN-E098","Marketing","Economie","Economic",0,2022,384,47.99);
        adaugaCE(bib,"ISBN-E099","Admitere ASE","Matematica","Economic",0,2023,320,35.99);
        // Medicina
        adaugaCE(bib,"ISBN-E100","Anatomie umana vol 1","Medicina","Medical",0,2021,672,85.99);
        adaugaCE(bib,"ISBN-E101","Anatomie umana vol 2","Medicina","Medical",0,2021,688,85.99);
        adaugaCE(bib,"ISBN-E102","Fiziologie","Medicina","Medical",0,2020,768,92.99);
        adaugaCE(bib,"ISBN-E103","Biochimie medicala","Medicina","Medical",0,2021,624,79.99);
        adaugaCE(bib,"ISBN-E104","Farmacologie","Medicina","Medical",0,2021,864,98.99);
        adaugaCE(bib,"ISBN-E105","Microbiologie","Medicina","Medical",0,2020,592,75.99);
        adaugaCE(bib,"ISBN-E106","Nutritie si Dietetica","Medicina","Medical",0,2022,416,50.99);
        // Stiinte sociale si umaniste
        adaugaCE(bib,"ISBN-E107","Psihologie generala","Psihologie","Uman",0,2021,384,48.99);
        adaugaCE(bib,"ISBN-E108","Pedagogie","Pedagogie","Pedagogic",0,2021,416,50.99);
        adaugaCE(bib,"ISBN-E109","Filosofie","Filosofie","Uman",0,2020,448,52.99);
        adaugaCE(bib,"ISBN-E110","Logica formala","Filosofie","Uman",0,2021,320,40.99);
        adaugaCE(bib,"ISBN-E111","Sociologie generala","Sociologie","Uman",0,2022,384,47.99);
        adaugaCE(bib,"ISBN-E112","Comunicare si Relatii Publice","Comunicare","Uman",0,2022,368,46.99);
        adaugaCE(bib,"ISBN-E113","Relatii Internationale","Stiinte Politice","Uman",0,2022,448,52.99);
        adaugaCE(bib,"ISBN-E114","Istoria Artei vol 1","Arta","Uman",0,2020,512,65.99);
        adaugaCE(bib,"ISBN-E115","Istoria Artei vol 2","Arta","Uman",0,2021,528,65.99);
        // Tehnica inginereasca
        adaugaCE(bib,"ISBN-E116","Electrotehnica","Electrica","Real",0,2020,512,58.99);
        adaugaCE(bib,"ISBN-E117","Electronica digitala","Electronica","Real",0,2020,448,52.99);
        adaugaCE(bib,"ISBN-E118","Robotica","Automatizari","Real",0,2022,384,48.99);
        adaugaCE(bib,"ISBN-E119","Rezistenta Materialelor","Constructii","Tehnic",0,2022,512,62.99);
        adaugaCE(bib,"ISBN-E120","Mecanica Fluidelor","Mecanica","Real",0,2021,416,51.99);
        adaugaCE(bib,"ISBN-E121","Constructii Civile","Constructii","Tehnic",0,2021,512,62.99);
        adaugaCE(bib,"ISBN-E122","Tehnologia Materialelor","Tehnica","Tehnic",0,2020,512,62.99);
        adaugaCE(bib,"ISBN-E123","Grafica pe Calculator","Informatica","Real",0,2021,416,50.99);
        adaugaCE(bib,"ISBN-E124","Calcul Numeric","Matematica","Real",0,2021,368,46.99);
        adaugaCE(bib,"ISBN-E125","Teoria Jocurilor","Matematica","Economic",0,2020,312,40.99);
        adaugaCE(bib,"ISBN-E126","Econometrie","Economie","Economic",0,2022,384,47.99);
        adaugaCE(bib,"ISBN-E127","Matematici Financiare","Matematica","Economic",0,2022,320,42.99);
        adaugaCE(bib,"ISBN-E128","Ingineria Programarii","Informatica","Real",0,2021,448,52.99);
        adaugaCE(bib,"ISBN-E129","Sisteme Expert","Informatica","Real",0,2020,320,42.99);
        adaugaCE(bib,"ISBN-E130","Procesarea Imaginilor","Informatica","Real",0,2022,448,54.99);
        adaugaCE(bib,"ISBN-E131","Automatizari Industriale","Automatizari","Real",0,2021,448,54.99);
        adaugaCE(bib,"ISBN-E132","Organe de Masini","Mecanica","Tehnic",0,2021,576,68.99);
        adaugaCE(bib,"ISBN-E133","Metale si Aliaje","Metalurgie","Tehnic",0,2021,448,54.99);
        adaugaCE(bib,"ISBN-E134","Calitate si Fiabilitate","Calitate","Tehnic",0,2022,320,42.99);
        adaugaCE(bib,"ISBN-E135","Agrotehnica","Agronomie","Agricol",0,2020,480,55.99);
        adaugaCE(bib,"ISBN-E136","Zootehnie","Agronomie","Agricol",0,2021,448,52.99);
        adaugaCE(bib,"ISBN-E137","Geologie","Geografie","Real",0,2020,448,52.99);
        adaugaCE(bib,"ISBN-E138","Geografie economica mondiala","Geografie","Uman",0,2022,512,58.99);
        adaugaCE(bib,"ISBN-E139","Turism si Ospitalitate","Turism","Economic",0,2021,416,50.99);
        adaugaCE(bib,"ISBN-E140","Criminologie","Drept","Juridic",0,2021,384,48.99);
        adaugaCE(bib,"ISBN-E141","Finante publice","Economie","Economic",0,2021,448,52.99);
        adaugaCE(bib,"ISBN-E142","Drept Commercial","Drept","Juridic",0,2022,448,56.99);
        adaugaCE(bib,"ISBN-E143","Asistenta Sociala","Sociologie","Uman",0,2021,384,47.99);
        adaugaCE(bib,"ISBN-E144","Jurnalism","Comunicare","Uman",0,2021,320,42.99);
        adaugaCE(bib,"ISBN-E145","Publicitate si Reclama","Comunicare","Uman",0,2022,352,44.99);
        adaugaCE(bib,"ISBN-E146","Stiinte Politice","Stiinte Politice","Uman",0,2021,416,50.99);
        adaugaCE(bib,"ISBN-E147","Teoria Muzicii","Muzica","Uman",0,2019,320,42.99);
        adaugaCE(bib,"ISBN-E148","Arhitectura","Arhitectura","Tehnic",0,2020,512,68.99);
        adaugaCE(bib,"ISBN-E149","Bioinformatica","Informatica","Medical",0,2021,448,54.99);
        adaugaCE(bib,"ISBN-E150","Calcul Paralel","Informatica","Real",0,2021,416,50.99);
        adaugaCE(bib,"ISBN-E151","Recunoastere Forme","Informatica","Real",0,2021,384,48.99);
        adaugaCE(bib,"ISBN-E152","Patologie generala","Medicina","Medical",0,2022,712,88.99);
        adaugaCE(bib,"ISBN-E153","Psihologie sociala","Psihologie","Uman",0,2020,368,46.99);
        adaugaCE(bib,"ISBN-E154","Drept International Public","Drept","Juridic",0,2021,512,62.99);
        adaugaCE(bib,"ISBN-E155","Actuariat","Matematica","Economic",0,2021,384,48.99);
        adaugaCE(bib,"ISBN-E156","Geometrie diferentiala","Matematica","Real",0,2020,356,42.99);
        adaugaCE(bib,"ISBN-E157","Electronica analogica","Electronica","Real",0,2021,480,55.99);
        adaugaCE(bib,"ISBN-E158","Tehnici de Compilare","Informatica","Real",0,2020,512,60.99);
        adaugaCE(bib,"ISBN-E159","Realitate Virtuala","Informatica","Real",0,2022,352,45.99);
        adaugaCE(bib,"ISBN-E160","Modelare Sisteme","Informatica","Real",0,2022,368,46.99);
        adaugaCE(bib,"ISBN-E161","Fizica pentru olimpici","Fizica","Real",9,2022,368,37.99);
        adaugaCE(bib,"ISBN-E162","100 teste BAC Romana","Romana","Uman",12,2023,288,28.99);
        adaugaCE(bib,"ISBN-E163","100 teste BAC Matematica","Matematica","Real",12,2023,256,28.99);
        adaugaCE(bib,"ISBN-E164","100 teste BAC Fizica","Fizica","Real",12,2023,240,26.99);
        adaugaCE(bib,"ISBN-E165","100 teste BAC Chimie","Chimie","Real",12,2023,224,25.99);
        adaugaCE(bib,"ISBN-E166","100 teste BAC Biologie","Biologie","Real",12,2023,208,24.99);
        adaugaCE(bib,"ISBN-E167","100 teste BAC Engleza","Engleza","Uman",12,2023,272,27.99);
        adaugaCE(bib,"ISBN-E168","Admitere Academia Militara","Matematica","Real",0,2023,320,35.99);
        adaugaCE(bib,"ISBN-E169","Educatie Fizica si Sport","Educatie Fizica","Sport",0,2021,256,32.99);
        adaugaCE(bib,"ISBN-E170","Algebra cls 9","Matematica","Real",9,2022,192,24.99);
        adaugaCE(bib,"ISBN-E171","Trigonometrie","Matematica","Real",10,2022,144,22.99);
        adaugaCE(bib,"ISBN-E172","Geometrie cls 9","Matematica","Real",9,2022,176,23.99);
        adaugaCE(bib,"ISBN-E173","Statistica si probabilitati","Matematica","Real",11,2022,160,22.99);
        adaugaCE(bib,"ISBN-E174","Limba Engleza cls 9","Engleza","Uman",9,2022,208,26.99);
        adaugaCE(bib,"ISBN-E175","Limba Engleza cls 10","Engleza","Uman",10,2022,216,26.99);
    }

    // ===================================================================
    // CARTI COPII (~100 titluri)
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

        adaugaCC(bib,"ISBN-C001","Harry Potter si Piatra Filozofala",rowling,rao,2019,8,false,320,39.99);
        adaugaCC(bib,"ISBN-C002","Harry Potter si Camera Secretelor",rowling,rao,2019,8,false,352,39.99);
        adaugaCC(bib,"ISBN-C003","Harry Potter si Prizonierul din Azkaban",rowling,rao,2020,8,false,384,42.99);
        adaugaCC(bib,"ISBN-C004","Harry Potter si Pocalul de Foc",rowling,rao,2020,10,false,624,49.99);
        adaugaCC(bib,"ISBN-C005","Harry Potter si Ordinul Phoenix",rowling,rao,2020,10,false,816,55.99);
        adaugaCC(bib,"ISBN-C006","Harry Potter si Printul Semisange",rowling,rao,2021,10,false,607,49.99);
        adaugaCC(bib,"ISBN-C007","Harry Potter si Talismanele Mortii",rowling,rao,2021,10,false,607,49.99);
        adaugaCC(bib,"ISBN-C008","Charlie si Fabrica de Ciocolata",dahl,art,2019,6,false,176,25.99);
        adaugaCC(bib,"ISBN-C009","James si Piersica Uriasa",dahl,art,2020,6,false,144,22.99);
        adaugaCC(bib,"ISBN-C010","Matilda",dahl,art,2020,7,false,240,27.99);
        adaugaCC(bib,"ISBN-C011","The BFG",dahl,art,2021,6,false,208,25.99);
        adaugaCC(bib,"ISBN-C012","Vulpea Doamna",dahl,art,2021,5,false,96,15.99);
        adaugaCC(bib,"ISBN-C013","Leul Vrajitoarea si Dulapul",lewis,rao,2019,7,false,160,22.99);
        adaugaCC(bib,"ISBN-C014","Printul Caspian",lewis,rao,2020,8,false,195,22.99);
        adaugaCC(bib,"ISBN-C015","Calatoria pe Apa Zorilor",lewis,rao,2020,8,false,176,22.99);
        adaugaCC(bib,"ISBN-C016","Calul si Baiatul",lewis,rao,2020,8,false,192,22.99);
        adaugaCC(bib,"ISBN-C017","Ultima Batalie",lewis,rao,2021,9,false,184,22.99);
        adaugaCC(bib,"ISBN-C018","Mica Sirena",andersen,corint,2019,5,true,64,15.99);
        adaugaCC(bib,"ISBN-C019","Degetarica",andersen,corint,2019,4,true,48,12.99);
        adaugaCC(bib,"ISBN-C020","Craiasa Zapezii",andersen,corint,2020,6,false,96,18.99);
        adaugaCC(bib,"ISBN-C021","Rata cea Urata",andersen,corint,2020,4,true,48,12.99);
        adaugaCC(bib,"ISBN-C022","Soldatelul de Cositor",andersen,corint,2019,5,true,48,12.99);
        adaugaCC(bib,"ISBN-C023","Lebedele Salbatice",andersen,corint,2020,6,false,64,14.99);
        adaugaCC(bib,"ISBN-C024","Frumoasa din Padurea Adormita",grimm,litera,2019,5,true,64,14.99);
        adaugaCC(bib,"ISBN-C025","Alba ca Zapada",grimm,litera,2019,5,true,64,14.99);
        adaugaCC(bib,"ISBN-C026","Scufita Rosie",grimm,litera,2020,4,true,48,12.99);
        adaugaCC(bib,"ISBN-C027","Cenusareasa",grimm,litera,2020,5,true,64,14.99);
        adaugaCC(bib,"ISBN-C028","Hansel si Gretel",grimm,litera,2019,5,true,48,12.99);
        adaugaCC(bib,"ISBN-C029","Rapunzel",grimm,litera,2019,4,true,40,10.99);
        adaugaCC(bib,"ISBN-C030","Motanul Incaltat",grimm,litera,2020,4,true,48,12.99);
        adaugaCC(bib,"ISBN-C031","Harap Alb",ispirescu,corint,2019,7,false,96,18.99);
        adaugaCC(bib,"ISBN-C032","Praslea cel Voinic",ispirescu,corint,2020,7,false,80,16.99);
        adaugaCC(bib,"ISBN-C033","Fat Frumos din Lacrima",ispirescu,corint,2020,6,false,72,15.99);
        adaugaCC(bib,"ISBN-C034","Ileana Cosanzeana",ispirescu,corint,2019,6,false,80,16.99);
        adaugaCC(bib,"ISBN-C035","Zana Zorilor",ispirescu,corint,2020,6,false,72,15.99);
        adaugaCC(bib,"ISBN-C036","Greuceanu",ispirescu,corint,2020,7,false,88,17.99);
        adaugaCC(bib,"ISBN-C037","Winnie the Pooh",milne,art,2019,4,true,176,18.99);
        adaugaCC(bib,"ISBN-C038","Casa de la Coltul Padurii",milne,art,2020,4,true,176,18.99);
        adaugaCC(bib,"ISBN-C039","Pippi Sosetica",lindgren,litera,2020,6,false,160,19.99);
        adaugaCC(bib,"ISBN-C040","Fratii Inimii",lindgren,litera,2019,8,false,256,25.99);
        adaugaCC(bib,"ISBN-C041","Cartea junglei",kipling,litera,2019,7,false,256,24.99);
        adaugaCC(bib,"ISBN-C042","Captains Courageous",kipling,litera,2021,9,false,192,21.99);
        adaugaCC(bib,"ISBN-C043","Alice in Tara Minunilor",carroll,corint,2019,7,false,192,21.99);
        adaugaCC(bib,"ISBN-C044","Peter Pan",bib.gasesteOrAdaugaAutor("Barrie","J.M.","Scotian",1860,false),litera,2020,6,false,224,22.99);
        adaugaCC(bib,"ISBN-C045","Pinocchio",bib.gasesteOrAdaugaAutor("Collodi","Carlo","Italian",1826,false),corint,2019,6,false,192,18.99);
        adaugaCC(bib,"ISBN-C046","Heidi",bib.gasesteOrAdaugaAutor("Spyri","Johanna","Elvetiana",1827,false),litera,2020,8,false,256,24.99);
        adaugaCC(bib,"ISBN-C047","Pollyanna",bib.gasesteOrAdaugaAutor("Porter","Eleanor","Americana",1868,false),litera,2021,8,false,240,23.99);
        adaugaCC(bib,"ISBN-C048","Fetitele",bib.gasesteOrAdaugaAutor("Alcott","Louisa May","Americana",1832,false),litera,2021,9,false,544,38.99);
        adaugaCC(bib,"ISBN-C049","Singur pe lume",bib.gasesteOrAdaugaAutor("Malot","Hector","Francez",1830,false),litera,2020,9,false,416,34.99);
        adaugaCC(bib,"ISBN-C050","Emil si Detectivii",bib.gasesteOrAdaugaAutor("Kastner","Erich","German",1899,false),litera,2020,7,false,176,20.99);
        adaugaCC(bib,"ISBN-C051","Robinson Crusoe",bib.gasesteOrAdaugaAutor("Defoe","Daniel","Britanic",1660,false),corint,2021,10,false,312,28.99);
        adaugaCC(bib,"ISBN-C052","Don Quijote pentru copii",bib.gasesteOrAdaugaAutor("Cervantes","Miguel de","Spaniol",1547,false),corint,2020,10,false,224,23.99);
        adaugaCC(bib,"ISBN-C053","Insula comorii",bib.gasesteOrAdaugaAutor("Stevenson","Robert Louis","Scotian",1850,false),corint,2019,10,false,224,22.99);
        adaugaCC(bib,"ISBN-C054","Aventurile lui Tom Sawyer",bib.gasesteOrAdaugaAutor("Twain","Mark","American",1835,false),corint,2020,9,false,200,22.99);
        adaugaCC(bib,"ISBN-C055","Micul Lord",bib.gasesteOrAdaugaAutor("Burnett","Frances Hodgson","Britanica",1849,false),litera,2020,8,false,224,22.99);
        adaugaCC(bib,"ISBN-C056","Enciclopedia copiilor",col,corint,2021,6,true,256,45.99);
        adaugaCC(bib,"ISBN-C057","Atlasul lumii pentru copii",col,corint,2021,6,true,128,35.99);
        adaugaCC(bib,"ISBN-C058","Corpul uman pentru copii",col,corint,2022,7,true,128,32.99);
        adaugaCC(bib,"ISBN-C059","Sistemul solar pentru copii",col,corint,2021,7,true,96,24.99);
        adaugaCC(bib,"ISBN-C060","Dinozaurii uriasi",col,corint,2022,5,true,80,22.99);
        adaugaCC(bib,"ISBN-C061","Animale din Romania",col,corint,2021,6,true,112,29.99);
        adaugaCC(bib,"ISBN-C062","Istoria lumii pentru copii",col,corint,2020,8,false,192,35.99);
        adaugaCC(bib,"ISBN-C063","Romania pentru copii",col,corint,2021,7,true,128,28.99);
        adaugaCC(bib,"ISBN-C064","Experimente stiintifice acasa",col,art,2022,8,true,144,29.99);
        adaugaCC(bib,"ISBN-C065","Mitologie Greaca pentru copii",col,corint,2021,8,false,256,28.99);
        adaugaCC(bib,"ISBN-C066","Abecedar",col,corint,2022,1,true,128,18.99);
        adaugaCC(bib,"ISBN-C067","Matematica distractiva cls 1",col,corint,2022,1,true,96,18.99);
        adaugaCC(bib,"ISBN-C068","Matematica distractiva cls 2",col,corint,2022,2,true,104,18.99);
        adaugaCC(bib,"ISBN-C069","Matematica distractiva cls 3",col,corint,2022,3,true,112,19.99);
        adaugaCC(bib,"ISBN-C070","Matematica distractiva cls 4",col,corint,2022,4,true,120,19.99);
        adaugaCC(bib,"ISBN-C071","Citim si scriem cls 1",col,corint,2022,1,true,96,16.99);
        adaugaCC(bib,"ISBN-C072","Citim si scriem cls 2",col,corint,2022,2,true,104,16.99);
        adaugaCC(bib,"ISBN-C073","Carte de colorat cu animale",col,art,2021,3,true,64,10.99);
        adaugaCC(bib,"ISBN-C074","Carte de colorat cu printese",col,art,2021,4,true,64,10.99);
        adaugaCC(bib,"ISBN-C075","Povesti de noapte buna",col,corint,2020,3,false,256,28.99);
        adaugaCC(bib,"ISBN-C076","Gulliver in Tara Piticilor",bib.gasesteOrAdaugaAutor("Swift","Jonathan","Irlandez",1667,false),corint,2019,9,false,256,25.99);
        adaugaCC(bib,"ISBN-C077","Omul Invizibil",bib.gasesteOrAdaugaAutor("Wells","H.G.","Britanic",1866,false),litera,2021,10,false,224,22.99);
        adaugaCC(bib,"ISBN-C078","Razboiul Lumilor",bib.gasesteOrAdaugaAutor("Wells","H.G.","Britanic",1866,false),litera,2020,10,false,192,20.99);
        adaugaCC(bib,"ISBN-C079","Masina Timpului",bib.gasesteOrAdaugaAutor("Wells","H.G.","Britanic",1866,false),litera,2021,10,false,160,19.99);
        adaugaCC(bib,"ISBN-C080","Basme romanesti vol 1",ispirescu,corint,2020,6,false,192,22.99);
        adaugaCC(bib,"ISBN-C081","Basme romanesti vol 2",ispirescu,corint,2021,6,false,192,22.99);
        adaugaCC(bib,"ISBN-C082","Basme internationale vol 1",col,corint,2020,5,false,224,24.99);
        adaugaCC(bib,"ISBN-C083","Basme internationale vol 2",col,corint,2021,5,false,224,24.99);
        adaugaCC(bib,"ISBN-C084","Oceane si mari",col,corint,2022,6,true,96,24.99);
        adaugaCC(bib,"ISBN-C085","Mitologie Romana pentru copii",col,corint,2022,8,false,224,26.99);
        adaugaCC(bib,"ISBN-C086","Ghid de supravietuire in natura",col,corint,2022,9,true,192,26.99);
        adaugaCC(bib,"ISBN-C087","Carte de colorat cu dinozauri",col,art,2022,4,true,64,10.99);
        adaugaCC(bib,"ISBN-C088","Cum sa desenezi pas cu pas",col,art,2021,6,true,128,24.99);
        adaugaCC(bib,"ISBN-C089","Calatorie spre centrul pamantului copii",bib.gasesteOrAdaugaAutor("Verne","Jules","Francez",1828,false),corint,2021,9,false,256,25.99);
        adaugaCC(bib,"ISBN-C090","20000 de leghe copii",bib.gasesteOrAdaugaAutor("Verne","Jules","Francez",1828,false),corint,2020,9,false,312,28.99);
        adaugaCC(bib,"ISBN-C091","Cei trei muschetari pentru copii",bib.gasesteOrAdaugaAutor("Dumas","Alexandre","Francez",1802,false),corint,2019,9,false,224,22.99);
        adaugaCC(bib,"ISBN-C092","Printul si Sarmanul",bib.gasesteOrAdaugaAutor("Twain","Mark","American",1835,false),corint,2021,8,false,192,21.99);
        adaugaCC(bib,"ISBN-C093","Fetita cu Chibrituri",andersen,corint,2019,5,true,32,10.99);
        adaugaCC(bib,"ISBN-C094","Printatesa pe Mazare",andersen,corint,2020,4,true,32,10.99);
        adaugaCC(bib,"ISBN-C095","Frumoasa si Bestia",grimm,litera,2020,5,false,64,14.99);
        adaugaCC(bib,"ISBN-C096","Aventuri in jungla",kipling,litera,2022,7,false,192,21.99);
        adaugaCC(bib,"ISBN-C097","Micul Print pentru copii",bib.gasesteOrAdaugaAutor("Saint-Exupery","Antoine de","Francez",1900,false),bib.gasesteOrAdaugaEditura("Humanitas","Romania","Bucuresti"),2020,6,false,96,14.99);
        adaugaCC(bib,"ISBN-C098","Jurnalul unui pusti vol 1",bib.gasesteOrAdaugaAutor("Kinney","Jeff","American",1971,true),art,2021,8,false,224,29.99);
        adaugaCC(bib,"ISBN-C099","Jurnalul unui pusti vol 2",bib.gasesteOrAdaugaAutor("Kinney","Jeff","American",1971,true),art,2021,8,false,224,29.99);
        adaugaCC(bib,"ISBN-C100","Geronimo Stilton vol 1",bib.gasesteOrAdaugaAutor("Stilton","Geronimo","Italian",1969,true),litera,2020,6,true,128,18.99);
    }

    // ===================================================================
    // MATERIALE REFERINTA (~50 titluri)
    // ===================================================================
    static void seedMaterialeReferinta(Biblioteca& bib)
    {
        adaugaRef(bib,"ISBN-R001","Dictionarul Explicativ al Limbii Romane","Dictionar",2009,1192,120.99);
        adaugaRef(bib,"ISBN-R002","Dictionarul Ortografic DOOM3","Dictionar",2021,688,89.99);
        adaugaRef(bib,"ISBN-R003","Dictionarul de Sinonime","Dictionar",2019,512,55.99);
        adaugaRef(bib,"ISBN-R004","Dictionarul de Antonime","Dictionar",2019,384,49.99);
        adaugaRef(bib,"ISBN-R005","Dictionarul Englez-Roman","Dictionar",2020,1024,95.99);
        adaugaRef(bib,"ISBN-R006","Dictionarul Roman-Englez","Dictionar",2020,1024,95.99);
        adaugaRef(bib,"ISBN-R007","Dictionarul Francez-Roman","Dictionar",2019,896,89.99);
        adaugaRef(bib,"ISBN-R008","Dictionarul German-Roman","Dictionar",2019,912,89.99);
        adaugaRef(bib,"ISBN-R009","Dictionarul de Informatica","Dictionar",2020,512,65.99);
        adaugaRef(bib,"ISBN-R010","Dictionarul de Matematica","Dictionar",2018,448,55.99);
        adaugaRef(bib,"ISBN-R011","Dictionarul de Filosofie","Dictionar",2018,640,72.99);
        adaugaRef(bib,"ISBN-R012","Dictionarul de Psihologie","Dictionar",2019,512,62.99);
        adaugaRef(bib,"ISBN-R013","Dictionarul de Economie","Dictionar",2021,640,72.99);
        adaugaRef(bib,"ISBN-R014","Dictionarul Juridic","Dictionar",2022,768,85.99);
        adaugaRef(bib,"ISBN-R015","Dictionarul Medical","Dictionar",2021,896,95.99);
        adaugaRef(bib,"ISBN-R016","Dictionarul de Chimie","Dictionar",2019,512,62.99);
        adaugaRef(bib,"ISBN-R017","Dictionarul de Fizica","Dictionar",2020,480,59.99);
        adaugaRef(bib,"ISBN-R018","Dictionarul de Biologie","Dictionar",2019,544,65.99);
        adaugaRef(bib,"ISBN-R019","Dictionarul de Geografie","Dictionar",2020,512,62.99);
        adaugaRef(bib,"ISBN-R020","Dictionarul de Sociologie","Dictionar",2020,576,68.99);
        adaugaRef(bib,"ISBN-R021","Atlas Geografic General","Atlas",2021,256,95.99);
        adaugaRef(bib,"ISBN-R022","Atlas Geografic Romania","Atlas",2020,128,65.99);
        adaugaRef(bib,"ISBN-R023","Atlas Geografic Europa","Atlas",2021,160,72.99);
        adaugaRef(bib,"ISBN-R024","Atlas Geografic Lumea","Atlas",2022,320,110.99);
        adaugaRef(bib,"ISBN-R025","Atlas Anatomic Uman","Atlas",2020,224,85.99);
        adaugaRef(bib,"ISBN-R026","Atlas Botanic","Atlas",2019,192,75.99);
        adaugaRef(bib,"ISBN-R027","Atlas Zoologic","Atlas",2020,208,78.99);
        adaugaRef(bib,"ISBN-R028","Atlas Astronomic","Atlas",2021,176,72.99);
        adaugaRef(bib,"ISBN-R029","Atlas Istoric Romania","Atlas",2019,192,75.99);
        adaugaRef(bib,"ISBN-R030","Atlas Istoric Universal","Atlas",2020,256,89.99);
        adaugaRef(bib,"ISBN-R031","Atlas Militar WW2","Atlas",2019,320,99.99);
        adaugaRef(bib,"ISBN-R032","Atlas Flora Romaniei","Atlas",2020,288,92.99);
        adaugaRef(bib,"ISBN-R033","Atlas Fauna Romaniei","Atlas",2021,304,95.99);
        adaugaRef(bib,"ISBN-R034","Atlas Geologic Romania","Atlas",2019,256,85.99);
        adaugaRef(bib,"ISBN-R035","Enciclopedia Universala Britanica vol 1","Enciclopedie",2010,512,145.99);
        adaugaRef(bib,"ISBN-R036","Enciclopedia Universala Britanica vol 2","Enciclopedie",2010,512,145.99);
        adaugaRef(bib,"ISBN-R037","Enciclopedia Romaniei","Enciclopedie",2015,1024,180.99);
        adaugaRef(bib,"ISBN-R038","Enciclopedia Stiintei","Enciclopedie",2019,512,120.99);
        adaugaRef(bib,"ISBN-R039","Enciclopedia Istoriei Lumii","Enciclopedie",2020,640,135.99);
        adaugaRef(bib,"ISBN-R040","Enciclopedia Medicinei","Enciclopedie",2020,1280,165.99);
        adaugaRef(bib,"ISBN-R041","Enciclopedia Dreptului","Enciclopedie",2021,1024,145.99);
        adaugaRef(bib,"ISBN-R042","Enciclopedia Economiei","Enciclopedie",2019,896,125.99);
        adaugaRef(bib,"ISBN-R043","Enciclopedia Tehnicii","Enciclopedie",2020,1152,155.99);
        adaugaRef(bib,"ISBN-R044","Enciclopedia Culturii Romane","Enciclopedie",2021,1536,195.99);
        adaugaRef(bib,"ISBN-R045","Enciclopedia Geografiei Romaniei","Enciclopedie",2019,768,115.99);
        adaugaRef(bib,"ISBN-R046","Enciclopedia Florei si Faunei","Enciclopedie",2020,896,125.99);
        adaugaRef(bib,"ISBN-R047","Enciclopedia Mitologiei Universale","Enciclopedie",2022,1024,145.99);
        adaugaRef(bib,"ISBN-R048","Enciclopedia Informaticii","Enciclopedie",2021,768,115.99);
        adaugaRef(bib,"ISBN-R049","Istoria Romanilor vol 1","Enciclopedie",2001,480,75.99);
        adaugaRef(bib,"ISBN-R050","Istoria literaturii romane","Enciclopedie",2020,1064,85.99);
    }

    // ===================================================================
    // CARTI RELIGIOASE (~15 titluri)
    // ===================================================================
    static void seedCartiReligioase(Biblioteca& bib)
    {
        auto* humanitas = bib.gasesteOrAdaugaEditura("Humanitas","Romania","Bucuresti");
        auto* col       = bib.gasesteOrAdaugaAutor("Colectiv","Autori","Roman",2000,true);
        struct R { string isbn,titlu,religie,cult; int an,pag; double pret; };
        std::vector<R> v = {
            {"ISBN-REL001","Biblia editie integrala","Crestina","Ortodoxa",2018,1504,85.99},
            {"ISBN-REL002","Noul Testament","Crestina","Ortodoxa",2020,512,35.99},
            {"ISBN-REL003","Vechiul Testament","Crestina","Ortodoxa",2019,992,65.99},
            {"ISBN-REL004","Psaltirea","Crestina","Ortodoxa",2019,256,25.99},
            {"ISBN-REL005","Liturghierul","Crestina","Ortodoxa",2020,320,35.99},
            {"ISBN-REL006","Ceaslovul","Crestina","Ortodoxa",2020,448,42.99},
            {"ISBN-REL007","Viata Sfintilor vol 1","Crestina","Ortodoxa",2021,512,55.99},
            {"ISBN-REL008","Viata Sfintilor vol 2","Crestina","Ortodoxa",2021,528,55.99},
            {"ISBN-REL009","Viata Sfintilor vol 3","Crestina","Ortodoxa",2021,496,55.99},
            {"ISBN-REL010","Filocalia vol 1","Crestina","Ortodoxa",2018,480,65.99},
            {"ISBN-REL011","Filocalia vol 2","Crestina","Ortodoxa",2018,512,65.99},
            {"ISBN-REL012","Cararea Imparatiei","Crestina","Ortodoxa",2019,320,39.99},
            {"ISBN-REL013","Biblia Catolica","Crestina","Catolica",2019,1600,89.99},
            {"ISBN-REL014","Catehismul Bisericii Catolice","Crestina","Catolica",2020,896,72.99},
            {"ISBN-REL015","Coranul traducere comentata","Islamica","Islam",2018,608,55.99},
        };
        for (auto& d : v) {
            auto* c = new CarteReligioasa(d.isbn,d.titlu,{col},humanitas,d.an,LimbaCartii::ROMANA,TipCoperta::CARTONATA,d.religie,d.cult,d.pag,d.pret);
            try { bib.adaugaCarte(c); } catch(...){ delete c; continue; }
            try { bib.adaugaExemplarLaCarte(d.isbn,"Cladirea D","Sala Religioasa","R-REL","Religios",ProvenientaCarte::CUMPARATA,d.pret*0.6); } catch(...) {}
        }
    }

    // ===================================================================
    // PERIODICE (~15 titluri)
    // ===================================================================
    static void seedPeriodicale(Biblioteca& bib)
    {
        auto* adev = bib.gasesteOrAdaugaEditura("Adevarul Holding","Romania","Bucuresti");
        auto* col  = bib.gasesteOrAdaugaAutor("Colectiv","Autori","Roman",2000,true);
        struct P { string issn,titlu,tip,dom; int nr,luna,an,pag; double pret; };
        std::vector<P> v = {
            {"ISSN-Z001","Adevarul","Ziar","Stiri",12458,4,2024,24,5.99},
            {"ISSN-Z002","Romania Libera","Ziar","Stiri",8745,4,2024,24,5.99},
            {"ISSN-Z003","Gazeta Sporturilor","Ziar","Sport",15678,4,2024,32,5.99},
            {"ISSN-Z004","Libertatea","Ziar","Stiri",9876,4,2024,24,5.99},
            {"ISSN-Z005","Jurnalul National","Ziar","Stiri",7654,4,2024,24,5.99},
            {"ISSN-R001","National Geographic Romania","Revista","Geografie",256,4,2024,128,22.99},
            {"ISSN-R002","Stiinta si Tehnica","Revista","Stiinta",412,4,2024,96,18.99},
            {"ISSN-R003","Historia","Revista","Istorie",189,4,2024,112,19.99},
            {"ISSN-R004","Computer World","Revista","IT",678,4,2024,80,15.99},
            {"ISSN-R005","Chips","Revista","IT",534,4,2024,88,14.99},
            {"ISSN-R006","Psychologies Romania","Revista","Psihologie",145,4,2024,96,18.99},
            {"ISSN-R007","Forbes Romania","Revista","Business",112,4,2024,104,22.99},
            {"ISSN-R008","Business Magazine","Revista","Business",256,4,2024,88,18.99},
            {"ISSN-R009","Auto Motor Sport","Revista","Auto",345,4,2024,96,16.99},
            {"ISSN-R010","Viva","Revista","Lifestyle",456,4,2024,112,14.99},
        };
        for (auto& d : v) {
            auto* c = new Periodic(d.issn,d.titlu,{col},adev,d.an,LimbaCartii::ROMANA,d.tip,d.nr,d.luna,d.an,d.dom,d.pag);
            try { bib.adaugaCarte(c); } catch(...){ delete c; continue; }
            try { bib.adaugaExemplarLaCarte(d.issn,"Cladirea A","Sala Lectura","R-PER","Periodice",ProvenientaCarte::CUMPARATA,d.pret); } catch(...) {}
        }
    }

    // ===================================================================
    // MANUSCRISE RARE (~10 titluri)
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
            auto* c = new ManuscrisRar(d.isbn,d.titlu,{d.autor},minerva,d.an,LimbaCartii::ROMANA,TipCoperta::PIELE,d.epoca,"Temperatura 18C, umiditate 45%",true,d.pret);
            try { bib.adaugaCarte(c); } catch(...){ delete c; continue; }
            try { bib.adaugaExemplarLaCarte(d.isbn,"Cladirea E","Sala Arhiva","R-ARH","Manuscrise",ProvenientaCarte::MOSTENIRE,d.pret); } catch(...) {}
        }
    }

    // ===================================================================
    // UTILIZATORI (~200)
    // ===================================================================
    static void seedUtilizatori(Biblioteca& bib)
    {
        bib.adaugaUtilizator(new UtilizatorStaff("STAFF-001","Marin","Andreea","a.marin@bib.ro","staff001","Fictiune",RolStaff::BIBLIOTECAR_SEF,4200.0,2019,3));
        bib.adaugaUtilizator(new UtilizatorStaff("STAFF-002","Ionescu","Cristian","c.ionescu@bib.ro","staff002","Tehnica",RolStaff::BIBLIOTECAR,3500.0,2020,9));
        bib.adaugaUtilizator(new UtilizatorStaff("STAFF-003","Popescu","Elena","e.popescu@bib.ro","staff003","Educativa",RolStaff::BIBLIOTECAR,3500.0,2021,2));
        bib.adaugaUtilizator(new UtilizatorStaff("STAFF-004","Dumitrescu","Mihai","m.dumitrescu@bib.ro","staff004","Administrativ",RolStaff::ADMINISTRATOR,5500.0,2015,6));
        bib.adaugaUtilizator(new UtilizatorStaff("STAFF-005","Stanciu","Ana","a.stanciu@bib.ro","staff005","Casierie",RolStaff::CASIER,3200.0,2022,1));

        string fac[]    = {"FIESC","FSEAP","FIG","FSE","FDSA"};
        string pren[]   = {"Ana","Ion","Maria","Gheorghe","Elena","Mihai","Ioana","Alexandru","Andreea","Cristian","Daniela","Florin","Gabriela","Horia","Ileana","Iulian","Jana","Liviu","Monica","Nicolae","Octavia","Pavel","Raluca","Stefan","Teodora","Valentina","Vlad","Xenia","Zoran","Catalin"};
        string nm[]     = {"Pop","Ionescu","Popa","Georgescu","Stan","Mihai","Constantin","Dumitrescu","Radu","Stoica","Marin","Florescu","Dima","Lazar","Moldovan","Nistor","Oprea","Petrescu","Rusu","Serban","Tudor","Ungureanu","Vasilescu","Zamfir","Antal","Barbu","Coman","Dobre","Enache","Florea"};
        int c = 1;
        for (int i=0;i<30;i++) {
            string id="STU-"+std::to_string(1000+c++);
            bib.adaugaUtilizator(new UtilizatorStudent(id,nm[i],pren[i],pren[i]+"."+nm[i]+"@usv.ro","pass"+id,12,2024,9,fac[i%5],(i%4)+1,"MAT"+std::to_string(2024000+c)));
        }
        for (int i=0;i<80;i++) {
            string id="BAS-"+std::to_string(2000+c++);
            bib.adaugaUtilizator(new UtilizatorBasic(id,nm[i%30],pren[(i+5)%30],pren[(i+5)%30]+"@gmail.com","pass"+id,6,2024,(i%12)+1));
        }
        for (int i=0;i<80;i++) {
            string id="PRE-"+std::to_string(3000+c++);
            bib.adaugaUtilizator(new UtilizatorPremium(id,nm[(i+10)%30],pren[(i+15)%30],pren[(i+15)%30]+".premium@gmail.com","pass"+id,24,2023,(i%12)+1));
        }
    }
};

#endif // DATA_SEEDER_H