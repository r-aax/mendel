#include <iostream>

#include "area_graph.h"
#include "decomposition.h"
#include "population.h"

using namespace std;

/// <summary>
/// 
/// </summary>
/// <returns></returns>
int main()
{
    AreaGraph ag;
    ag.init_from_rectangular_area(10, 10);
    ag.print();

    Population p(10, ag, 10);

    p.sort_items();
    p.print();
 
    for (int i { 0 }; i < 10000; ++i)
    {
        cout << "epoch " << i << endl;
        p.evolution(0.25);
        p.print();
    }

    p.items[0]->print();
}
