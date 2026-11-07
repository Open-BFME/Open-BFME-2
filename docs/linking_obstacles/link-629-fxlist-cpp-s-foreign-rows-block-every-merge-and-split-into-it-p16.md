### LINK-629: FXList.cpp's foreign rows block every merge and split into it (P16)
Status: Blocked (tooling / tu_map question). Updated: 2026-11-07; inspected revision: fbdc0dccd0 (static-defects lane, P16).

Evidence / affected units: Code/GameEngine/Source/GameClient/FXList.cpp, the TU tu_map approves for the
P16 rows (doFXObj@ParticleSystemFXNugget 0x001E24DC, ??0ParticleSystemFXNugget@@QAE@XZ 0x001E0AEF with its
funclets, parse@ParticleSystemFXNugget 0x001E264F). See fxlist-cpp-unit-link-prerequisites-2026-10-31.md for
the P16 cause. `tools/tu_skeleton.py --merge FXList.cpp --dry-run` and every
`--split <donor> --for FXList.cpp --dry-run` refuse with "TU path exists and holds rows of another TU (split it
first)". FXList.cpp holds 7 matched rows: 3 approved for FXList.cpp, and these 4.

- 0x0052BD3A `??0FXList@@QAE@ABV0@@Z` (31 B), tu_map approved for LivingWorldCampaign.cpp (C=0x0052BBF3..0x0052BD59).
  - The row is compiler-generated, with no source body, and its identity is weak. It was placed by a masked
    whole-.text search of the compiled body ("single hit"), and re_attempts.log 0x0052BD3A records it.
  - Its 31 retail bytes install vtable 0x00C61A20 and copy a string at +4. Zero Hour's FXList has no vtable,
    so FXList.cpp's Zero Hour class cannot be what retail compiled here.
  - `--split FXList.cpp --for LivingWorldCampaign.cpp --dry-run` carries no copy-ctor body. It carries the whole
    714-line Zero Hour FXList.cpp (its /FIzh_ascii.h flag line, every nugget class and its inline bodies), and
    fails compiling: `'calcDist': identifier not found`. The tool copies a file-local helper only for carved
    bodies, not for the in-class inline TracerFXNugget::doFX that calls it.
  - Not carved. Moving the Zero Hour port into LivingWorldCampaign.cpp would not be an honest carve. The row
    needs its identity proven (whose 0xC61A20 vtable, what string member) before it has a body to move.
- 0x0060CF5A `?_M_delete_node@?$hashtable@U?$pair@$$CBW4NameKeyType@@VFXList@@@...` (28 B) and
  0x0060CFB6 `?clear@?$hashtable@...FXList...` (73 B), tu_map approved for XferSave.cpp (C=0x0060CE41..0x0060CFFF).
  - These are STLport template COMDATs FXList.cpp emits through its hash_map<NameKeyType, FXList>.
  - The split refuses both: "no definition spells its name". A template instantiation has no carvable body,
    so a carve cannot move them.
  - Question for a tooling seat: should tu_map treat these instantiations as homeless (follow the file that
    emits them), or should the split tool place them by emitting unit? The consolidation lane does not change
    tu_map.csv (AGENTS.md).
- 0x0023DAA5 `?clear@?$_List_base@PAVFXNugget@@...` (39 B), the row the split listing shows as "(no approved TU)".
  - This is a second ledger row at an address whose tu_map identity is stlport_list_int_o1.cpp's row,
    approved for GameLogic.cpp, so it is an ICF alias.
  - The merge's mixed check already ignores it: the dry run counts FXList.cpp as mixed by 3, not 4. It is not
    a blocker, recorded so it is not chased.

Completed: none. Nothing was carved or edited; dry runs only.

Remaining / next check:
- The tooling or tu_map decision on the two hashtable rows.
- An identity proof for 0x0052BD3A.
- Then `--split FXList.cpp --for XferSave.cpp` and `--for LivingWorldCampaign.cpp` (or the rows' new homes),
  after which FXList.cpp is no longer mixed.

Measured separately for P16 (static-defects lane, 2026-11-07, scratch only):
- FXList.cpp's flags are not the wall. Its `// cl:` line builds all 34 FXListNuggetParse.cpp rows exact.
- The wall is its Zero Hour seed. Composed with the byte-proven BFME 2 donors, the seed's Zero Hour
  definitions of FieldParse/MultiIniFieldParse, Coord3D, GameClientRandomVariable, AsciiString (/FIzh_ascii.h)
  and the seven nugget classes conflict with the donors' canonical headers and views.
  - ParticleSystemFXNugget lacks nine BFME 2 members (m_nuggetType, m_systemLife, m_targetOffset,
    m_useTargetOffset, m_targetCoeff, m_setTargetMatrix, m_createBoneAtTarget, m_onlyIfOnLand, m_onlyIfOnWater).

Clearance: pending.
Census confirmation: not claimed.
