#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <getopt.h>

// define data type of BYTES
typedef uint8_t BYTE;
// define string type
typedef char *STRING;

int main(int argc, char *argv[])
{

    // Ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Remember filenames
    char *inputFile = argv[1];

    // Open memory card
    FILE *raw_file = fopen(inputFile, "r");
    if (raw_file == NULL)
    {
        printf("Could not open %s.\n", inputFile);
        return 1;
    }

    // define size of a block in bytes
    const int BLOCK_SIZE = 512;
    BYTE buffer[BLOCK_SIZE];
    // array to temporarily contain blocks for a jpeg
    // BYTE curJpeg[];

    FILE *img = NULL;
    STRING filename = NULL;

    int jpegCount = 0;

    // make sure that filename has enough memory/characters (incl. NULL)
    // STRING filename = malloc(8);

    // Repeat until end of card:
    // Read 512 bytes into a buffer
    //     fread(data, size, number, inptr)
    while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        // read each of the 512 bytes within current block
        for (int i = 0; i < BLOCK_SIZE; i++)
        {
            // If start of a new JPEG
            if (buffer[i] == 0xff && buffer[i + 1] == 0xd8 && buffer[i + 2] == 0xff
                && (buffer[i + 3] & 0xf0) == 0xe0)
            {
                // found a new jpeg

                // check for first jpeg
                if (jpegCount != 0)
                {
                    // close the img file
                    fclose(img);
                    free(filename);
                }

                // 1. create filename
                // make sure that filename has enough memory/characters (incl. NULL)
                filename = malloc(8);
                // filenames: ###.jpg, starting 000.jpg
                // sprintf(filename, "%03i.jpg", 2); // creates "002.jpg"
                sprintf(filename, "%03i.jpg", jpegCount);
                // 2. create file
                img = fopen(filename, "w"); // "w" is for "write mode"
                // count jpeg, zero indexed
                jpegCount++;
            }

        }

        // 3. write buffer to the file
        if (jpegCount != 0)
        {
            fwrite(buffer, BLOCK_SIZE, 1, img);
        }

    }

    // close all files and free memory
    fclose(raw_file);
    fclose(img);
    free(filename);
    
    // 989 blocks from 506,368 bytes in card.raw
    // printf("number of 0xff bytes: %i\n", jpegCount);

    //repeat until end of card:
    //  read 512 bytes into a buffer
    //  if start of new JPEG
    //      if first JPEG
    //      ...
    //      else
    //      ...
    //  else
    //      if already found JPEG
    //          ...
    //close any remaining files
}