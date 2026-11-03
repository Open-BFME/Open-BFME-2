### LINK-056: pointer-copy sweep spelling selects memmove for a native string-copy wrapper

Status: Blocked on template identity reconciliation. Updated: 2026-10-26; inspected revision: `896af216804e`.
Evidence / affected units: `StlSweepW5Rva004F6FE1.cpp`; native 27-byte wrapper calls 0x004F6D2E. This address is the 29-byte `__copy_backward_ptrs<TreeHintRef00217D4C*,TreeHintRef00217D4C*>(...,__false_type const&)` row in `Rva004F6D2ECopyBackward.cpp`. Raw evidence: `build/link-worker-w5/retail-probe-final.log`, `before-extra-providers.log` and `after-cohort.log`; the earlier AsciiString identity lead is in re_attempts.log at 0x004F6D4B.
Completed: diagnosis only. The real worker LINKS in the paired preview. The assigned unit retains L1/S1 because its pointer-to-pointer `__true_type` specialization emits the trivial memmove path. No source edit or repeated AsciiString row admission was attempted.
Remaining / next check: reconcile the wrapper's existing template row with the nontrivial string element family, keeping the one-name/one-address distinction from the older AsciiString copy_backward attempt at 0x000B6631. Do not suppress the only current-name provider or reinterpret another instantiation to call the worker.
Clearance: pending.
Census confirmation: not claimed.
