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

#ifndef GLOBPP_IS_GLOB_HPP
#define GLOBPP_IS_GLOB_HPP

#include <string>

#include <boost/spirit/home/qi/parse.hpp>

#include <globpp/glob_grammar.hpp>

namespace globpp {

template<class Iterator>
bool is_glob(Iterator first, Iterator last)
{
    glob_grammar<Iterator> g;
    return boost::spirit::qi::parse(first, last, g);
}

template<class Ch, class Tr, class Al>
bool is_glob(const std::basic_string<Ch, Tr, Al>& expression)
{
    return is_glob(expression.begin(), expression.end());
}

} // namespace globpp

#endif // GLOBPP_IS_GLOB_HPP
