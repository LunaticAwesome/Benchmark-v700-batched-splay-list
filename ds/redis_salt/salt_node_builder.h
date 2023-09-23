#pragma once

#include "salt_node.h"
#include <assert.h>
#include <algorithm>

template <typename Score, typename Member>
class SaltNodeBuilder {
public:
    using NODE = SaltNode<Score, Member>;

    SaltNodeBuilder()
        : scores_(nullptr),
          member_data_(nullptr),
          children_(nullptr),
          counts_(nullptr),
          rebuild_bound_(-1),
          rep_size_(0),
          asize_(0),
          capacity_(-1) {
    }

    void SetLeftBound(Score left_bound) {
        left_bound_ = left_bound;
    }

    void SetRightBound(Score right_bound) {
        right_bound_ = right_bound;
    }

    void SetCapacity(int capacity) {
        capacity_ = capacity;
        scores_ = new Score[capacity];
        member_data_ = new typename NODE::MemberData[capacity];

        children_ = new NODE*[capacity + 1];
        std::fill(children_, children_ + capacity + 1, nullptr);

        counts_ = new int[2 * capacity + 1];
        std::fill(counts_, counts_ + (2 * capacity + 1), 0);
    }

    void SetRebuildBound(int64_t rebuild_bound) {
        rebuild_bound_ = rebuild_bound;
    }

    void SetRepSize(int rep_size) {
        rep_size_ = rep_size;
    }

    void SetApproximateSize(int asize) {
        asize_ = asize;
    }

    void SetScore(int index, Score score) {
        scores_[index] = score;
    }

    void SetMemberData(int index, typename NODE::MemberData md) {
        member_data_[index] = md;
    }

    void SetChild(int index, NODE* child) {
        children_[index] = child;
    }

    void IncrementCount(int index, int value = 1) {
        counts_[index] += value;
    }

    bool IsMarked(int index) {
        return member_data_[index].accesses < 0;
    }

    NODE* Build(int64_t total_accesses = -1) {
        bool is_leaf = true;
        for (int i = 0; i <= rep_size_; ++i) {
            if (children_[i]) {
                is_leaf = false;
                break;
            }
        }

        return new NODE(scores_, member_data_, children_, counts_, capacity_, left_bound_, right_bound_,
                        rebuild_bound_, rep_size_, asize_, is_leaf);
    }

private:
    Score* scores_;
    typename NODE::MemberData* member_data_;
    NODE** children_;
    int* counts_;

    Score left_bound_;
    Score right_bound_;
    int64_t rebuild_bound_;
    int rep_size_;
    int asize_;
    int capacity_;
};
