# Pin audit, 2026-11-07 (LINK-631)

Read-only sweep of every reverse/symbols.csv pin at master `c32d83389b` (swarm Link lane, srv1).
A pin is judged when its real name sits on an address whose ledger rows carry a different real name.
For each, a ledger unit whose object defines the pinned name (census index 2026-11-06 17:34 at
94d8ffa1ad) was compiled and pin_admission.fold_proof_problems replayed against retail at the pin's
address: identity, bytes, relocations, callees. The same check is now `python3 tools/pin_consistency.py
--audit` (shadow; 69accdc3bc, 18b8469364).

- `own-body-differs.tsv`: the 42 pins whose own compiled body is not retail's body at their address
  (size, bytes or relocations), with the matched rows whose objects reference the name (callers).

Candidates, not verdicts: a different compiled body can also mean the defining unit compiles the
name differently from retail (an invented record layout, say). The sweep's compiles went through
build/match and the shared object store; they were removed afterwards (review of 69accdc3bc), and
--audit now compiles in isolation.
