### Publication and census follow-up (2026-11-02)

The final absorption landed as c9f1a00d82 with the separate verifier repair
a88a0030f1. The intervening Get_Shader fold landed as 93c5672365, so final
pre-push verification covered 28 rows and both EH graphs. Get_Shader is now
rowed; only Set_Texture remains an unrowed external donor provider in this
scope. Its pointer-word ABI still needs coordinated caller/header recovery.

The committed 2026-11-02 06:54 census at 357ce2a88f records linegrp.cpp
linked=yes with zero unresolved, duplicate, losing-COMDAT, address or
wrong-selected findings. This confirms the merged unit's census scope. The
publication audit itself remained INCONCLUSIVE against its older dae306bc9d
index and missing linegrp receipt; it did not establish global clearance.
The required flag profile remains: the fresh premerge 27-row default-profile
trial lost 13 matches, while the retained profile matched all 27. No flag
override is retired on the strength of the merge.
