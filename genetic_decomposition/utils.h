#pragma once

#include <random>

using namespace std;

/// <summary>
/// 
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns></returns>
inline int randint(int a,
                   int b)
{
    return a + rand() % (b - a + 1);
}

/// <summary>
/// 
/// </summary>
/// <param name="n"></param>
/// <returns></returns>
inline int randint(int n)
{
    return randint(0, n - 1);
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
inline bool randbool()
{
    return randint(0, 1) == 0;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
inline double rand01()
{
    return static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
}

/// <summary>
///
/// </summary>
/// <param name="prob"></param>
/// <returns></returns>
inline bool randbool(double prob)
{
    return rand01() < prob;
}

/// <summary>
/// 
/// </summary>
class Histogram
{

public:

    /// <summary>
    /// 
    /// </summary>
    vector<int> h;

    /// <summary>
    /// 
    /// </summary>
    void
    clear()
    {
        h.clear();
    }

    /// <summary>
    /// 
    /// </summary>
    Histogram()
    {
        clear();
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="v"></param>
    void
    calc(const vector<int>& v)
    {
        int s{ *max_element(v.begin(), v.end()) };

        clear();
        h.resize(s + 1);

        for (auto x : v)
        {
            ++h[x];
        }
    }

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    int
    max()
    {
        return *max_element(h.begin(), h.end());
    }
};