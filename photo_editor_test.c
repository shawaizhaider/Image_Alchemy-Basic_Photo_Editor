#include <stdio.h>
#include "freeimage_declarations.h"

void convertToGrayscale(FIBITMAP* image) {
    unsigned width = FreeImage_GetWidth(image);
    unsigned height = FreeImage_GetHeight(image);
    FREE_IMAGE_TYPE imageType = FreeImage_GetImageType(image);

    for (unsigned y = 0; y < height; y++) {
        for (unsigned x = 0; x < width; x++) {
            RGBQUAD pixel;
            FreeImage_GetPixelColor(image, x, y, &pixel);

            // Convert the pixel to grayscale based on image type
            BYTE gray;
            if (imageType == FIT_BITMAP) {
                // For standard bitmap images (such as PNG)
                gray = (BYTE)(0.299 * pixel.rgbRed + 0.587 * pixel.rgbGreen + 0.114 * pixel.rgbBlue);
            } else if (imageType == FIT_UINT16) {
                // For 16-bit grayscale images
                gray = (BYTE)(0.5 * (pixel.rgbRed + pixel.rgbGreen));
            } else {
                // Add additional cases as needed for other image types
                gray = (BYTE)((pixel.rgbRed + pixel.rgbGreen + pixel.rgbBlue) / 3);
            }

            pixel.rgbRed = pixel.rgbGreen = pixel.rgbBlue = gray;

            FreeImage_SetPixelColor(image, x, y, &pixel);
        }
    }
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_filename> <output_filename>\n", argv[0]);
        return 1;
    }

    const char* inputFilename = argv[1];
    const char* outputFilename = argv[2];

    printf("Input Filename: %s\n", inputFilename);

    // Load an image using FreeImage
    FIBITMAP* image = FreeImage_Load(FIF_PNG, inputFilename, 0);

    if (!image) {
        fprintf(stderr, "Failed to load the image: %s\n", inputFilename);
        return 1;
    }

    printf("Image loaded successfully\n");

    // Perform the image processing
    convertToGrayscale(image);

    // Save the processed image
    FreeImage_Save(FIF_PNG, image, outputFilename, 0);

    // Unload the image
    FreeImage_Unload(image);

    return 0;
}

