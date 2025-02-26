#include "area_graph.h"

#include <iostream>

/// <summary>
/// 
/// </summary>
AreaGraph::AreaGraph()
{
}

/// <summary>
/// 
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
void
AreaGraph::link_two_nodes(int a,
                          int b)
{
    g[a].push_back(b);
    g[b].push_back(a);
    es.push_back({ a, b });
}

/// <summary>
/// 
/// </summary>
/// <param name="rows"></param>
/// <param name="cols"></param>
void
AreaGraph::init_from_rectangular_area(int rows,
                                      int cols)
{
    g.clear();
    g.resize(rows * cols);

    for (int i { 0 }; i < rows; ++i)
    {
        for (int j { 0 }; j < cols; ++j)
        {
            int ind { i * cols + j };

            if (i < rows - 1)
            {
                link_two_nodes(ind, ind + cols);
            }

            if (j < cols - 1)
            {
                link_two_nodes(ind, ind + 1);
            }
        }
    }
}

/// <summary>
/// 
/// </summary>
void
AreaGraph::print()
{
    cout << "G (" << nodes_count() << " nodes, " << edges_count() << " edges):" << endl;

    for (int i { 0 }; i < g.size(); ++i)
    {
        cout << i << ":";

        for (auto x : g[i])
        {
            cout << " " << x;
        }

        cout << endl;
    }

    cout << "ES:";

    for (auto& e : es)
    {
        cout << " [" << e[0] << ", " << e[1] << "]";
    }

    cout << endl;
}
