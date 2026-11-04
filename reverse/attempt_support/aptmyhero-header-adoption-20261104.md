# AptMyHero header adoption — blocked (2026-11-04)

Seat: `nleigh` (3808776+nleigh@users.noreply.github.com), model
qwen38-27b-ninfer. Claim `class:AptMyHero`. Base commit `3a9216557b9`.
Verdict banked in `reverse/re_attempts.log`
(`??0AptMyHero@@QAE@PAVAptCreateAHero@@@Z @ 0x005B12C5 -> blocked`).

## Verdict

The class-header adoption of `Code/GameEngine/Include/GameClient/AptMyHero.h`
(three queued rows in `reverse/header_queue.tsv`: `AptMyHeroCtor.cpp`,
`AptMyHero_Unresolved.cpp`, `AptMyHero.cpp`) is **structurally blocked** on the
ctor row `??0AptMyHero@@QAE@PAVAptCreateAHero@@@Z` (0x005B12C5, 1155B).
Landing all three files requires a class-contract change to the canonical
header (typed vector members), which is outside a single header-adoption
lane's scope.

## Trial (executed and reverted; tree clean at base)

1. `AptMyHeroCtor.cpp`: include canonical `AptMyHero.h`, strip the private
   class, rename scalar members to canonical names
   (`holder140` -> `field140`, `pending144` -> `field144`,
   `flag148` -> `field148`, `availAttribPoints154` -> `field154`,
   `maxAttribPoints158` -> `field158`).
2. `./build.sh` full byte gate: **FAIL** on the ctor row. Reverted.

### Byte anchors (decoded from `build/match` target bytes)

Scratch decoder: `C:\Users\nleig\AppData\Local\Temp\opencode\aptmyhero_trial_decode.py`.

| Offset | Retail bytes | Meaning |
|---|---|---|
| 0x005B133A | call -> 0x00211E58 | generic 29B ICF-folded empty vector-base ctor; **unrowed** |
| 0x005B1354 | `movss` zero store | +0x168 |
| 0x005B1358 | `movss` zero store | +0x16C |
| 0x005B135D | `push 0x0C; lea esi+0x174; push` | array ctor arg setup |
| 0x005B136A | `mov [esi+0x170],1` | int member |
| 0x005B1374 | call -> 0x00629512 | `??_L@YGXPAXIHP6EX0@Z1@Z` CRT EH vector ctor |
| 0x005B1386 | `mov [esi+0x18C],0` | int member |

Trial compiled bytes: scalar stores **byte-identical**, then straight to the
+0x170/+0x18C stores — all vector-init code absent. The gap is exactly the
vector-init region.

### Symbol facts

- **0x00211E58**: ICF-folded empty vector-base ctor (29B). The no-size ctor of
  `_Vector_base<BfmeE8>` is not rowed and has no alternatename. The symbol is
  *defined* by `Code/GameEngine/Source/GameLogic/Object/SpecialPower/ManTheWallsSpecialPower.cpp`
  (line 47: `__declspec(noinline)` template specialization preserving the
  0x211E58 fold).
- **0x00629512**: `??_L` CRT EH vector ctor, owned by
  `Code/Libraries/Source/CRT/VS2003/ehvecctr.cpp` (vendored CRT).
- Superseded early misread: 0x00360D26 is
  `??1Rva00360D26Member@@QAE@XZ` (ObjectFilterRelease.cpp); the +0x174 array
  call goes to 0x00629512.

## Why no in-scope fix exists

Canonical `AptMyHero.h` keeps the vector members **opaque**
(`unsigned char field15C[12]`, `unsigned char field174[24]`) plus
`float field168/field16C`, `int field170`, `int field18C`, and a
`sizeof == 0x190` extent assert. MSVC emits member initializers in
declaration order; trivial (opaque) members emit **no** code; array members
cannot be memory-initialized. No C++ spelling over the canonical layout can
reproduce retail's interleaved init sequence. (Scalar-member renames alone are
byte-identical, which isolates the gap to the vector-init region.)

The only fix is **typed vector members in canonical `AptMyHero.h`** — a
class-contract change affecting:

- the 9 already-adopted AptMyHero consumer units (incl.
  `Code/Libraries/Source/WWVegas/WWLib/Rva005B0E9F.cpp` and
  `Code/GameEngine/Source/Common/Rva005B4A46Dtor.cpp`), which must be
  re-verified in the same batch,
- the 3 queued files, and
- the pending `base-extent` vote in `reverse/class_contracts/AptMyHero.json`
  (size 400, vslots 0/5; vote `[[0,316]]`x2 vs `[[0,320]]`x1 — not this
  worker's to decide).

## Queue failure reasons (pre-existing, from `header_adopt_lane` problems)

- `AptMyHeroCtor.cpp`: `availAttribPoints154` token at file scope.
- `AptMyHero.cpp`: `mapObjectInfo15C` is a `BfmePod8Vector` vs canonical
  `uchar[12]`.
- `AptMyHero_Unresolved.cpp`: `field10` is also a `Keyboard` member.

## Per-file prerequisites for the next worker

- **AptMyHeroCtor.cpp** — the trialed unit (blocked as above). Unused private
  views (`_STL`, `BfmeE8`, `MyHeroViewRange`, `ObjectCreationList`) are legal
  to leave in place.
- **AptMyHero.cpp** (1715-line body unit) — private `CreateAHeroData` (line 34)
  and `CreateAHeroManager` (line 69); uses `m_0c`-colliding tokens; typed
  `mapObjectInfo15C.resize` at ~line 1506. Including canonical `AptMyHero.h`
  forces removing the private `CreateAHeroData` (the canonical header pulls
  canonical `CreateAHeroData.h`; redefinition fails the gate) — i.e. the
  `CreateAHeroData` / `CreateAHeroManager` adoptions in the same file are
  **separate queue rows, separate class lanes/claims**.
- **AptMyHero_Unresolved.cpp** (dtor + vtable TU) — private `CreateAHeroData`
  (line 39) uses `field0C/field10/heroName08/image138`; the
  `MyHeroBlingRecord::field10` rename collides with `field10` -> `m_10`. The
  dtor body has the same class of implicit member lifetime-byte problem.

Canonical base reference: `Code/GameEngine/Include/GameLogic/CreateAHeroData.h`
(`m_0c`/`m_10`/`field08`/`field138` naming). Adopted-consumer pattern:
`Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptMyHeroRefreshCamera.cpp`
(canonical includes mid-file, raw pointer math over `field140`,
`m_0c`/`m_10`).

## Family history

LINK-177 (`AptMyHero_Unresolved` vtable slot-3 census loss) was repaired
2026-11-02 (lk15, cause `b056878e3e`, xfer-spelling fix); see
`docs/linking_obstacles/`. Only this adoption remained open for the family.
No new obstacle-register entry: this is not linking work.

## Suggested path forward (out of scope here)

1. Class-contract owner: decide typed vector members in canonical
   `AptMyHero.h` and settle the pending `base-extent` vote.
2. Coordinated multi-class batch: the 3-file AptMyHero adoption together with
   the `CreateAHeroData` / `CreateAHeroManager` lanes, re-verifying the 9
   already-adopted consumers in the same batch.
