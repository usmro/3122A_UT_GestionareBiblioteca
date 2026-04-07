#ifndef AUTOR_H
#define AUTOR_H

#include <string>
#include <iostream>
#include "IAfisabil.h"

using std::string;
using std::cout;

// Autor ca entitate separata - nu mai e un simplu string in Carte.
// IndexAutori din Biblioteca va asigura unicitatea: acelasi autor
// nu se inregistreaza de doua ori, indiferent de cate carti are.
class Autor : public IAfisabil
{
private:
    int         id;
    string      nume;
    string      prenume;
    string      nationalitate;
    int         anNastere;
    bool        esteViu;
    string      bio;        // scurta descriere
    string      linkProfil; // link extern (Wikipedia, Goodreads etc.)

    static int contor; // genereaza ID-uri automat

public:
    Autor(string _nume, string _prenume, string _nationalitate,
          int _anNastere, bool _esteViu,
          string _bio = "", string _link = "")
        : id(++contor),
          nume(_nume), prenume(_prenume),
          nationalitate(_nationalitate),
          anNastere(_anNastere), esteViu(_esteViu),
          bio(_bio), linkProfil(_link)
    {}

    // --- Getteri ---
    int    getId()            const { return id; }
    string getNume()          const { return nume; }
    string getPrenume()       const { return prenume; }
    string getNumeComplet()   const { return prenume + " " + nume; }
    string getNationalitate() const { return nationalitate; }
    int    getAnNastere()     const { return anNastere; }
    bool   getEsteViu()       const { return esteViu; }
    string getBio()           const { return bio; }
    string getLinkProfil()    const { return linkProfil; }

    // --- Setteri ---
    void setEsteViu(bool v)       { esteViu = v; }
    void setBio(string _bio)      { bio = _bio; }
    void setLink(string _link)    { linkProfil = _link; }

    // --- IAfisabil ---
    void afisareDetalii() const override
    {
        cout << "[Autor #" << id << "] "
             << getNumeComplet()
             << " (" << nationalitate << ", n." << anNastere << ")"
             << (esteViu ? " - activ" : " - decedat") << "\n";
        if (!bio.empty())       cout << "   Bio: "  << bio  << "\n";
        if (!linkProfil.empty()) cout << "   Link: " << linkProfil << "\n";
    }

    // --- Operator << pentru afisare rapida ---
    friend std::ostream& operator<<(std::ostream& os, const Autor& a)
    {
        os << a.getNumeComplet();
        return os;
    }
};

// Definit in Autor.cpp (sau inline pentru simplitate in proiect mic)
int Autor::contor = 0;

#endif // AUTOR_H