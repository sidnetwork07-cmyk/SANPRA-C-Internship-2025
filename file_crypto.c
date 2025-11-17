#include <stdio.h>
#include <stdlib.h>

void encryptFile(const char *sourceFile, const char *destFile, int key);
void decryptFile(const char *sourceFile, const char *destFile, int key);

int main() {
    int choice;
    char source[100], dest[100];
    int key;

    do {
        printf("\n===== File Encryptor / Decryptor =====\n");
        printf("1. Encrypt File\n");
        printf("2. Decrypt File\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("\n--- Encrypt File ---\n");
            printf("Enter source file name: ");
            scanf("%s", source);
            printf("Enter destination (encrypted) file name: ");
            scanf("%s", dest);
            printf("Enter key (integer, 0-255 recommended): ");
            scanf("%d", &key);

            encryptFile(source, dest, key);
            break;

        case 2:
            printf("\n--- Decrypt File ---\n");
            printf("Enter source (encrypted) file name: ");
            scanf("%s", source);
            printf("Enter destination (decrypted) file name: ");
            scanf("%s", dest);
            printf("Enter key (same key used in encryption): ");
            scanf("%d", &key);

            decryptFile(source, dest, key);
            break;

        case 3:
            printf("Exiting program...\n");
            break;

        default:
            printf("Invalid choice! Please try again.\n");
        }

    } while (choice != 3);

    return 0;
}

void encryptFile(const char *sourceFile, const char *destFile, int key) {
    FILE *fs, *fd;
    int ch;

    fs = fopen(sourceFile, "rb");
    if (fs == NULL) {
        printf("Error: Cannot open source file %s\n", sourceFile);
        return;
    }

    fd = fopen(destFile, "wb");
    if (fd == NULL) {
        printf("Error: Cannot create destination file %s\n", destFile);
        fclose(fs);
        return;
    }

    while ((ch = fgetc(fs)) != EOF) {
        ch = ch ^ key;  // XOR encryption
        fputc(ch, fd);
    }

    fclose(fs);
    fclose(fd);

    printf("File encrypted successfully: %s -> %s\n", sourceFile, destFile);
}

void decryptFile(const char *sourceFile, const char *destFile, int key) {
    FILE *fs, *fd;
    int ch;

    fs = fopen(sourceFile, "rb");
    if (fs == NULL) {
        printf("Error: Cannot open source file %s\n", sourceFile);
        return;
    }

    fd = fopen(destFile, "wb");
    if (fd == NULL) {
        printf("Error: Cannot create destination file %s\n", destFile);
        fclose(fs);
        return;
    }

    while ((ch = fgetc(fs)) != EOF) {
        ch = ch ^ key;  // XOR again → decrypt
        fputc(ch, fd);
    }

    fclose(fs);
    fclose(fd);

    printf("File decrypted successfully: %s -> %s\n", sourceFile, destFile);
}
