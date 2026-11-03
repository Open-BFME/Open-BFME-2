### XML lexer CRT header cleanup (2026-10-29)

At base `93d6aea258`, BfmeLexEAN.cpp drops its redundant local strncpy
import declaration and uses its existing string.h include. All eight function
rows, one data row and three imports remain exact; strict preparation passes.
The header auditor reports clean and its scoped refresh removes one queue
finding. Preview retains LINKS for 648 authored bytes against `85f6b7f40c`.
The outgoing audit is INCONCLUSIVE: the index predates the base and affected
consumer Common/0CreateAHeroManager21FE49.cpp lacks a current receipt. Carry
that consumer and this provider into the next scheduled census; no census
gain or full consumer closure is claimed.
[Evidence](../../reverse/attempt_support/lexean-ms-header-20261029-codexb.md).
