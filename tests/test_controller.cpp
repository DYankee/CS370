#include <iostream>
#include "asset_tests.cpp"
#include <gtest/gtest.h>


class AssetDataFixture : public ::testing::Test {
    protected:
        static Assets assets;

        static void SetUpTestSuite(){
            assets = GetAssets("./");
            InitWindow(1,1,"Tests");
        }

        static void TearDownTestSuite(){
            CloseWindow();
        }
};

Assets AssetDataFixture::assets;

TEST_F(AssetDataFixture, TextureLoading){
    EXPECT_TRUE(LoadTextureTest(assets.pngs));
}

//TEST_F(AssetDataFixture, MapLoading){
//    EXPECT_TRUE(LoadMapTest(assets.maps));
//}