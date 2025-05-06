
#include <iostream>
#include <cmath>
#include "vector"

using namespace std;

//CONST ZAD 1/2
constexpr double seed = 4212131231; // Seed za randomGenerator
constexpr int n = 6; // Heming(n,k)
constexpr int k = 3; //

//CONST ZAD 2
constexpr int N = 1000; // N nasumicno generisanih rijeci
constexpr int number_of_mistakes = 4;
constexpr int Im_rows = 8; // Im - Intervaling_matrix (redovi)
constexpr int Im_cols = 6;// -||- (kolone)
constexpr int Number_of_symbols = 50; // ukupan broj simbola
constexpr int Period = 50; // Period greski



int randomGenerator(double *u);                                                                     // Vraca 0 ili 1
int generateAllCodes(int i0, int i1, int i2, const int*prvi, const int*drugi, const int*treci);     //Koristi informacione bitovbe i matricu za stvaranje kodova
void writeBinary(int num);                                                                          //Ispisuje broj iz decimalnog u binarni
void writeMatrix(vector<vector<int>>Intervaling_matrix);                                            //Ispis Intervaling matrice



int main() {
    double  u = seed;

    //PRVI ZADATAK


    int prvi[n] = {1, 1, 0, 1, 1, 1};   //Inicijalna matrica
    int drugi[n] = {1, 1, 1 ,1, 1, 1};
    int treci[n] = {0, 1, 1 ,0, 0, 1};

    vector<int> Codes_xi_1;             //Niz svih kodnih rijeci
    vector<int> counter;                //Niz svih tezina



    for(int i = 0; i < pow(2, k); i++) {
        int bit = i;

        int i0 =  bit & 1;
        int i1 = (bit >> 1) & 1;          //Pravimo niz nasih kodnih rijeci
        int i2 = (bit >> 2) & 1;

        Codes_xi_1.push_back(generateAllCodes(i0,i1,i2,prvi,drugi,treci));
    }


    int dmin = 0;                          //Koristi se za broj gresaka koje moze da isparvi

    for(int i = 0; i < Codes_xi_1.size(); i++) {
        int cnt = 0;
        for(int j = 0; j < (n + 1); j++) {
            if(((Codes_xi_1[i] >> j) & 1)== 1) {          //Odredjivanje tezina
                cnt++;
            }

        }
        counter.push_back(cnt);
        if(dmin == 0 || dmin > cnt) {       //Provjera ako je manje onda mijenjamo min
            dmin = cnt;
        }
    }

    for(int j = 0; j < (n+1); j++) {
        int br = 0;
        for(int i = 0; i < counter.size();i++) {
            if(counter[i] ==j) {
                br++;
            }
        }
        cout << "Kodnih rijeci tezine " << j << " ima " << br << endl;
    }
    cout << endl;


    cout << "Kod moze da ispravi " << (dmin -1)/2 << " gresaka." << endl;



    // DRUGI ZADATAK
    //a)


    vector<int> Codes_xi_2;                         // Matrica slucajno generisanih rijeci

    for(int i = 0; i < N; i++){
        int  i0 = randomGenerator(&u);
        int  i1 = randomGenerator(&u);
        int  i2 = randomGenerator(&u);


        Codes_xi_2.push_back(generateAllCodes(i0, i1, i2, prvi, drugi, treci));         //Pravimo niz svih nasih kodnih rijeci

    }
    cout <<endl;
    cout << "KODNE RIJECI SU:" << endl;             //Ispis svih kodnih rijeci
    cout <<endl;
    for(int i =0; i < Codes_xi_2.size() ;i++) {
        writeBinary(Codes_xi_2[i]);
    }
    cout <<endl;
    cout <<endl;


    // b) & c)

    for(int f = 0; f < Number_of_symbols / Period ; f++) {                                   //Koliko simbola toliko ponavljamo pri cemu izdvajamo svakih 50,

        vector<vector<int>> Intervaling_matrix(Im_rows, vector<int>(Im_cols));      //Intervaling matrica Im_rows*Im_cols


        for(int i = 0; i < Im_rows  ; i++) {
            int t = 0;
            int i1 = randomGenerator(&u);

            int i2 =  randomGenerator(&u);
            int i3 = randomGenerator(&u);
            int z1 = i1 ^ i2;
            int z2 = i1 ^ i3;
            int z3 = i2 ^ i3;

            Intervaling_matrix[i][t++] = z1;
            Intervaling_matrix[i][t++] = z2;
            Intervaling_matrix[i][t++] = i1;
            Intervaling_matrix[i][t++] = z3;
            Intervaling_matrix[i][t++] = i2;
            Intervaling_matrix[i][t++] = i3;

        }

        cout << "Matrica origalno poslatih kodnih rijeci" << endl;
        cout << endl;
        writeMatrix(Intervaling_matrix);              //Ipis matrice bez gresaka ukoliko je potrebno


        int input_position = 15;                        // Ovdje je fiknso radi testiranja i moze se mijnejati, a moze se staviti i da korisnik unosi poziciju prve greske
        int wrong_position_start= input_position - 1;   // Pocetna pozcija greske u matrici jer je indexiranje od 0


        int mistakes[number_of_mistakes] = {wrong_position_start, wrong_position_start + 1,wrong_position_start + 2,wrong_position_start + 3};

        for(int i =0; i < number_of_mistakes; i++) {

            int wrong_position = mistakes[i];

            if(wrong_position >= Im_rows*Im_cols) {
                break;
            }
            int rw = wrong_position / Im_rows ;            //Ovdje na osnovu pozocije radimo pretargu po kolonama da nadjemo pozcijiu
            int cl = wrong_position % Im_rows ;

            (Intervaling_matrix[cl][rw] == 1) ? Intervaling_matrix[cl][rw] = 0 : Intervaling_matrix[cl][rw] = 1 ;


        }

        cout << "Matrica poslatih kodnih rijeci sa gresakma na unijetim pozicijama" << endl;
        cout << endl;
        writeMatrix(Intervaling_matrix);                //Ipis matrice sa greskama ukoliko je potrebno


        for(int i = 0; i < Im_rows ; i++) {
            int t = 0;
            int r1 = Intervaling_matrix[i][t++];
            int r2 = Intervaling_matrix[i][t++];
            int r3 = Intervaling_matrix[i][t++];
            int r4 = Intervaling_matrix[i][t++];
            int r5 = Intervaling_matrix[i][t++];
            int r6 = Intervaling_matrix[i][t++];

            cout << "Primljneo iz kanala: " << r1 << r2 << r3 << r4 << r5 << r6<< endl;

            int s1 = r1^r3^r5;
            int s2 = r2^r3^r6;
            int s3 = r4^r5^r6;
            int s4 = r1^r2^r3^r4^r5^r6;

            int positionS = s3 * 4 + s2 * 2 + s1 * 1;

            if(positionS != 0 && s4 == 1) {
                (Intervaling_matrix[i][positionS - 1] == 1 ) ? Intervaling_matrix[i][positionS - 1] = 0 : Intervaling_matrix[i][positionS - 1] = 1 ;
            }
            cout << "Dekodovano:          ";
            for(int j = 0; j < Im_cols; j++) {
                cout << Intervaling_matrix[i][j];
            }
            cout << endl;
            cout << endl;
        }
    }

        return  0;
    }


    int randomGenerator(double *u){
        double a = 429493445;
        double c = 907633385;
        (*u) = fmod(a * (*u) + c,4294967296);
        return (((*u) / 4294967296) <0.5) ? 0 : 1 ;
    }

    int generateAllCodes(int i0, int i1, int i2, const int*prvi, const int*drugi, const int*treci) {
        int info = 0b000000;
        vector<int> Codes_xi_1;
        for(int m = (n - 1); m >= 0 ; m--) {
            int br = (i2 & prvi[m])^ (i1 & drugi[m]) ^ (i0 & treci[m]);
            if(br == 1) {
                info = info | (1 << (5 -  m));

            }
        }

        return info;
    }

    void writeBinary(int num) {

        for(int i = (n - 1) ; i >=0; i--) {
            cout << ((num >> i)&1);
        }
        cout << endl;
    }

    void writeMatrix(vector<vector<int>>Intervaling_matrix) {
        for(int i = 0; i < Im_rows; i++) {
            for(int j = 0 ; j < Im_cols; j++) {
                cout << Intervaling_matrix[i][j] << " ";
            }

            cout << endl;
        }
        cout << endl;
    }


