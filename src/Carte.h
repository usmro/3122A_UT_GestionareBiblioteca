#ifndef CARTE_H
#define CARTE_H

#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;
using std::cout;

enum class TipCoperta { CARTONATA, BROSATA };
enum class StatusCarte { DISPONIBILA, IMPRUMUTATA, REZERVATA, DETERIORATA };

class Carte 
{
protected:
    string titlu;
    vector<string> autori;
    string isbn;
    string editura;
    int anAparitie;
    TipCoperta coperta;
    StatusCarte status;

public:
    Carte(string t, string autorUnic, string i, string ed, int an, TipCoperta c) 
    {
        titlu = t;
        autori.push_back(autorUnic);
        isbn = i;
        editura = ed;
        anAparitie = an;
        coperta = c;
        status = StatusCarte::DISPONIBILA;
    }

    Carte(string t, vector<string> listaAutori, string i, string ed, int an, TipCoperta c) 
    {
        titlu = t;
        autori = listaAutori;
        isbn = i;
        editura = ed;
        anAparitie = an;
        coperta = c;
        status = StatusCarte::DISPONIBILA;
    }

    virtual ~Carte() = default;

    string getTitlu() const 
    { 
        return titlu; 
    }

    vector<string> getAutori() const 
    { 
        return autori; 
    }

    string getIsbn() const 
    { 
        return isbn; 
    }

    string getEditura() const 
    { 
        return editura;
    }

    int getAnAparitie() const 
    { 
        return anAparitie; 
    }

    TipCoperta getCoperta() const 
    { 
        return coperta; 
    }

    StatusCarte getStatus() const 
    { 
        return status; 
    }

    void setStatus(StatusCarte statusNou) 
    { 
        status = statusNou; 
    }

    virtual void afisareDetalii() const 
    {
        cout << "-----------------------------------\n";
        cout << "Titlu: " << titlu << " (" << anAparitie << ")\n";
        cout << "ISBN: " << isbn << " | Editura: " << editura << "\n";
        cout << "Autor(i): ";
        for (const auto& autor : autori) {
            cout << autor << "; ";
        }
        cout << "\nStatus: ";
        switch (status) {
            case StatusCarte::DISPONIBILA: cout << "Disponibila"; break;
            case StatusCarte::IMPRUMUTATA: cout << "Imprumutata"; break;
            case StatusCarte::REZERVATA: cout << "Rezervata"; break;
            case StatusCarte::DETERIORATA: cout << "Deteriorata"; break;
        }
        cout << "\n";
    }

    virtual int getTimpImprumut() const = 0;
    virtual double getTaxaDeteriorare() const = 0;
    virtual double getTaxaIntarziere() const = 0;
};

#endif // CARTE_H