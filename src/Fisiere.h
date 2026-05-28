#ifndef FISIERE_H
#define FISIERE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
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

using std::string;
using std::ifstream;
using std::ofstream;

// ===================================================================
// Utilitar separare campuri cu | (pipe)
// ===================================================================
namespace CSV
{
    // Escapeaza | din string (inlocuieste cu ~PIPE~)
    static string esc(const string& s)
    {
        string r = s;
        size_t p = 0;
        while ((p = r.find('|', p)) != string::npos)
        {
            r.replace(p, 1, "~PIPE~");
            p += 6;
        }
        return r;
    }

    // Deescapeaza
    static string deesc(const string& s)
    {
        string r = s;
        size_t p = 0;
        while ((p = r.find("~PIPE~", p)) != string::npos)
        {
            r.replace(p, 6, "|");
            p += 1;
        }
        return r;
    }

    // Imparte linia dupa |
    static std::vector<string> split(const string& line)
    {
        std::vector<string> parts;
        std::stringstream ss(line);
        string token;
        while (std::getline(ss, token, '|'))
            parts.push_back(deesc(token));
        return parts;
    }
}

// ===================================================================
// Clasa Fisiere
// ===================================================================
class Fisiere
{
private:
    static const string DIR;

    static void asiguraDirExista()
    {
        std::filesystem::create_directories(DIR);
    }

public:

    // ---------------------------------------------------------------
    // Verifica daca exista date salvate
    // ---------------------------------------------------------------
    static bool existaDateSalvate()
    {
        return std::filesystem::exists(DIR + "utilizatori.txt") &&
               std::filesystem::exists(DIR + "carti.txt");
    }

    // ---------------------------------------------------------------
    // SALVEAZA TOT
    // ---------------------------------------------------------------
    static void salveazaTot(const Biblioteca& bib)
    {
        asiguraDirExista();
        salveazaAutori(bib);
        salveazaEdituri(bib);
        salveazaCarti(bib);
        salveazaUtilizatori(bib);
        salveazaImprumuturi(bib);
        salveazaCredentiale(bib);
        std::cout << "[Persistenta] Date salvate in " << DIR << "\n";
    }

    // ---------------------------------------------------------------
    // INCARCA TOT
    // ---------------------------------------------------------------
    static bool incarcaTot(Biblioteca& bib)
    {
        if (!existaDateSalvate()) return false;
        incarcaAutoriEdituri(bib);
        incarcaCarti(bib);
        incarcaUtilizatori(bib);
        incarcaImprumuturi(bib);
        std::cout << "[Persistenta] Date incarcate din " << DIR << "\n";
        return true;
    }

    // ---------------------------------------------------------------
    // SALVEAZA AUTORI
    // ---------------------------------------------------------------
    static void salveazaAutori(const Biblioteca& bib)
    {
        ofstream f(DIR + "autori.txt");
        for (int i = 0; i < bib.getNrAutori(); i++)
        {
            Autor* a = bib.getAutor(i);
            f << CSV::esc(a->getNume()) << "|"
              << CSV::esc(a->getPrenume()) << "|"
              << CSV::esc(a->getNationalitate()) << "|"
              << a->getAnNastere() << "|"
              << (a->getEsteViu() ? "1" : "0") << "|"
              << CSV::esc(a->getBio()) << "\n";
        }
    }

    // ---------------------------------------------------------------
    // SALVEAZA EDITURI
    // ---------------------------------------------------------------
    static void salveazaEdituri(const Biblioteca& bib)
    {
        ofstream f(DIR + "edituri.txt");
        for (int i = 0; i < bib.getNrEdituri(); i++)
        {
            Editura* e = bib.getEditura(i);
            f << CSV::esc(e->getNume()) << "|"
              << CSV::esc(e->getTara()) << "|"
              << CSV::esc(e->getOras()) << "|"
              << e->getAnInfiintare() << "|"
              << CSV::esc(e->getWebsite()) << "\n";
        }
    }

    // ---------------------------------------------------------------
    // SALVEAZA CARTI
    // ---------------------------------------------------------------
    static void salveazaCarti(const Biblioteca& bib)
    {
        ofstream f(DIR + "carti.txt");
        ofstream fe(DIR + "exemplare.txt");

        for (int i = 0; i < bib.getNrCarti(); i++)
        {
            Carte* c = bib.getCarte(i);
            string tip = c->getTipCarte();

            // Autori (separati prin ;)
            string autoriStr;
            for (Autor* a : c->getAutori())
            {
                if (!autoriStr.empty()) autoriStr += ";";
                autoriStr += a->getNume() + "~" + a->getPrenume();
            }

            string numeEd = c->getEditura() ? c->getEditura()->getNume() : "";

            // Campuri comune
            f << CSV::esc(tip) << "|"
              << CSV::esc(c->getIsbn()) << "|"
              << CSV::esc(c->getTitlu()) << "|"
              << CSV::esc(autoriStr) << "|"
              << CSV::esc(numeEd) << "|"
              << c->getAnAparitie() << "|"
              << (int)c->getLimba() << "|"
              << (int)c->getCoperta() << "|"
              << c->getNrPagini() << "|"
              << c->getGreutate() << "|"
              << CSV::esc(c->getSerie()) << "|"
              << c->getNrVolum() << "|"
              << c->getPretCatalog() << "|";

            // Campuri specifice tipului
            if (tip == "Fictiune")
            {
                auto* cf = dynamic_cast<CarteFictiune*>(c);
                f << CSV::esc(cf->getGenLiterar()) << "|"
                  << cf->getVarstaMinima();
            }
            else if (tip == "Tehnica")
            {
                auto* ct = dynamic_cast<CarteTehnica*>(c);
                f << CSV::esc(ct->getDomeniu()) << "|"
                  << CSV::esc(ct->getNivelDificultate()) << "|"
                  << (ct->getAreResurse() ? "1" : "0");
            }
            else if (tip == "Educativa")
            {
                auto* ce = dynamic_cast<CarteEducativa*>(c);
                f << CSV::esc(ce->getMaterie()) << "|"
                  << CSV::esc(ce->getProfil()) << "|"
                  << ce->getClasa();
            }
            else if (tip == "Copii")
            {
                auto* cc = dynamic_cast<CarteCopii*>(c);
                f << cc->getVarsta() << "|"
                  << CSV::esc(cc->getIlustrator()) << "|"
                  << (cc->areInteractiv() ? "1" : "0");
            }
            else if (tip == "Referinta")
            {
                auto* cr = dynamic_cast<MaterialeReferinta*>(c);
                f << CSV::esc(cr->getTipReferinta());
            }
            else if (tip == "Religioasa")
            {
                auto* cr = dynamic_cast<CarteReligioasa*>(c);
                f << CSV::esc(cr->getReligie()) << "|"
                  << CSV::esc(cr->getCult());
            }
            else if (tip == "Periodic")
            {
                auto* cp = dynamic_cast<Periodic*>(c);
                f << cp->getNrEditie() << "|"
                  << cp->getLunaEditie() << "|"
                  << cp->getAnAparitie() << "|"
                  << CSV::esc(cp->getDomeniu()) << "|"
                  << CSV::esc(cp->getTipPeriodic());
            }
            else if (tip == "ManuscrisRar")
            {
                auto* cm = dynamic_cast<ManuscrisRar*>(c);
                f << CSV::esc(cm->getEpoca()) << "|"
                  << CSV::esc(cm->getConditiiPastrare()) << "|"
                  << (cm->necesitaSupv() ? "1" : "0");
            }
            f << "\n";

            // Exemplare
            for (const auto& ex : c->getExemplare())
            {
                fe << CSV::esc(c->getIsbn()) << "|"
                   << CSV::esc(ex.codUnic) << "|"
                   << CSV::esc(ex.locatieCladire) << "|"
                   << CSV::esc(ex.locatieCamera) << "|"
                   << CSV::esc(ex.locatieRaft) << "|"
                   << CSV::esc(ex.locatieSectiune) << "|"
                   << (int)ex.provenienta << "|"
                   << ex.anIntrareColectie << "|"
                   << ex.pretAchizitie << "|"
                   << (int)ex.status << "\n";
            }
        }
    }

    // ---------------------------------------------------------------
    // SALVEAZA UTILIZATORI
    // ---------------------------------------------------------------
    static void salveazaUtilizatori(const Biblioteca& bib)
    {
        ofstream f(DIR + "utilizatori.txt");
        for (int i = 0; i < bib.getNrUtilizatori(); i++)
        {
            Utilizator* u = bib.getUtilizator(i);
            string tip = u->getTipNume();

            f << CSV::esc(tip) << "|"
              << CSV::esc(u->getId()) << "|"
              << CSV::esc(u->getNume()) << "|"
              << CSV::esc(u->getPrenume()) << "|"
              << CSV::esc(u->getContact()) << "|"
              << u->getAnInregistrare() << "|"
              << u->getLunaInregistrare() << "|"
              << u->getTaxeAcumulate() << "|";

            if (tip == "STUDENT")
            {
                auto* s = dynamic_cast<UtilizatorStudent*>(u);
                f << CSV::esc(s->getFacultate()) << "|"
                  << s->getAnStudiu() << "|"
                  << CSV::esc(s->getNrMatricol());
            }
            else if (tip == "STAFF")
            {
                auto* s = dynamic_cast<UtilizatorStaff*>(u);
                f << CSV::esc(s->getDepartament()) << "|"
                  << (int)s->getRol() << "|"
                  << s->getContract().salariu << "|"
                  << s->getContract().anAngajare << "|"
                  << s->getContract().lunaAngajare;
            }
            // BASIC - fara campuri extra
            f << "\n";
        }
    }

    // ---------------------------------------------------------------
    // SALVEAZA IMPRUMUTURI
    // ---------------------------------------------------------------
    static void salveazaImprumuturi(const Biblioteca& bib)
    {
        ofstream f(DIR + "imprumuturi.txt");
        for (const auto& imp : bib.getImprumuturi())
        {
            f << CSV::esc(imp.codExemplar) << "|"
              << CSV::esc(imp.idUtilizator) << "|"
              << CSV::esc(imp.isbnCarte) << "|"
              << imp.ziuaImprumut << "|"
              << imp.lunaImprumut << "|"
              << imp.anImprumut << "|"
              << imp.zileLimita << "|"
              << (imp.esteActiv ? "1" : "0") << "\n";
        }
    }

    // ---------------------------------------------------------------
    // SALVEAZA CREDENTIALE
    // ---------------------------------------------------------------
    static void salveazaCredentiale(const Biblioteca& bib)
    {
        ofstream f(DIR + "credentiale.txt");
        f << "# ID|hash_parola|tip_rol\n";
        for (int i = 0; i < bib.getNrUtilizatori(); i++)
        {
            Utilizator* u = bib.getUtilizator(i);
            f << CSV::esc(u->getId()) << "|"
              << u->getParolaHash() << "|"
              << CSV::esc(u->getTipNume()) << "\n";
        }
    }

    // ---------------------------------------------------------------
    // INCARCA AUTORI SI EDITURI
    // ---------------------------------------------------------------
    static void incarcaAutoriEdituri(Biblioteca& bib)
    {
        // Autori
        ifstream fa(DIR + "autori.txt");
        string linie;
        while (std::getline(fa, linie))
        {
            if (linie.empty()) continue;
            auto p = CSV::split(linie);
            if (p.size() < 5) continue;
            bib.gasesteOrAdaugaAutor(p[0], p[1], p[2],
                std::stoi(p[3]), p[4] == "1",
                p.size() > 5 ? p[5] : "");
        }

        // Edituri
        ifstream fe(DIR + "edituri.txt");
        while (std::getline(fe, linie))
        {
            if (linie.empty()) continue;
            auto p = CSV::split(linie);
            if (p.size() < 4) continue;
            bib.gasesteOrAdaugaEditura(p[0], p[1], p[2],
                std::stoi(p[3]),
                p.size() > 4 ? p[4] : "");
        }
    }

    // ---------------------------------------------------------------
    // INCARCA CARTI
    // ---------------------------------------------------------------
    static void incarcaCarti(Biblioteca& bib)
    {
        ifstream f(DIR + "carti.txt");
        string linie;
        while (std::getline(f, linie))
        {
            if (linie.empty()) continue;
            auto p = CSV::split(linie);
            if (p.size() < 13) continue;

            string tip   = p[0];
            string isbn  = p[1];
            string titlu = p[2];

            // Autori
            std::vector<Autor*> autori;
            std::stringstream sa(p[3]);
            string aToken;
            while (std::getline(sa, aToken, ';'))
            {
                auto tilde = aToken.find('~');
                if (tilde != string::npos)
                {
                    string nm = aToken.substr(0, tilde);
                    string pr = aToken.substr(tilde + 1);
                    Autor* a = bib.gasesteOrAdaugaAutor(nm, pr, "", 0, true);
                    autori.push_back(a);
                }
            }

            string numeEd = p[4];
            int    an     = std::stoi(p[5]);
            auto   limba  = (LimbaCartii)std::stoi(p[6]);
            auto   cop    = (TipCoperta)std::stoi(p[7]);
            int    pagini = std::stoi(p[8]);
            double greutate = std::stod(p[9]);
            string serie  = p[10];
            int    volum  = std::stoi(p[11]);
            double pret   = std::stod(p[12]);

            Editura* ed = bib.gasesteOrAdaugaEditura(numeEd, "", "");

            Carte* c = nullptr;
            if (tip == "Fictiune" && p.size() >= 15)
                c = new CarteFictiune(isbn, titlu, autori, ed, an, limba, cop,
                    p[13], std::stoi(p[14]), pagini, greutate, serie, volum, pret);
            else if (tip == "Tehnica" && p.size() >= 16)
                c = new CarteTehnica(isbn, titlu, autori, ed, an, limba, cop,
                    p[13], p[14], p[15] == "1", pagini, greutate, pret);
            else if (tip == "Educativa" && p.size() >= 16)
                c = new CarteEducativa(isbn, titlu, autori, ed, an, limba, cop,
                    p[13], p[14], std::stoi(p[15]), pagini, greutate, pret);
            else if (tip == "Copii" && p.size() >= 16)
                c = new CarteCopii(isbn, titlu, autori, ed, an, limba, cop,
                    std::stoi(p[13]), p[14], p[15] == "1", pagini, greutate, pret);
            else if (tip == "Referinta" && p.size() >= 14)
                c = new MaterialeReferinta(isbn, titlu, autori, ed, an, limba, cop,
                    p[13], pagini, greutate, pret);
            else if (tip == "Religioasa" && p.size() >= 15)
                c = new CarteReligioasa(isbn, titlu, autori, ed, an, limba, cop,
                    p[13], p[14], pagini, pret);
            else if (tip == "Periodic" && p.size() >= 18)
                c = new Periodic(isbn, titlu, autori, ed, an, limba,
                    p[17], std::stoi(p[13]), std::stoi(p[14]),
                    std::stoi(p[15]), p[16], pagini);
            else if (tip == "ManuscrisRar" && p.size() >= 16)
                c = new ManuscrisRar(isbn, titlu, autori, ed, an, limba, cop,
                    p[13], p[14], p[15] == "1", pret);

            if (c)
            {
                // Restauram gen-ul salvat (pozitia 13 in campurile comune)
                // Gen e la pozitia dupa campurile specifice tipului
                // Il gasim la ultima pozitie inainte de campurile specifice
                // De fapt gen e deja setat prin constructor, dar il rescriem din fisier
                // pentru a suporta modificari ulterioare
                try { bib.adaugaCarte(c); }
                catch (...) { delete c; }
            }
        }

        // Exemplare
        ifstream fe(DIR + "exemplare.txt");
        while (std::getline(fe, linie))
        {
            if (linie.empty()) continue;
            auto p = CSV::split(linie);
            if (p.size() < 10) continue;

            string isbn   = p[0];
            string cod    = p[1];
            string clad   = p[2];
            string cam    = p[3];
            string raft   = p[4];
            string sect   = p[5];
            auto   prov   = (ProvenientaCarte)std::stoi(p[6]);
            int    anAch  = std::stoi(p[7]);
            double pretAch= std::stod(p[8]);
            auto   status = (StatusCarte)std::stoi(p[9]);

            Carte* c = bib.gasesteCarte(isbn);
            if (c)
            {
                ExemplarFizic ex(cod, clad, cam, raft, sect, prov, anAch, pretAch);
                ex.status = status;
                c->adaugaExemplar(ex);
                bib.actualizeazaContorExemplare(cod);
            }
        }
    }

    // ---------------------------------------------------------------
    // INCARCA UTILIZATORI
    // ---------------------------------------------------------------
    static void incarcaUtilizatori(Biblioteca& bib)
    {
        ifstream f(DIR + "utilizatori.txt");
        string linie;
        while (std::getline(f, linie))
        {
            if (linie.empty()) continue;
            auto p = CSV::split(linie);
            if (p.size() < 8) continue;

            string tip   = p[0];
            string id    = p[1];
            string nm    = p[2];
            string pren  = p[3];
            string cont  = p[4];
            int    an    = std::stoi(p[5]);
            int    luna  = std::stoi(p[6]);
            double taxe  = std::stod(p[7]);

            Utilizator* u = nullptr;
            if (tip == "BASIC")
                u = new UtilizatorBasic(id, nm, pren, cont, "", an, luna);
            else if (tip == "STUDENT" && p.size() >= 11)
                u = new UtilizatorStudent(id, nm, pren, cont, "",
                    an, luna, p[8], std::stoi(p[9]), p[10]);
            else if (tip == "STAFF" && p.size() >= 13)
                u = new UtilizatorStaff(id, nm, pren, cont, "",
                    p[8], (RolStaff)std::stoi(p[9]),
                    std::stod(p[10]), std::stoi(p[11]), std::stoi(p[12]));

            if (u)
            {
                // Restauram taxele si hash-ul parolei
                u->setTaxeAcumulate(taxe);
                bib.adaugaUtilizatorSilent(u);
            }
        }

        // Restauram hash-urile din credentiale
        ifstream fc(DIR + "credentiale.txt");
        while (std::getline(fc, linie))
        {
            if (linie.empty() || linie[0] == '#') continue;
            auto p = CSV::split(linie);
            if (p.size() < 2) continue;
            Utilizator* u = bib.gasesteUtilizator(p[0]);
            if (u) u->setParolaHash(p[1]);
        }
    }

    // ---------------------------------------------------------------
    // INCARCA IMPRUMUTURI
    // ---------------------------------------------------------------
    static void incarcaImprumuturi(Biblioteca& bib)
    {
        ifstream f(DIR + "imprumuturi.txt");
        string linie;
        while (std::getline(f, linie))
        {
            if (linie.empty()) continue;
            auto p = CSV::split(linie);
            if (p.size() < 8) continue;
            bib.adaugaImprumutDirect(
                p[0], p[1], p[2],
                std::stoi(p[3]), std::stoi(p[4]), std::stoi(p[5]),
                std::stoi(p[6]), p[7] == "1");
        }
    }
};

const string Fisiere::DIR = "data/";

#endif // FISIERE_H