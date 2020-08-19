#include <bits/stdc++.h>
using namespace std;

class Square {
public:
    size_t size;
    deque<int> left, top, right, bottom;
    
    pair<int, int> offset;
    Square *parent;
    
    static deque<int> join_start(deque<int> *a, deque<int> *b, const function<int(int, int)> &func) {
        if (a->size() < b->size()) 
            swap(a, b);
        
        for (auto it1 = a->begin(), it2 = b->begin(); it2 != b->end(); it1++, it2++)
            *it1 = func(*it1, *it2);
        
        deque<int> result(std::move(*a));
        b->clear();
        return result;
    }
    
    static deque<int> join_from(deque<int> *a, deque<int> *b, const function<int(int, int)> &func, size_t offset) {
        auto it1 = a->begin() + offset;
        auto it2 = b->begin();
        
        deque<int> merged;
        while (it1 != a->end() && it2 != b->end()) {
            merged.push_back(func(*it1, *it2));
            it1++; it2++;
        }
        
        deque<int> result;
        
        if (a->size() > b->size()) {
            copy(merged.begin(), merged.end(), a->begin() + offset);
            a->insert(a->end(), it2, b->end());
            result.swap(*a);
            b->clear();
        } else {
            copy(merged.begin(), merged.end(), b->begin());
            b->insert(b->begin(), a->begin(), a->begin() + offset);
            result.swap(*b);
            a->clear();
        }
        
        return result;
    }
    
    static int min(int a, int b) {
        return std::min(a, b);
    }
    static int max(int a, int b) {
        return std::max(a, b);
    }
    
    void mirror() {
        left.swap(top);
        right.swap(bottom);
        
        swap(offset.first, offset.second);
    }
    
    static int find_offset(deque<int> &a, deque<int> &b) {
        int offset = INT_MIN;
        for (auto it1 = a.begin(), it2 = b.begin(); 
            it1 != a.end() && it2 != b.end(); it1++, it2++) {
                offset = max(offset, *it1 - *it2);
        }
        return offset;
    }
    
    void move(int horiz, int vert) {
        offset = {horiz, vert};
            
        for (int &i : left) i += horiz;
        for (int &i : right) i += horiz;
            
        for (int &i : top) i += vert;
        for (int &i : bottom) i += vert;
    }
    
public:
    Square() :
        size(1),
        left({0}),
        top({0}),
        right({1}),
        bottom({1}),
        offset({0, 0}),
        parent(nullptr)
    {}
    
    Square *right_add(Square *other) {
        int found_offset = find_offset(this->right, other->left);
        int from = found_offset + other->left.front() - this->left.front();
        int top_diff = other->top.front() - this->top.front();
        
        Square *target;
        
        if (this->size >= other->size) {
            target = this;
            other->move(found_offset, -top_diff);
        } else {
            target = other;
            this->move(-found_offset, top_diff);
        }
        
        target->size = this->size + other->size;
        
        target->top = join_from(&top, &other->top, min, from);
        target->right = join_start(&right, &other->right, max);
        target->bottom = join_from(&bottom, &other->bottom, max, from);
        target->left = join_start(&left, &other->left, min);
        
        this->parent = target;
        other->parent = target;
        
        return target;
    }
    
    Square *bottom_add(Square *other) {
        this->mirror();
        other->mirror();
        
        Square *ret = right_add(other);
        
        this->mirror();
        other->mirror();
        
        return ret;
    }
    
    pair<int, int> get_position() const {
        auto result = offset;
        
        if (parent != nullptr && parent != this) {
            auto bonus = parent->get_position();
            result.first += bonus.first;
            result.second += bonus.second;
        }
        
        return result;
    }
};

Square *process(const string &s, vector<Square*> &squares, size_t &i) {
    Square *sq;
    Square *other;
    
    while (i < s.size()) {
        char c = s[i++];
        switch(c) {
        case '(':
            sq = process(s, squares, i);
            break;
        case ')':
            return sq;
        case '.':
            squares.push_back(new Square());
            sq = squares.back();
            break;
        default:
            if (s[i] == '.') {
                i++;
                squares.push_back(new Square());
                other = squares.back();
            } else {
                other = process(s, squares, ++i);
            }
            
            if (c == '>') sq = (sq->right_add(other));
            else sq = (sq->bottom_add(other));
        }
    }
    
    return sq;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    string s; cin >> s;

    vector<Square*> squares;
    size_t i = 0;
    
    process(s, squares, i);
    
    if (squares.size() == 0) 
        exit(0);
        
    auto pos_0 = squares[0]->get_position();
    for (Square *sq : squares) {
        auto pos = sq->get_position();
        cout << pos.first - pos_0.first << " " << pos.second - pos_0.second << endl;
    }
    
    return 0;
}
