//
// globpp - Globbing patterns in C++
//
// Copyright (C) 2020 Sergiu Deitsch <sergiu.deitsch@gmail.com>
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

#ifndef GLOBPP_TRANSLATE_HPP
#define GLOBPP_TRANSLATE_HPP

#include <cmath>
#include <cstddef>
#include <iterator>
#include <regex>
#include <string>

#include <boost/spirit/home/qi/parse.hpp>
#include <boost/throw_exception.hpp>
#include <boost/utility/string_view.hpp>

#include <globpp/glob_error.hpp>
#include <globpp/glob_grammar.hpp>

namespace globpp {

// clang-format off
template
<
      class Iterator
    , class Regex
>
// clang-format off
inline void translate( Iterator first, Iterator last, Regex& r)
{
    typedef typename std::iterator_traits<Iterator>::value_type Ch;
    glob_grammar<Iterator> g;

    std::basic_string<Ch> out;
    out.reserve(static_cast<std::size_t>(
        std::ceil(static_cast<double>(std::distance(first, last)) * 1.5)));

    Iterator savedFirst = first;
    bool succeeded = boost::spirit::qi::parse(first, last, g, out);

    if (!succeeded) {
        std::string message{savedFirst, last};
        BOOST_THROW_EXCEPTION(
            glob_error{"'" + message + "' is not a valid globbing expression"});
    }

    r = Regex{'^' + out + '$'};
}

template
<
      class Regex = std::regex
    , class Ch
>
inline Regex translate(
    const boost::basic_string_view<Ch>& expression)
{
    Regex r;
    translate(expression.begin(), expression.end(), r);

    return r;
}

template
<
   class Regex = std::regex
>
inline Regex translate(const typename Regex::value_type* expression)
{
    return translate<Regex>(boost::basic_string_view<typename Regex::value_type>{expression});
}

} // namespace globpp

#endif // GLOBPP_TRANSLATE_HPP
