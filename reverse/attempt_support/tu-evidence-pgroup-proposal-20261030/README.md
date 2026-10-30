# Proposal: a funclet group follows its parent, never leads it (tu_evidence p-group)

Measured by halilkkaya-tue2 on 2026-10-30. The rule is NOT applied: it lowers TU-APPROVED by
1,043 rows (50.15% → 49.06%) and removes approval from 56 TUs that other seats may be merging,
so it is left for a maintainer decision. `rule.patch.txt` is the full commit, ready to apply
(tools/tu_evidence.py, tools/tests/test_tu_evidence.py, docs/consolidation.md);
`commit-message.txt` has the symptom, cause, fix and verification; `tus_changed.txt` lists
every TU whose approved count changes.

## Symptom (map rebuilt from current inputs)

- `tu_evidence.apply` approves a funclet of any proposed parent into that parent's TU, without
  checking the TU itself.
- `tu_skeleton` absorbs any donor whose rows all sit in the TU, approved or not, so one approved
  funclet drags its unapproved parent's file into a merge.
- ImmortalBody.cpp: tu_map marks it noncontiguous (StructureBody.cpp's rows split its span), yet
  33 funclets (0x0078FB39..0x0078FCD4) are approved there, 31 of them for parents placed only by
  the U rule (Symbiotic, Respawn, DelayedDeath, FreeLife, DetachableRider, Oathbreaker, Porcupine).
- Behavior/UpgradeSoundSelectorClientBehavior.cpp: 11 funclets approved, including 0x00771C54
  and 0x00771C6B, whose parents (0x00253DB2, 0x00253E8E) are placed by U while their own names
  point to the (Horde)NotifyTargetsOfImminentProbableCrushingUpdate.cpp files. A merge there
  yields three `$L310` rows in one source, which check_csv refuses.

## Rule (`group_refused()`)

No funclet group joins a TU the map marks noncontiguous. No funclet group follows a parent whose
own evidence names another file (a parent marked contradicted, or placed by U). A refused funclet
keeps its TU as proposed, exactly as with the group rule off.

## Measurements

- TU-APPROVED 47,924 → 46,881 rows; approved TUs 1,438 → 1,382. Exactly 1,043 rows go from
  approved to proposed and keep their TU; nothing else changes.
- Largest losses: GameClient.cpp −93, W3DDisplay.cpp −92, W3DScriptedModelDraw.cpp −76,
  AIPlayer.cpp −67, AIUpdate.cpp −67, W3DVolumetricShadow.cpp −64, RenderableRiverArea.cpp −58.
- `tu_map.py --validate c6926a544d` and `tu_evidence.py --validate`: identical output.
- Hold-out (`tu_map.py --holdout p-groups`): purity 99.88% before and after. Of the 260 held-out
  rows the rule removes, only 25% had the right TU name, against 74% for the rows it keeps.
- A looser variant (exempt parents whose own F/Z/S names the TU) keeps 426 more rows, mostly
  GameClient.cpp's; GameClient.cpp is noncontiguous only because of one WindowXlat.cpp Z row at
  0x002390E8, so fixing that span would restore those rows the normal way.
