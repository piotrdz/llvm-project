//===--- NoNewDeleteCheck.cpp - clang-tidy---------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "NoNewDeleteCheck.h"
#include "../utils/Matchers.h"
#include "../utils/OptionsUtils.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include <string>
#include <vector>

using namespace clang::ast_matchers;
using namespace clang::ast_matchers::internal;

namespace clang {
namespace tidy {
namespace misc {


void NoNewDeleteCheck::registerMatchers(MatchFinder *Finder) {
  if (!getLangOpts().CPlusPlus11) {
    return;
  }


  Finder->addMatcher(cxxNewExpr().bind("new_expr"), this);
  Finder->addMatcher(cxxDeleteExpr().bind("delete_expr"), this);
}

void NoNewDeleteCheck::check(const MatchFinder::MatchResult &Result) {
  const auto &Nodes = Result.Nodes;

  handleNew(Nodes);
  handleDelete(Nodes);
}

void NoNewDeleteCheck::handleNew(const BoundNodes &Nodes) {
  const auto *NewStmt = Nodes.getNodeAs<CXXNewExpr>("new_expr");
  if (NewStmt) {
    auto Location = NewStmt->getBeginLoc();
    if (Location.isMacroID()) {
      return; // ignore macros
    }

    diag(Location, "raw use of new; consider using smart pointer instead")
        << NewStmt->getSourceRange();
  }
}

void NoNewDeleteCheck::handleDelete(const BoundNodes &Nodes) {
  const auto *DeleteStmt = Nodes.getNodeAs<CXXDeleteExpr>("delete_expr");

  if (DeleteStmt) {
    auto Location = DeleteStmt->getBeginLoc();
    if (Location.isMacroID()) {
      return; // ignore macros
    }

    diag(Location, "raw use of delete; consider using smart pointer instead")
        << DeleteStmt->getSourceRange();
  }
}

} // namespace misc
} // namespace tidy
} // namespace clang
