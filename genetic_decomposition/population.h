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
    void
    sort_items();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="ratio"></param>
    void
    evolution(double ratio);

    /// <summary>
    /// 
    /// </summary>
    void
    print();
};

