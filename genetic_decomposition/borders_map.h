#pragma once

#include <vector>

using namespace std;

/// <summary>
/// 
/// </summary>
class BordersMap
{

public:

    /// <summary>
    /// 
    /// </summary>
    size_t colors_count;

    /// <summary>
    /// 
    /// </summary>
    vector<vector<size_t>> m;

    /// <summary>
    /// 
    /// </summary>
    /// <param name="colors_count_"></param>
    BordersMap(size_t colors_count_);

    /// <summary>
    /// 
    /// </summary>
    void
    clear();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="es"></param>
    /// <param name="nc"></param>
    void
    calc(const vector<vector<size_t>>& es,
         const vector<int> nc);

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    int
    max();

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    int
    sum();
};
