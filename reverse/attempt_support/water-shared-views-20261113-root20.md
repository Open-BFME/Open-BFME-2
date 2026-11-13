# Shared water class declarations

Four private declarations are removed through normal header_adopt_lane.adopt:
WaterTracksRenderSystem in Rva000FE1ACUpdate.cpp, VertexMaterialClass in
W3DWaterTracks.cpp, and CameraClass/WW3D in the flush unit. The update reads
its canonical used-list pointer through the existing opaque FeNode projection;
this does not identify FeNode as WaterTracksObj. Timing globals, intrinsic
barrier and iteration order stay the same. The full water header is unchanged.

Camera integration adds genuine PersistFactoryClass/ChunkSaveClass/
ChunkLoadClass forward declarations needed by rendobj.h. WW3D integration
removes unused layer.h, whose LayerListClass typedef conflicts with the
canonical forward declaration. The existing shader include order is retained.

All31 function rows and4 data rows pass across4 sources, including the
unchanged allocation/init consumer. All127 COMDAT fingerprints and sizes
agree using link_census's existing per-TU anonymous-namespace normalization.
Exactly2 unused BoundsValue helper names change namespace salt. Their37B
constructor and25B assignment retain fingerprints7476688645e4/79571e26f4e7,
with zero current incoming/outgoing relocations or weak bindings. The whole
BoundsValue namespace block is unchanged, and a local-object/reference audit
found no outside binding. This is not a raw old/new object-graph equality
claim: the old complete object was not retained. Other125 names are unchanged.

All four owning acceptance verdicts returned PASS and retired exactly their
four queue entries. Strict preparation verifies all four source providers;
its own verdict explicitly does not establish LINK closure. Three WaterTracksRenderSystem views retain separate preparer
prerequisites (field scope and whole-storage proof). RenderObjClass additionally
fails a scratch22/24 native test after diagnostic declarations resolve its
include errors; its direct native Get_User_Data call disappears. Those trials
are not applied. No body coverage or authoritative game-link/runtime gain is
claimed by these shared declarations.
