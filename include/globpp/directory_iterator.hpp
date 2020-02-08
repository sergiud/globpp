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

#include <boost/regex.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/utility/string_ref.hpp>

namespace globpp {

class directory_iterator
    : public boost::iterator_facade
    <
        directory_iterator,
        boost::filesystem::directory_entry,
        boost::single_pass_traversal_tag
    >
{
public:
    directory_iterator();
    explicit directory_iterator(const boost::filesystem::path& directory,
            const boost::string_ref& expression);

private:
    friend class boost::iterator_core_access;

    void increment();
    boost::filesystem::directory_entry& dereference() const;
    bool equal(const directory_iterator& other) const;

    boost::filesystem::directory_iterator it_;
    boost::filesystem::directory_iterator end_;
    boost::regex expr_;
};

} // namespace globpp
