# Xfer identity prerequisites, 2026-10-30

No production source is changed and no header key, matched byte or linked unit
is claimed. This handoff adds native evidence to the existing XferSaveOpen /
autosave / loader decisions. The served XferSaveOpen still verifies its complete
169-byte body and retains LINKS/169 bytes.

## Save-stream runtime identity

The stream object passed to XferSave::Open is demonstrably in the File family.
Native sendHero calls factory 6023C1 at 4D025C and passes the unchanged result
to Open60D10A at 4D027D. The factory constructs MemoryWriteFile at 602316;
602327 invokes File's constructor6024FD and60232E installs tableC7A7B8.
Its slot4 is the existing139-byte MemoryWriteFile::write6021CA, taking
(const void*,int), returning int, RET8. PersistentStorage independently
passes the same factory result through556885/5568AD/5568B5.

These are target dataflow/table facts. Existing ledger owner names identify
the matched providers; they do not uniquely recover the original static
formal spelling. A File-family call view is supported. Canonical serializer
Xfer's slot4 is IsLightCRC()const, with no argument and bool return, so merely
adopting that header here would misidentify the stream.

Nine direct Open declarations occur in XferSaveOpen, XferSaveChain,
MilesAudioManager, GameLogicInit, PersistentStorageThread,
ConnectionManager_heroData, CreateAHeroHero, Rva002DBC97Get and
Rva0052B4B6XferOpen. GameLogicGetCRC additionally declares the Chain wrapper.
Three row names encode the false stream type: Open60D10A, Chain60D4C9 and
the MD5 wrapper52B4B6. Genuine serializer Xfer parameters in those same files
must remain separate. Reconcile the whole typed call chain before changing
the row signatures; no pin/alias is a substitute for a function definition.

## Loader/autosave boundary

The existing loader tableC7AF18 has39 slots, with block methods at5/6/7
(60C629/60C469/60C6F6) and XferLoad::XferImpl60C7AD at38. The corresponding
block-method rows currently have base-scoped lowercase Xfer names.
Rva0060C5FA's47-byte constructor is a flat32-byte state initializer with no
C++ base clause: table0, opaque args4/8/C, loading flag10, stream14, count18,
current1C. Keep this construction/layout evidence distinct from an assumed
original class hierarchy or recovered constructor signature.

A private autosave adoption compiles but produces three new unresolved direct
calls: Rva0060C5FA::BeginBlock/EndBlock/SkipBlock. Those declarations are not
definitions, and their parent cannot verify exactly. The original production
source remains intact. Do not land the speculative view, add pins, or suppress
the byte/EH checks. Correct block-method ownership/call bindings first.

The canonical slot38 spelling XferData has zero rowed definitions and no
implementation bodies. A coordinated compatibility-API respelling to XferImpl
would affect nine declaration-only overrides across eight canonical consumers,
66 calls across three consumers, the shared header and one private family
declaration. Preserve the existing real XferLoad and XferMD5CRC XferImpl rows
and their distinct signatures. That respelling alone does not fix the loader
state placement, block-method ownership or false save-stream type.

## Reservation boundary and next pass

The attempted API-consumer reservation acquired11 scopes but correctly refused
MilesAudioManager.cpp and PersistentStorageThread.cpp, held by other seats.
No source/header/ledger edit was attempted. Respect those reservations; a
future coherent pass should claim the affected scopes before working on them.
The existing FamilyDeletingDtors EmitVtableTag constructor prerequisite is
also unchanged. All four Xfer header keys remain open.

`native-proof.json` records exact instruction bytes, both relevant tables,
current matched-owner facts and the held paths. Private experimental source
stays under build/xfer-autosave-20261030 and is not progress.
