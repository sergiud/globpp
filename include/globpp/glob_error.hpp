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

#ifndef GLOBPP_GLOB_ERROR_HPP
#define GLOBPP_GLOB_ERROR_HPP

#include <stdexcept>
#include <string>

#include <boost/config.hpp>

namespace globpp {

class glob_error
    : public std::invalid_argument
{
public:
    explicit glob_error(const std::string& message = "");
    ~glob_error() noexcept override;
};

} // namespace globpp

#endif // GLOBPP_GLOB_ERROR_HPP
