/////programul trebuie rulat pe windows astfel incat comanda de clear system("CLS") sa ruleze perfect
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <regex>
#include <cstdlib>
using namespace std;

class Vehicul{
    public:
    string tip;
    string model;
    string numar_inmatriculare;
    string capacitate;
    string folosit;
    string data_expirare_ITP;
    string an_fabricatie;
    Vehicul(){
        cin >> tip >> model >> numar_inmatriculare >> capacitate >> folosit >> data_expirare_ITP >> an_fabricatie;

    }
    Vehicul(string t, string m, string n, string c, string f, string d, string a){
        this->tip = t;
        this->model = m;
        this->numar_inmatriculare = n;
        this->capacitate = c;
        this->folosit = f;
        this->data_expirare_ITP = d;
        this->an_fabricatie = a;
    }
    friend ostream& operator<<(ostream& out, const Vehicul& v){
        out << v.tip <<";"<< v.model <<";"<< v.numar_inmatriculare <<";"<< v.capacitate <<";"<< v.folosit <<";"<< v.data_expirare_ITP <<";"<< v.an_fabricatie <<";";
        return out;
    }
};






void adaugare(vector<string> &f){
    string t;
    string m;
    string nr;
    string can;
    string fol;
    string ditp;
    string anf;
    cout << "\nAdaugati tipul vehiculului (Camion/Camioneta/Autobuz/Masina/Dubita): ";
    int ok = 0;
    while (ok == 0){
        cin >> t;
        if (t == "Camion" || t == "Camioneta" || t == "Autobuz" || t == "Masina" || t == "Dubita")
            ok = 1;
        else
            cout << "\nTrebuie sa introduci unul dintre vehiculele exemplificate: ";
    }
    
    cout << "\nAdaugati marca vehiculului (ex. Mercedes): ";
    cin >> m;
    cout << "\nAdaugati numarul de inmatriculare al vehiculului (ex. AB-123-ABC): ";
    cin >> nr;
    cout << "\nAdaugati capacitatea vehiculului (in tone): ";
    ok = 0;
    while (ok == 0){
        cin >> can;
        if (regex_match (can, regex("(\\d{1,2})") )){
            ok = 1;
        }
        else
            cout << "\nCantitatea pe care o introduceti trebuie sa fie un numar intreg: ";
    }
    
    cout << "\nAdaugati stadiul de uzura al vehiculului (este folosit? Da/Nu): ";
    ok = 0;
    while (ok == 0){
        cin >> fol;
        if (fol == "Da" || fol == "Nu")
            ok = 1;
        else
            cout << "\nTrebuie sa introduci unul dintre optiunile exemplificate: ";
    }
    cout << "\nAdaugati data cand expira ITP-ul (ex. 30/12/2020): ";
    ok = 0;
    while (ok == 0){
        cin >> ditp;
        if (regex_match (ditp, regex("(\\d{1,2}/\\d{1,2}/\\d{4})") )){
            time_t now = time(0);
            tm *ltm = localtime(&now);
            int an_loc = 1900 + ltm->tm_year;
            string lu;
            string ann;
            string zii;
            stringstream ss (ditp);
            getline(ss,zii,'/');
            getline(ss,lu,'/');
            getline(ss,ann);
            int an_ii = stoi(ann);
            int luna_ii = stoi(lu);
            int zi_ii = stoi(zii);
            if (zi_ii >0 && zi_ii < 32 && luna_ii > 0 && luna_ii < 13 && an_ii <= an_loc+1)
                ok = 1;
            else
                cout << "\nTrebuie sa introduci data de expirare corecta a ITP-ului ca in exemplul dat (ITP-ul se poate face doar pentru un an din anul curent): ";
            
        }
        else
            cout << "\nTrebuie sa introduci data de expirare a ITP-ului ca in exemplul dat: ";
        
        
        
    }
    cout << "\nAdaugati anul de fabricatie (ex. 2020): ";
    ok = 0;
    while (ok == 0){
        time_t now = time(0);
        tm *ltm = localtime(&now);
        int an_loc = 1900 + ltm->tm_year;
        cin >> anf;
        int k = stoi(anf);
        if (regex_match (anf, regex("(\\d{4})")) && k >=1950 && k <= an_loc){
            ok = 1;
        }
        else 
            cout << "\nTrebuie sa introduci un an corect: ";
    }
    

    Vehicul a(t,m,nr,can,fol,ditp,anf);
    f.push_back("\n"+a.tip);
    f.push_back(a.model);
    f.push_back(a.numar_inmatriculare);
    f.push_back(a.capacitate);
    f.push_back(a.folosit);
    f.push_back(a.data_expirare_ITP);
    f.push_back(a.an_fabricatie);
}
void stergere(vector<string> &f, string nr_inmatriculare){
    vector<string>::iterator p;
    if (find(f.begin(),f.end(), nr_inmatriculare) != f.end()){
        p = find(f.begin(),f.end(), nr_inmatriculare) + 4;
        f.erase(p);
        f.erase(p-1);
        f.erase(p-2);
        f.erase(p-3);
        f.erase(p-4);
        f.erase(p-5);
        f.erase(p-6);
    }
    else
        cout << "\nVehiculul pe care doriti sa il stergeti nu exista\n";
}



void ITP(vector<string> &f){
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int zi_local = 1 + ltm->tm_mday;
    int luna_local = 1 + ltm->tm_mon;
    int an_local = 1900 + ltm->tm_year;

    vector<string>::iterator i;
    for (i=f.begin();i!=f.end();i++){
        if (regex_match (*i, regex("(\\d{1,2}/\\d{1,2}/\\d{4})") )){
            string luna;
            string an;
            string zi;
            stringstream ss (*i);
            getline(ss,zi,'/');
            getline(ss,luna,'/');
            getline(ss,an);
            int an_i = stoi(an);
            int luna_i = stoi(luna);
            int zi_i = stoi(zi);
            if (an_i == an_local && luna_i == luna_local){
                cout << "Marca: " << *(i-4) << "; ";
                cout << "Numar de inmatriculare: " << *(i-3) << "; ";
                cout << "Este in uz: " << *(i-1) << "; ";
                cout << "Data expirare ITP: " << *(i) << "; ";

            }
            cout << "\n";
        }
        
    }
    cout << "\n";
}

void statistica(vector<string> &f){
    vector<string>::iterator i;
    int ex = 1;
    while (ex == 1){
        cout << "\n---------------------------------------------------------------------------------------------------------\n";
        cout << "Alegeti de mai jos statistica pe care doriti sa o vizualizati apasand tasta corespunzatoare acesteia:\n";
        cout << "   1. Statistica vechimi vehiculelor\n";
        cout << "   2. Statistica capacitatii vehiculelor\n";
        cout << "   3. Statistica completa a tuturor vehiculelor\n";
        cout << "Daca doriti sa va intoarceti la meniul principal, apasati tasta 0\n";
        cout << "---------------------------------------------------------------------------------------------------------\n";
        int r;
        cin >> r;
        system("CLS");
        switch (r){
            case 1:{
                time_t now = time(0);
                tm *ltm = localtime(&now);
                int ann = 1900 + ltm->tm_year;
                int c10p = 0;
                int c10m = 0;
                int cc = 0;
                int medie = 0;
                int contor = 0;
                for (i=f.begin();i!=f.end();i++){
                    if (regex_match (*i, regex("(\\d{4})") )){
                        contor = contor +1;
                        int w = stoi(*i);
                        if (w > 2010)
                            c10p = c10p + 1;
                        else
                            c10m = c10m + 1;
                        if (w == ann)
                            cc = cc + 1;
                        medie = medie + w;
                    }
                }  
                medie = medie / contor;
                cout << c10m << " vehicule au o vechime mai mare de 10 ani\n";
                cout << c10p << " vehicule au o vechime mai mica de 10 ani\n";
                cout << cc << " vehicule au fost fabricate in anul curent\n";
                cout << "Media aritmetica a anilor de fabricatie este " << medie << "\n";
                break;
            }
            case 2:{
                int tp = 0;
                int tm = 0;
                float medie = 0;
                int contor = 0;
                for (i=f.begin();i!=f.end();i++){
                    if (regex_match (*i, regex("(\\d{1,2})") )){
                        contor = contor + 1;
                        int w = stoi(*i);
                        if (w >=5)
                            tp = tp + 1;
                        else 
                            tm = tm + 1;   
                        medie = medie + w;
                    }
                }
                medie = medie / contor;
                cout << "Numarul vehiculelor cu o capacitate de peste 5 tone este: " << tp << "\n";
                cout << "Numarul vehiculelor cu o capacitate de sub 5 tone este: " << tm << "\n";
                cout << "Media artitmetica a capacitatii vehiculelor este: " << medie << "\n"; 
                break;
            }
            case 3:{
                
                vector<string>::iterator it;
                vector<string>::iterator o;
                for (it = f.begin();it!=f.end();it++){
                    cout << *it << " ";
                }
                break;
            }
            
            case 0:{
                ex = 0;
                break;
            }

            
            default:{
                cout << "Trebuie sa alegeti una dintre optiunile de mai sus\n";
                break;
            }
        }
    }


}


void nefolosite(vector<string> &f){
    vector<string>::iterator i;
    int n = 0;
    for (i=f.begin();i!=f.end();i++){
        if (regex_match (*i, regex("(Da||Nu)") )){
            if (*i == "nu" || *i == "Nu" || *i == "NU"){
                n = n + 1;
            }
        }
    }
    cout << "Numarul de vehicule nefolosite este: " << n << "\n";
    
}


int main(){
    ifstream f("vehicule.csv");
    vector<string> flota;
    vector<string>::iterator it;
    string a;
    if (f.is_open()){
        cout << "Fisierul a fost incarcat cu succes\n";
        while (getline(f,a,',')){
            flota.push_back(a);
        }
    }
    else{
        ofstream k("vehicule.csv");
        cout << "Fisierul a fost creat si incarcat cu succes\n";
        k << "Tip,Model,Numar,Capacitate,folosit,ExpirareITP,AnFabricatie,";
        k.close();
        ifstream f("vehicule.csv");
        while (getline(f,a,',')){
            flota.push_back(a);
        }
        f.close();
    }
    
    int exit = 1;
    while (exit == 1){
        cout << "\n--------------------------------------------------------------------------------\n";
        cout << "Pentru a adauga un vehicul nou apasati tasta 1\n";
        cout << "Pentru a casa un vehicul, apasati tasta 2\n";
        cout << "Pentru a vedea vehiculele al caror ITP expira in luna curenta, apasati tasta 3\n";
        cout << "Pentru generarea de statistici a vehiculelor, apasati tasta 4\n";
        cout << "Pentru a vizualiza numarul de vehicule care nu sunt folosite, apasati tasta 5\n";
        cout << "Daca doriti sa inchideti programul si sa salvati fisierul, apasati tasta 0\n";
        cout << "--------------------------------------------------------------------------------\n";

        int raspuns;
        cin >> raspuns;
        system("CLS");
        switch (raspuns){
            case 1:{
                adaugare(flota);
                cout << "vehiculul a fost adaugat cu succes!\n";
                break;
            }
            case 2:{
                cout << "Scrieti numarul de inmatriculare al vehiculului pe care doriti sa il casati! ex:AB/12/ABC\n";
                string nr_i;
                cin >> nr_i;
                stergere(flota,nr_i);
                cout << "vehiculul a fost casat cu succes!\n";
                break;
            }

            case 3:{
                cout << "Vehiculele al caror ITP expira in luna curenta sunt:\n";
                ITP(flota);
                break;
            }

            case 4:{
                statistica(flota);
                break;
            }

            case 5:{
                nefolosite(flota);
                break;
            }

            case 0:{
                exit = 0;
                cout << "Ati iesit cu succes din program iar progresul dumneavoastra a fost salvat!\n";
                break;
            }

            default:
                cout << "Trebuie sa alegeti una dintre optiunile de mai sus\n";
                break;
        }
    }
    
    
    ofstream o("vehicule.csv");
    for (it=flota.begin();it!=flota.end();it++){
        string a = *it;
        if (a[0]=='/')
            o << a;
        else
            o << a << ",";
    }
    o.close();
}
