#include "HandGraph.h"
#include <queue>
#include <algorithm>
using namespace std;

bool HandGraph::shrAttr(const Card &a, const Card &b)
{
    return a.color == b.color || a.suit == b.suit;
}

HandGraph::HandGraph(const list<Card> &hand)
{
    nds.reserve(hand.size());
    for (const Card &c : hand)
    {
        nds.push_back(c);
    }

    int n = static_cast<int>(nds.size());
    adj.assign(n, vector<int>());
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (shrAttr(nds[i], nds[j]))
            {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }
}

int HandGraph::nodeCnt() const
{
    return static_cast<int>(nds.size());
}

int HandGraph::idxOf(const Card &c) const
{
    for (int i = 0; i < static_cast<int>(nds.size()); ++i)
    {
        if (nds[i] == c)
        {
            return i;
        }
    }
    return -1;
}

int HandGraph::bfsFrom(int start, const vector<bool> &skip) const
{
    int n = static_cast<int>(nds.size());
    if (start < 0 || start >= n)
    {
        return 0;
    }
    if (skip[start])
    {
        return 0;
    }

    vector<bool> seen(n, false);
    queue<int> q;
    q.push(start);
    seen[start] = true;
    int count = 0;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        ++count;
        for (int v : adj[u])
        {
            if (!seen[v] && !skip[v])
            {
                seen[v] = true;
                q.push(v);
            }
        }
    }
    return count;
}

int HandGraph::compSize(const Card &start) const
{
    int s = idxOf(start);
    if (s < 0)
    {
        return 0;
    }
    vector<bool> skip(nds.size(), false);
    return bfsFrom(s, skip);
}

void HandGraph::dfsFrom(int u, vector<bool> &seen, list<Card> &out) const
{
    //Base Condition: stop when a node has already been visited
    if (seen[u])
    {
        return;
    }
    seen[u] = true;
    out.push_back(nds[u]);
    //Recursion: descend into every unvisited neighbor
    for (int v : adj[u])
    {
        dfsFrom(v, seen, out);
    }
}

int HandGraph::compSizeD(const Card &start) const
{
    int s = idxOf(start);
    if (s < 0)
    {
        return 0;
    }
    vector<bool> seen(nds.size(), false);
    list<Card> walk;
    dfsFrom(s, seen, walk);
    return static_cast<int>(walk.size());
}

int HandGraph::largestCompAfter(const Card &removed) const
{
    int n = static_cast<int>(nds.size());
    int r = idxOf(removed);
    vector<bool> skip(n, false);
    if (r >= 0)
    {
        skip[r] = true;
    }

    vector<bool> seen(n, false);
    int best = 0;
    for (int i = 0; i < n; ++i)
    {
        if (skip[i] || seen[i])
        {
            continue;
        }
        queue<int> q;
        q.push(i);
        seen[i] = true;
        int sz = 0;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            ++sz;
            for (int v : adj[u])
            {
                if (!seen[v] && !skip[v])
                {
                    seen[v] = true;
                    q.push(v);
                }
            }
        }
        if (sz > best)
        {
            best = sz;
        }
    }
    return best;
}

list<Card> HandGraph::bfsOrder(const Card &start) const
{
    list<Card> out;
    int s = idxOf(start);
    if (s < 0)
    {
        return out;
    }

    int n = static_cast<int>(nds.size());
    vector<bool> seen(n, false);
    queue<int> q;
    q.push(s);
    seen[s] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        out.push_back(nds[u]);
        for (int v : adj[u])
        {
            if (!seen[v])
            {
                seen[v] = true;
                q.push(v);
            }
        }
    }
    return out;
}

list<Card> HandGraph::dfsOrder(const Card &start) const
{
    list<Card> out;
    int s = idxOf(start);
    if (s < 0)
    {
        return out;
    }
    vector<bool> seen(nds.size(), false);
    dfsFrom(s, seen, out);
    return out;
}
