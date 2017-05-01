#include <bits/stdc++.h>

//dane wejściowe:
/*
    symbol startowy A
    zbiór symboli nieterminalnych {A, B, C, D, E, F, G, H }
    symbole terminalne to 26 liter alfabetu angielskiego
    przykładowe wejście:
    1       // liczba sprawdzanych gramatyk 
    2 3     // liczba produkcji typu <pierwszego> <drugiego>
    A B C   // produkcja typu 1
    A B B   // produkcja typu 1
    A b     // produkcja typu 2
    C c     // produkcja typu 2
    B b     // produkcja typu 2
    bbccc   // słowo
    
    dane wyjściowe:
    TAK     // słowo należy do gramatyki
    NIE     // else

*/

//dane do pojedynczego testu (instancji)
int m1, m2;
int8_t hash_table_type_st[70];
int8_t hash_table_type_nd[26];
std::string word;

void wczytaj_dane();
bool wykonaj_algorytm();

int main(){
    int liczba_testow; std::cin >> liczba_testow;
    for( int num_test = 0; num_test < liczba_testow; ++num_test){
        wczytaj_dane();
        if( wykonaj_algorytm() ) 
            printf("TAK\n");
        else
            printf("NIE\n");
    }

    return 0;
}

void wczytaj_dane(){
    scanf("%d %d", &m1, &m2);
    memset(hash_table_type_st, 0, sizeof(int8_t)*70);
    memset(hash_table_type_nd, 0, sizeof(int8_t)*26);
    
    //wczytywanie produkcji typu pierwszego
    for( int i=0; i < m1; ++i ){
        char tempA, tempB, tempC;
        std::cin >> tempA; std::cin >> tempB; std::cin >> tempC;
        hash_table_type_st[ ((tempB&7)<<3)+(tempC&7) ] |= 1<<(tempA&7);
    }

    //wczytywanie produkcji typu drugiego
    for( int i=0; i < m2; ++i ){
        char tempA, tempB;
        std::cin >> tempA; std::cin >> tempB;
        hash_table_type_nd[ tempB%26 ] |= 1<<(tempA&7);
    }

    //wczytanie słowa
    std::cin >> word;
}

bool wykonaj_algorytm(){
    int n = word.length();
    int8_t main_table[n][n]; memset(main_table, 0, sizeof(int8_t)*n*n);

    //część pierwsza inicjalizacja górnego wiersza produkcjami typu drugiego
    for(int i = 0; i < n; ++i ){    
        main_table[0][i] = hash_table_type_nd[ word[i]%26 ];
        //jezeli nic nie wstawiono to znaczy ze nie da sie stworzyc takiego slowa - wiec false
        if( !main_table[0][i] )
            return false;
    }

    //tutaj główna część algorytmu
    for(int a=1; a<n; ++a)
        for(int b=0; b < n-a; ++b){
            int a1 = 0;
            int a2 = a-1, b2 = b+1;
            
            while(a2 >= 0){
                if( main_table[a1][b] &&  main_table[a2][b2] )
                    for(int i=0; i<8; ++i )
                        for(int j=0; j<8; ++j)
                            if( (main_table[a1][b] & 1<<i)  && (main_table[a2][b2] & 1<<j) )
                                main_table[a][b] |= hash_table_type_st[(i<<3) + j];

                a1++;//b =const
                a2--;  b2++;
            }
        }
    
    return ((main_table[n-1][0] & 2))? true : false ;
}
