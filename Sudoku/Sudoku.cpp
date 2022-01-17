// Sudoku.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <set>

int map[9][9] = { 
    {0,9,0,0,2,0,6,0,0},
    {0,5,6,0,0,0,0,0,0},
    {0,8,0,7,0,1,0,0,2},
    {7,0,0,3,0,0,8,0,0},
    {0,0,8,6,0,7,4,0,0},
    {0,0,2,0,0,9,0,0,1},
    {8,0,0,2,0,6,0,5,0},
    {0,0,0,0,0,0,2,8,0},
    {0,0,1,0,5,0,0,4,0} 
};

enum class Result
{
    legal,
    ilegal,
    complete
};

Result rowLegal(int y) {
    std::set<int> bucket;
    for (int x = 0; x < 9; x++) {
        int value = map[y][x];
        if (value == 0) {
            continue;
        }
        if (bucket.find(value) != bucket.end()) {
            return Result::ilegal;
        }
        bucket.insert(value);
    }
    return (bucket.size()== 9)?Result::complete : Result::legal;
}

Result colLegal(int x) {
    std::set<int> bucket;
    for (int y = 0; y < 9; y++) {
        int value = map[y][x];
        if (value == 0) {
            continue;
        }
        if (bucket.find(value) != bucket.end()) {
            return Result::ilegal;
        }
        bucket.insert(value);
    }
    return (bucket.size() == 9) ? Result::complete : Result::legal;
}

Result gridLegal(int pX, int pY) {
    std::set<int> bucket;
    int xModVal = pX % 3;
    int yModVal = pY % 3;
    for (int y = pY - yModVal; y < (pY + 3 - yModVal); y++) {
        for (int x = pX - xModVal; x < (pX + 3 - xModVal); x++) {
            int value = map[y][x];
            if (value == 0) {
                continue;
            }
            if (bucket.find(value) != bucket.end()) {
                return Result::ilegal;
            }
            bucket.insert(value);
        }
    }
    return (bucket.size() == 9) ? Result::complete : Result::legal;
}

Result checkAll() {
    Result t_result = Result::complete;
    Result temp;
    for (int x = 0; x < 9; x++) {
        if ((temp = colLegal(x)) == Result::ilegal) {
            return Result::ilegal;
        }
        if (temp != Result::complete) {
            t_result = Result::legal;
        }
        if ((temp = rowLegal(x)) == Result::ilegal) {
            return Result::ilegal;
        }
        if (temp != Result::complete) {
            t_result = Result::legal;
        }
    }
    for (int y = 0; y < 9; y += 3) {
        for (int x = 0; x < 9; x += 3) {
            if ((temp = gridLegal(x, y)) == Result::ilegal) {
                return Result::ilegal;
            }
            if (temp != Result::complete) {
                t_result = Result::legal;
            }
        }
    }
    return t_result;
}

Result checkAllFor(int x, int y) {
    Result t_result = Result::complete;
    t_result = rowLegal(y);
    if (t_result == Result::ilegal) {
        return t_result;
    }
    t_result = colLegal(x);
    if (t_result == Result::ilegal) {
        return t_result;
    }
    t_result = gridLegal(x, y);
    if (t_result == Result::ilegal) {
        return t_result;
    }
    return t_result;
}

Result tryNext(int distance) {
    int x = distance % 9;
    int y = (int)(distance / 9);
    if (y >= 9) {
        return Result::complete;
    }
    int value = map[y][x];
    if (value == 0) {
        for (int i = 1; i <= 9; ++i) {
            map[y][x] = i;
            Result t_result = checkAllFor(x, y);
            if (t_result != Result::ilegal) {
                t_result = tryNext(distance + 1);
                if (t_result == Result::complete) {
                    return t_result;
                }
            }
        }
        map[y][x] = 0;
        return Result::ilegal;
    }
    else {
        return tryNext(distance + 1);
    }

}

void printMap() {
    for (int y = 0; y < 9; y ++) {
        for (int x = 0; x < 9; x ++) {
            std::cout << map[y][x];
        }
        std::cout << std::endl;
    }
}

int main()
{
    printMap();
    for (int i = 0; i < (9 * 9); ++i) {
        Result t_result = tryNext(i);
        if (t_result == Result::complete) {
            std::cout << std::endl << "Success" << std::endl;
            printMap();
            break;
        }
        else if ((t_result == Result::ilegal)) {
            std::cout << std::endl << "Fail" << std::endl;
            break;
        }
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
