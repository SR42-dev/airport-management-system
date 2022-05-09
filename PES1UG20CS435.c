#include "header.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

// ANY STATIC FUNCTIONS ARE UP HERE

static void q1TraverseDFS(int n, const connection_t graph[n][n], int visited[], int m)
{
    visited[m] = 1;
    for (int i = m; i < n; i++) for (int j = 0; j < n; j++) if (graph[i][j].distance != __INT_MAX__ && visited[j] != 1) q1TraverseDFS(n, graph, visited, j);
}

static int checkVisited(int visited[], int n)
{

    for (int i = 0; i < n; i++)
    {
        if (visited[i] != 1) return 0;
        visited[i] = 0;
    }

    return 1;
}

static void q2TraverseDFS(int n, const connection_t graph[n][n], int visited[], int m, int destination, int num, int* ans)
{
    visited[m] = 1;
    if (m == destination)
    {
        int flag = 0;
        for (int i = 0; i < n; i++) if (visited[i] == 1) flag++;
        if (flag <= num + 1) *ans = 1;
    }

    for (int i = m; i < n; i++) for (int j = 0; j < n; j++) if (graph[i][j].distance != __INT_MAX__ && visited[j] != 1) q2TraverseDFS(n, graph, visited, j, destination, num, ans);
}

static void q3TraverseDFS(int n, const connection_t matrix[n][n], int visited[], int m, int s, int* ans)
{
    visited[m] = 1;
    for (int i = m; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j].distance != __INT_MAX__ && j == s)
            {
                *ans = 1;
            }
            if (matrix[i][j].distance != __INT_MAX__ && visited[j] != 1)
            {
                q3TraverseDFS(n, matrix, visited, j, s, ans);
            }
        }
    }
}

static void swap(airport_t* x, airport_t* y)
{
    airport_t t = *x;
    *x = *y;
    *y = t;
}

static int partition(airport_t a[], int start, int end, int (*predicate_func)(const airport_t*, const airport_t*))
{
    int partitionIndex = start;
    airport_t pivot = a[end];
    int i;
    for (i = start; i < end; i++)
    {
        if (predicate_func(&a[i], &pivot))
        {
            swap(&a[i], &a[partitionIndex]);
            partitionIndex++;
        }
    }
    swap(&a[end], &a[partitionIndex]);
    return partitionIndex;
}

static void quickSort(airport_t a[], int start, int end, int (*predicate_func)(const airport_t*, const airport_t*))
{
    if (start < end)
    {
        int pIndex = partition(a, start, end, predicate_func);
        quickSort(a, start, pIndex - 1, predicate_func);
        quickSort(a, pIndex + 1, end, predicate_func);
    }
}

static int length(airport_t airport1, airport_t airport2)
{
    int i = 0;
    while (airport1.airport_name[i] != '\0' && airport2.airport_name[i] != '\0' && airport1.airport_name[i] == airport2.airport_name[i]) i++;
    return i;
}

static void shiftTable(const char p[], int t[])
{
    int m = 0;
    for (int i = 0; p[i] != '\0'; i++) m++;
    for (int j = 0; j < 500; j++) t[j] = m;
    for (int k = 0; k < m - 1; k++) t[p[k] - '0'] = m - 1 - k;
}

static int horspool(const char src[], const char p[], int t[])
{
    int m = 0, n = 0;

    for (int i = 0; p[i] != '\0'; i++) m++;
    for (int j = 0; src[j] != '\0'; j++) n++;

    int i, j;

    i = m - 1;

    while (i < n)
    {
        j = 0;
        while ((j < m) && (p[m - 1 - j] == src[i - j])) j++;
        if (j == m) return(i - m + 1);
        else i += t[src[i] - '0'];
    }
    return -1;
}

static int minKey(int n, int key[], int setMST[])
{

    int min = INT_MAX, min_index;

    for (int v = 0; v < n; v++)
        if (setMST[v] == 0 && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

static void generateMST(int n, const connection_t graph[n][n], int parent[], pair_t edges[n - 1])
{
    for (int i = 1; i < n; i++)
    {
        edges[i - 1].first = parent[i];
        edges[i - 1].second = i;
    }
}

static int minimumTime(int n, const connection_t graph[n][n], pair_t edges[], int parent[])
{
    int res = 0;
    for (int i = 0; i < n - 1; i++) res = res + graph[edges[i].first][edges[i].second].time;
    return res;
}

static void dijkstra(int n, const connection_t graph[n][n], int start, int* hash)
{
    int cost[n][n], distance[n], pred[n];
    int visited[n], count, min, nextnode;

    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
    {
        if (graph[i][j].time == 0) cost[i][j] = INT_MAX;
        else cost[i][j] = graph[i][j].time;
    }

    for (int i = 0; i < n; i++)
    {
        distance[i] = cost[start][i];
        pred[i] = start;
        visited[i] = 0;
    }

    distance[start] = 0;
    visited[start] = 1;
    count = 1;

    while (count < n - 1)
    {
        min = INT_MAX;

        for (int i = 0; i < n; i++) if (distance[i] < min && !visited[i])
        {
            min = distance[i];
            nextnode = i;
        }

        visited[nextnode] = 1;

        for (int i = 0; i < n; i++) if (!visited[i]) if (min + cost[nextnode][i] < distance[i])
        {
            distance[i] = min + cost[nextnode][i];
            pred[i] = nextnode;
        }

        count++;
    }

    for (int i = 0; i < n; i++) if (i != start) hash[i] = distance[i];
}

// YOUR SOLUTIONS BELOW

int q1(int n, const connection_t connections[n][n])
{
    int visited[9999];

    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
    }

    int ans = 1;

    for (int i = 0; i < n; i++)
    {
        q1TraverseDFS(n, connections, visited, i);
        ans = ans & checkVisited(visited, n);
    }
    return ans;

}

int q2(const airport_t* src, const airport_t* dest, int n, int k, const connection_t connections[n][n])
{
    int sval = src->num_id;
    int dval = dest->num_id;
    int visited[9999];
    int ans = 0;
    for (int i = 0; i < n; i++) visited[i] = 0;

    q2TraverseDFS(n, connections, visited, sval, dval, k, &ans);

    if (ans == 1) return 1;
    else return 0;

}

int q3(const airport_t* src, int n, const connection_t connections[n][n])
{
    int s = src->num_id;
    int visited[9999];
    int ans = 0;
    for (int i = 0; i < n; i++) visited[i] = 0;
    q3TraverseDFS(n, connections, visited, s, s, &ans);
    return ans;
}

void q4(int n, int (*predicate_func)(const airport_t*, const airport_t*), airport_t airport_list[n])
{
    quickSort(airport_list, 0, n - 1, predicate_func);
}

pair_t q5(int n, airport_t airports[n])
{
    pair_t ans = { -1, -1 };
    int max = 0;
    int a;

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            a = length(airports[i], airports[j]);
            if (max < a)
            {
                max = a;
                ans.first = airports[i].num_id;
                ans.second = airports[j].num_id;
            }
        }
    }

    return ans;
}

int q6(int n, int amount, const int entry_fee[n])
{
    int startIndex = 0, endIndex = n - 1;
    int mid;

    while (startIndex <= endIndex)
    {
        mid = startIndex + (endIndex - startIndex) / 2;
        if (entry_fee[mid] == amount)  return mid + 1;
        else if (entry_fee[mid] < amount)  startIndex = mid + 1;
        else endIndex = mid - 1;
    }

    return startIndex;
}

void q7(int n, const char* pat, int contains[n], const airport_t airports[n])
{
    for (int i = 0; i < n; i++)
    {
        int t[9999] = { 0 };
        shiftTable(pat, t);
        if (horspool(airports[i].airport_name, pat, t) >= 0) contains[i] = 1;
    }
}

int q8(int n, int trip_order[n - 1], const connection_t connections[n][n])
{
    // I could not figure this one out. Raise an issue if you know how to do this

    return 0;
}

int q9(int n, pair_t edges[n - 1], const connection_t connections[n][n])
{
    int parent[n];
    int key[n];
    int setMST[n];

    for (int i = 1; i < n; i++)
    {
        key[i] = INT_MAX;
        setMST[i] = 0;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < n - 1; count++)
    {
        int u = minKey(n, key, setMST);
        setMST[u] = 1;
        for (int v = 0; v < n; v++) if (connections[u][v].time && setMST[v] == 0 && connections[u][v].time < key[v]) parent[v] = u, key[v] = connections[u][v].time;
    }

    generateMST(n, connections, parent, edges);

    return minimumTime(n, connections, edges, parent);
}

void q10(int n, int k, const airport_t* src, const connection_t connections[n][n], const int destinations[k], int costs[k])
{
    int hash[n];
    int i = 0;

    dijkstra(n, connections, src->num_id, hash);

    while (i != k)
    {
        costs[i] = hash[destinations[i]];
        i++;
    }
}

// END