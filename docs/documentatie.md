Documentatie Proiect: Sistem de Gestionare a unei Biblioteci

Grupa: 3122A
Student: Ursescu Timotei

1. Cerinta Proiectului
Sistem de Gestionare a Bibliotecii 
		Descriere: 
			Implementati un sistem pentru o biblioteca virtuala, cu clase pentru carti, utilizatori si imprumuturi.
		Cerinte obligatorii:
			Clase: Carte (cu atribute: titlu, autor, ISBN), Utilizator (nume, ID, lista imprumuturi), Biblioteca (adaugare/eliminare carti, împrumut/returnare).
			Mostenire: Clase derivate pentru tipuri de carti (ex: CarteFictiune, CarteTehnica).
			Polimorfism: Metode virtuale pentru afisare detalii.
			Encapsulare: Atribute private, getteri/setteri.
			Evenimente logate: imprumut/returnare
			Teste unitare pentru verificarea stocului
			Git: Cel putin 5 commit-uri descriptive, branch "develop".

		Cerinte facultative:
			Sabloane: O clasa generica pentru stocare (ex: vector templatizat).
			Exceptii: Tratare erori (ex: carte indisponibila).
			Interfata consola cu meniu.

2. Clase necesare
Carte
    Parametrii:
        Titlu 
        Autor- aici voi implementa optiunea de autori multiplii(cum este si cazul multor carti tehnice)
        ISBN- trebuie verificat ca fiecare ISBN sa fie diferit de la carte la cartea dar toate exemplarele unei singure carti sa aiba acelasi ISBN
        Editura
        An aparitie
        Coperta- voi folosi o lista predefinita pentru tipul de coperta (Cartonata, Brosata) folosesc enum
        Status- disponibilitatea cartii- enum (Disponibila, Imprumutata, Rezervata, Deteriorata)
        Timp Imprumut- acesta difera in functie de tipul cartii
        Taxa Deteriorare- acesta difera in functie de tipul cartii
        Taxa Intarziere- acesta difera in functie de tipul cartii
    Clase Mostenite(tipul de carte):
        CarteTehnica
            Domeniul
            Nivel Dificultate
            Resurse Digitale (CD-uri, etc.)
        CarteFictiva
            Gen Literar
            Varsta Minima Recomandata
        CarteEducativa
            Materie
            Profil
            Clasa
        CarteCopii
            Varsta Recomandata
        MaterialeReferinta
            Tip (Dictionar, Atlas, Enciclopedie)
    Metode:
        Constructori
        Getteri si Setteri
        Metode virtuale

Utilizator
    Parametrii:
        Nume
        ID
        Email sau Nr Telefon
        Tip- sunt mai multe tipuri de utilizator, voi implementa 4 tipuri: Basic, Student, Premium, Staff - enum si in functie de tipul de utilizator 
        Imprumuturi- valabil doar pentru Primele 3 tipuri de utilizator
        Taxe acumulate
        Limita de imprumuturi- depinde de tipul utilizatorului
    Clase Mostenite:
        UtilizatorBasic
            Valabilitate Abonament
            Reguli
                Perioade scurte de imprumut (2 saptamani)
                Limita mica de imprumuturi (2 carti)
        UtilizatorStudent
            Valabilitate Abonament
            Facultate
            An Studiu
            NrMatricol
            Reguli
                Discount la taxe (20%)
                Perioade medii de imprumut (4 saptamani)
                Limita medie de imprumuturi (5 carti)
        UtilizatorPremium
            Valabilitate Abonament
            Reguli
                Discount la taxe (40%)
                Perioade lungi de imprumut (6 saptamani)
                Limita mare de imprumuturi (10 carti)
        UtilizatorStaff
            Departament
            Reguli
                Are acces la adaugare, modificare si stergere
                Nu are taxe
                Perioade lungi de imprumut (6 saptamani)
                Limita mare de imprumuturi (10 carti)
    Metode:
        Constructori
        Getteri si Setteri
        Metode virtuale

Biblioteca (Creierul Aplicatiei)
    Parametrii:
        Nume (Numele bibliotecii)
        Inventar Carti- un vector/listă de pointeri către clasa de bază Carte (pentru a putea stoca la un loc cărți tehnice, de ficțiune, etc.)
        Lista Utilizatori- un vector/listă de pointeri către clasa de bază Utilizator
        Total Încasări- (opțional) un double pentru a ține evidența banilor strânși din taxele de întârziere
    Metode:
        Constructori
        Destructori
        Getteri si Setteri
        Metode Gestiune Cărți (Folosite de Staff)
        Metode Gestiune Utilizatori (Folosite de Staff)
        Metode Gestiune Imprumuturi