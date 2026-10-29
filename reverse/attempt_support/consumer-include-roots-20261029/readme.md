# Explicit native includes restore Eva/thread strict receipts

Scope: Code/GameEngine/Source/GameClient/Eva.cpp (unchanged source), its
project-owned reference/shims/eva_vector/EvaVectorABI.h, and
Code/Libraries/Source/WWVegas/WWLib/thread.cpp. All three files were claimed;
all frozen-definition checks pass before and after. No generated source,
upstream vendor header, verifier, baseline, compiler flag, pin or path moves.

The previous supported preparation refused both consumers because a macro
include in a project source/shim has unknown search roots. Diagnosis finds
exactly EvaVectorABI.h's _STLP_NATIVE_HEADER(vector) and thread.cpp's
_STLP_NATIVE_C_HEADER(process.h). vendor/stlport/stl/_config.h182..194
sets the pinned MSVC7.1 macro path to ../include. Make those two operands
literal <../include/vector> and <../include/process.h>, retaining their
conditions and include order. This is the existing macro expansion, not a
new fallback. Plain <process.h> would incorrectly select the sweep shim,
which lacks _beginthreadex; that approach is not used.

The old control passes38/38 rows and2 data rows. The official bounded
link_check.py --prepare-current command now exits0 and produces version2
strict reusable receipts for both exact providers. Its ordinary byte/data/
string/float/import gates pass38/38 and2 data rows. A separate metadata
check proves both strict_current=True and exactly unchanged dependency
path sets: Eva76 headers, thread42. Only the project Eva shim's content
hash changes; thread resolves the same native CRT process.h with the same
header contents. All frozen checks still pass. No new tests are needed
for two include-spelling changes beyond these direct platform gates.

Ordinary joint preview against840db2d676:2/2 LINKS, preserving3471 authored
per-source bytes (Eva3016, thread455). The printed historical3310->3471
delta includes earlier thread recovery and is not a gain from these edits.
Raw object hashes differ, so no whole-object identity is claimed; the
retail row/data checks and exact header lookup comparison are the scope
of this evidence. No new unique matched bytes or measured census credit.

This clears the include-inventory prerequisite for these two consumers
only. LINK-008's graphics consumers and other strict-receipt gaps remain
open. The earlier GameWindow input cleanup and stopped handoff stay as
separate commits; the current include repair is a new source prerequisite,
not a replay of either admission/log operation. The complete outgoing
loss/selection audit and next census remain separate verification steps.

Model GPT-6; t=12 for the two-source include repair; lane=R; budget=30m.
