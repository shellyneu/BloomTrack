#include "bloomtrack.h"
#include <queue>
#include <string>

using namespace std;

int stokBungaMentah[JUMLAH_JENIS_BUNGA];
Transaksi riwayatTransaksi[MAX_TRANSAKSI];
int jumlahTransaksi = 0;

bool isEmpty(BinTree tree){
    if(tree == Nil){
        return true;
    } else {
        return false;
    }
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
            cout << "Warna        : " << nodeBantu->data.warnaDominan << endl;

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

void searchByHarga(BST* tree, long minHarga, long maxHarga) {
    if (tree == Nil) 
        return;
    
    searchByHarga(tree->left, minHarga, maxHarga);
    
    if (tree->data.harga >= minHarga && tree->data.harga <= maxHarga) {
        displayBouquet(tree->data);
    }
    
    searchByHarga(tree->right, minHarga, maxHarga);
}

void searchByUkuran(BST* tree, string ukuran) {
    if (tree == Nil) 
        return;
    
    searchByUkuran(tree->left, ukuran);
    
    if (tree->data.ukuran == ukuran) {
        displayBouquet(tree->data);
    }
    
    searchByUkuran(tree->right, ukuran);
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

void beliBouquet(BST* tree) {
    if (tree == Nil) {
        cout << "Katalog masih kosong!\n";
        return;
    }
    
    cout << "\n=== TRANSAKSI PENJUALAN ===\n";
    
    cout << "Nama Pembeli: ";
    string namaPembeli;
    getline(cin, namaPembeli);
    
    cout << "Nama Bouquet yang ingin dibeli: ";
    string nama;
    getline(cin, nama);
    
    BST* node = search(tree, nama);
    
    if (node == Nil) {
        cout << "Bouquet '" << nama << "' tidak ditemukan di katalog!\n";
        return;
    }
    
    cout << "\n" << string(60, '=') << "\n";
    cout << "DETAIL BOUQUET YANG DIPILIH\n";
    cout << string(60, '=') << "\n";
    cout << "Nama Bouquet      : " << node->data.namaBouquet << "\n";
    cout << "Harga             : Rp " << node->data.harga << "\n";
    cout << "Ukuran            : " << node->data.ukuran << "\n";
    cout << "Warna Dominan     : " << node->data.warnaDominan << "\n";
    cout << "\nKomposisi Bunga:\n";
    for (int i = 0; i < JUMLAH_JENIS_BUNGA; i++) {
        if (node->data.resepBunga[i] > 0) {
            cout << "  - " << NAMA_BUNGA[i] << ": " << node->data.resepBunga[i] << " tangkai\n";
        }
    }
    cout << string(60, '=') << "\n";
    
    cout << "\nApakah Anda yakin ingin membeli bouquet ini? (y/n): ";
    char konfirmasi;
    cin >> konfirmasi;
    cin.ignore();
    
    if (konfirmasi != 'y' && konfirmasi != 'Y') {
        cout << "\nTransaksi dibatalkan.\n";
        return;
    }
    
    cout << "\nMengecek ketersediaan bahan...\n";
    
    if (cekStokCukup(node->data.resepBunga)) {
        kurangiStok(node->data.resepBunga);
        cout << "\nTRANSAKSI BERHASIL!\n";
        
        // Simpan ke riwayat transaksi
        if (jumlahTransaksi < MAX_TRANSAKSI) {
            Transaksi t;
            t.namaPembeli = namaPembeli;
            t.namaBouquet = node->data.namaBouquet;
            t.hargaBouquet = node->data.harga;
            t.ukuran = node->data.ukuran;
            t.warnaDominan = node->data.warnaDominan;
            t.nomorTransaksi = jumlahTransaksi + 1;
            
            for (int i = 0; i < JUMLAH_JENIS_BUNGA; i++) {
                t.resepBunga[i] = node->data.resepBunga[i];
            }
            
            riwayatTransaksi[jumlahTransaksi] = t;
            jumlahTransaksi++;
        }
        
        cetakStruk(node->data, namaPembeli);
    } 
    else {
        cout << "\nTransaksi gagal. Stok bahan tidak mencukupi.\n";
    }
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
    // Lily = 1, Tulip = 2, Daisy = 3, Sunflower = 4
    Bouquet b1;
    b1.namaBouquet = "Bouquet Romantis";
    b1.harga = 150000;
    b1.ukuran = "M";
    b1.warnaDominan = "Merah";
    b1.resepBunga[0] = 5; 
    b1.resepBunga[1] = 3; 
    b1.resepBunga[2] = 0;
    b1.resepBunga[3] = 0;
    b1.resepBunga[4] = 0;
    
    Bouquet b2;
    b2.namaBouquet = "Bouquet Cerah";
    b2.harga = 120000;
    b2.ukuran = "L";
    b2.warnaDominan = "Kuning";
    b2.resepBunga[0] = 0;
    b2.resepBunga[1] = 4; 
    b2.resepBunga[2] = 3;
    b2.resepBunga[3] = 2;
    b2.resepBunga[4] = 2;
    
    Bouquet b3;
    b3.namaBouquet = "Bouquet Elegan";
    b3.harga = 200000;
    b3.ukuran = "L";
    b3.warnaDominan = "Putih";
    b3.resepBunga[0] = 3;
    b3.resepBunga[1] = 5;
    b3.resepBunga[2] = 2; 
    b3.resepBunga[3] = 0;
    b3.resepBunga[4] = 1; 
    
    Bouquet b4;
    b4.namaBouquet = "Bouquet Sederhana";
    b4.harga = 75000;
    b4.ukuran = "S";
    b4.warnaDominan = "Pink";
    b4.resepBunga[0] = 2; 
    b4.resepBunga[1] = 2; 
    b4.resepBunga[2] = 1; 
    b4.resepBunga[3] = 3; 
    b4.resepBunga[4] = 0;
    
    insertNode(tree, alokasi(b1));
    insertNode(tree, alokasi(b2));
    insertNode(tree, alokasi(b3));
    insertNode(tree, alokasi(b4));
    
    cout << "Katalog default berhasil dimuat (4 bouquet)\n\n";
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
    
    cout << "Warna Dominan: ";
    getline(cin, b.warnaDominan);
    
    cout << "\nResep Bunga (jumlah tangkai yang dibutuhkan):\n";
    for (int i = 0; i < JUMLAH_JENIS_BUNGA; i++) {
        cout << "  " << NAMA_BUNGA[i] << ": ";
        cin >> b.resepBunga[i];
    }
    cin.ignore();
    
    return b;
}

void displayHeaderKatalog() {
    cout << "\n" << string(100, '=') << "\n";
    cout << "NAMA BOUQUET        HARGA       UKURAN  WARNA          RESEP\n";
    cout << string(100, '=') << "\n";
}

void displayBouquet(Bouquet bouquet) {
    cout << bouquet.namaBouquet;
    for (int i = bouquet.namaBouquet.length(); i < 20; i++) cout << " ";
    
    cout << "Rp" << bouquet.harga;
    int digitCount = to_string(bouquet.harga).length();
    for (int i = digitCount; i < 10; i++) cout << " ";
    
    cout << bouquet.ukuran;
    for (int i = bouquet.ukuran.length(); i < 8; i++) cout << " ";
    
    cout << bouquet.warnaDominan;
    for (int i = bouquet.warnaDominan.length(); i < 15; i++) cout << " ";
    
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

void cetakStruk(Bouquet bouquet, string namaPembeli) {
    cout << "\n" << string(50, '=') << "\n";
    cout << "             BLOOMTRACK FLORIST  \n";
    cout << "              STRUK PEMBELIAN\n";
    cout << string(50, '=') << "\n";
    cout << "No. Transaksi: " << jumlahTransaksi << "\n";
    cout << "Pembeli      : " << namaPembeli << "\n";
    cout << "Bouquet      : " << bouquet.namaBouquet << "\n";
    cout << "Ukuran       : " << bouquet.ukuran << "\n";
    cout << "Warna        : " << bouquet.warnaDominan << "\n";
    cout << "Harga        : Rp " << bouquet.harga << "\n";
    cout << string(50, '-') << "\n";
    cout << "Bahan yang digunakan:\n";
    for (int i = 0; i < JUMLAH_JENIS_BUNGA; i++) {
        if (bouquet.resepBunga[i] > 0) {
            cout << "  - " << NAMA_BUNGA[i] << ": " << bouquet.resepBunga[i] << " tangkai\n";
        }
    }
    cout << string(50, '=') << "\n";
    cout << "    Terima kasih atas pembelian Anda!\n";
    cout << string(50, '=') << "\n";
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
            
            BST* hasil = search(tree, nama);
            if (hasil != Nil) {
                cout << "\nBouquet ditemukan:\n";
                displayHeaderKatalog();
                displayBouquet(hasil->data);
            } 
            else {
                cout << "Bouquet tidak ditemukan!\n";
            }
            break;
        }
        case 2: {
            long min, max;
            cout << "Harga Minimum (Rp): ";
            cin >> min;
            cout << "Harga Maksimum (Rp): ";
            cin >> max;
            cin.ignore();
            
            cout << "\nHasil pencarian:\n";
            displayHeaderKatalog();
            searchByHarga(tree, min, max);
            break;
        }
        case 3: {
            cout << "Ukuran (S/M/L): ";
            string ukuran;
            getline(cin, ukuran);
            
            cout << "\nHasil pencarian:\n";
            displayHeaderKatalog();
            searchByUkuran(tree, ukuran);
            break;
        }
        default:
            cout << "Pilihan tidak valid!\n";
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

void menuLaporanStatistik() {
    cout << "\n=== MENU LAPORAN STATISTIK ===\n";
    cout << "1. Penjualan Bunga Per Hari\n";
    cout << "2. Lihat Stok Gudang\n";
    cout << "3. Tampilkan Statistik\n";
    cout << "0. Kembali ke Menu Utama\n";
    cout << "Pilihan: ";
    
    int pilihan;
    cin >> pilihan;
    cin.ignore();
    
    switch (pilihan) {
        case 1: {
            clearScreen();
            cetakPenjualanBungaPerHari();
            break;
        }
        case 2: {
            clearScreen();
            cekStokGudang();
            break;
        }
        case 3: {
            clearScreen();
            cout << "FITUR BELUM DIIMPLEMENTASIKAN\n";
            break;
        }
        case 0: {
            break;
        }
        default:
            cout << "Pilihan tidak valid!\n";
    }
}