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
    AreaGraph& g;

    /// <summary>
    /// 
    /// </summary>
    int colors_count { 0 };

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
                  int colors_count_);

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
    print(int count_in_row);
};
