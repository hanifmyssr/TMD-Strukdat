#include "header.h"

int idx;      // index
int wlen;     // panjang current word
char cw[201]; // current word
int level = 0; // level / tingkat kedalaman simpul di set ke 0

// mengambil kata
void inc(char pita[])
{
    wlen = 0; // set panjang kata jadi 0 (memastikan)

    while (pita[idx] == '#' || pita[idx] == ' ')
    { // ignore blank atau pagar
        idx++;
    }

    // masukkan kata baru
    while ((pita[idx] != ' ') && (pita[idx] != '#') && idx != strlen(pita))
    {
        cw[wlen] = pita[idx];
        wlen++;
        idx++;
    }
    cw[wlen] = '\0'; // akhiri lagi
}

// mengembalikan current word
char *getcw()
{
    return cw;
}

// mengembalikan panjang current word
int getlen()
{
    return wlen;
}

// Mengubah string ke integer
int str_to_int(char str[])
{
    int hasil = 0;
    int i = 0;
    while(i < getlen()){
        hasil = hasil * 10 + (str[i] - 48);
        i += 1;
    }
    return hasil;
}

// membuat tree
void makeTree(data c, tree *T)
{
    simpul *node;
    node = (simpul *)malloc(sizeof(simpul));
    node->kontainer = c;
    node->sibling = NULL;
    node->child = NULL;
    node->first = NULL;
    (*T).root = node;
}

// menambahkan anak pada pohon
void addChild(data c, simpul *root)
{
    if (root != NULL)
    {
        /* jika simpul root tidak kosong,
        berarti dapat ditambahkan simpul anak
        */
        simpul *baru;
        baru = (simpul *)malloc(sizeof(simpul));
        baru->kontainer = c;
        baru->child = NULL;
        baru->first = NULL;

        if (root->child == NULL)
        {
            /* jika simpul root belum
            memiliki simpul anak maka simpul baru
            menjadi anak pertama */

            baru->sibling = NULL;
            root->child = baru;
        }
        else
        {
            if (root->child->sibling == NULL)
            {
                /* jika simpul root memiliki
                anak yang belum memiliki saudara, maka
                simpul baru menjadi anak kedua */
                baru->sibling = root->child;
                root->child->sibling = baru;
            }
            else
            {

                simpul *last = root->child;
                /* mencari simpul anak terakhir
                karena akan dikaitkan dengan simpul
                baru sebagai simpul anak terakhir yang
                baru, simpul anak terakhir adalah yang
                memiliki sibling simpul anak pertama,
                maka selama belum sampai pada simpul
                anak terakhir, penunjuk last akan
                berjalan ke simpul anak berikutnya */
                while (last->sibling != root->child)
                {
                    last = last->sibling;
                }
                baru->sibling = root->child;
                last->sibling = baru;
            }
        }
    }
}

// menghapus semua simpul
void delAll(simpul *root)
{
    if (root != NULL)
    {
        /* jika simpul root tidak kosong */
        if (root->child != NULL)
        {
            if (root->child->sibling == NULL)
            {
                /* jika hanya memiliki satu simpul anak */
                delAll(root->child);
                free(root);
                root = NULL;
            }
            else

            {
                /*jika memiliki lebih dari satu anak
                cari anak terakhir*/
                simpul *last = root->child;
                while (last->sibling != root->child)
                {
                    last = last->sibling;
                }
                last->sibling = NULL; // putuskan sibling anak terakhir

                simpul *bantu = root->child;
                while (bantu != NULL)
                {
                    simpul *next = bantu->sibling;
                    bantu->sibling = NULL;
                    delAll(bantu);
                    bantu = next;
                }
                free(root);
                root = NULL;
            }
        }
        else
        {
            free(root);
            root = NULL;
        }
    }
}

// menghapus anak
void delChild(data c, simpul *root)
{
    if (root != NULL)
    {
        simpul *hapus = root->child;
        if (hapus != NULL)
        {
            if (hapus->sibling == NULL)
            {
                /*jika hanya mempunyai satu anak*/
                if (strcmp(root->child->kontainer.nama, c.nama)==0)
                {
                    delAll(root->child);
                    root->child = NULL;
                }
                else
                {
                    printf("tidak ada simpul anak dengan kontainer karakter masukan\n");
                }
            }
            else
            {
                /*jika memiliki lebih dari satu simpul
                anak*/
                simpul *prev = NULL;
                /*mencari simpul yang akan dihapus*/
                int ketemu = 0;
                while ((hapus->sibling != root->child) && (ketemu == 0))
                {
                    if (strcmp(hapus->kontainer.nama, c.nama)==0)
                    {
                        ketemu = 1;
                    }
                    else
                    {
                        prev = hapus;
                        hapus = hapus->sibling;
                    }
                }
                /*memproses simpul anak terakhir karena
                belum terproses dalam pengulangan*/
                if ((ketemu == 0) && strcmp(hapus->kontainer.nama , c.nama)==0)
                {
                    ketemu = 1;
                }
                if (ketemu == 1)
                {
                    simpul *last = root->child;
                    /* mencari simpul anak terakhir untuk
                    membantu proses atau pemeriksaan jika yang
                    dihapus nantinya anak terakhir */
                    while (last->sibling != root->child)
                    {
                        last = last->sibling;
                    }
                    if (prev == NULL)
                    {
                        /*jika simpul yang dihapus
                        anak pertama*/

                        if ((hapus->sibling == last) && (last->sibling == root->child))
                        {
                            /*jika hanya ada dua anak*/
                            root->child = last;
                            last->sibling = NULL;
                        }
                        else
                        {

                            /* jika memiliki simpul anak
                            lebih dari dua simpul */

                            root->child = hapus->sibling;
                            last->sibling = root->child;
                        }
                    }
                    else
                    {
                        if ((prev == root->child) && (hapus->sibling == root->child))
                        {
                            /* jika hanya ada dua simpul
                            anak dan yang dihapus adalah simpul
                            anak kedua */

                            root->child->sibling = NULL;
                        }
                        else
                        {

                            /* jika yang dihapus bukan
                            simpul anak pertama dan simpul root
                            memiliki simpul anak lebih dari dua
                            simpul */

                            prev->sibling = hapus->sibling;
                            hapus->sibling = NULL;
                        }
                    }
                    delAll(hapus);
                }
                else
                {
                    printf("tidak ada simpul anak dengan kontainer karakter masukan\n");
                }
            }
        }
    }
}

// mencari simpul
simpul *findSimpul(char c[], simpul *root)
{
    simpul *hasil = NULL;
    if (root != NULL)
    {
        if (strcmp(root->kontainer.nama, c)==0)
        {
            hasil = root;
        }
        else
        {
            simpul *bantu = root->child;
            if (bantu != NULL)
            {
                if (bantu->sibling == NULL)
                {
                    /*jika memiliki satu simpul anak*/
                    if (strcmp(bantu->kontainer.nama , c)==0)
                    {
                        hasil = bantu;
                    }
                    else
                    {
                        hasil = findSimpul(c, bantu);
                    }
                }
                else
                {
                    int ketemu = 0;
                    /*jika memiliki banyak simpul anak*/
                    while ((bantu->sibling != root->child) && (ketemu == 0))
                    {
                        if (strcmp(bantu->kontainer.nama , c)== 0)
                        {
                            hasil = bantu;
                            ketemu = 1;
                        }
                        else
                        {
                            hasil = findSimpul(c, bantu);
                            if(hasil != NULL)ketemu = 1;
                            bantu = bantu->sibling;
                        }
                    }
                    /*memproses simpul anak terakhir karena belum terproses dalam
                    pengulangan*/

                    if (ketemu == 0)
                    {
                        if (strcmp(bantu->kontainer.nama, c)== 0)
                        {
                            hasil = bantu;
                        }
                        else
                        {
                            hasil = findSimpul(c, bantu);
                        }
                    }
                }
            }
        }
    }
    return hasil;
}

// menghitung panjang spasi dari tiap level
void hitung_spasi(simpul *root, int spasi[])
{
    if (root != NULL)
    {
        // jika root tidak NULL
        level += 1; // level tambah 1
        int len = 0; // inisialisasi
        // hitung panjang peluang dan juga valuenya
        if(root->kontainer.value < 10) len += 1; // jika value kelipatan satu
        else if(root->kontainer.value < 100) len += 2; // jika kelipatan dua
        else len += 3; // jika kelipatan tiga
        len += strlen(root->kontainer.nama) + 3; // ditambah dengan panjang peluangnya

        if(len > spasi[level]) spasi[level] = len; // jika len lebih panjang dari spasi ke - level
        
        // jika memiliki list
        if(root->first != NULL){
            elemen *temp = root->first;
            while(temp != NULL){
                // jika panjang isi list + 2 lebih panjang dari spasi ke - level
                if((strlen(temp->kontainer.peluang) + 2) > spasi[level]) spasi[level] = (strlen(temp->kontainer.peluang) + 2);
                // iterasi
                temp = temp->next;
            }
        }

        simpul *bantu = root->child;
        if (bantu != NULL)
        {
            if (bantu->sibling == NULL)
            {
                /*jika memiliki satu simpul anak*/
                hitung_spasi(bantu, spasi);
                level -= 1; // level kurangi satu
                
            }
            else
            {
                /*jika memiliki banyak simpul anak*/
                
                while (bantu->sibling != root->child)
                {
                    hitung_spasi(bantu, spasi);
                    level -= 1; // level kurangi satu
                    // iterasi
                    bantu = bantu->sibling;
                }
                /*memproses simpul anak
                terakhir karena belum terproses
                dalam pengulangan*/
                hitung_spasi(bantu, spasi);
                level -= 1; // level kurangi satu
            }
        }
    }
}

// menampilkan spasi
void print_spasi(int n)
{
    for(int i = 0; i < n; i++){
        printf(" ");
    }
}

// menampilkan pohon dari akar -> kiri -> kanan
void printTreePreOrder(simpul *root, int spasi[])
{
    if (root != NULL)
    {
        level += 1; // level tambah satu
        print_spasi(spasi[level]); // print spasi
        printf("%s - %d\n", root->kontainer.nama, root->kontainer.value);
        if(root->first != NULL){
            // jika punya list
            elemen *temp = root->first;
            while(temp != NULL){
                print_spasi(spasi[level]); // print spasi
                printf("[%s]\n", temp->kontainer.peluang);
                // iterasi
                temp = temp->next;
            }
        }printf("\n");

        simpul *bantu = root->child;
        if (bantu != NULL)
        {
            if (bantu->sibling == NULL)
            {
                /*jika memiliki satu simpul anak*/
                printTreePreOrder(bantu, spasi);
                level -= 1; // level kurangi satu
            }
            else
            {
                /*jika memiliki banyak simpul anak*/
                
                /*mencetak simpul anak*/
                while (bantu->sibling != root->child)
                {
                    printTreePreOrder(bantu, spasi);
                    level -= 1; // level kurangi satu
                    bantu = bantu->sibling;
                }
                /*memproses simpul anak
                terakhir karena belum terproses
                dalam pengulangan*/
                printTreePreOrder(bantu, spasi);
                level -= 1; // level kurangi satu
            }
        }
    }
}

// menambahkan elemen pada list tunggal dari pohon yg sudah di pruning
void addListTerpilih(simpul *root, list *L)
{
    if (root != NULL)
    {
        if(root->first != NULL){
            elemen *temp = root->first;
            while (temp != NULL)
            {
                addList(temp->kontainer.peluang, L);
                temp = temp->next;
            }
            
        }
        simpul *bantu = root->child;
        if (bantu != NULL)
        {
            if (bantu->sibling == NULL)
            {
                /*jika memiliki satu simpul anak*/
                addListTerpilih(bantu, L);
            }
            else
            {
                /*jika memiliki banyak simpul anak*/
                
                while (bantu->sibling != root->child)
                {
                    addListTerpilih(bantu, L);
                    bantu = bantu->sibling;
                }
                /*memproses simpul anak
                terakhir karena belum terproses
                dalam pengulangan*/
                addListTerpilih(bantu, L);
            }
        }
    }
}

// memotong simpul yg tidak terpilih dan juga menghitung total value
void prunning(simpul *root, int *flag, char temp[], int *total)
{
    if (root != NULL)
    {
        if(strcmp(root->kontainer.nama, temp) == 0){
            // jika simpul yg dipilih ketemu
            *flag = 1;
        }
        simpul *bantu = root->child;
        if (bantu != NULL)
        {
            if (bantu->sibling == NULL)
            {
                /*jika memiliki satu simpul anak*/
                prunning(bantu, flag, temp, total);
                if(*flag == 0){
                    // jika flag 0
                    free(bantu);
                    bantu = NULL;
                    root->child = NULL;
                }
            }
            else
            {
                /*jika memiliki banyak simpul anak*/
                // cari anak terakhir
                simpul *last = root->child;
                while(last->sibling != root->child){
                    last = last->sibling;
                }
                // putus sibling anak terakhir
                last->sibling = NULL;
                
                /*mencetak simpul anak*/
                while (bantu->sibling != NULL)
                {
                    prunning(bantu, flag, temp, total);
                    if(*flag == 0){
                        simpul *bantu2 = bantu;
                        bantu = bantu->sibling;
                        root->child = bantu;
                        bantu2->sibling = NULL;
                        free(bantu2);
                        bantu2 = NULL;
                    }else{
                        // jika flag 1, maka langsung putus aja :)
                        bantu->sibling = NULL;
                    }
                }
                /*memproses simpul anak
                terakhir karena belum terproses
                dalam pengulangan*/
                if(*flag == 0){
                    prunning(bantu, flag, temp, total);
                    if(*flag == 0){
                        free(bantu);
                        bantu = NULL;
                        root->child = NULL;
                    }
                }
            }
        }
        if(*flag == 1) *total += root->kontainer.value;
    }
}

// menambahkan elemen pada list pohon
void addelemen(char temp[], simpul *root)
{
    if(root != NULL){
        elemen *baru;
        baru = (elemen*)malloc(sizeof(elemen));
        strcpy(baru->kontainer.peluang, temp);
        baru->next = NULL;
        if((*root).first == NULL){
            (*root).first = baru;
        }else{
            elemen *last = (*root).first;
            while(last->next != NULL){
                last = last->next;
            }
            last->next = baru;    
        }
        baru = NULL;
    }
}

// membuat list tunggal
void createList(list *L)
{
    (*L).first = NULL;
}

// menambahkan elemen pada list tunggal
void addList(char temp[], list *L)
{
    elemen* baru;
    baru = (elemen*) malloc (sizeof(elemen));
    strcpy(baru->kontainer.peluang, temp);
    baru->next = NULL;
    if((*L).first == NULL){
        (*L).first = baru;
    }else{
        elemen *last = (*L).first;
        while(last->next != NULL){
            last = last->next;
        }
        last->next = baru;
    }
    baru = NULL;
}

// menampilkan list tunggal
void printList(list L)
{
    printf("semua peluang:\n");
    if(L.first != NULL){
        elemen *bantu = L.first;
        while(bantu != NULL){
            printf("[%s]\n", bantu->kontainer.peluang);
            bantu = bantu->next;
        }
    }
}