Player CRT-header trial, 2026-10-30
=================================

Inputs: BFME2 4bf903241756abcd19dd7a73cf78fc87ca1b6904 and retained
BFME1 1d5131d3f193cdf01a99da66ccd6828639585650. Source:
Code/GameEngine/Source/Common/RTS/PlayerInitFromDict.cpp.

The Microsoft-header queue calls its free and memset declarations drop-in
candidates. Tested three substitutions, each through ./build.sh:

* Include stdlib.h and string.h after hash_map; remove both local declarations.
* Include stdlib.h only; remove free and retain the original memset declaration.
* Include string.h only; remove memset and retain the original free declaration.

All three fail the existing 2762-byte Player::initFromDict at 0x002AFCDF,
and its existing $L10490 funclet binding becomes ambiguous. The first trial
keeps the parent's total length but changes register allocation and temporary
code around +0x440, with displaced branches/calls elsewhere. Thus this is
not merely local-label renumbering, and the byte verifier correctly refuses
the trial. No callee ABI equivalence or safe whole-file migration is claimed.

After restoring the original source, ./build.sh passes 31/31 rows, one data
row, six string literals, one empty-string reference and float/import checks.
The original funclets resolve through verified parent EH data. There is no
landed source change, queue retirement, baseline edit or new hatch. Future
work needs a source-level explanation for the changed parent code before
rebinding any funclet; choosing either identical unwind body by bytes alone
would not resolve the ambiguity.
