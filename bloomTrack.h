#ifndef BLOOMTRACK_H
#define BLOOMTRACK_H

#include <iostream>

using namespace std;

const int JUMLAH_JENIS_BUNGA = 5;
const string NAMA_BUNGA[JUMLAH_JENIS_BUNGA] = {
    "Mawar", "Lily", "Tulip", "Daisy", "Sunflower"
};

extern int stokBungaMentah[JUMLAH_JENIS_BUNGA];

struct Bouquet {
    string namaBouquet;
    long harga;
    string ukuran;
    string warnaDominan;
    int resepBunga[JUMLAH_JENIS_BUNGA];
};

struct BST {
    Bouquet data;
    BST* left;
    BST* right;
};

BST* buatNode(Bouquet bouquet);
BST* search(BST* tree, string namaBouquet);
BST* findMin(BST* tree);
BST* findMax(BST* tree);

BST* insert(BST* tree, Bouquet bouquet);
BST* deleteNode(BST* tree, string namaBouquet);
bool updateBouquet(BST* tree, string namaBouquet);

void inorder(BST* tree);
void preorder(BST* tree);
void postorder(BST* tree);
void levelOrder(BST* tree);

void searchByHarga(BST* tree, long minHarga, long maxHarga);
void searchByUkuran(BST* tree, string ukuran);

bool cekStokCukup(int resepBunga[]);
void kurangiStok(int resepBunga[]);
void beliBouquet(BST* tree);

void cekStokGudang();
void restockBunga();
void initStokAwal();

int countNodes(BST* tree);
void tampilkanTermurah(BST* tree);
void tampilkanTermahal(BST* tree);
void tampilkanStatistik(BST* tree);

Bouquet inputBouquet();
void displayBouquet(Bouquet bouquet);
void displayHeaderKatalog();
void cetakStruk(Bouquet bouquet);

void tampilkanMenu();
void menuLihatKatalog(BST* tree);
void menuCariBouquet(BST* tree);
void clearScreen();

#endif