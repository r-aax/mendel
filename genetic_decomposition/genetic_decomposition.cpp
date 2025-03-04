#include <iostream>

#include "area_graph.h"
#include "decomposition.h"
#include "population.h"
#include "genome.h"
#include "utils.h"
#include "evolution.h"

using namespace std;

/// <summary>
/// 
/// </summary>
/// <returns></returns>
int main()
{
    srand(static_cast<unsigned int>(time({})));

    // area
    size_t side{ 100 };
    AreaGraph area_graph;
    area_graph.init_from_rectangular_area(side, side);
 
    for (int i = 0; i < 100; ++i)
    {
        // evolution
        Evolution evo(area_graph, 10,
                      500, 50, 0.2, 0.2,
                      CrossoverPairsSelectionStrategy::Random,
                      side);

        // run evolution
        evo.run(false);

        // just best creature from population
        Evolution no_evo(area_graph, 10,
                         0, evo.creatures_count, 0.0, 0.0,
                         CrossoverPairsSelectionStrategy::Random,
                         side);

        cout << "RES " << i << " | bcs " << evo.best_cost_start << " | bcf " << evo.best_cost_finish << " | bcn " << no_evo.best_cost_start << endl;
    }

    cout << "FIN" << endl;
}
