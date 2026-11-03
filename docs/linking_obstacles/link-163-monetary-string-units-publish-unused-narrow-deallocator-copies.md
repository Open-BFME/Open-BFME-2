### LINK-163: Monetary string units publish unused narrow deallocator copies (2026-10-30)

The wide monetary parser emits an unused 18-byte const narrow-allocator copy
with only debug incoming references and a different throwing-free binding.
A TU-local imported forceinline specialization preserves the original vendor
operation and throwing context without publishing that external copy. All 16
parser rows and EH remain exact; 95 retained code definitions, imports and
actual relocation destinations are unchanged, including all switch targets.
No pin, row, header, alias or hatch changes. With the separately verified
formatter, strict preparation passes 33 rows and the preview against
`ccafe54d1d` retains 2/2 LINKS, 0 -> 5,446 authored bytes. This clears the
bounded current-object scope only; full affected-consumer selection/loss and
census confirmation remain pending.
[Parser evidence](../../reverse/attempt_support/money-char-deallocate-link-20261030/money-get.md).

The formatter's separate verified repair retains all 17 rows and EH, with 88
external code definitions and symbolic relocations unchanged. Its matching
cleanup preserves the existing throwing free binding; no allocator import is
introduced. Both actual strict objects reproduce their private candidates.
[Formatter evidence](../../reverse/attempt_support/money-char-deallocate-link-20261030/money-put.md).

Outgoing audit: INCONCLUSIVE on older `ccafe54d1d` versus base `dc24521e86`
and the missing current CreateAHeroManager consumer receipt. Carry both
removed-provider scopes and affected consumers into the next scheduled census;
the bounded preview does not clear the broader selected-copy/loss scope.
