//
// globpp - Globbing patterns in C++
//
// Copyright 2016 Sergiu Deitsch <sergiu.deitsch@gmail.com>
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

#include <cmath>
#include <cstddef>
#include <iterator>
#include <string>

#include <boost/regex.hpp>
#include <boost/spirit/home/qi/parse.hpp>
#include <boost/throw_exception.hpp>
#include <boost/utility/string_ref.hpp>

#include <globpp/glob_error.hpp>
#include <globpp/glob_grammar.hpp>

namespace globpp {

template<class Iterator, class Tr>
inline void translate(Iterator first, Iterator last, boost::basic_regex<typename std::iterator_traits<Iterator>::value_type, Tr>& r)
{
    typedef typename std::iterator_traits<Iterator>::value_type Ch;
    glob_grammar<Iterator> g;

    std::basic_string<Ch> out;
    out.reserve(static_cast<std::size_t>(std::ceil(static_cast<double>(std::distance(first, last)) * 1.5)));

    Iterator savedFirst = first;
    bool succeeded = boost::spirit::qi::parse(first, last, g, out);

    if (!succeeded) {
        std::string message(savedFirst, last);
        BOOST_THROW_EXCEPTION(glob_error("'" + message + "' is not a valid globbing expression"));
    }

    r = boost::basic_regex<Ch, Tr>(out);
}

template<class Ch, class Tr>
inline boost::basic_regex<Ch> translate(const boost::basic_string_ref<Ch, Tr>& expression)
{
    boost::basic_regex<Ch> r;
    translate(expression.begin(), expression.end(), r);

    return r;
}

} // namespace globpp
