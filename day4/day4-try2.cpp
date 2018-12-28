#include "../aoc.hpp"
using namespace std;
using namespace std::chrono;

struct is_delim : std::unary_function<const char &, bool>
{
    bool operator()(const char &c) const { return strchr(" :[]#-", int(c)) != nullptr; }
};

const static bool compare(const pair<int, int> &a, const pair<int, int> &b)
{
    return (a.second < b.second);
}

int main()
{
    auto start = high_resolution_clock::now();
    vector<string> input = read_input("input.txt");
    sort(begin(input), end(input));

    int guard{0}, sleepat{59}, wakeat{0};
    auto sleeping = map<int, int>();
    auto minutes = map<int, array<int, 60>>();

    for (string l : input)
    {
        auto tokens = split(begin(l), end(l), is_delim());

        if (l.find("Guard") != string::npos)
            guard = stoi(tokens[7]);

        if (l.find("asleep") != string::npos)
            sleepat = stoi(tokens[5]);

        if (l.find("wake") != string::npos)
        {
            wakeat = stoi(tokens[5]);
            sleeping[guard] += wakeat - sleepat;
            for (int i = sleepat; i < wakeat; ++i)
            {
                minutes[guard][i]++;
            }
        }
    }

    // Part 1
    guard = max_element(begin(sleeping), end(sleeping), compare)->first;
    cout << guard << endl;
    auto minute = max_element(begin(minutes[guard]), end(minutes[guard])) - minutes[guard].data();
    cout << "Part 1: Guard * Minutes: " << guard * minute << "\n";

    // Part 2
    auto max_minutes{0}, most_minute{0}, most_guard{0};
    for (auto g : minutes)
    {
        auto m = max_element(begin(minutes[g.first]), end(minutes[g.first]));
        auto minute = m - minutes[g.first].data();
        if (*m > max_minutes)
        {
            max_minutes = *m;
            most_minute = minute;
            most_guard = g.first;
        }
    }

    cout << "Part 2: Guard most frequently asleep * minute ";
    cout << most_guard << " * " << most_minute << " = ";
    cout << most_guard * most_minute << endl;

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Time taken by function: "
         << duration.count() << " ms" << endl;
}