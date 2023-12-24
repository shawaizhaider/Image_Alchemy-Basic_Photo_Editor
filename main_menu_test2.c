#include <stdio.h>
#include <stdlib.h>
#include <windows.h> 
#include <conio.h>
void displayTextWithAnimation(const char *text) {
    int len = strlen(text);
    for (int i = 0; i < len; ++i) {
        printf("%c", text[i]);
        Sleep(50); 
    }
}

void displayMainMenu() {
    system("COLOR EA"); 
    printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t");
    displayTextWithAnimation("WELCOME TO OUR CEP PROJECT\n");
    printf("\t\t\t\t");
    char arrow1=17;
    char arrow2=16;
    printf("     %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",arrow1,arrow1,arrow1,arrow1,arrow1,arrow1,arrow1,arrow1,arrow1,arrow1,arrow1,arrow1,arrow1,arrow1,arrow1,arrow1,arrow1,arrow1,arrow1,arrow1,arrow1,arrow1,arrow1,arrow1,arrow1,arrow2,arrow2,arrow2,arrow2,arrow2,arrow2,arrow2,arrow2,arrow2,arrow2,arrow2,arrow2,arrow2,arrow2,arrow2,arrow2,arrow2,arrow2,arrow2,arrow2,arrow2,arrow2,arrow2,arrow2,arrow2,arrow2);
    printf("\t\t\t\t");
    displayTextWithAnimation("PRESENTING YOU THE BEST PHOTO EDITING SOFTWARE OF THE CENTURY\n");
    printf("Press any key to continue...");
    getch(); 
    system("cls"); 
    system("COLOR 30");
    printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t");
    displayTextWithAnimation("Developers\n");
    printf("\t\t\t\t\t\t");
    displayTextWithAnimation("1) Shawaiz Haider\n");
    printf("\t\t\t\t\t\t");
    displayTextWithAnimation("2) Sannan Shahid\n");

    printf("Press any key to continue...");
    getch(); 
    system("cls");
}

int main() {
    displayMainMenu();
    return 0;
}
