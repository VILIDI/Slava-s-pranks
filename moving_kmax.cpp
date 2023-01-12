#include <iostream>
#include <vector>
#include <stack>
#include <queue>

class k_heap {
public:
    k_heap(int k)  {
        this->k_ = k;
    }
    k_heap(int k,  std::priority_queue<int, std::vector<int>, std::greater<int>> q) {
        this->k_= k;
        this->q_ = q;
    }
    k_heap clone() {
        return k_heap(k_, q_);
    }
    void insert_all(k_heap &other) {
        for (auto item: other.get_all()) {
            insert(item);
        }
    }
    void insert(int value) {
        if (q_.size() < k_) {
            q_.push(value);
        } else if (value > q_.top()) {
            q_.pop();
            q_.push(value);
        }
    }
    int get_kth_max() {
        return q_.size() == k_ ? q_.top() : -1;
    }

private:
    int k_;
    std::priority_queue<int, std::vector<int>, std::greater<int>> q_;
    std::vector<int> get_all() {
        std::vector<int> result(q_.size());
        while (q_.size()) {
            result[q_.size() - 1] = q_.top();
            q_.pop();
        }
        return  result;
    }
};


class moving_max
{
private:
    std::vector<int> array;
    std::stack<std::pair<int, k_heap>> stack_in;
    std::stack<std::pair<int, k_heap>> stack_out;

    int left = -1;
    int right = -1;

    int k_;
    void push_to_stack(std::stack<std::pair<int, k_heap>> &stack, int val);

public:
    moving_max(std::vector<int> array, int k);
    ~moving_max();
    void move_left();
    void move_right();
    int get();
};

moving_max::moving_max(std::vector<int> array, int k)
{
    this->k_ = k;
    this->array = array;
};

moving_max::~moving_max()
{
    this->array.clear();
};

void moving_max::push_to_stack(std::stack<std::pair<int, k_heap>> &s, int el) {
    k_heap curr = s.empty() ? k_heap(k_) : s.top().second.clone();
    curr.insert(el);
    s.push(std::pair<int, k_heap>(el, curr));
};

void moving_max::move_right()
{
    right++;

    push_to_stack(stack_in, array[right]);
}

void moving_max::move_left()
{
    left++;

    if (!stack_out.empty()) {
        stack_out.pop();
        return;
    }
    while (!stack_in.empty()) {
        int el = stack_in.top().first;
        push_to_stack(stack_out, el);
        stack_in.pop();
    }
    stack_out.pop();
}

int moving_max::get()
{
    if (stack_in.empty()) {
        return stack_out.top().second.get_kth_max();
    }
    if (stack_out.empty()) {
        return stack_in.top().second.get_kth_max();
    }
    k_heap h1 = stack_out.top().second.clone();
    k_heap h2 = stack_in.top().second.clone();
    h1.insert_all(h2);
    return h1.get_kth_max();
}

int main() {
    moving_max s = moving_max({1, 5, 7, 2, 12, 3, 1, 14}, 2);
    s.move_right();
    s.move_right();
    s.move_right();
    s.move_right();
    s.move_right();
    s.move_right();
    s.move_right();

    s.move_left();
    s.move_left();
    s.move_left();
    s.move_left();
    s.move_left();
    std::cout << s.get();
}
