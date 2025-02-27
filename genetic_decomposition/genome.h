#pragma once

#include <vector>

using namespace std;

/// <summary>
/// 
/// </summary>
class Genome
{

public:

    /// <summary>
    /// 
    /// </summary>
    vector<int> items;

    /// <summary>
    /// 
    /// </summary>
    /// <param name="colors_count"></param>
    /// <param name="nodes_count"></param>
    Genome(size_t colors_count,
           size_t nodes_count);

    /// <summary>
    /// 
    /// </summary>
    void
    print();
};
