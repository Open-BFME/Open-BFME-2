### LINK-128: MessageStream constructor identity lacks a verified vtable home

Status: Blocked on verified data identity. Updated: 2026-10-28; inspected revision: `3e03b082b4`; ordinary-preview index: `14dc3d2467`.

Evidence / affected units: the two constructor-binding keys in MessageStream.cpp's appendMessage (0x0030F6D4) and insertMessage (0x0030F704). The sole kept GameMessage(Type) constructor is 53 bytes and agrees with retail outside its DIR32 fields, but allowed_symbols certifies it `unknown`: its GameMessage vtable has a literal data-index entry at RVA 0x00809840 and no verified data-row home. [Scoped evidence](../../reverse/attempt_support/messagestream-constructor-identity-20261028-codex.md).

Completed: source byte verification passes 18/18 and its one data row; frozen-file check passes. Rebuilt the 20 missing ledger objects through the normal verifier (282/282, three data rows). The owning identity retirement then still finds both keys; neither is removed. Ordinary preview preserves LINKS, 573 -> 573 bytes. No source edit retained.

Remaining / next check: establish supported vtable data ownership, or recover the constructor and its opaque callers together with current TU approval. The former constructor-repoint attempt's nonlinking MessageStream prerequisite has changed, but the opaque callers remain separate work.

Clearance: none for identity retirement; the ordinary source preview alone is clean. Census confirmation: no new result claimed.
