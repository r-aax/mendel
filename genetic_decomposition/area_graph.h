#pragma once

#include <vector>

using namespace std;

/// <summary>
/// 
/// </summary>
class AreaGraph
{
    /// <summary>
    /// 
    /// </summary>
    vector<vector<int>> g;

    /// <summary>
    /// 
    /// </summary>
    vector<vector<int>> es;

public:

    /// <summary>
    /// 
    /// </summary>
    AreaGraph();

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    inline size_t
    nodes_count() const
    {
        return g.size();
    }

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    inline size_t
    edges_count() const
    {
        return es.size();
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="i"></param>
    /// <returns></returns>
    inline vector<int>&
    edge(int i)
    {
        return es[i];
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="a"></param>
    /// <param name="b"></param>
    void
    link_two_nodes(int a,
                   int b);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="rows"></param>
    /// <param name="cols"></param>
    void
    init_from_rectangular_area(int rows,
                               int cols);

    /// <summary>
    /// 
    /// </summary>
    void
    print();
};
