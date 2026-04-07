#ifndef CARTE_EDUCATIVA_H
#define CARTE_EDUCATIVA_H
#include "Carte.h"

class CarteEducativa : public Carte
{
private:
    string materie;
    string profil;
    int    clasa; // 0 = nu se aplica (universitate etc.)

public:
    CarteEducativa(string isbn, string titlu,
                   vector<Autor*> autori, Editura* editura,
                   int an, LimbaCartii limba, TipCoperta coperta,
                   string mat, string prof, int cl,
                   int pagini = 0, double greutate = 0.0,
                   double pretCatalog = 0.0)
        : Carte(isbn, titlu, autori, editura, an, limba, coperta,
                pagini, greutate, "", 0, pretCatalog),
          materie(mat), profil(prof), clasa(cl)
    {}

    string getMaterie() const { return materie; }
    string getProfil()  const { return profil; }
    int    getClasa()   const { return clasa; }

    void afisareDetalii() const override
    {
        Carte::afisareDetalii();
        cout << "  [Educativa] Materie: " << materie
             << " | Profil: " << profil;
        if (clasa > 0) cout << " | Clasa a " << clasa << "-a";
        cout << "\n";
    }

    int    getTimpImprumut()    const override { return 30; }
    double getTaxaDeteriorare() const override { return 40.0; }
    double getTaxaIntarziere()  const override { return 1.5; }
    string getTipCarte()        const override { return "Educativa"; }
};

#endif // CARTE_EDUCATIVA_H