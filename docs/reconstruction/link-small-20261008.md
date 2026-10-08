# Targeted linking repairs, 2026-10-08

Baseline: the genuine 2026-10-08 06:35 census at `7ef90c5054`, copied
from `build/census/current/link_index.pkl` into `build/link_census/`.
Figures below are per-source `link_check.py` previews against that census,
with every named provider and consumer refreshed together. They are not a
new whole-program census or new function recovery credit.

## Apt pool deallocation

`DogmaAllocator.cpp` retained a second `Rva006DB270::freeBlock` after its
ledger row moved to `DogmaPoolFreeBlock.cpp`. The earlier object's copy
inlines the free-list push and is explicitly wrong under retail truth.
It also duplicated both allocation callback globals. Remove those
definitions and the now-unused pool view; the verified owning TU retains
the deallocator and the two zero-initialized callback cells.

Target evidence: existing rows `0x006DB090` (136 bytes) and `0x006DB270`
(207 bytes), the census's two strong providers and wrong selected copy,
and the normal full-byte/literal gate. No function name, layout, flags,
pin, alias, ledger claim, or verifier rule is changed.

Verification: both pristine and repaired provider gates pass 2/2 rows
and six string references. Checking all 65 affected provider/consumer
units together predicts 35 clean units and `LINKED 0 -> 11,239` bytes
(padding excluded); the other 30 retain independent blockers. The
placement rescan of the edited TU serves zero bodies and zero pins.

BFME 1 linking sweep reviewed revision
`ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f`. Its `40eabf2e41` repair
demonstrates removing competing non-retail definitions while retaining
their verified owners; this is an applicable repair pattern, not Apt
identity evidence. No matching Dogma source repair was found there.
