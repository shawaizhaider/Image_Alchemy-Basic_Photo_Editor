#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

void selection_menu(){
    system("cls");
    int position = 1;
    int keyPressed = 0;
    while(keyPressed!=13){
    system("cls");
    arrowHere(1,position); printf("1. Convert to Grayscale\n");
    arrowHere(2,position); printf("2. Apply Gaussian Blur to Images\n");
    arrowHere(3,position); printf("3. Change Brightness of Image\n");
    arrowHere(4,position); printf("4. Rotate Image\n");
    arrowHere(5,position); printf("5. Apply Sepia Filter\n");
    arrowHere(6,position); printf("6. Flip Horizontal\n");
    arrowHere(7,position); printf("7. Flip Vertical\n");
    arrowHere(8,position); printf("8. Crop Image\n");
    arrowHere(9,position); printf("9. Resize Image\n");
    arrowHere(10,position); printf("10. Apply Sharpen Filter:\n");
    arrowHere(11,position); printf("11. Invert Colors of Image(Negative Image).\n");
    arrowHere(12,position); printf("12. Apply Artistic Filter\n");
    keyPressed = getch(); 
    fflush(stdin);

    // 80 is ascii value for down key
    if(keyPressed==80 && position!=12){
        position++;
    }
    // 72 is ascii value for up key
    else if(keyPressed==72 && position!=1){
        position--;
    }
    else{
        position=position;
    }
    }
    printf("The user selected opten#%d",position);
}
void arrowHere(int realPosition, int arrowPosition){
    if(realPosition==arrowPosition){
        printf("---->> - ");
    }
    else{
        printf("         ");
    }
}
int main()
{
    system("cls");
    selection_menu();
return 0;
}