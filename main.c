#include "header.h"

int main()
{
    // inisialisasi
    tree T;
    int n;
    scanf("%d", &n); // jumlah simpul
    int spasi[n]; // set spasi sebanyak n
    char peluang[81]; // peluang yang dipilih
    int flag = 0; // flag untuk menandakan kalo simpul yg dicari sudah ketemu
    int total_value = 0; // menyimpan total value dari simpul pohon
    list L; 
    createList(&L); // membuat list tunggal
    
    for (int i = 0; i < n; i++)
    {
        spasi[i] = 0; // spasi ke - i diset ke 0
        idx = 0; // idx diset ke 0
        char input[201];
        data pack;
        scanf(" %200[^\n]s", input);
        inc(input);
        strcpy(pack.nama, getcw());
        inc(input);
        strcpy(pack.parent, getcw());
        inc(input);
        pack.value = str_to_int(getcw());
        inc(input);
        int jumlah = str_to_int(getcw());
        simpul *cari;
        if(i == 0){
            makeTree(pack, &T);
        }else{
            cari = findSimpul(pack.parent, T.root);
            if(cari != NULL){
                addChild(pack, cari);
                cari = findSimpul(pack.nama, T.root);
            }
        }
        for (int j = 0; j < jumlah; j++)
        {
            scanf("%s", peluang);
            if(i == 0){
                addelemen(peluang, T.root);
            }else{
                if(cari != NULL){
                    addelemen(peluang, cari);
                }
            }
        }
    }

    // input peluang yg dipilih
    scanf("%s", peluang);

    // proses menampilkan pohon sebelum pruning
    hitung_spasi(T.root, spasi);
    for(int i = 0; i < n; i++){
        if(spasi[i] != 0){
            spasi[i] += spasi[i-1];
        }
    }
    level = -1;
    printTreePreOrder(T.root, spasi);
    
    // proses menampilkan pohon sebtelah pruning
    prunning(T.root, &flag, peluang, &total_value);
    for(int i = 0; i < n; i++){
        if(spasi[i] != 0){
            spasi[i] *= 0;
        }
    }
    level = 0;
    hitung_spasi(T.root, spasi);
    for(int i = 0; i < n; i++){
        if(spasi[i] != 0){
            spasi[i] += spasi[i-1];
        }
    }
    level = -1;
    printTreePreOrder(T.root, spasi);

    // proses menampilkan isi list tunggal
    printf("peluang akhir yang diambil: %s\ntotal value: %d\n", peluang, total_value);
    addListTerpilih(T.root, &L);
    printList(L);

    return 0;
}