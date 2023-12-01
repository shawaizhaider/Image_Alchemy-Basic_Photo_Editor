#include <stdio.h>
#include "D:\New folder\OneDrive - National University of Sciences & Technology\Programs\FreeImage3180Win32Win64\FreeImage\Dist\x32\FreeImage.h"
#undef main
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

int main() {
    // Load an image (replace "input.jpg" with your image file)
    const char *inputFileName = "D:\\New folder\\OneDrive - National University of Sciences & Technology\\Pictures\\Saved Pictures\\Class photos\\WhatsApp Image 2023-10-27 at 20.38.27_df1e4b1a.jpg";
    FIBITMAP *image = FreeImage_Load(FIF_JPEG, inputFileName, JPEG_DEFAULT);

    if (!image) {
        fprintf(stderr, "Error loading image\n");
        return 1;
    }

    // Apply a simple grayscale conversion
    convertToGrayscale(image);

    // Save the processed image (replace "output.jpg" with your desired output file)
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
