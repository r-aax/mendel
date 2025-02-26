#include "borders_map.h"

/// <summary>
/// 
/// </summary>
/// <param name="colors_count_"></param>
BordersMap::BordersMap(int colors_count_)
    : colors_count(colors_count_),
      m(colors_count, vector<int>(colors_count, 0))
{
}

/// <summary>
/// 
/// </summary>
void
BordersMap::clear()
{
    for (auto& row : m)
    {
        for (auto& v : row)
        {
            v = 0;
        }
    }
}

/// <summary>
/// 
/// </summary>
/// <param name="es"></param>
/// <param name="nc"></param>
void
BordersMap::calc(vector<vector<int>>& es,
                 vector<int> nc)
{
    clear();

    for (auto& e : es)
    {
        int a{ e[0] }, b{ e[1] };
        int ca{ nc[a] }, cb{ nc[b] };

        if (ca != cb)
        {
            if (ca > cb)
            {
                swap(ca, cb);
            }

            ++m[ca][cb];
        }
    }
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
int
BordersMap::max()
{
    int r{ 0 };

    for (auto& row : m)
    {
        for (auto v : row)
        {
            r = std::max(r, v);
        }
    }

    return r;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
int
BordersMap::sum()
{
    int r{ 0 };

    for (auto& row : m)
    {
        for (auto v : row)
        {
            r += v;
        }
    }

    return r;
}
