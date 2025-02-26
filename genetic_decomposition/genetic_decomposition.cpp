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
    ag.init_from_rectangular_area(20, 20);
    ag.print();

    Decomposition d(ag, 20);
    d.paint_random();
    d.print();
}
