# Delayed spline event constructor: map provider cleanup

Scope: `Code/GameEngine/Source/Common/Rva003C2F40TreeCtor.cpp`, constructor
`??0Rva003C2F40Owner@@QAE@XZ`, RVA `0x002BAE57`, 50 bytes.
Baseline checkout: `0b2b06a5e4`; preview index: `12b9e7a7c0`,
2026-10-30 10:11. This is an existing placeholder cleanup, not a recovered row.

## Target facts

The native constructor stores VA `0x00BFE408` into `this`, then calls RVA
`0x005011C1` with `this + 0x0C`. The table at RVA `0x007FE408` contains:

| Slot | Target RVA | Observed role / current ledger owner |
| --- | --- | --- |
| 0 | `0x002BAE8F` | Deleting destructor; rowed as nonvirtual `Rva002BAEAB` |
| 1 | `0x000B3FD0` | Empty return; shared post-load body |
| 2 | `0x002BAE89` | Returns the literal `DelayedSplineCameraEventModule` at `0x007FE424` |
| 3 | `0x003FD321` | Transfer wrapper in `VslotSmallBodiesAE.cpp` |
| 4 | `0x003FD2F6` | Boolean body in `V4SubObjectSizeGuard.cpp` |
| 5 | `0x003FD584` | Boolean step body in `Rva003FD584Step.cpp` |
| 6 | `0x0007C3F8` | Returns 8; current owner is `CameraClass::Class_ID` |

The actual destructor at `0x002BAEAB` calls the member destructor at
`0x002B80CE` on `this + 0x0C`, then the seven-byte vptr store at
`0x0049B47C` on `this`. Its eight-byte unwind action at `0x007767D2` also
jumps to `0x0049B47C`. The constructor and destructor share the EH handler
at `0x007767DA`. The member destructor already has an `_Rb_tree<int,
pair<const int, AsciiString>, ...>` row in `stlport_int_ascii_tree_dtor.cpp`.
These are address and code observations; shared bodies do not establish the
event's full source type or the names of its individual slots.

## Existing source and provider facts

`StlportIntMapDefaultCtor.cpp` already owns the 25-byte body at `0x005011C1`
under the `map<int, BfmePod24, ...>` constructor spelling. Its source describes
the folded int-keyed map constructors. `Rva00417F7CInit.cpp` provides an existing
example of declaring that out-of-line constructor with twelve-byte map storage.

The old constructor source instead declared an eight-byte private tree view
and called `??0Rva003C2F40Tree@@QAE@XZ` through a pin to the same address. The
pin's note incorrectly said the body was unrowed. No other active `Code/` or
shim source refers to that constructor name.

The verified change uses the existing map provider spelling and twelve-byte
storage. It does not claim that the event's mapped value type is `BfmePod24`.
The unused pin is deleted. `hatch_counters.py --update` lowers the address's
pin count from three to two, and also removes the stale
`Rva0073DFD0Element::Rva0073DFD0Element` present-unmatched register occurrence
left behind by the earlier `ShroudManagerCell` respelling (`7ed98efdf8`);
that source no longer contains the marker. No source-path or row moves occur.

The old header's `0x003C2F40` address and VNI provenance were unsupported for
this placement; the header now states the native address and runtime name.
The ledger's historical BFME 1 donor note is not proof of a BFME 2 donor path.

## Verification and remaining work

- `./build.sh` passes the constructor's 1/1 row before and after the change.
- Strict `link_check.py --prepare-current` passes 2/2 rows for this source and
  `StlportIntMapDefaultCtor.cpp`; the latter is unchanged.
- `eh_verify.py` reports EXACT 1, with no baselined mismatch.
- `find_declared_unmatched.py` reports all defined functions already matched.
- All six external COMDAT names and raw bodies are unchanged. Five retain
  identical relocation-aware digests. The constructor's only relocation change
  is its REL32 map call from the pin name to the existing rowed provider.
- `pin_consistency.py --check` and `check_csv.py` pass (9,388 pin rows).
- The two-source preview keeps the map provider at 25 linked bytes and the
  constructor at zero. The constructor's unresolved set falls from three to
  two: `??1Rva003C2F40Base@@UAE@XZ` and
  `??1Rva003C2F40Owner@@UAE@XZ`. No census gain is claimed.

Full closure needs a coherent native hierarchy across the constructor,
`Rva002BAEAB.cpp`, the slot owners, and
`GameLogic/System/LivingWorld/LivingWorldLogicDelayedEventXfer.cpp`. The latter
already constructs this event for kind 8 with a 28-byte allocation and uses a
Snapshot-derived seven-slot structural view. That is a source lead, not proof
that its placeholder signatures are the native declarations. The current
constructor emits only a partial placeholder vtable, while the destructor's
current composition view emits a nonvirtual deleting-destructor name. Do not
silence these differences by pinning destructor names, suppressing the vtable,
or treating the folded return-8 body as independent CameraClass provenance.

The staged `link_batch_audit.py` returns INCONCLUSIVE (exit 2): the index is
behind the outgoing base, and affected consumer
`Common/0CreateAHeroManager21FE49.cpp` lacks a current receipt. This does not
establish whole-image selected-provider or loss clearance. LINK-161 carries
the provider/caller scope and broader affected consumers into the next
scheduled census. No nightly or smoke run was started.
