# Preserved header-adoption recovery, 2026-11-08

Recovered the checkout's three remaining commits onto `2d62ba84f2` without
skipping a commit. The LINK-155 prose conflict retains upstream's paragraphs
first, followed by the preserved commit's original paragraph. No stash or
resync stash was recorded; the working tree was clean after the rebase.
The original six-commit backup remains at
`refs/runner/preparation/1793922361221664826`.

The other three saved commits already landed as `18a150c013` (ModuleInterface),
`9925ce051c` (MeshMatDescClass), and `9c6a000cc1` (AssetReference). The first two
are patch-equivalent according to `git cherry`; the AssetReference landing adds
the canonical destructor fold and recovery evidence. They are not reapplied.

The first `BFME_PUSH_SPACING_S=0 python3 tools/push.py --dry-run` passed CSV
validation, but refused a duplicate LINK-624 and four header retirements whose
acceptance now predicts lost census-linked bytes:

- RvaSmartPtr12 in ScriptEngine.cpp.
- ScriptList in ScriptEngineReset.cpp.
- SidesInfo in ScriptEngineCollectAssets.cpp and ScriptEngineReset.cpp.

Restore those four exact queue rows from current origin/master; they remain
unretired pending a passing cohort acceptance on current inputs. Historical
2026-11-05 acceptance and preview results in the earlier notes are not current
clearance for those rows. The recovered source edits stay subject to the push
hook's byte and link checks. The net outgoing queue reduction is 17 rows.

The newer SidesInfo obstacle becomes LINK-648, reserved by `/opt/runner/link-id`;
the older LINK-624 entry remains unchanged. Only the newer entry's heading and
filename change. No game source, shared header, shim, pin, alias, or provider is
changed by this recovery correction.
