# Native INI macro-table destructor at 0x0002CD7B

The atexit body at 0x007B6A6E calls 0x0002CD7B with the global storage at
VA 0x00DDF58C. The prior INI lifetime investigation identified the two
member-destruction calls. The live INI.cpp view already has the matching
case-insensitive set and macro map, so the trial only declared an
out-of-line destructor and gave it an empty body.

Add the declaration before INIMacroTable::m_macros. Define the body after
the existing `template IniMacroTableHash::~hashtable();` line.

```cpp
INIMacroTable::~INIMacroTable()
{
}
```

The scoped compile retained all 136 existing INI.cpp function rows and
four data rows. The new destructor has all 53 original bytes once its
four image references and its FS-relative exception-list operand are
resolved. The exception graph independently reports EXACT. Its set
cleanup at +0x14 binds the row at 0x0002CC38. Its map cleanup at +0 binds
the reconciled hashtable destructor at 0x0002CCC3. The handler matches
the existing retail location 0x0075C9F7.

The current TU map marks 0x0002CD7B displaced and does not approve the
trial's INI.cpp placement. The native destination helper offers a
neighbour heuristic only. The trial was reverted. Preserve the existing
function and handler rows until placement is approved, then replace
their EvacuateDamage spellings together. The DamageModule identity and
its callers remain separate prerequisites for closing the real link
blocker.
