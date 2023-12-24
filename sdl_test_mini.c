#include "src\include\SDL2\SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FreeImage.h"

// Function declarations
void convertToGrayscale(FIBITMAP *image){
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
void blur(FIBITMAP *image, int radius){
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
void processImage(const char *inputFileName, const char *outputFileName, int operation, int radius){
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
    printf("\n Select an operation to perfrom:\n");
    scanf("%d",&operation);
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
// Function to display a message box and get user's choice
int showMessageBox(const char *title, const char *message) {
    const SDL_MessageBoxButtonData buttons[] = {
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Grayscale" },
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Blur" },
        { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "Cancel" },
    };

    const SDL_MessageBoxColorScheme colorScheme = {
        { /* .colors (.r, .g, .b) */
            /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
            { 255, 0, 0 },
            /* [SDL_MESSAGEBOX_COLOR_TEXT] */
            { 0, 255, 0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
            { 255, 255, 0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
            { 0, 0, 255 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
            { 255, 0, 255 }
        }
    };

    SDL_MessageBoxData messageboxdata = {
        SDL_MESSAGEBOX_INFORMATION, /* .flags */
        NULL,                       /* .window */
        title,                      /* .title */
        message,                    /* .message */
        SDL_arraysize(buttons),     /* .numbuttons */
        buttons,                    /* .buttons */
        &colorScheme                /* .colorScheme */
    };

    int buttonId;
    if (SDL_ShowMessageBox(&messageboxdata, &buttonId) < 0) {
        fprintf(stderr, "Error displaying message box: %s\n", SDL_GetError());
        return -1;
    }

    return buttonId;
}

// Callback function for the "Process" button
void process_button_clicked(SDL_Renderer *renderer, const char *inputPath, const char *outputName, int operation, int radius) {
    // Process the image
    processImage(inputPath, outputName, operation, radius);

    // Display a message indicating successful processing
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Image Processed", "Image processed successfully.", NULL);
}

// Thread function to handle image processing
int thread_function(void *data) {
    SDL_Renderer *renderer = (SDL_Renderer *)data;

    // Ask the user which function to apply
    int choice = showMessageBox("Function Selection", "Choose a function to apply:");

    if (choice == -1 || choice == 2) {
        // User canceled or there was an error
        return 0;
    }

    // Load an image (replace "input.jpg" with your image file)
    const char *inputPath = "sample_.bmp";
    const char *outputName = "output.jpg";

    // Apply the selected operation
    switch (choice) {
        case 0:
            process_button_clicked(renderer, inputPath, outputName, 1, 0);
            break;
        case 1:
            process_button_clicked(renderer, inputPath, outputName, 2, 5); // Adjust radius as needed
            break;
        default:
            fprintf(stderr, "Invalid choice\n");
            break;
    }

    return 0;
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

    // Create a thread for image processing
    SDL_Thread *thread = SDL_CreateThread(thread_function, "ImageProcessingThread", (void *)renderer);

    // Event handling
    SDL_Event e;
    int quit = 0;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // Clear the renderer
        SDL_RenderClear(renderer);

        // Present the renderer
        SDL_RenderPresent(renderer);
    }

    // Wait for the thread to finish
    int threadReturnValue;
    SDL_WaitThread(thread, &threadReturnValue);

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
