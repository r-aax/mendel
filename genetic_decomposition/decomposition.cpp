#include "decomposition.h"

#include <iostream>
#include <algorithm>
#include <deque>

#include "borders_map.h"
#include "utils.h"

using namespace std;

/// <summary>
/// 
/// </summary>
/// <param name="g_"></param>
/// <param name="colors_count_"></param>
Decomposition::Decomposition(AreaGraph& g_,
                             size_t colors_count_)
    : g{ g_ },
      colors_count{ colors_count_ },
      genome(colors_count, g.nodes_count()),
      nodes_colors(g.nodes_count())
{
    birth();
}

/// <summary>
/// 
/// </summary>
/// <param name="d1"></param>
/// <param name="d2"></param>
/// <param name="mutation_probability"></param>
Decomposition::Decomposition(const Decomposition& d1,
                             const Decomposition& d2,
                             double mutation_probability)
    : g(d1.g),
      colors_count(d1.colors_count),
      genome(d1.genome, d2.genome),
      nodes_colors(g.nodes_count())
{
    // mutation
    if (randbool(mutation_probability))
    {
        genome.mutate(g.inc);
    }

    birth();
}

/// <summary>
/// 
/// </summary>
void
Decomposition::paint_incremental()
{
    deque<size_t> q;

    // put into deque data from genome
    for (int i{ 0 }; i < genome.items.size(); ++i)
    {
        int ni{ genome.items[i] };

        nodes_colors[ni] = i;
        q.push_back(ni);
    }

    // try to growth
    while (!q.empty())
    {
        size_t node{ q.front() };
        int color{ nodes_colors[node] };
        bool is_ngh_found{ false };

        // check all neighbours
        for (auto ngh : g.inc[node])
        {
            if (nodes_colors[ngh] == -1)
            {
                nodes_colors[ngh] = color;
                q.push_back(ngh);
                is_ngh_found = true;

                break;
            }
        }

        if (!is_ngh_found)
        {
            q.pop_front();
        }
    }
}

/// <summary>
/// 
/// </summary>
void
Decomposition::paint_from_genome()
{
    reset_nodes_colors();
    paint_incremental();
}

/// <summary>
/// 
/// </summary>
void
Decomposition::calculate_metrics()
{
    BordersMap bm(colors_count);

    bm.calc(g.es, nodes_colors);
    max_border = bm.max();
    total_borders = bm.sum();

    Histogram h;

    h.calc(nodes_colors);
    max_domain = h.max();
}

/// <summary>
/// 
/// </summary>
/// <param name="count_in_row"></param>
void
Decomposition::print(size_t count_in_row)
{
    cout << "DECOMP: max_domain = " << max_domain << ", max_border = " << max_border << ", total_borders = " << total_borders
         << ", cost = " << cost() << endl;
    genome.print();
    cout << "COLORS:";

    for (int i { 0 }; i < nodes_colors.size(); ++i)
    {
        if ((i % count_in_row) == 0)
        {
            cout << endl;
        }

        cout << " " << nodes_colors[i];
    }

    cout << endl;
}
