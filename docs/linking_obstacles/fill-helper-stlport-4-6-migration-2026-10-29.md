### Fill helper STLport 4.6 migration (2026-10-29)

At base `6a36399b76`, Rva00577CA0Fill.cpp replaces its private STL tag with
the 4.6 header declaration. Its sole 37-byte row and all external object facts
are unchanged; strict preparation passes and preview retains LINKS 37 -> 37
against index `85f6b7f40c`. The migration queue no longer serves it. The batch
audit remains inconclusive on the older index and missing current receipt for
Common/0CreateAHeroManager21FE49.cpp. Carry that consumer/provider scope into
the next scheduled census. No census gain or owner-name recovery is claimed.
[Evidence](../../reverse/attempt_support/fill-stlport46-20261029-codex.md).
