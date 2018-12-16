#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    int A[1000][1000];
    string line;
    char id_delim = '@';
    char pos_delim = ':';
    char xy_delim = ',';
    char size_delim = 'x';
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

    string pos_str;
    string size_str;

    ifstream inputfile("input.txt");
    if (inputfile.is_open())
    {
        while (getline(inputfile, line))
        {
            // Extract position
            pos_start_idx = line.find(id_delim);
            pos_end_idx = line.find(pos_delim);
            pos_str_len = pos_end_idx - pos_start_idx;
            pos_str = line.substr(pos_start_idx + 1, pos_str_len);

            x = stoi(pos_str.substr(0, pos_str.find(xy_delim)));
            y = stoi(pos_str.substr(pos_str.find(xy_delim) + 1, pos_str.find(pos_delim)));

            // Extract size
            size_start_idx = line.find(pos_delim);
            size_end_idx = line.length - 1;

            exit(1);
        }
    }
}