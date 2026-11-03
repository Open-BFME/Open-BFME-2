# SelectionXlat two-donor tooling compatibility audit

Bounded read-only audit, 2026-11-03, once across these two moves only:

- Code/GameEngine/Source/GameClient/MessageStream/SelectionXlat_areAllSelected.cpp
- Code/GameEngine/Source/GameClient/MessageStream/SelectionXlat_selectFriendsWrapper.cpp

Both are absorbed into the same directory's SelectionXlat.cpp. At inspection
the supported merge had already deleted both donors and placed their bodies in
the destination. No additional path move was assessed.

## Active references

No actionable active consumer was found. Combined full-path/basename searches,
including case-insensitive matches, found no old-path use in tools/, .githooks/,
.github/, Code include directives, project/build configuration, scripts or the
doxygen source registry. The targeted derived-path/glob search found no
SelectionXlat donor glob or MessageStream glob assumption requiring a change.
Both source paths share the destination directory, so no directory change can
alter a donor-relative quoted include search.

Core current ownership is correctly repointed:

- functions.csv:34505: boolean ThingTemplate hash_map operator[] at 42FE40/63B
  now belongs to SelectionXlat.cpp. The old basename appears only in its BFME1
  provenance note; preserve that original external donor path.
- The 430000/29B selectFriendsWrapper row now belongs to SelectionXlat.cpp.
  Its existing decorated name and callee contract are retained.
- No old-source key/path was found in data_rows, data_ledger, body_owners,
  header_queue, ms_header_queue, flag_overrides, tu_map, gate/data/identity/hatch
  registers, data_converged or pin_consistency_baseline. No old-path fold proof
  or symbols.csv provider binding remains. No manual register retirement or
  ownership/path update is indicated by this audit.
- Destination source comments at lines 358/368 retain the donor `from` paths.
  These are provenance, not Code include directives. The bodies are present at
  360 (selectionCountFor) and 371 (selectFriendsWrapper); unrelated mixed
  SelectFriends/TranslateGameMessage owners remain separate.

## Historical references retained intentionally

- reverse/link_status.csv:8487-8488 records the measured census's old two file
  rows. It must be refreshed by the census owner, not rewritten by a source move.
- reverse/attempt_support/selection-tu-prerequisites-20261101/{preview.txt,
  allocator-strict.txt,allocator-merge-report.txt} records prior object/merge
  evidence. Old paths identify what was verified then.
- reverse/attempt_support/0x0043003c-20261019-{w8,compact}/readme.md:27 records
  an old nearest-neighbor fallback and explicitly does not approve that path.
- The W3D terrain prior packet's include-referrer/preview logs are snapshots.
  Naming/attempt history and EA original path strings should retain provenance.

Verification needed for the concrete merge remains root's normal byte/data/EH,
ledger, selected-provider and outgoing link-batch checks; this audit performs no
compilation or link selection and does not manufacture current receipts or a
census result. If the outgoing batch gains another source move or a new active
consumer, extend the batch audit accordingly. For these two paths, no separate
active tooling/configuration edit remains identified.

No tracked edits, build/cache writes, claims, Git operation or network performed.
