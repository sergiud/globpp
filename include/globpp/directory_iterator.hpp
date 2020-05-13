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

#ifndef GLOBPP_DIRECTORY_ITERATOR_HPP
#define GLOBPP_DIRECTORY_ITERATOR_HPP

#include <regex>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/utility/string_view.hpp>

#include <globpp/translate.hpp>

namespace globpp {

// clang-format off
template
<
    class Regex
>
class basic_directory_iterator
    : public boost::iterator_facade
    <
        basic_directory_iterator<Regex>,
        boost::filesystem::directory_entry,
        boost::single_pass_traversal_tag
    >
// clang-format on
{
public:
    basic_directory_iterator() = default;

    explicit basic_directory_iterator(const boost::filesystem::path& directory,
                                      boost::string_view expression)
        : it_(directory)
        , expr_(translate<Regex>(expression))
    {
        // Look for the first match as the increment method will not be called
        // before the iterator is dereferenced for the first time.
        while (it_ != end_ &&
               !regex_match(it_->path().leaf().string(), expr_)) {
            ++it_;
        }
    }

private:
    friend class boost::iterator_core_access;

    void increment()
    {
        // Immediately increment the iterator and after that look for a match.
        // This is slightly different from the loop in the constructor, which
        // increments the iterator after matching.
        while (++it_ != end_ &&
               !regex_match(it_->path().leaf().string(), expr_)) {
            // nothing to do; just continue
        }
    }

    boost::filesystem::directory_entry& dereference() const
    {
        return *it_;
    }

    bool equal(const basic_directory_iterator& other) const
    {
        return it_ == other.it_;
    }

    boost::filesystem::directory_iterator it_;
    boost::filesystem::directory_iterator end_;
    Regex expr_;
};

using directory_iterator = basic_directory_iterator<std::regex>;

} // namespace globpp

#endif // GLOBPP_DIRECTORY_ITERATOR_HPP
