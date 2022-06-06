#include "graph.h"
#include <list>
#include <iostream>

using namespace std;

/*
 * constructor/destructor
 */
graph::graph(int n)
{ /*<<<*/
    no_vert = (n > 0) ? n : 1;

/*
 * allocate adjacency matrix
 */
    m_edge = new int*[no_vert];
    for (int i = 0; i < no_vert; i++)
        m_edge[i] = new int[no_vert];

    initialize();
} /*>>>*/

graph::~graph()
{ /*<<<*/
/*
 * delete nil element and all other allocated nodes
 */
    for (int i = 0; i < no_vert; i++)
        delete[] m_edge[i];
    delete[] m_edge;
} /*>>>*/


void graph::initialize()
{ /*<<<*/
/*
 * initialize adjacency matrix
 * -> use infinity to allow 0 weight edges
 */
    for (int i = 0; i < no_vert; i++)
        for (int j = 0; j < no_vert; j++)
            m_edge[i][j] = INT_MAX;

} /*>>>*/

void graph::permutation(int* perm, int n)
{ /*<<<*/
    random_generator rg;
    int p_tmp, p_pos;

    for (int i = 0; i < n; i++)
        perm[i] = i;

    for (int i = 0; i < n; i++)
    {
        rg >> p_pos;
        p_pos = (p_pos % (n - i)) + i;

        p_tmp = perm[i];
        perm[i] = perm[p_pos];
        perm[p_pos] = p_tmp;
    }
} /*>>>*/

void graph::output(int** m_out, int** m_out_2)
{ /*<<<*/
    if (!m_out)
        m_out = m_edge;

    cout << "[";
    for (int i = 0; i < no_vert; i++)
    {
        cout << "[\t";
        for (int j = 0; j < no_vert; j++)
            if (m_out[i][j] == INT_MAX)
                cout << "inf\t";
            else
                cout << m_out[i][j] << "\t";

        if (m_out_2)
        {
            cout << "]\t\t[\t";
            for (int j = 0; j < no_vert; j++)
                if (m_out_2[i][j] == INT_MAX)
                    cout << "inf\t";
                else
                    cout << m_out_2[i][j] << "\t";
        }

        cout << "]" << endl;
    }
    cout << "]" << endl;
} /*>>>*/


// TODO: Implement problem 1
void graph::generate_random(int n_edges, int max_weight)
{
    random_generator rg;
    int *edge_array = new int[no_vert];
    int max_edges = (no_vert * no_vert) - no_vert;
    int edge_count = 0;
   

    while (edge_count < n_edges && edge_count < max_edges)
    {
        
        permutation(edge_array, no_vert);

        int curr_node = edge_array[0];

        for (int i = 1; i < no_vert; i++)
        {
            int next_node = edge_array[i];
            int weight;

            
            rg >> weight;
            weight = (weight % ((max_weight * 2) + 1)) - max_weight;

            
            if (m_edge[curr_node][next_node] == INT_MAX)
            {
                m_edge[curr_node][next_node] = weight;
                edge_count++;

                // Paste the code givenin the report to avoid negative cycles from being created in order for the bellman ford's algorithm.

            }
            curr_node = next_node;

            if (edge_count == n_edges || edge_count == max_edges)
                break;
        }
    }
    delete [] edge_array;
}

// TODO: Implement problem 3
bool graph::bellman_ford(int s, int*& v_d, int*& v_pi)
{

    v_d = new int[no_vert];
    v_pi = new int[no_vert];

    // initialize arrays
    for (int i = 0; i < no_vert; i++)
    {
        v_d[i] = INT_MAX;
        v_pi[i] = INT_MAX;
    }

    v_d[s] = 0;

    // repeat no_vert - 1 times
    for (int i = 0; i < no_vert - 1; i++)               // Applying the pseudocode of Bellman Ford' algorithm
    {
        for (int j = 0; j < no_vert; j++)
        {
            int curr_vertex = (s + j) % no_vert;

            if (v_d[curr_vertex] != INT_MAX)
            {
                for (int k = 0; k < no_vert; k++)
                {
                    int curr_weight = m_edge[curr_vertex][k];
                    if (curr_weight != INT_MAX)
                    {
                        v_pi[k] = v_d[curr_vertex] + curr_weight < v_d[k] ? curr_vertex : v_pi[k];
                        v_d[k] = min(v_d[curr_vertex] + curr_weight, v_d[k]);
                    }
                }
            }
        }
    }

    
    for (int j = 0; j < no_vert; j++) {                       // To check if the graph contains negative cycle
        int curr_vertex = (s + j) % no_vert;
        
        if (v_d[curr_vertex] != INT_MAX)
        {
            for (int k = 0; k < no_vert; k++)
            {
                int curr_weight = m_edge[curr_vertex][k];
                if (curr_weight != INT_MAX)
                {
                    int dist = v_d[curr_vertex] + curr_weight;
                    if (dist < v_d[k])
                    {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

// TODO: Implement problem 4
void graph::floyd_warshall(int**& d, int**& pi)
{

    d = new int *[no_vert];
    pi = new int *[no_vert];

    
    for (int i = 0; i < no_vert; i++)                                   // Declare arrays
    {
        d[i] = new int[no_vert];
        pi[i] = new int[no_vert];

        for (int j = 0; j < no_vert; j++)
        {
            d[i][j] = i == j ? 0 : m_edge[i][j];
            pi[i][j] = m_edge[i][j] != INT_MAX ? i : m_edge[i][j];
        }
    }

     
    for (int k = 0; k < no_vert; k++)                                     // Applying Floyd Warshall algorithm
    {
        for (int i = 0; i < no_vert; i++)
        {
            for (int j = 0; j < no_vert; j++)
            {
                if (d[i][j] > d[i][k] + d[k][j] && d[i][k] != INT_MAX && d[k][j] != INT_MAX) {
                    d[i][j] = d[i][k] + d[k][j];
                    pi[i][j] = pi[k][j];
                }
            }
        }
    }
}

