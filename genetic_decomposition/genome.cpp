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
        items.push_back(randint(static_cast<int>(nodes_count)));
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
    size_t i{ static_cast<size_t>(randint(static_cast<int>(size()))) };

    // find node for this color
    size_t node{ items[i] };

    // now check if there are neighbours
    auto neighbours_count{ inc[node].size() };
    if (neighbours_count == 0)
    {
        return;
    }

    // select direction to move
    size_t direction{ static_cast<size_t>(randint(static_cast<int>(neighbours_count))) };

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
