#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    
    // Iterating through each pixel of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            
            //Adding the qty of red blue and green to find an average and then set the pixels RGB to the average value
            float sum =  image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen;
            int average = round(sum / 3);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //Copying the image into a temporary variable
    RGBTRIPLE temp[height][width];
    
    //Iterating through the image starting by the end to add the end pixel to the first pixel place in my temp
    for (int i = 0; i < height; i++)
    {
        int k = 0;
        for (int j = width - 1; j >= 0; j--, k++)
        {
            temp[i][k] = image[i][j];
        }  
        
    }
    
    //Applying the temp to my image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
           
        }  
        
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Initializing the RGB sums of the pixels surrounding my pixel
            float r_sum = 0;
            float g_sum = 0;
            float b_sum = 0;
          
            int surrounding_pixels = 0;
            //These arrays represent the rows and columns of the 3x3 square
            int coox[] = {j - 1, j, j + 1};
            int cooy[] = {i - 1, i, i + 1};
          
            for (int rows = 0; rows < 3; rows++)
            {
                for (int columns = 0; columns < 3; columns++)
                {
                  
                  
                    int r = cooy[rows];
                    int c = coox[columns];
                  
                    // if the row and the column are existent then we add the RGB values into our RGB sums
                    if (r >= 0 && r < height && c >= 0 && c < width)
                    {
                        RGBTRIPLE square = image[r][c];
                      
                        r_sum += square.rgbtRed;
                        b_sum += square.rgbtBlue;
                        g_sum += square.rgbtGreen;
                      
                        surrounding_pixels++;
                    }
                  
                }
            }
           
            //Average each color and apply it to the temp
            temp[i][j].rgbtRed = round(r_sum / surrounding_pixels);
            temp[i][j].rgbtBlue = round(b_sum / surrounding_pixels);
            temp[i][j].rgbtGreen = round(g_sum / surrounding_pixels);
          
        }
    }
    
    //Copying the temp into the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    
    }
    
    
   
   
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //gx AND gy TABLES
    int Gx[3][3]  = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
    int Gy[3][3]  = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1} };
    RGBTRIPLE temp[height][width];
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //iterating throught each pixel of the image
            float rx = 0;
            float gx = 0;
            float bx = 0;
           
            float ry = 0;
            float gy = 0;
            float by = 0;
           
           
            int coox[] = {j - 1, j, j + 1};
            int cooy[] = {i - 1, i, i + 1};
          
          
            //Iterating through the 3x3 square
            for (int rows = 0; rows < 3; rows++)
            {
                for (int columns = 0; columns < 3; columns++)
                {
                  
                  
                    int r = cooy[rows];
                    int c = coox[columns];
                  
                    if (r >= 0 && r < height && c >= 0 && c < width)
                    {
                        RGBTRIPLE square = image[r][c];
                        
                        // Multiplying  each of the 3x3 square pixels by the Gx and Gy table
                        rx += Gx[rows][columns] * square.rgbtRed;
                        bx += Gx[rows][columns] * square.rgbtBlue;
                        gx += Gx[rows][columns] * square.rgbtGreen;
                      
                        ry += Gy[rows][columns] * square.rgbtRed;
                        by += Gy[rows][columns] * square.rgbtBlue;
                        gy += Gy[rows][columns] * square.rgbtGreen;
                    }
                  
                }
              
              
            }
            //Finding the sobel values
            int G_red = round(sqrt(pow(rx, 2) + pow(ry, 2)));
            int G_blue = round(sqrt(pow(bx, 2) + pow(by, 2)));
            int G_green = round(sqrt(pow(gx, 2) + pow(gy, 2)));
          
            //Caping the value to 255 if it goes over 
            if (G_red > 255)
            {
                G_red = 255;
            }
          
            if (G_blue > 255)
            {
                G_blue = 255;
            }
          
            if (G_green > 255)
            {
                G_green = 255;
            }
          
            // Aplying the sobel values to the temp image
            temp[i][j].rgbtRed = G_red;
            temp[i][j].rgbtBlue = G_blue;
            temp[i][j].rgbtGreen = G_green;
          
          
          
          
        }
        
    }
    
    
    
    //Copying the temp into the image
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
              
              
                  
    return;
}
