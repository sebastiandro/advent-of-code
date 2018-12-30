#include "../aoc.hpp"
#include <list>
using namespace std;
using namespace std::chrono;

void reaction(list<char> &polymers);
void remove_unit(list<char> &polymers, char unit);

int main()
{
    // Part 1
    auto start = high_resolution_clock::now();

    list<char> polymers = read_line("input-day5.txt");
    list<char> polymers_p1 = list<char>(polymers);

    // Part 2
    string units = "abcdefghijklmnopqrstuvwxyz";
    list<char> polymers_copy;
    int least_reactions = 999999;
    char best_unit;
    for (char c : units)
    {
        polymers_copy = polymers;
        remove_unit(polymers_copy, c);
        reaction(polymers_copy);

        if (polymers_copy.size() < least_reactions)
        {
            least_reactions = polymers_copy.size();
            best_unit = c;
        }
    }

    cout << "Best unit: " << best_unit << ", remaining units: " << least_reactions << endl;

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count() << " ms" << endl;

    return 0;
}

void remove_unit(list<char> &polymers, char unit)
{
    auto it = polymers.begin();
    while (it != polymers.end())
    {
        char a = *it;
        char b = tolower(a);
        tolower(a) == unit ? it = polymers.erase(it) : it++;
    }
}
void reaction(list<char> &polymers)
{
    auto it = polymers.begin();
    auto nr_iterations = 0;

    while (it != polymers.end())
    {
        char a = *it;
        it++;
        char b = *it;

        // Same characters but not both are lower
        // then we have a match
        if (tolower(a) == tolower(b) && islower(a) != islower(b))
        {
            it--;

            it = polymers.erase(it);

            if (it != polymers.end())
                it = polymers.erase(it);

            if (it != polymers.begin())
                it--;
        }

        nr_iterations++;
    }
}
