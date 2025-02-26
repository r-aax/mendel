#pragma once

#include <vector>

using namespace std;

/// <summary>
/// 
/// </summary>
class AreaGraph
{

public:

    /// <summary>
    /// 
    /// </summary>
    vector<vector<int>> inc;

    /// <summary>
    /// 
    /// </summary>
    vector<vector<int>> es;

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
        return inc.size();
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
