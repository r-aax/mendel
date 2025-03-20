#pragma once

#include <string>

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
    static inline double mutation_probability{ 0.0 };

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
    size_t max_domain{ 0 };

    /// <summary>
    /// 
    /// </summary>
    size_t max_border{ 0 };

    /// <summary>
    /// 
    /// </summary>
    size_t total_borders{ 0 };

    /// <summary>
    /// 
    /// </summary>
    static inline size_t birth_counter{ 0 };

    /// <summary>
    /// 
    /// </summary>
    static inline size_t mutation_counter{ 0 };

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
    Decomposition(const Decomposition& d1,
                  const Decomposition& d2);

    /// <summary>
    /// 
    /// </summary>
    inline void birth()
    {
        ++birth_counter;
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
    paint_incremental_2();

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
    /// <returns></returns>
    inline size_t
    theoretical_target_max_domain() const
    {
        return (g.nodes_count() + 1) / colors_count;
    }

    /// <summary>
    /// 
    /// </summary>
    inline size_t
    cost() const
    {
        const size_t max_domain_penalty_weight{ 10 };
        auto max_domain_penalty{ max_domain - theoretical_target_max_domain() };
        auto max_border_penalty{ max_border };

        return max_domain_penalty * max_domain_penalty_weight + max_border_penalty;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="count_in_row"></param>
    void
    print(size_t count_in_row);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="filename"></param>
    /// <param name="side"></param>
    void
    paint(string filename,
          size_t side);
};
