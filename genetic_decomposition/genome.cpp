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
