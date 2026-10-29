# GameSpy colour-table ownership

Checked 2026-10-29 at BFME 2 upstream `d701d875b`, with the previously
verified BFME 1 reference `e42b9782`.

## Target facts

The matched `INI::parseOnlineChatColorDefinition` at RVA `0x001EF471`
passes the colour storage at VA `0x00DB9198` and the field table at
VA `0x00BE0428` to `INI::initFromINI`.

The retail field table has 29 consecutive colour fields, offsets 0 through
112 in steps of four, followed by a zero 16-byte terminator. Every field
uses the same parser through VA `0x0042F3FE`. In particular:

| Field key | Index | Byte offset |
| --- | ---: | ---: |
| OfflinePlayerBuddy | 9 | 36 |
| PlayerSelf | 10 | 40 |
| OfflinePlayerIgnored | 12 | 48 |
| ChatNormal | 13 | 52 |
| MOTDHeading | 28 | 112 |

The earlier 27-element source omitted the two offline fields and several
retail defaults differed. The replacement keeps the existing enum names,
with explicit gaps at 9 and 12: the missing original C++ enumerator
spellings have not been established. The new parser entries use the
retail keys and their witnessed numeric slots.

The array's complete 116-byte initializer, including alpha values and the
zero final colour, now equals retail. MSVC's sizeof probe independently
evaluates `sizeof(::GameSpyColor)` to 116. A separate COFF/retail comparison
checks all 29 parser-table names, offsets, parser relocations (including
ILT routing) and the null terminator.

## Source and ownership

The GameSpyColor identifier and the initial source structure come from the
existing Zero Hour-derived Chat.cpp and PeerDefs.h. BFME 2's field names,
positions, defaults and extent above come from its own image; no reason
for its particular defaults is inferred.

Two matched scalar data rows had separately claimed the first and third
array elements, through `g_00DB9198` and `g_00DB91A0`. Their definitions
are removed. The lobby combo-box reader now uses `GameSpyColor[2]`, and
one matched GameSpyColor row owns the complete array in Chat.cpp.
The ledger rewrite preserves the original row terminators.

This also removes the unbaselined GameSpyColor finding that prevented the
data-retirement tool from retiring AptOnlineCustomMatchCallbacks.cpp's
obsolete TheRva00222A8BTarget key. That unit already uses the canonical
window-manager datum; no new finding is added to a baseline.

Scoped verification passes all 140 rows of the provider, the two edited
consumers and that callback unit. Data checking reports zero findings for
those sources. The full gate at upstream `d701d875b` plus this repair passes
98,943 function rows and 2,230 data rows, with every reference, pin, module,
source-claim and no-op-patch check green. The separate getter-alias admission
prerequisite is recorded in `global-getter-alias-admission-20261029.md`;
that trial was reverted.

The pre-commit code-identity shadow check still reports 14 out-of-register
findings in existing bindings and template definitions in the edited sources.
The reported callee bindings and template definitions are unchanged by this repair;
no function-identity cleanup or census clearance is claimed.

The ordinary outgoing audit at base `91a3a60aa` was INCONCLUSIVE: index
`d92e7e6635` predates that base, and 50 source objects lack current census
receipts (first: `Common/AptOnlineCustomMatch_PopulateLobbyComboBox.cpp`).
The carried byte gate and cross-source checks passed; linking remains
UNVERIFIED until current census objects cover the provider/consumer scope.

Carry the changed array owner, the two removed scalar providers and all
colour readers into the next normal census. No census increase in linked
bytes or NOT OURS measurement is claimed by this repair.
