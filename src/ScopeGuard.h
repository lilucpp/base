// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author:Lu Li (lilucpp at gmail dot com)

#ifndef PEANUT_BASE_SCOPEGUARD_H
#define PEANUT_BASE_SCOPEGUARD_H

#include <functional>

namespace peanut {

class ScopeGuard {
 public:
  template <class F, class... Args>
  ScopeGuard(F &&f, Args &&...args)
      : f_(std::bind(std::forward<F>(f), std::forward<Args>(args)...)),
        active_(true) {}

  ~ScopeGuard() {
    if (active_) {
      f_();
    }
  }

  void dismiss() { active_ = false; }

  ScopeGuard() = delete;
  ScopeGuard(const ScopeGuard &) = delete;
  ScopeGuard &operator=(const ScopeGuard &) = delete;

  ScopeGuard(ScopeGuard &&rhs) : f_(std::move(rhs.f_)), active_(rhs.active_) {
    rhs.dismiss();
  }

 private:
  std::function<void()> f_;
  bool active_;
};

}  // namespace peanut

#endif  // PEANUT_BASE_SCOPEGUARD_H