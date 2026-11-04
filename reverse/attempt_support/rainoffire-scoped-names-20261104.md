# RainOfFireUpdate scoped naming follow-up

After destructor composition at `e0b4c6f428`, the supported scoped handoff
inventoried 17 local/parameter bindings in the destination TU. Native child
`/root/rainoffire_names` proposed eight clarifications and nine keeps. The parent
scanned every mapping and the preview diff, preserving the original proposal.

Seven update locals were applied together: emitterObject, elapsedFrames,
darknessFadeFraction, rainCenter, launchPosition, targetPosition and
firingDirection. Their roles follow the current frame calculation, camera
position, terrain query and weapon/transform calls in this complete function.
These are inferred scoped names, not recovered donor spellings. Ten bindings
were retained. The comma-declaration warning was checked against the complete
function: the warned syntax uses aggregate/call commas, with no omitted local
declarators found.

`name_lane.py scoped apply` verified all 13 rows, two strings, 13 float literals
and both EH-bound funclet labels in one source pass. Declared-unmatched checking
remains clear. No symbol, class, member, global, include or source path changes.
The naming ledgers retain the native proposer and parent review identities.

False reject retained for the tooling lane: the setter parameter `value` was
proposed as `darknessFactor`, but preview refused it because an unrelated
included `reference/shims/bfme2_bonefxupdate/Common/INI.h` declares
`LookupListRec::value`. The setter body only stores its own parameter into
darkness and uses that parameter in the display-level expression; it does not
name LookupListRec. The parent kept `value` in the review decision, recorded the
refusal through re_log.py for 0x004AC18D, and did not bypass or edit the check.
Local reproduction artifacts are under
`build/name_lane/scoped/rainoffire-merged-codex5-20261104.*`.
