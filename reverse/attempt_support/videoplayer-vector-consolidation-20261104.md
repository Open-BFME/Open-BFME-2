# VideoPlayer vector destructor consolidation

Inspected base: `074ded58448006a7e7d23fd0d3d1afdb2f0a8e08`.

## Compiler-context prerequisite

`VideoPlayer.cpp` suppressed instantiation of the record vector destructor with
an explicit specialization declaration. Removing that declaration allows the
existing destructor donor's explicit instantiation to compile in the TU.
The donor requires `/EHs`: `/EHsc` omits the retail destructor's EH state -1
store before deallocation. These are target byte/codegen observations, not
evidence of an original source spelling or external donor layout.

The prerequisite changes the TU from `/EHsc` to `/EHs` and removes only the
specialization declaration. `./build.sh Code/GameEngine/Source/GameClient/VideoPlayer.cpp`
passes all 34 existing rows. `find_declared_unmatched.py` reports all defined
functions matched. Isolated `tu_skeleton.Verifier` builds before/after have
identical normalized `link_census.object_facts`: 73 COMDAT copies, 10 defined
symbols, 29 undefined symbols and one weak alias; no added, removed or changed
facts in any of those sets. No link-wide alias is removed.

The supported merge dry-run accepts `Rva00689DB0Finish.cpp` with these changes.
It checks the destructor at 0x00689DB0 against its 103 retail bytes, with the
donor's EH rows at 0x007A7BA0 and 0x007A7BA8 carried with their parent.
The remaining donors are rejected for flag overrides, conflicting
SubsystemInterface definitions, or the element destructor's pointer view.
No census increase is claimed.
