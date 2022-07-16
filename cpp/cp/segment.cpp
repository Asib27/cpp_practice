#include<bits/stdc++.h>

const int MX = 2e5 + 5;

vector<int> numbers(MX);

struct seg_tree {

    vector<int> vec;

    const int NEUTRAL_ELEMENT = INT_MAX;

    inline int lc(int x) { return (x << 1); } // left child
    inline int rc(int x) { return ((x << 1) | 1); } // right child

    seg_tree(int n) { vec.assign(4 * n, NEUTRAL_ELEMENT); }

    inline int combine(int a, int b) { return min(a, b); }

    // call build(1, 1, n)
    void build(int at, int start, int end) {
        if (start == end) {
            vec[at] = numbers[start];
            return;
        }

        int mid = (start + end) >> 1;

        build(lc(at), start, mid);
        build(rc(at), mid + 1, end);

        vec[at] = combine(vec[lc(at)], vec[rc(at)]);

        return;
    }

    // for updating index i, call update(1, 1, n, i)
    void update(int at, int start, int end, int update_index) {
        if (start == end && start == update_index) {

            vec[at] = numbers[update_index];
            return;
        }

        int mid = (start + end) >> 1;

        if (update_index <= mid) {
            update(lc(at), start, mid, update_index);
        } else
            update(rc(at), mid + 1, end, update_index);
            vec[at] = combine(vec[lc(at)], vec[rc(at)]);
            return;
        }

    // for query [l, r] call query(1, 1, n, l, r)
    int query(int at, int start, int end, int q_left, int q_right){
        if (start > q_right || end < q_left) return NEUTRAL_ELEMENT;
        if (start >= q_left && end <= q_right) return vec[at];

        int mid = (start + end) >> 1;
        int l = query(lc(at), start, mid, q_left, q_right);
        int r = query(rc(at), mid + 1, end, q_left, q_right);

        return combine(l, r);
    }
};