"""No function in tools/ reads a module-scope name that nothing binds.

A function body is compiled without resolving its globals, so `repair_queue.ROOT`
in a module that never imports `repair_queue` is a NameError that waits until
that line runs. Two of those shipped:

- `next_work.build_debt` raised for every non-structural debt queue (repair,
  link, data, header, identity). Its own tests passed throughout, because none
  of them reaches that branch.
- `data_rows.admit_agreed` raised for every unrowed admission after a refactor
  removed `existing = load()` but left a read of `existing` 50 lines below
  (66e3867c704, fixed at 88fda10ed73).

Neither needed a fixture to find: both are visible in the AST. This walks every
top-level function in tools/ and reports names it reads that are bound neither
locally, nor at module scope, nor by builtins. It is deliberately conservative
-- it models the binding forms this tree uses and nothing more, so a new form
shows up as a false positive rather than a silent pass. There are no star
imports in tools/, which would defeat it.
"""
import ast
import builtins
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
MODULES = sorted(p for p in TOOLS.glob("*.py"))
DUNDERS = {"__file__", "__name__", "__doc__", "__package__", "__spec__", "__loader__"}


def module_bindings(tree):
    """Names bound at module scope, descending into if/for/while/with/try but
    not into a def or class, whose bodies are their own scope."""
    found = set()

    def collect(body):
        for node in body:
            if isinstance(node, (ast.FunctionDef, ast.AsyncFunctionDef, ast.ClassDef)):
                found.add(node.name)
            elif isinstance(node, (ast.Import, ast.ImportFrom)):
                found.update((a.asname or a.name).split(".")[0] for a in node.names)
            elif isinstance(node, (ast.Assign, ast.AnnAssign, ast.AugAssign)):
                targets = node.targets if isinstance(node, ast.Assign) else [node.target]
                for target in targets:
                    found.update(n.id for n in ast.walk(target) if isinstance(n, ast.Name))
            elif isinstance(node, (ast.If, ast.For, ast.AsyncFor, ast.While,
                                   ast.With, ast.AsyncWith, ast.Try)):
                for attr in ("body", "orelse", "finalbody", "handlers"):
                    for sub in getattr(node, attr, []) or []:
                        if isinstance(sub, ast.ExceptHandler):
                            if sub.name:
                                found.add(sub.name)
                            collect(sub.body)
                        else:
                            collect([sub])

    collect(tree.body)
    return found


def unbound_reads(func, module_names):
    """Names `func` reads that nothing binds for it."""
    bound, read = set(), set()
    for arg in (*func.args.posonlyargs, *func.args.args, *func.args.kwonlyargs,
                func.args.vararg, func.args.kwarg):
        if arg:
            bound.add(arg.arg)
    for node in ast.walk(func):
        if isinstance(node, ast.Name):
            (bound if isinstance(node.ctx, (ast.Store, ast.Del)) else read).add(node.id)
        elif isinstance(node, (ast.Import, ast.ImportFrom)):
            bound.update((a.asname or a.name).split(".")[0] for a in node.names)
        elif isinstance(node, ast.ExceptHandler) and node.name:
            bound.add(node.name)
        elif isinstance(node, (ast.Global, ast.Nonlocal)):
            bound.update(node.names)
        elif isinstance(node, ast.ClassDef):
            bound.add(node.name)
        elif isinstance(node, (ast.FunctionDef, ast.AsyncFunctionDef, ast.Lambda)):
            if node is not func:                    # a nested def: its params bind inside it
                for arg in (*node.args.posonlyargs, *node.args.args, *node.args.kwonlyargs,
                            node.args.vararg, node.args.kwarg):
                    if arg:
                        bound.add(arg.arg)
                bound.add(getattr(node, "name", ""))
    return sorted(read - bound - module_names - set(dir(builtins)) - DUNDERS)


@pytest.mark.parametrize("path", MODULES, ids=lambda p: p.name)
def test_every_function_s_globals_are_bound(path):
    tree = ast.parse(path.read_text(encoding="utf-8"))
    module_names = module_bindings(tree)
    missing = {node.name: unbound_reads(node, module_names)
               for node in tree.body
               if isinstance(node, (ast.FunctionDef, ast.AsyncFunctionDef))
               and unbound_reads(node, module_names)}
    assert missing == {}, (
        f"{path.name} reads names nothing binds; each is a NameError waiting for "
        f"its line to run: {missing}")


def test_the_walker_catches_a_deleted_local():
    """The discriminator: without it the sweep above passes on anything."""
    tree = ast.parse("import os\n\n"
                     "def f(a):\n"
                     "    existing = os.listdir(a)\n"
                     "    return existing\n")
    names = module_bindings(tree)
    assert unbound_reads(tree.body[1], names) == []
    broken = ast.parse("import os\n\n"
                       "def f(a):\n"
                       "    return existing\n")
    assert unbound_reads(broken.body[1], module_bindings(broken)) == ["existing"]


def test_the_walker_does_not_flag_this_tree_s_binding_forms():
    """Forms tools/ actually uses, each of which a naive walker reports."""
    tree = ast.parse(
        "import os\n"
        "if os.name == 'nt':\n"
        "    PLATFORM = 'win'\n"
        "else:\n"
        "    PLATFORM = 'posix'\n"
        "try:\n"
        "    import json as _json\n"
        "except ImportError:\n"
        "    _json = None\n"
        "\n"
        "def f(rows):\n"
        "    import re\n"
        "    class View:\n"
        "        pass\n"
        "    def inner(x):\n"
        "        return x\n"
        "    seen = {inner(r) for r in rows if re.match('a', r)}\n"
        "    try:\n"
        "        pass\n"
        "    except ValueError as error:\n"
        "        print(error)\n"
        "    return PLATFORM, _json, View, seen, __file__\n")
    func = next(n for n in tree.body if isinstance(n, ast.FunctionDef))
    assert unbound_reads(func, module_bindings(tree)) == []
