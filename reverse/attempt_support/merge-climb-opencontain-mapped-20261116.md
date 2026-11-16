# OpenContain mapped-struct adoption blocked

Frozen base d1432cf653a231a82eb95196e2efb27f15b9c393. Goal: reconcile the local Rva00462D08Mapped before the two approved destructor donors merge. The existing header and local struct both hold unsigned int m_bits; no header edit was proposed.

Normal baseline: 30/30 rows; strict link_check prepare-current passed; own link_check verdict LINKS, 1,825 -> 1,825 linked bytes. Fresh index SHA256 a7b66e94069f7511b81c03a7fb2a51180580f206a8212ebcbaa784c450d8c7d2 (2026-11-16 00:26, 40687a0659).

Supported command:
python3 tools/header_adopt_lane.py adopt --class Rva00462D08Mapped --header Code/GameEngine/Include/GameLogic/Module/Rva00462D08Mapped.h --apply Code/GameEngine/Source/GameLogic/Object/Contain/OpenContain.cpp

It exits 1: field renames: the header's layout: compile failed C2678 binary '<', const Rva00463D9BElement has no acceptable operator. Source restored; git tree clean before recording. No repaired byte/link result, merge, class-safety claim, or proven false-reject claim. Do not bypass the supported route. Diagnose the probe/declaration context before retrying.

Full logs and before-object snapshot: srv1 ~/bfme2-ops/swarm/sweeps/merge-climb/opencontain-mapped/. No Boat allocation or spend. This records-only commit remains local and must ride a later substantive batch; no go request.
