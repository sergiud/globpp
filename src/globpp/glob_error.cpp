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

#include <globpp/glob_error.hpp>
#include <globpp/glob_error.hpp>

namespace globpp {

glob_error::glob_error(const std::string& message)
    : invalid_argument(message)
{
}

glob_error::~glob_error() noexcept = default;

} // namespace globpp
