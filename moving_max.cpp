#include <iostream>
#include <vector>
#include <stack>

class moving_max
{
private:
    std::vector<int> array;
    std::stack<std::pair<int, int>> stack_in;
    std::stack<std::pair<int, int>> stack_out;

    int left = -1;
    int right = -1;

    void push_to_stack(std::stack<std::pair<int, int>> &stack, int val);

public:
    moving_max(std::vector<int> array);
    ~moving_max();
    void move_left();
    void move_right();
    int get();
};

moving_max::moving_max(std::vector<int> array)
{
    this->array = array;
};

moving_max::~moving_max()
{
    this->array.clear();
};

void moving_max::push_to_stack(std::stack<std::pair<int, int>> &s, int el) {
    int prev = s.empty() ? el : s.top().second;
    int curr = std::max(el, prev);
    s.push(std::pair<int, int>(el, curr));
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
        return stack_out.top().second;
    }
    if (stack_out.empty()) {
        return stack_in.top().second;
    }
    return std::max(stack_in.top().second, stack_out.top().second);
}

int main() {
    moving_max s = moving_max({1, 5, 7, 2, 12, 3, 1, 14});
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
