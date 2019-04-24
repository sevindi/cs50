#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 4)
    {
        printf("Usage: multiplier infile outfile\n");
        return 1;
    }

    // Remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    int multiplier = atoi(argv[1]);

    if (multiplier < 1 || 10 < multiplier)
    {
        printf("Multiplier must be between 1 and 100\n");
        return 1;
    }

    // Open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // Open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // Read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // Read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // Ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // New file's BITMAPFILEHEADER AND BITMAPINFOHEADER
    BITMAPFILEHEADER bfNew = bf;
    BITMAPINFOHEADER biNew = bi;

    // Resized width and height
    biNew.biWidth  = bi.biWidth * multiplier;
    biNew.biHeight = bi.biHeight * multiplier;

    // Infile's padding
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Outfile's padding
    int paddingNew = (4 - (biNew.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // New image sizes
    biNew.biSizeImage = (biNew.biWidth * sizeof(RGBTRIPLE) + paddingNew) * abs(biNew.biHeight);
    bfNew.bfSize = biNew.biSizeImage + 54;

    // Write outfile's BITMAPFILEHEADER
    fwrite(&bfNew, sizeof(BITMAPFILEHEADER), 1, outptr);

    // Write outfile's BITMAPINFOHEADER
    fwrite(&biNew, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Iterate over infile's scanline vertically
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // Multiply each scanline
        for (int j = 0; j < multiplier; j++)
        {
            // Iterate over infile's scanline horizontally
            for (int k = 0; k < bi.biWidth; k++)
            {
                // Temporary storage
                RGBTRIPLE triple;

                // Read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // Write RGB triple to outfile, multiplied by factor
                for (int l = 0; l < multiplier; l++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // Add a new padding
            for (int l = 0; l < paddingNew; l++)
            {
                fputc(0x00, outptr);
            }
            // Return to the beginning
            if (j < multiplier - 1)
            {
                fseek(inptr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
            }
        }

        // Skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    // Close infile
    fclose(inptr);

    // Close outfile
    fclose(outptr);

    // Completed
    return 0;
}
