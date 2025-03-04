#include "evolution.h"

#include <iostream>

using namespace std;

/// <summary>
/// 
/// </summary>
/// <param name="is_detail_print"></param>
void Evolution::run(bool is_detail_print)
{
    if (is_detail_print)
    {
        cout << "evo run : population_size = " << population_size
             << ", extinction_ratio = " << extinction_ratio
             << ", mutation_probability = " << mutation_probability << endl;
    }

    Decomposition::mutation_probability = mutation_probability;
    Decomposition::birth_counter = 0;
    Decomposition::mutation_counter = 0;

    for (int i{ 0 }; i < epochs_count; ++i)
    {
        population.evolution_step(crossover_pairs_selection_strategy,
                                  extinction_ratio);

        if (population.is_smooth())
        {
            if (is_detail_print)
            {
                cout << "evo i = " << i << " : population is smooth, evolution is stopped" << endl;
            }

            break;
        }

        if (is_detail_print)
        {
            cout << "evo i = " << i << " : best cost = "
                 << population.items[0]->cost() << ", worst cost = "
                 << population.items.back()->cost() << endl;

            /*
            string istr{ to_string(i) };

            istr.insert(0, 5 - istr.size(), '0');
            population.items[0]->paint("out/best_" + istr + ".png");
            population.items.back()->paint("out/worst_" + istr + ".png");
            */
        }
    }

    if (is_detail_print)
    {
        population.items[0]->print(print_row);

        /*
        population.items[0]->paint("out/winner.png");
        */
    }

    best_cost_finish = population.best_cost();
    best_cost_reduce = (static_cast<double>(best_cost_start) - best_cost_finish) / best_cost_start;
    creatures_count = Decomposition::birth_counter;
}
