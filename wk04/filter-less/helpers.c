#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    // loop through each row
    for (int i = 0, h = height; i < h; i++)
    {
        // loop through each column
        for (int j = 0, w = width; j < w; j++)
        {
            // need to get the 3 RGB values from the RGBTRIPLE struct
            int red = image[i][j].rgbtRed;
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;
            // printf("Original RGB value is %i \n", blue);
            // and then get their average
            // a + b + c / 3
            int rgbTotal = red + blue + green;
            float rgbAvg = rgbTotal / 3.0;
            // round the number in case not an integer result
            int rgbNew = roundf(rgbAvg);
            // printf("RGB Avg. is %i \n", rgbNew);
            // assign each RGB value index with the avg number learned
            // I need to actually change the value of the array stored in memory
            // not my temp variables
            image[i][j].rgbtRed = rgbNew;
            image[i][j].rgbtBlue = rgbNew;
            image[i][j].rgbtGreen = rgbNew;
            // Am I able to use pointers to change the values instead?
            // Not necessary, surely...
        }
    }

    // printf("last pixel has: %i\n", image[height-1][width-1].rgbtBlue);
    // printf("RGB Avg. is %f \n", rgbNew);
    // what am I returning? Nothing, it's void
    // I'm just changing the values of the data in memory with this function
    // there's nothing to return.
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    // calculate each channel value's sepia value
    // loop through each row
    for (int i = 0, h = height; i < h; i++)
    {
        // loop through each column
        for (int j = 0, w = width; j < w; j++)
        {
            // need to get the 3 RGB values from the RGBTRIPLE struct
            float originalRed = (float)image[i][j].rgbtRed;
            float originalGreen = (float)image[i][j].rgbtGreen;
            float originalBlue = (float)image[i][j].rgbtBlue;
            // printf("originalRed value is %i\n", originalRed);
            // calculate each channel value's sepia value
            float sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
            // printf("sepiaRed value is %f\n", sepiaRed);
            float sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
            float sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;
            // round and clamp new sepia value
            // float to int
            // round value to an int
            sepiaRed = roundf(sepiaRed);
            sepiaGreen = roundf(sepiaGreen);
            sepiaBlue = roundf(sepiaBlue);
            // printf("sepiaRed: %f\n", sepiaRed);
            // min 0 - max 255
            image[i][j].rgbtRed = valClamp((int) sepiaRed);
            image[i][j].rgbtGreen = valClamp((int) sepiaGreen);
            image[i][j].rgbtBlue = valClamp((int) sepiaBlue);

            // printf("sepiaRed value is %i\n", (int) sepiaRed);
            // printf("%i %i %i\n", image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue);
            // printf("final value is %i\n", image[i][j].rgbtRed);

        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0, h = height; i < h; i++)
    {
        for (int j = 0, w = width / 2; j < w; j++)
        {
            // to calculate index of "opposite" pixel
            // remember to -1 because of zero indexing
            int oppSide = (width - 1) - j;
            // temp variable to hold a value for swap
            RGBTRIPLE temp = image[i][j];
            // check if we're at the middle of the image

            // I need to get the index of one pixel
            // Then get the index of the pixel horizontally opposite to it
            // image[i][j] // left most pixel
            // image[i][width-j] // right most pixel

            // Then "swap" their values
            image[i][j] = image[i][oppSide];
            image[i][oppSide] = temp;

        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // create a reference copy of the image 2D array
    // I need to allocate memory for a reference copy
    // RGBTRIPLE(*imageRef)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    // I don't understand why this works, I vaguely copied the example in filter.c
    // calloc is malloc, but takes two arguments - good I need it for 2D array
    // "height" argument to get how many rows
    // "width" argument for how many collumns
    // "* sizeof(RGBTRIPLE) to get the size in bytes that the RGBTRIPLE data type is
    RGBTRIPLE(*imageRef)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    // I just don't understand why the pointer for imageRef has to be inside brackets.
    // Why the array I initialise is just for [width], but why won't [height][width] work.


    // TODO you need to actually make a copy of the RGBTRIPLE image
    // I think currently I'm just pointing to a location in memory, I haven't
    // actually made a copy.

    // TODO the two arrays have different addresses, but something is happening
    // where they're sharing the same data values still...
    // 19 aug 2022 11:19

    // create copy of RGBTRIPLE image
    // loop through height
    for (int i = 0, h = height; i < h; i++)
    {
        // loop through width
        for (int j = 0, w = width; j < w; j++)
        {
            imageRef[i][j] = image[i][j];
            // printf("imageRef   address is %p\nimage      address is %p\n", &imageRef[i][j].rgbtRed, &image[i][j].rgbtRed);
        }
    }

    // printf("image %i\n", image[24][24].rgbtRed);
    // printf("imageRef %i\n", imageRef[24][24].rgbtRed);
    // checked, values are kept at different addresses
    // they should be separate arrays because of this
    // printf("image %p\n", &image[24][24].rgbtRed);
    // printf("imageRef %p\n", &imageRef[24][24].rgbtRed);

    // printf("image %p\n", &image);
    // printf("imageRef %p\n", &imageRef);

    // select current pixel [i][j]

    // testing for pixel image[1][1]
    // [o][o][o]
    // [o][x][o]
    // [o][o][o]

    // loop through height
    for (int i = 0, h = height; i < h; i++)
    {
        // loop through width
        for (int j = 0, w = width; j < w; j++)
        {
            // printf("Original R: %i G: %i B: %i\n", imageRef[i][j].rgbtRed, imageRef[i][j].rgbtGreen, imageRef[i][j].rgbtBlue);

            // track how many valid pixels there are
            int pixelCount = 0;
            // accumulate RGB values in their own variables
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            // identify the surrounding pixels based on target pixel
            // note: target pixel is image[i][j]
            int targetRow [] = {i - 1, i, i + 1};
            int targetCol [] = {j - 1, j, j + 1};

            // check the surrounding pixels
            // loop through 3 rows
            for (int y = 0; y < 3; y++)
            {
                // loop through 3 columns
                for (int x = 0; x < 3; x++)
                {
                    // printf("Target Pixel (%i, %i) | Current Pixel (%i, %i)\n",j ,i ,targetCol[x], targetRow[y]);
                    // check if target pixel based on targetCol/Row is within bounds
                    if (targetCol[x] < width &&
                        targetCol[x] >= 0 &&
                        targetRow[y] < height &&
                        targetRow[y] >= 0)
                    {
                        // check reference image 2D array using targetCol and targetRow arrays
                        RGBTRIPLE currentPixel = imageRef[targetRow[y]][targetCol[x]];
                        // collect all the RGB values as a sum
                        sumRed += currentPixel.rgbtRed;
                        // printf("currentPixel.R: %i sumRed: %i\n", currentPixel.rgbtRed, sumRed);
                        sumGreen += currentPixel.rgbtGreen;
                        sumBlue += currentPixel.rgbtBlue;
                        pixelCount++;

                    }
                    // else
                    // {
                    //     printf("Pixel (%i, %i) skipped - out of bounds\n", j, i);
                    // }
                }
            }

            // printf("pixelCount: %i | sumRed: %i | sumGreen: %i | sumBlue: %i\n", pixelCount, sumRed, sumGreen, sumBlue);

            // get the RGB average by dividing by pixelCount
            // round the average values
            float avgRed = roundf(sumRed / (float)pixelCount);
            float avgGreen = roundf(sumGreen / (float)pixelCount);
            float avgBlue = roundf(sumBlue / (float)pixelCount);

            // printf("averages R: %i G: %i B: %i\n", (int)avgRed, (int)avgGreen, (int)avgBlue);

            // printf("roundRed is %i\n", roundRed);

            // assign new RGB value to the target pixel image[i][j]
            image[i][j].rgbtRed = (int)avgRed;
            image[i][j].rgbtGreen = (int)avgGreen;
            image[i][j].rgbtBlue = (int)avgBlue;
            // printf("New R: %i G: %i B: %i\n", image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue);

            // TODO why is imageRef and image the same value??
            // printf("imageRef   address is %p\nimage      address is %p\n", &imageRef[i][j].rgbtRed, &image[i][j].rgbtRed);
            // printf("Old pixel R value is %i, new pixel R value is %i\n", imageRef[i][j].rgbtRed, image[i][j].rgbtRed);

            // surroundingPixels[0] = image[j-1][i-1];     // top left corner
            // surroundingPixels[1] = image[j][i-1];       //
            // surroundingPixels[2] = image[j+1][i-1];     // top right corner
            // surroundingPixels[3] = image[j-1][i];       //
            // surroundingPixels[4] = image[j][i];         // current selected pixel
            // surroundingPixels[5] = image[j+1][i];       //
            // surroundingPixels[6] = image[j-1][i+1];     // bottom left corner
            // surroundingPixels[7] = image[j][i+1];       //
            // surroundingPixels[8] = image[j+1][i+1];     // bottom right corner
        }
    }

    // Free memory for imageRef
    free(imageRef);

    return;
}

// Clamp values between 0 - 255
int valClamp(int value)
{
    int result = 0;
    if (value > 255)
    {
        result = 255;
    }
    else if (value < 0)
    {
        result = 0;
    }
    else
    {
        result = value;
    }
    return result;
}