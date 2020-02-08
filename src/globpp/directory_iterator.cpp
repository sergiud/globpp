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

#include <globpp/directory_iterator.hpp>
#include <globpp/translate.hpp>

namespace globpp {

directory_iterator::directory_iterator()
{
}

directory_iterator::directory_iterator(const boost::filesystem::path& directory,
                                       const boost::string_ref& expression)
    : it_(directory)
    , expr_(translate(expression))
{
    // Look for the first match as the increment method will not be called
    // before the iterator is dereferenced for the first time.
    while (it_ != end_ && !regex_match(it_->path().leaf().string(), expr_))
        ++it_;
}

void directory_iterator::increment()
{
    // Immediately increment the iterator and after that look for a match.
    // This is slightly different from the loop in the constructor, which
    // increments the iterator after matching.
    while (++it_ != end_ && !regex_match(it_->path().leaf().string(), expr_))
        continue;
}

boost::filesystem::directory_entry& directory_iterator::dereference() const
{
    return *it_;
}

bool directory_iterator::equal(const directory_iterator& other) const
{
    return it_ == other.it_;
}

} // namespace globpp
