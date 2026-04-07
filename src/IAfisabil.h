#ifndef IAFISABIL_H
#define IAFISABIL_H

// Interfata pura (abstracta) implementata de orice entitate care poate fi afisata.
// Demonstreaza conceptul de interfata din POO - separata de ierarhia de mostenire.
class IAfisabil
{
public:
    virtual void afisareDetalii() const = 0;
    virtual ~IAfisabil() = default;
};

#endif // IAFISABIL_H