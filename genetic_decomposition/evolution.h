#pragma once

#include "area_graph.h"
#include "evolution_types.h"
#include "population.h"

/// <summary>
/// 
/// </summary>
class Evolution
{

public:

    /// <summary>
    /// 
    /// </summary>
    AreaGraph& area_graph;

    /// <summary>
    /// 
    /// </summary>
    size_t partitions_count;

    /// <summary>
    /// 
    /// </summary>
    size_t epochs_count{ 0 };

    /// <summary>
    /// 
    /// </summary>
    size_t population_size{ 0 };

    /// <summary>
    /// 
    /// </summary>
    double extinction_ratio{ 0.0 };

    /// <summary>
    /// 
    /// </summary>
    double mutation_probability{ 0.0 };

    /// <summary>
    /// 
    /// </summary>
    CrossoverPairsSelectionStrategy crossover_pairs_selection_strategy;

    /// <summary>
    /// 
    /// </summary>
    Population population;

    /// <summary>
    /// 
    /// </summary>
    size_t print_row;

    /// <summary>
    /// 
    /// </summary>
    /// <param name="area_graph_"></param>
    /// <param name="partitions_count_"></param>
    /// <param name="epochs_count_"></param>
    /// <param name="population_size_"></param>
    /// <param name="extinction_ratio_"></param>
    /// <param name="mutation_probability_"></param>
    /// <param name="crossover_pairs_selection_strategy_"></param>
    /// <param name="print_row_"></param>
    Evolution(AreaGraph& area_graph_,
              size_t partitions_count_,
              size_t epochs_count_,
              size_t population_size_,
              double extinction_ratio_,
              double mutation_probability_,
              CrossoverPairsSelectionStrategy crossover_pairs_selection_strategy_,
              size_t print_row_)
        : area_graph{ area_graph_ },
          partitions_count{ partitions_count_ },
          epochs_count{ epochs_count_ },
          population_size{ population_size_ },
          extinction_ratio{ extinction_ratio_ },
          mutation_probability{ mutation_probability_ },
          crossover_pairs_selection_strategy{ crossover_pairs_selection_strategy_ },
          population(population_size, area_graph, partitions_count),
          print_row{ print_row_ }
    {
    }

    /// <summary>
    /// 
    /// </summary>
    void run();
};
