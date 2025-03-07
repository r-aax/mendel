#include "evolution.h"

#include <iostream>

using namespace std;

/// <summary>
/// 
/// </summary>
/// <param name="is_detail_print"></param>
/// <param name="is_generate_images"></param>
void Evolution::run(bool is_detail_print,
                    bool is_generate_images)
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
        }

        if (is_generate_images)
        {
           string istr{ to_string(i) };

           istr.insert(0, 5 - istr.size(), '0');
           population.items[0]->paint("out/best_" + istr + ".png", side);
           //population.items.back()->paint("out/worst_" + istr + ".png", side);
        }
    }

    if (is_detail_print)
    {
        population.items[0]->print(side);
    }

    if (is_generate_images)
    {
        population.items[0]->paint("out/winner.png", side);
    }

    best_cost_finish = population.best_cost();
    best_cost_reduce = (static_cast<double>(best_cost_start) - best_cost_finish) / best_cost_start;
    creatures_count = Decomposition::birth_counter;
}
