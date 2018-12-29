#include "../aoc.hpp"
#include <list>
using namespace std;
using namespace std::chrono;

int main()
{
    auto start = high_resolution_clock::now();
    list<char> polymers = read_line("input-day5.txt");
    auto it = polymers.begin();

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
            it = polymers.erase(it);

            if (it != polymers.begin())
            {
                it--;
            }
        }
    }

    cout << "The number of units remaining: " << polymers.size() << endl;

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count() << " ms" << endl;

    return 0;
}
