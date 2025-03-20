#include "borders_map.h"

#include <cassert>

/// <summary>
/// 
/// </summary>
/// <param name="colors_count_"></param>
BordersMap::BordersMap(size_t colors_count_)
    : colors_count { colors_count_ },
      m(colors_count, vector<size_t>(colors_count, 0))
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
BordersMap::calc(const vector<vector<size_t>>& es,
                 const vector<int> nc)
{
    clear();

    for (auto& e : es)
    {
        auto a { e[0] }, b { e[1] };
        auto ca { nc[a] }, cb { nc[b] };

        assert((ca != -1) && (cb != -1));

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
size_t
BordersMap::max()
{
    size_t r { 0 };

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
size_t
BordersMap::sum()
{
    size_t r { 0 };

    for (auto& row : m)
    {
        for (auto v : row)
        {
            r += v;
        }
    }

    return r;
}
