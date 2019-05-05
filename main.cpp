#include <iostream>
#include <string.h>

using namespace std;

class nod{
    char val;
    nod *next, *prev;

public:
    nod();
    char get_val();
    nod *get_next();
    nod *get_prev();
    void set_val(char x);
    void set_next(nod *p);
    void set_prev(nod *p);
};

nod::nod(){
    val = 0;
    next = NULL;
    prev = NULL;
}

char nod::get_val(){
    return val;
}

nod* nod::get_next(){
    return next;
}

nod* nod::get_prev(){
    return prev;
}

void nod::set_val(char x){
    val = x;
}

void nod::set_next(nod *p){
    next = p;
}

void nod::set_prev(nod *p){
    prev = p;
}

class intreg{
    nod *pr, *ul;
    int nr_cifre;
    char semn;

public:
    intreg();

    nod *get_pr();
    nod *get_ul()const;
    int get_nr_cif()const;
    char get_semn() const;

    void const set_semn(char s);
    void set_pr(nod *p);
    void set_ul(nod *p);
    void set_nr_cifre(int nr);

    void add_cif(char c);
    intreg operator+(intreg &o2);
    intreg operator-(intreg &o2);
    intreg operator*(intreg &o2);
    bool operator== (intreg &o2);
    intreg operator=(intreg o2);
    intreg max_val_abs(intreg &o2);
    friend istream &operator >>(istream &in, const intreg &x);
    friend ostream &operator <<(ostream &out, const intreg &x);
    int nr_zerouri();
    void afisare();
};

intreg::intreg(){
    nr_cifre = 0;
    semn = 'x';
    pr = NULL;
    ul = NULL;
}
nod* intreg::get_pr(){
    return pr;
}

nod* intreg::get_ul()const{
    return ul;
}

int intreg::get_nr_cif()const{
    return nr_cifre;
}

char intreg::get_semn() const{
    return semn;
}

const void intreg::set_semn(char s){
    semn = s;
}

void intreg::set_pr(nod *p){
    pr = p;
}

void intreg::set_ul(nod *p){
    ul = p;
}

void intreg::set_nr_cifre(int nr){
    nr_cifre = nr;
}

void intreg::add_cif(char c){

    if(pr == NULL){
        pr = new nod;
        pr -> set_next(NULL);
        pr -> set_prev(NULL);
        pr -> set_val(c);
        ul = pr;
        nr_cifre++;
    }
    else{

        nod *nou = new nod;
        pr -> set_prev(nou);
        nou -> set_next(pr);
        nou -> set_prev(NULL);
        nou -> set_val(c);
        pr = nou;
        nr_cifre++;
    }
}

istream &operator >>(istream &in,intreg &x){
    char s[1000];
    int nr = 0;

    cin >> s;

    if(strlen(s) < 2)
        cout << "Nr. invalid";
    else{
        x.set_semn(s[0]);

        for(int i = 1; i < strlen(s); i++)
        {
            x.add_cif(s[i]);
            nr++;
        }
    }

    x.set_nr_cifre(nr);

    return in;
}

ostream& operator <<(ostream &out,const intreg &x){
    nod *it;

    out << x.get_semn();

    for(it = x.get_ul(); it != NULL; it = it -> get_prev())
        out << it -> get_val();
    return out;

}

int intreg::nr_zerouri(){

    int nr = 0;
    nod *q, *p;

    q = this -> get_pr();

    if(this -> get_nr_cif() == 1 && q -> get_val() - '0' == 0)
        return nr;

    while(pr -> get_val() - '0' == 0)
    {
        nr++;
        nr_cifre--;

        p = pr;

        pr = pr -> get_next();
        pr -> set_prev(NULL);
        delete p;
    }

    return nr;
}

intreg intreg::max_val_abs(intreg &o2){

    intreg v_a;

    if(this -> get_nr_cif() < o2.get_nr_cif())
    {
        v_a = o2;
        v_a.set_semn(o2.get_semn());

        return v_a;
    }

    if(this -> get_nr_cif() > o2.get_nr_cif())
    {
        v_a = (*this);
        v_a.set_semn(this -> get_semn());

        return v_a;
    }

    nod *it1, *it2;
    it1 = this -> get_ul();
    it2 = o2.get_ul();

    while(it1 != NULL)
    {
        if(it1 -> get_val() - '0' < it2 -> get_val() - '0')
            return o2;

        if(it1 -> get_val() - '0' > it2 -> get_val() - '0')
            return *this;

        it1 = it1 -> get_prev();
        it2 = it2 -> get_prev();
    }

    return *this;
}

intreg intreg::operator+(intreg &o2){

    int carry = 0, nr_c = 0;
    nod *it1, *it2;
    intreg s;

    if(this -> get_semn() == o2.get_semn())
    {
        it1 = this -> get_pr();
        it2 = o2.get_pr();

        s.set_semn(o2.get_semn());

        if(this -> get_nr_cif() < o2.get_nr_cif())
        {
            it2 = o2.get_pr();
            it1 = this -> get_pr();
        }
        else
            if(this -> get_nr_cif() > o2.get_nr_cif())
            {
                it1 = o2.get_pr();
                it2 = this -> get_pr();
            }

        int nr_c = 0, nr = 0;

        while(it1 != NULL)
        {
            nod *p = new nod;

            if(s.get_pr() == NULL)
            {
                nr = it1 -> get_val() - '0' + it2 -> get_val() - '0' + carry;
                p -> set_val((nr % 10) + '0');
                p -> set_next(NULL);
                p -> set_prev(NULL);
                carry = nr / 10;

                s.set_pr(p);
                s.set_ul(p);

                it1 = it1 -> get_next();
                it2 = it2 -> get_next();
                nr_c++;
            }
            else
            {
                nr = it1 -> get_val() - '0' + it2 -> get_val() - '0' + carry;
                p -> set_val((nr % 10) + '0');

                p -> set_next(NULL);
                p -> set_prev(s.get_ul());
                s.get_ul() -> set_next(p);
                s.set_ul(p);

                carry = nr / 10;
                it1 = it1 -> get_next();
                it2 = it2 -> get_next();
                nr_c++;
            }
        }


        while(it2 != NULL)
        {
            nod *p = new nod;
            nr = it2 -> get_val() - '0' + carry;

            p -> set_val((nr % 10) + '0');

            p -> set_next(NULL);
            p -> set_prev(s.get_ul());
            s.get_ul() -> set_next(p);
            s.set_ul(p);

            carry = carry / 10;

            it2 = it2 -> get_next();
            nr_c++;
        }

        if(carry != 0)
        {
            nod *p = new nod;

            p -> set_val(carry + '0');

            p -> set_next(NULL);
            p -> set_prev(s.get_ul());
            s.get_ul() -> set_next(p);
            s.set_ul(p);

            nr_c++;
        }

        s.set_nr_cifre(nr_c);

        return s;
    }else
    {
        if(this -> get_nr_cif() < o2.get_nr_cif())
            return o2 + (*this);
        else
        {

            nod *it1, *it2;
            intreg s;
            int nr_c = 0, carry = 0, nr;

            if(this -> get_nr_cif() == o2.get_nr_cif())
            {
                it1 = this -> get_pr();
                it2 = o2.get_pr();
                bool ok = 1;

                while(it1 != NULL)//verificare daca sunt egale
                {
                    if(it1 -> get_val() != it2 -> get_val())
                    {
                        ok = 0;
                        break;
                    }

                    it1 = it1 -> get_prev();
                    it2 = it2 -> get_prev();
                }


                if(ok)//valorile absolute sunt egale
                {
                    s.add_cif('0');
                    s.set_semn('+');
                    s.set_nr_cifre(0);

                    return s;
                }
            }

            if(this -> max_val_abs(o2) == (*this))
            {
                s.set_semn(this -> get_semn());
                it1 = this -> get_pr();
                it2 = o2.get_pr();
            }
            else
            {
                s.set_semn(o2.get_semn());
                it2 = this -> get_pr();
                it1 = o2.get_pr();
            }

            while(it2 != NULL)
            {
                nod *p = new nod;

                if(s.get_pr() == NULL)
                {
                    nr = (it1 -> get_val() - '0') - (it2 -> get_val() - '0') - carry;

                    if(nr < 0)
                    {

                        p -> set_val((10 - (it2 -> get_val() - '0') + (it1 -> get_val() - '0') - carry) + '0');
                        p -> set_next(NULL);
                        p -> set_prev(NULL);

                        s.set_pr(p);
                        s.set_ul(p);

                        carry = 1;

                        nr_c++;
                    }
                    else
                    {
                        p -> set_val(nr + '0');
                        p -> set_next(NULL);
                        p -> set_prev(NULL);

                        s.set_pr(p);
                        s.set_ul(p);
                        carry = 0;
                        nr_c++;
                    }

                    it1 = it1 -> get_next();
                    it2 = it2 -> get_next();
                }
                else
                {
                    nr = (it1 -> get_val() - '0') - (it2 -> get_val() - '0') - carry;

                    if(nr < 0)
                    {
                        p -> set_val((10 - (it2 -> get_val() - '0') + (it1 -> get_val() - '0') - carry) + '0');

                        p -> set_next(NULL);
                        p -> set_prev(s.get_ul());
                        s.get_ul() -> set_next(p);
                        s.set_ul(p);

                        carry = 1;
                        nr_c++;
                    }
                    else if((nr >= 0 && it1 -> get_next() != NULL) || (nr > 0))
                    {
                        p -> set_val(nr + '0');

                        p -> set_next(NULL);
                        p -> set_prev(s.get_ul());
                        s.get_ul() -> set_next(p);
                        s.set_ul(p);

                        carry = 0;
                        nr_c++;
                    }
                    else
                        if(nr == 0 && it2 -> get_next() == NULL && it1 -> get_next() == NULL)
                            return s;

                    it1 = it1 -> get_next();
                    it2 = it2 -> get_next();
                }
            }

            while(it1 != NULL)
            {
                nod *p = new nod;

                nr = (it1 -> get_val() - '0') - carry;

                if(nr >= 0)
                {
                    p -> set_val(nr + '0');

                    p -> set_next(NULL);
                    p -> set_prev(s.get_ul());
                    s.get_ul() -> set_next(p);
                    s.set_ul(p);

                    carry = 0;
                    nr_c++;
                }
                else
                    if(nr < 0)
                    {
                        p -> set_val(10 - (it1 -> get_val() - '0') - carry + '0');
                        p -> set_next(NULL);
                        p -> set_prev(s.get_ul());
                        s.get_ul() -> set_next(p);
                        s.set_ul(p);

                        carry = 1;
                        nr_c++;
                    }
                    else
                        if(nr == 0 && it1 -> get_next() == NULL)
                            return s;


                it1 = it1 -> get_next();
            }

            it1 = s.get_ul();

            while(it1 && it1 -> get_val() == '0')
            {
                nod *temp = it1;
                s.set_ul(it1 -> get_prev());
                s.get_ul() -> set_next(NULL);

                delete temp;

                it1 = it1 -> get_prev();
                nr_c--;
            }

            s.set_nr_cifre(nr_c);
            return s;
        }
    }
}

intreg intreg::operator*(intreg &o2){

    int carry = 0, cif, nr_c = 0;
    intreg p;

    if(this -> get_semn() != o2.get_semn())
        p.set_semn('-');
    else
        p.set_semn('+');

    nod *it1, *it2, *it11;

    if((this -> get_nr_cif() == 1 && (this -> get_pr()) -> get_val() - '0' == 0) || (o2.get_nr_cif() == 1 && (o2.get_pr() -> get_val() - '0' == 0)))
    {
        p.add_cif('0');
        return p;
    }

    if(this -> get_nr_cif() < o2.get_nr_cif())
        return o2 * (*this);

    it11 = this -> get_pr();
    it2 = o2.get_pr();


    cif = it2 -> get_val() - '0';
    it1 = it11;
    int nr = 0;

    while(it1 != NULL)
    {
        nod *q;
        nr = cif * (it1 -> get_val() - '0') + carry;

        if(p.get_pr() == NULL)
        {
            q = new nod;
            q -> set_next(NULL);
            q -> set_prev(NULL);
            q -> set_val((nr % 10) + '0');
            p.set_pr(q);
            p.set_ul(q);

            nr_c++;
        }
        else
        {
            q = new nod;
            q -> set_val((nr % 10) + '0');
            q -> set_next(NULL);
            q -> set_prev(p.get_ul());
            p.get_ul() -> set_next(q);
            p.set_ul(q);

            nr_c++;
        }

        carry = nr / 10;
        it1 = it1 -> get_next();
    }

    if(carry)
    {
        nod *q = new nod;

        q -> set_val(carry + '0');
        q -> set_next(NULL);
        q -> set_prev(p.get_ul());
        p.get_ul() -> set_next(q);
        p.set_ul(q);

        nr_c++;
        carry = 0;
    }

    it2 = it2 -> get_next();
    nod *it3 = p.get_pr();


    while(it2 != NULL)
    {
        it1 = it11;
        cif = it2 -> get_val() - '0';
        it3 = it3 -> get_next();
        nod *it33 = it3;

        while(it1 != NULL)
        {
            if(it33 == NULL)
            {
                nr = (it1 -> get_val() - '0') * cif + carry;
                nod *q = new nod;

                q -> set_val((nr %10) + '0');
                q -> set_next(NULL);
                q -> set_prev(p.get_ul());
                p.get_ul() -> set_next(q);
                p.set_ul(q);

                nr_c++;
            }
            else
            {
                nr = (it33 -> get_val() - '0') + (it1 -> get_val() - '0') * cif + carry;
                it33 -> set_val((nr % 10) + '0');
                it33 = it33 -> get_next();
            }

            carry = nr / 10;
            it1 = it1 -> get_next();
        }

        if(carry)
        {
            nod *q = new nod;

            q -> set_val(carry + '0');
            q -> set_next(NULL);
            q -> set_prev(p.get_ul());
            p.get_ul() -> set_next(q);
            p.set_ul(q);

            nr_c++;
            carry = 0;
        }
        it2 = it2 -> get_next();
    }

    if(carry)
    {
        nod *q = new nod;
        q -> set_val(carry + '0');

        q -> set_next(p.get_pr());
        q -> set_prev(NULL);
        p.get_pr() -> set_prev(q);
        p.set_pr(q);
    }

    return p;
}

bool intreg::operator==(intreg &o2){

    nod *it1, *it2;

    it1 = this -> get_pr();
    it2 = o2.get_pr();

    if(this -> get_semn() != o2.get_semn())
        return 0;

    if(this -> get_nr_cif() != o2.get_nr_cif())
        return 0;

    while(it1 != NULL)
    {
        if(it1 -> get_val() != it2 -> get_val())
            return 0;

        it1 = it1 -> get_next();
        it2 = it2 -> get_next();
    }

    return 1;
}

intreg intreg::operator= (intreg o2){

    pr = o2.get_pr();
    ul = o2.get_ul();
    nr_cifre = o2.get_nr_cif();
    semn = o2.get_semn();

    return *this;
}

void intreg::afisare(){

    while(ul != NULL)
    {
        cout << ul -> get_val() << " ";

        ul = ul -> get_prev();
    }
}

void citire(int &n, intreg *&V)
{
    cout << "Numarul de numere intregi pe care vreti sa-l introduceti:\n";
    cout << "n= ";
    cin >> n;
    cout << "\n";
    cout << "Numerele se vor citi astfel: exemplu: +123, -100\n";
    cout << "Introduceti numerele:\n";
    V = new intreg[n];

    for(int i = 0; i < n; i++)
    {
        cout << "Numarul " << i + 1 << ": ";
        cin >> V[i];
        cout << "\n";
    }

    cout << "Numerele intregi care au fost introduse sunt: ";
    for(int i = 0; i < n; i++)
        cout << V[i] << ", ";

    cout << "\n\n";
}

int main()
{
    intreg *V;
    int n;
    citire(n, V);

    cout << "\n";
    cout << "Aveti la dispozitie urmatoarele comenzi: \n";
    cout << "0 - Inchidere\n";
    cout << "1 - Maximul dintre valorile absolute ale celor 2 numere\n";
    cout << "2 - Aflare nr.zerouri consecutive de la sfarsitul numarului\n";
    cout << "3 - Inmultirea a doi intregi mari\n";
    cout << "4 - Adunarea a doi intregi mari\n";
    cout << "\n";

    int c;
    cout << "Introduceti numarul comenzii: ";
    cin >> c;

    while(c != 0)
    {
        switch(c)
        {
        case 1:
            {cout << "Introduceti 2 numere: nr1= ";
            intreg x, y;
            cin >> x;
            cout << "                     ,nr2= ";
            cin >> y;
            cout << "\n";
            cout << "Maximul dintre valorile absolute este: ";
            cout << x.max_val_abs(y);
            cout << "\n";
            break;}

        case 2:
            {cout << "Introduceti un numar: nr= ";
            intreg x;
            cin >> x;
            cout << "\n";
            cout << "Nr. zerouri consecutive de la sfarsitul numarului este: ";
            cout << x.nr_zerouri();
            cout << "\n";
            break;}

        case 3:
            {cout << "Introduceti 2 numere: nr1= ";
            intreg x, y;
            cin >> x;
            cout << "                      nr2= ";
            cin >> y;
            cout << "\n";
            cout << "nr1 * nr2 = ";
            cout << (x * y);
            cout << "\n";
            break;}

        case 4:
            {cout << "Introduceti 2 numere: nr1= ";
            intreg x, y;
            cin >> x;
            cout << "                      nr2= ";
            cin >> y;
            cout << "\n";
            cout << "nr1 + nr2 = ";
            cout << (x + y);
            cout << "\n";
            break;}
        }

        cout << "Introduceti alta comanda: ";
        cin >> c;
        cout << "\n";
    }


    return 0;
}
