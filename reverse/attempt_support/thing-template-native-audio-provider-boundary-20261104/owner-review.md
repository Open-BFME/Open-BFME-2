# ThingTemplate audio/list helper ownership review

Bounded read-only owner/type review. Read current exact ledger/pin/TU entries, whole small existing hint/subscript/list-copy/reference-insert owners, narrow HotKey declarations and relevant attempts/obstacle history. ThingTemplate's live audio body/calls and current object/provider freshness were not inspected; those belong to the parent. No build, claims, network or tracked edits. All tracked reads stopped before this report.

## 002A12E1 is already covered by a proper list-family body

The current ThingTemplate row names `pair<AsciiString,AudioEventRTS>::~pair`,53B at002A12E1. Separate existing row48990 already owns the full53B at the same address under `pair<const AsciiString,TreeHintOpaque002A484A>::~pair` in `Code/Libraries/Source/WWVegas/WWLib/stlport_rb_tree_subscript_002a6a2d.cpp`, with exact gen-alias notes: list-base4EC395 plus narrow-string release36410 relocations twin the older owner. This is existing covered code, not a lost destructor requiring a new one-function source.

Recorded native teardown destroys the mapped second field at+4 through the folded list base, then the first string. That evidence contradicts treating this particular pair's second as a0x88 audio event. Existing wrong AudioEvent pins or a masked-byte placement do not prove the application type. The generic Gen_uw destructor pin to2A12E1 likewise provides no class identity.

The completed existing family is:

| RVA / extent | Existing operation / current source |
|---|---|
|2A1383 /88B|list<SuperweaponInfo*> copy, stlport_list_superweaponinfo_copy.cpp|
|2A1538 /61B|pair copy, stlport_rb_tree_hint_002a5895.cpp|
|2A1CC9 /57B|key + mapped-list pair constructor, same hint source|
|2A1EC8 /45B|pair _Construct, same hint source|
|2A42B6 /34B|tree _M_create_node, same hint source|
|2A484A /148B|tree _M_insert, same hint source|
|2A48DE /151B|unique insert, same hint source|
|2A5895 /443B|hinted insert, same hint source|
|2A618C /29B|map hinted wrapper, same hint source|
|2A6A2D /149B|map subscript, stlport_rb_tree_subscript_002a6a2d.cpp|
|2A12E1 /53B|typed list-mapped pair destructor alias, same subscript source|
|200667 /5B|TreeHintOpaque destructor fold, same subscript source|
|221B8D /49B|typed lower-bound alias, same subscript source|

The subscript parent handler7755D3/10 and cleanups7755C3/8 and7755CB/8 are already rowed. In particular, prior missing-binding attempts49641/89387 are superseded by landed90530/90531: opaque destructor200667 and its cleanup were admitted. The old ThingTemplate parent handler774EB7/10 and cleanup774EAF/8 are separate existing rows; main-body alias coverage does not automatically dispose of those companions if the parent changes ownership.

## Exact existing type contracts and limits

Hint source models an eight-byte pair: four-byte AsciiString key plus a four-byte mapped object, constructed at node+0x10 in a24-byte node. Comparison reaches AsciiString operator<5598C. Its mapped copy delegates to complete list copy2A1383. Subscript source uses actual `_STL::list<int>` inheritance to obtain the native default/copy/destructor lifetime and suppress the extra placement-new EH state. It declares existing pair/hinted-insert operations instead of inventing forwarding bodies.

The source spellings are not complete original application type recovery. Hint/list-copy comments explicitly say SuperweaponInfo* is carried from ZH InGameUI.h; target evidence establishes four-byte elements and the native list operation. Subscript keeps application identity opaque and uses list<int> as an ABI/lifetime view. These existing views do not authorize new arbitrary casts or treating their different source spellings as a newly proved original class. No TreeHintOpaque002A484A canonical registration was found in the narrow registry lookup.

## 00358E9F belongs to the distinct HotKey tree family

Current ThingTemplate has the148B _M_insert row358E9F spelled with AsciiString/AudioEventRTS. Its actual neighbouring family already exists elsewhere:

- HotKey.cpp owns unique-insert359032/151B for Rva00359032Value, and a direct tree wrapper359218/20B.
- StlSweepR3Rva00359032.cpp owns the same151B under opaque Rva00359032Record and the complete node constructor358DA0/34B through a documented ICF admission.
- The Value view is8 bytes: unsigned string representation+0 and opaque pointer+4. Nearby HotKey Rva00358B65 destruction exposes an AsciiString followed by TargetRef00217D4C*, providing a distinct string/reference lifetime context.
- The reference Record view is opaque char[8] with declared copy/destruction, comparison via established AsciiString operator<5598C, and construction routed to existing358CA0. It expressly calls element identity donor inference.
- Value and Record `_M_insert` names are already pinned to358E9F. No separately rowed proper-typed _M_insert body at that address was found: the current covered148B owner is still the ThingTemplate AudioEvent spelling. The verified caller's native call displacement establishes its target, not the original application type by itself.

Thus the HotKey family supplies existing operation/type context and node/unique-insert coverage; it is not the same owner as the InGameUI list tree at2A484A merely because both _M_insert bodies have148-byte extents. This review makes no provider-freshness, same-body or alias-equivalence claim for the two helpers.

## Current approved routing

Committed tu_map approves2A12E1 and the listed InGameUI copy/insert/subscript addresses to `Code/GameEngine/Source/GameClient/InGameUI.cpp`. It approves358DA0/358E9F/359032 to `Code/GameEngine/Source/GameClient/MessageStream/HotKey.cpp`. Those address assignments are current routing facts, not permission to move rows arbitrarily into existing WWLib helper sources. The existing physical owner/alias files and current source-recovery approval are different facts. A folded helper's representative address also does not establish its original TU.

The nine-method cleanup cf60dfc838 was not repeated. Remaining work is the parent's bounded current audio/list identity, metadata, binding and provider review. No new original name, cast, pin, alias, row transfer, byte proof or full-unit clearance is proposed here.
