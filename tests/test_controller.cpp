#include <iostream>
#include "assets.cpp"



int main(){
    int result = 0;
    std::cout << "Running test assets" << std::endl;
    result = LoadTextureTest("sprites");

    return result;
}