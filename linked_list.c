#include "BinSTree.h"
#include <stdlib.h>

/* ============================================================
   1. ALOKASI & KONSTRUKTOR (Bikin Node & List)
   ============================================================ */
/* Pesan memori untuk node baru */
address1 AlokasiList (infotype X) {
    address1 P = (address1) malloc(sizeof(ElmtList));
    if (P != Nil) {
        InfoList(P) = X;
        Next(P) = Nil;
    }
    return P;
}

/* Fungsi untuk menambah node di akhir Linked List */
void InsertLastList(address1 *First, infotype X) {
    address1 P = AlokasiList(X);
    if (P != Nil) {
        if (*First == Nil) {
            *First = P;
        } else {
            address1 Last = *First;
            while (Next(Last) != Nil) {
                Last = Next(Last);
            }
            Next(Last) = P;
        }
    }
}

/* Fungsi untuk menghitung langkah pencarian di Linked List */
int GetSearchStepsList(address1 First, infotype X) {
    address1 P = First;
    int langkah = 1;
    while (P != Nil) {
        if (InfoList(P) == X) return langkah;
        langkah++;
        P = Next(P);
    }
    return langkah - 1; // Jika tidak ketemu sampai akhir list
}

/* Membentuk sebuah ListOfNode dari BinTree P */
ListOfNode BuildList (BinTree P) {
    ListOfNode L = Nil;
    // Implementasi fungsi BuildList
    return L;
}

void Menu() {
    printf("\n=== BINARY SEARCH TREE & LINKED LIST ===\n");
    printf("1. Insert Node (BST)\n");
    printf("2. Print Tree (BST)\n");
    printf("3. Delete Node (BST)\n");
    printf("4. Search Node (BST)\n");
    printf("5. Simulasi Misi 3 (Tabel Perbandingan)\n");
    printf("6. Exit\n");
    printf("Pilihan: ");
}
