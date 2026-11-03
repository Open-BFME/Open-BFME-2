### LINK-182 Real-link repairs in Libraries and Common (2026-11-03, seat halilkkaya-codex)

Notes Codex wrote for each commit, moved here from the pre-split register.


### CDManager real-link donor cleanup (2026-11-03, halilkkaya-codex)

Base c1325ac0b6: remove fourteen unrowed Zero Hour methods while retaining the
two ICF getter rows and TheCDManager. All eight real-link artifact names
attributed to this source disappear from its undefined externals. Six-source
normal checks pass389 rows; true base/tip preview retains five LINKS units
and changes CDManager0->54B, with no loss. Scoped DIR32389+17 witnesses passes.
No full real-link rerun or census confirmation is claimed; the actual CDManager
implementation remains separate work. [Audit and name list](../reverse/attempt_support/real-link-cdmanager-20261103.md).
