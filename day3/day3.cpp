#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    // Creating the matrix
    int N = 1000;
    int A[1000][1000] = {0};

    string line;
    char id_delim = '@';
    char pos_delim = ':';
    char xy_delim = ',';
    char size_delim = 'x';
    int left_margin = 0;
    int top_margin = 0;
    int x;
    int y;
    int width;
    int height;

    int pos_start_idx;
    int pos_end_idx;
    int pos_str_len;

    int size_start_idx;
    int size_end_idx;
    int size_str_len;

    int row;
    int col;
    int k = 0;

    string pos_str;
    string size_str;

    ifstream inputfile("input.txt");
    if (inputfile.is_open())
    {
        while (getline(inputfile, line))
        {
            k = k + 1;

            // Extract position
            pos_start_idx = line.find(id_delim);
            pos_end_idx = line.find(pos_delim);
            pos_str_len = pos_end_idx - pos_start_idx;
            pos_str = line.substr(pos_start_idx + 1, pos_str_len);

            // Margin same as x and y since we start from idx 0
            x = stoi(pos_str.substr(0, pos_str.find(xy_delim)));
            y = stoi(pos_str.substr(pos_str.find(xy_delim) + 1, pos_str.find(pos_delim)));

            // Extract size
            size_start_idx = line.find(pos_delim);
            size_end_idx = line.length() - 1;
            size_str = line.substr(size_start_idx + 1, size_end_idx);

            width = stoi(size_str.substr(0, size_str.find(size_delim)));
            height = stoi(size_str.substr(size_str.find(size_delim) + 1, size_str.length() - 1));

            // We fill the blank spots
            for (int i = 0; i < width; i++)
            {
                for (int j = 0; j < height; j++)
                {
                    int row = y + j;
                    int col = x + i;
                    A[row][col] += 1;
                }
            }
        }
    }

    int overlaps = 0;

    for (int m = 0; m < N; m++)
    {
        for (int n = 0; n < N; n++)
        {

            if (A[m][n] > 1)
            {
                overlaps = overlaps + 1;
            }
        }
    }

    printf("Number of overlaps: %i \n", overlaps);

    // Number 2

    return 0;
}