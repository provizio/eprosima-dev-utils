// Copyright 2022
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
 * @file DBQueueWaitHandler.ipp
 */

#pragma once

#include <cpp_utils//exception/InconsistencyException.hpp>

namespace eprosima {
namespace utils {
namespace event {

template <typename T>
void DBQueueWaitHandler<T>::add_value_(
        T&& value)
{
    logDebug(UTILS_WAIT_DBQUEUE, "Moving element to DBQueue.");
    queue_.Push(std::move(value));
}

template <typename T>
T DBQueueWaitHandler<T>::get_next_value_()
{
    // Assure that only one thread check if queue must be swapped
    std::unique_lock<std::mutex> lock(pop_queue_mutex_);

    // If front is empty, swap to back queue
    if (queue_.Empty())
    {
        logDebug(UTILS_WAIT_DBQUEUE, "Swapping DBQueue to get element.");
        queue_.Swap();
    }

    // If queue is empty, there is a synchronization problem
    if (queue_.Empty())
    {
        throw utils::InconsistencyException("Empty DBQueue, impossible to get value.");
    }

    // TODO: Do it with front and pop without copy
    auto value = std::move(queue_.Front());
    queue_.Pop();

    return value;
}

} /* namespace event */
} /* namespace utils */
} /* namespace eprosima */
