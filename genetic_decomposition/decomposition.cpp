#include "decomposition.h"

#include <iostream>
#include <algorithm>

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
      nodes_colors(g.nodes_count()),
      borders_map(colors_count, vector<int>(colors_count))
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
      nodes_colors(g.nodes_count()),
      borders_map(colors_count, vector<int>(colors_count))
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
    calculate_borders_map();
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
    for (int i { 0 }; i < colors_count; ++i)
    {
        for (int j { 0 }; j < colors_count; ++j)
        {
            borders_map[i][j] = 0;
        }
    }

    for (int i { 0 }; i < g.edges_count(); ++i)
    {
        vector<int>& e { g.edge(i) };
        int a { e[0] }, b { e[1] };

        int ca { nodes_colors[a] }, cb { nodes_colors[b] };

        if (ca != cb)
        {
            if (ca > cb)
            {
                swap(ca, cb);
            }

            ++borders_map[ca][cb];
        }
    }

    borders_map_max = 0;
    borders_map_sum = 0;

    for (int i { 0 }; i < colors_count; ++i)
    {
        for (int j { 0 }; j < colors_count; ++j)
        {
            int v { borders_map[i][j] };

            borders_map_max = max<int>(borders_map_max, v);
            borders_map_sum += v;

        }
    }
}

/// <summary>
/// 
/// </summary>
void
Decomposition::print()
{
    cout << "DECOMP: max_border = " << borders_map_max << ", sum_border = " << borders_map_sum << ", cost = " << cost() << endl;
    
    cout << "COLORS:";

    for (int i { 0 }; i < nodes_colors.size(); )
    {
        cout << " " << nodes_colors[i];

        ++i;

        if ((i % colors_count) == 0)
        {
            cout << endl;
        }
    }

    cout << "BORDERS MAP:" << endl;

    for (int i { 0 }; i < colors_count; ++i)
    {
        for (int j { 0 }; j < colors_count; ++j)
        {
            cout << " " << borders_map[i][j];
        }

        cout << endl;
    }
}
