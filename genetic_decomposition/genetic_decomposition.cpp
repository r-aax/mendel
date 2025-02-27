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
    srand(time({}));

    // area
    AreaGraph ag;
    ag.init_from_rectangular_area(10, 10);
    ag.print();

    // create polulation
    Population pop(10, ag, 4);

    pop.sort_items();
    pop.print();

    for (auto i{ 0 }; i < 1000; ++i)
    {
        cout << "i = " << i << endl;
        pop.evolution_step(0.25);
        pop.print();
    }

    pop.items[0]->print(10);
}
