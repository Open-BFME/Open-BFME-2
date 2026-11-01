"""Reproduce the private bank comparison without touching build/match/."""
import json
import sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / "tools"))
import permute
work = ROOT / "build" / "vector-overflow-owner-link-20261101" / "recheck"
work.mkdir(parents=True, exist_ok=True)
symbol = "?_M_insert_overflow@?$vector@URva00584405Element@@V?$allocator@URva00584405Element@@@_STL@@@_STL@@IAEXPAURva00584405Element@@ABU3@ABU__false_type@2@I_N@Z"
source = Path(__file__).with_name("candidate.cpp.txt")
scorer = permute.Scorer("0x0058431D", symbol, 189, work)
score, exact = scorer.score(source.read_text())
print(json.dumps({"score": score, "exact": exact, "unresolved": scorer.unresolved}))
raise SystemExit(0 if score >= 0.8929 and not exact else 1)
