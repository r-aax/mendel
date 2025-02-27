#include "population.h"

#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

/// <summary>
/// 
/// </summary>
/// <param name="population_size"></param>
/// <param name="g"></param>
/// <param name="colors_count"></param>
Population::Population(int population_size,
                       AreaGraph& g,
                       int colors_count)
    : items(population_size, nullptr)
{
    for (int i { 0 }; i < items.size(); ++i)
    {
        Decomposition* d = new Decomposition(g, colors_count);

        items[i] = d;
    }
}

/// <summary>
/// 
/// </summary>
Population::~Population()
{
    for (int i { 0 }; i < items.size(); ++i)
    {
        if (items[i] != nullptr)
        {
            delete items[i];
        }
    }
}

/// <summary>
/// 
/// </summary>
void
Population::sort_items()
{
    sort
    (
        items.begin(), items.end(),
        [] (Decomposition* a, Decomposition* b)
        {
            return a->cost() < b->cost();
        }
    );
}

/// <summary>
/// 
/// </summary>
/// <param name="ratio"></param>
void
Population::evolution(double ratio)
{
    assert((ratio > 0.0) && (ratio <= 0.25));

    int extinction_count = static_cast<int>(items.size() * ratio);

    cout << "extinction : " << extinction_count << endl;
}

/// <summary>
/// 
/// </summary>
void
Population::print()
{
    cout << "POPULATION (count = " << items.size() << "):";

    for (auto d : items)
    {
        cout << " " << d->cost()
             << " (" << d->max_domain << "/" << d->max_border << "/" << d->total_borders << ")";
    }

    cout << endl;
}
