/* Nama File : BinSTree.h 	*/
/* Deskripsi : File header untuk ADT Binary Tree Dinamis */
/* Dibuat oleh : Ade Chandra Nugraha */
/* Tanggal     : 22-11-2001 */

#ifndef _BINTREE_H
#define _BINTREE_H
#include <stdio.h>
#include <stdbool.h>
#define Nil NULL
#define Info(T) (T)->info
#define Left(T) (T)->left
#define Right(T) (T)->right
#define InfoList(L) (L)->info
#define Next(L) (L)->next

typedef int infotype;
typedef struct tElmtTree *address;
typedef struct tElmtTree {
	infotype info;
	address left, right;
} Node;	

typedef struct tElmtList *address1;
typedef struct tElmtList {
	infotype info;
	address1 next;
} ElmtList;	

typedef address BinTree;
typedef address1 ListOfNode;


/**** Primitif *****/
/* Selektor */
infotype GetAkar (BinTree P);
/* Mengirimkan informasi yang tersimpan di akar dari pohon Biner yg tdk kosong*/
BinTree GetLeft (BinTree P);
/* Mengirimkan anak kiri pohon biner P yang TIDAK kosong */
BinTree GetRight (BinTree P);
/* Mengirimkan anak kanan pohon biner P yang TIDAK kosong */

/* Konstruktor */
address Alokasi (infotype X);
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika Alokasi berhasil, maka address != Nil dan Info (P) = X */
BinTree Tree (infotype Akar, BinTree L, BinTree R);
/* Menghasilkan sebuah pohon biner dari A, L dan R, jika alokasi berhasil */
/* Menghasilkan pohon kosong (Nil) jika alokasi gagal */
void MakeTree (infotype Akar, BinTree L, BinTree R, BinTree *P);
/* IS : BinTree Sembarang */
/* FS : Menghasilkan sebuah BinTree */
/* Menghasilkan sebuah pohon biner dari A, L dan R, jika alokasi berhasil */
/* Menghasilkan pohon kosong (Nil) jika alokasi gagal */
void BuildTree (BinTree *P);
/* Membentuk sebuah BinTree P dari pita karakter yang dibaca */
/* IS : Pita berisi "konstanta" pohon dalam bentuk prefix. Memori pasti cukup */
/*      Alokasi pasti berhasil */
/* FS : P dibentuk dari ekspresi dalam pita */

/**** Predikat Penting *****/
bool IsUnerLeft (BinTree P);
/* Mengirimkan true jika BinTree tidak kosong */
/* P adalah pohon UnerLeft (hanya mempunyai sub pohon kiri */
bool IsUnerRight (BinTree P);
/* Mengirimkan true jika BinTree tidak kosong */
/* P adalah pohon UnerRight (hanya mempunyai sub pohon kanan */
bool IsBiner (BinTree P);
/* Mengirimkan true jika BinTree tidak kosong */
/* P adalah pohon Biner (mempunyai sub pohon kiri dan sub pohon kanan */
bool IsEmpty (BinTree P);
/* Mengirimkan true jika BinTree KOSONG */
/***** Traversal *****/
void PreOrder (BinTree P);
/* Traversal PreOrder menggunakan Rekursif */
/* IS : P terdefinisi */
/* FS : Semua simpul P sudah diproses secara PreOrder : Akar, Kiri, Kanan */
void InOrder (BinTree P);
/* Traversal InOrder menggunakan Rekursif */
/* IS : P terdefinisi */
/* FS : Semua simpul P sudah diproses secara InOrder : Kiri, Arak, Kanan */
void PostOrder (BinTree P);
/* Traversal PostOrder menggunakan Rekursif */
/* IS : P terdefinisi */
/* FS : Semua simpul P sudah diproses secara PostOrder :  Kiri, Kanan, Akar */
void PrintTree (BinTree P);
/* IS : P terdefinisi, h adalah jarak indentasi */
/* FS : Semua simpul P sudah ditulis dengan indentasi */

/***** Search *****/
bool Search (BinTree P, infotype X);
/* Mengirimkan true jika ada node dari P yang bernilai X */
address SearchAddress (BinTree P, infotype X);
/* Mengirimkan alamat Node jika ada node dari P yang bernilai X */
/* Mengirimkan Nil jika tidak ditemukan. Pencarian dilakukan di seluruh cabang (Pohon Biner Biasa) */

/***** Fungsi Lain *****/
int nbElmt (BinTree P);
/* Mengirimkan banyak elemen (node) pohon biner P */
int nbDaun (BinTree P);
/* Mengirimkan banyak daun (node) pohon biner P */
bool IsSkewLeft (BinTree P);
/* Mengirimkan true jika P adalah pohon condong kiri */
bool IsSkewRight (BinTree P);
/* Mengirimkan true jika P adalah pohon condong kanan */
int Level (BinTree P, infotype X);
/* Mengirimkan level dari node X yang merupakan salah satu simpul dari */
/* pohon biner P. Akar (P) levelnya adalah 1. Pohon tidak kosong */
int Depth (BinTree P);
/* Pohon Biner mungkin Kosong, mengirimkan 'depth' yaitu tinggi dari Pohon */
/* Basis : Pohon Kosong, tingginya Nol */
/* Rekurens : 1 + maksimal (Depth (Anak Kiri), Depth  (Anak Kanan)) */
// int Max (infotype Data1, infotype Data2);
/* Mengirimkan Nilai terbesar dari dua data */

/***** Operasi Lain *****/
void AddDaunTerkiri (BinTree *P, infotype X);
/* Menambah elemen Tree di cabang Kiri dengan alokasi baru */
/* IS : P boleh kosong */
/* FS : P bertambah simpulnya, dengan X sebagai simpul daun terkiri */
void AddDaun (BinTree *P, infotype X, infotype Y, bool Kiri);
/* IS : P tidak kosong, X adalah salah satu daun Pohon Biner P */
/* FS : P bertambah simpulnya, dengan Y sebagai anak kiri X (jika Kiri) */
/*      atau sebagai anak Kanan X (jika NOT Kiri) */
void DelDaunTerkiri (BinTree *T, infotype *X);
/* IS : P TIDAK Kosong */
/* FS : P dihapus daun terkirinya, dan didealokasi, dengan X adalah info */
/*      yang semula disimpan pada daun terkiri yang dihapus */
void DelDaun (BinTree *T, infotype X);
/* IS : P TIDAK kosong, X adalah salah satu daun */
/* FS : X dihapus dari P */

/***** Manipulasi LIST OF NODE *****/
ListOfNode MakeListDaun (BinTree P);
/* Jika P adalah Pohon Kosong, maka menghasilkan List Kosong */
/* Jika P bukan Pohon Kosong, menghasilkan List yang elemennya adalah semua */
/*        daun pohon P, jika semua alokasi berhasil */
/*       		menghasilkan list kosong jika ada alokasi yang gagal */
ListOfNode MakeListPreOrder (BinTree P);
/* Jika P adalah Pohon Kosong, maka menghasilkan List Kosong */
/* Jika P bukan Pohon Kosong, menghasilkan List yang elemennya adalah semua */
/*        elemen pohon P dengan urutan PreOrder, jika semua alokasi berhasil */
/*       		menghasilkan list kosong jika ada alokasi yang gagal */
ListOfNode MakeListLevel (BinTree P, int N);
/* Jika P adalah Pohon Kosong, maka menghasilkan List Kosong */
/* Jika P bukan Pohon Kosong, menghasilkan List yang elemennya adalah semua */
/*        elemen pohon P yang levelnya = N, jika semua alokasi berhasil */
/*       		menghasilkan list kosong jika ada alokasi yang gagal */

/***** Membentuk Balanced Tree *****/
BinTree BuildBalanceTree (int N);
/* Menghasilkan sebuah balance Tree dengan N Node, nilai setiap node dibaca */

/***** Operasi untuk Binary Search Tree *****/
bool BSearch (BinTree P, infotype X);
/* Mengirimkan True jika ada node dari P yang bernilai X */
address BinSearch (BinTree P, infotype X);
/* Mengirimkan alamat Node jika ada node dari P yang bernilai X */
/* Mengirimkan Nil jika tidak ditemukan */
void InsSearch (BinTree *P, infotype X);
/* Menghasilkan sebuah pohon Binary Search Tree P dengan tambahan simpul X. */
/* Belum ada simpul P yang bernilai X */

void DestroyTree (BinTree *P);
/* Menghapus seluruh elemen Tree secara Rekursif */
/* IS : P terdefinisi */
/* FS : Semua simpul P sudah dihapus secara PostOrder :  Kiri, Kanan, Akar */
address getSuccessor(address curr);
/* Mengirimkan alamat node successor (node terkecil di subtree kanan) */
/* IS : curr adalah node yang memiliki anak kanan (Right(curr) != Nil) */
/* FS : Mengirimkan alamat node successor (node terkecil di subtree kanan) */
address getPredecessor(address curr);
/* Mengirimkan alamat node predecessor (node terbesar di subtree kiri) */
/* IS : curr adalah node yang memiliki anak kiri (Left(curr) != Nil) */
/* FS : Mengirimkan alamat node predecessor (node terbesar di subtree kiri) */
address DelBTree (address P, infotype X);
/* IS : Pohon P TIDAK kosong */
/* FS : Nilai X yang dihapus pasti ada, sebuah node dengan nilai X dihapus */
void DelNode (BinTree *P);
/* IS : P adalah pohon biner TIDAK kosong */
/* FS : Q berisi salinan nilai daun terkanan */
void DeAlokasi (address P);
/* IS : P terdefinisi */
/* FS : P dikembalikan ke sistem */
/* Melakukan dealokasi / pengembalian address P ke system */

// tambabhaan insert bst dengan cara lain
void Menu();
void insertWithBST(BinTree T, infotype valNode);

// tambahan AVL
void RotateRight(BinTree *P);
void RotateLeft(BinTree *P);
void PrintTreeDownward(BinTree P);
void PrintTreeDownwardUtil(BinTree P, char *prefix, bool isTail, char *pos);
void SearchBST(BinTree P, infotype X, int kunjungan);
address BalanceNode(address P);

#endif
