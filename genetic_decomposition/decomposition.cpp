#include "decomposition.h"

#include <iostream>
#include <algorithm>
#include <deque>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "borders_map.h"
#include "utils.h"

using namespace std;

/// <summary>
/// 
/// </summary>
/// <param name="g_"></param>
/// <param name="colors_count_"></param>
Decomposition::Decomposition(AreaGraph& g_,
                             size_t colors_count_)
    : g{ g_ },
      colors_count{ colors_count_ },
      genome(colors_count, g.nodes_count()),
      nodes_colors(g.nodes_count())
{
    birth();
}

/// <summary>
/// 
/// </summary>
/// <param name="d1"></param>
/// <param name="d2"></param>
Decomposition::Decomposition(const Decomposition& d1,
                             const Decomposition& d2)
    : g(d1.g),
      colors_count(d1.colors_count),
      genome(d1.genome, d2.genome),
      nodes_colors(g.nodes_count())
{
    // mutation
    if (randbool(mutation_probability))
    {
        ++mutation_counter;
        genome.mutate(g.inc);
    }

    birth();
}

/// <summary>
/// 
/// </summary>
void
Decomposition::paint_incremental()
{
    deque<size_t> q;

    // put into deque data from genome
    for (int i { 0 }; i < genome.items.size(); ++i)
    {
        size_t ni { genome.items[i] };

        nodes_colors[ni] = i;
        q.push_back(ni);
    }

    // try to growth
    while (!q.empty())
    {
        size_t node { q.front() };
        int color { nodes_colors[node] };

        q.pop_front();

        // check all neighbours
        for (auto ngh : g.inc[node])
        {
            if (nodes_colors[ngh] == -1)
            {
                nodes_colors[ngh] = color;
                q.push_back(ngh);
            }
        }
    }
}

/// <summary>
/// 
/// </summary>
void
Decomposition::paint_incremental_2()
{
    bool cont { true };

    // Create queue for each color.
    vector<deque<size_t>> q(colors_count);

    // For each color put one vertex into the queue.
    for (int i { 0 }; i < colors_count; ++i)
    {
        q[i].push_back(genome.items[i]);
    }

    // Now we try to growth while at least one queue is not empty.
    while (cont)
    {
        cont = false;

        for (size_t c { 0 }; c < colors_count; ++c)
        {
            if (q[c].empty())
            {
                continue;
            }

            cont = true;

            size_t node { q[c].front() };

            q[c].pop_front();

            if (nodes_colors[node] == -1)
            {
                nodes_colors[node] = c;

                for (auto ngh : g.inc[node])
                {
                    q[c].push_back(ngh);
                }
            }
        }
    }
}

/// <summary>
/// 
/// </summary>
void
Decomposition::paint_from_genome()
{
    reset_nodes_colors();
    paint_incremental_2();
}

/// <summary>
/// 
/// </summary>
void
Decomposition::calculate_metrics()
{
    BordersMap bm(colors_count);

    bm.calc(g.es, nodes_colors);
    max_border = bm.max();
    total_borders = bm.sum();

    Histogram h;

    h.calc(nodes_colors);
    max_domain = h.max();
}

/// <summary>
/// 
/// </summary>
/// <param name="count_in_row"></param>
void
Decomposition::print(size_t count_in_row)
{
    cout << "DECOMP: max_domain = " << max_domain
         << " (" << theoretical_target_max_domain() << ")"
         << ", max_border = " << max_border << ", total_borders = " << total_borders
         << ", cost = " << cost() << endl;
    genome.print();
    cout << "COLORS:";

    for (int i { 0 }; i < nodes_colors.size(); ++i)
    {
        if ((i % count_in_row) == 0)
        {
            cout << endl;
        }

        cout << " " << nodes_colors[i];
    }

    cout << endl;
}

/// <summary>
/// 
/// </summary>
/// <param name="filename"></param>
/// <param name="side"></param>
void
Decomposition::paint(string filename,
                     size_t side)
{
    int pix { 5 };

#define RGB(R, G, B) (cv::Scalar(B, G, R))

    static cv::Scalar black { RGB(0x0, 0x0, 0x0) };
    static vector<cv::Scalar> colors
    {
        RGB(0xcd, 0x5c, 0x5c), // indianred
        RGB(0xe6, 0x73, 0x00), // fulvous
        RGB(0xb0, 0xbf, 0x1a), // android green
        RGB(0x46, 0x82, 0xb4), // steel blue
        RGB(0xff, 0x80, 0x95), // salmon pink
        RGB(0x00, 0xff, 0xff), // aqua
        RGB(0xf0, 0xf8, 0xff), // alice blue
        RGB(0x99, 0xff, 0x99), // mint green
        RGB(0xff, 0xea, 0x80), // jasmine
        RGB(0xc9, 0xc0, 0xbb)  // pale silver
    };

#undef RBG

    // canvas
    cv::Mat image(side * pix, side * pix, CV_8UC3, cv::Scalar(255, 255, 255));

    if (!image.data)
    {
        throw exception("could not open or find the image");
    }

    // fill
    int thickness { -1 };

    // draw distribution
    for (int i { 0 }; i < side; ++i)
    {
        for (int j { 0 }; j < side; ++j)
        {
            int c { nodes_colors[side * i + j] };
            cv::Scalar color = ((c == -1) ? black : colors[c]);

            cv::rectangle(image,
                          cv::Point(pix * i, pix * j),
                          cv::Point(pix * (i + 1) - 1, pix * (j + 1) - 1),
                          color,
                          thickness, cv::LINE_8);
        }
    }

    // draw genome points with black color
    for (auto x : genome.items)
    {
        auto i { x / side }, j { x % side };

        cv::rectangle(image,
                      cv::Point(pix * i, pix * j),
                      cv::Point(pix * (i + 1) - 1, pix * (j + 1) - 1),
                      cv::Scalar(0, 0, 0),
                      thickness, cv::LINE_8);
    }

    cv::imwrite(filename, image);
}
