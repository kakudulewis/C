#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    //Check Argument count
    if (argc != 2)
    {
        printf("Usage: ./recover image \n");
        return 1;
    }
    
    //Open file
    FILE *file = fopen(argv[1], "r");
    
    //Check Validity of File
    if (!file)
    {
        printf("Could not open file\n");
        return 2;
    }
    
    //Declare Variable to store 512bytes
    unsigned char buffer[512];
    
    //Initialise Pointer to out image 
    FILE *img = NULL;
    
    //Count images as program runs
    int img_count = 0;
    
    char *filename = malloc(8 * sizeof(char));
    
    while(fread(buffer, sizeof(char), 512, file))
    {
        //Check JPEG Headers
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            sprintf(filename, "%03i.jpg", img_count);
            
            img = fopen(filename, "w");
            
            img_count++;
        }
        
        if (img != NULL)
        {
            fwrite(&buffer, sizeof(char), 512, img);
        }
    }
    
    free(filename);
    fclose(file);
    fclose(img);
}

