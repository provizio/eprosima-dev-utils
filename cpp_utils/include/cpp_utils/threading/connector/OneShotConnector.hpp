// Copyright 2022 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @file OwnedTask.hpp
 *
 * This file contains class Task definition.
 */

#pragma once

#include <functional>

#include <cpp_utils/threading/task/ITask.hpp>
#include <cpp_utils/threading/manager/IManager.hpp>

namespace eprosima {
namespace utils {
namespace threading {

template <typename ... Args>
class OneShotConnector
{
public:

    static void execute(IManager* tp, const std::function<void(Args...)>& callback, Args... args);

    static void execute(IManager* tp, std::function<void(Args...)>&& callback, Args... args);

};
using SimpleOneShotConnector = OneShotConnector<>;

} /* namespace threading */
} /* namespace utils */
} /* namespace eprosima */

// Include implementation template file
#include <cpp_utils/threading/connector/impl/OneShotConnector.ipp>
