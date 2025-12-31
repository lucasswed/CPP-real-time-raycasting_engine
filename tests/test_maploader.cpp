#include <gtest/gtest.h>
#include "world/MapLoader.h"
#include <fstream>
#include <filesystem>

// Test fixture for MapLoader
class MapLoaderTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Create test directory
        test_dir = "test_maps";
        std::filesystem::create_directory(test_dir);
    }

    void TearDown() override
    {
        // Clean up test files
        std::filesystem::remove_all(test_dir);
    }

    // Helper to create a test map file
    void createTestMap(const std::string &filename, const std::vector<std::string> &lines)
    {
        std::ofstream file(test_dir + "/" + filename);
        for (const auto &line : lines)
        {
            file << line << "\n";
        }
        file.close();
    }

    std::string test_dir;
};

// Test loading a valid map file
TEST_F(MapLoaderTest, LoadValidMapFile)
{
    createTestMap("valid.cub", {"11111",
                                "10001",
                                "10N01",
                                "10001",
                                "11111"});

    MapLoader loader;
    EXPECT_TRUE(loader.loadMapFromFile(test_dir + "/valid.cub"));

    const auto &map = loader.getMapMatrix();
    EXPECT_EQ(map.size(), 5);
    EXPECT_EQ(map[0], "11111");
}

// Test loading non-existent file
TEST_F(MapLoaderTest, LoadNonExistentFile)
{
    MapLoader loader;
    EXPECT_FALSE(loader.loadMapFromFile("nonexistent.cub"));
}

// Test empty map
TEST_F(MapLoaderTest, LoadEmptyFile)
{
    createTestMap("empty.cub", {});

    MapLoader loader;
    EXPECT_TRUE(loader.loadMapFromFile(test_dir + "/empty.cub"));
    EXPECT_EQ(loader.getMapMatrix().size(), 0);
}

// Test map matrix getter
TEST_F(MapLoaderTest, GetMapMatrix)
{
    createTestMap("test.cub", {"111",
                               "1N1",
                               "111"});

    MapLoader loader;
    loader.loadMapFromFile(test_dir + "/test.cub");

    const auto &map = loader.getMapMatrix();
    EXPECT_EQ(map.size(), 3);
    EXPECT_EQ(map[1][1], 'N');
}

// Main function for running tests
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
