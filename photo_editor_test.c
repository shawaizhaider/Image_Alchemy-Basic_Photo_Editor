#include <stdio.h>
#include "D:\New folder\OneDrive - National University of Sciences & Technology\Programs\FreeImage3180Win32Win64\FreeImage\Dist\x32\FreeImage.h"
#include <string.h>
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

int main() {
    char inputFileName[256];  // Assuming a reasonable maximum length for the file path

    // Prompt the user to enter the image file path
    printf("Enter the path of the image file: ");
    fgets(inputFileName, sizeof(inputFileName), stdin);
    inputFileName[strcspn(inputFileName, "\n")] = '\0';  // Remove the trailing newline character, if any

    // Load the image based on the user-provided file path
    FIBITMAP *image = FreeImage_Load(FIF_JPEG, inputFileName, JPEG_DEFAULT);

if (!image) {
    fprintf(stderr, "Error loading image\n");
    fprintf(stderr, "File Location: %s\n", inputFileName);
    return 1;
}

    // Apply a simple grayscale conversion
    convertToGrayscale(image);

    // Save the processed image
    const char *outputFileName = "output.jpg";
    if (!FreeImage_Save(FIF_JPEG, image, outputFileName, JPEG_DEFAULT)) {
        fprintf(stderr, "Error saving image\n");
        FreeImage_Unload(image);
        return 1;
    }

    // Unload the image
    FreeImage_Unload(image);

    printf("Image processed successfully. Saved as %s\n", outputFileName);

    return 0;
}
