# Recipes proven on near misses

Short, reusable fixes that turned near misses into byte matches. They were
proven in the solo fork (`dylanrussellmd/bfme2-solo`, private, so its commit
ids are not cited here); each recipe names the retail RVA where it closed a
body instead. `rg ',0x0042E014,' reverse/functions.csv` finds the landed row
and its source when this ledger has it; `reverse/attempts/<rva>.cpp` is the
bank where one is named. Advice tools: `tools/flag_hint.py` (flags from byte
tells), `tools/sig_check.py` (declaration vs retail), `tools/wpo_detect.py`
(private register conventions); `wb_draft.py` prints the first two with each
draft and `next_work.py` serves `wpo` candidates last.

## StrategicHUD `Impl` constructors (Apt movie clips)

- **Inline ctor calling the out-of-line callback binder.** The in-place
  callback reference gets an inline constructor that calls the rowed delegate
  binder; that is what orders the arg-slot `esp` save before `ecx`.
  HUD::Impl ctor 0x0042E014 (1801 B); CommandButtonMovieClip::Impl ctor
  0x005E136C.
- **Two-string `operator+` inline but not inlined.** Define the concat
  operator `inline` in each unit (a COMDAT at /O1, not expanded): visible, it
  lets the frame overlap the concat node with the arg-slot save as retail
  does; also the fold proof for its ICF address. New-turn indicator ctor
  0x0057C152, end-turn button ctor 0x00579575.
- **Separate button bases, nothrow base ctor.** Model the panel as an
  interface plus two button bases under their own vtables; with the base ctor
  nothrow no EH state is stored between them. Palantir panel ctor
  0x00578D22 (1811 B).
- **User-declared ctor on the text-plus-string node.** A non-POD node (a
  user-declared default ctor) lets the builder construct straight into the
  argument temporary instead of copying a temp. RegionDetailsMovieClip
  SetTabsState 0x005E314B; DynamicAutoResolveMovieClip::Impl ctor 0x005FC20E,
  which this closed from a 1013-vs-1001 B bank. The same lever in reverse:
  an out-of-line copy ctor fixed EH temp order in `0d47672ab0`
  (`__adjust_heap` 0x00428372).

## Headers and types

- **`<math.h>`, never hand-declared `fabs`/`floor`/`sqrt`.** The float
  overloads keep compares in float (dword constant, pop before `fxch`).
  0x002E3978, AIFollowWaypointPathState::onEnter 0x0034ED7B,
  isPosDifferent/isAngleDifferent 0x0028B0A8/0x0028B119.
- **Typed struct arrays, not byte-offset arithmetic.** Indexing a modelled
  array reproduces retail's `[index+base]` operand order. The TheAudio volume
  loops 0x0005244A and 0x000524AA.
- **Real STLport containers over hand-written views.** Use `_STL::vector`
  and friends from the vendored headers; private views drift in codegen and
  block linking. CreateAHeroManager::GetSubClassDefaultBlingId 0x0021BF11
  closed once a hand-written `ClassVector` view became
  `std::vector<CreateAHeroClass>`.

## Flags

The region decides /O, /arch and /G for most units (`tools/flag_defaults.py`);
`flag_hint.py` compares tells with the flags the build really passes.

- **`/G7` tells.** `add reg, 1` / `add [mem], -1` instead of `inc`/`dec`
  (`flag_hint` p=1.00), and `imul` for a small scale such as `level*12`
  (p=0.93): CreateAHeroHero::SetButtonForLevel 0x0040737F and
  ShowBattleStepStateHandler::OnHitAnimDone 0x005EAEAF closed on the imul,
  the list max-scan 0x005CCCFC on `/G7 /arch:SSE`, and 18 banks improved
  with these flags and the `<math.h>` change above.
  `__EH_prolog` means `/O1`; an inline `fs:[0]` frame means not `/O1`.

## Frames, stores and locals

- **Inline helpers for Coord3D copies and zeroing.** Copying or zeroing a
  member Coord3D through a small `__forceinline` helper (Zero Hour's inline
  `Coord3D::set`/`zero`) stops cl forwarding just-stored members, so it
  re-reads them as retail does and keeps the retail store order; member-wise
  or struct assignment forwards them instead. Three Pathfinder functor
  constructors: 0x002ED72B, 0x002EE43A, 0x002ED484.
- **Block-scope address-taken locals.** Retail reuses the slot of a dead
  `&local` for later temporaries; cl does so only when the local's block has
  closed (frame 0x18 -> 0x10 in the `0x002EDCF7` bank).
- **Struct assignment moves the whole frame.** `Coord3D pos = *p;` made cl
  keep loop counters in memory and pack the range into a different dead
  parameter home; the unit's inline `copyCoord3D` (Zero Hour's `set`) gave
  retail's frame and registers (0.74 -> exact, Pathfinder::CanApproachToTarget
  0x002FA2DC). Try it first when a bank's slots and registers differ and the
  body copies a struct.

## Stack-slot packing: what does not explain it

Banks where retail packs locals into other dead slots, sinks a store to just
before a call, or saves `esp` after building a by-value argument were
tested together (13 banks, scratch compiles only). Do not retry these:

- **Compiler build.** game.dat's Rich header lists 1762 C++ and 184 C
  objects from 13.10.3077, the cl in `inputs/toolchains/vs2003`, and no
  LTCG or POGO entries: no other 7.1 build, no `/GL`.
- **Flags.** One at a time on each bank: `/O2`, `/Ox`, `/Ob1`, `/Ob2`,
  `/Oy-`, `/Oa`, `/Ow`, `/Op`, `/Ot`, `/Gs0`, `/GF`, `/Gy-`, `/GS`,
  `/G5|6|7`, `/GR`, `/EHa|s|sc`, `/Zi`, `/Oi-`, `/O1` minus `/Gs /GF /Gy`,
  and `#pragma optimize` `g` off, `a` on, `w` on, `y` off, `t` on. None
  was exact. The only gain was `/EHa` on `0x002080DA` (0.959 -> 0.975),
  and it made other banks worse.
- **Declaration order.** Nine orders of five function-scope locals
  (`0x002ECAFF`) compiled to the same bytes. cl 7.1 does not lay out the
  frame in declaration order.
- **Small source changes.** A const-reference parameter instead of a named
  `&local` gives the same code. So do init order, hoisting and block scope
  for the late `this` store (`0x002EDCF7`). Zero-init helper vs direct vs
  aggregate init and out-param temps change nothing (`0x002FA202`).
  Copy ctor, out-of-line ctor, virtual dtor and EH flags do not give the
  per-argument `esp` saves. A trivial dtor gives one save, but in the wrong
  place (`0x002F06A3`). An inline function returning the class by value
  copies it with `movsd` and gets no RVO. In matched code the save marks a
  class-type argument built in its own slot. Two examples: the inline
  `end()` iterators in `EnableComponents` (0x004117E8), and an out-of-line
  copy ctor (0x005E5A38). Start from those when you try this again.
- **Register-copy order.** Where `mov esi, ecx` lands next to the argument
  loads in the prologue (`0x00470717`) does not move with local order,
  inline casts or hoisting `this`.

## Shapes and order of work

- **WorldBuilder twins for loop shapes.** `python3 tools/wb_show.py 0xRVA --gd`
  shows the debug twin; its loop condition (top-tested, `break` after the
  call) is usually retail's under /O1. The first-match scan 0x002A8AB1,
  which 63 callers reach.
- **Fan-in first for repairs.** Fix the callee or spelling many rows share
  before single rows: calling SubsystemInterface's ctor through its one
  pinned `void` spelling restored 38 rows across 40 units; `link_rank.py`
  ranks by bytes held out.
- **A callee spelled `void` that returns `float`.** If the instruction after
  the call stores or uses st0 (`fstp`, `fst`, `fcomp` and so on), the callee
  returns a float. Respelling 0x002C9B80 (and its forwarder 0x002C9BC3) as
  float unblocked four callers, 1214 B in all: CanApproachToTarget,
  isWithinAttackRange, 0x002CB2D1 and HordeContain slot 20. A scan of all
  such call sites found no other member callee spelled void, only CRT import
  thunks.
- **Never hand-write `/alternatename`.** Bind callers to the ledger row's
  real spelling instead (nine units' placeholder callees were rebound this
  way); dead pragmas whose alias another object defines, or that no object
  references, can simply be dropped.
