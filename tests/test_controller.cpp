#include <iostream>
#include "asset_tests.cpp"
#include <gtest/gtest.h>
#include "../src/systems/map_manager.hpp"


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

/*
Tests for functions that act on maps
*/ 
// Make sure the correct number of objects are found
TEST(MapFunctions, FindObjTest){
    InitWindow(1,1,"Tests");
    TmxMap* map = LoadTMX("tiled/stage1.tmx");
    TmxObjectGroup entities;
    std::vector<TmxObject> EnemyObjs;
    int EnemiesFound = 0;
    if (!map) {
        EnemiesFound = -1;
    }
    else{
        TmxObjectGroup entities = FindLayerByName(map->layers, map->layersLength, "Entities")->exact.objectGroup;
        EXPECT_EQ(entities.objectsLength, 3);
        std::vector<TmxObject> EnemyObjs = FindObjectsByType(entities.objects, entities.objectsLength, "Enemy");
        EnemiesFound = EnemyObjs.size();
    }
    EXPECT_EQ(EnemiesFound, 2);
    CloseWindow();
}

TEST(MapFunctions, GetObjectPropertiesTest){
    InitWindow(1,1,"Tests");
    TmxMap* map = LoadTMX("tiled/stage1.tmx");
    TmxObjectGroup entities;
    std::vector<TmxObject> EnemyObjs;
    std::map<std::string, float> props;
    int MapFound = 0;
    if (!map) {
       MapFound = -1;
    }
    else{
        TmxObjectGroup entities = FindLayerByName(map->layers, map->layersLength, "Entities")->exact.objectGroup;
        std::vector<TmxObject> EnemyObjs = FindObjectsByType(entities.objects, entities.objectsLength, "Enemy");
        props = GetObjectProperties(EnemyObjs[0]);
    }

    EXPECT_EQ(props.size(), 3);
    EXPECT_EQ(props["DMG"], 1.0);

    CloseWindow();
}