"""How many --prepared sources one rename transaction carries.

A respell whose callers keep private views must take every one of them in one
commit: a unit left behind calls a symbol no row names. `_batch_source_edits`
refuses more than PREPARED_DEFAULT (32) unless `--max-prepared N` raises the
limit for that run, and a value above PREPARED_CEILING (256) also needs
`--beyond-prepared-ceiling`. However many sources it carries, the plan stays one
transaction: one ./build.sh over all of them, and every file restored when any
unit fails. Miniature git trees; verification is injected."""
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import rename  # noqa: E402

UNITS = [f"Code/Game/Caller{i:02d}.cpp" for i in range(52)]


def run(root, *args):
    return subprocess.run(["git", *args], cwd=root, capture_output=True, text=True, check=True)


@pytest.fixture
def tree(tmp_path):
    rows = "".join(f"?caller{i:02d}@@YAXXZ,,0x{0x401000 + 0x10 * i:08X},8,{rel},matched,\n"
                   for i, rel in enumerate(UNITS))
    files = {"reverse/functions.csv": "name,export_rva,target_rva,target_size,source,status,notes\n" + rows,
             "reverse/deleted_rows.csv": "name,target_rva,reason\n"}
    files.update({rel: f"// cl: /O2\nvoid accepts(int);\nvoid caller{i:02d}() {{ accepts(1); }}\n"
                  for i, rel in enumerate(UNITS)})
    for rel, text in files.items():
        path = tmp_path / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(text.encode("utf-8"))
    run(tmp_path, "init", "-q")
    run(tmp_path, "config", "core.autocrlf", "false")
    run(tmp_path, "add", "-A")
    run(tmp_path, "-c", "user.name=t", "-c", "user.email=", "commit", "-qm", "callers")
    return tmp_path


def respelled(count):
    """The prepared sources of a signature-only respell: each caller's private view takes the new signature."""
    return {rel: f"// cl: /O2\nvoid accepts(const int &);\nvoid caller{i:02d}() {{ accepts(1); }}\n".encode()
            for i, rel in enumerate(UNITS[:count])}


def plan_with(ctx, edits):
    plan = rename.Plan("function", "?accepts@@YAXH@Z", "?accepts@@YAXABH@Z", "inferred", "respell", UNITS[0], None)
    rename._batch_source_edits(ctx, plan, edits)
    return plan


def snapshot(root):
    return {p.relative_to(root).as_posix(): p.read_bytes()
            for p in root.rglob("*") if p.is_file() and ".git" not in p.parts and "build" not in p.parts}


def test_the_default_still_refuses_33_prepared_sources(tree):
    ctx = rename.Context(tree, object_scan=False)
    assert ctx.max_prepared == rename.PREPARED_DEFAULT == 32
    plan_with(ctx, respelled(32))
    with pytest.raises(rename.Refusal, match=r"at most 32 .* \(33 given; --max-prepared N raises"):
        plan_with(rename.Context(tree, object_scan=False), respelled(33))


def test_the_override_takes_52_as_one_transaction(tree):
    ctx = rename.Context(tree, object_scan=False)
    ctx.max_prepared = 52
    plan = plan_with(ctx, respelled(52))
    assert sorted(plan.after) == sorted(UNITS) and plan.verify == sorted(UNITS)
    builds = []

    def verify(_ctx, sources):
        builds.append(list(sources))
        return True
    rename.apply_rename(plan, ctx=ctx, verify=verify, checks=None)
    assert builds == [sorted(UNITS)]                              # one ./build.sh over all 52
    assert all((tree / rel).read_bytes() == data for rel, data in respelled(52).items())


@pytest.mark.parametrize("bad", [UNITS[0], UNITS[25], UNITS[51]])
def test_a_failure_in_any_unit_rolls_back_all_of_them(tree, bad):
    before = snapshot(tree)
    ctx = rename.Context(tree, object_scan=False)
    ctx.max_prepared = 52
    plan = plan_with(ctx, respelled(52))
    with pytest.raises(rename.VerifyFailed):
        rename.apply_rename(plan, ctx=ctx, verify=lambda _ctx, sources: bad not in sources, checks=None)
    assert snapshot(tree) == before


def test_an_override_is_still_a_limit(tree):
    ctx = rename.Context(tree, object_scan=False)
    ctx.max_prepared = 40
    with pytest.raises(rename.Refusal, match="at most 40"):
        plan_with(ctx, respelled(41))


@pytest.mark.parametrize("extra,ceiling_refused", [
    (["--max-prepared", "52"], False),
    (["--max-prepared", "256"], False),
    (["--max-prepared", "257"], True),
    (["--max-prepared", "300", "--beyond-prepared-ceiling"], False),
])
def test_the_cli_ceiling_needs_a_second_flag(tree, capsys, extra, ceiling_refused):
    argv = ["function", "--rva", "0x00401000", "--new", "acceptsRecord", "--basis", "inferred",
            "--evidence", "agree:none", "--dry-run", "--no-claim", "--no-object-scan", "--root", str(tree), *extra]
    if ceiling_refused:
        with pytest.raises(SystemExit) as exit_:
            rename.main(argv)
        assert exit_.value.code == 2 and "above the 256 ceiling" in capsys.readouterr().err
    else:
        rename.main(argv)                       # parsed: the plan itself decides (here, the evidence refuses)
        assert "ceiling" not in capsys.readouterr().err


def test_max_prepared_must_be_positive(tree, capsys):
    with pytest.raises(SystemExit):
        rename.main(["function", "--rva", "0x00401000", "--new", "acceptsRecord", "--basis", "inferred",
                     "--evidence", "agree:none", "--dry-run", "--no-claim", "--root", str(tree),
                     "--max-prepared", "0"])
    assert "at least 1" in capsys.readouterr().err
