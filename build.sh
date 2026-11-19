#!/usr/bin/env bash
set -euo pipefail

# No arguments: full byte-for-byte verification of every function (~10 min
# solo with BUILD_POOL=8; longer while other clones build — a host-wide lock
# serializes full builds). To iterate quickly, pass source files or function
# names to verify just those (a few seconds, skips the baseline hash and
# no-op patch):
#   ./build.sh src/math/color.cpp

# Keep Wine quiet and avoid needing an X display.
export WINEDEBUG="${WINEDEBUG:--all}"
export DISPLAY="${DISPLAY:-}"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
if [[ "${1:-}" == "--variant" ]]; then
    if [[ "${2:-}" != "modern" ]]; then
        echo "build.sh: --variant requires modern; omit it for retail verification" >&2
        exit 2
    fi
    shift 2
    exec python3 "$SCRIPT_DIR/tools/build_variant.py" "$@"
fi
exec python3 "$SCRIPT_DIR/tools/build.py" "$@"
