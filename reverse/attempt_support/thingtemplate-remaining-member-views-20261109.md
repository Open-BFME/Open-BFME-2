# Six more ThingTemplate consumers use the shared layout

Inspected at f50e511dac on 2026-11-09. These complete source files replace
their private ThingTemplate bodies with the existing canonical header:

- ThingTemplateParseModuleName.cpp retains its signed +0x5F8 mode, +0x64 name,
  +0x94/+0x98 replacement strings and four ModuleInfo descriptors +0x2E4..308.
- ThingTemplateSetCopiedFromDefault.cpp retains four module calls, both copied
  flags, the +0x484 next pointer, +0x5D8 ID, +0x64 name and armor-record owner
  reset. Its existing private ModuleInfo provider remains unchanged and queued.
- ThingTemplateValidate.cpp also removes its private StringBase declaration.
  Non-owning shared-string views retain shadow selection and the four wide
  string words at +0x30/+0x38/+0x40/+0x58 within canonical eight-byte records.
- ThingTemplate_resolveNames.cpp retains the +0x324 prerequisite descriptor,
  byte +2 of the canonical kind mask and +0x5E6 build-facility flag. Its existing
  mask value2 becomes a function-local constant.
- Rva0033E102Rebuild.cpp keeps its +0x370 record vector, +0x37C finder, +0x5E9
  flag and temporary's genuine cleanup.
- ThingTemplateRva0033D331.cpp keeps its +0x358 record vector, +0x364 finder
  and +0x5EA flag. The final finder access names the canonical storage rather
  than repeating the literal enclosing-object offset.

Native field accesses, operations and retained lifetimes are target facts.
Existing donor commentary is retained separately; no donor is imported here.
The views recover neither original member names beyond the header nor complete
container lifetimes/original TUs. Shared headers, source paths, all ledger
identities/extents, pins, aliases declared in source and compiler flags remain.

All six first private trials pass all fifteen native rows and three exact EH
graphs. Normal build.sh passes15/15, seven literals and three empty-string
references; there are no float/import obligations. Frozen checks pass before
and after. Three old compiler $L labels renumber, but the trusted parent-EH
proof resolves them to the same retail funclets; no ledger or pin is rewritten.
Six current-input link previews against index5b5011469d (2026-11-09 19:12,
census9b9d058303 at17:41) preserve726+306+106+212+131+101 =1582 linked bytes.
Owning acceptance retires six header rows, leaving68 ThingTemplate consumers
locally. All six changed sources have strict reusable receipts.

The before/private and final/normal objects retain44 COMDAT payloads/sizes
identically. No definition or undefined reference is added. Weak defaults and
/INCLUDE directives are unchanged. The sole removed definition is the old
?COMMANDCENTER_MASK@ThingTemplate@@2HB: the fresh index has this source as its
only emitter and toucher; current Code has only the new local constant, and
narrow function/pin/data/export searches have no binding to the old spelling.
The initial local provider assertion exposed this emitted incidental constant;
its removal is recorded explicitly after that consumer audit. The native
condition still uses the same folded value2.

Four objects inherit the canonical AsciiString header's seven existing alias
directives; every identical pair already exists in the index. No alias is
declared/removed or admitted here, and no counted hatch grows. The other two
objects already included that header, so their directives do not change.

Local evidence: build/thingtemplate-header-cohort-20261109/{remaining-sources.json,
probe-remaining.py,remaining-private-proof.json,remaining-private-eh.json,
remaining-build.log,remaining-frozen-*.log,remaining-link.log,
remaining-accept.log,remaining-prepare.log,prove-remaining-providers.py,
remaining-provider-diff.json,resolve-mask-provider-index.json}. Historical
before/candidate snapshots are not to be overwritten by rerunning probes.

The remaining ModuleInfo queue row in ThingTemplateSetCopiedFromDefault.cpp
needs its real67-byte setCopiedFromDefault provider preserved when adopting
ModuleInfoClass.h; a textual class swap would erase it. Other ThingTemplate
constructor/member-lifetime, static-table-access and W3D prerequisites remain.
The preceding publication's broad audit remains INCONCLUSIVE for unchanged
BfmeConv975.cpp at index5b5011469d/basef9b89f6e63. Carry this into the next
census. No new global linking coverage, real image or runtime result is claimed.
