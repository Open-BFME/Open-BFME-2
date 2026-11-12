"""rename.py runs the pre-commit hook's path-sensitive checks (class_gate,
ledger_guard, code_identity_gate, link_debt, check_case_collisions,
hatch_counters, data_check, eh_verify, and with a ledger file pin_admission,
pin_consistency, name_dependents) against what the commit will contain, so a
plan that passes check_csv but would fail at commit is refused by the rename
and rolled back byte for byte. conversion_gate, tu_ownership, invented_names,
header_dependents and the baseline shrink-only assertions are not run: a
rename cannot change what they judge.

A miniature git tree. ledger_guard is the real tool (standard library only);
the other three are small stand-ins with the hook's contract (`--staged`: read
the index, exit 1 to refuse, name_dependents lists units on stdout), which is
what shows the checks see the private index and never the real one.
test_hook_drift.. reads .githooks/pre-commit itself, so a hook change that
this module's jobs do not follow fails here."""
import hashlib
import json
import os
import re
import shlex
import shutil
import signal
import subprocess
import sys
import threading
import time
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import rename  # noqa: E402
from rename import Refusal, VerifyFailed  # noqa: E402

OLD = "?Rva00401000@Widget@@QAEHH@Z"
NEW = "?countParts@Widget@@QAEHH@Z"
UNIT = "Code/Game/Widget.cpp"


@pytest.mark.parametrize("cancellable", [False, True])
def test_windows_build_receives_large_scope_together(tmp_path, monkeypatch, cancellable):
    sources = [f"Code/Game/Long directory/Unit {i} é.cpp" for i in range(1917)]
    ctx = rename.Context(tmp_path)
    script = ctx.path("tools/build.py")
    script.parent.mkdir()
    script.write_text(
        "import pathlib, sys\n"
        "assert sys.argv[1:] == ['--selectors-stdin']\n"
        "pathlib.Path('received.json').write_bytes(sys.stdin.buffer.read())\n"
        "print('Functions: OK 1/1')\n", encoding="utf-8")
    monkeypatch.setattr(sys, "platform", "win32")
    cancel = threading.Event() if cancellable else None
    assert rename.build_verify(ctx, sources, cancel)
    assert json.loads((tmp_path / "received.json").read_bytes()) == sources

FUNCTIONS = f"""name,export_rva,target_rva,target_size,source,status,notes
{OLD},,0x00401000,40,{UNIT},matched,address-derived
?caller@Gadget@@QAEXXZ,,0x00402000,20,Code/Game/Gadget.cpp,matched,calls {OLD}
"""
SYMBOLS = f"name,address,notes\n{OLD},0x00401000,pin\n"
WIDGET = "// cl: /O2\nint Widget::Rva00401000(int n) { return n; }\n"
GADGET = "void Gadget::caller() {}\n"

# pin_admission stand-in: refuse when the INDEX holds two names at one address.
PIN_ADMISSION = '''import subprocess, sys
text = subprocess.run(["git", "show", ":reverse/symbols.csv"], capture_output=True, text=True).stdout
seen = {}
for line in text.splitlines()[1:]:
    name, address = line.split(",")[:2]
    seen.setdefault(address, set()).add(name)
bad = [a for a, names in seen.items() if len(names) > 1]
if bad:
    print("pin admission: FAIL 1\\n  second real name at " + bad[0])
    sys.exit(1)
print("pin admission: OK")
'''
# class_gate stand-in: refuse a staged unit that mentions `ForbiddenView`.
CLASS_GATE = '''import subprocess, sys
for path in subprocess.run(["git", "diff", "--cached", "--name-only"], capture_output=True, text=True).stdout.split():
    if path.endswith(".cpp") and "ForbiddenView" in subprocess.run(["git", "show", ":" + path],
                                                                   capture_output=True, text=True).stdout:
        print("  " + path + ": declares its own `ForbiddenView`", file=sys.stderr)
        sys.exit(1)
'''
# name_dependents stand-in: the plan removed a name that Gadget.cpp calls.
NAME_DEPENDENTS = '''print("Code/Game/Gadget.cpp")\n'''


def git(root, *args):
    return subprocess.run(["git", "-C", str(root), *args], check=True, capture_output=True, text=True).stdout


@pytest.fixture
def tree(tmp_path):
    files = {
        "reverse/functions.csv": FUNCTIONS,
        "reverse/symbols.csv": SYMBOLS,
        "reverse/deleted_rows.csv": "name,target_rva,reason\n",
        "reverse/data_rows.csv": "name,address,address_kind,size,section,source,status,evidence,model\n",
        UNIT: WIDGET,
        "Code/Game/Gadget.cpp": GADGET,
        "tools/pin_admission.py": PIN_ADMISSION,
        "tools/class_gate.py": CLASS_GATE,
    }
    for rel, text in files.items():
        path = tmp_path / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(text.encode("utf-8"))
    shutil.copy(TOOLS / "ledger_guard.py", tmp_path / "tools" / "ledger_guard.py")
    git(tmp_path, "init", "-q")
    git(tmp_path, "add", "-A")
    git(tmp_path, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-q", "-m", "base")
    return tmp_path


def ctx_of(root):
    return rename.Context(root, object_scan=False)


def snapshot(root):
    return {p.relative_to(root).as_posix(): p.read_bytes()
            for p in root.rglob("*") if p.is_file() and ".git" not in p.parts}


def plan_of(root, **edits):
    ctx = ctx_of(root)
    plan = rename.Plan("function", OLD, NEW, "inferred", "", UNIT, 0x00401000, verify=[UNIT])
    for rel, data in edits.items():
        plan.edit(ctx, rel.replace("__", "/").replace("_csv", ".csv").replace("_cpp", ".cpp"), data)
    return plan


def renamed_functions():
    return FUNCTIONS.replace(OLD, NEW).encode()


def apply(root, plan, verify=lambda ctx, sources: True):
    return rename.apply_rename(plan, ctx=ctx_of(root), verify=verify, checks=rename.ledger_checks)


def real_index(root):
    return (root / ".git" / "index").read_bytes()


def test_clean_plan_passes_and_leaves_the_real_index_alone(tree):
    plan = plan_of(tree)
    plan.edit(ctx_of(tree), "reverse/functions.csv", renamed_functions())
    plan.edit(ctx_of(tree), "reverse/symbols.csv", SYMBOLS.replace(OLD, NEW).encode())
    index = real_index(tree)
    apply(tree, plan)
    assert (tree / "reverse/functions.csv").read_bytes() == renamed_functions()
    assert real_index(tree) == index and git(tree, "diff", "--cached", "--name-only") == ""


def test_plan_pin_admission_would_refuse_is_refused_and_rolled_back(tree):
    plan = plan_of(tree)
    plan.edit(ctx_of(tree), "reverse/functions.csv", renamed_functions())
    plan.edit(ctx_of(tree), "reverse/symbols.csv", (SYMBOLS + f"{NEW},0x00401000,alias pin\n").encode())
    before, index = snapshot(tree), real_index(tree)
    with pytest.raises(VerifyFailed, match=r"\[pin_admission\].*second real name"):
        apply(tree, plan)
    assert snapshot(tree) == before and real_index(tree) == index
    assert not rename.journals(ctx_of(tree))


def test_pin_admission_judges_the_plan_not_the_working_tree_alone(tree):
    """The same clashing pin edited into the tree by hand, outside the plan,
    is not what the commit will contain: it is unstaged, so not judged here
    (ledger_guard names it instead)."""
    (tree / "reverse/symbols.csv").write_bytes((SYMBOLS + f"{NEW},0x00401000,alias pin\n").encode())
    plan = plan_of(tree)
    plan.edit(ctx_of(tree), "reverse/functions.csv", renamed_functions())
    with pytest.raises(VerifyFailed) as refused:
        apply(tree, plan)
    assert str(refused.value).split("[")[1].startswith("ledger_guard]")


def test_class_gate_refusal_is_reported_by_name(tree):
    plan = plan_of(tree)
    plan.edit(ctx_of(tree), UNIT, (WIDGET + "struct ForbiddenView { int x; };\n").encode())
    before = snapshot(tree)
    with pytest.raises(VerifyFailed, match=r"\[class_gate\]"):
        apply(tree, plan)
    assert snapshot(tree) == before


def test_ledger_guard_refuses_a_ledger_edited_outside_the_plan(tree):
    plan = plan_of(tree)
    plan.edit(ctx_of(tree), "reverse/functions.csv", renamed_functions())
    (tree / "reverse/data_rows.csv").write_bytes(b"name,address\nx,1\n")      # someone else's edit
    with pytest.raises(VerifyFailed, match=r"\[ledger_guard\]"):
        apply(tree, plan)


def test_a_later_plan_is_judged_with_the_files_an_earlier_one_of_the_run_wrote(tree):
    """One Context applies two plans before anything is staged (rename_files does it
    batch after batch): the first writes data_rows.csv, the second does not, and
    ledger_guard must not call the first's leftover outside dirt. An edit no plan of
    the run wrote is still refused."""
    ctx = ctx_of(tree)
    data = b"name,address,address_kind,size,section,source,status,evidence,model\nx,0x1,d,4,.data,s,matched,\n"
    first = plan_of(tree)
    first.edit(ctx, "reverse/data_rows.csv", data)
    rename.apply_rename(first, ctx=ctx, verify=lambda c, s: True, checks=rename.ledger_checks)
    second = plan_of(tree)
    second.edit(ctx, "reverse/functions.csv", renamed_functions())
    index = real_index(tree)
    rename.apply_rename(second, ctx=ctx, verify=lambda c, s: True, checks=rename.ledger_checks)
    assert real_index(tree) == index
    assert ctx.kept == {"reverse/data_rows.csv", "reverse/functions.csv"}
    (tree / "reverse/symbols.csv").write_bytes(b"name,address,notes\nz,0x2,pin\n")      # nobody's plan
    third = plan_of(tree)
    third.edit(ctx, "reverse/functions.csv", renamed_functions().replace(b"caller", b"calls"))
    with pytest.raises(VerifyFailed, match=r"\[ledger_guard\]"):
        rename.apply_rename(third, ctx=ctx, verify=lambda c, s: True, checks=rename.ledger_checks)


def test_every_refusing_check_is_named(tree):
    plan = plan_of(tree)
    plan.edit(ctx_of(tree), "reverse/functions.csv", renamed_functions())
    plan.edit(ctx_of(tree), "reverse/symbols.csv", (SYMBOLS + f"{NEW},0x00401000,alias pin\n").encode())
    plan.edit(ctx_of(tree), UNIT, (WIDGET + "struct ForbiddenView { int x; };\n").encode())
    with pytest.raises(VerifyFailed, match=r"\[class_gate, pin_admission\]|\[pin_admission, class_gate\]"):
        apply(tree, plan)


def stand_in_name_dependents(tree):
    (tree / "tools/name_dependents.py").write_text(NAME_DEPENDENTS)
    git(tree, "add", "tools/name_dependents.py")
    git(tree, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-q", "-m", "stand-in")


def test_name_dependents_units_are_built_before_success(tree, monkeypatch):
    stand_in_name_dependents(tree)
    built = []
    fake = lambda ctx, sources, cancel=None: built.append(list(sources)) or True      # noqa: E731
    monkeypatch.setattr(rename, "build_verify", fake)
    plan = plan_of(tree)
    plan.edit(ctx_of(tree), "reverse/functions.csv", renamed_functions())
    apply(tree, plan, verify=fake)
    assert built == [[UNIT], ["Code/Game/Gadget.cpp"]]


def test_a_failing_name_dependent_build_refuses_and_restores(tree, monkeypatch):
    stand_in_name_dependents(tree)
    fake = lambda ctx, sources, cancel=None: sources == [UNIT]                         # noqa: E731
    monkeypatch.setattr(rename, "build_verify", fake)
    plan = plan_of(tree)
    plan.edit(ctx_of(tree), "reverse/functions.csv", renamed_functions())
    before = snapshot(tree)
    with pytest.raises(VerifyFailed, match=r"\[name_dependents\]"):
        apply(tree, plan, verify=fake)
    assert snapshot(tree) == before and not rename.journals(ctx_of(tree))


def test_a_unit_the_plan_already_verifies_is_not_built_twice(tree, monkeypatch):
    stand_in_name_dependents(tree)
    built = []
    fake = lambda ctx, sources, cancel=None: built.append(list(sources)) or True      # noqa: E731
    monkeypatch.setattr(rename, "build_verify", fake)
    plan = plan_of(tree)
    plan.verify = [UNIT, "Code/Game/Gadget.cpp"]
    plan.edit(ctx_of(tree), "reverse/functions.csv", renamed_functions())
    apply(tree, plan, verify=fake)
    assert built == [[UNIT, "Code/Game/Gadget.cpp"]]


def test_the_pre_rename_call_runs_nothing(tree):
    (tree / "tools/pin_admission.py").write_text("raise SystemExit('always refuses')\n")
    assert rename.commit_checks(ctx_of(tree), rename.Plan("function", "a", "b", "x", "", None, None)) == []


def test_staged_index_is_private(tree):
    index = real_index(tree)
    (tree / "reverse/symbols.csv").write_bytes(b"name,address,notes\n")
    with rename.staged_index(ctx_of(tree), ["reverse/symbols.csv"]) as env:
        staged = subprocess.run(["git", "-C", str(tree), "diff", "--cached", "--name-only"], env=env,
                                capture_output=True, text=True).stdout
    assert staged.split() == ["reverse/symbols.csv"]
    assert real_index(tree) == index and git(tree, "diff", "--cached", "--name-only") == ""


def test_a_tree_that_is_no_repository_is_not_judged(tmp_path):
    (tmp_path / "tools").mkdir()
    (tmp_path / "tools/class_gate.py").write_text("raise SystemExit(1)\n")
    plan = rename.Plan("function", "a", "b", "x", "", None, None)
    plan.after["reverse/functions.csv"] = b"x"
    assert rename.commit_checks(ctx_of(tmp_path), plan) == []


# ------------------------------------------------ the rest of the hook's checks

def stand_in(tree, name, text):
    (tree / "tools").mkdir(exist_ok=True)
    (tree / f"tools/{name}.py").write_text(text)


# code_identity_gate / pin_consistency stand-ins: refuse when the INDEX holds the marker
INDEX_MARKER = '''import subprocess, sys
text = subprocess.run(["git", "show", ":reverse/symbols.csv"], capture_output=True, text=True).stdout
if "BAD" in text:
    print("%s: FAIL 1" % sys.argv[0])
    sys.exit(1)
'''


def renamed_plan(tree, symbols=None):
    plan = plan_of(tree)
    plan.edit(ctx_of(tree), "reverse/functions.csv", renamed_functions())
    if symbols is not None:
        plan.edit(ctx_of(tree), "reverse/symbols.csv", symbols.encode())
    return plan


def test_code_identity_gate_and_pin_consistency_are_run_and_named(tree):
    stand_in(tree, "code_identity_gate", INDEX_MARKER)
    stand_in(tree, "pin_consistency", INDEX_MARKER.replace("sys.argv[0]", "'pins'"))
    plan = renamed_plan(tree, SYMBOLS.replace(OLD, NEW) + "BAD,0x00999000,x\n")
    with pytest.raises(VerifyFailed, match=r"\[code_identity_gate, pin_consistency\]"):
        apply(tree, plan)


def test_pin_consistency_runs_only_when_a_ledger_file_is_written(tree):
    stand_in(tree, "pin_consistency", "raise SystemExit('always refuses')\n")
    plan = rename.Plan("function", "a", "b", "x", "", UNIT, None)
    plan.edit(ctx_of(tree), UNIT, (WIDGET + "// edit\n").encode())
    assert rename.commit_checks(ctx_of(tree), plan) == []
    plan.edit(ctx_of(tree), "reverse/symbols.csv", SYMBOLS.encode() + b"x,0x1,y\n")
    assert rename.commit_checks(ctx_of(tree), plan)[0].startswith("pin_consistency:")


def test_a_missing_hook_tool_fails_in_the_repository_and_is_skipped_in_a_fixture(tree, monkeypatch):
    plan = renamed_plan(tree)
    ctx = ctx_of(tree)
    assert rename.commit_checks(ctx, plan) == []                       # a fixture lacks the tools
    monkeypatch.setattr(rename, "ROOT", tree)                          # now it is "the repository"
    problems = rename.commit_checks(ctx, plan)
    missing = {p.split(":")[0] for p in problems}
    assert {"code_identity_gate", "link_debt", "hatch_counters", "data_check"} <= missing
    assert "class_gate" not in missing and "ledger_guard" not in missing        # present in the fixture
    assert all("is missing" in p for p in problems)
    assert rename.commit_checks(ctx, plan, missing_ok=True) == []
    assert not any(p.startswith("link_debt") for p in rename.commit_checks(ctx, plan, skip=("link_debt",)))


def test_a_moved_unit_is_judged_at_its_new_path(tree):
    new = "Code/Game/Gadget2.cpp"
    plan = plan_of(tree)
    plan.moves.append(("Code/Game/Gadget.cpp", new))
    plan.moved_bytes["Code/Game/Gadget.cpp"] = GADGET.encode()
    plan.before["Code/Game/Gadget.cpp"] = GADGET.encode()
    plan.after[new] = (GADGET + "struct ForbiddenView { int x; };\n").encode()
    before = snapshot(tree)
    with pytest.raises(VerifyFailed, match=r"\[class_gate\].*Gadget2.cpp"):
        apply(tree, plan)
    assert snapshot(tree) == before and git(tree, "diff", "--cached", "--name-only") == ""


def test_cancelling_kills_the_running_tool_at_once(tree):
    stand_in(tree, "code_identity_gate", "import time\ntime.sleep(60)\n")
    cancel = threading.Event()
    threading.Timer(0.5, cancel.set).start()
    started = time.time()
    assert rename.commit_checks(ctx_of(tree), renamed_plan(tree), cancel=cancel) == []
    assert time.time() - started < 10


def test_a_large_input_reaches_a_child_that_reads_it_late():
    # far over the pipe buffer, and the child sleeps before reading: the call must neither hang nor drop input
    data = bytes(range(256)) * 8192                      # 2 MiB
    child = ("import sys, time, hashlib\ntime.sleep(1)\n"
             "data = sys.stdin.buffer.read()\nprint(len(data), hashlib.sha256(data).hexdigest())\n")
    done = []
    worker = threading.Thread(daemon=True, target=lambda: done.append(
        rename._run_cancellable([sys.executable, "-c", child], threading.Event(), input=data)))
    worker.start()
    worker.join(30)
    assert done, "_run_cancellable never returned for a 2 MiB input"
    assert done[0].returncode == 0 and done[0].stdout.split() == [str(len(data)), hashlib.sha256(data).hexdigest()]


def test_a_large_input_does_not_stop_a_cancel():
    # the child never reads its stdin: cancelling still kills it and returns None
    cancel = threading.Event()
    threading.Timer(0.5, cancel.set).start()
    done = []
    worker = threading.Thread(daemon=True, target=lambda: done.append(
        rename._run_cancellable([sys.executable, "-c", "import time; time.sleep(60)"], cancel,
                                input=b"x" * (2 << 20))))
    worker.start()
    worker.join(15)
    assert done == [None]


def test_a_signal_in_the_main_thread_does_not_wait_for_the_tools(tree, monkeypatch):
    stand_in(tree, "code_identity_gate", "import time\ntime.sleep(60)\n")

    def interrupted(ctx, plan):
        time.sleep(0.5)
        raise KeyboardInterrupt
    monkeypatch.setattr(rename, "_csv_checks", interrupted)
    started = time.time()
    with pytest.raises(KeyboardInterrupt):
        rename.ledger_checks(ctx_of(tree), renamed_plan(tree))
    assert time.time() - started < 5


def alive(pid):
    try:
        os.kill(pid, 0)
    except ProcessLookupError:
        return False
    return True


def wait_gone(pid, seconds=5):
    deadline = time.time() + seconds
    while alive(pid) and time.time() < deadline:
        time.sleep(0.1)
    return not alive(pid)


def sleeper(tree, name):
    """Make tool `name` a stand-in that records its pid and sleeps."""
    stand_in(tree, name, "import os, time\nopen(os.environ.get('PIDFILE') or "
             f"{str(tree / 'pid')!r}, 'w').write(str(os.getpid()))\ntime.sleep(60)\n")


def test_a_signal_while_waiting_for_the_hook_tools_cancels_them(tree, monkeypatch):
    # check_csv is done (nothing to wait for); the slow tool is still running
    sleeper(tree, "code_identity_gate")
    monkeypatch.setattr(rename, "_csv_checks", lambda ctx, plan: [])
    # a real signal: it wakes the main thread out of the wait, which interrupt_main does not
    threading.Timer(1.5, signal.pthread_kill, (threading.main_thread().ident, signal.SIGINT)).start()
    started = time.time()
    with pytest.raises(KeyboardInterrupt):
        rename.ledger_checks(ctx_of(tree), renamed_plan(tree))
    assert time.time() - started < 6
    pid = int((tree / "pid").read_text())
    assert wait_gone(pid), "the hook tool outlived the interrupted ledger_checks"


def test_cancelling_kills_the_name_dependents_build(tree):
    # the extra unit's ./build.sh (and what it started) stops with the cancel
    stand_in_name_dependents(tree)
    (tree / "build.sh").write_text("#!/bin/sh\nsleep 60 &\necho $! > pid\necho $$ > started\nwait\n")
    (tree / "build.sh").chmod(0o755)
    cancel = threading.Event()

    def watch():
        while not (tree / "started").exists():
            time.sleep(0.05)
        cancel.set()
    threading.Thread(target=watch, daemon=True).start()
    started = time.time()
    assert rename.commit_checks(ctx_of(tree), renamed_plan(tree), cancel=cancel) == []
    assert time.time() - started < 15
    assert wait_gone(int((tree / "pid").read_text())), "the build's child outlived the cancel"


# --------------------------------------------- the hook and these jobs say the same

HOOK = TOOLS.parent / ".githooks" / "pre-commit"


def strip_shell_comments(text):
    """`text` without its shell comments (`#` at the start of a word, outside
    quotes) and with backslash-newline continuations joined. A comment that
    ends in a backslash does not continue onto the next line, so comments go first."""
    out, quote, i = [], None, 0
    while i < len(text):
        c = text[i]
        if quote == "'":
            quote = None if c == "'" else quote
        elif c == "\\":
            out.append(text[i:i + 2])
            i += 2
            continue
        elif quote == '"':
            quote = None if c == '"' else quote
        elif c in "'\"":
            quote = c
        elif c == "#" and (i == 0 or text[i - 1] in " \t\n;&|("):
            while i < len(text) and text[i] != "\n":
                i += 1
            continue
        out.append(c)
        i += 1
    assert quote is None, "unbalanced quote: the hook parser lost its place"
    return "".join(out).replace("\\\n", " ")


# An interpreter spelling: python3, python, python3.11, /usr/bin/python3, "$PYTHON3", py (with -3),
# the hook's own sh .githooks/run-python3 wrapper; flags (-u, -I, -B) may follow it.
_PY = r"(?:[\w./$\"{}-]*python[\w.]*\"?|py(?:\s+-\d(?:\.\d+)?)?|[\w./-]*run-python3)"
_FLAGS = r"(?:\s+-[A-Za-z]\w*)*"
_ARGS = r"((?:[^|&;<>)\n]|\|(?!\|))*)"
_RUN_PATH = re.compile(_PY + _FLAGS + r"\s+(?:\./)?tools/(\w+)\.py" + _ARGS, re.I)
_RUN_STDIN = re.compile(r"git\s+show\s+\S*:tools/(\w+)\.py\s*\|\s*" + _PY + _FLAGS + r"\s+-(?=\s|$)" + _ARGS, re.I)
_MENTION = re.compile(r"(?<![\w])tools/(\w+)\.py|(?<![\w.])-m\s+tools\.(\w+)")
# HEAD's copy of a tool loaded into a file first (`capture VAR "why" git show HEAD:tools/X.py`), then
# run from it on stdin (`python3 - ARGS < "$VAR"`): the hook's repair_queue debt check.
_CAPTURED = re.compile(r"\bcapture\s+(\w+)\s+(?:\"[^\"]*\"|'[^']*'|\S+)\s+git\s+show\s+\S*:tools/(\w+)\.py")
_RUN_CAPTURED = re.compile(_PY + _FLAGS + r"\s+-(?=\s|$)" + _ARGS + r"<\s*\"?\$\{?(\w+)\}?\"?", re.I)


# The first word after an interpreter that is not a flag (-c and -m stop the flag run: the code or module
# follows; -X and -W take an argument of their own). Anything that runs a script must name it as
# tools/<word>.py, so a variable, a glob, a hyphen, a subdirectory, a doubled slash, another case, a quote
# split or a cd into tools/ is not hidden; a module named like a script of tools/ (`-m rename`, which runs
# with PYTHONPATH=tools or after a cd) is refused, since `-m tools.<word>` is the one module spelling read.
_RUN_ANY = re.compile(r"(?<![\w./$\"{}-])(?i:" + _PY + r")(?:\s+-[XW]\s+\S+|\s+-[A-Za-bd-ln-z]\w*)*\s+(-m\s+)?(\S+)")
_SCRIPT = re.compile(r"(?:\./)?tools/\w+\.py")
_MODULE = re.compile(r"tools\.\w+")


def unreadable_runs(text):
    """[(interpreter word, what follows)] for each run of an interpreter in stripped hook `text` that this
    test cannot read as `tools/<word>.py` or `-m tools.<word>`. A word with no path, variable or dot in it
    (`python syntax error` in an echo) is no script; `-c` code, `-` (stdin) and a module outside tools
    (`-m pytest`) are not tools."""
    out = []
    for match in _RUN_ANY.finditer(text):
        module, word = match.group(1), match.group(2)
        if module:
            if re.match(r"tools\b", word) and not _MODULE.fullmatch(word.strip("'\"")):
                out.append((match.group(0).split()[0], "-m " + word))
            elif re.fullmatch(r"\w+", word) and (TOOLS / f"{word}.py").is_file():
                out.append((match.group(0).split()[0], "-m " + word))      # PYTHONPATH=tools or a cd into it
        elif word.startswith("-") or not re.search(r"[/$\\.`]", word):
            continue
        elif not _SCRIPT.fullmatch(word.strip("'\"")):
            out.append((match.group(0).split()[0], word))
    return out


def hook_mentions(text=None):
    """Every tool the hook names outside a comment, however it is run: as
    `python3 tools/X.py`, `python -u tools/X.py`, `py -3 tools/X.py`, through
    run-python3, from `git show REF:tools/X.py | python3 -`, in a quoted command
    line or as `-m tools.X`. A run of an interpreter whose script is not spelled
    as exactly tools/<word>.py (a variable, a glob, a hyphen, a subdirectory, a
    doubled slash, another case, a path split by quotes, a cd into tools/) cannot
    be read here and fails, as does any `tools/` path built from a shell
    expansion or a quote, so no run of a tool named that way is hidden. A tool
    run by another interpreter spelling than the ones above is not seen; a bare `-m word` is refused only when
    tools/word.py exists."""
    text = strip_shell_comments(HOOK.read_text() if text is None else text)
    dynamic = re.findall(r"tools/[^\s'\"]*[$`][^\s'\"]*|tools/['\"]\S*", text)
    assert not dynamic, f"the hook builds a tools/ path from a shell expansion: {dynamic}"
    odd = unreadable_runs(text)
    assert not odd, f"the hook runs a script this test cannot read as tools/<word>.py: {odd}"
    return sorted({a or b for a, b in _MENTION.findall(text)})


def hook_invocations(text=None):
    """{tool: [argument tokens of each run of `tools/<tool>.py` in the hook, shell
    variables left out]}, for every spelling hook_mentions reads and that runs the
    tool with arguments after it. A mention this cannot read as a run is missing
    here and still judged by hook_mentions."""
    text = strip_shell_comments(HOOK.read_text() if text is None else text)
    captured = dict(_CAPTURED.findall(text))          # {variable: tool} of each captured HEAD copy
    found = {}

    def add(tool, args):
        try:
            tokens = shlex.split(args, comments=True)
        except ValueError:       # the run sits inside a quoted command line: its closing quote
            tokens = shlex.split(args.rstrip("'\" "), comments=True)
        found.setdefault(tool, []).append([t for t in tokens if "$" not in t])
    for line in text.splitlines():
        for pattern in (_RUN_PATH, _RUN_STDIN):
            for match in pattern.finditer(line):
                add(match.group(1), match.group(2))
        for match in _RUN_CAPTURED.finditer(line):
            if match.group(2) in captured:
                add(captured[match.group(2)], match.group(1))
    return found


def test_every_commit_check_is_a_command_the_hook_runs_with_the_same_arguments(tree):
    ctx = ctx_of(tree)
    plan = rename.Plan("function", OLD, NEW, "inferred", "", UNIT, 0x00401000, verify=[UNIT])
    paths = sorted(set(rename.COMMIT_LEDGER_FILES) | set(rename.NAME_LEDGER_FILES) | {UNIT})
    jobs = rename._hook_jobs(ctx, plan, paths)
    assert set(jobs) >= {"class_gate", "ledger_guard", "code_identity_gate", "link_debt", "check_case_collisions",
                         "hatch_counters", "data_check", "pin_admission", "pin_consistency", "name_dependents",
                         "data_converged", "eh_verify"}
    hook = hook_invocations()
    for label, (tool, args, _stdin) in jobs.items():
        mine = [a for a in args if "{" not in a]
        assert mine in hook.get(tool, []), \
            f"{label}: .githooks/pre-commit never runs tools/{tool}.py {' '.join(mine)}; hook has {hook.get(tool)}"


def test_the_ledger_files_that_switch_on_the_ledger_checks_are_the_hooks():
    text = HOOK.read_text()
    cases = {tuple(m.split("|")) for m in re.findall(r"^\s*((?:reverse/[\w./]+\|)+reverse/[\w./]+)\) ledger_changed=1",
                                                      text, re.M)}
    assert cases == {tuple(rename.COMMIT_LEDGER_FILES)}, cases


# What the pre-commit hook runs that rename.py does not mirror in _hook_jobs, and why. A tool the
# hook runs must be a job (or one of the two run by _csv_checks) or be listed here: adding a check to
# the hook fails test_every_tool_the_hook_runs_is_mirrored_or_exempt until someone decides which.
CSV_CHECKS = {
    "check_csv": "run by _csv_checks (whole ledger, not --staged)",
    "find_declared_unmatched": "run by _csv_checks over the plan's units",
}
HOOK_EXEMPT = {
    "merge_rows": "union merge driver registration, not a check",
    "conversion_gate": "refuses a row repointed to assembly; a rename repoints no row",
    "tu_ownership": "shadow mode (--shadow) and a rename keeps each unit's owner",
    "invented_names": "shadow mode (--shadow); judges invented names and a rename invents none",
    "header_dependents": "units a header edit reaches; a rename edits no header outside the plan's builds",
    "flag_defaults": "flag overrides edited by hand; rename.py refuses a file keyed in flag_overrides.csv",
    "delta_sources": "chooses the sources the hook builds; the plan names the sources it builds itself",
    "link_check": "shadow mode (--shadow) against the link census",
    "build": "run_build's byte verification; rename.py runs ./build.sh over the plan's units itself (_verify)",
    "gate_baseline": "shrink-only assertion, piped in from HEAD (`git show HEAD:tools/gate_baseline.py | python3 -`); "
                     "rename.py never edits reverse/gate_baseline.txt (FROZEN_KEYED refuses a name keyed there)",
    "repair_queue": "verify-removed re-checks rows whose gate-debt line a commit deleted, run from HEAD's copy "
                    "(captured, then fed on stdin); rename.py deletes no baseline line",
    "image_ownership": "check-history runs only when reverse/image_ownership_history.csv is staged, a file only the "
                       "publisher seat writes (signed); rename.py never names or edits it",
    "obstacle_ids": "a LINK ID heading two docs/linking_obstacles/ entries; rename.py edits no obstacle entry (it "
                    "reports docs mentions, never rewrites them)",
    "push_receipts": "record-commit writes the commit receipt after the checks pass; it judges nothing",
    "stlport_overlay": "named only as an input path (the STLport git diff binding and the wide-change case "
                       "patterns); the hook runs no check of that name",
    "data_rows": "named only in a python comment inside the hook's embedded script; the hook runs no check of that name",
}


def mirrored_tools(tree):
    ctx = ctx_of(tree)
    plan = rename.Plan("function", OLD, NEW, "inferred", "", UNIT, 0x00401000, verify=[UNIT])
    paths = sorted(set(rename.COMMIT_LEDGER_FILES) | set(rename.NAME_LEDGER_FILES) | {UNIT})
    return {tool for tool, _args, _stdin in rename._hook_jobs(ctx, plan, paths).values()} | set(CSV_CHECKS)


def unjudged_tools(text, mirrored):
    return sorted(set(hook_mentions(text)) - mirrored - set(HOOK_EXEMPT))


def test_every_tool_the_hook_runs_is_mirrored_or_exempt(tree):
    mirrored = mirrored_tools(tree)
    hook = set(hook_mentions())
    unjudged = unjudged_tools(HOOK.read_text(), mirrored)
    assert not unjudged, (f".githooks/pre-commit runs {unjudged}, which rename.py neither mirrors in _hook_jobs "
                          "nor lists in HOOK_EXEMPT with the reason a rename cannot change what it judges")
    both = sorted(set(HOOK_EXEMPT) & mirrored)
    assert not both, f"{both} are exempt here yet mirrored: drop the exemption"
    stale = sorted((set(HOOK_EXEMPT) | set(CSV_CHECKS)) - hook)
    assert not stale, f"{stale} are listed here but the hook no longer runs them"


# Every way the hook could spell a run of a tool. A new check in any of these spellings is read by
# hook_mentions (so the test above judges it) and by hook_invocations (so the arguments are compared).
SPELLINGS = [
    "python3 tools/zz_new.py --staged",
    "python tools/zz_new.py --staged",
    "python3.11 tools/zz_new.py --staged",
    "/usr/bin/python3 tools/zz_new.py --staged",
    "python3 -u tools/zz_new.py --staged",
    "python3 -I -B tools/zz_new.py --staged",
    "py -3 tools/zz_new.py --staged",
    "py -3.11 tools/zz_new.py --staged",
    'shadow_cap python3 tools/zz_new.py --staged',
    '"$PYTHON3" tools/zz_new.py --staged',
    "sh .githooks/run-python3 tools/zz_new.py --staged",
    "python3 ./tools/zz_new.py --staged",
    "git show HEAD:tools/zz_new.py | python3 - --staged",
    "git show HEAD:tools/zz_new.py | python - --staged",
    "git show HEAD:tools/zz_new.py|python3 -u - --staged",
    "git show :tools/zz_new.py | py -3 - --staged",
    'capture zz "loading zz" git show HEAD:tools/zz_new.py; python3 - --staged < "$zz"',
    "python3 -m tools.zz_new --staged",
    "bash -c 'python3 tools/zz_new.py --staged'",
]
HOOK_SNIPPET = "if [ -n \"$x\" ]; then\n    {run} || fail \"zz\"\nfi\n"


@pytest.mark.parametrize("spelling", SPELLINGS)
def test_a_new_hook_check_is_found_in_every_spelling(spelling, tree):
    text = HOOK.read_text() + HOOK_SNIPPET.format(run=spelling)
    assert "zz_new" in hook_mentions(text)
    assert unjudged_tools(text, mirrored_tools(tree)) == ["zz_new"]
    if "-m tools." not in spelling:
        assert ["--staged"] in hook_invocations(text).get("zz_new", []), hook_invocations(text).get("zz_new")


def test_a_captured_head_copy_run_on_stdin_is_read_with_its_arguments():
    text = ('capture chk "loading HEAD checker" git show HEAD:tools/zz_new.py\n'
            'args=()\npython3 - verify-x "${args[@]}" < "$chk" || fail x\n'
            'python3 - other < "$unknown"\n')
    assert hook_invocations(text) == {"zz_new": [["verify-x"]]}
    assert hook_mentions(text) == ["zz_new"]


def test_a_continued_and_a_quoted_run_are_found():
    text = 'python3 -u \\\n    tools/zz_new.py --a \\\n    --b || fail x\n'
    assert hook_invocations(text) == {"zz_new": [["--a", "--b"]]}
    assert hook_mentions("x='python tools/zz_new.py'\n") == ["zz_new"]


def test_the_hooks_own_stdin_runs_are_read_with_their_arguments():
    runs = hook_invocations()
    assert runs["gate_baseline"] == [["--assert-shrink-only", "HEAD"]]
    assert runs["repair_queue"] == [["verify-removed"]]
    assert ["--staged", "--shadow"] in runs["tu_ownership"]


@pytest.mark.parametrize("text, tools", [
    ("# python3 tools/zz_new.py\n", []),
    ("echo hi # python3 tools/zz_new.py\n", []),
    ("echo \"a # b\" python3 tools/zz_new.py\n", ["zz_new"]),
    ("echo 'a # b' python3 tools/zz_new.py\n", ["zz_new"]),
    ("n=${#arr[@]}; python3 tools/zz_new.py\n", ["zz_new"]),
    ("# comment ending in a backslash \\\npython3 tools/zz_new.py\n", ["zz_new"]),
    ("git diff -- 'tools/*.py'\n", []),
])
def test_comments_hide_a_mention_and_quotes_do_not(text, tools):
    assert hook_mentions(text) == tools


def test_a_tool_path_built_from_a_variable_is_refused():
    with pytest.raises(AssertionError, match="shell expansion"):
        hook_mentions('python3 "tools/$name.py" --staged\n')


def test_an_unbalanced_quote_is_refused_not_guessed_at():
    with pytest.raises(AssertionError, match="unbalanced"):
        hook_mentions("echo 'oops\npython3 tools/zz_new.py\n")


@pytest.mark.parametrize("run", [
    "python3 tools/zz-new.py",
    'T=tools; python3 "$T/zz_new.py"',
    'for f in tools/zz_*.py; do python3 "$f"; done',
    "cd tools && python3 zz_new.py",
    "python3 tools/sub/zz_new.py",
    "python3 tools\\zz_new.py",
    "python3 tools/zz_new.PY",
    "python3 tools//zz_new.py",
    'python3 tools/"$n".py',
    "python3 tools/'zz'_new.py",
    "python3 tools/`echo zz_new`.py",
    "python3 -m tools.sub.zz_new",
    "python3 -m tools.zz-new",
    "PYTHONPATH=tools python3 -m rename --help",
    "cd tools; python3 -m rename",
    "python3 -X dev -m rename",
    "python3 -W error -X utf8 -m name_metric",
    "python3 -u ./tools/sub/zz_new.py --staged",
    "git show HEAD:tools/zz_new.py | python3 $script",
])
def test_a_run_whose_script_is_not_exactly_a_tools_path_is_refused_not_hidden(run):
    with pytest.raises(AssertionError, match="shell expansion|cannot read as tools"):
        hook_mentions(run + "\n")


@pytest.mark.parametrize("text, tools", [
    ('fail "python syntax error in a staged tool (see above)"\n', []),
    ("python3 -c 'import sys; print(1)'\n", []),
    ("printf '' | python3 - --staged\n", []),
    ("python3 -m pytest tools/tests -q\n", []),
    ("cp a b 2>/dev/null; py -3 tools/zz_new.py\n", ["zz_new"]),
    ("python3 'tools/zz_new.py' --staged\n", ["zz_new"]),
])
def test_a_run_that_names_no_script_or_a_plain_one_is_read_as_it_is(text, tools):
    assert hook_mentions(text) == tools
