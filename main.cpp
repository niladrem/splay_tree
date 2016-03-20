#include <bits/stdc++.h>
#include "splaytree.hpp"

using namespace std;

int main(){
    SplayTree<int> tree;
    while(true){
        cout << "\n1 - dodaj wartosc\n";
        cout << "2 - znajdz wartosc\n";
        cout << "3 - usun wartosc\n";
        char c;
        cin >> c;
        if(c == '1'){
            cout << "Podaj wartosc: ";
            int i;
            cin >> i;
            tree.insert(i, i);
        }
        else if(c == '2'){
            cout << "Podaj wartosc: ";
            int i;
            cin >> i;
            if(tree.find(i)){
                cout << "Znaleziono wartosc " << i << "\n";
            }
            else{
                cout << "Nie znaleziono wartosci " << i << "\n";
            }
        }
        else if(c == '3'){
            cout << "Podaj wartosc: ";
            int i;
            cin >> i;
            tree.erase(i);
        }
    }
    return 0;
}
