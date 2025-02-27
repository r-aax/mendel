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
    int colors_count;

    /// <summary>
    /// 
    /// </summary>
    vector<vector<int>> m;

    /// <summary>
    /// 
    /// </summary>
    /// <param name="colors_count_"></param>
    BordersMap(int colors_count_);

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
    calc(const vector<vector<int>>& es,
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
