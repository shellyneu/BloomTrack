#include <iostream>
#include <string>
#include "bloomTrack.h"

using namespace std;

int main() {
    BST* root = Nil;
    createTree(root);
    int pilihan;
    
    stokAwal();
    katalogBouquet(root);
    
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
                cout << "Bouquet berhasil ditambahkan\n";
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
            {
                clearScreen();
                cout << "FITUR BELUM DIIMPLEMENTASIKAN\n";
                break;
            }
            
            case 6: 
            {
                clearScreen();
                cekStokGudang();
                break;
            }
            
            case 7: 
            {
                clearScreen();
                menuLaporanStatistik();
                break;
            }
            
            case 0: 
            {
                clearScreen();
                cout << "Terima kasih telah menggunakan BloomTrack!\n";
                break;
            }
            
            default:
                cout << "Pilihan tidak valid! Silakan coba lagi.\n";
        }
        
        if (pilihan != 0) {
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.get();
        }
        
    } while (pilihan != 0);
    
}