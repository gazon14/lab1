#include "gtest/gtest.h"
#include "SameGameBoard.h"

class SameGameBoardTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Optional: Any setup code before each test
    }

    void TearDown() override {
        // Optional: Any cleanup code after each test
    }

    // You can add utility functions for common test actions
    // ...

    CSameGameBoard board;
};

TEST_F(SameGameBoardTest, Initialization) {
    // Test the initial state after construction
    ASSERT_EQ(board.GetColumns(), 15);
    ASSERT_EQ(board.GetRows(), 15);
    ASSERT_EQ(board.GetHeight(), 35);
    ASSERT_EQ(board.GetWidth(), 35);
    ASSERT_EQ(board.GetRemainingCount(), 15 * 15);
    ASSERT_EQ(board.GetNumColors(), 3);
    // Add more assertions based on your specific initialization
}

TEST_F(SameGameBoardTest, SetupBoard) {
    // Test the SetupBoard function
    board.SetupBoard();
    ASSERT_GT(board.GetRemainingCount(), 0);
    // Assuming SetupBoard sets up a non-empty board
}

TEST_F(SameGameBoardTest, DeleteBlocks) {
    // Test the DeleteBlocks function
    board.SetupBoard();
    int initialRemaining = board.GetRemainingCount();

    // Assuming a valid row and column
    int deletedCount = board.DeleteBlocks(0, 0);

    ASSERT_GT(initialRemaining, board.GetRemainingCount());
    ASSERT_GT(deletedCount, 0);
    // Assuming DeleteBlocks removes at least one block
}

TEST_F(SameGameBoardTest, IsGameOver) {
    // Test the IsGameOver function
    // Assuming the board is set up in a way that the game is not over initially
    ASSERT_FALSE(board.IsGameOver());

    // Modify the board to make the game over
    // Set up a specific scenario where there are no more valid moves
    board.DeleteBlocks(0, 0);
    board.DeleteBlocks(1, 0);
    // ... (continue deleting blocks)

    ASSERT_TRUE(board.IsGameOver());
    // Assuming IsGameOver correctly identifies when the game is over
}

// Add more test cases as needed for other methods and scenarios
