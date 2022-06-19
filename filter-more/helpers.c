#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Average
            int a = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // Apply
            image[i][j].rgbtRed = a;
            image[i][j].rgbtGreen = a;
            image[i][j].rgbtBlue = a;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, n = width - 1; j < n; j++, n--)
        {
            // Temporary value
            int tempRed = image[i][j].rgbtRed;
            int tempGreen = image[i][j].rgbtGreen;
            int tempBlue = image[i][j].rgbtBlue;

            // Apply (swap)
            image[i][j].rgbtRed = image[i][n].rgbtRed;
            image[i][n].rgbtRed = tempRed;
            image[i][j].rgbtGreen = image[i][n].rgbtGreen;
            image[i][n].rgbtGreen = tempGreen;
            image[i][j].rgbtBlue = image[i][n].rgbtBlue;
            image[i][n].rgbtBlue = tempBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    // Iterate each row
    for (int i = 0; i < height; i++)
    {
        // Iterate each column
        for (int j = 0; j < width; j++)
        {
            // Divisor
            int d = 0;

            // Pixels that are within 1 row and column of the original pixel (forming a 3x3 box)
            int row[] = {i - 1, i, i + 1};
            int col[] = {j - 1, j, j + 1};

            // Total (Red, Green, Blue) (set float for the division afterward)
            float tr = 0, tg = 0, tb = 0;

            // Iterate every neighboring pixel within the radius 1 in the x direction
            for (int r = 0; r < 3; r++)
            {
                // Iterate every neighboring pixel within the radius 1 in the y direction
                for (int c = 0; c < 3; c++)
                {
                    // Current pixel
                    int curRow = row[r];
                    int curCol = col[c];

                    // Calculate the total from neighboring pixel RGB (handle edge cases)
                    if (curRow >= 0 && curRow < height && curCol >= 0 && curCol < width)
                    {
                        tr += image[curRow][curCol].rgbtRed;
                        tg += image[curRow][curCol].rgbtGreen;
                        tb += image[curRow][curCol].rgbtBlue;
                        d++;
                    }
                }
            }
            // Set pixel RGB to copy (prevent confict)
            copy[i][j].rgbtRed = round(tr / d);
            copy[i][j].rgbtGreen = round(tg / d);
            copy[i][j].rgbtBlue = round(tb / d);
        }
    }
    // Apply
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    // Gx, Gy kernel
    int Gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int Gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    // Iterate each row
    for (int i = 0; i < height; i++)
    {
        // Iterate each column
        for (int j = 0; j < width; j++)
        {
            int row[] = {i - 1, i, i + 1};
            int col[] = {j - 1, j, j + 1};

            // Gx, Gy (Red, Green, Blue)
            float gxr = 0, gxg = 0, gxb = 0;
            float gyr = 0, gyg = 0, gyb = 0;

            // Iterate every neighboring pixel within the radius 1 in the x direction
            for (int r = 0; r < 3; r++)
            {
                // Iterate every neighboring pixel within the radius 1 in the y direction
                for (int c = 0; c < 3; c++)
                {
                    // Current pixel
                    int curRow = row[r];
                    int curCol = col[c];

                    // Calculate the edge value from neighboring pixel RGB (handle edge cases)
                    if (curRow >= 0 && curRow < height && curCol >= 0 && curCol < width)
                    {
                        // Current pixel
                        RGBTRIPLE curPixel = image[curRow][curCol];

                        // Gx values
                        gxr += Gx[r][c] * curPixel.rgbtRed;
                        gxg += Gx[r][c] * curPixel.rgbtGreen;
                        gxb += Gx[r][c] * curPixel.rgbtBlue;

                        // Gy values
                        gyr += Gy[r][c] * curPixel.rgbtRed;
                        gyg += Gy[r][c] * curPixel.rgbtGreen;
                        gyb += Gy[r][c] * curPixel.rgbtBlue;
                    }
                }
            }
            // Edge values (Square root of Gx^2 + Gy^2)
            int evr = round(sqrt(gxr * gxr + gyr * gyr));
            int evg = round(sqrt(gxg * gxg + gyg * gyg));
            int evb = round(sqrt(gxb * gxb + gyb * gyb));

            // Cap value at 255 and set pixel RGB to copy (prevent confict)
            copy[i][j].rgbtRed = evr > 255 ? 255 : evr;
            copy[i][j].rgbtGreen = evg > 255 ? 255 : evg;
            copy[i][j].rgbtBlue = evb > 255 ? 255 : evb;
        }
    }
    // Apply
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
    return;
}
