#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Function to encode a character based on the given mapping
int encodeCharacter(char ch)
{
    switch (tolower(ch))
    {
    case 'a':
        return 10;
    case 'b':
        return 11;
    case 'c':
        return 12;
    case 'd':
        return 13;
    case 'e':
        return 14;
    case 'f':
        return 15;
    case 'g':
        return 16;
    case 'h':
        return 17;
    case 'i':
        return 18;
    case 'j':
        return 19;
    case 'k':
        return 20;
    case 'l':
        return 21;
    case 'm':
        return 22;
    case 'n':
        return 23;
    case 'o':
        return 24;
    case 'p':
        return 25;
    case 'q':
        return 26;
    case 'r':
        return 27;
    case 's':
        return 28;
    case 't':
        return 29;
    case 'u':
        return 30;
    case 'v':
        return 31;
    case 'w':
        return 32;
    case 'x':
        return 33;
    case 'y':
        return 34;
    case 'z':
        return 35;
    case ' ':
        return 36;
    case '.':
        return 37;
    case '?':
        return 38;
    case '!':
        return 39;
    default:
        return -1; // Invalid character
    }
}

// Function to decode an encoded number to a character
char decodeCharacter(int encodedValue)
{
    switch (encodedValue)
    {
    case 10:
        return 'A';
    case 11:
        return 'B';
    case 12:
        return 'C';
    case 13:
        return 'D';
    case 14:
        return 'E';
    case 15:
        return 'F';
    case 16:
        return 'G';
    case 17:
        return 'H';
    case 18:
        return 'I';
    case 19:
        return 'J';
    case 20:
        return 'K';
    case 21:
        return 'L';
    case 22:
        return 'M';
    case 23:
        return 'N';
    case 24:
        return 'O';
    case 25:
        return 'P';
    case 26:
        return 'Q';
    case 27:
        return 'R';
    case 28:
        return 'S';
    case 29:
        return 'T';
    case 30:
        return 'U';
    case 31:
        return 'V';
    case 32:
        return 'W';
    case 33:
        return 'X';
    case 34:
        return 'Y';
    case 35:
        return 'Z';
    case 36:
        return ' ';
    case 37:
        return '.';
    case 38:
        return '?';
    case 39:
        return '!';
    default:
        return -1; // Invalid encoding
    }
}

// Function to encode a plain-text message and write it to a file
void encodeToFile()
{
    char ch;
    FILE *inputFile, *outputFile;

    inputFile = fopen("unencoded.txt", "r");
    if (inputFile == NULL)
    {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    outputFile = fopen("encoded.txt", "w");
    if (outputFile == NULL)
    {
        perror("Error opening output file");
        fclose(inputFile);
        exit(EXIT_FAILURE);
    }

    while ((ch = fgetc(inputFile)) != EOF)
    {
        int encodedValue = encodeCharacter(ch);
        if (encodedValue != -1)
        {
            fprintf(outputFile, "%d ", encodedValue);
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Encoding complete. Encoded text saved to 'encoded.txt'\n");
}

// Function to decode an encoded message and print it to the console
void decodeFromFile()
{
    int encodedValue;
    FILE *inputFile;

    inputFile = fopen("encoded.txt", "r");
    if (inputFile == NULL)
    {
        perror("Error: unencoded.txt not found");
        exit(EXIT_FAILURE);
    }

    printf("Decoded message: ");
    while (fscanf(inputFile, "%d", &encodedValue) != EOF)
    {
        char decodedChar = decodeCharacter(encodedValue);
        if (decodedChar != -1)
        {
            printf("%c", decodedChar);
        }
        else if (encodedValue == 36)
        { // Check for space
            printf(" ");
        }
    }
    printf("\n");

    fclose(inputFile);
}

int main()
{
    int choice;

    printf("Choose an option:\n");
    printf("1. Encode a file\n");
    printf("2. Decode a file\n");
    printf("3. Encode/Decode custom text\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        encodeToFile();
    }
    else if (choice == 2)
    {
        decodeFromFile();
    }
    else if (choice == 3)
    {
        // Encoding and decoding custom text
        char text[1000];
        int i = 0;

        printf("Enter text to encode/decode (max 1000 characters): ");
        getchar(); // Consume newline left in buffer
        fgets(text, sizeof(text), stdin);

        printf("Choose an option:\n");
        printf("1. Encode text\n");
        printf("2. Decode text\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            printf("Encoded text: ");
            for (i = 0; text[i] != '\0'; i++)
            {
                int encodedValue = encodeCharacter(text[i]);
                if (encodedValue != -1)
                {
                    printf("%d ", encodedValue);
                }
            }
            printf("\n");
        }
        else if (choice == 2)
        {
            printf("Decoded text: ");
            while (text[i] != '\0')
            {
                if (text[i] == ' ')
                {
                    printf(" "); // Print space
                }
                else if (isdigit(text[i]))
                {
                    int decodedValue = 0;
                    while (isdigit(text[i]))
                    {
                        decodedValue = decodedValue * 10 + (text[i] - '0');
                        i++;
                    }
                    char decodedChar = decodeCharacter(decodedValue);
                    if (decodedChar != -1)
                    {
                        printf("%c", decodedChar);
                    }
                    else
                    {
                        printf("Invalid input");
                        break;
                    }
                }
                else
                {
                    printf("Invalid input");
                    break;
                }
                i++;
            }
            printf("\n");
        }
        else
        {
            printf("Invalid choice\n");
        }
    }
    else
    {
        printf("Invalid choice\n");
    }

    return 0;
}
