# Rva0056B188 listener override prerequisites

Inspected `b9047f2d164`, isolated `build/r20`. No source/header/ledger adoption,
row move, pin, alias or new body was applied. Existing constructor and destructor
emitters pass `./build.sh`: 16/16 rows, including their parent-owned EH actions.

The served class has two bridged secondary tables. Direct native reads establish:

| Table RVA | Object displacement | Native extent | Missing derived targets |
| --- | ---: | ---: | --- |
| `0086D35C` | `14` | 16B, 4 slots | slot0 `0056B1F2`; slot2 `0056AA22` |
| `0086D36C` | `8` | 60B, 15 slots | slot7 `0056AA32`; slot9 `0056AA54`; slot10 `0050BD7C` |

Primary `0086D3A8` has five slots and already matches. Native construction proves
the owner at +18, value at +1C, flag at +20 and the three bases at +0/+8/+14.
`LivingWorldTutorial.cpp` allocates the same 36-byte instance and calls its
constructor. Its role is a tutorial task listener; the original class name and
generic callback parameter types remain unknown.

Existing physical row owners:

| RVA / size | Current source | Current prototype |
| --- | --- | --- |
| `56B1F2` / 38 | `Common/Rva0056B1F2Release.cpp` | nonvirtual member, `void(void*)` |
| `56AA22` / 16 | `Common/Rva0056AA32Guard.cpp` | nonvirtual member, `void(int,int)` |
| `56AA32` / 34 | same mixed file | nonvirtual member, `int(const Rva004E0625*)` |
| `56AA54` / 82 | `Common/Rva0056AA54Probe.cpp` | free `__stdcall bool(void*,void*)` |
| `50BD7C` / 5 | `Common/VslotSmallBodiesAM.cpp` | nonvirtual member, `bool(int,int)`; shared fold |

The first four addresses each occur once in native `.rdata`/`.data`; `56AA22`
has no foreign-table obstruction. B218 uses `56AAA6`, not `56AA22`. The true
leaf at `50BD7C` is shared; do not fold its mixed placeholder class wholesale.

## Prototype boundary

Registered observer `Rva0056B188Second` declares slot0(int). Its empty native
RET4 callback proves one argument word, not its original type. The derived
`56B1F2` body compares that word with the stored owner pointer and unregisters
the owner; this does not establish the generic base's original C++ prototype.

Read-only calls to the existing owning planners reproduce both refusals:
`rename.to_class_symbol` refuses moving `...QAEXPAX@Z` to
`?slot0@Rva0056B188@@UAEXH@Z`; `signature_only_change` refuses the same identifier's
PAX-to-H change because it removes type codes. No vote-free supported alignment
was found. Changing the registered header or adding a duplicate identity merely
to avoid those checks would not resolve the proof boundary.

The second table additionally needs pointer/word and int/bool reconciliation for
slot7, a supported ordinary virtual-member identity route for the free stdcall
slot9, and a proven shared-fold route for slot10. Preserve slot9's actual SpawnArmy
and compiler-owned EH providers. No bool-codegen or convention equivalence is
claimed without a coherent prepared build.

## Next coherent experiment

First establish a supported, reviewed prototype/identity transaction preserving
the uncertainty above. Prepare the constructor, destructor, release provider and
mixed guard source together; retain all unrelated guard bodies. Include
`LivingWorldTutorial.cpp` when sharing the complete derived declaration. The
slot9 probe and shared true-leaf provider expand the eventual full cohort.
Verify native this-adjustment, full row/EH graphs, both complete secondary
tables and unchanged other COMDATs. Keep rows in approved units and preserve
the existing source coverage; no new aliases or table ledger deletions.

Scratch evidence: `build/root-b188-prototype-proof.json`,
`build/root-b188-rows.json`, `build/root-b188-baseline.log`. The pass remains a
published authoritative real link that neither bridges nor refuses both tables.
No measurement was launched and no bridge retirement is claimed.
