# Tracker: minimal native-contract member-name alignment

Sicher: this private package is bound to source HEAD `8ceca1621406b9dac9f2ca826343fb741eea2c4a` and the unchanged generated-owner contract `reverse/class_contracts/Rva001EB15A.json`. Root owns production changes and all existing reservations. No production source, contract, header, registry, index, claim, or Git changes were made by this worker.

## Exact proposed change

Apply `MEMBER-ALIGNMENT.patch.txt` to `Code/GameEngine/Source/Common/RTS/UnitRevivalTracker.cpp`, or use the exact `CANDIDATE-SOURCE.cpp.txt` bytes. There are four line sites: five declared members `a,b,c,wide,text` become `m_00,m_04,m_08,m_wstr0C,m_str10`, and the one typed `UnitRevivalEntry::m_record.a` use becomes `m_record.m_00`. The record's existing `m_14`, every type, namespace, lifetime and initializer remain unchanged. Its constructors are declarations only in this TU; no direct initializer needs renaming. Unrelated `RevivalLogicFlags::setFlag(bool b)` and `RevivalStaticAsciiString(const char *text)` remain byte-for-byte unchanged.

These are existing offset-generated native contract names. This package makes no recovered-original-name claim and performs no token-global renaming.

## Exactly two authorized native compiler calls

`tu_skeleton.Verifier(source).matched(text, rows)` was used once for the original control and once for the single candidate, with native default/profile flags (`flags=None`), `BFME_OBJSTORE=off` and native adjacent dot-scratch/build-tu_skeleton outputs. `*-ARGS.json`, actual compiler sidecars, effective source and copied COFF objects preserve the complete calls and dependencies. All actually opened header hashes and command fingerprints were checked. No vendor, SDK, flag, guard, include-path or tool change was used.

Both objects pass 41/41 original rows, strict/unmasked, with no unresolved relocations, and all applicable EH checks EXACT. The complete runtime graph is equal: 79/79 nodes, all runtime bytes and bound relocations, external definitions, COMDAT selections, eight SafeSEH handlers, weak/default contracts, undefined symbol contracts, CRT sections and DIR32 bindings. Object file hashes differ; no raw whole-COFF hash-equality claim is made. Full evidence is in `RUN-RESULT.json` and `COMPLETE-RUNTIME-GRAPH.json`.

Only an isolated Python graph-reader namespace was corrected after the two compiles; the final graph was read from those same existing objects. There was no third compiler call or second candidate.

## Root's next normal step and limits

The current production source and contract hashes still equal the captured inputs. Native adjacent scratch sources were removed. This is source-name clarity only: **zero new recovered bodies and zero new C++ bytes**. Root still needs the normal production source application, native header-owner/adoption verification, required build/source gates and separate commit. This package does not assert that the fifth header-owner adoption or a new full link has already passed.

The conservative vendor pthread header-walk refusal is preserved as prior history; nothing here suppresses or weakens it. The change avoids needing the adopter's unsafe global field-token replacement. PC remains on.

## Frozen hashes

- Original source: `9642079319c16074a3d1485f13cf7eda9bb727e877efb75528dafba6793e67f3`
- Candidate source: `3c7711b37302cb47e2fd6dd4b0063165ba9044a889f72c39dd920c76555e034a`
- Contract: `b8f8ac879d69288fd82b1909733d531d39609176600555b55fcaaa2d66ae342a`
- Control COFF: `2e924847cba4cbae34be500bf48c80f15e962bb183ce037177dce55e24676e09`
- Candidate COFF: `a093a8f445fc59c5bf95e00fd816c34677feffb5271b61a49a3a9833a46e7593`

`MANIFEST.json` binds every package file and the unchanged input/helper hashes. Do not rerun the one-shot native compile script.
