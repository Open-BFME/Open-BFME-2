#!/usr/bin/env python3
"""Plan or compile isolated modern objects; never write verifier artifacts.

Called by build.sh --variant modern. This entry point deliberately has no
implicit action: a plan is not a compile, link, or verification result.
"""
import argparse
import hashlib
import json
import re
import struct
import uuid
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
DEFINES = ("BFME2_MODERN=1",)


def replace_response_objects(text, replacements):
    """Accept only exit_link's generated input/DEF/INCLUDE line grammar."""
    counts = dict.fromkeys(replacements, 0)
    result = []
    for line in text.splitlines():
        if re.fullmatch(r'"[^"\r\n]+\.(?:obj|lib)"', line):
            old = line[1:-1]
            if old in replacements:
                counts[old] += 1
                line = '"' + replacements[old] + '"'
        elif not (re.fullmatch(r'/DEF:"[^"\r\n]+\.def"', line) or
                  re.fullmatch(r'/INCLUDE:[^\s"@]+(?:@\d+)?', line)):
            raise ValueError(f"unsupported baseline response line: {line}")
        result.append(line)
    if any(count != 1 for count in counts.values()):
        raise ValueError("each replaced object must occur exactly once")
    return "\n".join(result) + "\n"


def replacement_code_names(original, replacement):
    import exit_link as link
    sections, symbols, _ = link.coff_view(original)
    _, modern_symbols, _ = link.coff_view(replacement)
    missing = link.external_definitions(symbols) - link.external_definitions(modern_symbols)
    if missing:
        raise ValueError(f"replacement loses external definitions: {sorted(missing)}")
    return {s.name for s in symbols.values() if s.cls == link.link_cycle.EXTERNAL
            and 0 < s.sec <= len(sections) and sections[s.sec - 1].flags & 0x20}


def check_consumer_offsets(inputs, replaced, names):
    """No retained consumer may assume offsets inside a replaced code symbol."""
    import coffar
    import link_cycle
    references = 0
    for path in inputs:
        if path in replaced or path.suffix.lower() not in (".obj", ".lib"):
            continue
        members = coffar.read_archive(path) if path.suffix.lower() == ".lib" else [(path.name, path.read_bytes())]
        for member, raw in members:
            # Standard short import records contain an imported name, no COFF relocations.
            if len(raw) >= 20 and raw[:8] == b"\0\0\xff\xff\0\0\x4c\x01":
                continue
            neutral = raw[:2] == b"\0\0" and raw[2:4] != b"\xff\xff"
            if len(raw) < 20 or (raw[:2] != b"\x4c\x01" and not neutral):
                raise ValueError(f"unsupported COFF consumer {path}:{member}")
            sections, symbols = link_cycle.parse_coff(raw)
            if neutral:
                # VC7's CRT contains machine-neutral directive/weak-name members.
                # They cannot contain executable code or relocation addends.
                if (not sections or any(s.name != ".drectve" or s.relocs or s.flags & 0x20 for s in sections)
                        or any(s.sec > 0 and s.cls == link_cycle.EXTERNAL for s in symbols.values())):
                    raise ValueError(f"unsupported COFF neutral consumer {path}:{member}")
                continue
            for section in sections:
                for offset, index, kind in section.relocs:
                    if symbols[index].name not in names:
                        continue
                    if kind not in (6, 7, 20):
                        raise ValueError(f"unsupported replacement relocation {path}:{member}")
                    references += 1
                    if struct.unpack_from("<i", raw, section.ptr + offset)[0]:
                        raise ValueError(f"interior reference to {symbols[index].name} in {path}:{member}")
    return references


def link_input_manifest(response, *, root=ROOT):
    """Hash every explicit input of exit_link's generated response file.

    Includes archives and resource objects, even if they supply no MAP public.
    The exit_link control-file contract places retail.def beside the response.
    Call before and after the link; this is evidence, not a currency override.
    """
    import image_iso
    root = Path(root).resolve(strict=True)
    response = Path(response).resolve(strict=True)
    paths = set(image_iso.response_inputs(response, root))
    paths.update((response, response.with_name("retail.def")))
    entries = []
    for path in sorted(paths):
        path = path.resolve(strict=True)
        relative = path.relative_to(root).as_posix()
        entries.append({"path": relative,
                        "sha256": hashlib.sha256(path.read_bytes()).hexdigest()})
    return entries


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


def link_modern(base, names):
    """Relink an unchanged, proven local baseline with explicit modern TUs.

    The baseline's omitted scaffolds stay omitted. New compiler-generated EH
    belongs to its modern parent; no modified body is called retail-EXACT.
    """
    import build
    import exit_link as link
    import image_iso
    paths = variant_paths(ROOT, "modern")
    base = (ROOT / base).absolute()
    if (base.resolve() != base or base.parent != paths["link"] or
            not re.fullmatch(r"base-[0-9a-f]{32}", base.name)):
        raise ValueError("modern link requires an isolated local baseline")
    result = json.loads((base / "result.json").read_text())
    receipt = json.loads((base / "image_receipt.json").read_text())
    manifest = json.loads((base / "variant_inputs.json").read_text())
    if (result.get("mode") != "local-base-link" or result.get("force") is not False or
            result.get("stubs") is not False or result["link"]["exit"] != 0 or
            result["link"]["pe_defect"] is not None or manifest.get("link_exit") != 0 or
            receipt.get("variant") != "modern-base" or receipt.get("stubbed") != []):
        raise ValueError("baseline is not a successful non-stub local link")
    for key, filename in (("image_sha256", "exit.exe"), ("map_sha256", "exit.map")):
        if link.digest(base / filename) != receipt[key]:
            raise ValueError(f"baseline {filename} changed")
    response = base / "exit.rsp"
    if link_input_manifest(response) != manifest["inputs"]:
        raise ValueError("baseline link inputs changed")
    if not names:
        raise ValueError("modern link needs explicit replacement sources")
    inputs = image_iso.response_inputs(response, ROOT)
    context = build.CompilationContext()
    substitutions, replacements, code_names, replaced = {}, [], set(), set()
    for name in dict.fromkeys(names):
        source = (ROOT / name).resolve(strict=True)
        if not source.is_relative_to(ROOT / "Code") or source.suffix.lower() not in (".c", ".cpp"):
            raise ValueError(f"invalid modern replacement source: {name}")
        original = build.obj_path(source)
        modern = paths["objects"] / original.name
        if original not in inputs or not build.compile_is_current(source, original):
            raise ValueError(f"baseline source is absent or stale: {name}")
        if not build.compile_is_current(source, modern, strict=True, context=context):
            raise ValueError(f"modern compile is absent or stale: {name}")
        code_names.update(replacement_code_names(original, modern))
        replaced.add(original)
        substitutions[original.relative_to(ROOT).as_posix()] = modern.relative_to(ROOT).as_posix()
        replacements.append({"source": source.relative_to(ROOT).as_posix(),
                             "object": modern.relative_to(ROOT).as_posix(),
                             "sha256": link.digest(modern), "source_sha256": link.digest(source),
                             "baseline_object_sha256": link.digest(original),
                             "compiler_command": build.compiler_command(source, modern, context=context)[0]})
    references = check_consumer_offsets(inputs, replaced, code_names)
    text = replace_response_objects(response.read_text(encoding="utf-8"), substitutions)
    out = paths["link"] / ("modern-" + uuid.uuid4().hex)
    out.mkdir()
    (out / "retail.def").write_bytes((base / "retail.def").read_bytes())
    text = text.replace('/DEF:"' + (base / "retail.def").relative_to(ROOT).as_posix() + '"',
                        '/DEF:"' + (out / "retail.def").relative_to(ROOT).as_posix() + '"')
    rsp = out / "exit.rsp"
    rsp.write_text(text, encoding="utf-8")
    image = out / "exit.exe"
    command = [str(build.vc71_root() / "Vc7/bin/link.exe"), *link.link_arguments(image, rsp)]
    before = link_input_manifest(rsp)
    tree = link.census.census_inputs_state()
    tool_state = (link.tool_digests(), link.digest(Path(__file__)))
    linked = link.run_native(command)
    (out / "link.log").write_text(linked.stdout + linked.stderr, encoding="utf-8")
    if (link_input_manifest(rsp) != before or link.census.census_inputs_state() != tree or
            (link.tool_digests(), link.digest(Path(__file__))) != tool_state):
        raise ValueError("modern link inputs or tools changed during linking")
    record = {"mode": "local-modern-link", "authoritative": False,
              "tree": tree, "tools": tool_state[0], "variant_tool_sha256": tool_state[1],
              "baseline_image_sha256": receipt["image_sha256"], "replacements": replacements,
              "consumer_references_checked": references, "inputs": before,
              "command": command, "link_exit": linked.returncode, "force": False, "stubs": False,
              "initializer_bridge": result["initializer_bridge"],
              "vtables_bridged": receipt["vtables_bridged"],
              "vtable_slots_bridged": receipt["vtable_slots_bridged"]}
    (out / "variant_inputs.json").write_text(json.dumps(record, indent=2) + "\n", encoding="utf-8")
    print(f"modern link: exit {linked.returncode}, output {out.relative_to(ROOT)}")
    if linked.returncode != 0 or not image.exists():
        return 1
    defect = link.census.pe_defect(image)
    if defect:
        raise ValueError(f"modern PE defect: {defect}")
    link.image_receipt(image, False, set(), vtables=result.get("vtable_bridge"))
    path = out / "image_receipt.json"
    modern_receipt = json.loads(path.read_text())
    modern_receipt.update(authoritative=False, variant="modern", local_fork=True,
                          baseline_image_sha256=receipt["image_sha256"],
                          modified_sources=[entry["source"] for entry in replacements])
    path.write_text(json.dumps(modern_receipt, indent=2) + "\n", encoding="utf-8")
    image_iso.write_object_manifest(rsp, image.with_suffix(".map"), out / "image_objects.json", cwd=ROOT)
    return 0


def main(argv=None, *, root=ROOT):
    parser = argparse.ArgumentParser(description=__doc__)
    action = parser.add_mutually_exclusive_group(required=True)
    action.add_argument("--plan", action="store_true",
                        help="print validated output layout without compiling or writing")
    action.add_argument("--compile", nargs="+", metavar="SOURCE",
                        help="compile explicit Code sources with modern definitions; does not link")
    action.add_argument("--link-base", action="store_true",
                        help="link the verified reference objects as an isolated local baseline")
    action.add_argument("--link-modern", nargs="+", metavar="BASE_OR_SOURCE",
                        help="baseline directory followed by explicit modern replacement sources")
    action.add_argument("--blob", action="store_true",
                        help="link the changed modern code into a loader blob for the 1.06 baseline "
                             "and build the loader DLL (build/modern/blob); not a verification result")
    args = parser.parse_args(argv)
    try:
        paths = variant_paths(root, "modern")
        if args.link_modern:
            if Path(root).resolve() != ROOT or len(args.link_modern) < 2:
                raise ValueError("modern link needs the repository root, baseline and source(s)")
            return link_modern(args.link_modern[0], args.link_modern[1:])
        if args.blob:
            import modern_blob
            if Path(root).resolve() != ROOT:
                raise ValueError("the blob needs the repository root")
            out = paths["reports"].parent / "blob"
            blob, report = modern_blob.build_blob(out)
            dll = modern_blob.build_loader(out)
            print(json.dumps({"variant": "modern", "action": "blob", "authoritative": False,
                              "blob": str(blob.relative_to(ROOT)), "loader": str(dll.relative_to(ROOT)),
                              "hooks": len(report["hooks"]), "size": report["size"],
                              "relocation_sites_checked": report["relocation_sites_checked"],
                              "warnings": report["warnings"]}, indent=2))
            return 0
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
