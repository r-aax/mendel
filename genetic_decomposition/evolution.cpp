#include "evolution.h"

#include <iostream>

using namespace std;

/// <summary>
/// 
/// </summary>
void Evolution::run()
{
    Decomposition::mutation_probability = mutation_probability;
    Decomposition::counter = 0;

    for (int i{ 0 }; i < epochs_count; ++i)
    {
        population.evolution_step(crossover_pairs_selection_strategy,
                                  extinction_ratio);

        if (population.is_smooth())
        {
            break;
        }

        cout << "evo i = " << i << " : best cost = "
             << population.items[0]->cost() << ", worst cost = "
             << population.items.back()->cost() << endl;
    }

    population.items[0]->print(print_row);
    cout << "total creatures : " << Decomposition::counter << endl;
}
