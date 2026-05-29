#include "BinSTree.h"
#include <stdio.h>
#include <stdbool.h>

int main(){
    BinTree T = Nil;
    int pilihan;
    infotype valNode, parentVal;
    char posisi;

    do {
        Menu();
        scanf("%d", &pilihan);
    
        switch (pilihan){
        case 1:
            printf("input info node baru: ");
            scanf("%d", &valNode);
            
            InsSearch(&T, valNode); 
            
            printf("Node %d berhasil diproses & diseimbangkan dengan AVL.\n", valNode);
            break;
        case 2:
            if(IsEmpty(T)) printf("Pohon Kosong.\n");
            else PrintTreeDownward(T);
            break;
        case 3:
            printf("input info node yang dicari: ");
            scanf("%d", &valNode);
            SearchBST(T, valNode, 1);
            break;
        case 4:
            printf("Exiting program.\n");
            break;
        }

    } while (pilihan != 4);

    return 0;
}