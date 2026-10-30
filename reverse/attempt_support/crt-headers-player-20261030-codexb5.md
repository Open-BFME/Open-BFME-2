# Player CRT-header adoption remains blocked

Inspected BFME 2 `43231d14ed`, reference `337e4b48e8`.
The reference freshness stamp is stale. Official upstream was fetched at
`6b4ffbe661dd9a78116c4b7dcb47a502f5d4999b`; the reference file claim belongs
to another worker, so no refresh or new successful freshness stamp is claimed.
The checkout stays on the clean, previously verified pin. A full build probe
was stopped when that ownership conflict was confirmed; its partial output is
not a verification pass.

`PlayerInitFromDict.cpp` passes the supported build unchanged: 31/31 rows,
one data row, 21 funclet pins and string/float/import reference checks.
`find_declared_unmatched.py` passes before and after restoration.

The Microsoft-header queue lists its local `free` and `memset` declarations.
The following trials all fail the byte gate:

- Replace both declarations with `<stdlib.h>` and `<string.h>`, first in
  the include block, then at the old declarations.
- Delete both declarations, relying on existing container/string includes.
- Retain `free`, replace only `memset` with `<string.h>`.
- Retain `memset`, replace only `free` with `<stdlib.h>`.
- Delete only `free`, keeping the existing includes and `memset` declaration.

In these trials the native `Player::initFromDict` parent at RVA `0x002AFCDF`
grows from 2,762 to 2,764 bytes. A normalized COFF comparison of the first
trial preserves the other 51 external COMDAT fingerprints. The first changed
instruction sequence loads a key address into EBX earlier and reuses it for
ECX; later pushes use zero rather than EBX. This is compiler output evidence,
not a demonstrated semantic difference or a proven explanation of the cause.
The parent mismatch also leaves the two allocation-failure funclets ambiguous;
the verifier correctly refuses to choose between equal bodies.

The source was restored exactly and its unchanged 31/31 build passes again.
Both header findings remain in the queue. No labels, extents, pins, flags,
headers or checks were altered to admit a trial. The next attempt needs a
clean C++ explanation for the parent's code generation before adopting these
declarations. The first attempt-log entry accidentally used `0x002AF729`
(`Player::init`); the subsequent tool-recorded entry corrects the target to
`0x002AFCDF`. No trial changed `Player::init`.

## Nonthrowing allocation declaration

`WW3D2/Rva00131BE5Ctor.cpp` also passes its unchanged 142-byte constructor
at `0x00131B57`. Replacing its local `operator new(unsigned) throw()` with
either `<new>` or `<new.h>` fails: the compiler inserts
`mov byte ptr [ebp-4], 2` before allocation, adding four bytes. The target
keeps the previous state. This isolates an exception-contract prerequisite;
the standard throwing declaration alone does not reproduce the target.
The source was restored and its header-queue finding retained. No exception
flag, declaration attribute or verifier was changed to admit either trial.

# Relation-map identity retirement preflight

The default picker also selected `RelationMapXfer.cpp`, whose remaining
identity entry concerns `PlayerRelationMap::xfer` at `0x002ADEBE`.
The supported file build passes 6/6 rows, including the existing iterator
`0x0041E832` and bucket-skip `0x0039FD3E` owners. Strict explicit-provider
preparation passes for this source as well.

`repair_queue.py retire identity` refuses without changing the register:
1,645 ledger objects are missing, so selected copies are unknown. This result
does not establish that the registered identity finding is cleared. A later
`link_check.py --fetch-index` imported 20,077 objects into the object store;
it does not itself populate or verify every current ledger object. Retry the
owning retirement path after a current whole-tree build supplies that proof.

The initial link pick, `stlport_list_int.cpp`, already reports LINKS in an
ordinary source preview against `85f6b7f40c`: 67 -> 67 authored bytes. Its
source was left untouched and its claims released. This is scoped preview
evidence, not a census change. The subsequent fetched index is `6fe1089c24`
(2026-10-30 04:25); no new census was run.
