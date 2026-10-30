# Auto-resolve token table: hatch-counter false reject

Control: 7906295d3f8e99862e1b7b005566c1fd7a6b4984.
Two registered data-identity keys name g_00DC85C4 in GUI/Rva00427157Ctor.cpp
and GameClient/Rva0041811DTokenParsers.cpp. The existing definition in
Common/System/INI_VeterancyLevelToken.cpp is g_Va00DC85C4Names[9], the
eight AutoResolveUnit strings and terminating null at RVA 009C85C4.
Both consumer declarations have exactly the provider's const-char-pointer
array type. Only the two declarations and uses are respelled; the GUI unit's
now redundant /alternatename is removed. No provider or table contents change.

Before and after: 18/18 functions, one data row and eight string references
pass the normal build; all three EH graphs are EXACT. COFF comparison keeps
all 61 code sections' raw bytes identical (including COMDATs and padding).
Exactly one DIR32 reference in each object changes from g_00DC85C4 to the
existing global. data_check reports zero findings and zero converged-address
violations. repair_queue retire data passes and retires each of the two keys.

The publication prerequisite then fails: hatch_counters.py --update counts
one additional address_global occurrence key in the GUI unit and two in the
token-parsers unit for g_Va00DC85C4Names. Its count is keyed by source/name,
so adopting an existing canonical address-derived global is not admitted as
a total-keeping move here. No --allow or --admit is run, and the checker is
not changed. A separate tooling/policy repair must resolve this conflict.
This reproduces the class of canonical-global retirement blockage already
recorded for other addresses; do not replay the same source trial unchanged.

All source and data-register edits are restored; no debt retirement or
alias removal is retained. The adjacent diagnostic patch contains the proven
source change and the owning tool's two-key retirement, but is not landable
under the current hatch rules. The ordinary pre-trial preview against
ccafe54d1d (2026-10-30 15:43) retains 2/2 LINKS, 691 + 462 authored bytes;
no link gain, new census or runtime proof is claimed.
