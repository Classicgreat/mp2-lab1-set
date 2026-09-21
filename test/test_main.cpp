#include "../include/tbitfield.h"
#include <../gtest/gtest.h>

TEST(TBitField, init) { ASSERT_NO_THROW(TBitField tb(10)); }

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
