#ifndef HAND_GRAPH_H
#define HAND_GRAPH_H

#include <list>
#include <vector>
#include "Card.h"
using namespace std;

// Adjacency-list graph over an NPC hand. Nodes are cards held; an edge
// connects two cards that share a color or a suit. Used by the NPC turn to
// score candidate plays by the size of the largest remaining connected
// component after a hypothetical removal.
class HandGraph
{
public:
    HandGraph(const list<Card> &hand);

    int compSize(const Card &start) const;
    int compSizeD(const Card &start) const;
    int largestCompAfter(const Card &removed) const;

    list<Card> bfsOrder(const Card &start) const;
    list<Card> dfsOrder(const Card &start) const;

    int nodeCnt() const;

private:
    vector<Card> nds;
    vector<vector<int>> adj;

    static bool shrAttr(const Card &a, const Card &b);
    int idxOf(const Card &c) const;

    int bfsFrom(int start, const vector<bool> &skip) const;
    void dfsFrom(int u, vector<bool> &seen, list<Card> &out) const;
};

#endif
