#include <iostream>
#include <iomanip>

using namespace std;

class Date
{
    static const int tageInMonaten[12];
private:
    unsigned int tag, monat, jahr;
public:
    Date(int t1 = 1, int t2 = 1, int t3 = 2019);
    Date operator+(unsigned int n);
    friend ostream& operator<<(ostream& out, Date& d);
    friend istream& operator>>(istream& in, Date& d);
};
const int Date::tageInMonaten[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

ostream& operator<<(ostream& out, Date& d)
{
    if ((d.tag < 10) && (d.monat < 10))
    {
        out << "0" << d.tag << "." << "0" << d.monat << "." << d.jahr;
    }
    else if ((d.tag < 10) && (d.monat >= 10))
    {
        out << "0" << d.tag << "." << d.monat << "." << d.jahr;
    }
    else if ((d.tag >= 10) && (d.monat < 10))
    {
        out << d.tag << "." << "0" << d.monat << "." << d.jahr;
    }
    else
    {
        out << d.tag << "." << d.monat << "." << d.jahr;
    }
    return out;
}
istream& operator>>(istream& in, Date& d)
{
    int ein1, ein2, ein3;
    char c1, c2;
    in >> ein1 >> c1 >> ein2 >> c2 >> ein3;
    while ((ein2 > 12) || (ein1 > Date::tageInMonaten[ein2-1]) || (ein3 < 1000) || (ein3 > 9999))
    {
        cout << "Wrong Input!" << endl;
        cout << "Please try again: ";
        in >> ein1 >> c1 >> ein2 >> c2 >> ein3;
    }
    d.tag = ein1;
    d.monat = ein2;
    d.jahr = ein3;
    return in;
}
Date::Date(int t1, int t2, int t3):
    tag(t1),
    monat(t2),
    jahr(t3)
    {}
Date Date::operator+(unsigned int n)
{
    tag = tag + n;
    if (tag > tageInMonaten[monat-1])
    {
        do
        {
            tag = tag - tageInMonaten[monat-1];
            monat++;
            if (monat > 12)
            {
                jahr++;
                monat = 1;
            }
        } while (tag > tageInMonaten[monat-1]);
    }
    return Date(tag, monat, jahr);
}

enum Board {Kein, Frueh, Halb, Voll};
ostream& operator<<(ostream& out2, Board& b)
{
    switch(b)
    {
    case Kein:
        return out2 << "without meals";
        break;
    case Frueh:
        return out2 << "breakfast";
        break;
    case Halb:
        return out2 << "half board";
        break;
    case Voll:
        return out2 << "all inclusive";
        break;
    default:
        return out2 << "breakfast";
        break;
    }
}

class Hotel
{
private:
    string hotelName;
    Date ankunftsDatum;
    int nachtZahl, einzelZahl, doppelZahl;
    Board verpflegungsTyp;
    double preisNachtEinzel, preisNachtDoppel;
    bool parkPlatz;
public:
    //Hotel(Date b, string a = "Hotel California", int c = 1, int d = 2, int e = 3,
          //Board f = Frueh, double g = 100, double h = 200, bool i = true);
    Hotel();
    ~Hotel();
    double get_price();
    Date get_arrival();
    Date get_checkout();
    int get_guests();
    void print();
    Date get_datum();
    int get_nachtZahl();
    int get_einzelZahl();
    int get_doppelZahl();
    string get_name();
    Board get_verpflegung();
};
Board Hotel::get_verpflegung()
{
    return verpflegungsTyp;
}
int Hotel::get_einzelZahl()
{
    return einzelZahl;
}
int Hotel::get_doppelZahl()
{
    return doppelZahl;
}
string Hotel::get_name()
{
    return hotelName;
}
int Hotel::get_nachtZahl()
{
    return nachtZahl;
}
Date Hotel::get_datum()
{
    return ankunftsDatum;
}
Hotel::Hotel()
{
    cout << "name of hotel: ";
    if (cin.peek() == '\n')
        cin.ignore();
    getline(cin, hotelName);
    cout << "arrival on: ";
    cin >> ankunftsDatum;
    cout << "how many nights: ";
    cin >> nachtZahl;
    cout << "how many single bedrooms: ";
    cin >> einzelZahl;
    cout << "how many double bedrooms: ";
    cin >> doppelZahl;
    cout << "a all inclusive" << endl << "b breakfast" << endl << "h half board" << endl << "w without meals"
    << endl;
    char st6;
    cin >> st6;
    switch (st6)
    {
        case 'W':
            verpflegungsTyp = Kein;
            break;
        case 'w':
            verpflegungsTyp = Kein;
            break;
        case 'B':
            verpflegungsTyp = Frueh;
            break;
        case 'b':
            verpflegungsTyp = Frueh;
            break;
        case 'H':
            verpflegungsTyp = Halb;
            break;
        case 'h':
            verpflegungsTyp = Halb;
            break;
        case 'A':
            verpflegungsTyp = Voll;
            break;
        case 'a':
            verpflegungsTyp = Voll;
            break;
        default :
            verpflegungsTyp = Frueh;
            break;
    }
    cout << "price one night in single bedroom: ";
    cin >> preisNachtEinzel;
    cout << "price one night in double bedroom: ";
    cin >> preisNachtDoppel;
    cout << "with parking (y(es) or n(o)): ";
    char st9;
    cin >> st9;
    if ((st9 == 'y') || (st9 == 'Y'))
        parkPlatz = true;
    else
        parkPlatz = false;
}

double Hotel::get_price()
{
    double insgesamt;
    insgesamt = ((einzelZahl*preisNachtEinzel) + (doppelZahl*preisNachtDoppel))*nachtZahl;
    if (parkPlatz)
        return((nachtZahl*10)+insgesamt);
    else
        return insgesamt;
}
Date Hotel::get_arrival()
{
    return ankunftsDatum;
}
Date Hotel::get_checkout()
{
    return (ankunftsDatum + nachtZahl);
}
int Hotel::get_guests()
{
    return((doppelZahl*2)+einzelZahl);
}
void Hotel::print()
{
    Date d5;
    d5 = get_arrival();
    cout << d5;
    cout << setw(20) << hotelName << setw(20) << nachtZahl << " Naechte" << setw(20)
    << einzelZahl << " Einzelzimmer" << setw(20) << doppelZahl << " Doppelzimmer" << setw(20);
    cout << verpflegungsTyp;
    if (parkPlatz)
        cout << setw(20) << "Mit Parkplatz";
    else
        cout << setw(20) << "Ohne Parkplatz";
}
Hotel::~Hotel()
{
    cout << "destructor hotel " << get_name() << " at ";
    cout << ankunftsDatum;
    cout << " for ";
    cout << get_guests();
    cout << " guests done" << endl;
}

class Transport
{
public:
    virtual ~Transport()
    {cout << "destructor Transport done" << endl;};
    virtual bool withTransfer() = 0;
    virtual double get_price() = 0;
    virtual void print() = 0;
};

class SelfOrganized : public Transport
{
public:
    SelfOrganized(){};
    virtual ~SelfOrganized()
    {cout << "destructor Self-organized done" << endl;};
    virtual bool withTransfer() override {return false;};
    virtual double get_price() override {return (0.00);};
    virtual void print() override {cout << "self-organized transport" << endl;};
};

class PublicTransport : public Transport
{
private:
    Date abfahrtZeit;
    string kode;
    string von;
    string zu;
    double preisEinSitzplatz;
    bool firstClass;
public:
    PublicTransport(Date a, string b = "000", string c = "Ursprung", string d = "Ziel",
                    double e = 0.00, bool f = false);
    virtual ~PublicTransport();
    virtual bool get_class()
    {
        return firstClass;
    };
    virtual double get_preisEin()
    {
        return preisEinSitzplatz;
    };
    virtual void print() override
    {
        cout << abfahrtZeit;
        cout << " " << kode;
        cout << " from " << von << " to " << zu;
        if (firstClass)
            cout << " (first class)" << endl;
        else
            cout << " (oekonomisch)" << endl;
    }
};
PublicTransport::PublicTransport(Date a, string b, string c, string d, double e, bool f):
    abfahrtZeit(a),
    kode(b),
    von(c),
    zu(d),
    preisEinSitzplatz(e),
    firstClass(f)
    {}
PublicTransport::~PublicTransport()
{
    cout << "destructor PublicTransport " << kode << " at ";
    cout << abfahrtZeit;
    cout << " done" << endl;
}

class Flight : public PublicTransport
{
private:
    bool transfer;
public:
    Flight(Date a, string b = "000", string c = "Ursprung", string d = "Ziel",
                    double e = 0.00, bool f = false, bool g = true) : PublicTransport(a,b,c,d,e,f)
                    {transfer = g;};
    virtual ~Flight()
    {cout << "destructor Flight done" << endl;};
    virtual bool withTransfer() override {return transfer;};
    virtual double get_price() override
    {
        if (!get_class())
            return get_preisEin();
        else
            return (2*get_preisEin());
    };
    virtual void print() override
    {
        cout << "flight ";
        PublicTransport::print();
    };
};

class Train : public PublicTransport
{
public:
    Train(Date a, string b = "000", string c = "UrsprungFlughafen", string d = "ZielFlughafen",
                    double e = 0.00, bool f = false) : PublicTransport(a,b,c,d,e,f)
                    {};
    virtual ~Train()
    {cout << "destructor Train done" << endl;};
    virtual bool withTransfer() override
    {
        return false;
    };
    virtual double get_price() override
    {
        if (!get_class())
            return get_preisEin();
        else
            return (1.5*get_preisEin());
    };
    virtual void print()
    {
        cout << "train ";
        PublicTransport::print();
    };
};

class Trip
{
private:
    const unsigned int no = lastNo + 1;
    static unsigned int lastNo;
    unsigned int passagierZahl;
    Hotel* hotel;
    Transport* transportOutward;
    Transport* transportBack;
    Trip* next;
public:
    Trip(){};
    Trip(unsigned int a, Hotel* b, Transport* c, Transport* d, Trip* e = nullptr):
        passagierZahl(a),
        hotel(b),
        transportOutward(c),
        transportBack(d),
        next(e)
        {
            lastNo++;
        };
    virtual ~Trip()
    {
        delete hotel;
        delete transportOutward;
        delete transportBack;
        cout << "destructor Trip done" << endl;
    };
    unsigned int get_no();
    Trip* get_next();
    void set_next(Trip* a);
    double get_price();
    void print();
};
unsigned int Trip::lastNo = 0;
unsigned int Trip::get_no()
{
    return no;
}
Trip* Trip::get_next()
{
    return next;
}
void Trip::set_next(Trip* a)
{
    next = a;
}
double Trip::get_price()
{
    double summe;
    summe = hotel->get_price() + (transportOutward->get_price() + transportBack->get_price())*passagierZahl;
    return summe;
}
void Trip::print()
{
    Date dre;
    Board fred;
    dre = hotel->get_arrival();
    fred = hotel->get_verpflegung();
    cout << "trip inquiry " << get_no() << " for " << passagierZahl <<
    " person(s)" << endl << "check-in:\thotel ";
    cout << dre;
    cout << " " << hotel->get_name() << " for " << hotel->get_nachtZahl() << " night(s) "
    << hotel->get_doppelZahl() << " double bedroom(s) " << hotel->get_einzelZahl() << " single bedroom(s) " << endl;
    cout << "\t\t\t" << fred;
    cout << endl << "outward journey: ";
    transportOutward->print();
    cout << endl << "journey back: ";
    transportBack->print();
    cout << endl << "no transfer" << endl << "\tprice: " << get_price() << " EUR" << endl;
}

class TravelAgency
{
private:
    Trip* trips;
public:
    TravelAgency(){trips = nullptr;};
    void addTrip(Trip* h)
    {
        if (trips == nullptr)
        {
            trips = h;
        }
        else
        {
            h->set_next(trips);
            trips = h;
        }
    };
    void entfernTrip(Trip* h)
    {
        Trip* tempTrip3 = new Trip();
        Trip* tempTrip4 = new Trip();
        tempTrip3 = trips;
        if (tempTrip3 == h)
        {
            trips = h->get_next();
            delete h;
            return;
        }
        else
        {
            tempTrip4 = tempTrip3;
            tempTrip3 = tempTrip3->get_next();
            while (tempTrip3 != nullptr)
            {
                if (tempTrip3 == h)
                {
                    tempTrip4->set_next(h->get_next());
                    delete h;
                    return;
                }
                else
                {
                    tempTrip4 = tempTrip3;
                    tempTrip3 = tempTrip3->get_next();
                }
            }
        cout << "Nix ist gefunden!" << endl;
        }
    };
    Trip* suchTrip(unsigned int m)
    {
        Trip* tempTrip1 = new Trip();
        tempTrip1 = trips;
        while (tempTrip1 != nullptr)
        {
            if (tempTrip1->get_no() == m)
            {
                return tempTrip1;
            }
            else
            {
                tempTrip1 = tempTrip1->get_next();
            }
        }
        if (m <= trips->get_no())
            cout << "Frueher geloescht, also nicht gefunden jetzt!" << endl;
        else
            cout << "Nicht gefunden, weil niemals hier gespeichert!" << endl;
        return nullptr;
    };
    void printAllTrips()
    {
        Trip* tempTrip2 = new Trip();
        tempTrip2 = trips;
        while (tempTrip2 != nullptr)
        {
            tempTrip2->print();
            cout << endl;
            tempTrip2 = tempTrip2->get_next();
        }
    };
};

int main()
{
    TravelAgency* hotlineAge = new TravelAgency();
    do
    {
        cout << "HOTLINE TRAVEL AGENCY" << endl << "0) Ausgang" << endl << "1) Neue Reise" << endl << "2) Suchen" <<
        endl << "3) Ausdrucken" << endl << "Ihre Wahl: ";
        int choice;
        cin >> choice;
        if (choice == 0)
        {
            return 0;
        }
        else if (choice == 1)
        {
            Trip* neuTrip2 = new Trip();
            Hotel* aufbauHotel = new Hotel();
            cout << "please choose transport for outward journey" << endl << "0 self-organized"
            << endl << "1 by flight" << endl << "2 by train" << endl << "your choice: ";
            int st11;
            cin >> st11;
            if (st11 == 1)
            {
                string st12, st13, st14;
                cout << "code of flight: ";
                if (cin.peek() == '\n')
                    cin.ignore();
                getline(cin, st12);
                cout << "airport of departure: ";
                getline(cin, st13);
                cout << "airport of arrival: ";
                if (cin.peek() == '\n')
                    cin.ignore();
                getline(cin, st14);
                cout << "price for one passenger: ";
                double st15;
                cin >> st15;
                Transport* st16 = new Flight(aufbauHotel->get_datum(),st12,st13,st14,st15);

                 cout << "please choose transport for journey back" << endl << "0 self-organized"
            << endl << "1 by flight" << endl << "2 by train" << endl << "your choice: ";
            int st17;
            cin >> st17;
            Date zurueckDatum;
            zurueckDatum = aufbauHotel->get_datum() + aufbauHotel->get_nachtZahl();
            if (st17 == 1)
            {
                string st18, st19, st20;
                cout << "code of flight: ";
                if (cin.peek() == '\n')
                    cin.ignore();
                getline(cin, st18);
                cout << "airport of departure: ";
                if (cin.peek() == '\n')
                    cin.ignore();
                getline(cin, st19);
                cout << "airport of arrival: ";
                if (cin.peek() == '\n')
                    cin.ignore();
                getline(cin, st20);
                cout << "price for one passenger: ";
                double st21;
                cin >> st21;
                Transport* st22 = new Flight(zurueckDatum,st18,st19,st20,st21);

                Trip* neuTrip3 = new Trip(aufbauHotel->get_guests(),aufbauHotel,st16,st22,nullptr);
                neuTrip2 = neuTrip3;
            }
            if (st17 == 0)
            {
                Transport* st22 = new SelfOrganized();
                Trip* neuTrip3 = new Trip(aufbauHotel->get_guests(),aufbauHotel,st16,st22,nullptr);
                neuTrip2 = neuTrip3;
            }
            if (st17 == 2)
            {
                string st18, st19, st20;
                cout << "code of train: ";
                if (cin.peek() == '\n')
                    cin.ignore();
                getline(cin, st18);
                cout << "main train station of departure: ";
                if (cin.peek() == '\n')
                    cin.ignore();
                getline(cin, st19);
                cout << "main train station of arrival: ";
                if (cin.peek() == '\n')
                    cin.ignore();
                getline(cin, st20);
                cout << "price for one passenger: ";
                double st21;
                cin >> st21;
                Transport* st22 = new Train(zurueckDatum,st18,st19,st20,st21);

                Trip* neuTrip3 = new Trip(aufbauHotel->get_guests(),aufbauHotel,st16,st22,nullptr);
                neuTrip2 = neuTrip3;
            }

            }
            if (st11 == 0)
            {
                Transport* st16 = new SelfOrganized();

                cout << "please choose transport for journey back" << endl << "0 self-organized"
            << endl << "1 by flight" << endl << "2 by train" << endl << "your choice: ";
            int st17;
            cin >> st17;
            Date zurueckDatum;
            zurueckDatum = aufbauHotel->get_datum() + aufbauHotel->get_nachtZahl();
            if (st17 == 1)
            {
                string st18, st19, st20;
                cout << "code of flight: ";
                if (cin.peek() == '\n')
                    cin.ignore();
                getline(cin, st18);
                cout << "airport of departure: ";
                if (cin.peek() == '\n')
                    cin.ignore();
                getline(cin, st19);
                cout << "airport of arrival: ";
                if (cin.peek() == '\n')
                    cin.ignore();
                getline(cin, st20);
                cout << "price for one passenger: ";
                double st21;
                cin >> st21;
                Transport* st22 = new Flight(zurueckDatum,st18,st19,st20,st21);

                Trip* neuTrip3 = new Trip(aufbauHotel->get_guests(),aufbauHotel,st16,st22,nullptr);
                neuTrip2 = neuTrip3;
            }
            if (st17 == 0)
            {
                Transport* st22 = new SelfOrganized();
                Trip* neuTrip3 = new Trip(aufbauHotel->get_guests(),aufbauHotel,st16,st22,nullptr);
                neuTrip2 = neuTrip3;
            }
            if (st17 == 2)
            {
                string st18, st19, st20;
                cout << "code of train: ";
                if (cin.peek() == '\n')
                    cin.ignore();
                getline(cin, st18);
                cout << "main train station of departure: ";
                if (cin.peek() == '\n')
                    cin.ignore();
                getline(cin, st19);
                cout << "main train station of arrival: ";
                if (cin.peek() == '\n')
                    cin.ignore();
                getline(cin, st20);
                cout << "price for one passenger: ";
                double st21;
                cin >> st21;
                Transport* st22 = new Train(zurueckDatum,st18,st19,st20,st21);

                Trip* neuTrip3 = new Trip(aufbauHotel->get_guests(),aufbauHotel,st16,st22,nullptr);
                neuTrip2 = neuTrip3;
            }

            }
            if (st11 == 2)
            {
                string st12, st13, st14;
                cout << "code of train: ";
                if (cin.peek() == '\n')
                    cin.ignore();
                getline(cin, st12);
                cout << "main train station of departure: ";
                if (cin.peek() == '\n')
                    cin.ignore();
                getline(cin, st13);
                cout << "main train station of arrival: ";
                if (cin.peek() == '\n')
                    cin.ignore();
                getline(cin, st14);
                cout << "price for one passenger: ";
                double st15;
                cin >> st15;
                Transport* st16 = new Train(aufbauHotel->get_datum(),st12,st13,st14,st15);

                cout << "please choose transport for journey back" << endl << "0 self-organized"
            << endl << "1 by flight" << endl << "2 by train" << endl << "your choice: ";
            int st17;
            cin >> st17;
            Date zurueckDatum;
            zurueckDatum = aufbauHotel->get_datum() + aufbauHotel->get_nachtZahl();
            if (st17 == 1)
            {
                string st18, st19, st20;
                cout << "code of flight: ";
                if (cin.peek() == '\n')
                    cin.ignore();
                getline(cin, st18);
                cout << "airport of departure: ";
                if (cin.peek() == '\n')
                    cin.ignore();
                getline(cin, st19);
                cout << "airport of arrival: ";
                if (cin.peek() == '\n')
                    cin.ignore();
                getline(cin, st20);
                cout << "price for one passenger: ";
                double st21;
                cin >> st21;
                Transport* st22 = new Flight(zurueckDatum,st18,st19,st20,st21);

                Trip* neuTrip3 = new Trip(aufbauHotel->get_guests(),aufbauHotel,st16,st22,nullptr);
                neuTrip2 = neuTrip3;
            }
            if (st17 == 0)
            {
                Transport* st22 = new SelfOrganized();
                Trip* neuTrip3 = new Trip(aufbauHotel->get_guests(),aufbauHotel,st16,st22,nullptr);
                neuTrip2 = neuTrip3;
            }
            if (st17 == 2)
            {
                string st18, st19, st20;
                cout << "code of train: ";
                if (cin.peek() == '\n')
                    cin.ignore();
                getline(cin, st18);
                cout << "main train station of departure: ";
                if (cin.peek() == '\n')
                    cin.ignore();
                getline(cin, st19);
                cout << "main train station of arrival: ";
                if (cin.peek() == '\n')
                    cin.ignore();
                getline(cin, st20);
                cout << "price for one passenger: ";
                double st21;
                cin >> st21;
                Transport* st22 = new Train(zurueckDatum,st18,st19,st20,st21);

                Trip* neuTrip3 = new Trip(aufbauHotel->get_guests(),aufbauHotel,st16,st22,nullptr);
                neuTrip2 = neuTrip3;
            }

            }
            hotlineAge->addTrip(neuTrip2);
            cout << endl;
        }
        else if (choice == 2)
        {
            cout << "number of trip: ";
            int suchKeyWort;
            cin >> suchKeyWort;
            Trip* ergebNis = new Trip();
            ergebNis = hotlineAge->suchTrip(suchKeyWort);
            if (ergebNis != nullptr)
                {
                    ergebNis->print();
                    cout << "(d)elete or (n)ot: ";
                    char fergTel;
                    cin >> fergTel;
                    if ((fergTel == 'd') || (fergTel == 'D'))
                        {
                            hotlineAge->entfernTrip(ergebNis);
                        }
                }
            cout << endl;
        }
        else if (choice == 3)
        {
            hotlineAge->printAllTrips();
            cout << endl;
        }
    } while(0 != 1);
}
