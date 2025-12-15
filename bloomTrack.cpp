#include "bloomtrack.h"
#include <queue>
#include <iomanip>
#include <climits>  

int stokBungaMentah[JUMLAH_JENIS_BUNGA];

BST* buatNode(Bouquet bouquet) {
    BST* nodeBaru = new BST;
    nodeBaru->data = bouquet;
    nodeBaru->left = nullptr;
    nodeBaru->right = nullptr;
    return nodeBaru;
}

BST* insert(BST* tree, Bouquet bouquet) {
    if (tree == nullptr) {
        return buatNode(bouquet);
    }
    
    if (bouquet.namaBouquet < tree->data.namaBouquet) {
        tree->left = insert(tree->left, bouquet);
    } 
    else if (bouquet.namaBouquet > tree->data.namaBouquet) {
        tree->right = insert(tree->right, bouquet);
    } 
    else {
        cout << "Bouquet dengan nama '" << bouquet.namaBouquet << "' sudah ada!\n";
    }
    
    return tree;
}

BST* search(BST* tree, string namaBouquet) {
    if (tree == nullptr || tree->data.namaBouquet == namaBouquet) {
        return tree;
    }
    
    if (namaBouquet < tree->data.namaBouquet) {
        return search(tree->left, namaBouquet);
    } 
    else {
        return search(tree->right, namaBouquet);
    }
}

BST* findMin(BST* tree) {
    if (tree == nullptr) 
        return nullptr;
    
    while (tree->left != nullptr) {
        tree = tree->left;
    }
    return tree;
}

BST* findMax(BST* tree) {
    if (tree == nullptr) 
        return nullptr;
    
    while (tree->right != nullptr) {
        tree = tree->right;
    }
    return tree;
}

BST* deleteNode(BST* tree, string namaBouquet) {
    if (tree == nullptr) {
        return nullptr;
    }
    
    if (namaBouquet < tree->data.namaBouquet) {
        tree->left = deleteNode(tree->left, namaBouquet);
    } 
    else if (namaBouquet > tree->data.namaBouquet) {
        tree->right = deleteNode(tree->right, namaBouquet);
    } 
    else {
        if (tree->left == nullptr && tree->right == nullptr) {
            delete tree;
            return nullptr;
        }
        else if (tree->left == nullptr) {
            BST* temp = tree->right;
            delete tree;
            return temp;
        }
        else if (tree->right == nullptr) {
            BST* temp = tree->left;
            delete tree;
            return temp;
        }
        else {
            BST* successor = findMin(tree->right);
            tree->data = successor->data;
            tree->right = deleteNode(tree->right, successor->data.namaBouquet);
        }
    }
    
    return tree;
}

bool updateBouquet(BST* tree, string namaBouquet) {
    BST* node = search(tree, namaBouquet);
    
    if (node == nullptr) {
        cout << "Bouquet tidak ditemukan!\n";
        return false;
    }
    
    cout << "\n=== UPDATE BOUQUET: " << namaBouquet << " ===\n";
    cout << "Pilih data yang ingin diubah:\n";
    cout << "1. Harga\n";
    cout << "2. Ukuran\n";
    cout << "3. Warna Dominan\n";
    cout << "4. Resep Bunga\n";
    cout << "Pilihan: ";
    
    int pilihan;
    cin >> pilihan;
    cin.ignore();
    
    switch (pilihan) {
        case 1:
            cout << "Harga baru (Rp): ";
            cin >> node->data.harga;
            cin.ignore();
            break;
        case 2:
            cout << "Ukuran baru (S/M/L): ";
            getline(cin, node->data.ukuran);
            break;
        case 3:
            cout << "Warna dominan baru: ";
            getline(cin, node->data.warnaDominan);
            break;
        case 4:
            cout << "Input resep baru:\n";
            for (int i = 0; i < JUMLAH_JENIS_BUNGA; i++) {
                cout << "  " << NAMA_BUNGA[i] << ": ";
                cin >> node->data.resepBunga[i];
            }
            cin.ignore();
            break;
        default:
            cout << "Pilihan tidak valid!\n";
            return false;
    }
    
    cout << "Update berhasil!\n";
    return true;
}

void inorder(BST* tree) {
    if (tree != nullptr) {
        inorder(tree->left);
        displayBouquet(tree->data);
        inorder(tree->right);
    }
}

void preorder(BST* tree) {
    if (tree != nullptr) {
        displayBouquet(tree->data);
        preorder(tree->left);
        preorder(tree->right);
    }
}

void postorder(BST* tree) {
    if (tree != nullptr) {
        postorder(tree->left);
        postorder(tree->right);
        displayBouquet(tree->data);
    }
}

void levelOrder(BST* tree) {
    if (tree == nullptr) 
        return;
    
    std::queue <BST*> q;
    q.push(tree);
    
    while (!q.empty()) {
        BST* current = q.front();
        q.pop();
        
        displayBouquet(current->data);
        
        if (current->left != nullptr) {
            q.push(current->left);
        }
        if (current->right != nullptr) {
            q.push(current->right);
        }
    }
}

void searchByHarga(BST* tree, long minHarga, long maxHarga) {
    if (tree == nullptr) 
        return;
    
    searchByHarga(tree->left, minHarga, maxHarga);
    
    if (tree->data.harga >= minHarga && tree->data.harga <= maxHarga) {
        displayBouquet(tree->data);
    }
    
    searchByHarga(tree->right, minHarga, maxHarga);
}

void searchByUkuran(BST* tree, string ukuran) {
    if (tree == nullptr) 
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
    if (tree == nullptr) {
        cout << "Katalog masih kosong!\n";
        return;
    }
    
    cout << "\n=== TRANSAKSI PENJUALAN ===\n";
    cout << "Nama Bouquet yang ingin dibeli: ";
    string nama;
    getline(cin, nama);
    
    BST* node = search(tree, nama);
    
    if (node == nullptr) {
        cout << "Bouquet '" << nama << "' tidak ditemukan di katalog!\n";
        return;
    }
    
    cout << "\nBouquet ditemukan:\n";
    displayBouquet(node->data);
    
    cout << "\nMengecek ketersediaan bahan...\n";
    
    if (cekStokCukup(node->data.resepBunga)) {
        kurangiStok(node->data.resepBunga);
        cout << "\nTRANSAKSI BERHASIL!\n";
        cetakStruk(node->data);
    } 
    else {
        cout << "\nTransaksi gagal. Stok bahan tidak mencukupi.\n";
    }
}

void initStokAwal() {
    for (int i = 0; i < JUMLAH_JENIS_BUNGA; i++) {
        stokBungaMentah[i] = 50;
    }
}

void cekStokGudang() {
    cout << "\n=== STOK GUDANG BUNGA MENTAH ===\n";
    cout << string(40, '=') << "\n";
    for (int i = 0; i < JUMLAH_JENIS_BUNGA; i++) {
        cout << left << setw(15) << NAMA_BUNGA[i] << ": " 
             << right << setw(5) << stokBungaMentah[i] << " tangkai\n";
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
    if (tree == nullptr) 
        return 0;
    return 1 + countNodes(tree->left) + countNodes(tree->right);
}

void tampilkanTermurah(BST* tree) {
    if (tree == nullptr) 
        return;
    
    static long minHarga = LONG_MAX;
    static Bouquet bouquetTermurah;
    static bool found = false;
    
    if (!found) {
        minHarga = LONG_MAX;
    }
    
    tampilkanTermurah(tree->left);
    
    if (tree->data.harga < minHarga) {
        minHarga = tree->data.harga;
        bouquetTermurah = tree->data;
        found = true;
    }
    
    tampilkanTermurah(tree->right);
    
    if (tree->left == nullptr && tree->right == nullptr && found) {
        cout << "\nBOUQUET TERMURAH:\n";
        displayBouquet(bouquetTermurah);
        found = false;
    }
}

void tampilkanTermahal(BST* tree) {
    if (tree == nullptr) 
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
    
    if (tree->left == nullptr && tree->right == nullptr && found) {
        cout << "\nBOUQUET TERMAHAL:\n";
        displayBouquet(bouquetTermahal);
        found = false;
    }
}

void tampilkanStatistik(BST* tree) {
    if (tree == nullptr) {
        cout << "Belum ada data bouquet!\n";
        return;
    }
    
    cout << "\n=== STATISTIK BLOOMTRACK ===\n";
    cout << "Total Jenis Bouquet: " << countNodes(tree) << "\n";
    
    tampilkanTermurah(tree);
    tampilkanTermahal(tree);
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
    cout << left << setw(20) << "NAMA BOUQUET"
         << setw(12) << "HARGA"
         << setw(8) << "UKURAN"
         << setw(15) << "WARNA"
         << "RESEP\n";
    cout << string(100, '=') << "\n";
}

void displayBouquet(Bouquet bouquet) {
    cout << left << setw(20) << bouquet.namaBouquet
         << "Rp" << right << setw(9) << bouquet.harga << " "
         << left << setw(8) << bouquet.ukuran
         << setw(15) << bouquet.warnaDominan;
    
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

void cetakStruk(Bouquet bouquet) {
    cout << "\n" << string(50, '=') << "\n";
    cout << "             BLOOMTRACK FLORIST  \n";
    cout << "              STRUK PEMBELIAN\n";
    cout << string(50, '=') << "\n";
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

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void tampilkanMenu() {
    cout << "\n";
    cout << "╔════════════════════════════════════════════╗\n";
    cout << "║         BLOOMTRACK - FLORIST SYSTEM        ║\n";
    cout << "╚════════════════════════════════════════════╝\n";
    cout << "  1. Tambah Bouquet Baru\n";
    cout << "  2. Lihat Katalog\n";
    cout << "  3. Cari Bouquet\n";
    cout << "  4. Transaksi Penjualan\n";
    cout << "  5. Update Info Bouquet\n";
    cout << "  6. Hapus Bouquet\n";
    cout << "  7. Manajemen Gudang\n";
    cout << "  8. Laporan Statistik\n";
    cout << "  0. Keluar\n";
    cout << "═══════════════════════════════════════════════\n";
    cout << "Pilihan: ";
}

void menuLihatKatalog(BST* tree) {
    if (tree == nullptr) {
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
    if (tree == nullptr) {
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
            if (hasil != nullptr) {
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