#include "population.h"

#include <algorithm>
#include <cassert>
#include <iostream>

#include "utils.h"

using namespace std;

/// <summary>
/// 
/// </summary>
/// <param name="population_size"></param>
/// <param name="g"></param>
/// <param name="colors_count"></param>
Population::Population(size_t population_size,
                       AreaGraph& g,
                       size_t colors_count)
    : items(population_size, nullptr)
{
    for (int i { 0 }; i < items.size(); ++i)
    {
        Decomposition* d = new Decomposition(g, colors_count);

        items[i] = d;
    }

    sort_items();
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
/// <param name="mutation_probability"></param>
void Population::revival_random(size_t count,
                                double mutation_probability)
{
    assert(size() >= 2);

    int s{ static_cast<int>(size()) };

    // construct new creatures
    for (auto i{ 0 }; i < count; )
    {
        auto father{ randint(s) };
        auto mother{ randint(s) };

        if (father != mother)
        {
            items.push_back(new Decomposition(*items[father], *items[mother], mutation_probability));
            ++i;
        }
    }
}


/// <summary>
/// 
/// </summary>
/// <param name="count"></param>
/// <param name="mutation_probability"></param>
void Population::revival_best_n_worst_n(size_t count,
                                        double mutation_probability)
{
    assert(2 * count <= size());

    size_t lo{ 0 }, hi{ size() - 1 };

    for (auto i{ 0 }; i < count; ++i)
    {
        items.push_back(new Decomposition(*items[lo + i], *items[hi - i], mutation_probability));
    }
}

/// <summary>
/// 
/// </summary>
/// <param name="count"></param>
/// <param name="mutation_probability"></param>
void Population::revival_best_1_worst_n(size_t count,
                                        double mutation_probability)
{
    assert(count + 1 <= size());

    size_t hi{ size() - 1 };

    for (auto i{ 0 }; i < count; ++i)
    {
        items.push_back(new Decomposition(*items[0], *items[hi - i], mutation_probability));
    }
}

/// <summary>
/// 
/// </summary>
/// <param name="count"></param>
/// <param name="mutation_probability"></param>
void Population::revical_best_pairs(size_t count,
                                    double mutation_probability)
{
    assert(2 * count <= size());

    for (auto i{ 0 }; i < count; ++i)
    {
        items.push_back(new Decomposition(*items[2 * i], *items[2 * i + 1], mutation_probability));
    }
}

/// <summary>
/// 
/// </summary>
/// <param name="strategy"></param>
/// <param name="count"></param>
/// <param name="mutation_probability"></param>
void Population::revival(CrossoverPairsSelectionStrategy strategy,
                         size_t count,
                         double mutation_probability)
{
    switch (strategy)
    {
        case CrossoverPairsSelectionStrategy::Random:
            revival_random(count, mutation_probability);
            break;

        case CrossoverPairsSelectionStrategy::BestN_WorstN:
            revival_best_n_worst_n(count, mutation_probability);
            break;

        case CrossoverPairsSelectionStrategy::Best1_WorstN:
            revival_best_1_worst_n(count, mutation_probability);
            break;

        case CrossoverPairsSelectionStrategy::BestPairs:
            revical_best_pairs(count, mutation_probability);
            break;

        default:
            throw exception();
            break;
    }
}

/// <summary>
/// 
/// </summary>
/// <param name="strategy"></param>
/// <param name="extinction_ratio"></param>
/// <param name="mutation_probability"></param>
void Population::evolution_step(CrossoverPairsSelectionStrategy strategy,
                                double extinction_ratio,
                                double mutation_probability)
{
    assert((extinction_ratio > 0.0) && (extinction_ratio <= 0.25));

    size_t count = static_cast<size_t>(items.size() * extinction_ratio);

    worst_extinction(count);
    revival(strategy, count, mutation_probability);
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
