#include "ScoreBST.h"
#include <iostream>
#include <iomanip>
using namespace std;

ScoreBST::ScoreBST()
{
    root = nullptr;
}

ScoreBST::~ScoreBST()
{
    destroy(root);
}

// Public insert delegates to the recursive helper threading the root pointer.
void ScoreBST::insert(const string &name, const Scores &scr)
{
    insert(root, name, scr);
}

// Recursive insert; ordering is trns ascending, cmbHi descending on tie.
void ScoreBST::insert(ScoreNode *&node, const string &name, const Scores &scr)
{
    //Base Condition: an empty slot becomes the new leaf
    if (node == nullptr)
    {
        node = new ScoreNode{name, scr, nullptr, nullptr};
        return;
    }
    //Recursion: walk left when the new record outranks the current node
    bool less = (scr.trns < node->scr.trns)
                || (scr.trns == node->scr.trns && scr.cmbHi > node->scr.cmbHi);
    if (less)
    {
        insert(node->left, name, scr);
    }
    else
    {
        insert(node->right, name, scr);
    }
}

// Post-order destroy frees children before the parent.
void ScoreBST::destroy(ScoreNode *node)
{
    //Base Condition: a null subtree owns nothing
    if (node == nullptr)
    {
        return;
    }
    //Recursion: free both children, then this node
    destroy(node->left);
    destroy(node->right);
    delete node;
}

// Public in-order walk; rank counter starts at 1 and the helper advances it.
void ScoreBST::inOrder() const
{
    cout << "\n"
         << setw(10) << " " << "=== LEADERBOARD (BST in-order, turns asc) ===\n";
    int rank = 1;
    inOrder(root, rank);
}

// In-order walk prints left, current, right; rank advances on each visit.
void ScoreBST::inOrder(ScoreNode *node, int &rank) const
{
    //Base Condition: an empty subtree contributes nothing
    if (node == nullptr)
    {
        return;
    }
    //Recursion: left subtree, then this node, then right subtree
    inOrder(node->left, rank);
    cout << setw(15) << " " << "Rank " << rank++ << ":\n";
    cout << setw(15) << " " << "  Player  : " << node->name << '\n';
    cout << setw(15) << " " << "  Turns   : " << node->scr.trns << '\n';
    cout << setw(15) << " " << "  HiCombo : " << node->scr.cmbHi << "\n\n";
    inOrder(node->right, rank);
}

// Public find delegates to the recursive helper starting at root.
ScoreNode *ScoreBST::find(const string &name)
{
    return find(root, name);
}

// Recursive walk; name is not the ordering key so both subtrees may match.
ScoreNode *ScoreBST::find(ScoreNode *node, const string &name)
{
    //Base Condition: an empty subtree contains no match
    if (node == nullptr)
    {
        return nullptr;
    }
    if (node->name == name)
    {
        return node;
    }
    //Recursion: check left subtree, then right subtree
    ScoreNode *hit = find(node->left, name);
    if (hit != nullptr)
    {
        return hit;
    }
    return find(node->right, name);
}

int ScoreBST::height() const
{
    return height(root);
}

// Height of a subtree; leaf height is 1, null is 0.
int ScoreBST::height(ScoreNode *node) const
{
    //Base Condition: a null subtree has zero height
    if (node == nullptr)
    {
        return 0;
    }
    //Recursion: this node contributes one, plus the taller child
    int hl = height(node->left);
    int hr = height(node->right);
    return 1 + (hl > hr ? hl : hr);
}

int ScoreBST::count() const
{
    return count(root);
}

// Count of nodes in a subtree, including the root.
int ScoreBST::count(ScoreNode *node) const
{
    //Base Condition: a null subtree owns zero nodes
    if (node == nullptr)
    {
        return 0;
    }
    //Recursion: this node counts as one, plus both children
    return 1 + count(node->left) + count(node->right);
}
