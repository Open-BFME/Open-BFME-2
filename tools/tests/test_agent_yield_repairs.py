"""agent_yield credits repairs: gate-debt lines a commit deletes, net of any it adds."""
import sys
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import agent_yield  # noqa: E402

DIFF = """diff --git a/reverse/gate_baseline.txt b/reverse/gate_baseline.txt
--- a/reverse/gate_baseline.txt
+++ b/reverse/gate_baseline.txt
@@ -3,3 +3,1 @@
-# old comment
-tail 0x00001000 ?a@@YAXXZ
-ltable 0x00002000 ?b@@YAXXZ
+# new comment
"""


def test_deleted_debt_lines_are_repairs(monkeypatch):
    monkeypatch.setattr(agent_yield, "git", lambda *args: DIFF)
    assert agent_yield.commit_repairs("abc") == 2


def test_an_added_line_cancels_a_removed_one(monkeypatch):
    monkeypatch.setattr(agent_yield, "git", lambda *args: DIFF + "+strnul 0x00003000 ?c@@YAXXZ\n")
    assert agent_yield.commit_repairs("abc") == 1
