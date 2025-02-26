#pragma once

#include "area_graph.h"

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
    vector<int> nodes_colors;

    /// <summary>
    /// 
    /// </summary>
    vector<vector<int>> borders_map;

    /// <summary>
    /// 
    /// </summary>
    int borders_map_max { 0 };

    /// <summary>
    /// 
    /// </summary>
    int borders_map_sum { 0 };

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
    /// <param name="a"></param>
    /// <param name="b"></param>
    Decomposition(Decomposition& a,
                  Decomposition& b);

    /// <summary>
    ///
    /// </summary>
    /// <param name="v"></param>
    void
    repaint_negative_colors_from_vector(vector<int>& v);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="start_color"></param>
    void
    paint_uniform(int start_color = 0);

    /// <summary>
    /// 
    /// </summary>
    void
    paint_random();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="init_colors"></param>
    void
    paint_from_vector(vector<int> init_colors);

    /// <summary>
    /// 
    /// </summary>
    void
    calculate_borders_map();

    /// <summary>
    /// 
    /// </summary>
    inline int
    cost() const
    {
        return borders_map_sum;
    }

    /// <summary>
    /// 
    /// </summary>
    void
    print();
};
