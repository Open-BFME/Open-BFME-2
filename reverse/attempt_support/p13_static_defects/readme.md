# P13 out-of-object pointers: the open items and the two tool requests

Static-defects lane, 2026-11-07. Detector: `tools/image_iso.py --relocation-bounds-only` on the
diagnostic-link image 3f421fb15c57 (master b033afb2ab, real-link run 42419917598): 11 open,
down from 102 at the first run and 24 at e3397174c459.

| Defect | Sites | Status |
|---|---|---|
| `_FilterBlock_mmx` 0x001D7330 | 6 | Fixed: the bicubic bank is g_vp6BicubicTapsMmx (agree:nl-dddc9deb88a1), defined in FilterBlockMmx.cpp, and all six sites address it directly. |
| `??1Rva007EB2C0Object` 0x00658260 and its `??_G` | 4 | Tool request 1 below. |
| `?rva00261C89@Rva00261C89@@QAE_NXZ` (KindGate) | 1 | Tool request 2 below. |

## Tool request 1: name_lane serves ledger-owned, address-named globals that have no data row

The dtor reads the two flag bytes at retail VA 0x00E09FA8/0x00E09FA9 as `g_Va0130A588 + 4/+5`. They are
the globals `g_Va0130A58C`/`g_Va0130A58D` in Rva007EB270Shutdown.cpp. data_ledger.csv rows 33786/33787 own
them; reverse/data_rows.csv has no row for either. Naming them in the dtor's unit builds exact (2/2), but:
- the hatch gate refuses each new reference to an address-named global ("address_global +2", register
  grants 0; re_attempts.log 0x00658260);
- `name_lane.py register-data` refuses: the address already has an overlapping data_ledger.csv owner;
- `name_lane.py next --file Code/GameEngine/Source/Common/Rva007EB270Shutdown.cpp` serves one key only,
  `Rva007EB270Shutdown function`. Neither global is offered for naming.

Request: `name_lane.py next` serves an address-named global that the data ledger owns but data_rows.csv
does not row, as a `global` key of its owning source. The agreed name then lands through rename.py's
global route. With real names, the dtor's +4/+5 reads become direct references, and the four defects go.

## Tool request 2: a member-to-constructor respell (rva002618A2/rva002618FA as BitFlags<69> constructors)

KindGate's two masks are MSVC function-local statics. One guard word (`g_00DFEAD4`) carries bits 1 and 2,
and each object is initialized once under its bit through a call that returns `this`:
`?rva002618FA@Rva002618A2@@QAEPAV1@HHHHHH@Z` (0x002618FA, push 0 then five bit indices) and
`?rva002618A2@Rva002618A2@@QAEPAV1@HHHH@Z` (0x002618A2, push 0 then three). That is the shape of Zero
Hour's `BitFlags(BogusInitType, Int idx...)` constructors. Today's source spells the statics as globals,
`g_00DFEA9C` and `g_00DFEAB8`, and addresses them as `&g_00DFEA98 + 4` and `(char *)&g_00DFEA9C + 0x1C`.
That is the out-of-object defect. Naming the globals directly lets cl keep each address in ebx/edi, while
retail reloads each as an immediate: ./build.sh fails byte comparison (re_attempts.log 0x00261C89). The
structural inference, not yet verified, is that real function-local statics constructed through BitFlags
constructors restore retail's shape.

Request: a rename.py route that respells a member function returning `this` as a constructor of the real
class: `?rva002618FA@Rva002618A2@@QAEPAV1@HHHHHH@Z` -> a `BitFlags<69>` ctor taking the dummy init enum
and five ints, and `rva002618A2` likewise with three. It must cover their 9 spelling units and change the
row's kind and scope, which `function --respell` (identifier or signature only) does not. After it,
KindGate's statics become real function-local statics, and the global placeholders `g_00DFEA98`,
`g_00DFEA9C` and `g_00DFEAB8` go.

## Request 2's premise: tested in scratch, 2026-11-08

Bridge lane. cl was called directly with the build's command, output in a scratch directory, with nothing
through `build/match` or `./build.sh`. Controls: the current KindGate unit compares EXACT, and the same unit
with one planted constant differs. `check_csv` refuses a stash for a row that has real C++, so the whole unit
is below rather than banked under `reverse/attempts/`.

**Result: real function-local statics reach retail's bytes, and the two rows match as real constructors.**

| Body | Compiled as | Result against retail |
|---|---|---|
| 0x00261C89 (120) | Two local statics, `const BitFlags<69> &` to each | EXACT, relocations masked |
| 0x002618A2 (88) | `BitFlags<69>(BogusInitType, int, int, int)` | EXACT, only `_memset` relocated |
| 0x002618FA (129) | `BitFlags<69>(BogusInitType, int, int, int, int, int)` | EXACT, only `_memset` relocated |

The relocations masked in 0x00261C89 fall where retail's addresses do, in retail's order: guard twice,
`s_set` (retail 0x00DFEAB8), 5-arg ctor (0x002618FA), guard twice, `s_clear` (0x00DFEA9C), 3-arg ctor
(0x002618A2), `s_set`, `test` (0x002615C0), `s_clear`, `test`. The guard is one compiler word, `$S1`, with
bits 1 and 2, as retail's 0x00DFEAD4 is. The object's sections run `s_clear`, `s_set`, guard, the same order as
retail's addresses; no image was linked to check placement.

```cpp
// cl: /O1 /G7 /MD
template <int N>
class BitFlags
{
public:
	enum BogusInitType { kInit = 0 };
	BitFlags(BogusInitType, int a, int b, int c) throw();
	BitFlags(BogusInitType, int a, int b, int c, int d, int e) throw();
	bool test(const void *other) const;
private:
	unsigned m_words[7];
};
class Rva00261C89
{
public:
	bool rva00261C89();
private:
	char m_pad[0x108];
	unsigned m_kind[7];
};
bool Rva00261C89::rva00261C89()
{
	static const BitFlags<69> s_set(BitFlags<69>::kInit, 8, 9, 10, 11, 12);
	static const BitFlags<69> s_clear(BitFlags<69>::kInit, 0x6d, 7, 0x59);
	const BitFlags<69> &set = s_set;
	const BitFlags<69> &clear = s_clear;
	void *kind = m_kind;
	return set.test(kind) && !clear.test(kind);
}
```

Two conditions, in everything tried:

- **The references.** Calling `s_set.test(kind)` directly gives 122 bytes: cl keeps each address in `ebx`/`edi`,
  while retail loads an immediate before each call. So does every other shape and flag set tried that kept
  the frame right: mutable statics, casts at the call, nested blocks, by-reference `test`, `/Ob0`, `/Oa`, `/Ow`,
  `/G6`, `/Oy-`. `/Og-` and `/O2` also miss, and they break the current unit too. Why a reference binding stops the
  hoist was not established, and these bytes do not show that the original source was written this way.
- **No EH state at the constructor calls.** Retail has no frame. Plain constructors under the unit's flags give 158
  bytes with `__EH_prolog`. `throw()` on the constructors or `/GX-` on the unit each give the exact 120, and the
  bytes do not say which retail had. An in-class constructor body does not help: it was not inlined and kept the
  frame. The two constructor bodies are exact with or without `throw()`.

Target facts: the guard, the bit tests, the two bodies returning `this` (0x002618A2 ends `ret 0x10`), the call and
address order. Structural inference: these are function-local statics built by constructors, which is
what the exact result supports and does not prove. Donor fact: the names `BitFlags` and `BogusInitType` come from
Zero Hour. `?test@?$BitFlags@$0EF@@@QBE_NPBX@Z` is already on master at 0x002615C0.

Not tested: `./build.sh` on real units, a link, the other 7 units that spell these rows, and the choice between
`throw()` and `/GX-` against the rest of KindGate's eventual translation unit.

## Request 2 stopped by the coordinator, 2026-11-08: real, but not what the plan needs next

Bridge lane. Nothing below landed; the row names and all 9 units are unchanged on master. Why it stopped: the spelling
in the request is wrong on the bytes, the route needs a `name_lane` change, and the scope is really three placeholder
classes. The coordinator's decisions, should this resume: an ordinary respell with votes for the name, no
`--basis retail` family; `throw()` rather than `/GX-`, with the source and the row saying that retail's bytes do not
distinguish them, and likewise that the `const &` form matches but is not proven as the original's spelling. If a voter
disagrees or votes do not arrive, it waits: this scratch result does not choose the name.

**The 9 units match through `./build.sh`, on a throwaway branch.** All 9 passed before as a control and all 9 passed
with the two rows respelled as constructors (`Functions: OK 2/2` on `Rva002618A2.cpp`, ledger names changed to match,
`Rva00261C89KindGate.cpp` on real statics). The class spelling was the request's, for the shape only. The edit is
`try_ctor.py.txt` beside this readme. The consumers became temporaries, `&BitFlags<69>(BitFlags<69>::kInit, ...)`, each
unit with a private view of the class, and `throw()` on the constructors. `CastleBehavior.cpp` and
`Rva0039A1CADtor.cpp` declare `rva002618FA` and never call it, so they only lost the declaration. Not done: a link,
`tools/rename.py`, or anything through the hooks.

**`BitFlags<69>` is wrong on the bytes.**

- Target facts: both constructors `memset` 0x1C bytes (7 dwords) and index by `bit >> 5`. Callers pass bit 191
  (`rva0039BE95`'s caller: 109, 90, 10, 11, 191) and 0xAF (175). So N is at least 192, and a 7-dword store suggests at
  most 224.
- `BitFlags<69>` would be 3 dwords and could not hold those bits. `KINDOFMASK_NONE` is declared `BitFlags<116>`, also
  too small. `?test@?$BitFlags@$0EF@@@QBE_NPBX@Z` (0x002615C0) is spelled 69 too, and `BitFlags69Test.cpp` says retail
  walks seven words regardless. None of these N is established; that row's own spelling is in question as well.
- Donor fact only: the names `BitFlags` and `BogusInitType` come from Zero Hour.

**A voter brief must name no N.** It should give the facts above (0x1C storage, highest bit seen) and leave the spelling
to the voters.

**Three placeholder classes hold what looks like one retail class's constructors.** These are one shape; that they are one
class is a structural inference.

| Row | Today's spelling | Bits |
|---|---|---|
| 0x00045411 (44 bytes) | `??0Rva00045411BitSet@@QAE@HH@Z` | 1 |
| 0x0006EE7A (66 bytes) | `??0Rva0006EE7A@@QAE@HHH@Z` | 2 |
| 0x002618A2 (88 bytes) | `?rva002618A2@Rva002618A2@@QAEPAV1@HHHH@Z` | 3 |
| 0x002618FA (129 bytes) | `?rva002618FA@Rva002618A2@@QAEPAV1@HHHHHH@Z` | 5 |

`Rva00045411BitSet` has 229 mentions across the tree, and its header also declares 3-arg and 6-arg forms. Its 6-arg form
is given a body in `CastleBehavior.cpp`, while retail's caller 0x0039A142 goes to 0x002618FA, so what provides that body in a
link needs reading before any merge. Respelling only two rows would leave one retail class under three names.

**The keys are not ready, and would need a `name_lane` change.** These rows are served as identifier keys, so a voter
cannot answer with a constructor. `spelled_problem` refuses an answer that changes the row's member
(`it must stay the same operator or member`). `rename.py function --respell` takes prepared C++, but changing a row's
kind and scope through it was not tried.

## Request 1 needed no tool change, 2026-11-09

Bridge lane. Both refusals above came from one missing thing: `name_lane` serves a `global` from its data row, and
`rename.py global` plans from one. So the route is a data row under the global's current address-derived name, which
asserts nothing. With the row, `next --file` serves the key as eligible, and `rename.py global` plans the consumers: 3 units
for `g_Va00E032DC`, including the macro-hidden `Rva00433C18Pool` and the `IntList` view, and 3 each for `g_Va0130A58C/D`.
`register-data` and `--admit-agreed` are for data with no definition yet, and are not this route.

Traps: the size is what the build proves by `sizeof`, not the ledger's, which is a next-address bound (`g_Va0130A58D` is 1,
not 3). A key is not served while another worker holds the source's file claim. `rename.py`'s plan does not list
`reverse/hatch_baseline.tsv`, so the rename's commit runs `hatch_counters --update` for the `address_global` lines that fall.

The same route is open to the other owned, address-named globals with no row (475 at this writing, these three included);
none of the others is rowed here. The plan above was run past the agreement check only, with a stand-in name; no vote exists yet.
