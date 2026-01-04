#include <iostream>
#include <string>
#include "bloomTrack.h"

using namespace std;

int main() {
    BST* root = Nil;
    TreeTransaksi rootTransaksi = Nil;
    createTree(root);
    int pilihan;
    
    stokAwal();
    katalogBouquet(root);
    
    cout << "Selamat datang di BloomTrack Florist System! \n";

    do {        
       
        tampilkanMenu(); 

        if (!(cin >> pilihan)) {
            cin.clear();            
            cin.ignore(1000, '\n'); 
            pilihan = -1;           
        } else {
            cin.ignore();         
        }
                
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
                beliBouquet(root, rootTransaksi);
                break;
            }
            
            case 5: 
            {
                clearScreen();
                menuHapusBouquet(root);
                break;
            }
            
            case 6: 
            {
                clearScreen();
                cout << "\n=== MANAJEMEN GUDANG ===\n";
                cout << "1. Cek Stok Gudang\n";
                cout << "2. Restock Bunga\n";
                cout << "0. Kembali\n";
                cout << "Pilihan: ";
                
                int subPilihan;
                cin >> subPilihan;
                cin.ignore();
                
                switch(subPilihan) {
                    case 1:
                        clearScreen();
                        cekStokGudang();
                        break;
                    case 2:
                        clearScreen();
                        restockBunga();
                        break;
                    case 0:
                        break;
                    default:
                        cout << "Pilihan tidak valid!\n";
                }
                break;
            }
            
            case 7: 
            {
                clearScreen();
                menuLaporanStatistik(root, rootTransaksi);
                break;
            }
            
            case 0: 
            {
                cout << "Yakin ingin keluar? (y/n): ";
                char konfirmasi;
                cin >> konfirmasi;
                cin.ignore();
                
                if (konfirmasi == 'y' || konfirmasi == 'Y') {
                    deleteTree(root);
                    deleteTreeTransaksi(rootTransaksi);
                    cout << "\nTerima kasih telah menggunakan BloomTrack!\n";
                } else {
                    pilihan = -1; 
                    clearScreen(); 
                }
                break;
            }
            
            default:
                cout << "Pilihan tidak valid! Silakan coba lagi.\n";
        }
        
        if (pilihan != 0) {
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.get();
            clearScreen(); 
        }
        
    } while (pilihan != 0);
    
    return 0;
}