### LINK-236: static initializers the exit link bridges

Status: open (lane started 2026-11-04 by halilkkaya-in-o1 at `993e6014c8`; next seat continues).

`initializers_bridged` (real link at `612abfbebb`: 961) counts the entries in retail's `.CRT$XCU`
table that no kept object registers. `tools/exit_link.py` registers them from a generated
`retail_initializers.obj` so that an image can start. The exit test needs the count at 0, with every
entry registered by real source. This entry records how the count is measured, the method that
retires an entry, and what remains.

**Mechanism (MSVC 7.1, target and object facts).** A global with a dynamic initializer makes its
object emit a TU-local `_$E<n>` in `.text$yc` and a DIR32 to it in `.CRT$XCU`. A global with a
destructor also gets an atexit cleanup `_$E<n+1>` in `.text$yd`. Every object numbers its own
ordinals, so two TUs' `_$E1` are different functions. The VC 8 `??__E` names in the ledger are labels
only; the object symbol is `_$E<n>`. The linker sorts `.text$yc` and `.text$yd` to the end of
`.text`, which is why retail's initializers sit together at 0x007AB7F0..0x007B67FF and the cleanups
at 0x007B6880 and later. `_initterm` runs the table in link order, and each TU's entries are
contiguous in definition order.

**Measuring locally.** `python3 tools/image_report.py --out build/<dir>` takes about 20 s over the
`build/match` objects (no link, allowed for seats). It writes `initializers.not_registered_rvas`,
`plain_functions`, `twice`, `by_shape_only` and `unidentified`. `image_report.bridge_entries(rows,
kept)` gives exactly the list `exit_link` bridges.

**Tool fix `212c0525c0`.** The 2026-11-03 report credited each object's `_$E1` to the first ledger
row aliased `_$E1`, so its numbers were wrong:
- the "54 `??__E` rows nobody registers" were all registered;
- the 60 "unreachable" entries were registered too;
- the 27 "registered not in retail" were atexit ordinals credited by name.

Now a `_$E<n>` is read only in its own object. An unrowed one is first narrowed by masked shape;
then its relocations pick the entry, because each DIR32 and REL32 target must land where the ledger
places it.

| Measure (on `993e6014c8`'s objects) | Old | New |
| --- | ---: | ---: |
| Registered | 145 | 228 |
| Bridged | 961 | 938 |
| Unreachable | 60 | 0 |
| Registered twice | not reported | 116 |
| Unidentified | not reported | 342 |

**Method to retire an entry (`a8956992cd`, `a3743fba03`, 0x007AE9E6, bridged 938 -> 937).**
1. Read the plain row's body. It names the global it builds (DIR32 store or `mov ecx, g`).
2. Find the global's owner in `reverse/data_ledger.csv`. The initializer row belongs with that
   definition.
3. In the owner, give the definition its initializer: `unsigned int doubleClickTime =
   GetDoubleClickTime();`. The spelling comes from the Zero Hour donor's `GadgetListBox.cpp`; keep the
   linkage the ledger name has.
4. `./build.sh` the owner, then read its object's `.CRT$XCU` and the new `_$E<n>` body. They must equal
   retail's bytes.
5. Commit the retraction on its own: delete the plain row, add a line to `reverse/deleted_rows.csv` and
   remove the body. `add_match --replace-rva` takes over only scaffold rows.
6. Then run `add_match '_$E<n>' <rva> <size> <owner>`. A bare `_$E<n>` row is not a hatch
   (`hatch_counters` rule 9).
7. Re-run `image_report`: the RVA should leave `not_registered_rvas`. Also run link_check and scoped
   DIR32 checks on both files.

**What is left (937 bridged, all plain function rows), by grab-bag file:**

| Grab-bag file | Rows |
| --- | ---: |
| `Rva007AB7F0HalfRateInits.cpp` | 425 |
| `INI/Rva007ABBF6BlockParseInits.cpp` | 130 |
| `StaticTagInitializers.cpp` | 63 |
| `GameNetwork/Rva007B55E0TxnNameInits.cpp` | 62 |
| `Rva007AD295ZeroInits.cpp` | 56 |
| `Rva007ABC6FFrameRateInits.cpp` | 31 |
| `Rva007ABEF3ArgCtorInits.cpp` | 16 |
| `Rva007ABBB3CtorInits.cpp` | 13 |
| `Rva007AB85CAtexitInits.cpp` | 12 |
| `Rva007AC6DDGlobalInits.cpp` | 12 |
| Smaller files | about 100 |

Most rows say "owning TU unrecovered". The work is attribution first, then step 3 in the owner.

**HalfRateInits (425 rows).** Each row is `s = LOGICFRAMES_PER_SECOND / 2` into a TU-local static
that nothing reads. The Zero Hour donor's `Drawable.h:279` has `const Int DRAWABLE_FRAMES_PER_FLASH =
LOGICFRAMES_PER_SECOND / 2;`. That is a structural inference: BFME 2 made the frame rate a variable
(`BfmeClientFramesPerSecond`), so every TU that includes the header carries this initializer. The
fix is the header constant, with each owner TU including the header. Do not make 425 statics in the
grab-bag.

**How to attribute a TU.**
- Neighbouring entries in retail's table that are already registered by a known object bound the run.
- The static's `.bss` address falls inside its TU's data contribution next to ledgered globals.

**Runtime hazards found (not counted in `initializers_bridged`).**
- **Registered twice (116).** Objects register an initializer whose retail entry another object
  already registers, so the image builds that global twice. 52 come from
  `FXParticleSystemFactories.obj`, which re-emits `ModuleTag<...>::s_key`/`s_name` template-static
  initializers rowed in `FXParticleSystemModules.cpp`; an example is 0x007AF6F3. Retail compiled these
  once. The split `FXParticleSystem*` files each instantiate them, and merging those files into their
  TU removes the copies.
- **Unidentified (342).** Registrations whose shape and relocations match no retail entry. 224 are
  in `FXParticleSystem.obj`, `FXParticleSystemFactories.obj` and `FXParticleSystemModules.obj`; for
  example `g_categoryModuleTemplate<N>` ctor+atexit. They run in our image and never in retail. Check
  whether retail initializes these statically before an image boots.
- **Shape-only credits (3).** These are listed in `by_shape_only` and are weak.

**Next useful checks.**
- Pick a family whose global already has a data-ledger owner and apply the method there. The
  `Rva007ADBD1ImportInits.cpp` timeGetTime globals are owned by `Network.cpp` and
  `Rva005A6709Predicate.cpp`.
- Separately, decide the HalfRate header constant.
