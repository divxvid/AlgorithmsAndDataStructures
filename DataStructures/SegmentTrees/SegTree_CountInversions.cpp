/*
 * Refer to Codeforces EDU Segment Tree part 3A.
 */


#include <bits/stdc++.h>
using namespace std ;

struct SegmentTree {
    SegmentTree *left, *right ;
    long long value ;
    int left_limit, right_limit ;

    SegmentTree() {}

    SegmentTree(vector<int>& a) {
        buildTree(a, 0, a.size()-1) ;
    }

    ~SegmentTree() {
        if (left)
            delete left ;
        if (right)
            delete right ;
    }

    void buildTree(vector<int>& a, int l, int r) {
        left_limit = l ;
        right_limit = r ;
        if (l == r) {
            value = a[l] ;
            left = right = nullptr ;
            return ;
        }

        int mid = (l + r + 1) / 2 ;
        left = new SegmentTree() ;
        left->buildTree(a, l, mid-1) ;
        right = new SegmentTree() ;
        right->buildTree(a, mid, r) ;
        this->value = left->value + right->value ;
    }

    long long range_sum(int l, int r) {
        if (this->left_limit > r || this->right_limit < l) {
            // this node is out of bound
            return 0 ; // TODO: change for other utilities
        }

        if (this->left_limit >= l && this->right_limit <= r) {
            //this node lies completely inside the interval
            return this->value ;
        }

        return left->range_sum(l, r) + right->range_sum(l, r) ;
    }

    void update(int index, int value) {
        if (left_limit == right_limit && left_limit == index) {
            this->value = value ;
            return ;
        }

        int mid = (this->left_limit + this->right_limit + 1) / 2;
        if (index < mid) {
            left->update(index, value) ;
        } else {
            right->update(index, value) ;
        }

        this->value = left->value + right->value ;
    }
};

int main() {
    int n ;
    cin >> n ;

    vector<int> a(n) ;
    for (int& x : a) cin >> x ;

    vector<int> mask(n+1, 0) ;
    SegmentTree st(mask) ;

    for (int i = 0; i < n; ++i) {
        mask[i] = st.range_sum(a[i]+1, n);
        st.update(a[i], 1) ;
    }

    for (int i = 0; i < n; ++i)
        cout << mask[i] << ' ' ;
    cout << '\n' ;
}
