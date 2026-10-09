# Verified BFME 1 reference at f98983a7

At frozen BFME 2 `a6f9dbef229b9524708f805cd8dca17fd0e8a02c`, the normal full gate passed with both previous committed BFME 1 `2f243e26d44a74a48ef0ccfe9b543874e6567883` and current official/committed BFME 1 `f98983a7d3bb405f1a4ba94bb6a2a168062a819d`. Each run verified all 73,104 bodies across 20,798 sources, with all string, float, import, DIR32, pin, module, source-claim and no-op checks green. No update regression was found.

The old run compiled 5,058 dependency-stale units and reused 15,737 proven-current units. The new run reused all 20,795 compile units. Actual resolver directories were checked; 81 used reference headers from three normal consumer receipts were independently hash-checked. No header, toolchain or input path changed between the two donor revisions. Full outputs and comparison hashes accompany this receipt.

Official BFME 1 was fetched once by the coordinator. BFME 2 already committed f989 before this audit, so this change records verification and creates no obsolete pointer update. The isolated old checkout was preserved; only this worker's checkout moved. A success stamp was written only after both original full-gate processes terminated successfully.

The refreshed byte sweep has 5,343 independent control placements, zero currently available ranked donor files and three old immediate-only near leads totaling 75 bytes. The named lift lane reports 229 bodies, of which 151 are servable (94,221 bytes); these are reference leads and not C++ recoveries.

Changed donor trials use private objects and recorded O1/SSE/G7 and O2/SSE/G7 profiles. Each compiled 17 of 18 eligible non-Common units directly. X4Iostream initially lacked its actual donor `inputs/vendor/stlport/src/stlport_prefix.h`; explicitly adding that source include compiled it in both profiles, with 31/59 placements and zero new unique leads. The original failure and repaired include/header hashes remain separate. Common's single changed unit is covered by the repair seat's coordinated 231-unit profiles. The ASM-bearing bridge source is excluded.

O1 offers two small placements (FE369/16 and FDF3F/13); they remain separately reserved leads. Their donor names are not asserted as target identities. No recovery rows, pins, aliases, gate code or baselines change here.

Historical same-code 9cb→0e comparison at 0d4 also had every body green but two pre-existing DIR32 conflicts. Current code's genuine shroud global and scalar pending-surface vector fixes resolve both; neither old conflict is classified as a reference update regression.

Verified at `2026-10-09T16:02:01.433386+00:00`. Local detailed receipts: `build/reference975/bfme1-freshness-f98983a7/`.
