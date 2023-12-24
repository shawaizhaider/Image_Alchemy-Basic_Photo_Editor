#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <conio.h>
#include "FreeImage.h"
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))



// Function to set text color on Windows console
void displayTextWithAnimation(const char *text) {
    int len = strlen(text);
    for (int i = 0; i < len; ++i) {
        printf("%c", text[i]);
        Sleep(50); 
    }
}

void displayMainMenu() {
    system("COLOR 0A"); 
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
void arrowHere(int realPosition, int arrowPosition){
    if(realPosition==arrowPosition){
        printf("---->> - ");
    }
    else{
        printf("         ");
    }
}
int selection_menu(){
    system("cls");
    int position = 1;
    int keyPressed = 0;
    while(keyPressed!=13){
    system("cls");
    printf("\n\t\t\t\t\t**********Select your Desired function**********");
    printf("\n\n\n\n\n\n\t\t\t\t\t");
    arrowHere(1,position); printf("1. Convert to Grayscale\n");
    printf("\t\t\t\t\t");
    arrowHere(2,position); printf("2. Apply Gaussian Blur to Images\n");
    printf("\t\t\t\t\t");
    arrowHere(3,position); printf("3. Change Brightness of Image\n");
    printf("\t\t\t\t\t");
    arrowHere(4,position); printf("4. Rotate Image\n");
    printf("\t\t\t\t\t");
    arrowHere(5,position); printf("5. Apply Sepia Filter\n");
    printf("\t\t\t\t\t");
    arrowHere(6,position); printf("6. Flip Horizontal\n");
    printf("\t\t\t\t\t");
    arrowHere(7,position); printf("7. Flip Vertical\n");
    printf("\t\t\t\t\t");
    arrowHere(8,position); printf("8. Crop Image\n");
    printf("\t\t\t\t\t");
    arrowHere(9,position); printf("9. Resize Image\n");
    printf("\t\t\t\t\t");
    arrowHere(10,position); printf("10. Apply Sharpen Filter:\n");
    printf("\t\t\t\t\t");
    arrowHere(11,position); printf("11. Invert Colors of Image(Negative Image).\n");
    printf("\t\t\t\t\t");
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
    return position;
}

// Function to apply a simple grayscale conversion to an image
void convertToGrayscale(FIBITMAP *image) {
    int width = FreeImage_GetWidth(image);
    int height = FreeImage_GetHeight(image);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            RGBQUAD pixel;
            FreeImage_GetPixelColor(image, x, y, &pixel);

            // Convert the pixel to grayscale
            BYTE grayscale = (BYTE)(0.3 * pixel.rgbRed + 0.59 * pixel.rgbGreen + 0.11 * pixel.rgbBlue);

            // Set the pixel to the grayscale value
            pixel.rgbRed = grayscale;
            pixel.rgbGreen = grayscale;
            pixel.rgbBlue = grayscale;

            FreeImage_SetPixelColor(image, x, y, &pixel);
        }
    }
}

void blur(FIBITMAP *image, int radius) {
    int width = FreeImage_GetWidth(image);
    int height = FreeImage_GetHeight(image);

    // Create a temporary image to store the filtered result
    FIBITMAP *filteredImage = FreeImage_Clone(image);

    // Apply the noise reduction filter to each pixel
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int count = 0;
            int accR = 0, accG = 0, accB = 0;

            for (int i = -radius; i <= radius; ++i) {
                for (int j = -radius; j <= radius; ++j) {
                    int xi = x + i;
                    int yj = y + j;

                    if (xi >= 0 && xi < width && yj >= 0 && yj < height) {
                        RGBQUAD pixel;
                        FreeImage_GetPixelColor(image, xi, yj, &pixel);
                        accR += pixel.rgbRed;
                        accG += pixel.rgbGreen;
                        accB += pixel.rgbBlue;
                        count++;
                    }
                }
            }

            RGBQUAD filteredPixel;
            filteredPixel.rgbRed = (BYTE)(accR / count);
            filteredPixel.rgbGreen = (BYTE)(accG / count);
            filteredPixel.rgbBlue = (BYTE)(accB / count);
            FreeImage_SetPixelColor(filteredImage, x, y, &filteredPixel);
        }
    }

    // Copy the filtered image back to the original image
    BYTE *bitsFiltered = FreeImage_GetBits(filteredImage);
    BYTE *bitsImage = FreeImage_GetBits(image);
    memcpy(bitsImage, bitsFiltered, FreeImage_GetPitch(filteredImage) * height);

    FreeImage_Unload(filteredImage);
}

void adjustBrightness(FIBITMAP* image, float factor) {
    int width = FreeImage_GetWidth(image);
    int height = FreeImage_GetHeight(image);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            RGBQUAD color;
            FreeImage_GetPixelColor(image, x, y, &color);

            // Adjust brightness for each channel (RGB)
            color.rgbRed = (BYTE)MIN(255, MAX(0, (int)(color.rgbRed * factor)));
            color.rgbGreen = (BYTE)MIN(255, MAX(0, (int)(color.rgbGreen * factor)));
            color.rgbBlue = (BYTE)MIN(255, MAX(0, (int)(color.rgbBlue * factor)));

            FreeImage_SetPixelColor(image, x, y, &color);
        }
    }
}


// void rotateImage(FIBITMAP *image, double angle) {
//     // Rotate the image and replace the original image with the rotated one
//     FIBITMAP *rotatedImage = FreeImage_Rotate(image, angle, NULL);

//     // Unload the original image
//     FreeImage_Unload(image);

//     // Replace the original image with the rotated one
//     image = rotatedImage;
// }
//change
void rotateImage(FIBITMAP **image, double angle) {
    // Rotate the image and replace the original image with the rotated one
    FIBITMAP *rotatedImage = FreeImage_Rotate(*image, angle, NULL);

    // Unload the original image
    FreeImage_Unload(*image);

    // Replace the original image with the rotated one
    *image = rotatedImage;
}

void applySepiaFilter(FIBITMAP* image) {
    int width = FreeImage_GetWidth(image);
    int height = FreeImage_GetHeight(image);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            RGBQUAD pixel;
            FreeImage_GetPixelColor(image, x, y, &pixel);

            // Calculate sepia values
            int tr = (int)(0.393 * pixel.rgbRed + 0.769 * pixel.rgbGreen + 0.189 * pixel.rgbBlue);
            int tg = (int)(0.349 * pixel.rgbRed + 0.686 * pixel.rgbGreen + 0.168 * pixel.rgbBlue);
            int tb = (int)(0.272 * pixel.rgbRed + 0.534 * pixel.rgbGreen + 0.131 * pixel.rgbBlue);

            // Clamp values to the valid range
            pixel.rgbRed = (BYTE)MIN(255, tr);
            pixel.rgbGreen = (BYTE)MIN(255, tg);
            pixel.rgbBlue = (BYTE)MIN(255, tb);

            FreeImage_SetPixelColor(image, x, y, &pixel);
        }
    }
}
void flipHorizontal(FIBITMAP* image) {
    FreeImage_FlipHorizontal(image);
}

// Function to flip an image vertically
void flipVertical(FIBITMAP* image) {
    FreeImage_FlipVertical(image);
}

// Function to crop an image
// void cropImage(FIBITMAP* image, int startX, int startY, int width, int height) {
//     FIBITMAP* croppedImage = FreeImage_Copy(image, startX, startY, startX + width, startY + height);
//     FreeImage_Unload(image);
//     image = croppedImage;
// }
// change
void cropImage(FIBITMAP** image, int startX, int startY, int width, int height) {
    FIBITMAP* croppedImage = FreeImage_Copy(*image, startX, startY, startX + width, startY + height);
    
    FreeImage_Unload(*image);  // Free memory of the original image
    *image = croppedImage;     // Update the original image pointer
}


//change



// Function to resize an image
// Function to resize an image
// void resizeImage(FIBITMAP* image, int newWidth, int newHeight) {
//     // Resize the image using FreeImage_Rescale
//     FIBITMAP* resizedImage = FreeImage_Rescale(image, newWidth, newHeight, FILTER_BICUBIC);

//     // Unload the original image
//     FreeImage_Unload(image);

//     // Replace the original image with the resized one
//     image = resizedImage;
// }
// change
void resizeImage(FIBITMAP** image, int newWidth, int newHeight) {
    // Resize the image using FreeImage_Rescale
    FIBITMAP* resizedImage = FreeImage_Rescale(*image, newWidth, newHeight, FILTER_BICUBIC);

    // Unload the original image
    FreeImage_Unload(*image);

    // Replace the original image with the resized one
    *image = resizedImage;
}


void applySharpenFilter(FIBITMAP* image) {
    int width = FreeImage_GetWidth(image);
    int height = FreeImage_GetHeight(image);

    FIBITMAP* originalImage = FreeImage_Clone(image);

    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            RGBQUAD pixel;
            FreeImage_GetPixelColor(originalImage, x, y, &pixel);

            RGBQUAD leftPixel, rightPixel, topPixel, bottomPixel;
            FreeImage_GetPixelColor(originalImage, x - 1, y, &leftPixel);
            FreeImage_GetPixelColor(originalImage, x + 1, y, &rightPixel);
            FreeImage_GetPixelColor(originalImage, x, y - 1, &topPixel);
            FreeImage_GetPixelColor(originalImage, x, y + 1, &bottomPixel);

            // Apply simple sharpening filter
            pixel.rgbRed = (BYTE)MIN(255, MAX(0, (int)(1.5 * pixel.rgbRed - 0.25 * (leftPixel.rgbRed + rightPixel.rgbRed + topPixel.rgbRed + bottomPixel.rgbRed))));
            pixel.rgbGreen = (BYTE)MIN(255, MAX(0, (int)(1.5 * pixel.rgbGreen - 0.25 * (leftPixel.rgbGreen + rightPixel.rgbGreen + topPixel.rgbGreen + bottomPixel.rgbGreen))));
            pixel.rgbBlue = (BYTE)MIN(255, MAX(0, (int)(1.5 * pixel.rgbBlue - 0.25 * (leftPixel.rgbBlue + rightPixel.rgbBlue + topPixel.rgbBlue + bottomPixel.rgbBlue))));

            FreeImage_SetPixelColor(image, x, y, &pixel);
        }
    }

    FreeImage_Unload(originalImage);
}
void invertColors(FIBITMAP* image) {
    int width = FreeImage_GetWidth(image);
    int height = FreeImage_GetHeight(image);

    FREE_IMAGE_TYPE imageType = FreeImage_GetImageType(image);

    if (imageType == FIT_BITMAP) {
        // Check if the image is grayscale
        if (FreeImage_GetBPP(image) == 8) {
            // Grayscale image
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    BYTE pixelValue;
                    FreeImage_GetPixelIndex(image, x, y, &pixelValue);

                    // Invert grayscale value
                    pixelValue = 255 - pixelValue;

                    FreeImage_SetPixelIndex(image, x, y, &pixelValue);
                }
            }
        } else {
            // Color image
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    RGBQUAD pixel;
                    FreeImage_GetPixelColor(image, x, y, &pixel);

                    // Invert color values
                    pixel.rgbRed = 255 - pixel.rgbRed;
                    pixel.rgbGreen = 255 - pixel.rgbGreen;
                    pixel.rgbBlue = 255 - pixel.rgbBlue;

                    FreeImage_SetPixelColor(image, x, y, &pixel);
                }
            }
        }
    }
}
// Function to apply a custom artistic filter to an image
void applyArtisticFilter(FIBITMAP *image) {
    int width = FreeImage_GetWidth(image);
    int height = FreeImage_GetHeight(image);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            RGBQUAD pixel;
            FreeImage_GetPixelColor(image, x, y, &pixel);

            // Apply a custom artistic filter to manipulate colors
            // You can experiment with different color transformations
            pixel.rgbRed = (BYTE)(pixel.rgbRed * 0.7);
            pixel.rgbGreen = (BYTE)(pixel.rgbGreen * 1.2);
            pixel.rgbBlue = (BYTE)(pixel.rgbBlue * 0.8);

            FreeImage_SetPixelColor(image, x, y, &pixel);
        }
    }
}


int main() {
    system("cls");
    displayMainMenu();
    char choice_m='y';
    printf("\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t");
    printf("*****Wanna edit catchy pictures? You are at right place*****\n\n");
    printf("\t\t\t\t");
    printf("Help: Path is the location of your image.\n");
    printf("\t\t");
    printf("   (If your image and photo editor are in same folder just type its name with extension)");
    do{
    int radius;
    char str[200];
    char *ptr = str;
    printf("\t\t\t\t\t");
    printf("\t\tEnter the path of Picture you want to edit: ");
    fflush(stdin);
    gets(str);
    while (*ptr != '\0') {
        if (*ptr == '\\') {
            *ptr = '/';
        }
        ptr++;
    }

    int a = strlen(str);
    char str_final[a];
    strcpy(str_final, str);
    // printf("Your string length is %d.\n", a);
    printf("\n\n\n");
    printf("\t\t\t\t\tYour entered path is: ");
    puts(str_final);

    // Load an image (replace "input.jpg" with your image file)
    const char *inputFileName = str_final;
    FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(inputFileName, 0);

    while (fif == FIF_UNKNOWN)
    {
        printf("\n\t\t\t\t\tUnsupported image format. Try again \n");
        fflush(stdin);
        gets(str);
        ptr=str;
        while (*ptr != '\0') {
        if (*ptr == '\\') {
            *ptr = '/';
        }
        ptr++;
        
    }

    a = strlen(str);
    str_final[a];
    strcpy(str_final, str);
    // printf("Your string length is %d.\n", a);
    printf("\n\t\t\tYour entered path is: ");
    puts(str_final);
    inputFileName = str_final;
    fif = FreeImage_GetFileType(inputFileName, 0);
    if(fif!=FIF_UNKNOWN){
        break;
    }
    }

    FIBITMAP *image = FreeImage_Load(fif, inputFileName, 0);

    while (!image) {
        printf("\n\t\t\t\t\tError loading image,try again: \n");
        gets(str);
        ptr=str;
        while (*ptr != '\0') {
        if (*ptr == '\\') {
            *ptr = '/';
        }
        ptr++;
        
    }

    a = strlen(str);
    str_final[a];
    strcpy(str_final, str);
    // printf("Your string length is %d.\n", a);
    printf("\t\t\t\t\tYour entered path is: ");
    puts(str_final);
    inputFileName=str_final;
    FIBITMAP *image = FreeImage_Load(fif, inputFileName, 0);
    }
    system("cls");
    printf("\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t");
    printf("Image Loaded successfully ");
    printf("\n\t\t\t\t");
    printf("Press any key to continue...");
    getch();
    fflush(stdin);
    // selection_menu();
    printf("\n\n\n\n\n\n\t\t\t\t");
    int choice=selection_menu();
    float factor;
    double angle;
    int startX = 50;
    int startY = 30;
    int width = 100;
    int height = 100;
    // printf("Enter your choice (1  to 12): ");
    // scanf("%d", &choice);

    switch (choice) {
        case 1:
            system("cls");
            system("COLOR D7");
            convertToGrayscale(image);
            break;
        case 2:
            system("cls");
            system("COLOR 40");
            // Ask the user for the radius parameter
            // int radius
            printf("\n\n\n\t\t\t\tEnter the radius for blur from one to ten : ");
            scanf("%d", &radius);
            blur(image, radius);
            break;
        case 3:
            system("cls");
            system("COLOR A0");
            printf("\n\n\n\t\t\t\tEnter the factor for brightness:(max 2)\n");
            scanf("%f",&factor);
            adjustBrightness(image,factor);
        break;    
        case 4:
            system("cls");
            system("COLOR B0");
            printf("\n\n\n\t\t\t\tEnter the angle in degrees to rotate the image:\n");
            scanf("%lf",&angle);
            rotateImage(&image,angle);
            break;
        case 5:
            system("cls");
            system("COLOR 27");
            applySepiaFilter(image);
            break;
        case 6:
            system("cls");
            system("COLOR 1F");
            flipHorizontal(image);
            break;
        case 7:
            system("cls");
            system("COLOR 50");
            flipVertical(image);
            break;
        case 8:
            system("cls");
            system("COLOR 47");
            printf("\n\n\n\t\t\t\tEnter the value of startX:\n");
            scanf("%d",&startX);
            printf("\n\n\n\t\t\t\tEnter the value of StartY.\n");
            fflush(stdin);
            scanf("%d",&startY);
            printf("\n\n\n\t\t\t\tEnter the width:\n");
            fflush(stdin);
            scanf("%d",&width);
            printf("\n\n\n\t\t\t\tEnter the height:\n");
            fflush(stdin);
            scanf("%d",&height);
            cropImage(&image,startX,startY,width,height);
            break;
        case 9:
            system("cls");
            system("COLOR 60");
            printf("\n\n\n\t\t\t\tEnter the new width of the image:\n");
            fflush(stdin);
            scanf("%d",&width);
            printf("\n\n\n\t\t\t\tEnter the new height of the image:\n");
            fflush(stdin);
            scanf("%d",&height);
            resizeImage(&image,width,height);
            break;
        case 10:
            system("cls");
            system("COLOR B0");
            applySharpenFilter(image);
            break;   
        case 11:
            system("cls");
            system("COLOR 5F");
            invertColors(image);
            break; 
        case 12:
            system("cls");
            system("COLOR 17");
            applyArtisticFilter(image);
            break;
    
        default:
            fprintf(stderr, "Invalid choice\n");
            FreeImage_Unload(image);
            return 1;
    }
    

    // for different file types
    char output[50];
    const char *extension = NULL;

    switch (fif) {
        case FIF_JPEG:
            extension = "jpg";
            break;
        case FIF_PNG:
            extension = "png";
            break;
        default:
            fprintf(stderr, "Unsupported image format\n");
            FreeImage_Unload(image);
            return 1;
    }

    printf("Enter the name of the output file without extension: ");
    fflush(stdin);
    gets(output);

    strcat(output, ".");
    strcat(output, extension);

    if (!FreeImage_Save(fif, image, output, 0)) {
        fprintf(stderr, "Error saving image\n");
        FreeImage_Unload(image);
        printf("Program has ben crashed, press any key to exit...");
        getch();
        return 1;
    }

    FreeImage_Unload(image);

    printf("Image processed successfully. Saved as %s\n", output);
    printf("Do you want to edit another picture.\n");
    scanf(" %c",&choice_m);
    }while((choice_m=='y')||(choice_m=='Y'));
    if(choice_m!='y'&&choice_m!='Y'){
        printf("\t\t\t\tThanks for using our photo editor.\n");
        printf("\t\t\t\tHave a nice day :)\n");
    }
    printf("Press any key to exit...");
    getch();

    return 0;
}