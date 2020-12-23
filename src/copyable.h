// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author:Lu Li (lilucpp at gmail dot com)

#ifndef PEANUT_BASE_COPYABLE_H
#define PEANUT_BASE_COPYABLE_H

namespace peanut {

/// A tag class emphasises the objects are copyable.
/// The empty base class optimization applies.
/// Any derived class of copyable should be a value type.
class copyable {
 protected:
  copyable() = default;
  ~copyable() = default;
};

}  // namespace peanut

#endif  // PEANUT_BASE_COPYABLE_H
