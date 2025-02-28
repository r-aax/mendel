#pragma once

#include "decomposition.h"
#include "evolution_types.h"

/// <summary>
/// 
/// </summary>
class Population
{

public:

    /// <summary>
    /// 
    /// </summary>
    vector<Decomposition*> items;

    /// <summary>
    /// 
    /// </summary>
    /// <param name="population_size"></param>
    /// <param name="g"></param>
    /// <param name="colors_count"></param>
    Population(size_t population_size,
               AreaGraph& g,
               size_t colors_count);

    /// <summary>
    /// 
    /// </summary>
    ~Population();

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    inline size_t size() const
    {
        return items.size();
    }

    /// <summary>
    /// 
    /// </summary>
    void sort_items();

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    inline size_t best_cost() const
    {
        return items[0]->cost();
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="count"></param>
    void worst_extinction(size_t count);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="count"></param>
    void revival_random(size_t count);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="count"></param>
    void revival_best_n_worst_n(size_t count);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="count"></param>
    void revival_best_1_worst_n(size_t count);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="count"></param>
    void revical_best_pairs(size_t count);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="strategy"></param>
    /// <param name="count"></param>
    void revival(CrossoverPairsSelectionStrategy strategy,
                 size_t count);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="strategy"></param>
    /// <param name="extinction_ratio"></param>
    void evolution_step(CrossoverPairsSelectionStrategy strategy,
                        double extinction_ratio);

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    bool is_smooth() const
    {
        return items[0]->cost() == items.back()->cost();
    }

    /// <summary>
    /// 
    /// </summary>
    void
    print();
};

