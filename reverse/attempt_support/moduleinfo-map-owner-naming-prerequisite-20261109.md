# Two enclosing-template map accessors need reviewed identities

Read-only investigation at 3a7b59cb3d on 2026-11-09. No source, ledger, pin or
header queue row is changed for these bodies. These are existing matched
placeholder identities, not missing bodies or a byte-coverage regression.

| Body | Current source and identity | Current caller |
| --- | --- | --- |
| RVA0033C259,47B | Common/Thing/ModuleInfoRva0033C259.cpp; ?rva0033C259@ModuleInfo@@QBEMH@Z | GameLogic/Object/Update/AIUpdateInterfacePrivateCommands.cpp, call00268B64 |
| RVA0033C288,43B | Common/Thing/ModuleInfoRva0033C288.cpp; ?rva0033C288@ModuleInfo@@QBEPBHH@Z | GameLogic/Object/Update/AIUpdateInterface_chooseLocomotorSetExplicit.cpp, call00268A46 |

All paths above are below Code/GameEngine/Source/. Native evidence, independently
reproduced by the parent from the retail image: 00268A43 loads ECX from
[EAX+4], then00268A46 calls0033C288. At00268B61 the same load precedes the
0033C259 call at00268B64; its float result is stored at AIUpdate+0x1F8.
Caller context identifies the loaded pointer as Object's ThingTemplate pointer.
The descriptor result is consumed as a vector representation. The canonical
ModuleInfo header already records that+0x3A0/+0x3AC are enclosing-object fields,
not fields of its twelve-byte descriptor. ThingTemplate ownership is supported;
the float's original semantic name is not established by these bytes.

Donor facts, kept separate: the committed BFME1 code still calls a generated
Gen_001418F0::bfmeFindFloat for the analogous float map and a reconstructed
BfmeThingTemplate::findLocomotorTemplateVector wrapper around Gen_00141940's
lookup. ZH's real findLocomotorTemplateVector belongs to AIUpdateModuleData,
not ThingTemplate. These facts supply no canonical BFME2 getter names. In
particular, do not claim the float is called speed or cite canonical:bfme1.

Supported next step: infer and independently approve readable identifiers with
their final owner/signatures and prepared C++, then use ordinary function
--respell through tools/rename.py and the naming workflow. The current --to-class
route handles placeholder virtual-slot owners; it does not move these
nonvirtual members of readable, registered ModuleInfo. Same-identifier owner
changes encounter the signature-only/new-placeholder restrictions. No gate
edit, wrapper, invented donor name or beyond-object cast is a remedy.

The existing pin ?rva0033C259@ThingTemplate@@QBEMH@Z at RVA0033C259 has a stale
"body unrowed" note (reverse/symbols.csv around line6152). Reconcile it through
the supported plan and prove both caller/provider closures; never add another
name by hand. The current index has exactly one old-name provider and one live
caller for each accessor. All four cached objects fail strict currency in this
read-only review, so this is not current compiler/link verification.

No foreign source/RVA/class claim conflict was found during inspection, but
claims must be reacquired fresh for implementation. tools/rename.py itself is
reserved by swarm-seat6; it is not edited here. The blocked work remains queued.
Local parent retail proof: build/thingtemplate-header-cohort-20261109/
map-native-caller-proof.json. No new byte match, link gain or runtime outcome
is claimed. The review used the committed reference only, with no upstream fetch.
