cmake_minimum_required (VERSION 3.0)
project (globpp)

find_package (Boost 1.55 REQUIRED filesystem regex system)

add_library (globpp
  include/globpp/directory_iterator.hpp
  include/globpp/glob.hpp
  include/globpp/glob_error.hpp
  include/globpp/glob_grammar.hpp
  include/globpp/is_glob.hpp
  include/globpp/translate.hpp
  src/globpp/directory_iterator.cpp
  src/globpp/glob_error.cpp
)
add_library (globpp::globpp ALIAS globpp)

target_include_directories (globpp PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries (globpp PUBLIC
  Boost::boost
  Boost::filesystem
  Boost::regex
  Boost::system
)

add_executable (example_glob examples/glob.cpp)

target_link_libraries (example_glob PRIVATE globpp::globpp)
