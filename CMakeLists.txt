cmake_minimum_required (VERSION 3.0)
project (globpp
  DESCRIPTION "Globbing patterns in C++"
  VERSION 0.1
  LANGUAGES CXX
)

include (CPack)
include (CTest)
include (GNUInstallDirs)

find_package (Boost 1.55 REQUIRED filesystem regex system unit_test_framework)

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

target_compile_features (globpp PUBLIC
  cxx_constexpr
  cxx_noexcept
  cxx_uniform_initialization
)

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

install (TARGETS globpp
  EXPORT globpp-targets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT Runtime
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install (EXPORT globpp-targets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/globpp/cmake
  COMPONENT Development)

install (DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/globpp
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  COMPONENT Development
)

export (TARGETS globpp FILE globpp-targets.cmake)
export (PACKAGE globpp)

if (BUILD_TESTING)
  add_executable (test_translate
    tests/test_translate.cpp
  )
  target_link_libraries (test_translate PRIVATE globpp::globpp
    Boost::unit_test_framework)

  add_test (NAME glob_ranges COMMAND test_translate -t ranges)
  add_test (NAME glob_any_character COMMAND test_translate -t any_character)
  add_test (NAME glob_single_character COMMAND test_translate -t
    single_character)
endif (BUILD_TESTING)
