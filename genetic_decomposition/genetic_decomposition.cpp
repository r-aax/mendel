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

    // create two decompositions
    Decomposition d1(ag, 4), d2(ag, 4);
    d1.paint_from_genome();
    d1.calculate_metrics();
    d2.paint_from_genome();
    d2.calculate_metrics();
    d1.print(10);
    d2.print(10);

    // create decomposition from parents
    Decomposition d(d1, d2);
    d.paint_from_genome();
    d.calculate_metrics();
    d.print(10);
}
