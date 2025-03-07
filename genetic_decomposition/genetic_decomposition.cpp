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
    size_t side{ 300 };
    AreaGraph area_graph;
    area_graph.init_from_rectangular_area(side, side);
 
    // evolution
    Evolution evo(area_graph, 10,
                  500, 50, 0.2, 0.2,
                  CrossoverPairsSelectionStrategy::Random,
                  side);

    // run evolution
    evo.run(true, true);

    return 0;
}
