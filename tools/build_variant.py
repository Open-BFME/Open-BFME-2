#!/usr/bin/env python3
"""Plan or compile isolated modern objects; never write verifier artifacts.

Called by build.sh --variant modern. This entry point deliberately has no
implicit action: a plan is not a compile, link, or verification result.
"""
import argparse
import hashlib
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
DEFINES = ("BFME2_MODERN=1",)


def variant_paths(root, variant):
    """Validate every output directory, without creating or changing anything."""
    if variant != "modern":
        raise ValueError("only the explicit modern variant is supported here")
    root = Path(root).resolve(strict=True)
    paths = {name: root / "build" / "modern" / name
             for name in ("objects", "link", "reports")}
    for path in paths.values():
        for directory in (root / "build", root / "build/modern", path):
            # resolve follows Windows junctions as well as POSIX symlinks.
            if directory.resolve() != directory or directory.is_symlink():
                raise ValueError(f"redirected variant directory: {directory}")
            if directory.exists() and not directory.is_dir():
                raise ValueError(f"variant directory is a file: {directory}")
    return paths


def compile_sources(names, *, root=ROOT):
    import build
    root = Path(root).resolve(strict=True)
    paths = variant_paths(root, "modern")
    sources = []
    for name in names:
        source = (root / name).resolve()
        if (not source.is_relative_to(root / "Code") or not source.is_file()
                or source.suffix.lower() not in (".cpp", ".c", ".asm")):
            raise ValueError(f"invalid modern source: {name}")
        sources.append(source)
    if not sources:
        raise ValueError("at least one source is required")
    if root != build.ROOT.resolve():
        raise ValueError("compiler root differs from source root")
    context = build.CompilationContext()
    jobs = [(source, paths["objects"] / build.obj_path(source).name)
            for source in dict.fromkeys(sources)]
    if len({output for _, output in jobs}) != len(jobs):
        raise ValueError("source names collide in object namespace")
    for _, output in jobs:
        context.validate_output(output)
    compiled = []
    for source, output in jobs:
        build.compile_source(source, output, inventory=True, context=context)
        if not build.compile_is_current(source, output, strict=True, context=context):
            raise ValueError(f"compile receipt did not prove inputs: {source}")
        compiled.append({"source": source.relative_to(root).as_posix(),
                         "object": output.relative_to(root).as_posix(),
                         "sha256": hashlib.sha256(output.read_bytes()).hexdigest()})
    return compiled


def main(argv=None, *, root=ROOT):
    parser = argparse.ArgumentParser(description=__doc__)
    action = parser.add_mutually_exclusive_group(required=True)
    action.add_argument("--plan", action="store_true",
                        help="print validated output layout without compiling or writing")
    action.add_argument("--compile", nargs="+", metavar="SOURCE",
                        help="compile explicit Code sources with modern definitions; does not link")
    action.add_argument("--link-base", action="store_true",
                        help="link the verified reference objects as an isolated local baseline")
    args = parser.parse_args(argv)
    try:
        paths = variant_paths(root, "modern")
        if args.link_base:
            import exit_link
            if Path(root).resolve() != exit_link.ROOT.resolve():
                raise ValueError("linker root differs from variant root")
            return exit_link.run_local_base(exit_link.census.ledger())
        objects = compile_sources(args.compile, root=root) if args.compile else []
    except (OSError, RuntimeError, ValueError) as error:
        parser.error(str(error))
    print(json.dumps({"variant": "modern", "action": "compile" if args.compile else "plan",
                      "compiled": bool(args.compile), "linked": False, "objects": objects,
                      "defines": list(DEFINES),
                      "paths": {key: str(value) for key, value in paths.items()}}, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
