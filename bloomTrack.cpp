#include "bloomtrack.h"
#include <queue>
#include <string>

using namespace std;

int stokBungaMentah[JUMLAH_JENIS_BUNGA];
int nomorTransaksiTerakhir = 0;
Transaksi riwayatTransaksi[MAX_TRANSAKSI];
int jumlahTransaksi = 0;

bool isEmpty(BinTree tree){
    return tree == Nil;
}

bool isEmpty(TreeTransaksi tree){
    return tree == Nil;
}

void createTree(BinTree &tree){
    tree = Nil;
}

node alokasi(Bouquet bouquet) {
    node nodeBaru = new BST;
    nodeBaru->data = bouquet;
    nodeBaru->left = Nil;
    nodeBaru->right = Nil;
    return nodeBaru;
}

void dealokasi(node nodeHapus){
    delete nodeHapus;
}

void insertNode(BST* &root, node newNode) {
    if (root == Nil) {
        root = newNode;
    } else if (newNode->data.namaBouquet < root->data.namaBouquet) {
        insertNode(root->left, newNode);
    } else {
        insertNode(root->right, newNode);
    }
}


BST* search(BST* tree, string namaBouquet) {
    if (tree == Nil || tree->data.namaBouquet == namaBouquet) {
        return tree;
    }
    
    if (namaBouquet < tree->data.namaBouquet) {
        return search(tree->left, namaBouquet);
    } 
    else {
        return search(tree->right, namaBouquet);
    }
}

void searchByData(BinTree tree, string namaBouquet){
    if(isEmpty(tree) == true){
        cout << "Tree kosong!" << endl;
    } else {
        node nodeBantu = tree;
        node parent = Nil;
        bool ketemu = false;
        while(nodeBantu != Nil){
            if(namaBouquet < nodeBantu->data.namaBouquet){
                parent = nodeBantu;
                nodeBantu = nodeBantu->left;
            } else if(namaBouquet > nodeBantu->data.namaBouquet){
                parent = nodeBantu;
                nodeBantu = nodeBantu->right;
            } else if(namaBouquet == nodeBantu->data.namaBouquet){
                ketemu = true;
                break;
            }
        }
        if(ketemu == false){
            cout << "Data tidak ditemukan" << endl;
        } else if(ketemu == true){
            cout << "\nData ditemukan didalam tree!" << endl;
            cout << "Nama Bouquet : " << nodeBantu->data.namaBouquet << endl;
            cout << "Harga        : Rp" << nodeBantu->data.harga << endl;
            cout << "Ukuran       : " << nodeBantu->data.ukuran << endl;

            node sibling = Nil;
            if(parent != Nil){
                cout << "Parent       : " << parent->data.namaBouquet << endl;
                if(parent->left == nodeBantu){
                    sibling = parent->right;
                } else if(parent->right == nodeBantu){
                    sibling = parent->left;
                }
            } else {
                cout << "Parent       : - (node root)"<< endl;
            }

            if(sibling != Nil){
                cout << "Sibling      : " << sibling->data.namaBouquet << endl;
            } else {
                cout << "Sibling      : - " << endl;
            }

            if(nodeBantu->left != Nil){
                cout << "Child kiri   : " << nodeBantu->left->data.namaBouquet << endl;
            } else {
                cout << "Child kiri   : -" << endl;
            }
            if(nodeBantu->right != Nil){
                cout << "Child kanan  : " << nodeBantu->right->data.namaBouquet << endl;
            } else {
                cout << "Child kanan  : -" << endl;
            }
        }
    }
}

node mostLeft(BinTree tree){
    if(tree == Nil)
        return Nil;
    while (tree->left != Nil){
        tree = tree->left;
    }
    return tree;
}

node mostRight(BinTree tree){
    if(tree == Nil)
        return Nil;
    while (tree->right != Nil){
        tree = tree->right;
    }
    return tree;
}

bool deleteNode(BinTree &tree, string namaBouquet) {
    if (tree == Nil) {
        return false;
    } else {
        if (namaBouquet < tree->data.namaBouquet) {
            return deleteNode(tree->left, namaBouquet);
        } else if (namaBouquet > tree->data.namaBouquet) {
            return deleteNode(tree->right, namaBouquet);
        } else {
            if (tree->left == Nil && tree->right == Nil) {
                node tmp = tree;
                tree = Nil;
                dealokasi(tmp);
            }
            else if (tree->left == Nil) {
                node tmp = tree;
                tree = tree->right;
                dealokasi(tmp);
            }
            else if (tree->right == Nil) {
                node tmp = tree;
                tree = tree->left;
                dealokasi(tmp);
            }
            else {
                node successor = mostLeft(tree->right);
                tree->data = successor->data;
                return deleteNode(tree->right, successor->data.namaBouquet);
            }
            return true;
        }
    }
}

nodeTransaksi alokasiTransaksi(Transaksi transaksi) {
    nodeTransaksi nodeBaru = new BSTTransaksi;
    nodeBaru->data = transaksi;
    nodeBaru->left = Nil;
    nodeBaru->right = Nil;
    return nodeBaru;
}

void dealokasiTransaksi(nodeTransaksi node){
    delete node;
}

void insertTransaksi(TreeTransaksi &tree, nodeTransaksi nodeBaru){
    if(tree == Nil){
        tree = nodeBaru;
    } else if(nodeBaru->data.totalHarga < tree->data.totalHarga){
        insertTransaksi(tree->left, nodeBaru);
    } else {
        insertTransaksi(tree->right, nodeBaru);
    }
}

BSTTransaksi* searchTransaksi(TreeTransaksi tree, long totalHarga) {
    if (tree == Nil || tree->data.totalHarga == totalHarga) {
        return tree;
    }
    
    if (totalHarga < tree->data.totalHarga) {
        return searchTransaksi(tree->left, totalHarga);
    } 
    else {
        return searchTransaksi(tree->right, totalHarga);
    }
}

void inorderTransaksi(TreeTransaksi tree) {
    if (tree != Nil) {
        inorderTransaksi(tree->left);
        displayTransaksi(tree->data);
        inorderTransaksi(tree->right);
    }
}

void inorder(BST* tree) {
    if (tree != Nil) {
        inorder(tree->left);
        displayBouquet(tree->data);
        inorder(tree->right);
    }
}

void preorder(BST* tree) {
    if (tree != Nil) {
        displayBouquet(tree->data);
        preorder(tree->left);
        preorder(tree->right);
    }
}

void postorder(BST* tree) {
    if (tree != Nil) {
        postorder(tree->left);
        postorder(tree->right);
        displayBouquet(tree->data);
    }
}

void levelOrder(BST* tree) {
    if (tree == Nil) 
        return;
    
    queue <BST*> q;
    q.push(tree);
    
    while (!q.empty()) {
        BST* current = q.front();
        q.pop();
        
        displayBouquet(current->data);
        
        if (current->left != Nil) {
            q.push(current->left);
        }
        if (current->right != Nil) {
            q.push(current->right);
        }
    }
}

int searchByHarga(BST* tree, long minHarga, long maxHarga) {
    if (tree == Nil) 
        return 0;
    
    int count = 0;
    count += searchByHarga(tree->left, minHarga, maxHarga);
    
    if (tree->data.harga >= minHarga && tree->data.harga <= maxHarga) {
        displayBouquet(tree->data);
        count++;
    }
    
    count += searchByHarga(tree->right, minHarga, maxHarga);
    return count;
}

int searchByUkuran(BST* tree, string ukuran) {
    if (tree == Nil) 
        return 0;
    
    int count = 0;
    count += searchByUkuran(tree->left, ukuran);
    
    if (tree->data.ukuran == ukuran) {
        displayBouquet(tree->data);
        count++;
    }
    
    count += searchByUkuran(tree->right, ukuran);
    return count;
}

bool cekStokCukup(int resepBunga[]) {
    for (int i = 0; i < JUMLAH_JENIS_BUNGA; i++) {
        if (stokBungaMentah[i] < resepBunga[i]) {
            cout << "Stok " << NAMA_BUNGA[i] << " tidak cukup!\n";
            cout << "   Dibutuhkan: " << resepBunga[i] << ", Tersedia: " << stokBungaMentah[i] << "\n";
            return false;
        }
    }
    return true;
}

void kurangiStok(int resepBunga[]) {
    for (int i = 0; i < JUMLAH_JENIS_BUNGA; i++) {
        stokBungaMentah[i] -= resepBunga[i];
    }
}

void beliBouquet(BST* tree, TreeTransaksi &treeTransaksi) {
    if (tree == Nil) {
        cout << "Katalog masih kosong!\n";
        return;
    }
    
    cout << "\n=== TRANSAKSI PENJUALAN ===\n";
    
    cout << "Nama Pembeli: ";
    string namaPembeli;
    getline(cin, namaPembeli);
    
    ItemTransaksi keranjang[MAX_ITEM_TRANSAKSI];
    int resepKeranjang[MAX_ITEM_TRANSAKSI][JUMLAH_JENIS_BUNGA];
    int jumlahItemBeli = 0;
    long totalBelanja = 0;
    
    char lanjut;
    do {
        if (jumlahItemBeli >= MAX_ITEM_TRANSAKSI) {
            cout << "\nKeranjang penuh! Maksimal " << MAX_ITEM_TRANSAKSI << " bouquet per transaksi.\n";
            break;
        }
        
        cout << "\nNama Bouquet yang ingin dibeli: ";
        string nama;
        getline(cin, nama);
        
        BST* node = search(tree, nama);
        
        if (node == Nil) {
            cout << "Bouquet '" << nama << "' tidak ditemukan di katalog!\n";
            cout << "Ingin coba lagi? (y/n): ";
            cin >> lanjut;
            cin.ignore();
            if (lanjut == 'y' || lanjut == 'Y') continue;
            else break;
        }
        
        cout << "\n" << string(60, '=') << "\n";
        cout << "DETAIL BOUQUET\n";
        cout << string(60, '=') << "\n";
        cout << "Nama Bouquet      : " << node->data.namaBouquet << "\n";
        cout << "Harga             : Rp " << node->data.harga << "\n";
        cout << "Ukuran            : " << node->data.ukuran << "\n";
        cout << "\nKomposisi Bunga:\n";
        for (int i = 0; i < JUMLAH_JENIS_BUNGA; i++) {
            if (node->data.resepBunga[i] > 0) {
                cout << "  - " << NAMA_BUNGA[i] << ": " << node->data.resepBunga[i] << " tangkai\n";
            }
        }
        cout << string(60, '=') << "\n";
        
        if (!cekStokCukup(node->data.resepBunga)) {
            cout << "\nStok tidak mencukupi untuk bouquet ini.\n";
            cout << "Ingin pilih bouquet lain? (y/n): ";
            cin >> lanjut;
            cin.ignore();
            if (lanjut == 'y' || lanjut == 'Y') continue;
            else break;
        }
        
        cout << "\nTambahkan ke keranjang? (y/n): ";
        char tambah;
        cin >> tambah;
        cin.ignore();
        
        if (tambah == 'y' || tambah == 'Y') {
            kurangiStok(node->data.resepBunga);
            
            keranjang[jumlahItemBeli].namaBouquet = node->data.namaBouquet;
            keranjang[jumlahItemBeli].harga = node->data.harga;
            keranjang[jumlahItemBeli].ukuran = node->data.ukuran;
            
            for (int i = 0; i < JUMLAH_JENIS_BUNGA; i++) {
                resepKeranjang[jumlahItemBeli][i] = node->data.resepBunga[i];
            }
            
            totalBelanja += node->data.harga;
            jumlahItemBeli++;
            
            cout << "\n✓ Bouquet ditambahkan ke keranjang!\n";
            cout << "Total item: " << jumlahItemBeli << " | Total: Rp " << totalBelanja << "\n";
        }
        
        if (jumlahItemBeli < MAX_ITEM_TRANSAKSI) {
            cout << "\nBeli bouquet lain? (y/n): ";
            cin >> lanjut;
            cin.ignore();
        } else {
            break;
        }
        
    } while (lanjut == 'y' || lanjut == 'Y');
    
    if (jumlahItemBeli == 0) {
        cout << "\nTidak ada transaksi yang dilakukan.\n";
        return;
    }
    
    cout << "\n" << string(60, '=') << "\n";
    cout << "RINGKASAN BELANJA\n";
    cout << string(60, '=') << "\n";
    cout << "Pembeli: " << namaPembeli << "\n";
    cout << "Jumlah Item: " << jumlahItemBeli << "\n";
    for (int i = 0; i < jumlahItemBeli; i++) {
        cout << (i+1) << ". " << keranjang[i].namaBouquet 
             << " (" << keranjang[i].ukuran << ") - Rp " << keranjang[i].harga << "\n";
    }
    cout << string(60, '-') << "\n";
    cout << "TOTAL: Rp " << totalBelanja << "\n";
    cout << string(60, '=') << "\n";
    
    cout << "\nProses pembayaran? (y/n): ";
    char bayar;
    cin >> bayar;
    cin.ignore();
    
    if (bayar != 'y' && bayar != 'Y') {
        cout << "\nMengembalikan stok...\n";
        for (int i = 0; i < jumlahItemBeli; i++) {
            for (int j = 0; j < JUMLAH_JENIS_BUNGA; j++) {
                stokBungaMentah[j] += resepKeranjang[i][j];
            }
        }
        cout << "Transaksi dibatalkan. Stok dikembalikan.\n";
        return;
    }
    
    nomorTransaksiTerakhir++;
    
    Transaksi t;
    t.nomorTransaksi = nomorTransaksiTerakhir;
    t.namaPembeli = namaPembeli;
    t.jumlahItem = jumlahItemBeli;
    t.totalHarga = totalBelanja;
    
    for (int i = 0; i < jumlahItemBeli; i++) {
        t.items[i] = keranjang[i];
    }
    
    nodeTransaksi nodeTransaksiBaru = alokasiTransaksi(t);
    insertTransaksi(treeTransaksi, nodeTransaksiBaru);
    
    cout << "\n✓ TRANSAKSI BERHASIL!\n";
    cout << "Nomor Transaksi: #" << t.nomorTransaksi << "\n";
    
    cetakStruk(t);
}

void stokAwal() {
    for (int i = 0; i < JUMLAH_JENIS_BUNGA; i++) {
        stokBungaMentah[i] = 50;
    }
}

void cekStokGudang() {
    cout << "\n=== STOK GUDANG BUNGA MENTAH ===\n";
    cout << string(40, '=') << "\n";
    for (int i = 0; i < JUMLAH_JENIS_BUNGA; i++) {
        cout << NAMA_BUNGA[i] << ": " << stokBungaMentah[i] << " tangkai\n";
    }
    cout << string(40, '=') << "\n";
}

void restockBunga() {
    cout << "\n=== RESTOCK BUNGA ===\n";
    cout << "Pilih jenis bunga:\n";
    for (int i = 0; i < JUMLAH_JENIS_BUNGA; i++) {
        cout << i + 1 << ". " << NAMA_BUNGA[i] << " (Stok: " << stokBungaMentah[i] << ")\n";
    }
    cout << "Pilihan (1-5): ";
    
    int pilihan;
    cin >> pilihan;
    cin.ignore();
    
    if (pilihan < 1 || pilihan > JUMLAH_JENIS_BUNGA) {
        cout << "Pilihan tidak valid!\n";
        return;
    }
    
    cout << "Jumlah yang ingin ditambahkan: ";
    int jumlah;
    cin >> jumlah;
    cin.ignore();
    
    if (jumlah <= 0) {
        cout << "Jumlah harus positif!\n";
        return;
    }
    
    stokBungaMentah[pilihan - 1] += jumlah;
    cout << "Berhasil menambah " << jumlah << " tangkai " << NAMA_BUNGA[pilihan - 1] << "!\n";
    cout << "   Stok sekarang: " << stokBungaMentah[pilihan - 1] << " tangkai\n";
}

int countNodes(BST* tree) {
    if (tree == Nil) 
        return 0;
    return 1 + countNodes(tree->left) + countNodes(tree->right);
}

void deleteTree(BinTree &tree){
    if(tree == Nil){
        return;
    } else {
        deleteTree(tree->left);
        deleteTree(tree->right);
        dealokasi(tree);
        tree = Nil;
    }
}

void deleteTreeTransaksi(TreeTransaksi &tree){
    if(tree == Nil){
        return;
    } else {
        deleteTreeTransaksi(tree->left);
        deleteTreeTransaksi(tree->right);
        dealokasiTransaksi(tree);
        tree = Nil;
    }
}

int size(BinTree tree){
    if(isEmpty(tree) == true){
        return 0;
    } else {
        return 1 + size(tree->left) + size(tree->right);
    }
}

int height(BinTree tree){
    if(isEmpty(tree) == true){
        return -1;
    } else {
        int hl = height(tree->left);
        int hr = height(tree->right);
        int maxHeight;
        if (hl > hr){
            maxHeight = hl;
        } else {
            maxHeight = hr;
        }
        return 1 + maxHeight;
    }
}

void tampilkanTermurah(BST* tree) {
    if (tree == Nil) 
        return;
    
    static long long minHarga = 9999999999LL;
    static Bouquet bouquetTermurah;
    static bool found = false;
    
    if (!found) {
        minHarga = 9999999999LL;
    }
    
    tampilkanTermurah(tree->left);
    
    if (tree->data.harga < minHarga) {
        minHarga = tree->data.harga;
        bouquetTermurah = tree->data;
        found = true;
    }
    
    tampilkanTermurah(tree->right);
    
    if (tree->left == Nil && tree->right == Nil && found) {
        cout << "\nBOUQUET TERMURAH:\n";
        displayBouquet(bouquetTermurah);
        found = false;
    }
}

void tampilkanTermahal(BST* tree) {
    if (tree == Nil) 
        return;
    
    static long maxHarga = 0;
    static Bouquet bouquetTermahal;
    static bool found = false;
    
    if (!found) {
        maxHarga = 0;
    }
    
    tampilkanTermahal(tree->left);
    
    if (tree->data.harga > maxHarga) {
        maxHarga = tree->data.harga;
        bouquetTermahal = tree->data;
        found = true;
    }
    
    tampilkanTermahal(tree->right);
    
    if (tree->left == Nil && tree->right == Nil && found) {
        cout << "\nBOUQUET TERMAHAL:\n";
        displayBouquet(bouquetTermahal);
        found = false;
    }
}

void tampilkanStatistik(BST* tree) {
    if (tree == Nil) {
        cout << "Belum ada data bouquet!\n";
        return;
    }
    
    cout << "\n=== STATISTIK BLOOMTRACK ===\n";
    cout << "Total Jenis Bouquet: " << countNodes(tree) << "\n";
    
    tampilkanTermurah(tree);
    tampilkanTermahal(tree);
}

void katalogBouquet(BinTree &tree) {
    Bouquet b1;
    b1.namaBouquet = "Romantis";
    b1.harga = 150000;
    b1.ukuran = "M";
    b1.resepBunga[0] = 5; 
    b1.resepBunga[1] = 3; 
    b1.resepBunga[2] = 0;
    b1.resepBunga[3] = 0;
    b1.resepBunga[4] = 0;
    
    Bouquet b2;
    b2.namaBouquet = "Cerah";
    b2.harga = 120000;
    b2.ukuran = "L";
    b2.resepBunga[0] = 0;
    b2.resepBunga[1] = 4; 
    b2.resepBunga[2] = 3;
    b2.resepBunga[3] = 2;
    b2.resepBunga[4] = 2;
    
    Bouquet b3;
    b3.namaBouquet = "Elegan";
    b3.harga = 200000;
    b3.ukuran = "L";
    b3.resepBunga[0] = 3;
    b3.resepBunga[1] = 5;
    b3.resepBunga[2] = 2; 
    b3.resepBunga[3] = 0;
    b3.resepBunga[4] = 1; 
    
    Bouquet b4;
    b4.namaBouquet = "Sederhana";
    b4.harga = 75000;
    b4.ukuran = "S";
    b4.resepBunga[0] = 2; 
    b4.resepBunga[1] = 2; 
    b4.resepBunga[2] = 1; 
    b4.resepBunga[3] = 3; 
    b4.resepBunga[4] = 0;
    
    insertNode(tree, alokasi(b1));
    insertNode(tree, alokasi(b2));
    insertNode(tree, alokasi(b3));
    insertNode(tree, alokasi(b4));
}

Bouquet inputBouquet() {
    Bouquet b;
    
    cout << "\n=== INPUT BOUQUET BARU ===\n";
    cout << "Nama Bouquet: ";
    getline(cin, b.namaBouquet);
    
    cout << "Harga (Rp): ";
    cin >> b.harga;
    cin.ignore();
    
    cout << "Ukuran (S/M/L): ";
    getline(cin, b.ukuran);
    
    cout << "\nResep Bunga (jumlah tangkai yang dibutuhkan):\n";
    for (int i = 0; i < JUMLAH_JENIS_BUNGA; i++) {
        cout << "  " << NAMA_BUNGA[i] << ": ";
        cin >> b.resepBunga[i];
    }
    cin.ignore();
    
    return b;
}

void displayHeaderKatalog() {
    cout << "\n" << string(90, '=') << "\n";
    cout << "NAMA BOUQUET        HARGA       UKURAN  RESEP\n";
    cout << string(90, '=') << "\n";
}

void displayBouquet(Bouquet bouquet) {
    cout << bouquet.namaBouquet;
    for (int i = bouquet.namaBouquet.length(); i < 20; i++) cout << " ";
    
    cout << "Rp" << bouquet.harga;
    int digitCount = to_string(bouquet.harga).length();
    for (int i = digitCount; i < 10; i++) cout << " ";
    
    cout << bouquet.ukuran;
    for (int i = bouquet.ukuran.length(); i < 8; i++) cout << " ";
    
    cout << "[";
    bool first = true;
    for (int i = 0; i < JUMLAH_JENIS_BUNGA; i++) {
        if (bouquet.resepBunga[i] > 0) {
            if (!first) 
                cout << ", ";
            cout << NAMA_BUNGA[i] << ":" << bouquet.resepBunga[i];
            first = false;
        }
    }
    cout << "]\n";
}

void displayHeaderTransaksi() {
    cout << "\n" << string(90, '=') << "\n";
    cout << "NO.   NAMA PEMBELI       ITEM       TOTAL HARGA\n";
    cout << string(90, '=') << "\n";
}

void displayTransaksi(Transaksi t) {
    cout << "#" << t.nomorTransaksi;
    string noStr = "#" + to_string(t.nomorTransaksi);
    for (int i = noStr.length(); i < 6; i++) cout << " ";
    
    cout << t.namaPembeli;
    for (int i = t.namaPembeli.length(); i < 20; i++) cout << " ";
    
    cout << t.jumlahItem << " item";
    string itemStr = to_string(t.jumlahItem) + " item";
    for (int i = itemStr.length(); i < 11; i++) cout << " ";
    
    cout << "Rp " << t.totalHarga << "\n";
}

void cetakStruk(Transaksi transaksi) {
    cout << "\n" << string(60, '=') << "\n";
    cout << "              BLOOMTRACK FLORIST  \n";
    cout << "               STRUK PEMBELIAN\n";
    cout << string(60, '=') << "\n";
    cout << "No. Transaksi : #" << transaksi.nomorTransaksi << "\n";
    cout << "Pembeli       : " << transaksi.namaPembeli << "\n";
    cout << string(60, '-') << "\n";
    cout << "Item yang dibeli:\n";
    for (int i = 0; i < transaksi.jumlahItem; i++) {
        cout << "  " << (i+1) << ". " << transaksi.items[i].namaBouquet 
             << " (" << transaksi.items[i].ukuran << ")\n";
        cout << "     Rp " << transaksi.items[i].harga << "\n";
    }
    cout << string(60, '-') << "\n";
    cout << "Total Harga   : Rp " << transaksi.totalHarga << "\n";
    cout << string(60, '=') << "\n";
    cout << "      Terima kasih atas pembelian Anda!\n";
    cout << string(60, '=') << "\n";
}

void cetakPenjualanBungaPerHari() {
    cout << "\n";
    cout << "========== PENJUALAN BUNGA PER HARI ==========\n";
    cout << string(70, '=') << "\n";
    cout << "No. | Nama Bunga     | Stok Tangkai | Harga/Tangkai | Total Harian\n";
    cout << string(70, '=') << "\n";
    
    long totalPenjualanHarian = 0;
    
    for (int i = 0; i < JUMLAH_JENIS_BUNGA; i++) {
        long hargaPerTangkai = HARGA_BUNGA[i];
        long totalHarian = (long)stokBungaMentah[i] * hargaPerTangkai;
        totalPenjualanHarian += totalHarian;
        
        cout << (i + 1) << ".  | ";
        cout << NAMA_BUNGA[i];
        cout << string(14 - NAMA_BUNGA[i].length(), ' ') << "| ";
        cout << stokBungaMentah[i] << " tangkai      | Rp";
        cout << hargaPerTangkai << "    | Rp";
        cout << totalHarian << "\n";
    }
    
    cout << string(70, '=') << "\n";
    cout << "TOTAL POTENSI PENJUALAN HARI INI: Rp" << totalPenjualanHarian << "\n";
    cout << "Harga per tangkai: Mawar Rp5.000, Lily Rp7.000, Tulip Rp6.000, Daisy Rp4.500, Sunflower Rp8.000\n";
    cout << string(70, '=') << "\n";
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void tampilkanMenu() {
    cout << "\n";
    cout << "================================================\n";
    cout << "         BLOOMTRACK - FLORIST SYSTEM        \n";
    cout << "================================================\n";
    cout << "  1. Tambah Bouquet Baru\n";
    cout << "  2. Lihat Katalog\n";
    cout << "  3. Cari Bouquet\n";
    cout << "  4. Transaksi Penjualan\n";
    cout << "  5. Hapus Bouquet\n";
    cout << "  6. Manajemen Gudang\n";
    cout << "  7. Laporan Statistik\n";
    cout << "  0. Keluar\n";
    cout << "================================================\n";
    cout << "Pilihan: ";
}

void menuLihatKatalog(BST* tree) {
    if (tree == Nil) {
        cout << "Katalog masih kosong!\n";
        return;
    }
    
    clearScreen();
    cout << "\n=== KATALOG BOUQUET ===\n";
    cout << "1. Inorder (Urut A-Z)\n";
    cout << "2. Preorder\n";
    cout << "3. Postorder\n";
    cout << "4. Level Order\n";
    cout << "Pilihan: ";
    
    int pilihan;
    cin >> pilihan;
    cin.ignore();
    
    displayHeaderKatalog();
    
    switch (pilihan) {
        case 1:
            cout << "[INORDER TRAVERSAL]\n";
            inorder(tree);
            break;
        case 2:
            cout << "[PREORDER TRAVERSAL]\n";
            preorder(tree);
            break;
        case 3:
            cout << "[POSTORDER TRAVERSAL]\n";
            postorder(tree);
            break;
        case 4:
            cout << "[LEVEL ORDER TRAVERSAL]\n";
            levelOrder(tree);
            break;
        default:
            cout << "Pilihan tidak valid!\n";
    }
}

void menuCariBouquet(BST* tree) {
    if (tree == Nil) {
        cout << "Katalog masih kosong!\n";
        return;
    }
    
    clearScreen();
    cout << "\n=== CARI BOUQUET ===\n";
    cout << "1. Berdasarkan Nama\n";
    cout << "2. Berdasarkan Range Harga\n";
    cout << "3. Berdasarkan Ukuran\n";
    cout << "Pilihan: ";
    
    int pilihan;
    cin >> pilihan;
    cin.ignore();
    
    switch (pilihan) {
        case 1: {
            cout << "Nama Bouquet: ";
            string nama;
            getline(cin, nama);
            
            // Validasi input tidak kosong
            if (nama.empty()) {
                cout << endl << "Nama bouquet tidak boleh kosong!\n";
                break;
            }
            
            BST* hasil = search(tree, nama);
            if (hasil != Nil) {
                cout << "\n✓ Bouquet ditemukan:\n";
                displayHeaderKatalog();
                displayBouquet(hasil->data);
            } 
            else {
                cout << endl << "Bouquet dengan nama '" << nama 
                     << "' tidak ada dalam katalog.\n";
            }
            break;
        }
        case 2: {
            long min, max;
            cout << "Harga Minimum (Rp): ";
            
            // Validasi input harga minimum
            if (!(cin >> min)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "\nHarga minimum harus berupa angka!\n";
                break;
            }
            
            // Validasi nilai logis harga minimum
            if (min <= 0) {
                cin.ignore(1000, '\n');
                cout << "\nHarga minimum harus lebih dari 0!\n";
                break;
            }
            
            cout << "Harga Maksimum (Rp): ";
            
            // Validasi input harga maksimum
            if (!(cin >> max)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "\nHarga maksimum harus berupa angka!\n";
                break;
            }
            cin.ignore();
            
            // Validasi nilai logis harga maksimum
            if (max <= 0) {
                cout << "\nHarga maksimum harus lebih dari 0!\n";
                break;
            }
            
            if (max < min) {
                cout << "\nHarga maksimum tidak boleh kurang dari harga minimum!\n";
                break;
            }
            
            cout << "\nMencari bouquet dengan harga Rp" << min << " - Rp" << max << "...\n";
            cout << "\nHasil pencarian:\n";
            displayHeaderKatalog();
            int resultCount = searchByHarga(tree, min, max);
            
            if (resultCount == 0) {
                cout << "\nTidak ada bouquet dalam range harga Rp" 
                     << min << " - Rp" << max << ".\n";
            } else {
                cout << "\nDitemukan " << resultCount << " bouquet(s) dalam range harga tersebut.\n";
            }
            break;
        }
        case 3: {
            cout << "Ukuran (S/M/L): ";
            string ukuran;
            getline(cin, ukuran);
            
            if (ukuran.empty()) {
                cout << "\nUkuran tidak boleh kosong!\n";
                break;
            }
            
            if (ukuran != "S" && ukuran != "M" && ukuran != "L" && 
                ukuran != "s" && ukuran != "m" && ukuran != "l") {
                cout << "\nUkuran harus S, M, atau L!\n";
                break;
            }
            
            cout << "\nMencari bouquet ukuran " << ukuran << "...\n";
            cout << "\nHasil pencarian:\n";
            displayHeaderKatalog();
            int resultCount = searchByUkuran(tree, ukuran);
            
            if (resultCount == 0) {
                cout << "\nTidak ada bouquet dengan ukuran " << ukuran << ".\n";
            } else {
                cout << "\nDitemukan " << resultCount << " bouquet(s) dengan ukuran tersebut.\n";
            }
            break;
        }
        default:
            cout << "\nPilihan harus 1, 2, atau 3!\n";
    }
}

void menuHapusBouquet(BST* &tree) {
    if (tree == Nil) {
        cout << "Katalog masih kosong!\n";
        return;
    }
    
    cout << "\n=== HAPUS BOUQUET ===\n";
    cout << "Nama Bouquet yang ingin dihapus: ";
    string nama;
    getline(cin, nama);
    
    BST* cek = search(tree, nama);
    if (cek == Nil) {
        cout << "Bouquet '" << nama << "' tidak ditemukan!\n";
        return;
    }
    
    cout << "\nBouquet yang akan dihapus:\n";
    displayHeaderKatalog();
    displayBouquet(cek->data);
    
    cout << "\nApakah Anda yakin ingin menghapus bouquet ini? (y/n): ";
    char konfirmasi;
    cin >> konfirmasi;
    cin.ignore();
    
    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        if (deleteNode(tree, nama)) {
            cout << "\nBouquet '" << nama << "' berhasil dihapus!\n";
        } else {
            cout << "\nGagal menghapus bouquet!\n";
        }
    } else {
        cout << "\nPenghapusan dibatalkan.\n";
    }
}

void menuLihatTransaksi(TreeTransaksi tree) {
    if (tree == Nil) {
        cout << "Belum ada transaksi!\n";
        return;
    }
    
    clearScreen();
    cout << "\n=== RIWAYAT TRANSAKSI (Urut berdasarkan Total Harga) ===\n";
    displayHeaderTransaksi();
    inorderTransaksi(tree);
    cout << string(90, '=') << "\n";
}

void menuLaporanStatistik(BST* tree, TreeTransaksi treeTransaksi) {
    clearScreen();
    
    cout << "\n";
    cout << "================================================\n";
    cout << "        LAPORAN PENJUALAN BLOOMTRACK\n";
    cout << "================================================\n";
    
    // 1. PENJUALAN BUNGA PER HARI
    cout << "\n[1] PENJUALAN BUNGA PER HARI\n";
    cout << string(70, '=') << "\n";
    cout << "No. | Nama Bunga     | Stok Tangkai | Harga/Tangkai | Total Harian\n";
    cout << string(70, '=') << "\n";
    
    long totalPenjualanHarian = 0;
    
    for (int i = 0; i < JUMLAH_JENIS_BUNGA; i++) {
        long hargaPerTangkai = HARGA_BUNGA[i];
        long totalHarian = (long)stokBungaMentah[i] * hargaPerTangkai;
        totalPenjualanHarian += totalHarian;
        
        cout << (i + 1) << ".  | ";
        cout << NAMA_BUNGA[i];
        cout << string(14 - NAMA_BUNGA[i].length(), ' ') << "| ";
        cout << stokBungaMentah[i] << " tangkai      | Rp";
        cout << hargaPerTangkai << "    | Rp";
        cout << totalHarian << "\n";
    }
    
    cout << string(70, '=') << "\n";
    cout << "TOTAL POTENSI PENJUALAN HARI INI: Rp" << totalPenjualanHarian << "\n";
    cout << "Harga per tangkai: Mawar Rp5.000, Lily Rp7.000, Tulip Rp6.000, Daisy Rp4.500, Sunflower Rp8.000\n";
    cout << string(70, '=') << "\n";
    
    // 2. RIWAYAT TRANSAKSI
    cout << "\n[2] RIWAYAT TRANSAKSI PENJUALAN\n";
    cout << string(100, '=') << "\n";
    
    if (jumlahTransaksi == 0) {
        cout << "Belum ada transaksi penjualan.\n";
    } else {
        cout << "No. | Nama Pembeli       | Item Bouquet         | Total Harga\n";
        cout << string(100, '=') << "\n";
        for (int i = 0; i < jumlahTransaksi; i++) {
            cout << riwayatTransaksi[i].nomorTransaksi << ".  | ";
            cout << riwayatTransaksi[i].namaPembeli;
            cout << string(18 - riwayatTransaksi[i].namaPembeli.length(), ' ') << "| ";
            if (riwayatTransaksi[i].jumlahItem > 0) {
                cout << riwayatTransaksi[i].items[0].namaBouquet;
                cout << string(20 - riwayatTransaksi[i].items[0].namaBouquet.length(), ' ') << "| Rp";
                cout << riwayatTransaksi[i].totalHarga << "\n";
            }
        }
    }
    cout << string(100, '=') << "\n";
}