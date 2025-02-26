#include "decomposition.h"

#include <iostream>
#include <algorithm>

#include "borders_map.h"

using namespace std;

/// <summary>
/// 
/// </summary>
/// <param name="g_"></param>
/// <param name="colors_count_"></param>
Decomposition::Decomposition(AreaGraph& g_,
                             int colors_count_)
    : g(g_),
      colors_count(colors_count_),
      nodes_colors(g.nodes_count())
{
}

/// <summary>
///
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
Decomposition::Decomposition(Decomposition& a,
                             Decomposition& b)
    : g(a.g),
      colors_count(a.colors_count),
      nodes_colors(g.nodes_count())
{
    vector<int> hist(colors_count);

    for (int i { 0 }; i < g.nodes_count(); ++i)
    {
        int ca { a.nodes_colors[i] }, cb { b.nodes_colors[i] };

        if (ca == cb)
        {
            nodes_colors[i] = ca;
        }
        else
        {
            nodes_colors[i] = -1;
            ++hist[ca];
            ++hist[cb];
        }
    }

    vector<int> unused_colors;

    for (int i { 0 }; i < colors_count; ++i)
    {
        for (int j { 0 }; j < (hist[i] / 2); ++j)
        {
            unused_colors.push_back(i);
        }
    }

    random_shuffle(unused_colors.begin(), unused_colors.end());
    repaint_negative_colors_from_vector(unused_colors);
    repaint_isolated_nodes();
    calculate_borders_map();
}

/// <summary>
/// 
/// </summary>
/// <param name="ind"></param>
/// <returns></returns>
bool
Decomposition::is_node_isolated(int ind)
{
    int color { nodes_colors[ind] };

    for (int ngh : g.inc[ind])
    {
        if (nodes_colors[ngh] == color)
        {
            return false;
        }
    }

    return true;
}

/// <summary>
///
/// </summary>
/// <param name="v"></param>
void
Decomposition::repaint_negative_colors_from_vector(vector<int>& v)
{
    int ni { 0 }, vi { 0 };

    while ((ni < nodes_colors.size()) && (vi < v.size()))
    {
        if (nodes_colors[ni] == -1)
        {
            nodes_colors[ni] = v[vi++];
        }

        ++ni;
    }
}

/// <summary>
/// 
/// </summary>
void
Decomposition::repaint_isolated_nodes()
{
    vector<int> unused_colors;

    for (int i = 0; i < g.nodes_count(); ++i)
    {
        if (is_node_isolated(i))
        {
            unused_colors.push_back(nodes_colors[i]);
            nodes_colors[i] = -1;
        }
    }

    random_shuffle(unused_colors.begin(), unused_colors.end());
    repaint_negative_colors_from_vector(unused_colors);
}

/// <summary>
/// 
/// </summary>
/// <param name="start_color"></param>
void
Decomposition::paint_uniform(int start_color)
{
    int color { start_color };

    for (auto& x : nodes_colors)
    {
        x = color;
        color = (color + 1) % colors_count;
    }

    calculate_borders_map();
}

/// <summary>
/// 
/// </summary>
void
Decomposition::paint_random()
{
    int color { 0 };
    vector<int> colors;

    for (auto& x : nodes_colors)
    {
        colors.push_back(color);
        color = (color + 1) % colors_count;
    }

    random_shuffle(colors.begin(), colors.end());

    paint_from_vector(colors);
}

/// <summary>
/// 
/// </summary>
/// <param name="init_colors"></param>
void
Decomposition::paint_from_vector(vector<int> init_colors)
{
    for (int i { 0 }; i < g.nodes_count(); ++i)
    {
        nodes_colors[i] = init_colors[i];
    }

    calculate_borders_map();
}

/// <summary>
/// 
/// </summary>
void
Decomposition::calculate_borders_map()
{
    BordersMap bm(colors_count);

    bm.calc(g.es, nodes_colors);
    borders_map_max = bm.max();
    borders_map_sum = bm.sum();
}

/// <summary>
/// 
/// </summary>
void
Decomposition::print()
{
    cout << "DECOMP: max_border = " << borders_map_max << ", sum_border = " << borders_map_sum << ", cost = " << cost() << endl;
    
    cout << "COLORS:";

    for (int i { 0 }; i < nodes_colors.size(); ++i)
    {
        if ((i % colors_count) == 0)
        {
            cout << endl;
        }

        cout << " " << nodes_colors[i];
    }

    cout << endl;
}
