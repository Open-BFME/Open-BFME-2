# InstantDeathBehavior native field table (2026-11-04, codex4)

Inspected base: `cab1cca4c5`. Scope: the seed
`Code/GameEngine/Source/GameLogic/Object/Behavior/InstantDeathBehavior.cpp`.
No new bytes, census gain or full-game link is claimed.

## Target facts and change

Retail parser RVA 0x0045D35F (34 bytes) calls DieMuxData::getFieldParse at
0x004CE52E and MultiIniFieldParse::add at 0x0002BC6E, first with extra offset
8 and then with table VA 0x00C41FA8 and offset 0. That table has four
16-byte entries and a zero terminator:

| Token | Callback RVA | Offset |
| --- | --- | --- |
| FX | 0x00339B9A | 0x38 |
| OCL | 0x0045D1BD | 0 |
| Weapon | 0x0045D200 | 0 |
| Sound | 0x0045D2F6 | 0 |

The former seed used ZH headers, three donor callbacks and no Sound entry.
Replace that context with canonical FieldParse/DestroyDieModuleData headers
and declarations for the existing rowed callbacks. Preserve the constructor's
existing element-neutral vector views, without claiming recovered element
identities. Remove the donor-only destructor, crc, xfer and loadPostProcess
bodies; none has a function row or pin under that name. Their four registered
present-unmatched hatches are removed through hatch_counters.py --update.
No /alternatename, pin or code-identity register changes.

## Verification and limits

- ./build.sh: **1/1 byte-exact**; string/float/import checks pass.
- find_declared_unmatched.py: all definitions matched, before and after.
- link_check.py --prepare-current: strict reusable provider receipt passes.
- link_check.py: **LINKS**, unchanged **34 -> 34 bytes**, against census index
  2026-11-04 07:28 at `a62ac1c10b`.
- Both data_check.py modes: zero findings/second names/unjudged rows.
- Read the compiled table through build.read_object_symbol_bytes (read-only):
  **80 bytes**, eight DIR32 relocations to the four retail token literals and
  existing rowed callbacks, with exact offsets and a zero terminator.
- Supported planner records the original retail source path at string RVA
  0x00841EB8. This proves the path, not donor layout or code identity.
- tu_skeleton --merge --dry-run changes accepted donors from zero to the
  pool-key, behavior constructor and module-data constructor (**7 rows** with
  the seed). Its link guard passes for these census-linked inputs. No move
  is applied in this prerequisite commit.
- Staged link_batch_audit exits 2 **INCONCLUSIVE**: census index `a62ac1c10b`
  differs from the outgoing base; affected consumer
  `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
  receipt. This consumer scope must carry into the next scheduled census;
  no batch-wide clearance or consumer-link gain is claimed.

Remaining: apply the verified three-donor merge separately. Parser/onDie
views still disagree on member names and element types; module-data destructor
composition fails bytes. Keep both mixed sources in place. LINK-068's
DieModule table/provider cleanup remains open; this source still calls its
rowed DieMuxData::getFieldParse, now through the native declaration.
No nightly, link-cycle or smoke runner was started. There are no source-path
moves in this prerequisite commit.
