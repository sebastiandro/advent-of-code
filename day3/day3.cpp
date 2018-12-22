#include <iostream>
#include <fstream>
using namespace std;
const int N = 1000;

struct claim
{
    int id, x, y, width, height;
};

claim decode_line(string line)
{

    int x;
    int y;
    int width;
    int height;

    int id;

    int pos_start_idx;
    int pos_end_idx;
    int pos_str_len;

    int size_start_idx;
    int size_end_idx;
    int size_str_len;

    string pos_str;
    string size_str;

    char id_delim = '@';
    char pos_delim = ':';
    char xy_delim = ',';
    char size_delim = 'x';

    // Extract ID
    pos_start_idx = line.find(id_delim);
    id = stoi(line.substr(1, pos_start_idx));

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

    claim decoded_line = {id, x, y, width, height};
    return decoded_line;
}

int main()
{
    // Creating the matrix
    static int A[N * N][2] = {0};

    string line;
    claim clm;

    ifstream inputfile("input.txt");
    if (inputfile.is_open())
    {
        while (getline(inputfile, line))
        {

            clm = decode_line(line);

            for (int i = clm.y; i < clm.y + clm.height; i++)
            {
                for (int j = clm.x; j < clm.x + clm.width; j++)
                {
                    int p = i * N + j;
                    A[p][0] = A[p][0] + 1;
                    A[p][1] = clm.id;
                }
            }
        }
    }

    inputfile.close();

    // Question 1
    int overlaps = 0;
    int last_id = -1;
    int curr_id_overlaps = -1;
    int no_overlap_claim_id;

    for (int i = 0; i < N * N; i++)
    {
        {
            if (A[i][0] > 1)
            {
                overlaps++;
            }
        }
    }

    // Question 2
    no_overlap_claim_id = -1;
    ifstream inputfile2("input.txt");
    if (inputfile2.is_open())
    {
        while (getline(inputfile2, line))
        {
            int current_claims_overlaps = 0;
            claim clm = decode_line(line);
            for (int i = clm.y; i < clm.y + clm.height; i++)
            {
                for (int j = clm.x; j < clm.x + clm.width; j++)
                {
                    int p = i * N + j;
                    if (*A[p] > 1)
                    {
                        current_claims_overlaps++;
                    }
                }
            }
            if (current_claims_overlaps == 0)
            {
                no_overlap_claim_id = clm.id;
                break;
            }
        }
    }

    printf("Number of overlaps: %i \n", overlaps);
    printf("No overlap id: %i \n", no_overlap_claim_id);
    return 0;
}
