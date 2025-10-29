#include <iostream>
#include "assets.cpp"



int main(){
    // Vars
    int assetTestResult = 0;

    // Init
    InitWindow(1, 1, "Assets test");

    std::cout << "Running asset check test" << std::endl;
    assetTestResult = assetTests();
    std::cout << assetTestResult << std::endl;

    CloseWindow();
    return assetTestResult;
}