#include "src\include\SDL2\SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FreeImage.h"

// Function declarations
void convertToGrayscale(FIBITMAP *image);
void blur(FIBITMAP *image, int radius);
void processImage(const char *inputFileName, const char *outputFileName, int operation, int radius);

// Callback function for the "Process" button
void process_button_clicked(SDL_Renderer *renderer, const char *inputPath, const char *outputName, int operation, int radius) {
    // Process the image
    processImage(inputPath, outputName, operation, radius);

    // Display a message indicating successful processing
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Image Processed", "Image processed successfully.", NULL);
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

// Function to apply a blur filter to an image
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

// Function to process the image based on the chosen operation
void processImage(const char *inputFileName, const char *outputFileName, int operation, int radius) {
     radius;
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
    inputFileName = str_final;
    FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(inputFileName, 0);

    if (fif == FIF_UNKNOWN) {
        fprintf(stderr, "Unsupported image format\n");
        return;
    }

    FIBITMAP *image = FreeImage_Load(fif, inputFileName, 0);

    if (!image) {
        fprintf(stderr, "Error loading image\n");
        return;
    }

    // Apply the selected operation
    switch (operation) {
        case 1:
            convertToGrayscale(image);
            break;
        case 2:
            blur(image, radius);
            break;
        default:
            fprintf(stderr, "Invalid operation\n");
            FreeImage_Unload(image);
            // Additional cleanup and error handling if needed
            return;
    }

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
            return;
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
        return;
    }

    // Unload the image
    FreeImage_Unload(image);

    printf("Image processed successfully. Saved as %s\n", output);

}

int main(int argc, char *argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window and renderer
    SDL_Window *window = SDL_CreateWindow("Image Processor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Event handling
    SDL_Event e;
    int quit = 0;

    // Create texture for the background
    SDL_Surface *backgroundSurface = SDL_LoadBMP("sample_.bmp");
    SDL_Texture *backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    // Create texture for the button
    SDL_Surface *buttonSurface = SDL_LoadBMP("button.bmp");
    SDL_Texture *buttonTexture = SDL_CreateTextureFromSurface(renderer, buttonSurface);
    SDL_FreeSurface(buttonSurface);

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
            // Handle button click event
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);

                // Check if the click is within the button area
                if (x >= 300 && x <= 500 && y >= 400 && y <= 500) {
                    // Call the process_button_clicked function
                    process_button_clicked(renderer, "input.jpg", "output.jpg", 1, 0);
                }
            }
        }

        // Clear the renderer
        SDL_RenderClear(renderer);

        // Draw the background
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        // Draw the button
        SDL_Rect buttonRect = {300, 400, 200, 100};
        SDL_RenderCopy(renderer, buttonTexture, NULL, &buttonRect);

        // Present the renderer
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(buttonTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
