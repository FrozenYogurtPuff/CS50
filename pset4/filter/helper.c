#include "helpers.h"
#include <stdlib.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;
            int b = image[i][j].rgbtBlue;
            int avg = round((r + g + b) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = (BYTE) avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;
            int b = image[i][j].rgbtBlue;
            double sepia_r = round(0.393 * r + 0.769 * g + 0.189 * b);
            double sepia_g = round(0.349 * r + 0.686 * g + 0.168 * b);
            double sepia_b = round(0.272 * r + 0.534 * g + 0.131 * b);
            sepia_r = (sepia_r > 255) ? 255 : sepia_r;
            sepia_g = (sepia_g > 255) ? 255 : sepia_g;
            sepia_b = (sepia_b > 255) ? 255 : sepia_b;
            image[i][j].rgbtRed = (BYTE) sepia_r;
            image[i][j].rgbtGreen = (BYTE) sepia_g;
            image[i][j].rgbtBlue = (BYTE) sepia_b;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE * temp = malloc(sizeof(RGBTRIPLE));
            *temp = image[i][width - 1 - j];
            image[i][width - 1 - j] = image[i][j];
            image[i][j] = *temp;
            free(temp);
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE (*newimage)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    int dxy[3] = {-1, 0, 1};
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double blocks;
            int r = 0, g = 0, b = 0;
            for (int dx = 0; dx < 3; dx++)
            {
                int nx = i + dxy[dx];
                if (nx < 0 || nx >= height)
                    continue;
                for (int dy = 0; dy < 3; dy++)
                {
                    int ny = j + dxy[dy];
                    if (ny < 0 || ny >= width)
                        continue;
                    r += image[nx][ny].rgbtRed;
                    g += image[nx][ny].rgbtGreen;
                    b += image[nx][ny].rgbtBlue;
                }
            }
            if ((i == 0 || i == height - 1) && (j == 0 || j == width - 1))
                blocks = 4;
            else if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
                blocks = 6;
            else
                blocks = 9;
            r = round(r / blocks);
            g = round(g / blocks);
            b = round(b / blocks);
            newimage[i][j].rgbtRed = (BYTE) r;
            newimage[i][j].rgbtGreen = (BYTE) g;
            newimage[i][j].rgbtBlue = (BYTE) b;
        }
    }
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            image[i][j] = newimage[i][j];
    free(newimage);
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE (*newimage)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    int Gx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    int Gy[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};
    int dxy[3] = {-1, 0, 1};
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int rx = 0, gx = 0, bx = 0;
            int ry = 0, gy = 0, by = 0;
            for (int dx = 0; dx < 3; dx++)
            {
                int nx = i + dxy[dx];
                if (nx < 0 || nx >= height)
                    continue;
                for (int dy = 0; dy < 3; dy++)
                {
                    int ny = j + dxy[dy];
                    if (ny < 0 || ny >= width)
                        continue;
                    rx += image[nx][ny].rgbtRed * Gx[dx][dy];
                    gx += image[nx][ny].rgbtGreen * Gx[dx][dy];
                    bx += image[nx][ny].rgbtBlue * Gx[dx][dy];
                    ry += image[nx][ny].rgbtRed * Gy[dx][dy];
                    gy += image[nx][ny].rgbtGreen * Gy[dx][dy];
                    by += image[nx][ny].rgbtBlue * Gy[dx][dy];
                }
            }
            int rsqrt = round(sqrt(rx * rx + ry * ry));
            int gsqrt = round(sqrt(gx * gx + gy * gy));
            int bsqrt = round(sqrt(bx * bx + by * by));
            rsqrt = (rsqrt > 255) ? 255 : rsqrt;
            gsqrt = (gsqrt > 255) ? 255 : gsqrt;
            bsqrt = (bsqrt > 255) ? 255 : bsqrt;
            newimage[i][j].rgbtRed = (BYTE) rsqrt;
            newimage[i][j].rgbtGreen = (BYTE) gsqrt;
            newimage[i][j].rgbtBlue = (BYTE) bsqrt;
        }
    }
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            image[i][j] = newimage[i][j];
    free(newimage);
    return;
}
