#ifndef COLECTIE_H
#define COLECTIE_H

#include <vector>
#include <stdexcept>
#include <algorithm>

// Sablon generic (template) pentru stocare omogena de pointeri.
// Inlocuieste vector<Carte*> si vector<Utilizator*> brute din Biblioteca.
// Demonstreaza cerinta facultativa: sabloane (clase generice).
template <typename T>
class Colectie
{
private:
    std::vector<T*> elemente;

public:
    Colectie() = default;

    ~Colectie()
    {
        for (auto* el : elemente)
            delete el;
        elemente.clear();
    }

    // Interzice copierea - evita double delete
    Colectie(const Colectie&) = delete;
    Colectie& operator=(const Colectie&) = delete;

    void adauga(T* element)
    {
        if (!element)
            throw std::invalid_argument("Nu se poate adauga un element null.");
        elemente.push_back(element);
    }

    bool elimina(T* element)
    {
        auto it = std::find(elemente.begin(), elemente.end(), element);
        if (it != elemente.end())
        {
            delete *it;
            elemente.erase(it);
            return true;
        }
        return false;
    }

    T* get(int index) const
    {
        if (index < 0 || index >= (int)elemente.size())
            throw std::out_of_range("Index in afara colectiei.");
        return elemente[index];
    }

    int dimensiune() const
    {
        return (int)elemente.size();
    }

    bool esteGoala() const
    {
        return elemente.empty();
    }

    // Permite iterare cu range-based for
    typename std::vector<T*>::const_iterator begin() const { return elemente.begin(); }
    typename std::vector<T*>::const_iterator end()   const { return elemente.end();   }
};

#endif // COLECTIE_H