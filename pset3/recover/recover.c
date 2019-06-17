#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

int main(int argc, char *argv[])
{
    // Make sure to take only 2 command
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover rawfile\n");
        return 1;
    }
    // Remember the file name
    char *infile = argv[1];
    // Open the given file
    FILE *inptr = fopen(infile, "r");
    // Make sure file is usable
    if (inptr == NULL)
    {
        fprintf(stderr, "%s is not supported\n", infile);
        return 2;
    }
    // Allocate memory for 512 bytes units
    unsigned char *unit = malloc(512);

    FILE *outptr = NULL;
    int n = 0;

    // Read the input file
    while (fread(unit, 512, 1, inptr))
    {
        // Make sure of jpeg patterns
        if (unit[0] == 0xff && unit[1] == 0xd8 && unit[2] == 0xff && (unit[3] >= 0xe0 || 0xef >= unit[3]))
        {
            // Create a file name for jpegs
            char img[8];
            sprintf(img, "%03d.jpg", n);

            // Open the created file
            outptr = fopen(img, "w");

            // Prompt error if image file cannot be created
            if (outptr == NULL)
            {
                fclose(inptr);
                fprintf(stderr, "%s.jpg couldn't created", img);
                return 3;
            }

            n++;
        }
        // Write image info to file
        if (outptr != NULL)
        {
            fwrite(unit, 512, 1, outptr);
        }

    }
    // Close rawfile
    fclose(inptr);
    // Close image file
    fclose(outptr);
    // Free the allocated memory
    free(unit);

    return 0;
}
