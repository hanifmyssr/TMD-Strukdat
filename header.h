#include <stdio.h>
#include <malloc.h>
#include <string.h>

/*Saya Muhammad Hanif Muyassar mengerjakan evaluasi Tugas Masa Depan dalam mata kuliah Algoritma dan
Struktur Data untuk keberkahanNya maka saya tidak melakukan kecurangan seperti yang telah
dispesifikasikan. Aamiin.
*/

// bungkusan data untuk list dalam simpul
typedef struct
{
    char nama[81];
    char parent[81];
    int value;
} data;

// bungkusan isi dari list tunggal
typedef struct
{
    char peluang[81];
} isi;

// bungkusan list tunggal
typedef struct lol *alamatlol;
typedef struct lol
{
    isi kontainer;
    alamatlol next;
} elemen;

typedef struct
{
    elemen *first;
} list;

// bungkusan tree
typedef struct smp *alamatsimpul;
typedef struct smp
{
    data kontainer;
    alamatsimpul sibling;
    alamatsimpul child;
    elemen *first;
} simpul;

typedef struct
{
    simpul *root;
} tree;


// variabel global
extern int idx; // index (cacah karakter)
extern int wlen; // panjang kata
extern char cw[201]; // current word
extern int level; // level tiap simpul

// MESIN KATA.
void inc(char pita[]); // tombol increment kata (pindah next kata)
char *getcw(); // tombol mendapatkan current word
int getlen(); // tombol mendapatkan panjang string di current word

// prosedur tambahan
int str_to_int(char str[]); // ubah string ke integer
void addelemen(char temp[], simpul *root); // menambahkan elemen pada list pohon
void createList(list *L); // membuat list tunggal
void addList(char temp[], list *L); // menambahkan elemen pada list tunggal
void addListTerpilih(simpul *root, list *L); // menambahkan elemen dari pohon ke dalam list tunggal
void printList(list L); // menampilkan isi list
void hitung_spasi(simpul *root, int spasi[]); // menghitung spasi antar simpul
void prunning(simpul *root, int *flag, char temp[], int *total); // memotong simpul yg tidak terpilih

// prosedur pohon
void makeTree(data c, tree *T); // membuat pohon
void addChild(data c, simpul *root); // menambahkan anak
void delAll(simpul *root); // menghapus semua
void delChild(data c, simpul *root); // menghapus anak
simpul *findSimpul(char c[], simpul *root); // mencari simpul
void printTreePreOrder(simpul *root, int spasi[]); // menampilkan pohon dari akar, kiri, sampai kanan