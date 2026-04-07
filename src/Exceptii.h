#ifndef EXCEPTII_H
#define EXCEPTII_H

#include <stdexcept>
#include <string>

// Exceptii custom pentru biblioteca.
// Demonstreaza cerinta facultativa: tratare erori cu clase proprii.

// Carte inexistenta sau indisponibila
class CarteLipsaException : public std::runtime_error
{
public:
    explicit CarteLipsaException(const std::string& titlu)
        : std::runtime_error("Cartea '" + titlu + "' nu este disponibila sau nu exista.") {}
};

// Utilizatorul a atins limita de imprumuturi permise
class LimitaDepastitaException : public std::runtime_error
{
public:
    explicit LimitaDepastitaException(const std::string& numeUser, int limita)
        : std::runtime_error("Utilizatorul '" + numeUser +
                             "' a atins limita de " + std::to_string(limita) +
                             " imprumuturi.") {}
};

// ISBN duplicat la adaugare
class IsbnDuplicatException : public std::runtime_error
{
public:
    explicit IsbnDuplicatException(const std::string& isbn)
        : std::runtime_error("ISBN-ul '" + isbn + "' exista deja in inventar.") {}
};

// Utilizator inexistent
class UtilizatorInexistentException : public std::runtime_error
{
public:
    explicit UtilizatorInexistentException(const std::string& id)
        : std::runtime_error("Utilizatorul cu ID '" + id + "' nu a fost gasit.") {}
};

// Taxa negativa sau invalida
class TaxaInvalidaException : public std::runtime_error
{
public:
    explicit TaxaInvalidaException(double suma)
        : std::runtime_error("Suma '" + std::to_string(suma) + "' este invalida.") {}
};

#endif // EXCEPTII_H