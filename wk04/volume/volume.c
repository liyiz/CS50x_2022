// Modifies the volume of an audio file
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;
// define data type of BYTES
typedef uint8_t BYTE;
typedef int16_t WAV16;


int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    // copy the header from the input file and add to the output file
    uint8_t header[HEADER_SIZE];
    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);

    // TODO: Read samples from input file and write updated data to output file
    // create a buffer for 16-bit bytes?? I don't fully understand why
    // something to do with WAV files?
    int16_t buffer;
    // loop will keep reading in samples of 2 bytes until the end of the input file
    // I'm still not sure how it knows when to stop, shouldn't I need to identify how
    // far to go with the loop? Or define a break or something?
    // Remember an & means you're getting the address of that variable
    // and * means you're getting the value from an address
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        // multiply by factor for volume change
        buffer *= factor;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
// I shouldn't have gone on holiday, I feel so lost getting back into this course :(
// I followed the solution video, but I feel guilty because I don't feel like I've
// fully understood everything.