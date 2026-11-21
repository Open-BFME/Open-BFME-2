# Native shared 24-byte record

At source head9a39def1d3, tools/header_adopt_lane.py generated the shared
Rva001EB15A header from its native five-view contract, selected data+includes,
and applied all five private-view replacements. The generated size, field
offset and absence-of-vptr checks are retained. The contract has no queued
decisions. No row identity, source ownership, symbol binding or data admission
changed in this step.

The ordinary build passes145/145 existing code/EH rows. Native link_check
reports LINKS for each of the five sources and8,036->8,052 census-linked
bytes; the16-byte Carryover difference already existed before this header
adoption and is not new recovery credit. The earlier explicit54-byte record
destructor prerequisite changed COMDAT ANY2 to NODUP1; that separate banked
source change is not hidden as complete physical COFF equality.

The original UnitRevivalEntry served batch still has three unfinished provider
sources. This component prerequisite retires none of those queue rows and
adds no completed-task, new-body, unique-byte or runtime credit. No source
path deletion or TU merge is included. The latest complete image proof remains
source16a726a1c0, before the subsequent integration and record prerequisites;
the current source has not been executed.
