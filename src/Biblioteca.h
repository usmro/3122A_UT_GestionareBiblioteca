#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <iostream>
#include <vector>
#include <string>
#include "Carte.h"
#include "Utilizator.h"

using std::vector;
using std::string;
using std::cout;

class Biblioteca 
{
private:
    string nume;
    vector<Carte*> inventarCarti;
    vector<Utilizator*> listaUtilizatori;
    double totalIncasari; 

public:

    Biblioteca(string _nume) 
    {
        nume = _nume;
        totalIncasari = 0.0;//initializez incasarea cu 0
    }

    ~Biblioteca() 
    {
        for (auto carte : inventarCarti) 
        {
            delete carte;
        }
        for (auto utilizator : listaUtilizatori) 
        {
            delete utilizator;
        }
    }

    string getNume() const 
    { 
        return nume; 
    }
    
    void setNume(string _nume) 
    { 
        nume = _nume; 
    }
    
    double getTotalIncasari() const 
    { 
        return totalIncasari; 
    }

    void adaugaCarte(Carte* c) 
    {
        inventarCarti.push_back(c);
        cout << "[Staff] Cartea '" << c->getTitlu() << "' a fost adaugata in inventar.\n";
    }

    void afiseazaInventar() const 
    {
        cout << "\n=== INVENTAR BIBLIOTECA: " << nume << " ===\n";
        for (const auto& carte : inventarCarti) 
        {
            carte->afisareDetalii(); 
        }
    }

    void adaugaUtilizator(Utilizator* u) 
    {
        listaUtilizatori.push_back(u);
        cout << "[Staff] Utilizatorul " << u->getNume() << " " << u->getPrenume() << " a fost inregistrat.\n";
    }

    void afiseazaUtilizatori() const 
    {
        cout << "\n=== UTILIZATORI INREGISTRATI ===\n";
        for (const auto& u : listaUtilizatori) 
        {
            u->afisareProfil();
        }
    }

    void imprumutaCarte(Utilizator* u, Carte* c) 
    {
        cout << "[Sistem] " << u->getNume() << " a imprumutat cartea '" << c->getTitlu() << "'.\n";
        cout << "   -> Trebuie returnata in maxim " << c->getTimpImprumut() << " zile.\n";
    }

    void returneazaCarte(Utilizator* u, Carte* c, int zileIntarziere) 
    {
        cout << "[Sistem] " << u->getNume() << " a returnat cartea '" << c->getTitlu() << "'.\n";
        if (zileIntarziere > 0) 
        {
            double taxaBruta = zileIntarziere * c->getTaxaIntarziere();//calculez taaxa in functie de tipul cartii
            double taxaFinala = u->aplicaDiscountTaxe(taxaBruta);//calculez discount in functie de tipul utilizatorului
            u->adaugaTaxa(taxaFinala);
            cout << "   -> ATENTIE: Intarziere " << zileIntarziere << " zile! Taxa aplicata (dupa discount): " << taxaFinala << " RON.\n";
        }
    }

    void incaseazaTaxa(Utilizator* u, double suma) 
    {
        if (suma > 0) 
        {
            u->platesteTaxa(suma);//scad din taxa totala a utilizatorului
            totalIncasari += suma;//adaug la incasarile bibliotecii
            cout << "[Casierie] S-au incasat " << suma << " RON de la " << u->getNume() << ".\n";
        }
    }
};

#endif // BIBLIOTECA_H