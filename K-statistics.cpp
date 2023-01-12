#include <iostream>
#include <vector>

unsigned int quick_select(std::vector<unsigned int> &coordinates, unsigned int aver_index) {

    if (coordinates.size() == 1) {
        return coordinates[0];
    }
    int aver_ind = std::rand() % coordinates.size();
    unsigned int average = coordinates[aver_ind];
    std::vector<unsigned int> lefts;
    std::vector<unsigned int> rights;
    for (unsigned int coordinate: coordinates) {
        if (coordinate < average) {
            lefts.push_back(coordinate);
        } else {
            if (coordinate > average) {
                rights.push_back(coordinate);
            }
        }
    }
    if (aver_index <= rights.size()) {
        return quick_select(rights, aver_index);
    } else {
        if (aver_index <= coordinates.size() - lefts.size()) {
            return average;
        } else {
            return quick_select(lefts, aver_index + lefts.size() - coordinates.size());
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int num_of_num;
    int num_of_com;
    int k_num;
    std::cin >> num_of_num;
    std::cin >> num_of_com;
    std::cin >> k_num;
    std::vector<unsigned int> numbers;
    for (int i = 0; i < num_of_num; ++i) {
        unsigned int number;
        std::cin >> number;
        numbers.push_back(number);
    }
    int right = 0;
    int left = 0;
    unsigned int k_stat = 0;
    std::vector<unsigned int> segment;
    segment.push_back(numbers[0]);
    bool flag = true;
    for (int ind = 0; ind < num_of_com; ++ind) {
        char direction;
        std::cin >> direction;
        if (direction == 'R') {
            ++right;
            segment.push_back(numbers[right]);
        } else {
            ++left;
            segment.erase(segment.begin());
        }

        if (right - left + 1 < k_num) {
            std::cout << -1 << ' ';
            flag = true;
        } else {
            if (k_stat > numbers[right] or flag) {
                k_stat = quick_select(segment, segment.size() - k_num + 1);
            }
            std::cout << k_stat << ' ';
        }
    }
    return 0;
}
