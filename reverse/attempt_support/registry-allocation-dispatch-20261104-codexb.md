# Registry consolidation: distinct delete dispatches

Inspected `c6adee4abf` on 2026-11-04. Claimed both
`Code/Libraries/Source/WWVegas/WWLib/registry.cpp` and
`Code/Libraries/Source/WWVegas/WWLib/RegistryDeleteValues.cpp`.
The supported WWLib planner and current in-memory TU plan identify 38
approved rows in these two donors, with no mixed or refused files. The files
hold 43 matched rows in total. No map or approval was changed.

Earlier evidence attributed the remaining merge failure to incompatible
StringClass copy-assignment configurations:
[prior trial](consolidation-registry-2026-11-04.md), and the same-day
`tu-merge:.../registry.cpp` attempt in the log. This pass tested the actual
byte mismatch under the destination's complete flags.

## Target facts

- `Deleta_All_Values` at RVA 0x00610300 is 233 bytes. Its call at 0x006103D0
  targets scalar `operator delete`, RVA 0x0002FD60, after the array destructor
  iterator at 0x006103CA.
- The separately rowed StringClass vector deleting destructor at 0x0011F6B0
  is 84 bytes. Its array branch calls array delete (0x0002FD80) at 0x0011F6D8;
  its scalar branch calls scalar delete at 0x0011F6F5.
- Both delete providers already have distinct matched rows in mem_ops.cpp.
  Treating them as aliases would erase a real target distinction.

## Trials

All compiles used ordinary `./build.sh`; no direct build-cache compile.

1. Copy the destination's flags onto RegistryDeleteValues.cpp. Only its
   Deleta_All_Values row fails: the entire body matches except that the call
   at +0xD0 now selects array delete, 32 bytes above scalar delete. The
   StringClass copy-assignment flag is not needed to explain this mismatch.
2. Remove `/FIbfme_wwstring_teardown.h` from those donor flags, retaining
   the donor's existing allocation declarations before its explicit teardown
   include. All four donor rows pass, without NATIVE_COPY_ASSIGN.
3. Give registry.cpp the same allocation declarations and explicit teardown
   include, removing its forced include. All ordinary registry rows pass,
   including Get_Value_List; the separate StringClass deleting-destructor
   row now fails because its array branch selects scalar delete. Across the
   two files, 42/43 pass.
4. Include vector.h before declaring array delete, then parse the string
   teardown header. The StringClass destructor matches again, but
   Deleta_All_Values again selects array delete: 42/43 pass.
5. Parse string/vector headers without array delete, explicitly instantiate
   `VectorClass<StringClass>::Clear()`, then declare array delete. This still
   loses Deleta_All_Values in the same way: 42/43 pass.

These are local declaration/code-generation experiments, not recovered
retail include order. No shared header, operator provider, alias, pin or
compiler hatch was added. No merge was applied. A common source context
must retain both retail deallocation choices before another mechanical merge
trial is useful; adding NATIVE_COPY_ASSIGN is not that prerequisite.

## Restored verification

Both files were restored byte-for-byte to their originals. Ordinary build
passes 43/43, 10 string literals plus five empty references, and 49 named
imports; both declared-unmatched checks pass. check_csv passes. A restored
link_check preview against census 2026-11-04 16:16 (`2f0cb97f52`) reports
both units linking and preserves all 4,706 scoped census bytes. The failed
array-delete trial preview had rejected the donor; it is not retained.
No source/path/register change remains and no census or file-count gain is
claimed. LINK-255 records the next prerequisite.
