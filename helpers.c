#include "helpers.h"
#include <math.h>

// Convert image to grayscale

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j, avg = 0;
    for (i = 0; i<height; i++)
    {
        for (j = 0; j<width; j++)
        {
            avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3.0);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j;
    RGBTRIPLE temp;
    for (i = 0; i<height; i++)
    {
        if (width%2 == 0)
            {
                for (j = 0; j<(width/2); j++)
                {
                    temp = image[i][j];
                    image[i][j] = image[i][width-j-1];
                    image[i][width-j-1] = temp;
                }
            }
        else
        {
            for (j = 0; j<((width-1)/2); j++)
            {
                temp = image[i][j];
                image[i][j] = image[i][width-j-1];
                image[i][width-j-1] = temp;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j, a, b, rsum, bsum, gsum;
    float t;
    RGBTRIPLE image1[height][width];
    for (i = 0; i<height; i++)
    {
        for (j = 0; j<width; j++)
        {
            image1[i][j] = image[i][j];
        }
    }
    for (i = 0; i<height; i++)
    {
        for (j = 0; j<width; j++)
        {
            rsum = 0; bsum = 0; gsum = 0; t = 0.0;
            for (a = i-1; a<i+2; a++)
            {
                for (b = j-1; b<j+2; b++)
                {
                    if (!((a >= 0 && a < height) && (b >= 0 && b < width))) continue;
                    rsum += image1[a][b].rgbtRed;
                    gsum += image1[a][b].rgbtGreen;
                    bsum += image1[a][b].rgbtBlue;
                    t++;
                }
            }
            image[i][j].rgbtRed = round(rsum/t);
            image[i][j].rgbtBlue = round(bsum/t);
            image[i][j].rgbtGreen = round(gsum/t);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j, a, b, Gxr, Gxg, Gxb, Gyr, Gyg, Gyb, t, t2;
    double Gr, Gg, Gb;
    RGBTRIPLE image1[height][width];
    for (i = 0; i<height; i++)
    {
        for (j = 0; j<width; j++)
        {
            image1[i][j] = image[i][j];
        }
    }
    for (i = 0; i<height; i++)
    {
        for (j = 0; j<width; j++)
        {
            Gxr = 0; Gxg = 0; Gxb = 0; Gyr = 0; Gyg = 0; Gyb = 0; Gr = 0; Gg = 0; Gb = 0;
            for (a = i-1; a<i+2; a++)
            {
                for (b = j-1; b<j+2; b++)
                {
                    if (!((a >= 0 && a < height) && (b >= 0 && b < width))) continue;

                    switch (a-i)
                    {
                        case -1:
                            t = 1;
                            break;
                        case 0:
                            t = 2;
                            break;
                        case 1:
                            t = 1;
                            break;
                    }
                    Gxr += ((b-j)*t) * image1[a][b].rgbtRed;
                    Gxg += ((b-j)*t) * image1[a][b].rgbtGreen;
                    Gxb += ((b-j)*t) * image1[a][b].rgbtBlue;

                    switch (b-i)
                    {
                        case -1:
                            t2 = 1;
                            break;
                        case 0:
                            t2 = 2;
                            break;
                        case 1:
                            t2 = 1;
                            break;
                    }
                    Gyr += ((a-i)*t2) * image1[a][b].rgbtRed;
                    Gyg += ((a-i)*t2) * image1[a][b].rgbtGreen;
                    Gyb += ((a-i)*t2) * image1[a][b].rgbtBlue;

                    Gr = pow((pow(Gxr, 2) + pow(Gyr, 2)), 0.5);
                    Gg = pow((pow(Gxg, 2) + pow(Gyg, 2)), 0.5);
                    Gb = pow((pow(Gxb, 2) + pow(Gyb, 2)), 0.5);
                }
            }
            if (Gr > 255) Gr = 255;
            if (Gg > 255) Gg = 255;
            if (Gb > 255) Gb = 255;
            image[i][j].rgbtRed = round(Gr);
            image[i][j].rgbtBlue = round(Gb);
            image[i][j].rgbtGreen = round(Gg);
        }
    }
    return;
}
