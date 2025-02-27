#pragma once

#include "area_graph.h"
#include "genome.h"

/// <summary>
/// 
/// </summary>
class Decomposition
{

public:

    /// <summary>
    /// 
    /// </summary>
    static double mutation_probability;

    /// <summary>
    /// 
    /// </summary>
    AreaGraph& g;

    /// <summary>
    /// 
    /// </summary>
    size_t colors_count { 0 };

    /// <summary>
    /// 
    /// </summary>
    Genome genome;

    /// <summary>
    /// 
    /// </summary>
    vector<int> nodes_colors;

    /// <summary>
    /// 
    /// </summary>
    int max_domain{ 0 };

    /// <summary>
    /// 
    /// </summary>
    int max_border{ 0 };

    /// <summary>
    /// 
    /// </summary>
    int total_borders{ 0 };

    /// <summary>
    /// 
    /// </summary>
    /// <param name="g_"></param>
    /// <param name="colors_count_"></param>
    Decomposition(AreaGraph& g_,
                  size_t colors_count_);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="d1"></param>
    /// <param name="d2"></param>
    /// <param name="mutation_probability"></param>
    Decomposition(const Decomposition& d1,
                  const Decomposition& d2,
                  double mutation_probability);

    /// <summary>
    /// 
    /// </summary>
    inline void birth()
    {
        paint_from_genome();
        calculate_metrics();
    }

    /// <summary>
    /// 
    /// </summary>
    inline void
    reset_nodes_colors()
    {
        for (auto& x : nodes_colors)
        {
            x = -1;
        }
    }

    /// <summary>
    /// 
    /// </summary>
    void
    paint_incremental();

    /// <summary>
    /// 
    /// </summary>
    void
    paint_from_genome();

    /// <summary>
    /// 
    /// </summary>
    void
    calculate_metrics();

    /// <summary>
    /// 
    /// </summary>
    inline int
    cost() const
    {
        return max_domain + max_border + total_borders;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="count_in_row"></param>
    void
    print(size_t count_in_row);
};
