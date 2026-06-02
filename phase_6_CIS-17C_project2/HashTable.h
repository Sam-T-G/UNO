#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <vector>
#include <list>
#include <utility>
#include <cstddef>
#include <string>
using namespace std;

// Open-chained hash table keyed by string. Value type V is the only
// template knob; the key is always string so the bucket index can use a
// BKDR string mix without a separate hash trait.
template <typename V>
class HashTable
{
public:
    class iterator
    {
    public:
        iterator(HashTable *t, size_t b);
        pair<string, V> &operator*();
        iterator &operator++();
        bool operator!=(const iterator &o) const;

    private:
        HashTable *tbl;
        size_t bkt;
        typename list<pair<string, V>>::iterator inr;
        void skip();
    };

    HashTable(size_t cap = 17);

    void insert(const string &k, const V &v); // insert or update
    V *find(const string &k);                 // nullptr if not found
    size_t size() const;
    iterator begin();
    iterator end();

private:
    static size_t hashStr(const string &s);
    size_t bktIdx(const string &k) const;

    vector<list<pair<string, V>>> bkts;
    size_t cnt;
};

// --- implementation (template, header-only) ---

template <typename V>
HashTable<V>::HashTable(size_t cap) : bkts(cap > 0 ? cap : 17), cnt(0) {}

// BKDR multiplicative hash, seed 131.
template <typename V>
size_t HashTable<V>::hashStr(const string &s)
{
    size_t h = 0;
    for (size_t i = 0; i < s.size(); ++i)
    {
        h = h * 131 + static_cast<size_t>(s[i]);
    }
    return h;
}

template <typename V>
size_t HashTable<V>::bktIdx(const string &k) const
{
    return hashStr(k) % bkts.size();
}

template <typename V>
void HashTable<V>::insert(const string &k, const V &v)
{
    size_t b = bktIdx(k);
    typename list<pair<string, V>>::iterator it = bkts[b].begin();
    for (; it != bkts[b].end(); ++it)
    {
        if (it->first == k)
        {
            it->second = v; // overwrite existing key
            return;
        }
    }
    bkts[b].push_back(make_pair(k, v));
    ++cnt;
}

template <typename V>
V *HashTable<V>::find(const string &k)
{
    size_t b = bktIdx(k);
    typename list<pair<string, V>>::iterator it = bkts[b].begin();
    for (; it != bkts[b].end(); ++it)
    {
        if (it->first == k)
        {
            return &it->second;
        }
    }
    return nullptr;
}

template <typename V>
size_t HashTable<V>::size() const
{
    return cnt;
}

template <typename V>
typename HashTable<V>::iterator HashTable<V>::begin()
{
    return iterator(this, 0);
}

template <typename V>
typename HashTable<V>::iterator HashTable<V>::end()
{
    return iterator(this, bkts.size());
}

// --- iterator ---

template <typename V>
HashTable<V>::iterator::iterator(HashTable *t, size_t b) : tbl(t), bkt(b)
{
    if (bkt < tbl->bkts.size())
    {
        inr = tbl->bkts[bkt].begin();
        skip();
    }
}

// Advance past empty buckets so operator* always points at a live entry.
template <typename V>
void HashTable<V>::iterator::skip()
{
    while (bkt < tbl->bkts.size() && inr == tbl->bkts[bkt].end())
    {
        ++bkt;
        if (bkt < tbl->bkts.size())
        {
            inr = tbl->bkts[bkt].begin();
        }
    }
}

template <typename V>
pair<string, V> &HashTable<V>::iterator::operator*()
{
    return *inr;
}

template <typename V>
typename HashTable<V>::iterator &HashTable<V>::iterator::operator++()
{
    ++inr;
    skip();
    return *this;
}

template <typename V>
bool HashTable<V>::iterator::operator!=(const iterator &o) const
{
    if (bkt != o.bkt)
    {
        return true;
    }
    if (bkt >= tbl->bkts.size())
    {
        return false;
    }
    return inr != o.inr;
}

#endif
