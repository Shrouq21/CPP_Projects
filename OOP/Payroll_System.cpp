#include <vector>
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <map>
using namespace std;

class payable
{
public:
    virtual double GetAmountmoney() const { return -1; }
    virtual ~payable() { cout << "payable destructor\n"; }
};

class Staff_member : public payable
{
protected:
    string name, company;
    int age, hoursworked;

public:
    Staff_member() {}
    Staff_member(string name, string company, int age, int hoursworked)
        : name(name), company(company), age(age), hoursworked(hoursworked) {}

    virtual void set_name(const string& name) { this->name = name; }
    virtual const string get_name() const { return name; }

    virtual void set_company(const string& company) { this->company = company; }
    virtual const string get_company() const { return company; }

    virtual void set_age(const int& age) { this->age = age; }
    virtual const int get_age() const { return age; }

    virtual void set_hoursworked(const int& hoursworked) { this->hoursworked = hoursworked; }
    virtual const int get_hoursworked() const { return hoursworked; }

    virtual string print_instring()
    {
        ostringstream os;
        os << name << " " << company << " " << age << " " << hoursworked;
        return os.str();
    }

    void print_info()
    {
        cout << "Name: " << name
             << "\nAge: " << age
             << "\nCompany: " << company
             << "\n\n";
    }

    virtual ~Staff_member() { cout << "staff_member destructor\n"; }
};

class volunteer : public Staff_member {
private:
    double current_payment;

public:
    volunteer() {}
    volunteer(string name, string company, int age, int hoursworked, double current_payment)
        : Staff_member(name, company, age, hoursworked), current_payment(current_payment) {}

    virtual double GetAmountmoney() const override
    {
        cout << "Volunteer Payment: ";
        return current_payment;
    }

    virtual ~volunteer() { cout << "volunteer destructor\n"; }
};

class employee : public Staff_member {
public:
    employee() {}
    employee(string name, string company, int age, int hoursworked)
        : Staff_member(name, company, age, hoursworked) {}

    virtual ~employee() { cout << "employee destructor\n"; }
};

class salaried_based : public employee {
private:
    double monthly_salary;

public:
    salaried_based() {}
    salaried_based(string name, string company, int age, int hoursworked, int m)
        : employee(name, company, age, hoursworked), monthly_salary(m) {}

    virtual double GetAmountmoney() const override {
        cout << "Salaried Employee: ";
        return monthly_salary;
    }

    virtual ~salaried_based() { cout << "salaried_based destructor\n"; }
};

class hourly_based : public employee {
private:
    double salary_per_hour;

public:
    hourly_based() {}
    hourly_based(string name, string company, int age, int hoursworked, int salary_per_hour)
        : employee(name, company, age, hoursworked), salary_per_hour(salary_per_hour) {}

    virtual double GetAmountmoney() const override
    {
        cout << "Hourly Employee: ";
        return hoursworked * salary_per_hour;
    }

    virtual ~hourly_based() { cout << "hourly_based destructor\n"; }
};

class commission_salaried : public salaried_based {
private:
    double commission_month = 0;
    double commission_rate = 0;

public:
    commission_salaried() {}
    commission_salaried(string name, string company, int age, int hoursworked,
                        int m, double commission_month, double commission_rate)
        : salaried_based(name, company, age, hoursworked, m),
          commission_month(commission_month), commission_rate(commission_rate) {}

    void set_commission_month(const int& commission_month) { this->commission_month = commission_month; }
    void set_commission_rate(const int& commission_rate) { this->commission_rate = commission_rate; }

    const int get_commission_rate() const { return commission_rate; }
    const int get_commission_month() const { return commission_month; }

    double GetAmountmoney() const override
    {
        return salaried_based::GetAmountmoney() + commission_month * commission_rate;
    }

    virtual ~commission_salaried() { cout << "commission_salaried destructor\n"; }
};

class inventory
{
protected:
    string type, name;
    int price;

public:
    inventory() {}
    inventory(string type, int price, string name) : type(type), price(price), name(name) {}

    void set_type(const string& type) { this->type = type; }
    void set_price(const int& p) { this->price = p; }
    const string get_type() const { return type; }
    const int get_price() const { return price; }
    void set_name(const string& name) { this->name = name; }

    virtual ~inventory() { cout << "inventory destructor\n"; }
};

class food : public inventory {
public:
    food() {}
    food(string type, int price, string name) : inventory(type, price, name) {}

    ~food() { cout << "food destructor\n"; }
};

class books : public inventory {
protected:
    string author;
    int n_pgs;

public:
    books() {}
    books(string type, int price, string book_name, string author, int n_pgs)
        : inventory(type, price, book_name), author(author), n_pgs(n_pgs) {}

    void set_author_name(const string& name) { this->author = name; }
    void set_pgs(const int& pgs) { this->n_pgs = pgs; }

    const string get_author() const { return author; }
    const int get_pgs() const { return n_pgs; }

    ~books() { cout << "books destructor\n"; }
};

class invoice : public payable
{
private:
    vector<inventory*> in;

public:
    void add_item(inventory* i)
    {
        in.push_back(i);
    }

    virtual double GetAmountmoney() const override
    {
        double sum = 0;
        for (const auto* item : in)
        {
            sum += item->get_price();
        }
        cout << "Total Item Price: ";
        return sum;
    }

    ~invoice()
    {
        cout << "invoice destructor\n";
        for (auto x : in)
            delete x;
    }
};

class payroll
{
private:
    vector<payable*> p;
    vector<Staff_member*> member;

public:
    void add_payable(payable* pay) { p.push_back(pay); }
    void add_member(Staff_member* m) { member.push_back(m); }

    void pay()
    {
        cout << "payroll::pay\n";
        for (const auto Payable : p)
        {
            cout << Payable->GetAmountmoney() << "\n";
        }
    }

    void info()
    {
        for (const auto m : member)
        {
            m->print_info();
        }
    }

    ~payroll()
    {
        cout << "payroll destructor\n";
        for (auto x : p)
            delete x;
    }
};

class company
{
private:
    payroll Payroll;

public:
    company() {}

    void run()
    {
        Payroll.add_payable(new volunteer("Ahmed Hassan", "Vodafone", 33, 28, 20000));
Payroll.add_member(new volunteer("Ahmed Hassan", "Vodafone", 33, 28, 20000));

Payroll.add_payable(new hourly_based("Yasser Ali", "Etisalat", 40, 19, 100));
Payroll.add_member(new hourly_based("Yasser Ali", "Etisalat", 40, 19, 100));

Payroll.add_payable(new salaried_based("Emad Mostafa", "WE", 29, 40, 5000));
Payroll.add_member(new salaried_based("Emad Mostafa", "WE", 29, 40, 5000));

Payroll.add_payable(new commission_salaried("Alaa Mahmoud", "Huawei", 35, 38, 2000, 1000, 10));
Payroll.add_member(new commission_salaried("Alaa Mahmoud", "Huawei", 35, 38, 2000, 1000, 10));

invoice* in1 = new invoice();
in1->add_item(new books("Science Fiction", 200, "The Time Machine", "H.G. Wells", 100));
in1->add_item(new food("Pasta", 100, "Spaghetti Bolognese"));
Payroll.add_payable(in1);

        Payroll.add_payable(in1);

        Payroll.pay();
        Payroll.info();
    }
};

int main()
{
    company c;
    c.run();
}
