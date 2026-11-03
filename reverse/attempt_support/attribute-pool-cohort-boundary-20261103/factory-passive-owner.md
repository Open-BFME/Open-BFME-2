# AttributeModifierPoolUpdate: three-file replacement review

Bounded read-only review, 2026-11-03. Used the complete immutable originals in
this directory after observing the owning trial temporarily swap live Code.
No compilation, tracked edits, network, claims or alias/codegen experiment.

Original snapshots:

- ModuleFactoryInit.cpp: 931 lines, SHA256
  b874e0c2bfc69e2630b85f67ddf876ffc7f0207b1aca01c4d27ff9930c9f42d8.
- PassiveAreaEffectBehavior.cpp: 687 lines, SHA256
  9af0aa89db3e0dc223aac37c6e157444969e5e84540ce2201cd8aa5735696d59.
- AttributeModifierPoolUpdate.cpp: 1184 lines, SHA256
  77df6ac7b5beab26f9aebb9480b09634a435acb528debf0e955a87450b381f31.

## ModuleFactoryInit: callback-only use, inherited-header boundary

The whole source has 569 static-only class declarations, 309 registration
calls and one implementation, ModuleFactory::init. The target appears only at
line 60 (static declaration) and 798 (callback address passed to the existing
six-argument registration helper). The canonical static callback has exactly
the existing `Module *(Thing *, const ModuleData *)` contract. No target
instance, constructor, destructor, member access or base-pointer adjustment
occurs here. The callback registration itself needs no receiver cast or layout
inference.

The full header nevertheless imports canonical UpdateModule -> BehaviorModule
-> ObjectModule -> Module. The existing recorded include chain already loads
sweep PreRTS, donor Snapshot/BitFlags and sweep Common/Module through the
modulefactory ModuleFactory shim. Sweep Module uses `__MODULE_H_`; canonical
Module uses `__BFME2_MODULE_H_`, so a one-class include replacement does not
deduplicate that type. Snapshot is more subtle: donor and canonical copies
share `__SNAPSHOT_H_`, so the earlier donor three-slot/nonvirtual-destructor
surface can silently suppress canonical Snapshot. This requires coherent
ancestor/include adoption, not a callback signature change or a guard bypass.

## PassiveAreaEffectBehavior: one compatible call, unrelated lifetime collision

Original local target declaration (131-135) contains only
`void rva00403415(int *, int)`. Object's private finder returns the target pointer
(158), and the only method call (481-484) passes the +0x2C anti-category mask and
current frame+delay. The canonical signature matches exactly; preserve the
finder's complete/primary pool receiver and the 32-bit argument contract. No
pool allocation, destruction or member access occurs in this consumer.

However, lines 270-309 independently define BehaviorModuleBase,
BehaviorModuleOther, BehaviorModule, UpdateModuleInterface and UpdateModule.
The canonical target header imports conflicting definitions of the latter
three. These are live ancestors of PassiveAreaEffectBehavior, whose constructor
(~610), destructor (~635), xfer and update are implemented here. Removing these
local bases as incidental declarations changes its own tables, typed module
data access and member lifetimes; that is wider than replacing the pool class.
The derived placeholder virtual slots must not merely be appended to a larger
canonical base.

The local primary `template<int N> BitFlags` at 223 allocates seven words for
every N because this source only uses its BitFlags<69> view. Importing the
canonical UpdateModule contract also introduces BitFlags<11> as DisabledMaskType;
the local primary would make it 28 bytes instead of the target's four-byte mask.
There is no existing pool-call use of that return value here; it remains a
concrete ancestor/type prerequisite, not evidence to change the existing
BitFlags<69> consumer or to add an ABI cast.

## Owner TU: canonical storage view is not a lifetime-equivalent member model

This source already includes canonical BehaviorModule/UpdateModule (92/94), so
its principal boundary is the target's members rather than duplicate ancestors:

- Original target (111-134) owns `_STL::vector<Rva00297360Element>` at +0x20,
  maxFrame at +0x2C, `AttributeModifierCategoryFrame[15]` at +0x30 and counts
  at +0x6C. Vector base ctor/destructor specializations are deliberately opaque
  (77-79) so real C++ lifetimes produce native calls and EH.
- Empty target destructor at 696 still invokes the vector member destructor
  (native 403960) before UpdateModule. Constructor 682 implicitly constructs
  the vector through 211E58 before its EraseRange call. Canonical `m_field20`
  is only an eight-byte POD call/access view and `m_field28` a raw pointer:
  a literal class swap loses both automatic member lifetimes and cleanup.
- Original category element (105-109) has a zeroing constructor. Its array
  therefore emits native iterator 1423 and folded zero ctor 326BE6 before the
  explicit loop. Canonical `unsigned int m_field30[15]` has no such implicit
  construction. Equal storage size does not preserve this native call graph.
- Original local Rva002983DAVector (82-89) defines three pointer members;
  canonical header defines two under the same class name. Its used first two
  accessors are compatible storage reads, but direct inclusion conflicts until
  the duplicate view is removed/reconciled with proof.

Safe storage correspondences for ordinary consumers: m_maxFrame -> m_field2C,
m_poolCounts -> m_field6C, categoryFrames[i].frame -> m_field30[i], and vector
begin/end words -> m_field20.m_field00/m_field04 with capacity at m_field28.
These mappings do **not** supply vector methods, construction/destruction or
the category array's implicit constructor. The owner uses begin/end/erase/
push_back throughout rva00403382, rva00403448, rva00403744, addModifierToPool
and xfer. Do not convert live objects to POD fields and invoke destructors on
unconstructed typed objects merely to recover bytes.

Canonical target also declares update, disabled-mask getter, loadPostProcess
and GetSnapshotName overrides absent from the original owner class view. The
narrow current row lookup finds named update at 403CA8 in Tick, key at 403A61,
and nonvirtual name at 403A5B. It finds no exact-name matched row/pin for the
three disabled/load/name virtual spellings. This is existing provider/interface
cleanup, not uncovered native text. If adoption changes emitted tables from
pure/inherited entries to those names, prove each binding and undefined-provider
delta separately; masked ctor/dtor bytes cannot establish that closure.

The header's A8 extent, +20/+2C/+30/+6C storage and measured table addresses
are target-backed. That does not make its partial storage model a drop-in C++
owner lifetime declaration. Consumer-only adoptions may be independently sound
once their own ancestor boundaries are resolved; do not infer all nine can adopt
from success in the simpler clients. Stop this review here; owning trial results
and normal full-object/data/provider checks remain root's responsibility.
