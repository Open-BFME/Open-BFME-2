### Browser and shader-manager stale header queue entries (2026-10-30)

At base `c647a75e55`, the browser's comdef declaration repair and the shader
manager's heap/debug declaration repair are already present in source.
The owning auditor's scoped refresh removes their two stale local queue
records (five declarations). Strict preparation verifies 31/31 function rows
and six data rows; ordinary paired preview retains 2/2 LINKS and 4,566
authored bytes against `12b9e7a7c0` (2026-10-30 10:11 UTC). No source or
provider changes, new census gain or full SDK closure are claimed. The
shader manager's shared Windows/multimedia shim and d3d9 include findings
remain prerequisites.
[Historical repairs, scan scope and checks](../../reverse/attempt_support/browser-shader-stale-msheaders-20261030-codexb4.md).
