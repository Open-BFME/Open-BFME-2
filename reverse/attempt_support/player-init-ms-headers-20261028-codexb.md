# PlayerInitFromDict CRT header recheck — 2026-10-28

Base: a33df6e0d0. Source: `Code/GameEngine/Source/Common/RTS/PlayerInitFromDict.cpp`.

Replacing the three local free/memset/memcmp declarations with stdlib.h and
string.h still changes initFromDict (RVA 0x002AFCDF, 2762 bytes). The build
rejects the changed parent and the ambiguous $L10490 unwind binding
($L10513 and $L10512). Removing this source's object and dependency receipt
and running the supported build with BFME_OBJSTORE=off reproduces the failure.
The build's internal gates compile before its final deps-cache summary.

This confirms the existing ms-headers trial in re_attempts.log (t=20,
model=claude-opus-5-5), rather than a new regression. No header or ledger
change is retained. Restoring the original source passes 31/31 rows, its
one data row, six literal references and one empty-string reference; the
frozen-file check is clean. The pre-trial ordinary link preview was LINKS
for 4707 authored bytes against index d92e7e6635. No census gain is claimed.

Keep the queue entry. A future attempt needs a source-level explanation
of the declaration-sensitive register allocation and independently provable
EH identity; repeating header placement variants is already exhausted.
