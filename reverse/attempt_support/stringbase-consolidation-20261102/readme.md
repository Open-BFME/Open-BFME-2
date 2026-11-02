# StringBase TU recovery (halilkkaya-codex, 2026-11-02)

Stack base1291df600d; local prerequisite base185bd2c3d2.
The current approved WideStrLenSource TU has five eligible sources, all inside
WWLib. The four donor definitions of StringBase are replaced through
header_adopt_lane adopt --apply by the existing canonical
reference/shims/bfme2_ascii/string_base.h; the seed selects that same header.
The shared header is unchanged. Existing byte-allocator declarations gain one
common declaration guard; their API and generated bodies are unchanged. This
is declaration reconciliation, not allocator identity or lifetime recovery.

All35 source rows, named imports, literals and existing EH graphs pass.
find_declared_unmatched is clean. The five sources retain LINKS2293B in the
ordinary current-object preview against984a4cdc4d. Strict preparation passes
all five sources. No header_queue key names any of these files, so none is
retired or silently deleted.

46 of47 original external COMDAT definitions keep their byte/relocation
digests. Trim's old public inline peek (QBE) becomes canonical private peek
(ABE), with the same4B receiver operation. The old public symbol has exactly
one indexed touching unit: trim itself; no outside consumer loses a provider.
The other four units' complete external definitions remain unchanged.
canonical-definitions.json records the sets.

The supported dry-run now accepts all five files,35rows and no rejects.
Merging is a separate next commit, including hatch/register transfers.
