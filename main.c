#include "BinSTree.h"
#include <stdio.h>
#include <stdbool.h>


// Prototipe fungsi penghitung langkah (pastikan sudah ditaruh di BinSTree.h juga)
int GetSearchStepsBST(BinTree P, infotype X, int langkah);
int GetSearchStepsList(address1 First, infotype X);
void InsertLastList(address1 *First, infotype X);

int main(){
    BinTree T = Nil;
    address1 HeadList = Nil;
    int pilihan;
    infotype valNode;

    do {
        Menu();
        scanf("%d", &pilihan);
    
        switch (pilihan){
        case 1:
            printf("input info node baru: ");
            scanf("%d", &valNode);
            InsSearch(&T, valNode);
            printf("Node %d berhasil diinsert.\n", valNode);
            break;
        case 2:
            if(IsEmpty(T)) printf("Pohon Kosong.\n");
            else PrintTreeDownward(T);
            break;
        case 3:
            printf("input info node yang ingin dihapus: ");
            scanf("%d", &valNode);
            T = DelBTree(T, valNode);
            printf("Node %d berhasil dihapus dari BST.\n", valNode);
            break;
        case 4:
            printf("input info node yang dicari: ");
            scanf("%d", &valNode);
            SearchBST(T, valNode, 1);
            break;
        case 5:
            printf("\n=================================================================\n");
            printf("      SIMULASI MISI 3: PERBANDINGAN BST vs LINKED LIST           \n");
            printf("=================================================================\n");
            
            // 1. Siapkan data awal
            int data_pegawai[] = {45, 87, 65, 39, 92, 88, 73, 58, 47, 62, 59, 64, 11, 41};
            int target_cari[] = {45, 39, 64, 41, 92, 47, 99}; // 99 adalah data tidak ada
            
            BinTree SimTree = Nil;
            address1 SimList = Nil;

            // 2. Build Tree dan Build List
            for (int i = 0; i < 14; i++) {
                InsSearch(&SimTree, data_pegawai[i]); // Insert ke BST (Punyamu sudah AVL!)
                InsertLastList(&SimList, data_pegawai[i]); // Insert ke Linked List
            }

            // 3. Cetak Tabel Perbandingan
            printf("%-10s | %-12s | %-20s | %-15s\n", "ID Dicari", "Langkah BST", "Langkah Linked List", "Lebih Cepat");
            printf("-----------------------------------------------------------------\n");
            
            for (int i = 0; i < 7; i++) {
                int id = target_cari[i];
                int stepBST = GetSearchStepsBST(SimTree, id, 1);
                int stepList = GetSearchStepsList(SimList, id);
                
                char pemenang[15];
                if (stepBST < stepList) sprintf(pemenang, "BST");
                else if (stepList < stepBST) sprintf(pemenang, "Linked List");
                else sprintf(pemenang, "Seri");

                printf("%-10d | %-12d | %-20d | %-15s\n", id, stepBST, stepList, pemenang);
            }
            printf("=================================================================\n");
            
            // Bersihkan memori simulasi tree (opsional)
            DestroyTree(&SimTree);
            break;
        case 6:
            printf("Exiting program.\n");
            break;
        }

    } while (pilihan != 6);

    return 0;
}