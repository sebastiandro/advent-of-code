#include <iostream>
#include <fstream>
using namespace std;

struct Guard
{
    int minutes[60];
    int id;
};

void read_input(string filename, string *target_list);

int main()
{
    // Read and save input
    string inputs[1002];
    read_input("input.txt", inputs);
    return 0;
}

void read_input(string filename, string *target_list)
{
    string line;
    ifstream inputfile(filename);
    int nrLines = 0;

    if (inputfile.is_open())
    {
        int i = 0;
        while (getline(inputfile, line))
        {
            *target_list = line;
            target_list++;
        }
    }
}

int sort_by_date()
{
    return 0;
}