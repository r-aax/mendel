#pragma once

/// <summary>
/// 
/// </summary>
enum class CrossoverPairsSelectionStrategy
{
    /// <summary>
    /// 
    /// </summary>
    Random,

    /// <summary>
    /// a b c d .... d c b a
    /// </summary>
    BestN_WorstN,

    /// <summary>
    /// 
    /// </summary>
    Best1_WorstN,

    /// <summary>
    /// a a b b c c d d ....
    /// </summary>
    BestPairs
};
