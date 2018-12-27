//
//  main.cpp
//  AdventOfCode
//
//  Created by Sebastian Nilsson on 2018-12-25.
//  Copyright © 2018 Sebastian Nilsson. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <time.h>
#include <tuple>
#include <sstream>
#include <locale>
#include <iomanip>
#include <chrono>
using namespace std;
using namespace std::chrono;

void read_input(string filename, vector<string> &inpts);
bool compare_line_dates(string &line_a, string &line_b);
void add_guards(vector<string> &inpts, map<int, tuple<int, vector<int>>> &guard_minutes);
void update_guard_sleep(tuple<int, vector<int>> &tp, int fell_asleep_min, int woke_up_min);
int find_worst_guard(map<int, tuple<int, vector<int>>> &guard_minutes);
int find_worst_minute(int guard_id, map<int, tuple<int, vector<int>>> &guard_minutes);
tuple<int, int> most_frequent_asleep(map<int, tuple<int, vector<int>>> &guard_minutes);

static int runs = 0;

int main()
{
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    vector<string> inpts(1002);

    // Map key is guard ID
    // Map value is tuple with # total minutes slept, and vector of minutes
    map<int, tuple<int, vector<int>>> guard_minutes;

    // Read and sort inputs by date
    read_input("input.txt", inpts);
    sort(inpts.begin(), inpts.end(), compare_line_dates);

    // Add guards to guard_minutes matrix
    add_guards(inpts, guard_minutes);

    int worst_guard_id = find_worst_guard(guard_minutes);
    int worst_minute = find_worst_minute(worst_guard_id, guard_minutes);

    cout << "Worst Guard ID: " << worst_guard_id << endl;
    cout << "Worst Minute for that Guard: " << worst_minute << endl;
    cout << "Number of iterations: " << runs << endl;

    // Populate
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(t2 - t1).count();
    cout << "Execution time: " << duration << " ms" << endl;

    // Part 2
    tuple<int, int> most_freq_tp = most_frequent_asleep(guard_minutes);
    int p2_minute = get<0>(most_freq_tp);
    int p2_guard_id = get<1>(most_freq_tp);
    cout << "Guard " << p2_guard_id << " sleeps the most at " << p2_minute << endl;
    return 0;
}

tuple<int, int> most_frequent_asleep(map<int, tuple<int, vector<int>>> &guard_minutes)
{

    map<int, tuple<int, vector<int>>>::iterator it;
    it = guard_minutes.begin();
    int total_max_minutes_slept = 0;
    int all_most_frequent_minute = 0;
    int guard_id = 0;
    while (it != guard_minutes.end())
    {
        tuple<int, vector<int>> tp = it->second;
        vector<int> minutes = get<1>(tp);
        int max_slept_minutes = 0;
        int most_frequent_minute = 0;
        for (int i = 0; i < minutes.size(); i++)
        {
            int minutes_slept = minutes[i];
            if (minutes_slept > max_slept_minutes)
            {
                most_frequent_minute = i;
                max_slept_minutes = minutes_slept;
            }
        }

        if (max_slept_minutes > total_max_minutes_slept)
        {
            total_max_minutes_slept = max_slept_minutes;
            guard_id = it->first;
            all_most_frequent_minute = most_frequent_minute;
        }

        it++;
    }

    return make_tuple(all_most_frequent_minute, guard_id);
}

void add_guards(vector<string> &inpts, map<int, tuple<int, vector<int>>> &guard_minutes)
{
    string line;
    map<int, tuple<int, vector<int>>>::iterator it;
    int current_guard_id;
    int hash_idx = 25;
    int minute_idx = 15;
    int fell_asleep_min = 0;
    int woke_up_min = 0;
    bool is_sleeping = false;
    for (int i = 0; i < inpts.size(); i++)
    {
        string line = inpts[i];
        char line_type = line.at(19);

        // New guard
        if (line_type == 'G')
        {
            // Continue to create the new guard
            current_guard_id = stoi(line.substr(hash_idx + 1, 4));
            it = guard_minutes.find(current_guard_id);

            // If we haven't added this guard yet
            if (it == guard_minutes.end())
            {
                vector<int> minutes(60, 0);
                guard_minutes[current_guard_id] = make_tuple(0, minutes);
            }
        }
        // Fall asleep
        else if (line_type == 'f')
        {
            fell_asleep_min = stoi(line.substr(minute_idx, 2));
            is_sleeping = true;
            // Wake up
        }
        else
        {
            woke_up_min = stoi(line.substr(minute_idx, 2));

            tuple<int, vector<int>> &gm = guard_minutes.find(current_guard_id)->second;

            update_guard_sleep(gm, fell_asleep_min, woke_up_min);

            is_sleeping = false;
        }

        ++runs;
    }
}

int find_worst_guard(map<int, tuple<int, vector<int>>> &guard_minutes)
{
    map<int, tuple<int, vector<int>>>::iterator it;
    it = guard_minutes.begin();

    int max_total_minutes = 0;
    int worst_id = 0;
    while (it != guard_minutes.end())
    {

        tuple<int, vector<int>> tp = it->second;

        int total_minutes = get<0>(tp);
        vector<int> minutes = get<1>(tp);

        if (total_minutes > max_total_minutes)
        {
            max_total_minutes = total_minutes;
            worst_id = it->first;
        }
        it++;
        ++runs;
    }

    return worst_id;
}

int find_worst_minute(int guard_id, map<int, tuple<int, vector<int>>> &guard_minutes)
{

    tuple<int, vector<int>> tp = guard_minutes[guard_id];
    vector<int> minutes = get<1>(tp);

    int worst_minute = 0;
    int max_minutes_slept = 0;
    for (int i = 0; i < minutes.size(); i++)
    {
        if (minutes[i] > max_minutes_slept)
        {
            worst_minute = i;
            max_minutes_slept = minutes[i];
        }
        ++runs;
    }

    return worst_minute;
}

void update_guard_sleep(tuple<int, vector<int>> &tp, int fell_asleep_min, int woke_up_min)
{
    int &total_minutes_slept = get<0>(tp);
    vector<int> &minutes = get<1>(tp);

    total_minutes_slept += (woke_up_min - fell_asleep_min - 1);

    int i = 0;
    for (i = fell_asleep_min; i < woke_up_min; i++)
    {
        minutes[i] += 1;
        ++runs;
    }
}

void read_input(string filename, vector<string> &inpts)
{
    string line;
    ifstream inputfile(filename);
    if (inputfile.is_open())
    {
        int i = 0;
        while (getline(inputfile, line))
        {
            //inpts.push_back(line);
            inpts[i] = line;
            i++;
            ++runs;
        }
    }
}

bool compare_line_dates(string &line_a, string &line_b)
{
    string str_time_a = line_a.substr(1, 16);
    string str_time_b = line_b.substr(1, 16);

    char buffer_a[16];
    char buffer_b[16];
    strncpy(buffer_a, str_time_a.c_str(), 16);
    strncpy(buffer_b, str_time_b.c_str(), 16);

    ++runs;

    struct tm tm_a;
    struct tm tm_b;

    strptime(buffer_a, "%Y-%m-%d %H:%M", &tm_a);
    strptime(buffer_b, "%Y-%m-%d %H:%M", &tm_b);

    if (tm_a.tm_yday < tm_b.tm_yday)
    {
        return true;
    }
    else if (tm_a.tm_yday == tm_b.tm_yday)
    {

        // If it is the same hour we compare minutes
        if (tm_a.tm_hour == tm_b.tm_hour)
        {
            return tm_a.tm_min < tm_b.tm_min;
        }

        // else we compare hours
        return tm_a.tm_hour < tm_b.tm_hour;
    }
    else
    {
        return false;
    }
}
