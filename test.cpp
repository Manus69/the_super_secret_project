#include <vector>
#include <iostream>
#include <string>

#include <fstream>
#include <string>
#include <algorithm>

template <typename T>
void print_vector(const std::vector<T> &vector)
{
    int n;
    int count;

    n = 0;
    count = vector.size();
    while (n < count)
    {
        std::cout << vector[n];
        std::cout << " ";
        n ++;
    }
}

int main() 
{

    clock_t start;
    clock_t end;

    start = clock();


    std::vector<std::string> vector;
    std::ifstream file("text_file.txt");
    std::string str;

    while (std::getline(file, str))
    {
        vector.push_back(str);
    }

    // std::printf("number of lines: %lu;\n", vector.size());

    std::sort(vector.begin(), vector.end());

    // print_vector(vector);

    std::cout << vector[vector.size() - 1];


    // std::vector<const char *> vector;
    // std::ifstream file("text_file.txt");
    // std::string str;

    // while (std::getline(file, str))
    // {
    //     // std::printf("%s ", str.c_str());
    //     vector.push_back(str.c_str());
    // }

    // print_vector(vector);

    // std::sort(vector.begin(), vector.end());

    // std::cout << vector[vector.size() - 2];
    // std::printf("%s ", vector[vector.size() - 2]);




    // std::vector<int> numbers;
    // int n;

    
    // n = 1 << 20;
    // while (n)
    // {
    //     numbers.push_back(n);
    //     n --;
    // }
    // std::sort(numbers.begin(), numbers.end());
    // std::cout << numbers[numbers.size() - 1];
    

    // double x;
    // std::vector<double> vector;

    // x = 1000000 + 3.14159;
    // while (x > 0)
    // {
    //     vector.push_back(x);
    //     x --;
    // }
    // std::cout << vector[vector.size() - 1];


    end = clock();

    printf("\ntime elapsed: %f\n", ((double)(end - start)) / CLOCKS_PER_SEC);

    return 0;
}