// photo_editor_test.c
#include <stdio.h>
#include "freeimage_declarations.h"

void convertToGrayscale(FIBITMAP* image) {
    unsigned width = FreeImage_GetWidth(image);
    unsigned height = FreeImage_GetHeight(image);

    for (unsigned y = 0; y < height; y++) {
        for (unsigned x = 0; x < width; x++) {
            RGBQUAD pixel;
            FreeImage_GetPixelColor(image, x, y, &pixel);

            // Convert the pixel to grayscale
            BYTE gray = (BYTE)((pixel.rgbRed + pixel.rgbGreen + pixel.rgbBlue) / 3);

            pixel.rgbRed = pixel.rgbGreen = pixel.rgbBlue = gray;

            FreeImage_SetPixelColor(image, x, y, &pixel);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_path> <output_path>\n", argv[0]);
        return 1;
    }

    const char* inputPath = argv[1];
    const char* outputPath = argv[2];

    // Load an image using FreeImage
    FIBITMAP* image = FreeImage_Load(FIF_JPEG, inputPath, 0);

    if (!image) {
        fprintf(stderr, "Failed to load the image: %s\n", inputPath);
        return 1;
    }

    // Print some debug information about the image
    unsigned width = FreeImage_GetWidth(image);
    unsigned height = FreeImage_GetHeight(image);
    printf("Image loaded successfully: %s\n", inputPath);
    printf("Image dimensions: %u x %u\n", width, height);

    // Perform the image processing
    convertToGrayscale(image);

    // Save the processed image
    if (FreeImage_Save(FIF_PNG, image, outputPath, 0)) {
        printf("Image processed successfully. Output saved to: %s\n", outputPath);
    } else {
        fprintf(stderr, "Failed to save the processed image: %s\n", outputPath);
    }

    // Unload the image
    FreeImage_Unload(image);

    return 0;
}
