//
// globpp - Globbing patterns in C++
//
// Copyright 2020 Sergiu Deitsch <sergiu.deitsch@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#define BOOST_TEST_MODULE globpp

#include <algorithm>

#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/scope_exit.hpp>
#include <boost/test/included/unit_test.hpp>

#include <globpp/directory_iterator.hpp>

namespace {

void touch(const boost::filesystem::path& p)
{
    boost::filesystem::ofstream{p, std::ios_base::trunc};
}

} // namespace

BOOST_AUTO_TEST_CASE(ranges)
{
    boost::filesystem::path dir = boost::filesystem::temp_directory_path() /
                                  boost::filesystem::unique_path();

    BOOST_TEST_REQUIRE(boost::filesystem::create_directories(dir));

    BOOST_SCOPE_EXIT((dir))
    {
        boost::filesystem::remove_all(dir);
    }
    BOOST_SCOPE_EXIT_END

    touch(dir / "test1");
    touch(dir / "test2");
    touch(dir / "test3");

    globpp::directory_iterator it{dir, "test[1-2]"};
    globpp::directory_iterator end;

    std::vector<boost::filesystem::path> fnames;
    std::transform(
        it, end, std::back_inserter(fnames),
        [](const boost::filesystem::path& p) { return p.filename(); });

    BOOST_TEST(
        (std::find(fnames.begin(), fnames.end(), "test1") != fnames.end()));
    BOOST_TEST(
        (std::find(fnames.begin(), fnames.end(), "test2") != fnames.end()));
    BOOST_TEST(
        (std::find(fnames.begin(), fnames.end(), "test3") == fnames.end()));
}
