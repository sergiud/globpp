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

#include <globpp/translate.hpp>

#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(ranges)
{
    boost::regex r1 = globpp::translate("test[1-2]");
    boost::regex r2 = globpp::translate("test[!1-2]");

    BOOST_TEST(regex_match("test1", r1));
    BOOST_TEST(regex_match("test2", r1));
    BOOST_TEST(!regex_match("test3", r1));

    BOOST_TEST(!regex_match("test1", r2));
    BOOST_TEST(!regex_match("test2", r2));
    BOOST_TEST(regex_match("test3", r2));
}

BOOST_AUTO_TEST_CASE(single_character)
{
    boost::regex r1 = globpp::translate("foo?bar");

    BOOST_TEST(regex_match("foo!bar", r1));
    BOOST_TEST(!regex_match("foobar", r1));
}

BOOST_AUTO_TEST_CASE(any_character)
{
    boost::regex r1 = globpp::translate("foo*bar");

    BOOST_TEST(regex_match("foo!bar", r1));
    BOOST_TEST(regex_match("foo123bar", r1));
    BOOST_TEST(regex_match("foobar", r1));
}
