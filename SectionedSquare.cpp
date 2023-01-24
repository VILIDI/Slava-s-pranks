#include <vector>
#include <math.h>

using namespace std;

class Square {
public:
    virtual void tryAdd(int x, int y);
    virtual bool isIn(int x, int y);
    virtual int numAbove(int a, int b, int c);
    virtual int getCount();
};


class SmallSquare : Square {

private:
    int highX;
    int highY;
    int lowX;
    int lowY;
    int count = 0;
    vector<pair<int, int>> points;
public:
    SmallSquare(int hX, int hY, int lX, int lY) {
        this->highX = hX;
        this->highY = hY;
        this->lowX = lX;
        this->lowY = lY;
    }
    void tryAdd(int x, int y) override {
        if (isIn(x, y)) {
            count++;
            points.emplace_back(x, y);
        }
    }

    bool isIn(int x, int y) override {
        return (lowX < x & x >= highX) & (lowY < y & y >= highY);
    }

    int getCount() override {
        return count;
    }

    int numAbove(int a, int b, int c) override {
        int count = 0;
        for (auto p : points) {
            (a * p.first + b * p.second + c) ? count++ : count;
        }
        return count;
    }
};

class BigSquare : Square {
private:
    vector<vector<SmallSquare>> squares;
    int lenX;
    int lenY;

public:
    BigSquare(int xMax, int yMax) {
//    TODO: add here
    }

    void tryAdd(int x, int y) {
        for (auto row : squares) {
            for (auto square : row) {
                square.tryAdd(x, y);
            }
        }
    }

    int numAbove(int a, int b, int c) {
        // TODO: put here
        return 0;
    }
};

int main() {

}
