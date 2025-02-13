//===--- NoNewDeleteCheck.h - clang-tidy-------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISC_NO_NEW_DELETE_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISC_NO_NEW_DELETE_H

#include "../ClangTidyCheck.h"

namespace clang {
namespace tidy {
namespace misc {

/// Checks for uses of new and delete in code
class NoNewDeleteCheck : public ClangTidyCheck {
public:
  NoNewDeleteCheck(StringRef Name, ClangTidyContext *Context)
      : ClangTidyCheck(Name, Context) {}

  void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  void check(const ast_matchers::MatchFinder::MatchResult &Result) override;

private:
  void handleNew(const ast_matchers::BoundNodes& Nodes);
  void handleDelete(const ast_matchers::BoundNodes &Nodes);
};

} // namespace misc
} // namespace tidy
} // namespace clang

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISC_NO_NEW_DELETE_H
