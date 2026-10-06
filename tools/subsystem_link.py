#!/usr/bin/env python3
"""Build one subsystem as a static library and link it into a harness, without /FORCE.

The pillar-3 acceptance link (docs/subsystem_template.md). It answers "is this
directory real source?": every translation unit compiles with its own `// cl:`
line, the objects become one .lib, and a small harness links against it with
the real VC7.1 linker. No /FORCE, so a duplicate definition or an unresolved
name fails the link.

The harness may define the subsystem's EXTERNAL dependencies (other libraries'
symbols) in its extern file. It may never define the subsystem's own symbols:
any name the extern file defines that also matches --own is refused, and so is
an own-class name the library leaves undefined unless it is listed with
--allow (each allow needs a reason in the template's queue item).

  python3 tools/subsystem_link.py Code/Libraries/Source/profile \\
      --harness tools/tests/subsystem_harness/profile_main.cpp \\
      --externs tools/tests/subsystem_harness/profile_externs.cpp \\
      --own Profile --own ProfileId --own ProfileHighLevel ... [--allow SYMBOL] [--run]

Outputs in build/subsystem/<dir name>/: <name>.lib, harness.exe, link.log, report.json.
Exit 0 only when every TU compiles, the link succeeds without /FORCE, and the
own-symbol rules hold.
"""
import argparse
import json
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402

SYSTEM_LIBS = ["msvcrt.lib", "oldnames.lib", "kernel32.lib", "user32.lib", "winmm.lib", "advapi32.lib"]


def toolchain():
    import os
    root = Path(os.environ.get("VC71_ROOT", build.DEFAULT_VC71_ROOT))
    return root, root / "Vc7" / "bin"


def run(cmd, env=None):
    res = subprocess.run(cmd, capture_output=True, text=True, errors="replace", env=env, cwd=ROOT)
    return res.returncode, res.stdout + res.stderr


def symbols(dumpbin, obj, env):
    """(defined, undefined) external names of one object."""
    code, out = run([str(dumpbin), "/NOLOGO", "/SYMBOLS", str(obj)], env)
    if code:
        raise SystemExit(f"subsystem_link: dumpbin failed on {obj}:\n{out[-1500:]}")
    defined, undefined = set(), set()
    for line in out.splitlines():
        m = re.search(r"\s(SECT\w+|UNDEF)\s.*External\s+\|\s+(\S+)", line)
        if m:
            (undefined if m.group(1) == "UNDEF" else defined).add(m.group(2))
    return defined, undefined


def owns(name, classes):
    """True when a decorated name is a member of (or nested in) one of `classes`."""
    # ??0X@@ ctor, ??1X@@ dtor, ??_7X@@6B@ vftable, ??_GX@@ deleting dtor
    return any(re.search(rf"@{re.escape(c)}@@", name) or re.search(rf"@{re.escape(c)}@[^@]", name)
               or re.match(rf"\?\?(?:_\w|\d){re.escape(c)}@", name)
               for c in classes)


def compile_one(source, out):
    ok, text, code = build.try_compile_source(source, out)
    if not ok:
        print(f"subsystem_link: compile FAILED {source.relative_to(ROOT)} (exit {code})\n{text[-3000:]}")
    return ok


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("directory")
    ap.add_argument("--harness", required=True)
    ap.add_argument("--externs", action="append", default=[])
    ap.add_argument("--own", action="append", default=[], help="class owned by the subsystem")
    ap.add_argument("--allow", action="append", default=[], help="own symbol the library may leave undefined")
    ap.add_argument("--run", action="store_true", help="run the linked harness")
    args = ap.parse_args(argv)

    directory = (ROOT / args.directory).resolve()
    name = directory.name
    out = ROOT / "build" / "subsystem" / name
    out.mkdir(parents=True, exist_ok=True)
    root, bindir = toolchain()
    env = build.compiler_environment(root)

    tus = sorted(p for p in directory.glob("*.cpp"))
    objs, failed = [], False
    for tu in tus:
        obj = out / (tu.stem + ".obj")
        failed |= not compile_one(tu, obj)
        objs.append(obj)
    harness_objs = []
    for src in [args.harness] + args.externs:
        obj = out / ("harness_" + Path(src).stem + ".obj")
        failed |= not compile_one(ROOT / src, obj)
        harness_objs.append(obj)
    if failed:
        return 1

    lib = out / f"{name}.lib"
    code, text = run([str(bindir / "lib.exe"), "/NOLOGO", f"/OUT:{lib}"] + [str(o) for o in objs], env)
    if code:
        print(f"subsystem_link: lib.exe failed\n{text}")
        return 1

    dumpbin = bindir / "dumpbin.exe"
    lib_def, lib_undef = set(), set()
    for o in objs:
        d, u = symbols(dumpbin, o, env)
        lib_def |= d
        lib_undef |= u
    ext_def = set()
    for o in harness_objs[1:]:
        ext_def |= symbols(dumpbin, o, env)[0]
    unresolved_in_lib = sorted(lib_undef - lib_def)
    problems = []
    for s in sorted(ext_def):
        if owns(s, args.own) and s not in args.allow:
            problems.append(f"harness externs define an own symbol: {s}")
    for s in unresolved_in_lib:
        if owns(s, args.own) and s not in args.allow:
            problems.append(f"library leaves an own symbol undefined: {s}")

    exe = out / "harness.exe"
    libpaths = [root / "Vc7" / "lib", root / "Vc7" / "PlatformSDK" / "Lib"]
    cmd = ([str(bindir / "link.exe"), "/NOLOGO", "/SUBSYSTEM:CONSOLE", "/OPT:REF", f"/OUT:{exe}",
            f"/MAP:{out / 'harness.map'}"] + [f"/LIBPATH:{p}" for p in libpaths]
           + [str(o) for o in harness_objs] + [str(lib)] + SYSTEM_LIBS)
    assert "/FORCE" not in " ".join(cmd)
    code, text = run(cmd, env)
    (out / "link.log").write_text(text)
    link_errors = [line for line in text.splitlines() if re.search(r"\bLNK\d{4}\b", line)]
    if code:
        problems.append(f"link failed (exit {code}): " + "; ".join(link_errors[:20]))

    ran = None
    if args.run and not code:
        rc, rtext = run([str(exe)], env)  # env PATH carries msvcr71.dll (Common7/IDE)
        ran = {"exit": rc, "output": rtext[-2000:]}
        if rc:
            problems.append(f"harness exited {rc}")

    report = {"directory": args.directory, "translation_units": [t.name for t in tus],
              "lib": str(lib.relative_to(ROOT)), "link_exit": code, "link_messages": link_errors,
              "external_dependencies": [s for s in unresolved_in_lib if not owns(s, args.own)],
              "allowed_own_undefined": [s for s in unresolved_in_lib if owns(s, args.own)],
              "harness_extern_definitions": sorted(ext_def), "run": ran, "problems": problems}
    (out / "report.json").write_text(json.dumps(report, indent=1))
    print(f"subsystem_link: {len(tus)} TUs -> {lib.name}; {len(report['external_dependencies'])} external "
          f"dependencies; harness externs define {len(ext_def)}; link exit {code}")
    for p in problems:
        print(f"  FAIL {p}")
    if ran:
        print(f"  harness exit {ran['exit']}: {ran['output'].strip()[:400]}")
    print("subsystem_link: OK" if not problems else "subsystem_link: FAIL")
    return 1 if problems else 0


if __name__ == "__main__":
    sys.exit(main())
