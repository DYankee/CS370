#include <iostream>
#include "asset_tests.cpp"
#include <gtest/gtest.h>


TEST(AssetTests, TextureLoading){
    InitWindow(1,1, "Tests");
    Assets assets = GetAssets("./");
    std::cout << assets.pngs[0];

    EXPECT_TRUE(LoadTextureTest(assets.pngs));
    CloseWindow();
}