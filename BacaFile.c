#include <stdio.h>
#include <stdlib.h>
#include "AStar.h"

// Fungsi membaca file .txt dan diubah ke matriks
int bacaFile(char *namaFile, char ***matriks, int *baris, int *kolom)
{
    // Membuak file dan jika file tidak dapat dibuka
    FILE *file = fopen(namaFile, "r");
    if (file == NULL)
    {
        printf("Gagal membuka file %s\n", namaFile);
        return 0;
    }

    // Menghitung besar ukuran matriks
    int p = 0, l = 0;
    char c;
    while ((c = fgetc(file)) != EOF)
    {
        if (c != '\n')
        {
            p++;
        }
        else
        {
            l++;
        }
    }
    *kolom = p / l;
    *baris = l;

    // Jika matriks tidak ditemukan
    *matriks = (char **)malloc(*baris * sizeof(char *));
    if (*matriks == NULL)
    {
        printf("Gagal mengalokasikan memori\n");
        return 0;
    }
    for (int i = 0; i < *baris; i++)
    {
        (*matriks)[i] = (char *)malloc(*kolom * sizeof(char));
        if ((*matriks)[i] == NULL)
        {
            printf("Gagal mengalokasikan memori\n");
            return 0;
        }
    }

    rewind(file);

    // Membaca file .txt dan diinput menjadi matriks
    for (int i = 0; i < *baris; i++)
    {
        for (int j = 0; j < *kolom; j++)
        {
            do
            {
                c = fgetc(file);
            } while (c == '\n');
            (*matriks)[i][j] = c;
        }
    }

    fclose(file);
    return 1;
}

int main()
{
    // Input nama file
    char namaFile[100];
    printf("Masukkan nama file: ");
    scanf("%s", namaFile);

    char **matriks;
    int baris, kolom;

    // Membuka file
    int berhasil = bacaFile(namaFile, &matriks, &baris, &kolom);
    while (!berhasil)
    {
        printf("File tidak bisa dibuka\n");
        printf("Nama file yang ingin dibaca: ");
        scanf("%s", namaFile);
        berhasil = bacaFile(namaFile, &matriks, &baris, &kolom);
    }

    // Mencari posisi start dan end
    Point start = {-1, -1}; // Inisialisasi start dan end dengan nilai yang tidak mungkin muncul di labirin
    Point end = {-1, -1};

    for (int y = 0; y < baris; y++)
    {
        for (int x = 0; x < kolom; x++)
        {
            if (matriks[y][x] == 'S')
            {
                start.x = x;
                start.y = y;
            }
            else if (matriks[y][x] == 'E')
            {
                end.x = x;
                end.y = y;
            }
        }
    }

    // Periksa apakah start dan end telah ditemukan
    if (start.x == -1 || start.y == -1 || end.x == -1 || end.y == -1)
    {
        printf("Titik awal atau akhir tidak ditemukan dalam labirin.\n");
        return 0;
    }

    // Fungsi mencari shortest path dengan A-Star
    findshortestPath(matriks, baris, kolom, start, end);

    // Fungsi mencari longest path dengan A-Star
    findLongestPath(matriks, baris, kolom, start, end);

    // Membebaskan memori matriks
    for (int i = 0; i < baris; i++)
    {
        free(matriks[i]);
    }
    free(matriks);

    return 0;
}
