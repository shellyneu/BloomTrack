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
    } else if (newNode->data.harga < root->data.harga) {
        insertNode(root->left, newNode);
    } else if (newNode->data.harga > root->data.harga) {
        insertNode(root->right, newNode);
    } else {
        if (newNode->data.namaBouquet < root->data.namaBouquet) {
            insertNode(root->left, newNode);
        } else {
            insertNode(root->right, newNode);
        }
    }
}

BST* search(BST* tree, string namaBouquet) {
    if (tree == Nil) {
        return Nil;
    }
    
    if (tree->data.namaBouquet == namaBouquet) {
        return tree;
    }
    
    BST* found = search(tree->left, namaBouquet);
    if (found != Nil) {
        return found;
    }
    
    return search(tree->right, namaBouquet);
}

void searchByData(BinTree tree, string namaBouquet){
    if(isEmpty(tree) == true){
        cout << "Tree kosong!" << endl;
    } else {
        BST* hasil = search(tree, namaBouquet);
        if(hasil == Nil){
            cout << "Data tidak ditemukan" << endl;
        } else {
            cout << "\nData ditemukan didalam tree!" << endl;
            cout << "Nama Bouquet : " << hasil->data.namaBouquet << endl;
            cout << "Harga        : Rp" << hasil->data.harga << endl;
            cout << "Ukuran       : " << hasil->data.ukuran << endl;
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
    }
    
    if (tree->data.namaBouquet == namaBouquet) {
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
    
    bool found = deleteNode(tree->left, namaBouquet);
    if (!found) {
        found = deleteNode(tree->right, namaBouquet);
    }
    return found;
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

void orderBouquet(BST* tree, TreeTransaksi &treeTransaksi) {
    if (tree == Nil) {
        cout << "Katalog masih kosong!\n";
        return;
    }
    
    cout << "\n=== ORDER BOUQUET ===\n";
    
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
    
    cout << "\nTRANSAKSI BERHASIL!\n";
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

void katalogBouquet(BinTree &tree) {
    Bouquet b1;
    b1.namaBouquet = "Srikandi";
    b1.harga = 150000;
    b1.ukuran = "M";
    b1.resepBunga[0] = 5; 
    b1.resepBunga[1] = 3; 
    b1.resepBunga[2] = 0;
    b1.resepBunga[3] = 0;
    b1.resepBunga[4] = 0;
    
    Bouquet b2;
    b2.namaBouquet = "Dewisri";
    b2.harga = 120000;
    b2.ukuran = "L";
    b2.resepBunga[0] = 0;
    b2.resepBunga[1] = 4; 
    b2.resepBunga[2] = 3;
    b2.resepBunga[3] = 2;
    b2.resepBunga[4] = 2;
    
    Bouquet b3;
    b3.namaBouquet = "Arimbi";
    b3.harga = 200000;
    b3.ukuran = "L";
    b3.resepBunga[0] = 3;
    b3.resepBunga[1] = 5;
    b3.resepBunga[2] = 2; 
    b3.resepBunga[3] = 0;
    b3.resepBunga[4] = 1; 
    
    Bouquet b4;
    b4.namaBouquet = "Maharani";
    b4.harga = 75000;
    b4.ukuran = "S";
    b4.resepBunga[0] = 2; 
    b4.resepBunga[1] = 2; 
    b4.resepBunga[2] = 1; 
    b4.resepBunga[3] = 3; 
    b4.resepBunga[4] = 0;
    
    Bouquet b5;
    b5.namaBouquet = "Serena";
    b5.harga = 50000;
    b5.ukuran = "S";
    b5.resepBunga[0] = 1;
    b5.resepBunga[1] = 1;
    b5.resepBunga[2] = 1;
    b5.resepBunga[3] = 2;
    b5.resepBunga[4] = 0;
    
    Bouquet b6;
    b6.namaBouquet = "Adonia";
    b6.harga = 100000;
    b6.ukuran = "M";
    b6.resepBunga[0] = 3;
    b6.resepBunga[1] = 2;
    b6.resepBunga[2] = 2;
    b6.resepBunga[3] = 2;
    b6.resepBunga[4] = 1;
    
    Bouquet b7;
    b7.namaBouquet = "Aghniya";
    b7.harga = 180000;
    b7.ukuran = "L";
    b7.resepBunga[0] = 4;
    b7.resepBunga[1] = 4;
    b7.resepBunga[2] = 3;
    b7.resepBunga[3] = 0;
    b7.resepBunga[4] = 2;
    
    Bouquet b8;
    b8.namaBouquet = "Bidhadari";
    b8.harga = 250000;
    b8.ukuran = "L";
    b8.resepBunga[0] = 5;
    b8.resepBunga[1] = 6;
    b8.resepBunga[2] = 4;
    b8.resepBunga[3] = 3;
    b8.resepBunga[4] = 3;
    
    insertNode(tree, alokasi(b1));
    insertNode(tree, alokasi(b2));
    insertNode(tree, alokasi(b3));
    insertNode(tree, alokasi(b4));
    insertNode(tree, alokasi(b5));
    insertNode(tree, alokasi(b6));
    insertNode(tree, alokasi(b7));
    insertNode(tree, alokasi(b8));
}

Bouquet inputBouquet() {
    Bouquet b;
    
    cout << "\n=== INPUT BOUQUET BARU ===\n";
    cout << "Nama Bouquet: ";
    getline(cin, b.namaBouquet);
    
    bool hargaValid = false;
    while (!hargaValid) {
        cout << "Harga (Rp): ";
        if (cin >> b.harga) {
            if (b.harga > 0) {
                hargaValid = true;
            } else {
                cout << "Error: Harga harus lebih dari 0!\n";
            }
        } else {
            cout << "Error: Format harga tidak sesuai! Harga hanya boleh berupa angka.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
    cin.ignore();
    
    bool ukuranValid = false;
    while (!ukuranValid) {
        cout << "Ukuran (S/M/L): ";
        getline(cin, b.ukuran);
        
        bool isNumber = true;
        for (int i = 0; i < b.ukuran.length(); i++) {
            if (!isdigit(b.ukuran[i])) {
                isNumber = false;
                break;
            }
        }
        
        if (b.ukuran.empty()) {
            cout << "Error: Ukuran tidak boleh kosong!\n";
        } else if (isNumber) {
            cout << "Error: Format tidak valid! Ukuran harus berupa huruf (S/M/L), bukan angka.\n";
        } else if (b.ukuran == "S" || b.ukuran == "M" || b.ukuran == "L" || 
                    b.ukuran == "s" || b.ukuran == "m" || b.ukuran == "l") {
            if (b.ukuran == "s") b.ukuran = "S";
            if (b.ukuran == "m") b.ukuran = "M";
            if (b.ukuran == "l") b.ukuran = "L";
            ukuranValid = true;
        } else {
            cout << "Error: Ukuran tidak valid! Hanya menerima S, M, atau L.\n";
        }
    }
    
    cout << "\nResep Bunga (jumlah tangkai yang dibutuhkan):\n";
    for (int i = 0; i < JUMLAH_JENIS_BUNGA; i++) {
        bool resepValid = false;
        while (!resepValid) {
            cout << "  " << NAMA_BUNGA[i] << ": ";
            if (cin >> b.resepBunga[i]) {
                if (b.resepBunga[i] >= 0) {
                    resepValid = true;
                } else {
                    cout << "Error: Jumlah tangkai tidak boleh negatif!\n";
                }
            } else {
                cout << "Error: Format tidak sesuai! Jumlah tangkai hanya boleh berupa angka.\n";
                cin.clear();
                cin.ignore(1000, '\n');
            }
        }
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
    cout << "  1. Order Bouquet\n";
    cout << "  2. Tambah Bouquet\n";
    cout << "  3. Lihat Katalog Bouquet\n";
    cout << "  4. Cari Bouquet\n";
    cout << "  5. Hapus Bouquet\n";
    cout << "  6. Manajemen Gudang\n";
    cout << "  7. Laporan Statistik\n";
    cout << "  0. KELUAR\n";
    cout << "================================================\n";
    cout << "Pilihan: ";
}

void lihatKatalogBouquet(BST* tree) {
    if (tree == Nil) {
        cout << "Katalog masih kosong!\n";
        return;
    }
    
    clearScreen();
    cout << "\n=== KATALOG BOUQUET ===\n";
    cout << "Pilih cara tampilan:\n";
    cout << "1. Berdasarkan Harga (Termurah ke Termahal)\n";
    cout << "2. Berdasarkan Harga Menengah Dulu\n";
    cout << "3. Berdasarkan Harga (Budget & Premium)\n";
    cout << "4. Berdasarkan Urutan Penambahan\n";
    cout << "Pilihan: ";
    
    int pilihan;
    cin >> pilihan;
    cin.ignore();
    
    displayHeaderKatalog();
    
    switch (pilihan) {
        case 1:
            cout << "[INORDER TRAVERSAL - TAMPILAN TERMURAH KE TERMAHAL]\n";
            inorder(tree);
            break;
        case 2:
            cout << "[PREORDER TRAVERSAL - TAMPILAN HARGA MENENGAH PRIORITAS]\n";
            preorder(tree);
            break;
        case 3:
            cout << "[POSTORDER TRAVERSAL - TAMPILAN HARGA (Budget & Premium Dulu)]\n";
            postorder(tree);
            break;
        case 4:
            cout << "[LEVEL ORDER TRAVERSAL - TAMPILAN BERDASARKAN URUTAN PENAMBAHAN]\n";
            levelOrder(tree);
            break;
        default:
            cout << "Pilihan tidak valid!\n";
    }
}

void cariBouquet(BST* tree) {
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
            
            if (nama.empty()) {
                cout << endl << "Nama bouquet tidak boleh kosong!\n";
                break;
            }
            
            BST* hasil = search(tree, nama);
            if (hasil != Nil) {
                cout << "\nBouquet ditemukan:\n";
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
            bool inputValid = false;
            
            while (!inputValid) {
                cout << "Harga Minimum (Rp): ";
                
                if (!(cin >> min)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Error: Harga minimum harus berupa angka!\n";
                    continue;
                }
                
                if (min <= 0) {
                    cin.ignore(1000, '\n');
                    cout << "Error: Harga minimum harus lebih dari 0!\n";
                    continue;
                }
                
                inputValid = true;
            }
            
            inputValid = false;
            while (!inputValid) {
                cout << "Harga Maksimum (Rp): ";
                
                if (!(cin >> max)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Error: Harga maksimum harus berupa angka!\n";
                    continue;
                }
                
                if (max <= 0) {
                    cout << "Error: Harga maksimum harus lebih dari 0!\n";
                    continue;
                }
                
                if (max < min) {
                    cout << "Error: Harga maksimum tidak boleh kurang dari harga minimum!\n";
                    cout << "Harga minimum yang diinput: Rp" << min << "\n";
                    continue;
                }
                
                inputValid = true;
            }
            cin.ignore();
            
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
                cout << "\nError: Ukuran tidak boleh kosong!\n";
                break;
            }
            
            bool isNumber = true;
            for (int i = 0; i < ukuran.length(); i++) {
                if (!isdigit(ukuran[i])) {
                    isNumber = false;
                    break;
                }
            }
            
            if (isNumber) {
                cout << "\nError: Ukuran harus berupa huruf (S/M/L), bukan angka!\n";
                break;
            }
            
            if (ukuran != "S" && ukuran != "M" && ukuran != "L" && 
                ukuran != "s" && ukuran != "m" && ukuran != "l") {
                cout << "\nError: Ukuran tidak valid! Hanya menerima S, M, atau L.\n";
                break;
            }
            
            if (ukuran == "s") ukuran = "S";
            if (ukuran == "m") ukuran = "M";
            if (ukuran == "l") ukuran = "L";
            
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

void hapusBouquet(BST* &tree) {
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

void laporanStatistik(BST* tree, TreeTransaksi treeTransaksi) {
    clearScreen();
    
    cout << "\n";
    cout << "================================================\n";
    cout << "        LAPORAN STATISTIK BLOOMTRACK\n";
    cout << "================================================\n";
    
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
    
    cout << "\n[2] RIWAYAT ORDER BOUQUET\n";
    cout << string(100, '=') << "\n";
    
    if (jumlahTransaksi == 0) {
        cout << "Belum ada order bouquet.\n";
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