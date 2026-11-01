# Living World record vector copy, 2026-11-01

Control: `46c1050380`; ordinary preview index `0d24c60eef` (09:19 UTC).

## Native identity and bounded repair

The 96-byte constructor at RVA `0x0052CD81` calls the 38-byte range helper
`0x0052C987`. That helper calls `_Construct<Rva004E194E>` at `0x0052C3D7`,
whose existing copy call reaches `0x0052BE96`. These providers already live
in the approved `LivingWorldCampaign.cpp` TU. The record has a vptr, two
integers, an AsciiString at +12 and a trailing byte, with total size 20.
The former SaveMapPreview view instead names a different native copy at
`0x002262E7`; equal element sizes did not establish identity.

The existing caller file now uses the target-owned record view and STLport's
native malloc allocator configuration. The constructor retains all 96 raw
bytes, changing only its two typed helper relocation names. Its complete
resolved bytes and EH graph are EXACT. The emitted range helper is 38 bytes;
the count base is the native 60-byte malloc form rather than the 59-byte
node-allocator form.

`pin_admission.py --add` admits the count-base ICF member at `0x004FF36C`,
using this matched source as its fold proof and recursively proving its
callees. The old SaveMapPreview range-copy pin at `0x0052C987` is removed;
the actual record's existing pin remains. Total pin-hatch count is unchanged.
`repair_queue.py retire identity` retires the caller's one wrong-identity key,
with zero remaining findings for this source.

No provider source, shared header, code row, source path or TU assignment is
changed. Original application-level record and vector names remain unknown.
The allocator accessor retains its existing AsciiString template spelling:
this change does not claim complete recovery of the vector's source type.

## Verification and limits

- Normal caller verification: 1/1, all 96 bytes exact; frozen scan clean.
- Strict caller/count-base/GameMemory cohort: 16/16 rows and 11 data rows.
- Read-only strict preparation of LivingWorldCampaign: 77/77 rows, six strings,
  two floats and existing verified EH-label renumberings. That source is held
  by another seat and was not edited.
- Whole-object proof: 10 external code definitions become 16; three retained
  definitions are identical, and only the caller changes symbolic code
  relocations. Six old SaveMapPreview helper definitions disappear and twelve
  actual-record helpers appear. See the complete name inventory.
- Ordinary three-source preview: all LINKS, 4,435 -> 4,531 authored bytes.
  Caller 0 -> 96; count-base provider stays 473 and campaign stays 3,962.
  This is a bounded prediction, not a new census or unique-byte measurement.

A private direct three-argument call to the neutral helper produced 92 bytes,
because it lost the native empty-tag argument. It was never placed in Code.
Using the actual four-argument STLport instantiation preserves that argument
and the native constructor. The private probe never wrote the shared match
cache. The supporting provider's three-argument neutral wrapper identity is
unchanged; its body remains the separately verified native range loop.

Wider affected-consumer selection and the next scheduled census remain the
publication audit's responsibility. No runtime or image-ownership result is
claimed.
