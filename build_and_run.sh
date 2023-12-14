#!/bin/bash

gcc -o main_output.exe photo_editor_original.c -I "D:\New folder\OneDrive - National University of Sciences & Technology\Programs\FreeImage3180Win32Win64\FreeImage\Dist\x32" -L "D:\New folder\OneDrive - National University of Sciences & Technology\Programs\FreeImage3180Win32Win64\FreeImage\Dist\x32" -lfreeimage

./main_output.exe
