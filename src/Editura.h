#ifndef EDITURA_H
#define EDITURA_H

#include <string>
#include <iostream>
#include "IAfisabil.h"

using std::string;
using std::cout;

// Editura ca entitate separata - nu mai e un simplu string in Carte.
// Permite cautare/filtrare dupa editura si evita duplicarea datelor.
class Editura : public IAfisabil
{
private:
    int    id;
    string nume;
    string tara;
    string oras;
    string website;
    int    anInfiintare;

    static int contor;

public:
    Editura(string _nume, string _tara, string _oras,
            int _anInf = 0, string _web = "")
        : id(++contor),
          nume(_nume), tara(_tara), oras(_oras),
          website(_web), anInfiintare(_anInf)
    {}

    int    getId()             const { return id; }
    string getNume()           const { return nume; }
    string getTara()           const { return tara; }
    string getOras()           const { return oras; }
    string getWebsite()        const { return website; }
    int    getAnInfiintare()   const { return anInfiintare; }

    void setWebsite(string w)  { website = w; }

    void afisareDetalii() const override
    {
        cout << "[Editura #" << id << "] " << nume
             << " | " << oras << ", " << tara;
        if (anInfiintare > 0) cout << " (inf. " << anInfiintare << ")";
        if (!website.empty()) cout << " | " << website;
        cout << "\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const Editura& e)
    {
        os << e.nume;
        return os;
    }
};

int Editura::contor = 0;

#endif // EDITURA_H