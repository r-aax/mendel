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
/// <param name="count"></param>
void Population::worst_extinction(size_t count)
{
    assert(count < size());

    for (auto i{ 0 }; i < count; ++i)
    {
        Decomposition* d{ items.back() };

        delete d;
        items.pop_back();
    }
}

/// <summary>
/// 
/// </summary>
/// <param name="count"></param>
void Population::revival(size_t count)
{
    // one new creature can be born from two parents
    assert(2 * count <= size());

    size_t lo{ 0 }, hi{ size() - 1 };

    for (auto i{ 0 }; i < count; ++i)
    {
        Decomposition* d = new Decomposition(*items[lo + i], *items[hi - i]);

        items.push_back(d);
    }
}

/// <summary>
/// 
/// </summary>
/// <param name="ratio"></param>
void Population::evolution_step(double ratio)
{
    assert((ratio > 0.0) && (ratio <= 0.25));

    size_t count = static_cast<size_t>(items.size() * ratio);

    worst_extinction(count);
    revival(count);
    sort_items();
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
