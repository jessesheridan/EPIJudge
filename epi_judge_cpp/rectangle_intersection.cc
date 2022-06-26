#include <tuple>

#include "test_framework/fmt_print.h"
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
struct Rect {
  int x, y, width, height;
};

Rect IntersectRectangle(const Rect& r1, const Rect& r2) {
  int x = 0;
  int y = 0;
  int width = -1;
  int height = -1;

  if ((r2.x >= r1.x) && (r2.x <= r1.x + r1.width)) {
    x = r2.x;
    width = std::min(r1.width - (r2.x - r1.x), r2.width);
  }
  if ((r1.x >= r2.x) && (r1.x <= r2.x + r2.width)) {
    x = r1.x;
    width = std::min(r2.width - (r1.x - r2.x), r1.width);
  }

  if ((r2.y >= r1.y) && (r2.y <= r1.y + r1.height)) {
    y = r2.y;
    height = std::min(r1.height - (r2.y - r1.y), r2.height);
  }
  if ((r1.y >= r2.y) && (r1.y <= r2.y + r2.height)) {
    y = r1.y;
    height = std::min(r2.height - (r1.y - r2.y), r1.height);
  }

  if (height != -1 && width != -1) {
    return {x, y, width, height};
  }

  return {0, 0, -1, -1};


}
bool operator==(const Rect& r1, const Rect& r2) {
  return std::tie(r1.x, r1.y, r1.width, r1.height) ==
         std::tie(r2.x, r2.y, r2.width, r2.height);
}

namespace test_framework {
template <>
struct SerializationTrait<Rect> : UserSerTrait<Rect, int, int, int, int> {
  static std::vector<std::string> GetMetricNames(const std::string& arg_name) {
    return {FmtStr("height({})", arg_name), FmtStr("width({})", arg_name)};
  }

  static std::vector<int> GetMetrics(const Rect& x) {
    return {x.height, x.width};
  }
};
}  // namespace test_framework

std::ostream& operator<<(std::ostream& out, const Rect& r) {
  return PrintTo(out, std::make_tuple(r.x, r.y, r.width, r.height));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"r1", "r2"};
  return GenericTestMain(args, "rectangle_intersection.cc",
                         "rectangle_intersection.tsv", &IntersectRectangle,
                         DefaultComparator{}, param_names);
}
