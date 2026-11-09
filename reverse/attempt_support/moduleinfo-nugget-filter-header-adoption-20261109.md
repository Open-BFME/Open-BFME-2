# Four ModuleInfo Nugget consumers adopt the canonical header

Inspected at6124bd48af on2026-11-09. Complete source scope:
ModuleInfoNuggetAssign.cpp, ModuleInfoRva0033C84A.cpp,
ModuleInfoRva0033C8B5.cpp and ModuleInfo_clearModuleDataWithTag.cpp.
Each removes its private ModuleInfo/Nugget declarations and includes the
unchanged ModuleInfoClass.h. Existing row names, sources and extents stay.

The assignment uses canonical first/second/interfaceMask/copiedFromDefault/
inheritable members. The three filter bodies retain their existing STL vector
erase binding and iterator representation. Two source-local vector references
view the canonical three-pointer descriptor at offset0; they create no vector
or Nugget lifetime. The tag scan uses canonical begin/end and member spellings.
Nugget stride20B, data pointer+8, mask+0x0C and flags+0x10/+0x11 stay exact.
The module-data predicates remain the existing isAiModuleData and neutral
slot07 calls, without a new subclass/slot identity claim.

Offsets, accesses and byte results are target facts. Existing donor commentary
is retained separately; the change imports no donor and claims no original TU
or additional recovered layout. Source-local STL declarations/specializations
remain as before. No source path, shared header, ledger identity, pin, alias
declaration, hatch or compiler flag is changed.

All four first private trials match five native rows (282 ledger bytes), with
no EH-bearing row or missing EH object. Normal build.sh passes5/5 with no
string/float/import obligations; frozen checks pass before/after. All four
current-input link previews against index5b5011469d (2026-11-09 19:12;
census9b9d058303 at17:41) preserve57+56+102+66=281 linked bytes. The tag row's
one trailing padding byte is outside that code count. Owning acceptance retires
four header rows, leaving24 ModuleInfo consumers locally. Strict receipts are
prepared for all four changed sources.

Before/private and final/normal provider audit preserves all11 COMDAT payloads
and sizes and every public definition, undefined reference and selection policy.
Weak defaults and /INCLUDE directives are unchanged. The two filter objects
which did not previously include AsciiString inherit its seven existing alias
directives; every identical pair is already in the current index. No alias is
declared, removed or admitted here. The two existing AsciiString consumers'
directives do not change.

Local evidence: build/thingtemplate-header-cohort-20261109/{moduleinfo-filter-
sources.json,probe-moduleinfo-filters.py,moduleinfo-filter-private-proof.json,
moduleinfo-filter-private-eh.json,moduleinfo-filter-build.log,
moduleinfo-filter-frozen-*.log,moduleinfo-filter-link.log,
moduleinfo-filter-accept.log,moduleinfo-filter-prepare.log,
prove-moduleinfo-filters.py,moduleinfo-filter-provider-diff.json}. Historical
before/candidate snapshots must not be overwritten by rerunning probes.

The remaining24 class consumers, their enclosing-object identities and genuine
constructor/destructor lifetimes remain separate. Do not treat the two queued
map accessors at enclosing offsets+0x3A0/+0x3AC as twelve-byte ModuleInfo members;
the canonical header already records that identity prerequisite. The preceding
publication's broader audit remains INCONCLUSIVE for unchanged
AICowerState_onEnter.cpp at index5b5011469d/baseefb6e7363c. Carry it into the next
census. This scoped cleanup establishes no new global linking coverage, image
or runtime result.
