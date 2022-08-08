// Glaze Library
// For the license information refer to glaze.hpp

#include <chrono>
#include <iostream>
#include <random>
#include <any>

#include "boost/ut.hpp"
#include "glaze/json/json_ptr.hpp"
#include "glaze/json/overwrite.hpp"
#include "glaze/json/read.hpp"
#include "glaze/json/write.hpp"
#include "glaze/json/eigen.hpp"

#include <Eigen/Core>
#include <iterator>

int main()
{
  using namespace boost::ut;
  "write"_test = [] {
     Eigen::Matrix<double, 2, 2> m{};
     m << 5, 1, 1, 7;
     std::string json{};
     glaze::write_json(m, json);
     expect(json == "[5,1,1,7] ");  
  };

  "read"_test = [] {
     Eigen::Matrix<double, 2 , 2> m{};
     glaze::read_json(m, "[2,1,7,4]");
     expect(m.rows() == 2);
     expect(m.cols() == 2);
     expect(m(0,1) == 7);
     expect(m(1,1) == 4);
  };
}
