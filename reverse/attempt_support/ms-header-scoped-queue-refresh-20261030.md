# Scoped Microsoft-header queue refresh

Control: 7906295d3f8e99862e1b7b005566c1fd7a6b4984.
The queue still classified Rva00131BE5Ctor.cpp as a drop-in candidate.
The current audit independently finds operator new's local throw() versus
the shipped new header's throw(...), an ABI/EH conflict. No source trial
or declaration substitution is appropriate for that classification.

The CLI's scan --write-queue accepted explicit paths but always called
write_queue, replacing the full inventory with that limited scan. A worker
could not safely refresh the stale selected entry through the documented
CLI without dropping unrelated work. Wire explicit-path scans to the
existing refresh_queue routine; preserve full replacement for a scan with
no paths. The scanner, contract comparisons and byte/EH gates are unchanged.

Three isolated CLI regressions fail before the fix: changed, clean and failed
analysis each remove unrelated queued work. They pass after the fix, alongside
the full-inventory case. The complete audit suite passes 65 tests, with five
existing platform skips. Its pre-existing same-size-edit test assumed LF text
on Windows; comparing the actual before/after byte sizes preserves the intended
invariant for CRLF as well. The broader related suite initially passed 245
other tests; the only failure was that fixture assertion, now covered by the
successful audit rerun.

Live command: scan --write-queue --jobs 2
Code/Libraries/Source/WWVegas/WW3D2/Rva00131BE5Ctor.cpp.
It changes only that entry from drop-in/same to conflicting/abi. All 870
unrelated queue records remain byte-identical. The normal repair_queue picker
now excludes this source from drop-in candidates and retains its file claim
scope in the conflicting lane. No baseline exemption, game-source change,
recovered code, linked-byte gain, new census or runtime result is claimed.

Refresh a selected stale entry with the same scoped command, inspect its fresh
classification, then follow its prerequisites and normal verification. The
whole-inventory scan remains available by omitting paths.

Post-rebase control: 85e3b96b8bfebc887f089772e6806cb3ac3e5b04. Refresh again from the upstream queue rather than replaying the old generated file: all 869 unrelated records remain byte-identical, including upstream retirements. The one selected entry retains its fresh conflicting classification.
