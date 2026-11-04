# LANPlayer and address header adoption, 2026-11-04

Inspected revision: 5745478eab. Scope: LANAPI.cpp and LANAPIhandlers.cpp in
Code/GameEngine/Source/GameNetwork/. Existing obstacle: LINK-193.

Target facts: the existing byte-verified bodies use an eight-byte address with
IP at +0 and a word port at +4. The shared BfmeNetAddress.h declares that layout;
LANPlayerClass.h embeds it at +0x14. The private address views added an empty
Rva00248CDD base to expose the already-rowed inequality helper.

Changes: include both shared headers, remove both private declarations, and use
the shared address field spellings only on address accesses. Connection-info
and TransportAddress fields retain their existing declarations. Cast the two
inequality call sites to the existing Rva00248CDD view, preserving the helper's
symbol and address. A TU-local AddressValue supplies the former constructor
expressions; handlers retain their existing NoAddress temporary helper. No
shared header or ledger identity changes are needed.

Trial evidence: aggregate sender initialization reversed the IP/port loads in
LANAPI::update (0x0044AAED), producing the only mismatch in 124 rows. A local
constructor with the original parameter types and argument order restores the
retail load order. This is a codegen observation, not evidence for a retail
helper-class name. Other local zeroed records use aggregate initialization.

Validation:
- ./build.sh on both files: 124/124 code rows exact, one data row exact;
  62 string literals, 16 empty-string references and 41 named imports verified.
- find_declared_unmatched.py on each file: all defined functions already matched.
- header_adopt_lane.py accept --class LANPlayer on both files: PASS/PASS,
  two queue rows retired by the owning tool.
- header_adopt_lane.py accept --class BfmeNetAddress on both files: PASS/PASS,
  two more queue rows retired by the owning tool.
- Ordinary link_check.py: LINKS 8,534 -> 8,534 B for LANAPI.cpp and
  6,171 -> 6,171 B for LANAPIhandlers.cpp, total 14,705 -> 14,705 B;
  index reports census 2026-11-04 17:56 at 8c757ea0db.
- git diff --check: clean.

Clearance scope: these four header-queue rows only. LINK-193 remains open for
LANAPI's own private class declarations and its other documented consumers.
No new census, ownership or real-link headline result is claimed.
