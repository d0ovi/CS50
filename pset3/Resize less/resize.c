// Resizes a BMP file with an int

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage 
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }
    
    // make the argv[1] to integer n
    int n = atoi(argv[1]);
    
    //Check if n positive integer less than or equal to 100
    if (n < 0 || n > 100)
    {
        fprintf(stderr, "Usage: n is not accepted\n");
        return 2;
    }
    
    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }
    
    // make changes and resize different parameters in headers:
    LONG biWidthOld = bi.biWidth; 
    LONG biHeightOld = bi.biHeight;

    bi.biWidth *= n;
    bi.biHeight *= n;
    // ?? Do I need to change padding? I need both old and new paddings for the fseek
    //As I understand, the Width and Height changes and the old value is not saved
    // so the padding should be alright without changing
    // But we still need the old one. 
    
    //determine padding for scanlines, both old and new
    int paddingOld = (4 - (biWidthOld * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // Now we need to count biSizeImage (this parameter includes padding, but it is image size
    // without headers)
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + padding) * abs(bi.biHeight);
    
    // And recount the bfSize (total size of file, includes pixels, padding and headers)
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // I need more memory to allocate for the bigger pic:
    RGBTRIPLE scanline[bi.biWidth * sizeof(RGBTRIPLE)];
    //this is the same as char s[5], in here, i=5; just in this case the type is rgbtriple and the i = bi.biwidth * sizeof(RGBTRIPLE)

    // iterate over infile's scanlines
    // the first loop is for every row
    for (int i = 0, biHeight = abs(biHeightOld); i < biHeight; i++)
    {
        //This loop is for repeating the row for n times
        for (int j = 0; j < n; j++)
        {
            // This loop is for every pixel.
            for (int k = 0; k < biWidthOld; k++)
            {
                // temporary storage
                RGBTRIPLE triple; 
                
                // read the file from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                // now write the pixel as much as n 
                for (int l = 0; l < n; l++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // add padding
            for (int m = 0; m < padding; m++)
            {
                fputc(0x00, outptr);
            }
            // this is the magic that repeats row n times 
            if (j < n - 1)
            {
                fseek(inptr, -(biWidthOld * (int)sizeof(RGBTRIPLE)), SEEK_CUR);
                //okay, so apparently you need to have "-" to move backwards.... 
                //we use Width from input file as we are creating a new one, but still moving and reading old image
            }
        }
        
        // skip over padding from the infile, if any
        fseek(inptr, paddingOld, SEEK_CUR);
    }


    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
