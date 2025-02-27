#include <iostream>

#include "area_graph.h"
#include "decomposition.h"
#include "population.h"
#include "genome.h"

using namespace std;

/// <summary>
/// 
/// </summary>
/// <returns></returns>
int main()
{
    // area
    AreaGraph ag;
    ag.init_from_rectangular_area(10, 10);
    ag.print();

    // create population
    Population pop(10, ag, 4);

    // info
    for (auto dp : pop.items)
    {
        dp->paint_from_genome();
        dp->calculate_metrics();
    }

    pop.sort_items();
    pop.print();
}
