#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <memory>

using namespace std;

template <typename type>
class Array
{
private:
    int dimensiune;
    int *ptr;
public:
    Array();
    Array(int Size);
    Array(const Array &array_de_copiat);
    ~Array();
    int Get_Size() const;
    int* Get_Ptr();
    const Array &operator=(const Array &other);
    void Citire();
    ///friend istream& operator>>(istream& Cin, Array<type> &x);
    friend ostream& operator<<(ostream& Cout, Array<type> &x);
};


class Finantare_Minima : public exception
{
public:
    const char *what() const throw()
    {
        return "Sponsorul nu poate oferi mai putin decat finantarea minima!\n";
    }
};


class Finantare_Negativa : public Finantare_Minima
{
public:
      const char *what() const throw()
      {
          return "Finantarea nu poate fi un nr. negativ!\n";
      }
};


class Angajat
{
private:
    char nume[50];
    int an_angajare;
    string departament;
public:
    Angajat();
    Angajat(char Nume[], int An_angajare, string Departament);
    friend ostream& operator<<(ostream& Cout, Angajat x);
    string Get_Department();
    void Schimbare_Departament(string Departament);
    void operator=(const Angajat& angajatul);
    void Calculare_Salariu();
    template <typename Type>
    Type Adaugare_Bonus(Type bonus);
};


class Task
{
private:
    char nume[50];
    Angajat angajat;
    int status;
public:
    Task();
    Task(char Nume[50], Angajat angajatul, char Status[50]);
    void operator=(const Task& taskul);
    friend ostream& operator<<(ostream& Cout, Task x);
    void Schimbare_Status(char Status[]);
};


class Necesitati
{
private:
    char nume[50];
    double pret_bucata;
    int nr_bucati;
public:
    Necesitati();
    Necesitati(char Nume[], double Pret_bucata, int Nr_bucati);
    friend ostream& operator<<(ostream& Cout, Necesitati x);
    void Schimbare_Nr_Bucati(int Nr_bucati);
    void operator=(const Necesitati& necesitatile);
    double Get_Pret_Bucata();
    int Get_Nr_Bucati();
};


class Proiect
{
private:
    vector<Angajat> echipa;
    Necesitati necesitati[50];
    Task taskuri[50];
    Array<int> feedback;
    int size_necesitati;
    int size_taskuri;
public:
    Proiect(Angajat Echipa[], int size_Echipa, Necesitati necesitatile[], int size_necesitatile, Task Taskuri[], int size_Taskuri);
    void Exista_Reprezentant(string Departament);
    double Calculare_Buget_Necesar();
    double Calculare_Feedback_Proiect();
};


class Sponsor
{
protected:
    char nume[50];
    int suma;
protected:
    virtual string Get_Role()
    {
        return "Sponsor";
    }
public:
    Sponsor();
    Sponsor(char Nume[], int Suma);
    virtual void Afisare()
    {
        cout << Get_Role() << ": " << nume << "\n";
    }
};


class Contribuitor : public Sponsor
{
private:
  int badge;
  static int finantare_minima;
public:
    Contribuitor();
    Contribuitor(char Nume[], int Suma);
    string Get_Role() override;
    void Afisare() override;
    static int Oferire_Badge(int Suma)
    {
        if(Suma >= finantare_minima * 2)
            return 1;
        else
            return 0;
    };
    void Verificare1(int Suma);
    void Verificare(int Suma);
};


class Premium : public Sponsor
{
private:
  static int finantare_minima;
  int badge;
  char tematica_proiect[50];
public:
    Premium();
    Premium(char Nume[], int Suma, char Tematica_proiect[]);
    string Get_Role() override;
    void Afisare() override;
    static int Oferire_Badge(int Suma)
    {
        if(Suma >= finantare_minima * 2)
            return 1;
        else
            return 0;
    };
    void Verificare1(int Suma);
    void Verificare(int Suma);
};


class Cauza
{
public:
    virtual string Tip_Beneficiar() = 0;
    virtual void Afisare_Cauza() = 0;
    virtual ~Cauza()
    {

    }
};


class Asociatie : private Cauza
{
private:
    string nume;
    string descriere;
public:
    Asociatie();
    Asociatie(string Nume, string Descriere);
    string Tip_Beneficiar() override;
    void Afisare_Cauza() override;
};


class Pers_Fizica : private Cauza
{
private:
    char nume[50];
    unique_ptr<char[]> p;
public:
    Pers_Fizica();
    Pers_Fizica(char Nume[], char *P);
    string Tip_Beneficiar() override;
    void Afisare_Cauza() override;
};
