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

            // Convert the pixel to grayscale using luminosity method
            BYTE gray = (BYTE)(0.21 * pixel.rgbRed + 0.72 * pixel.rgbGreen + 0.07 * pixel.rgbBlue);

            pixel.rgbRed = pixel.rgbGreen = pixel.rgbBlue = gray;

            FreeImage_SetPixelColor(image, x, y, &pixel);
        }
    }
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_image_path> <output_image_path>\n", argv[0]);
        return 1;
    }

    const char *inputPath = argv[1];
    const char *outputPath = argv[2];

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

        // Perform the image processing
        convertToGrayscale(image);

        // Save the processed image
        if (!FreeImage_Save(FIF_PNG, image, outputPath, 0)) {
            fprintf(stderr, "Failed to save the image: %s\n", outputPath);
            FreeImage_Unload(image);
            return 1;
        }
        FREE_IMAGE_TYPE imageType = FreeImage_GetImageType(image);
        printf("Image Type: %d\n", imageType);


        // Unload the image
        FreeImage_Unload(image);
        return 0;
    } else {
        fprintf(stderr, "Unsupported image format.\n");
        return 1;
    }
}
