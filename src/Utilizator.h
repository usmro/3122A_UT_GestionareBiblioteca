#ifndef UTILIZATOR_H
#define UTILIZATOR_H

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "IAfisabil.h"

using std::string;
using std::vector;
using std::cout;

// -----------------------------------------------------------------------
// Enum-uri
// -----------------------------------------------------------------------
enum class TipUtilizator { BASIC, STUDENT, STAFF };

// -----------------------------------------------------------------------
// Eveniment din istoria utilizatorului
// -----------------------------------------------------------------------
struct EvenimentIstoric
{
    int    an;
    int    luna;
    string descriere;

    EvenimentIstoric(int _an, int _luna, string _desc)
        : an(_an), luna(_luna), descriere(_desc) {}
};

// -----------------------------------------------------------------------
// Utilitar hash pentru parole
// -----------------------------------------------------------------------
namespace Securitate
{
    inline string hashParola(const string& parola)
    {
        std::size_t h = std::hash<string>{}(parola);
        std::ostringstream oss;
        oss << std::hex << std::setw(16) << std::setfill('0') << h;
        return oss.str();
    }

    inline bool verificaParola(const string& parolaIntrodusa,
                                const string& hashStocata)
    {
        return hashParola(parolaIntrodusa) == hashStocata;
    }
}

// -----------------------------------------------------------------------
// Clasa de baza: Utilizator
// -----------------------------------------------------------------------
class Utilizator : public IAfisabil
{
protected:
    string         id;
    string         nume;
    string         prenume;
    string         contact;
    TipUtilizator  tip;
    double         taxeAcumulate;
    string         parolaHash;
    int            anInregistrare;
    int            lunaInregistrare;

    vector<EvenimentIstoric> istoric;
    vector<string>           imprumututiCurente;

public:
    Utilizator(string _id, string _nume, string _prenume,
               string _contact, TipUtilizator _tip,
               string parola = "",
               int an = 2024, int luna = 1)
        : id(_id), nume(_nume), prenume(_prenume),
          contact(_contact), tip(_tip),
          taxeAcumulate(0.0),
          parolaHash(parola.empty() ? "" : Securitate::hashParola(parola)),
          anInregistrare(an), lunaInregistrare(luna)
    {}

    virtual ~Utilizator() = default;

    // Getteri
    string        getId()               const { return id; }
    string        getNume()             const { return nume; }
    string        getPrenume()          const { return prenume; }
    string        getNumeComplet()      const { return prenume + " " + nume; }
    string        getContact()          const { return contact; }
    TipUtilizator getTip()              const { return tip; }
    double        getTaxeAcumulate()    const { return taxeAcumulate; }
    string getParolaHash()               const { return parolaHash; }
void   setParolaHash(const string& h)      { parolaHash = h; }
void   setTaxeAcumulate(double t)          { taxeAcumulate = t; }
    int           getNrImprumuturi()    const { return (int)imprumututiCurente.size(); }
    int           getAnInregistrare()   const { return anInregistrare; }
    int           getLunaInregistrare() const { return lunaInregistrare; }

    const vector<EvenimentIstoric>& getIstoric() const { return istoric; }

    // Setteri
    void setContact(const string& c) { contact = c; }

    void setParola(const string& parolaNoua)
    {
        parolaHash = Securitate::hashParola(parolaNoua);
    }

    bool verificaParola(const string& parola) const
    {
        return Securitate::verificaParola(parola, parolaHash);
    }

    // Taxe
    void adaugaTaxa(double suma)
    {
        if (suma < 0) return;
        taxeAcumulate += suma;
    }

    void platesteTaxa(double suma)
    {
        taxeAcumulate -= suma;
        if (taxeAcumulate < 0) taxeAcumulate = 0;
    }

    // Imprumuturi
    void adaugaImprumut(const string& codExemplar)
    {
        imprumututiCurente.push_back(codExemplar);
    }

    void eliminaImprumut(const string& codExemplar)
    {
        auto it = std::find(imprumututiCurente.begin(),
                            imprumututiCurente.end(), codExemplar);
        if (it != imprumututiCurente.end())
            imprumututiCurente.erase(it);
    }

    bool poateImprumuta() const
    {
        return getNrImprumuturi() < getLimitaImprumuturi();
    }

    // Istoric
    void adaugaEveniment(int an, int luna, const string& desc)
    {
        istoric.emplace_back(an, luna, desc);
        std::sort(istoric.begin(), istoric.end(),
            [](const EvenimentIstoric& a, const EvenimentIstoric& b)
            {
                if (a.an != b.an) return a.an < b.an;
                return a.luna < b.luna;
            });
    }

    void afisareIstoric() const
    {
        cout << "  Istoric " << getNumeComplet() << ":\n";
        for (const auto& ev : istoric)
            cout << "    [" << ev.luna << "/" << ev.an << "] "
                 << ev.descriere << "\n";
    }

    // Virtuale pure
    virtual int    getLimitaImprumuturi()          const = 0;
    virtual double aplicaDiscountTaxe(double taxa) const = 0;
    virtual bool   areDreptDeAdmin()               const { return false; }
    virtual string getTipNume()                    const = 0;

    // IAfisabil
    virtual void afisareDetalii() const override
    {
        cout << "[" << getTipNume() << "] "
             << getNumeComplet()
             << " | ID: " << id
             << " | Contact: " << contact
             << " | Taxe: " << taxeAcumulate << " RON"
             << " | Imprumuturi: " << getNrImprumuturi()
             << "/" << getLimitaImprumuturi()
             << " | Inregistrat: " << lunaInregistrare
             << "/" << anInregistrare << "\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const Utilizator& u)
    {
        os << u.getNumeComplet() << " [" << u.id << "]";
        return os;
    }
};

#endif // UTILIZATOR_H