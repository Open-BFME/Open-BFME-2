# Native make_pair consumer EH mismatch

The two legacy consumers considered here are:
`Holder00524477::Rva00524477` at 0x00524477/101B and
`GameLogic::rva00246F8E` at 0x00246F8E/73B. The direct temporary attempt below
was blocked and restored. The subsequent GameLogic-only comparator-visibility
repair passes verification and is awaiting the parent's commit. Dispatch remains
unchanged and blocked. No header, pin or hatch change is retained.

## Target facts

Native factory 0x0023FC23/27B accepts three cdecl stack words: hidden output
pointer, integer reference, and string reference. It calls the pair constructor
at 0x00523DB7, returns the output pointer in EAX and ends in RET0. The existing
provider is `_STL::make_pair<int, AsciiString>(const int &, const AsciiString &)`.
The two consumers pass those words at calls 0x00524495 and 0x00246FA2, forward
EAX to their find operation, then destroy the string at result+4. Both retail
consumers lack an EH frame. Both currently emit the obsolete explicit-output
symbol; the canonical provider exists in current objects.

Alias history is recorded in
`docs/linking_obstacles/alias-removal-sole-providers-2026-11-15.md`: f7a5440a17
introduced the binding and 1e79469632 removed it. Prior source comments already
reported typed-return EH growth or an MSVC7.1 ICE; the earlier placement-wrapper
attempt in `reverse/re_attempts.log` also failed. These are prior observations,
not proof that no legitimate typed source can match.

## Restored trial

The trial placed a canonical `make_pair` temporary directly in each find
full-expression, removing the raw eight-byte buffer and explicit destruction.
Dispatch used the canonical STLport utility include; GameLogic already uses the
same pair-to-key view in its matched `setControlBarOverride` body. No alias,
wrapper, nothrow annotation, optimization pragma or pin was added.

The official two-source build failed exactly the two changed bodies:

| Consumer | Retail | Trial | EH |
|---|---:|---:|---|
| 0x00524477 | 101B | 124B | new object-only frame |
| 0x00246F8E | 73B | 98B | new object-only frame |

Both introduced `__EH_prolog`, a handler relocation and lifetime-state updates.
The remaining 19 associative EH graphs stayed EXACT. The changes therefore
cannot be banked on symbol correctness or approximate byte similarity.

Both source files were restored under exact trial-hash guards. The official
restored build passed 174/174 functions and four data rows; EH passed 19/19
EXACT. Comparing saved and restored COFF providers found zero additions,
removals or changed definitions in either source. No compiler is left running.

Ignored evidence: `build/decal-diagnostic/make-pair-23fc23-trial/` contains the
source manifest, before/proposed/failed source copies, original/failed COFF,
native disassembly, trial/restoration build logs, provider comparisons and EH
reports. `canonical-temporary.patch` is a failed experiment, not an approved fix.

## Next evidence question

Determine which actual declaration or compiler-visible call behavior explains
the native absence of EH while the pair is live during lookup. Establish this
from the lookup/comparator/string call graph and original compiler settings
before another source trial. Do not hide the mismatch with casts, blanket
nothrow, a replacement alias, a fabricated wrapper or an unproved flag change.

## Verified GameLogic comparator visibility repair

GameLogic previously exposed only a declaration of the key comparator. The
existing native provider defines its inline signed-integer-then-string body.
Making that same body visible in GameLogic, together with the canonical pair
temporary, removes the compiler's unnecessary EH frame without any exception
annotation or flag change. Native 0x00240CE0 calls the existing AsciiString
comparison at 0x0005598C; both exact bodies are now emitted in GameLogic too.
The preexisting key view and all headers are unchanged; no new class or helper
wrapper is introduced.

The official whole-source build passes 173/173 functions and four data rows.
All 19 associative EH graphs are EXACT. The lookup is exactly 73 bytes, with
no unresolved or masked relocations and no EH frame. Its obsolete explicit-output
reference is absent from current COFF. Both added comparator providers equal the
existing provider definitions and independently match native bytes/relocations:
0x00240CE0/47B and 0x0005598C/23B. The only changed retained provider is the lookup.
The incidental nonidentical AsciiString scalar-deleting-destructor shadow is no
longer emitted; its existing rowed provider remains strictly exact at
0x001F6083/28B. No provider address loses its rowed implementation.

Declaration, class, CSV and pin checks pass; the source's hatch delta is zero.
The four-source provider-inclusive link preview is clean, but uses the stale
2026-11-16 16:28 census at 0534e78db3 and is not a fresh real-link result.
Evidence is in the `comparator-visible/` subdirectory of the scratch directory
above, including strict native-provider proof, complete provider delta and EH.
No further trial was started; the parent owns committing and real-link testing.
