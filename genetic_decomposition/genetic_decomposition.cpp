#include <iostream>

#include "area_graph.h"
#include "decomposition.h"
#include "population.h"
#include "genome.h"
#include "utils.h"

using namespace std;

/// <summary>
/// 
/// </summary>
/// <returns></returns>
int main()
{
    srand(static_cast<unsigned int>(time({})));

    // area
    AreaGraph ag;
    ag.init_from_rectangular_area(45, 45);
    ag.print();

    // create polulation
    Population pop(100, ag, 9);

    pop.sort_items();
    pop.print();

    for (auto i{ 0 }; i < 500; ++i)
    {
        cout << "i = " << i << endl;
        pop.evolution_step(0.25);
        pop.print();

        if (pop.items[0]->cost() == pop.items.back()->cost())
        {
            break;
        }
    }

    pop.items[0]->print(45);
}
