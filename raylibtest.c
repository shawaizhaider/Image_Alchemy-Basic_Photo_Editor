#include "raylib.h"
void ImageToImage(Image *dst, const Image src);
int ImageDataIsEqual(const Image *img1, const Image *img2);
int main()
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Photo Editor");

    // GUI Controls
    Texture2D image = LoadTexture("resources/image.png"); // Loaded image texture
    Image imageEdited = LoadImage("resources/image.png"); // Loaded image to be edited
    Vector2 imagePosition = { (float)screenWidth/2 - (float)image.width/2, (float)screenHeight/2 - (float)image.height/2 };

    Rectangle undoButtonRec = { screenWidth/2 - 60, screenHeight - 50, 120, 30 };
    Rectangle redoButtonRec = { screenWidth/2 + 60, screenHeight - 50, 120, 30 };

    bool undoButtonPressed = false;
    bool redoButtonPressed = false;

    // Undo and Redo functionality variables
    int index = 0;
    const int historySize = 10;
    Image imageHistory[historySize];

    // Clear image history array
    for (int i = 0; i < historySize; i++)
    {
        imageHistory[i] = LoadImage("resources/default.png"); // Set to a default image
    }

    while (!WindowShouldClose()) // Main loop
    {
        // Update
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            // Edit image code here...
        }

        // Undo functionality
        if (IsKeyPressed(KEY_Z) && !undoButtonPressed)
        {
            if (index > 0) index--;
            UnloadImage(imageEdited);
            imageEdited = LoadImage("resources/default.png");
            ImageFormat(&imageHistory[index], imageEdited.format);

        }

        // Redo functionality
        if (IsKeyPressed(KEY_R) && !redoButtonPressed)
        {
            if (index < historySize-1) index++;
            UnloadImage(imageEdited);
            imageEdited = LoadImage("resources/default.png");
            ImageToImage(&imageHistory[index], imageEdited);

        }

        // Save edited image in imageHistory array
        if (index == historySize-1 || ImageDataIsEqual(&imageEdited, &imageHistory[index]) != 1)
        {
            UnloadImage(imageHistory[historySize - 1]);
            for (int i = historySize - 1; i > 0; i--)
            {
                imageHistory[i - 1] = ImageCopy(imageHistory[i]);

            }
            ImageToImage(&imageHistory[0], imageEdited);  // Copy imageEdited to imageHistory[0]


            index = 0;
        }

        // Draw
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawTexture(image, 0, 0, WHITE); // Draw original image
            Texture2D editedTexture = LoadTextureFromImage(imageEdited);
            DrawTexture(editedTexture, imagePosition.x, imagePosition.y, WHITE);
            UnloadTexture(editedTexture); // Unload the temporary texture


            DrawRectangleLinesEx(undoButtonRec, 2, GRAY);
            DrawRectangleLinesEx(redoButtonRec, 2, GRAY);

            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            {
                if (CheckCollisionPointRec(GetMousePosition(), undoButtonRec)) undoButtonPressed = true;
                else if (CheckCollisionPointRec(GetMousePosition(), redoButtonRec)) redoButtonPressed = true;
            }
            else
            {
                undoButtonPressed = false;
                redoButtonPressed = false;
            }

            if (undoButtonPressed) DrawRectangleRec(undoButtonRec, GRAY);
            if (redoButtonPressed) DrawRectangleRec(redoButtonRec, GRAY);

            DrawText("UNDO", screenWidth/2 - 55, screenHeight - 35, 20, (undoButtonPressed)? GRAY : BLACK);
            DrawText("REDO", screenWidth/2 + 55, screenHeight - 35, 20, (redoButtonPressed)? GRAY : BLACK);

        EndDrawing();
    }

    // De-Initialization
    UnloadTexture(image); // Unload image texture
    UnloadImage(imageEdited); // Unload edited image data

    // Clear image history array
    for (int i = 0; i < historySize; i++)
    {
        UnloadImage(imageHistory[i]);
    }

    CloseWindow(); // Close window and OpenGL context

    return 0;
}
