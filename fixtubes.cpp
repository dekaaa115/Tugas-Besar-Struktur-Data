#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX_KURSI = 10; // Konstanta untuk jumlah kursi maksimal

// Struktur untuk menyimpan data film
struct Film {
    string nama;
    string waktu;
    float harga;
};

// Struktur untuk node dalam linked list
struct Node {
    int data; // Data kursi yang terisi
    Node* next; // Pointer ke node berikutnya
};

// Fungsi untuk menampilkan daftar film
void tampilkanDaftarFilm() {
    cout << " |================================================================|\n";
    cout << " |                      DAFTAR FILM HARI INI                      |\n";
    cout << " |================================================================|\n";
    cout << " |            FILM              |   WAKTU     |      HARGA        |\n";
    cout << " |------------------------------|-------------|-------------------|\n";
    cout << " | 1. Vina Sebelum 7 Hari       | Pagi        | Rp. 30.000,-      |\n";
    cout << " |                              | Siang       | Rp. 35.000,-      |\n";
    cout << " | 2. POSSESSION                | Pagi        | Rp. 30.000,-      |\n";
    cout << " |                              | Siang       | Rp. 35.000,-      |\n";
    cout << " | 3. Badarawudi Di Desa Penari | Pagi        | Rp. 30.000,-      |\n";
    cout << " |                              | Siang       | Rp. 35.500,-      |\n";
    cout << " |================================================================|\n";
}

// Fungsi untuk memilih film berdasarkan input pengguna
Film pilihFilm() {
    char kode;
    char waktu;
    Film film;
    
    cout << " Kode Film [1/2/3] : ";
    cin >> kode;
    cout << " Waktu Tayang Pagi/Siang [P/S] : ";
    cin >> waktu;
    
    // Menentukan film dan harga berdasarkan input
    switch(kode) {
        case '1':
            film.nama = "Vina Sebelum 7 Hari";
            film.harga = (waktu == 'P' || waktu == 'p') ? 30000 : 35000;
            film.waktu = (waktu == 'P' || waktu == 'p') ? "Pagi <11:00-13:30>" : "Siang <14:30-17:00>";
            break;
        case '2':
            film.nama = "POSSESSION";
            film.harga = (waktu == 'P' || waktu == 'p') ? 30000 : 35000;
            film.waktu = (waktu == 'P' || waktu == 'p') ? "Pagi <11:30-13:30>" : "Siang <16:00-17:30>";
            break;
        case '3':
            film.nama = "Badarawudi Di Desa Penari";
            film.harga = (waktu == 'P' || waktu == 'p') ? 30000 : 35500;
            film.waktu = (waktu == 'P' || waktu == 'p') ? "Pagi <12:00-14:00>" : "Siang <15:00-17:00>";
            break;
        default:
            cout << " Inputan Kode Film Tidak Sesuai\n";
            break;
    }
    return film;
}

// Fungsi untuk menambah node ke linked list
void tambahKursi(Node*& head, int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->next = head;
    head = newNode;
}

// Fungsi untuk menghapus node dari linked list
void hapusKursi(Node*& head) {
    if (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    } else {
        cout << " Tidak ada kursi yang dapat dibatalkan.\n";
    }
}

// Fungsi untuk menampilkan data dari linked list
void tampilkanKursi(Node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << "\n";
}

int main() {
    char jawab;

    do {
        tampilkanDaftarFilm();
        Film film = pilihFilm();
        
        cout << " Nama Penonton : ";
        string nama_penonton;
        cin >> nama_penonton;

        cout << " Jumlah Tiket : ";
        int jumlah_tiket;
        cin >> jumlah_tiket;

        cout << "\n -> Masukkan nomor kursi yang telah terisi\n\n";
        Node* kursi_terisi = nullptr; // Linked list untuk menyimpan nomor kursi yang terisi
        for (int i = 0; i < jumlah_tiket; ++i) {
            int nomor_kursi;
            cout << " Kursi Terisi " << i + 1 << " : ";
            cin >> nomor_kursi;
            tambahKursi(kursi_terisi, nomor_kursi); // Menambah kursi ke linked list
        }

        cout << "\n Apakah Anda ingin membatalkan kursi terakhir yang dipesan? [Y/T] : ";
        char batal;
        cin >> batal;
        if (batal == 'Y' || batal == 'y') {
            hapusKursi(kursi_terisi); // Menghapus kursi terakhir dari linked list
            jumlah_tiket--;
        }

        cout << "\n NOMOR KURSI YANG TERISI: \n";
        cout << " -------------------------\n";
        tampilkanKursi(kursi_terisi); // Menampilkan nomor kursi yang terisi

        // Menghitung total harga, potongan, PPN, dan total bayar
        float total_harga = film.harga * jumlah_tiket;
        float potongan = (jumlah_tiket >= 5) ? 0.1 * total_harga : 0;
        float ppn = 0.02 * total_harga;
        float total_bayar = total_harga - potongan + ppn;

        // Menampilkan detail pembayaran
        cout << "\n Pembayaran : Rp." << total_harga << "\n";
        cout << " Potongan : Rp." << potongan << "\n";
        cout << " PPN : Rp." << ppn << "\n";
        cout << " Total Bayar : Rp." << total_bayar << "\n";

        // Meminta input uang bayar dari pengguna dan menghitung kembalian
        float uang_bayar;
        do {
            cout << " Uang Bayar : Rp.";
            cin >> uang_bayar;
            if (uang_bayar < total_bayar) {
                cout << " Uang yang Anda masukkan kurang.\n";
            }
        } while (uang_bayar < total_bayar);

        float uang_kembali = uang_bayar - total_bayar;
        cout << " Uang Kembali : Rp." << uang_kembali << "\n";
        cout << "\n MOHON DATANG TEPAT WAKTU \n";
        cout << " =-=-= TERIMA KASIH ATAS KUNJUNGAN ANDA =-=-=\n";

        // Menanyakan apakah pengguna ingin input data lagi
        cout << "\n Input Data Lagi [Y/T] : ";
        cin >> jawab;
    } while (jawab == 'Y' || jawab == 'y');

    return 0;
}