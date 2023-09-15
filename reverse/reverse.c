#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

#define TRUE 1
#define FALSE 0

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Program usage: $ ./reverse [name of input file].wav [name of output file].wav ... \n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *input_ptr = fopen(argv[1], "r");
    if (input_ptr == NULL)
    {  
        printf("Error! Could not open file %s \n", argv[1]);
        return 1;
    }

    // Read header
    // TODO #3
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, input_ptr);

    // Use check_format to ensure WAV format
    // TODO #4
    if (check_format(header) == FALSE)
    {
        printf("File does not have WAV format \n");
        return 1;
    }
    if (header.audioFormat != 1)
    {
        printf("File does not have WAV format \n");
        return 1;
    }

    // Open output file for writing
    // TODO #5
    FILE *output_ptr = fopen(argv[2], "w");
    if (output_ptr == NULL)
    {  
        printf("Error! Could not open file %s \n", argv[2]);
        return 1;
    }

    // Write header to file
    // TODO #6
    fwrite(&header,sizeof(WAVHEADER),1,output_ptr);

    // Use get_block_size to calculate size of block
    // TODO #7
    int block_size = get_block_size(header);

    // Write reversed audio to file
    // TODO #8
    if (fseek(input_ptr, block_size, SEEK_END) == 1 )   // fseek sets pointer to end of file
        return -1;

    BYTE buffer[block_size];                            // buffer array to hold current audio block being read
    while(ftell(input_ptr) - block_size > sizeof(header))
    {   

        if (fseek(input_ptr, -2 * block_size, SEEK_CUR))
            return -1;

        fread(buffer, block_size, 1, input_ptr);
        fwrite(buffer, block_size, 1, output_ptr);
    }

    // Close files
    fclose(input_ptr);
    fclose(output_ptr);

    return 0;
}

int check_format(WAVHEADER header)
{
    // TODO #4
    BYTE wavBytes[] = {'W', 'A', 'V', 'E'};
    if (memcmp(header.format, wavBytes, 4) == 0)
        return TRUE;

    return FALSE;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    return header.numChannels * (header.bitsPerSample / 8);
}


// Skip the WAV header (44 bytes)
    // for (int i = numSamples - 1; i >= 0; i--) {
    //     fseek(input_ptr, 44 + i * block_size, SEEK_SET); // Move to the start of the i-th block from the end
    //     while (fread(audio_blocks, block_size, 1, input_ptr) > 0)
    //     {
    //         fwrite(audio_blocks, block_size, 1, output_ptr);
    //     }
    // }