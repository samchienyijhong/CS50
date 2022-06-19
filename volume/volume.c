// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

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

    // First 44-byte header
    uint8_t header[HEADER_SIZE];

    // Read from input and write to ouput (Copy)
    fread(header, sizeof(header), 1, input);
    fwrite(header, sizeof(header), 1, output);

    // TODO: Read samples from input file and write updated data to output file

    // Each 2-byte samples
    int16_t buffer;

    // Read from input to the end and write to ouput (Copy)
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        // Update volume
        buffer *= factor;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
