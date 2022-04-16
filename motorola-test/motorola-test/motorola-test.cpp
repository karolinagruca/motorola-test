// motorola-test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>

struct rect
{
    int a;
    int b;
};

struct fence_build
{
    int area;

    std::vector<rect> best_rects;
};

bool validate_run_cmd(const std::string& cmd)
{
    return cmd == "RUN";
}

void ask_for_run_cmd()
{
    do
    {
        std::string cmd;
        std::cout << "Type in RUN" << std::endl;
        std::cin >> cmd;

        if (validate_run_cmd(cmd))
        {
            std::cout << "Great, let's go:)" << std::endl;
            return;
        }
    } while (true);
}

// check if all the characters in string are a digit
bool validate_fence_length(const std::string& text)
{
    for (int i = 0; i < text.length(); ++i)
    {
        char character = text[i];
        if (!std::isdigit(character))
        {
            return false;
        }
    }

    return true;
}

int get_fence_length()
{
    std::cout << "Give fence length" << std::endl;
    std::string fence_length_text;
    std::cin >> fence_length_text;

    bool is_fence_length_valid = validate_fence_length(fence_length_text);
    while (!is_fence_length_valid)
    {
        std::cout << "Incorrect fence length, try again. Give fence length" << std::endl;
        std::cin >> fence_length_text;

        is_fence_length_valid = validate_fence_length(fence_length_text);
    }

    return std::stoi(fence_length_text);
}

int get_rect_area(int a, int b)
{
    return a * b;
}

fence_build get_best_fence_build(int fence_length)
{
    fence_build best_fence_build;

    if (fence_length < 3)
    {
        return best_fence_build;
    }

    // fence_length = 2a + b
    // so if a = 1, b = fence_length - 2

    int a = 1;
    int b = fence_length - 2;
    while (b > 0)
    {
        int area = get_rect_area(a, b);

        if (area > best_fence_build.area)
        {
            best_fence_build.area = area;
            best_fence_build.best_rects.clear();

            rect new_best_rect;
            new_best_rect.a = a;
            new_best_rect.b = b;
            best_fence_build.best_rects.push_back(new_best_rect);
        }
        else if (area == best_fence_build.area)
        {
            rect another_best_rect;
            another_best_rect.a = a;
            another_best_rect.b = b;
            best_fence_build.best_rects.push_back(another_best_rect);
        }

        b = b - 2;
        a = a + 1;
    }

    return best_fence_build;
}

void print_best_fence_build(const fence_build& best_fence_build, int fence_lenght)
{
    if (fence_lenght < 3)
    {
        std::cout << "Error, no possible combinations, length must be >= 3" << std::endl;
        return;
    }

    std::cout << "Maximum possible area is " << best_fence_build.area << " given fence lenght " << fence_lenght << std::endl;

    std::cout << "Possible rects for the build" << std::endl;

    for (int i = 0; i < best_fence_build.best_rects.size(); ++i)
    {
        rect possible_rect = best_fence_build.best_rects[i];
        std::cout << "a: " << possible_rect.a << ", b: " << possible_rect.b << std::endl;
    }
}

int main()
{
    ask_for_run_cmd();

    int fence_length = get_fence_length();

    fence_build best_fence_build = get_best_fence_build(fence_length);

    print_best_fence_build(best_fence_build, fence_length);
}
