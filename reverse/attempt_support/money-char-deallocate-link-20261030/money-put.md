# Wide monetary formatter: unused narrow allocator copy

Inspected base `dc24521e86`, index `ccafe54d1d` (2026-10-30 15:43).
`stlport_wide_money_put_string.cpp` has the same debug-only unused narrow
allocator COMDAT as the parser. Its imported forceinline specialization keeps
the original vendor operation, assertion, const ABI and global throwing C++
free context. It follows the existing malloc and wide-allocator cleanup
specializations. No pin, row, alias, hatch, header or compiler setting changes.

Private before/after verification passes all 17 rows and every emitted handler
parent graph EXACT. All 88 retained external code bodies and their symbolic
relocations are identical; only the unused allocator disappears. The import
symbol set is unchanged, with no allocator import introduced.
[Private comparison](money-put-comparison.json), [actual object](money-put-actual.json).

Literal build.sh, frozen-definition and strict preparation pass. Joint
preparation with the parser passes 33/33 rows. The ordinary preview against
`ccafe54d1d` retains 2/2 LINKS, 0 -> 5,446 authored bytes (formatter 2,616,
parser 2,830). Both actual strict objects reproduce their private candidates.
No new unique coverage, original source-name or official census gain is
claimed. Full consumer selection/loss checks and scheduled census confirmation
remain pending.

Ready-batch audit: INCONCLUSIVE on the older index versus `dc24521e86` and
the missing current CreateAHeroManager consumer receipt. Carry the complete
removed-provider/consumer scope into the next scheduled census.
