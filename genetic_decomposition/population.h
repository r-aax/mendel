#pragma once

#include "decomposition.h"

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
    Population(int population_size,
               AreaGraph& g,
               int colors_count);

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
    void
    sort_items();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="count"></param>
    void worst_extinction(size_t count);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="count"></param>
    void revival(size_t count);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="ratio"></param>
    void evolution_step(double ratio);

    /// <summary>
    /// 
    /// </summary>
    void
    print();
};

