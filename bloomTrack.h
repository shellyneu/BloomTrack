#ifndef BLOOMTRACK_H
#define BLOOMTRACK_H

#include <iostream>

using namespace std;

const int JUMLAH_JENIS_BUNGA = 5;
const int MAX_TRANSAKSI = 100;
const string NAMA_BUNGA[JUMLAH_JENIS_BUNGA] = {
    "Mawar", "Lily", "Tulip", "Daisy", "Sunflower"
};
const long HARGA_BUNGA[JUMLAH_JENIS_BUNGA] = {
    5000, 7000, 6000, 4500, 8000
};

extern int stokBungaMentah[JUMLAH_JENIS_BUNGA];

struct Bouquet {
    string namaBouquet;
    long harga;
    string ukuran;
    int resepBunga[JUMLAH_JENIS_BUNGA];
};

const int MAX_ITEM_TRANSAKSI = 10;

struct ItemTransaksi {
    string namaBouquet;
    long harga;
    string ukuran;
};

struct Transaksi {
    int nomorTransaksi;
    string namaPembeli;
    ItemTransaksi items[MAX_ITEM_TRANSAKSI];
    int jumlahItem;
    long totalHarga;
};

struct BST {
    Bouquet data;
    BST* left;
    BST* right;
};

struct BSTTransaksi {
    Transaksi data;
    BSTTransaksi* left;
    BSTTransaksi* right;
};

typedef BST* node;
typedef BST* BinTree;
typedef BSTTransaksi* nodeTransaksi;
typedef BSTTransaksi* TreeTransaksi;
#define Nil nullptr

extern int nomorTransaksiTerakhir;
extern Transaksi riwayatTransaksi[MAX_TRANSAKSI];
extern int jumlahTransaksi;

bool isEmpty(BinTree tree);
bool isEmptyTransaksi(TreeTransaksi tree);
void createTree(BinTree &tree);
node alokasi(Bouquet bouquet);
void dealokasi(node nodeHapus);
void insertNode(BST* &root, node newNode);
BST* search(BST* tree, string namaBouquet);
void searchByData(BinTree tree, string namaBouquet);
node mostLeft(BinTree tree);
node mostRight(BinTree tree);
bool deleteNode(BinTree &tree, string namaBouquet);
void deleteTree(BinTree &tree);
void deleteTreeTransaksi(TreeTransaksi &tree);
int size(BinTree tree);
int height(BinTree tree);

void inorder(BST* tree);
void preorder(BST* tree);
void postorder(BST* tree);
void levelOrder(BST* tree);

int searchByHarga(BST* tree, long minHarga, long maxHarga);  // Modified: returns count
int searchByUkuran(BST* tree, string ukuran);  // Modified: returns count

nodeTransaksi alokasiTransaksi(Transaksi transaksi);
void dealokasiTransaksi(nodeTransaksi node);
void insertTransaksi(TreeTransaksi &tree, nodeTransaksi nodeBaru);
BSTTransaksi* searchTransaksi(TreeTransaksi tree, long totalHarga);
void inorderTransaksi(TreeTransaksi tree);
void displayTransaksi(Transaksi t);
void displayHeaderTransaksi();

bool cekStokCukup(int resepBunga[]);
void kurangiStok(int resepBunga[]);
void orderBouquet(BST* tree, TreeTransaksi &treeTransaksi);

void cekStokGudang();
void restockBunga();
void stokAwal();

int countNodes(BST* tree);
void tampilkanTermurah(BST* tree);
void tampilkanTermahal(BST* tree);
void tampilkanStatistik(BST* tree);

Bouquet inputBouquet();
void displayBouquet(Bouquet bouquet);
void displayHeaderKatalog();
void cetakStruk(Transaksi transaksi);
void cetakPenjualanBungaPerHari();
void katalogBouquet(BinTree &tree);

void tampilkanMenu();
void lihatKatalogBouquet(BST* tree);
void cariBouquet(BST* tree);
void hapusBouquet(BST* &tree);
void menuLihatTransaksi(TreeTransaksi tree);
void laporanStatistik(BST* tree, TreeTransaksi treeTransaksi);
void clearScreen();

#endif