# The nine names the real link cannot find in AptArray.cpp, and the one cause

`next_work.py --claim` serves `??0AptArray@@QAE@XZ` @ 0x006D91B0 as a link-cycle
repair worth 1,507 bytes: "the real link stops here: 9 name(s) it references
exist nowhere, e.g. `?ContainsNativeHashVirtual@AptValueWithHash@@UBE_NXZ`".

That sample is the sample for **8 of the 72 sources** in
`reverse/exit_link_blockers.tsv`, and the cause is one thing, not nine:

> `Code/Libraries/Source/Apt/AptObject/AptScriptFunction.h` declares the whole
> virtual set of the AptValue hierarchy, and **seven of the intermediate
> classes' overrides have no definition anywhere in the tree**. Any unit that
> constructs an AptObject-derived value emits that class's vftable, and a
> vftable references every slot, so all seven come out undefined in every such
> object.

`link_check.py` says AptArray.cpp LINKS. It is reading a census index from
2026-11-10 with 348 source changes since; the real link is right and the
prediction is not current. Do not take LINKS here as a clearance.

## The seven, with the retail body each one is

Every one is a trivial default that `/OPT:ICF` folded onto some other body, so
none of them has a byte of its own. The retail evidence is the vftable slot:
MSVC fills slots in declaration order, `AptValue` declares 15 virtuals, and
`tools/vftable_map.py --va` reads the installed tables. Comparing the base
table with a derived one names the override and its address at the same time.

| slot | name | retail rva | size | the body ICF folded it onto | the C++ |
| ---: | --- | --- | ---: | --- | --- |
| 3 | `?GetNativeHashVirtual@AptValueWithHash@@UAEPAUAptNativeHash@@XZ` | 0x006CBFD0 | 4 | `?GetData@AptValueVector@@QAEPAPAPAVAptValue@@XZ` | `return &mNativeHash;` |
| 4 | `?ContainsNativeHashVirtual@AptValueWithHash@@UBE_NXZ` | 0x001826C0 | 3 | `?_AptValidate@@YA_NXZ` | `return true;` |
| 5 | `?getHasClass@AptObject@@UBEHXZ` | 0x006D6460 | 10 | `?getBit8@Rva008993E0Owner@@QAEHXZ` | `return mbHasClass;` |
| 6 | `?setHasClass@AptObject@@UAEXH@Z` | 0x006D6440 | 32 | `?setBit8@Rva008993E0Owner@@QAEXH@Z` | `mbHasClass = value != 0;` |
| 9 | `?DeleteThis@AptValue@@UAEXXZ` | 0x006CBCF0 | 12 | `?rva006CBCF0@Rva006CBCF0@@QAEXXZ` | `if (this) delete this;` |
| 10 | `?PreDestroy@AptValue@@UAEXXZ` | 0x0069E440 | 1 | `?debugIgnoreLeaks@?$StringBase@D@@QAEXXZ` | `{}` |
| 12 | `?IsGarbageCollected@AptValueGC@@UBE_NXZ` | 0x001826C0 | 3 | `?_AptValidate@@YA_NXZ` | `return true;` |

Each C++ shape is the fold partner's own source, not a guess:

- **slot 3.** `AptValueVector::GetData` is `return &mpValues;` and its row says
  "the bare `lea eax,[ecx+8]` shape carries no call or data references".
  `AptValueWithHash::mNativeHash` is at +8 (the header of
  `AptValueWithHash_RegisterReferences.cpp` records the same offset), so
  `return &mNativeHash;` is the same four bytes. A `mov eax,[ecx+8]` would also
  be four bytes and would NOT fold -- return the address, not the field.
- **slots 4 and 12.** 0x001826C0 returns **true**, on two independent witnesses:
  `_AptValidate` is `return true;` in `Apt.cpp`, and the body is also
  `codecvt<char,char,mbstate_t>::do_always_noconv`, which returns true by the
  standard. The return-FALSE three-byte body is a different address, 0x0073B660
  (`?Rva0073B660False@@YA_NPAXH@Z`), and that is where `AptValue`'s own
  `ContainsNativeHashVirtual` sits. Base false, derived true -- a value that
  carries a hash answers yes. Getting these two the wrong way round is the one
  real trap here.
- **slots 5 and 6.** `Rva008993E0Owner` is `char m_pad[0x1c]` then
  `union { unsigned int m_flags; struct { unsigned int m_low : 8; unsigned int m_bit8 : 1; }; }`.
  `AptObject` has the identical shape: `mnImplementedObjects : 8` then
  `mbHasClass : 1` in the word at +0x1C (AptArray.cpp records the native
  constructor clearing "the low byte and bits8..9 at +1C"). Same offset, same
  bit, same two bodies.
- **slot 9.** `Rva006CBCF0::rva006CBCF0` is `if (this) v14(1);` where `v14` takes
  one int. Slot 14 of a 15-slot table is the scalar deleting destructor at
  +0x38, and MSVC compiles `delete this` on a polymorphic type as exactly that
  call with `__flags = 1`. 12 bytes: `test ecx,ecx` / `je` / `push 1` /
  `mov eax,[ecx]` / `call [eax+0x38]` / `ret`.
- **slot 10.** One byte is `ret`, so the body is empty.

Slots 12 and 13 of the BASE table are `__purecall`, which is the independent
check that this slot mapping is right: `AptValue::IsGarbageCollected` and
`AptValue::RegisterReferences` are the only two pure virtuals it declares.

## Landing them

Each is a new matched row at an address another row already owns, so each takes
`add_match.py --icf-owner <the partner above>` and lands with `fold-proof=`.
Do not pin and do not add an `/alternatename`: these are real definitions of
names the headers already declare, and one out-of-line definition per name
resolves it for every unit at once.

Put each one in its own class's unit, not in a consumer:
`AptObject.cpp` for slots 5 and 6, an `AptValueWithHash` unit for 3 and 4,
`AptValue.cpp` for 9 and 10. `AptValueGC` (slot 12) has no unit of its own yet.
Writing them as header inlines instead would also link -- that is the ledger's
"header-inline default slot" idiom -- but it puts a COMDAT copy of each in every
Apt object for no gain, and an out-of-line definition is the retail shape: one
body, folded.

`build.py` passes `-O2` to every unit before the `// cl:` flags are appended, so
a unit whose comment reads only `// cl: /MD` is still optimised and these bodies
still come out at the sizes above. Three bytes for `return true` needs that.

## What is left after the seven

AptArray.cpp's object has 52 undefined externals; 43 are supplied by other
objects. Subtracting the seven above leaves the vftable's own bindings --
`??_GAptObject@@MAEPAXI@Z`, `??_GAptValueWithHash@@MAEPAXI@Z`,
`??_GAptArray@@MAEPAXI@Z` -- and those belong to the bridge lane, which already
carries `??_7AptValueWithHash@@6B@` as `bridged` in
`reverse/vtable_bridge_queue.tsv` with AptArray.cpp among its sources. They are
not part of this repair.

## Why this is a handoff and not a commit

Every one of the seven sits in a file or at an address another worker holds:
`BugFixer300@vm` took `Code/GameEngine/Source/Common/AptObject.cpp`,
`Code/Libraries/Source/Apt/AptValueWithHash_RegisterReferences.cpp`, 0x006CBFD0,
0x006D6440 and 0x006D6460 while this was being measured, and is working the same
blocker from `Code/Libraries/Source/Apt/AptObject/AptFactoryConstructors.cpp`
(10 missing names, the same sample). `Code/Libraries/Source/Apt/AptValue.cpp`,
the only right home for slots 9 and 10, is held as well.

## Reproducing

    ./build.sh Code/Libraries/Source/Apt/AptArray.cpp
    # then list the object's undefined externals (secnum 0, class 2, value 0) in
    # build/match/^code_^libraries_^source_^apt_^apt^array.obj and subtract the
    # names reverse/functions.csv and reverse/symbols.csv already hold

    python3 tools/vftable_map.py --va 0x00CEAED0   # AptValue, the base table
    python3 tools/vftable_map.py --va 0x00CEA778   # AptArray
    python3 tools/vftable_map.py --va 0x00CEE8C8   # an AptScriptFunction table

The derived tables agree with each other and differ from the base in exactly
the five slots the four intermediate classes override.
