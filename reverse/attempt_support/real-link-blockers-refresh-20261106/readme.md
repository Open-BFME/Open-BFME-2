# Refresh real-link blockers from the completed authoritative run

Official run42136415666 at0e8f5c6e8f3cfa35270f176457bbfaaac16a151c:
https://github.com/Open-BFME/Open-BFME-2/actions/runs/42136415666
Artifact13467202847,real-link-0e8f5c6e8f3cfa35270f176457bbfaaac16a151c.
ZIP SHA256 ab2c3c5d5eced778d203e78a17a259579610b64341697bdf110d6172501af881
was checked before extracting only selected text files. No runner was started,
restarted, approved, or changed. This is an existing hosted result.

scoreboard.json:2026-11-06 00:54 UTC, authoritative=true, build=success,
linker_exit1120, unresolved310, duplicates0, image_written=false,
omitted_funclets=[], initializers_bridged674. Those bridges are temporary
scaffolding, not progress. The complete errors.tsv has310 distinct error
symbols,277 attributed to export-unowned data, and33 other error symbols.

The prior committed list described the older2b78296450 real link. It still
served region.cpp and coord3d.cpp for names already provided afterwards.
Current region.cpp passes52/52 and all7 IntRange/LineSegment2D named providers
are present. None of those7 occurs in the newer errors.tsv. Current
coord3d.cpp also passes67/67 with3 strings and10 floats; the newer errors.tsv
no longer attributes an error to that source. Its unrelated Coord3D class-key
header prerequisites were not retried and no source body was changed.

Regeneration used only the owning tool:
python3 tools/exit_link.py --blockers build/real-link-20261106/real-link-0e8f5c6e8f3c/errors.tsv --blockers-commit 0e8f5c6e8f3cfa35270f176457bbfaaac16a151c
It records32 source buckets and311 source-attributed names. This differs from
the310 distinct missing symbols because one export has two owner sources.
The measured commit and historical errors are preserved; no missing name was
hand-deleted and no successful real link or executable is claimed.

This refresh verifies upstream repairs and aligns the picker with an actual
measurement. It does not claim a code fix or a measured missing-count drop by
this worker. Current unowned data and the remaining class-side providers still
block an image. The run at47fd56b8793 was in progress when this completed
result was retrieved and supplies no replacement measurement yet.

Coord3D recheck t=3 model=gpt-6 lane=R budget=30m.
Refresh and artifact verification t=4 model=gpt-6 lane=R budget=30m.
