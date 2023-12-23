#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FreeImage.h"

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

int main() {
    int radius;
    char str[200];
    char *ptr = str;
    printf("Enter the path: ");
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
    printf("Your string length is %d.\n", a);
    printf("Your entered path is: ");
    puts(str_final);

    // Load an image (replace "input.jpg" with your image file)
    const char *inputFileName = str_final;
    FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(inputFileName, 0);

    if (fif == FIF_UNKNOWN) {
        fprintf(stderr, "Unsupported image format\n");
        return 1;
    }

    FIBITMAP *image = FreeImage_Load(fif, inputFileName, 0);

    if (!image) {
        fprintf(stderr, "Error loading image\n");
        return 1;
    }

    // Ask the user which operation to apply
    printf("Choose an operation:\n");
    printf("1. Convert to Grayscale\n");
    printf("2. Apply Gaussian Blur to Images\n");

    int choice;
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            convertToGrayscale(image);
            break;
        case 2:
            // Ask the user for the radius parameter
            // int radius
            printf("Enter the radius for blur from one to ten : ");
            scanf("%d", &radius);
            blur(image, radius);
            break;
        default:
            fprintf(stderr, "Invalid choice\n");
            FreeImage_Unload(image);
            return 1;
    }

    // Save the processed image
    char output[50];
    const char *extension = NULL;

    switch (fif) {
        case FIF_JPEG:
            extension = "jpg";
            break;
        case FIF_PNG:
            extension = "png";
            break;
        // Add more cases for other supported formats as needed
        default:
            fprintf(stderr, "Unsupported image format\n");
            FreeImage_Unload(image);
            return 1;
    }

    // Ask the user for the output file name
    printf("Enter the name of the output file without extension: ");
    fflush(stdin);
    gets(output);

    // Concatenate the output file name with the determined extension
    strcat(output, ".");
    strcat(output, extension);

    if (!FreeImage_Save(fif, image, output, 0)) {
        fprintf(stderr, "Error saving image\n");
        FreeImage_Unload(image);
        return 1;
    }

    // Unload the image
    FreeImage_Unload(image);

    printf("Image processed successfully. Saved as %s\n", output);

    return 0;
}
