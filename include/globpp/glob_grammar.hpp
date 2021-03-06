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

#ifndef GLOBPP_GLOB_GRAMMAR_HPP
#define GLOBPP_GLOB_GRAMMAR_HPP

#include <iterator>
#include <string>

#include <boost/spirit/home/qi.hpp>

namespace globpp {

//! @cond private_details

namespace detail {

template<class Ch>
struct escaped_symbols;

template<>
struct escaped_symbols<char>
{
    static boost::spirit::qi::symbols<char, const char* const> normal()
    {
        boost::spirit::qi::symbols<char, const char* const> symbols;

        symbols.add
            ("?", ".")
            ("*", ".*")
            (".", "\\.")
            ("{", "\\{")
            ("}", "\\}")
            ("(", "\\(")
            (")", "\\)")
            ("\\", "\\\\")
            ("+", "\\+")
            ("|", "\\|")
            ("^", "\\^")
            ("$", "\\$")
            // allow escaped characters
            ("\\[", "\\[")
            ("\\]", "\\]")
            ("\\*", "\\*")
            ("\\?", "\\?")
            ;

        return symbols;
    }

    static boost::spirit::qi::symbols<char, char> negate()
    {
        boost::spirit::qi::symbols<char, char> symbols;

        symbols.add
            ("!", '^')
            ;

        return symbols;
    }

    static constexpr const char* special() noexcept
    {
        return "![]";
    }

    static constexpr char group_start() noexcept
    {
        return '[';
    }

    static constexpr char group_end() noexcept
    {
        return ']';
    }
};

} // namespace detail

//! @endcond

template
<
    class Iterator,
    class Tr = std::char_traits<typename std::iterator_traits<Iterator>::value_type>,
    class Al = std::allocator<typename std::iterator_traits<Iterator>::value_type>
>
class glob_grammar
    : public boost::spirit::qi::grammar<Iterator, std::basic_string<typename std::iterator_traits<Iterator>::value_type, Tr, Al>()>
{
public:
    using char_type = typename std::iterator_traits<Iterator>::value_type;
    using string_type =
        std::basic_string<typename std::iterator_traits<Iterator>::value_type,
                          Tr, Al>;

    glob_grammar()
        : glob_grammar::base_type(start_, "globpp")
    {
        escaped_ = detail::escaped_symbols<char_type>::normal();
        negate_ = detail::escaped_symbols<char_type>::negate();

        namespace qi = boost::spirit::qi;

        chars_ =
            +((escaped_ | qi::char_) - detail::escaped_symbols<char_type>::group_start())
            ;

        group_start_char_ =
             negate_ | qi::char_
             ;

        group_chars_ =
            +((escaped_ | qi::char_) - detail::escaped_symbols<char_type>::group_end())
            ;

        group_ =
               qi::char_(detail::escaped_symbols<char_type>::group_start())
            >> group_start_char_ >> group_chars_
            >> qi::char_(detail::escaped_symbols<char_type>::group_end())
            ;

        start_ =
            *(
                  chars_
                | group_
            )
            >>
            qi::eoi
            ;
    }

private:
    boost::spirit::qi::rule<Iterator, string_type()> start_;
    boost::spirit::qi::symbols<char_type, const char_type* const> escaped_;
    boost::spirit::qi::symbols<char_type, char> negate_;
    boost::spirit::qi::rule<Iterator, string_type()> group_;
    boost::spirit::qi::rule<Iterator, string_type()> chars_;
    boost::spirit::qi::rule<Iterator, string_type()> group_chars_;
    boost::spirit::qi::rule<Iterator, string_type()> group_start_char_;
};

} // namespace globpp

#endif // GLOBPP_GLOB_GRAMMAR_HPP
