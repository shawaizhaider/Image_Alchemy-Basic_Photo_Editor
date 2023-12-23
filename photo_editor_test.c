// photo_editor_test.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FreeImage.h"

// Function to apply a simple averaging filter for noise reduction
void applyNoiseReduction(FIBITMAP* image, int radius) {
    int width = FreeImage_GetWidth(image);
    int height = FreeImage_GetHeight(image);

    // Create a temporary image to store the filtered result
    FIBITMAP* filteredImage = FreeImage_Clone(image);

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
    FreeImage_Unload(image);
    image = FreeImage_Clone(filteredImage);
    FreeImage_Unload(filteredImage);
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <input_image_path> <output_image_path> <operation> <radius>\n", argv[0]);
        fprintf(stderr, "Available operations: noise_reduction, grayscale\n");
        return 1;
    }

    const char *inputPath = argv[1];
    const char *outputPath = argv[2];
    const char *operation = argv[3];
    int radius = atoi(argv[4]);  // Convert radius argument to an integer

    FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(inputPath, 0);
    if (fif == FIF_UNKNOWN) {
        fif = FreeImage_GetFIFFromFilename(inputPath);
    }

    if ((fif != FIF_UNKNOWN) && FreeImage_FIFSupportsReading(fif)) {
        FIBITMAP* image = FreeImage_Load(fif, inputPath, 0);

        if (!image) {
            fprintf(stderr, "Failed to load the image: %s\n", inputPath);
            return 1;
        }

        // Perform the selected operation
        if (strcmp(operation, "noise_reduction") == 0) {
            // Apply simple averaging filter for noise reduction
            applyNoiseReduction(image, radius);
        } else if (strcmp(operation, "grayscale") == 0) {
            // Convert the image to grayscale
            FIBITMAP* grayscaleImage = FreeImage_ConvertToGreyscale(image);
            FreeImage_Unload(image);
            image = grayscaleImage;
        } else {
            fprintf(stderr, "Unknown operation: %s\n", operation);
            FreeImage_Unload(image);
            return 1;
        }

        // Save the processed image
        if (!FreeImage_Save(FIF_PNG, image, outputPath, 0)) {
            fprintf(stderr, "Failed to save the image: %s\n", outputPath);
            FreeImage_Unload(image);
            return 1;
        }

        // Unload the image
        FreeImage_Unload(image);
        return 0;
    } else {
        fprintf(stderr, "Unsupported image format.\n");
        return 1;
    }
}
