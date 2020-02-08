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

#include <iostream>
#include <string>
#include <vector>

#include <boost/utility/string_ref.hpp>

#include <globpp/directory_iterator.hpp>

int main(int argc, char** argv)
{
    std::vector<std::string> patterns;

    if (argc < 2)
        patterns.assign(1, "*");
    else
        patterns.assign(argv + 1, argv + argc);

    for (std::vector<std::string>::iterator it = patterns.begin();
         it != patterns.end(); ++it) {
        globpp::directory_iterator it_glob(".", *it);
        globpp::directory_iterator end;

        for (; it_glob != end; ++it_glob) {
            // output the path without quotes
            std::cout << it_glob->path().string() << std::endl;
        }
    }
}
