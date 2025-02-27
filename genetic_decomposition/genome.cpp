#include "genome.h"

#include <iostream>

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
