# SlowDeathBehavior name-key consolidation prerequisite (2026-10-31)

At a55934026e the native getModuleNameKey owner and the seed macro both emit the 69-byte cached-key body, with different local statics. The resulting duplicate/selected findings are LINK-155. The approved destination is the existing Behavior/SlowDeathBehavior.cpp, not the current one-function Module/SlowDeathBehaviorPoolKey.cpp. This prerequisite does not replace the required supported TU merge.

A TU-local macro scope around only SlowDeathBehavior.h keeps getModuleNameKey declaration-only. Its Behavior/Die/Update dependencies are included before the override; push_macro/pop_macro restore the ordinary macro before later headers. Factory implementation, virtual slots and access remain identical. No shared header, private class copy, alias or pin is added.

Private before/after COFF proof retains both seed rows and all 62 remaining external code definitions/relocations. All 558 initialized data definitions remain identical, as do the two four-byte BSS slots for the separate memory-pool getter. Only the inline name-key body and its two local statics disappear; the existing strong native owner still owns its two real global slots in data_ledger.csv. BSS section.data is checked directly: read_object_symbol_bytes on a BSS zero file pointer reads the object header and is not a content comparison.

Normal seed build passes both rows. Strict preparation of seed plus strong owner passes all five rows, literal checks and EXACT owner EH. Fresh supported name_lane planning and current tu_skeleton routing precede any merge. Remaining broader UpdateModule disabled masks, crc, isDieApplicable identity, mixed donors and native class-layout prerequisites are retained. No census gain or final source-file reduction is claimed by this prerequisite.

Earlier vector cleanup publication a55934026e landed first attempt in 49.9 seconds after the account spacing wait. Its batch audit is INCONCLUSIVE against older index d249ce458a / outgoing base280160758f and missing current Common/0CreateAHeroManager21FE49.cpp consumer receipt. Carry that scope into the next scheduled census with these module providers. No maintainer-only runner is used.

Current paired preview clears the standalone name-key owner for78 authored bytes. The seed retains its four distinct disabled-mask/crc/isDieApplicable findings. This narrow preview is not final merge clearance or an updated census.
