# ModuleInfo header adoption in terrain and revival consumers

Inspected revision: `9715c1427198aed905a828e71cda71d7760bd042`.

Replace the private ModuleInfo layouts in TerrainLogicXfer.cpp,
LivingWorldPlayer.cpp and LivingWorldPlayerCreateRevival.cpp with the existing
Common/ModuleInfoClass.h. The two revival units also lose their unused private
ModuleNugget views. LivingWorldPlayer's existing inline count expression now
uses the canonical m_end/m_begin fields. No shared header, flags, ledger row,
pin, alias or source path changes.

Target layout evidence is already documented in ModuleInfoClass.h: a 12-byte
vector over 20-byte nuggets. These consumers only require that layout and the
existing getNthData/getCount interface. No donor identity is inferred here.

Verification on 2026-11-05:

- find_declared_unmatched.py passes before and after for all three sources.
- build.sh: revival creation 14/14 function rows exact; terrain plus main
  living-world TU 99/99 function rows and one data row exact. String, float,
  import and compiler-owned EH/funclet checks pass.
- header_adopt_lane.py accept --class ModuleInfo passes all three sources and
  retires their three header_queue.tsv rows through the owning tool.
- Ordinary link_check.py against census c95fcfcfcd (2026-11-05 05:17):
  TerrainLogicXfer.cpp LINKS 2,245 -> 2,245 bytes;
  LivingWorldPlayer.cpp LINKS 4,765 -> 4,765 bytes;
  LivingWorldPlayerCreateRevival.cpp LINKS 1,183 -> 1,183 bytes.
  Total preview preservation: 8,193 -> 8,193 bytes, three clean units.

This retires header debt; it claims no new census coverage or runtime result.
The searched obstacle register contains no entry for these three consumer
adoptions. Its broader ModuleInfo/ThingTemplate provider and class-identity
prerequisites remain unchanged.
