### Render2DSentence glyph surface preview refresh (2026-10-28)

Status: selected-copy repair already landed; census confirmation pending.
At base `2502c74f7152`, the published index remains `d92e7e6635`. The glyph
surface unit alone reports selected W3DRadarResetSurface assignment and
PendingSurfaceStruct deleting-destructor conflicts. Including the current
Render2DSentenceDrawBFME2.cpp in the same preview changes the glyph unit to
LINKS for 777 authored bytes, consistent with the earlier renderer correction
below. The Draw unit itself still reports an unproven Add_Quad selected copy;
this preview does not establish its closure. Carry both units and their selected
providers into the next scheduled census. No measured link gain is claimed.
