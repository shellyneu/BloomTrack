#include <iostream>
#include <string>
#include "bloomTrack.h"

using namespace std;

int main() {
    BST* root = Nil;
    createTree(root);
    int pilihan;
    
    initStokAwal();
    
    cout << "Selamat datang di BloomTrack Florist System! \n";
    
    do {
        tampilkanMenu();
        cin >> pilihan;
        cin.ignore();
        
        switch (pilihan) {
            case 1: 
            {
                clearScreen();
                Bouquet baru = inputBouquet();
                node nodeBaru = alokasi(baru);
                insertNode(root, nodeBaru);
                break;
            }
            
            case 2: 
            {
                menuLihatKatalog(root);
                break;
            }
            
            case 3: 
            {
                menuCariBouquet(root);
                break;
            }
            
            case 4: 
            {
                clearScreen();
                beliBouquet(root);
                break;
            }
            
            case 5: 
            
            case 6: 

            
            case 7: 
            

            case 8: 

            
            case 0: 
            
            default:
                cout << "Pilihan tidak valid! Silakan coba lagi.\n";
        }
        
        if (pilihan != 0) {
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.get();
        }
        
    } while (pilihan != 0);
    
}