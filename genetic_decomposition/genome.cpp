#include "genome.h"

#include <iostream>
#include <cassert>

#include "utils.h"

/// <summary>
/// 
/// </summary>
Genome::Genome(size_t colors_count,
               size_t nodes_count)
{
    items.clear();

    for (int i{ 0 }; i < colors_count; ++i)
    {
        items.push_back(randint(0, static_cast<int>(nodes_count - 1)));
    }
}

/// <summary>
/// 
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
Genome::Genome(const Genome& a,
               const Genome& b)
{
    assert(a.size() == b.size());

    auto s{ a.size() };

    items.clear();

    for (auto i{ 0 }; i < s; ++i)
    {
        items.push_back(randbool() ? a.items[i] : b.items[i]);
    }
}

/// <summary>
/// 
/// </summary>
/// <param name="inc"></param>
void Genome::mutate(const vector<vector<size_t>>& inc)
{
    // select gene index (color)
    auto i{ randint(size()) };

    // find node for this color
    auto node{ items[i] };

    // now check if there are neighbours
    auto neighbours_count{ inc[node].size() };
    if (neighbours_count == 0)
    {
        return;
    }

    // select direction to move
    auto direction{ randint(neighbours_count) };

    // write mutation to genome
    node = inc[node][direction];
    items[i] = node;
}

/// <summary>
/// 
/// </summary>
void
Genome::print()
{
    cout << "GENOME:";

    for (auto x : items)
    {
        cout << " " << x;
    }

    cout << endl;
}
