#include "BinSTree.h"
#include <stdlib.h>

/* ============================================================
   1. ALOKASI & KONSTRUKTOR (Bikin Node & Pohon)
   ============================================================ */

/* Pesan memori untuk node baru */
address Alokasi(infotype X) {
    address P = (address)malloc(sizeof(Node));
    if (P != Nil) {
        Info(P) = X;
        Left(P) = Nil;
        Right(P) = Nil;
    }
    return P;
}

/* Balikin memori ke sistem */
void DeAlokasi(address P) {
    free(P);
}

/* Gabungin Akar, Kiri, dan Kanan jadi satu pohon */
BinTree Tree(infotype Akar, BinTree L, BinTree R) {
    address P = Alokasi(Akar);
    if (P != Nil) {
        Left(P) = L;
        Right(P) = R;
    }
    return P;
}

/* Sama kayak Tree, tapi hasilnya ditaruh di parameter pointer *P */
void MakeTree(infotype Akar, BinTree L, BinTree R, BinTree *P) {
    *P = Tree(Akar, L, R);
}

/* Bikin pohon dari input keyboard (urutan: Akar, Kiri, Kanan) */
void BuildTree(BinTree *P) {
    infotype X;
    scanf("%d", &X); // Ketik -999 kalau mau kasih Nil (kosong)
    if (X == -999) {
        *P = Nil;
    } else {
        *P = Alokasi(X);
        if (*P != Nil) {
            BuildTree(&Left(*P));  // Rekursif bikin cabang kiri
            BuildTree(&Right(*P)); // Rekursif bikin cabang kanan
        }
    }
}

/* ============================================================
   2. SELEKTOR & PREDIKAT (Cek Kondisi Pohon)
   ============================================================ */

infotype GetAkar(BinTree P) { return Info(P); }
BinTree GetLeft(BinTree P)  { return Left(P); }
BinTree GetRight(BinTree P) { return Right(P); }

bool IsEmpty(BinTree P) { return P == Nil; }

/* Cek apakah cuma punya anak kiri */
bool IsUnerLeft(BinTree P) {
    return !IsEmpty(P) && (Left(P) != Nil && Right(P) == Nil);
}

/* Cek apakah cuma punya anak kanan */
bool IsUnerRight(BinTree P) {
    return !IsEmpty(P) && (Left(P) == Nil && Right(P) != Nil);
}

/* Cek apakah punya 2 anak lengkap */
bool IsBiner(BinTree P) {
    return !IsEmpty(P) && (Left(P) != Nil && Right(P) != Nil);
}

/* ============================================================
   3. TRAVERSAL (Keliling Pohon)
   ============================================================ */

/* Urutan: Akar -> Kiri -> Kanan */
void PreOrder(BinTree P) {
    if (!IsEmpty(P)) {
        printf("%d ", Info(P));
        PreOrder(Left(P));
        PreOrder(Right(P));
    }
}

/* Urutan: Kiri -> Akar -> Kanan */
void InOrder(BinTree P) {
    if (!IsEmpty(P)) {
        InOrder(Left(P));
        printf("%d ", Info(P));
        InOrder(Right(P));
    }
}

/* Urutan: Kiri -> Kanan -> Akar */
void PostOrder(BinTree P) {
    if (!IsEmpty(P)) {
        PostOrder(Left(P));
        PostOrder(Right(P));
        printf("%d ", Info(P));
    }
}

/* Cetak pohon */
void PrintTree(BinTree P) {
    if (!IsEmpty(P)) {
        printf("info node: %d\n", Info(P));
        if(Left(P) != Nil) printf("info node left son: %d\n", Info(Left(P)));
        if(Right(P) != Nil) printf("info node right son: %d\n", Info(Right(P)));
        printf("--------------------------\n");
        PrintTree(Left(P));
        PrintTree(Right(P));
    }
}

/* Fungsi pembantu menggunakan karakter ASCII Standar (Aman untuk Terminal Windows) */
void PrintTreeDownwardUtil(BinTree P, char* prefix, bool isLast, char* type) {
    if (IsEmpty(P)) return;

    // Cetak prefix garis, diikuti simbol cabang ASCII, posisi (L/R), dan nilainya
    printf("%s", prefix);
    printf(isLast ? "\\-- " : "|-- "); // Menggunakan \-- dan |--
    printf("%s:[%d]\n", type, Info(P));

    // Siapkan prefix garis baru untuk anak-anaknya ke bawah
    char newPrefix[512];
    // Menggunakan karakter pipa ASCII "|" standar
    snprintf(newPrefix, sizeof(newPrefix), "%s%s", prefix, isLast ? "    " : "|   ");

    // Rekursif ke bawah untuk anak kiri dan kanan
    if (Left(P) != Nil && Right(P) != Nil) {
        PrintTreeDownwardUtil(Left(P), newPrefix, false, "L");
        PrintTreeDownwardUtil(Right(P), newPrefix, true, "R");
    } else if (Left(P) != Nil) {
        PrintTreeDownwardUtil(Left(P), newPrefix, true, "L");
    } else if (Right(P) != Nil) {
        PrintTreeDownwardUtil(Right(P), newPrefix, true, "R");
    }
}

/* Fungsi utama yang akan kamu panggil di main.c */
void PrintTreeDownward(BinTree P) {
    printf("\n==================== STRUKTUR AVL TREE ====================\n");
    if (IsEmpty(P)) {
        printf("Pohon Kosong.\n");
        return;
    }
    
    // Cetak Root paling atas
    printf("Root:[%d]\n", Info(P));
    
    char prefix[512] = "";
    if (Left(P) != Nil && Right(P) != Nil) {
        PrintTreeDownwardUtil(Left(P), prefix, false, "L");
        PrintTreeDownwardUtil(Right(P), prefix, true, "R");
    } else if (Left(P) != Nil) {
        PrintTreeDownwardUtil(Left(P), prefix, true, "L");
    } else if (Right(P) != Nil) {
        PrintTreeDownwardUtil(Right(P), prefix, true, "R");
    }
    printf("===========================================================\n");
}

/* ============================================================
   4. SEARCH & STATISTIK
   ============================================================ */

/* Cari apakah ada angka X di dalam pohon (semua cabang dicek) */
bool Search(BinTree P, infotype X) {
    if (IsEmpty(P)) return false;
    if (Info(P) == X) return true;
    return Search(Left(P), X) || Search(Right(P), X);
}

void SearchBST(BinTree P, infotype X, int kunjungan) {
    if (IsEmpty(P)) {
        printf("Node dengan nilai %d TIDAK ditemukan di pohon.\n", X);
        printf("Total langkah pemeriksaan: %d kali.\n", kunjungan);
        return;
    }
    printf("Langkah ke-%d -> Mengunjungi node dengan nilai %d\n", kunjungan, Info(P));
    if (Info(P) == X)
    {
        printf("Node dengan nilai %d ditemukan di pohon.\n", X);
        printf("Total langkah pemeriksaan: %d kali.\n", kunjungan);
        return;
    }

    if (X < Info(P)) SearchBST(Left(P), X, kunjungan + 1);
    else SearchBST(Right(P), X, kunjungan + 1);
}


address SearchAddress(BinTree P, infotype X) {
    if (P == Nil) {
        return Nil;
    }
    
    if (Info(P) == X) {
        return P;
    }
    
    address hasilKiri = SearchAddress(Left(P), X);
    if (hasilKiri != Nil) {
        return hasilKiri;
    }
    
    return SearchAddress(Right(P), X);
}

/* Hitung total jumlah node */
int nbElmt(BinTree P) {
    if (IsEmpty(P)) return 0;
    return 1 + nbElmt(Left(P)) + nbElmt(Right(P));
}

/* Hitung node yang gak punya anak sama sekali */
int nbDaun(BinTree P) {
    if (IsEmpty(P)) return 0;
    if (Left(P) == Nil && Right(P) == Nil) return 1;
    return nbDaun(Left(P)) + nbDaun(Right(P));
}

/* Cek apakah pohon condong ke kiri terus */
bool IsSkewLeft(BinTree P) {
    if (IsEmpty(P)) return true;
    if (Right(P) != Nil) return false;
    return IsSkewLeft(Left(P));
}

bool IsSkewRight(BinTree P) {
    if (IsEmpty(P)) return true;
    if (Left(P) != Nil) return false;
    return IsSkewRight(Right(P));
}

/* Cari kedalaman/tinggi pohon (ambil jalur terpanjang) */
// int Max(int a, int b) { return (a > b) ? a : b; }
int Depth(BinTree P) {
    if (IsEmpty(P)) return 0;
    int leftDepth = Depth(Left(P));
    int rightDepth = Depth(Right(P));
    return 1 + ((leftDepth > rightDepth) ? leftDepth : rightDepth);
}

/* Cari level suatu node (Akar = level 1) */
int Level(BinTree P, infotype X) {
    if (Info(P) == X) return 1;
    if (Search(Left(P), X)) return 1 + Level(Left(P), X);
    return 1 + Level(Right(P), X);
}

/* ============================================================
   5. OPERASI MODIFIKASI DAUN
   ============================================================ */

/* Tambah node baru di ujung kiri paling bawah */
void AddDaunTerkiri(BinTree *P, infotype X) {
    if (IsEmpty(*P)) *P = Alokasi(X);
    else AddDaunTerkiri(&Left(*P), X);
}

/* Tambah anak (Y) ke node (X) yang masih berupa daun */
void AddDaun(BinTree *P, infotype X, infotype Y, bool Kiri) {
    if (Info(*P) == X && Left(*P) == Nil && Right(*P) == Nil) {
        if (Kiri) Left(*P) = Alokasi(Y);
        else Right(*P) = Alokasi(Y);
    } else {
        if (Left(*P) != Nil && Search(Left(*P), X)) AddDaun(&Left(*P), X, Y, Kiri);
        else if (Right(*P) != Nil && Search(Right(*P), X)) AddDaun(&Right(*P), X, Y, Kiri);
    }
}

/* Hapus node paling kiri bawah */
void DelDaunTerkiri(BinTree *P, infotype *X) {
    if (Left(*P) == Nil && Right(*P) == Nil) {
        *X = Info(*P);
        DeAlokasi(*P);
        *P = Nil;
    } else {
        if (Left(*P) != Nil) DelDaunTerkiri(&Left(*P), X);
        else DelDaunTerkiri(&Right(*P), X);
    }
}

/* Hapus node X yang posisinya adalah daun */
void DelDaun(BinTree *P, infotype X) {
    if (!IsEmpty(*P)) {
        if (Info(*P) == X && Left(*P) == Nil && Right(*P) == Nil) {
            DeAlokasi(*P);
            *P = Nil;
        } else {
            DelDaun(&Left(*P), X);
            DelDaun(&Right(*P), X);
        }
    }
}

/* ============================================================
   6. BINARY SEARCH TREE (BST) - Pohon Terurut
   ============================================================ */

/* Cari angka di BST (Kiri < Akar < Kanan) */
bool BSearch(BinTree P, infotype X) {
    if (IsEmpty(P)) return false;
    if (Info(P) == X) return true;
    return (X < Info(P)) ? BSearch(Left(P), X) : BSearch(Right(P), X);
}

/* Cari alamat node X di BST */
address BinSearch(BinTree P, infotype X) {
    if (IsEmpty(P) || Info(P) == X) return P;
    return (X < Info(P)) ? BinSearch(Left(P), X) : BinSearch(Right(P), X);
}

/* Masukkan angka ke BST tanpa merusak urutan */
void InsSearch(BinTree *P, infotype X) {
    // TAHAP 1 & 2: LOGIKA INSERT BST BIASA
    if (IsEmpty(*P)) {
        *P = Alokasi(X);
        return;
    }

    if (X < Info(*P)) {
        InsSearch(&Left(*P), X);
    } else if (X > Info(*P)) {
        InsSearch(&Right(*P), X);
    } else {
        return;
    }

    // TAHAP 3: BALANCING
    *P = BalanceNode(*P);
}

// tambahan insert bst dengan cara lain
void Menu() {
    printf("\n=== BINARY SEARCH TREE ===\n");
    printf("1. Insert Node\n");
    printf("2. Print Tree\n");
    printf("3. Delete Node\n");
    printf("4. Search Node\n");
    printf("5. Exit\n");
    printf("Pilihan: ");
}

void insertWithBST(BinTree T, infotype valNode){
    if(valNode < GetAkar(T)){
        if(Left(T) == Nil){
            Left(T) = Alokasi(valNode);
            printf("node %d lebih kecil dari parent %d, akan menjadi Left Son\n", valNode, GetAkar(T));
        } else{
            insertWithBST(Left(T), valNode);
        }
    } else if(valNode > GetAkar(T)){
        if(Right(T) == Nil){
            Right(T) = Alokasi(valNode);
            printf("node %d lebih besar dari parent %d, akan menjadi Right Son\n", valNode, GetAkar(T));
        } else{
            insertWithBST(Right(T), valNode);
        }
    } else {
        printf("node %d sudah ada di tree, tidak bisa diinsert\n", valNode);
    }
}

// Fungsi pembantu untuk mencari pengganti node yang dihapus dengan successor (node terkecil di subtree kanan)
address getSuccessor(address curr) {
    curr = Right(curr);
    while (curr != Nil && Left(curr) != Nil) {
        curr = Left(curr);
    }
    return curr;
}

// Fungsi pembantu untuk mencari pengganti node yang dihapus dengan predecessor (node terbesar di subtree kiri)
address getPredecessor(address curr) {
    curr = Left(curr);
    while (curr != Nil && Right(curr) != Nil) {
        curr = Right(curr);
    }
    return curr;
}

// Fungsi utama untuk menghapus node dengan nilai X dari BST
address DelBTree(address P, infotype X) {
    // TAHAP 1 & 2: LOGIKA DELETE BST BIASA
    if (P == Nil) return Nil;

    if (X < Info(P)) {
        Left(P) = DelBTree(Left(P), X);
    } else if (X > Info(P)) {
        Right(P) = DelBTree(Right(P), X);
    } else {
        if (Left(P) == Nil) {
            address temp = Right(P);
            free(P);
            return temp;
        } else if (Right(P) == Nil) {
            address temp = Left(P);
            free(P);
            return temp;
        }
        address temp = getSuccessor(P);
        Info(P) = Info(temp);
        Right(P) = DelBTree(Right(P), Info(temp));
    }

    if (P == Nil) return P;

    // Tahap 3: SEIMBANGKAN KEMBALI (AVL)
    return BalanceNode(P);
}

/* Hapus seluruh pohon sampai bersih */
void DestroyTree(BinTree *P) {
    if (!IsEmpty(*P)) {
        DestroyTree(&Left(*P));
        DestroyTree(&Right(*P));
        DeAlokasi(*P);
        *P = Nil;
    }
}

/* ============================================================
   7. MANIPULASI LIST & BALANCED TREE
   ============================================================ */

/* Helper: Masukin info ke list di paling belakang */
void InsVLast(ListOfNode *L, infotype X) {
    address1 P = (address1)malloc(sizeof(ElmtList));
    if (P != Nil) {
        InfoList(P) = X;
        Next(P) = Nil;
        if (*L == Nil) *L = P;
        else {
            address1 last = *L;
            while (Next(last) != Nil) last = Next(last);
            Next(last) = P;
        }
    }
}

/* Bikin list yang isinya semua daun pohon */
void CollectDaun(BinTree P, ListOfNode *L) {
    if (!IsEmpty(P)) {
        if (Left(P) == Nil && Right(P) == Nil) InsVLast(L, Info(P));
        else {
            CollectDaun(Left(P), L);
            CollectDaun(Right(P), L);
        }
    }
}
ListOfNode MakeListDaun(BinTree P) {
    ListOfNode L = Nil;
    CollectDaun(P, &L);
    return L;
}

/* Bikin list dari semua node (urutan PreOrder) */
void CollectPreOrder(BinTree P, ListOfNode *L) {
    if (!IsEmpty(P)) {
        InsVLast(L, Info(P));
        CollectPreOrder(Left(P), L);
        CollectPreOrder(Right(P), L);
    }
}
ListOfNode MakeListPreOrder(BinTree P) {
    ListOfNode L = Nil;
    CollectPreOrder(P, &L);
    return L;
}

/* Bikin list dari node yang ada di level tertentu saja */
void CollectLevel(BinTree P, int N, int current, ListOfNode *L) {
    if (!IsEmpty(P)) {
        if (current == N) InsVLast(L, Info(P));
        else {
            CollectLevel(Left(P), N, current + 1, L);
            CollectLevel(Right(P), N, current + 1, L);
        }
    }
}
ListOfNode MakeListLevel(BinTree P, int N) {
    ListOfNode L = Nil;
    CollectLevel(P, N, 1, &L);
    return L;
}

/* Bikin pohon yang tingginya seimbang antara kiri dan kanan */
BinTree BuildBalanceTree(int N) {
    if (N == 0) return Nil;
    infotype X;
    scanf("%d", &X);
    address P = Alokasi(X);
    if (P != Nil) {
        Left(P) = BuildBalanceTree(N / 2);
        Right(P) = BuildBalanceTree(N - (N / 2) - 1);
    }
    return P;
}

/* Rotasi Kanan untuk kasus Left-Left (LL) */
void RotateRight(BinTree *P) {
    address child = Left(*P);
    Left(*P) = Right(child);
    Right(child) = *P;
    *P = child; // Langsung mengubah pointer parent-nya
}

/* Rotasi Kiri untuk kasus Right-Right (RR) */
void RotateLeft(BinTree *P) {
    address child = Right(*P);
    Right(*P) = Left(child);
    Left(child) = *P;
    *P = child; // Langsung mengubah pointer parent-nya
}

// Fungsi  untuk menyeimbangkan node setelah operasi insert atau delete
address BalanceNode(address P) {
    if (P == Nil) {
        return Nil;
    }

    // Hitung Balance Factor (BF)
    int bf = Depth(Left(P)) - Depth(Right(P));

    // KASUS KIRI (Left): Jika BF > 1
    if (bf > 1) {
        // Cek BF dari anak kirinya
        int balLeft = Depth(Left(Left(P))) - Depth(Right(Left(P)));
        
        if (balLeft >= 0) { 
            RotateRight(&P); // Kasus LL
        } else {
            RotateLeft(&Left(P)); // Kasus LR
            RotateRight(&P);
        }
    }

    // KASUS KANAN (Right): Jika BF < -1
    else if (bf < -1) {
        // Cek BF dari anak kanannya
        int balRight = Depth(Left(Right(P))) - Depth(Right(Right(P)));
        
        if (balRight <= 0) {
            RotateLeft(&P); // Kasus RR
        } else {
            RotateRight(&Right(P)); // Kasus RL
            RotateLeft(&P);
        }
    }

    return P;
}