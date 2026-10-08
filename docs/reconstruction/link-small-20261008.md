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

## Audio-key member release

`Rva003ED498Count.cpp` also defined `bfmeClearMembers`, although its row
belongs to `LargeGroupAudioKeyList.cpp`. The earlier strong definition
was selected instead of the ledger owner. Remove the redundant release
walk and its private erase-tree view; keep all six rows owned by the
edited unit and the existing release helper unchanged.

The pristine nine-row gate included the Apt providers above. The repaired
audio-only gate passes all seven rows. Checking the five affected units
together predicts `RvaTreeDtorFamily.cpp` clean, with
`LINKED 0 -> 4,755` bytes. The four other units retain independent tree,
global, or call-name blockers. The placement rescan serves no new bodies
or pins.

BFME 1 donor repair `8cc14958ea` at the reviewed revision above routes
the same subsystem's callers to its already matched member-release
provider. BFME 2 already uses that call spelling; that part is inherited.
Its remaining local defect is the competing definition, proven by this
target's census and ledger ownership rather than donor addresses.

## Mouse singleton name

`MouseProcessEvents.cpp` called its singleton `MessageStreamSubsystem`,
which has no provider. Restore `TheMessageStream`, already defined by
`Common/MessageStream.cpp`. Target initialization names the subsystem
`TheMessageStream`; the mouse's native loads read RVA `0x00A00950`
(VA `0x00E00950`), in the PE `.data` loader-zero tail. BFME 1's
`bde8f7a746` singleton repair and its
`Mouse_createStreamMessages.cpp` supply corroborating name/usage evidence;
the BFME 1 data-ledger implementation is inapplicable to this repository.

Pristine and changed gates pass all six consumer rows. The unchanged
message-stream provider passes all 13 rows. The repaired consumer previews
clean: `LINKED 0 -> 2,020` bytes. Its placement rescan serves zero bodies
and zero pins.

The shadow data check's `wrong-name` warning uses a stale provisional
`data_ledger.csv` row that attributes `MessageStreamSubsystem` to
`GameEngineClientSubsystems.cpp`. That source now declares `TheMessageStream`
extern and has no definition of the former name. Refreshing its object
through the normal eight-row gate with the button unit, then deriving a
scratch ledger with `data_ledger.py --out`, chooses `TheMessageStream` and
its sole owner `MessageStream.cpp` at the same RVA. No new global is defined
by this change. The committed generated index and its baseline are untouched.

## Deferred button renderer

BFME 1's `745fed6271` const-view repair also applies to the unresolved
struct-typed `TheGlobalData` in `W3DPushButton.cpp`. Binding its radial-clock
reads to `TheWritableGlobalData` preserves all seven rows. However, the
unit also privately defines retail initialization word VA `0x00DE6128`,
which six matched clearers reset through another definition. That existing
data-identity defect would remain behind a clean linking preview.

A direct shared-guard repair for the seven image caches changes the native
nested EH state pairs and leaves two colour-static guard bits unreconciled.
Restore the original source, record the blocker through `re_log.py`, and
exclude this unit from the published gain. No verifier workaround is used.

Across the three edited source files, the previews identify 37 newly clean
units covering 18,014 non-padding matched bytes. No census records were
rewritten, and no new alias, pin, function row, baseline, header or compiler
flag was added.
