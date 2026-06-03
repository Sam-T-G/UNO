#ifndef SCOREBST_H
#define SCOREBST_H
#include <string>
#include "Scores.h"
using namespace std;

// One leaderboard entry in the tree. Left/right are owned and freed by the
// containing ScoreBST destructor through a post-order walk.
struct ScoreNode
{
    string name;
    Scores scr;
    ScoreNode *left;
    ScoreNode *right;
};

// Binary search tree of leaderboard entries, ordered by trns ascending with
// cmbHi descending as the tiebreak. The tree is rebuilt from scores.dat on
// every leaderboard view, so the file stays authoritative and the tree never
// outlives a single render pass.
class ScoreBST
{
public:
    ScoreBST();
    ~ScoreBST();
    void insert(const string &name, const Scores &scr);
    void inOrder() const;
    ScoreNode *find(const string &name);
    int height() const;
    int count() const;

private:
    ScoreNode *root;
    void insert(ScoreNode *&node, const string &name, const Scores &scr);
    void destroy(ScoreNode *node);
    void inOrder(ScoreNode *node, int &rank) const;
    ScoreNode *find(ScoreNode *node, const string &name);
    int height(ScoreNode *node) const;
    int count(ScoreNode *node) const;
};

#endif
