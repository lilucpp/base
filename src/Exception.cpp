// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author:Lu Li (lilucpp at gmail dot com)

#include "Exception.h"

#include "CurrentThread.h"

namespace peanut {

Exception::Exception(string msg) : message_(std::move(msg)), stack_(CurrentThread::stackTrace(/*demangle=*/false)) {}

}  // namespace peanut
