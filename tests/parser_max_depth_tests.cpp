#include "simdjson.h"
#include "test_macros.h"

#include <cstdlib>
#include <limits>

static constexpr size_t max_size_t_depth = (std::numeric_limits<size_t>::max)();
static constexpr size_t invalid_max_depth_values[] = {
  max_size_t_depth,
  max_size_t_depth / 2,
  max_size_t_depth / 8,
  max_size_t_depth / 16
};

static bool dom_parser_depth_overflow_is_capacity() {
  TEST_START();
  simdjson::dom::parser parser(simdjson::SIMDJSON_MAXSIZE_BYTES);
  for (size_t depth : invalid_max_depth_values) {
    ASSERT_ERROR(parser.allocate(simdjson::dom::MINIMAL_DOCUMENT_CAPACITY, depth), simdjson::CAPACITY);
  }
  TEST_SUCCEED();
}

static bool ondemand_parser_depth_overflow_is_capacity() {
  TEST_START();
  simdjson::ondemand::parser parser(simdjson::SIMDJSON_MAXSIZE_BYTES);
  for (size_t depth : invalid_max_depth_values) {
    ASSERT_ERROR(parser.allocate(simdjson::dom::MINIMAL_DOCUMENT_CAPACITY, depth), simdjson::CAPACITY);
  }
  TEST_SUCCEED();
}

int main() {
  RUN_TEST(dom_parser_depth_overflow_is_capacity());
  RUN_TEST(ondemand_parser_depth_overflow_is_capacity());

  std::cout << "All tests passed!" << std::endl;
  return EXIT_SUCCESS;
}
