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
            printf("Node %d berhasil diproses ke dalam BST.\n", valNode);
            break;
        case 2:
            if(IsEmpty(T)) printf("Pohon Kosong.\n");
            else PrintTree(T);
            break;
        case 3:
            printf("Exiting program.\n");
            break;
        default:
            break;
        }

    } while (pilihan != 3);

    return 0;
}