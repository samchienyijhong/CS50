#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // If the program is not executed with exactly one command-line argument, it should remind the user of correct usage, and main should return 1.
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open memory card
    FILE *raw_file = fopen(argv[1], "r");

    // If the forensic image cannot be opened for reading, your program should inform the user as much, and main should return 1.
    if (raw_file == NULL)
    {
        printf("Error occured opening the raw file.\n");
        return 1;
    }

    // An 8-bit unsigned integer (byte)
    typedef uint8_t BYTE;

    // Memory block (512 bytes)
    BYTE buffer[BLOCK_SIZE];

    // Variables
    int count = 0;
    bool is_first_jpeg = false;
    bool is_found_jpeg = false;
    FILE *img;
    char filename[10];

    // Repeat until end of memory card (each 512-byte block)
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        // Validate JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // JPEG is found
            is_found_jpeg = true;

            // JPEG is first one
            if (!is_first_jpeg)
            {
                is_first_jpeg = true;
            }
            else
            {
                fclose(img);
            }
            sprintf(filename, "%03i.jpg", count);
            img = fopen(filename, "w");
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
            count++;
        }
        else
        {
            // If already found JPEG
            if (is_found_jpeg)
            {
                // Write whole memory block to created file
                // Assume any slack space will be filled with 0s.
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
            }
        }
    }
    // Close any remaining files
    fclose(raw_file);
    fclose(img);
    return 0;
}

