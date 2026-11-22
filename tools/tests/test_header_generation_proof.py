"""Canonical syntax is input provenance; native facts remain real source facts."""
from copy import deepcopy
from dataclasses import replace
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import header_generation_inputs as I
import header_generation_proof as P


NAME = "Canonical"
HEADER = "Code/Canonical.h"
DECL = "class Canonical {\npublic:\n void *value;\n Canonical(void *held);\n void helper();\n virtual ~Canonical() {}\n};\n"
CONTRACT = {"class": NAME, "key": "class", "size": 8, "bases": [],
            "fields": [{"offset": 0, "name": "__vfptr", "kind": "VPTR", "size": 4},
                       {"offset": 4, "name": "value", "kind": "P", "size": 4, "type": "void*"}],
            "vslots": {"0": "~Canonical()"}}
LAYOUT = {"fwd": False, "key": "class", "size": 8, "bases": [], "fields": [[4, "value", "void*", 4]],
          "statics": [], "methods": ["Canonical", "helper", "~Canonical"], "virtual": ["~Canonical"],
          "vslots": {"0": "~Canonical()"}, "vfptr": True}
TABLE = "??_7Canonical@@6B@"


def git(root, *args):
    return subprocess.run(["git", *args], cwd=root, capture_output=True, check=True)


def put(root, path, body, tracked=True):
    path = root / path
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(body.encode("ascii") if isinstance(body, str) else body)
    if tracked:
        git(root, "add", "--", path.relative_to(root).as_posix())
    return path


class Case:
    def __init__(self, root):
        self.root, self.units, self.objects = root, {}, {}

    def source(self, source="Code/A.cpp", *, bound=True, emitting=True, record=True, deps=(), body=None,
               tracked=True):
        text = body if body is not None else ('#include "Canonical.h"\n' if bound else "void unrelated() {}\n")
        put(self.root, source, text, tracked=tracked)
        meta = I._receipt_path(self.root, source)
        output = meta.with_name(meta.name[:-len(".deps.json")] + ".obj")
        raw = b"object of " + source.encode()
        put(self.root, output.relative_to(self.root).as_posix(), raw, tracked=False)
        opened = (HEADER,) + tuple(deps) if bound else tuple(deps)
        md5 = lambda path: hashlib.md5(Path(path).read_bytes()).hexdigest()
        payload = {"path": source, "source": md5(self.root / source), "object": md5(output),
                   "deps": {path: md5(self.root / path) for path in opened}}
        meta.write_text(json.dumps(payload))
        facts = (frozenset({"real-owner"}), frozenset({"real-owner", TABLE} if emitting else {"real-owner"}))
        self.objects[raw] = (facts, {NAME: deepcopy(LAYOUT)} if record else {})
        pp = f'#line 1 "{source}"\n'
        if bound:
            pp += f'#line 1 "{HEADER}"\n' + DECL + f'#line 2 "{source}"\n'
        else:
            pp += text
        self.units[source] = {"state": I.CompilerInputs("command", "inventory", (), True),
                              "command": ["cl", "-c", "-Fo" + str(output), source], "env": {},
                              "stdout": pp.encode(), "stderr": b"".join(
                                  b"Note: including file: " + str(self.root / path).encode() + b"\n" for path in opened),
                              "returncode": 0, "object": output, "receipt": meta}
        return source

    def capture(self, *sources, contract=None):
        return P.capture(NAME, HEADER, deepcopy(CONTRACT) if contract is None else contract,
                         sources or tuple(self.units), root=self.root)


@pytest.fixture
def case(tmp_path, monkeypatch):
    git(tmp_path, "init", "-q")
    put(tmp_path, HEADER, DECL)
    case = Case(tmp_path)
    monkeypatch.setattr(I, "_compiler_inputs", lambda root, source, output, cache=None: case.units[source]["state"])
    def normal_command(root, source, output):
        command = list(case.units[source]["command"])
        positions = [i for i, arg in enumerate(command) if arg.startswith(("-Fo", "/Fo"))]
        if len(positions) == 1:
            command[positions[0]] = command[positions[0]][:3] + str(output)
        return command, case.units[source]["env"]
    monkeypatch.setattr(P, "_normal_command", normal_command)
    monkeypatch.setattr(P, "_command_fingerprint", lambda *a: "command")
    def preprocess(command, env):
        source = next(arg for arg in command if arg.endswith(".cpp"))
        unit = case.units[source]
        return subprocess.CompletedProcess(command, unit["returncode"], unit["stdout"], unit["stderr"])
    monkeypatch.setattr(P, "_preprocess", preprocess)
    def opened(source, output):
        return {source.resolve()} | {Path(line[len(b"Note: including file: "):].decode()).resolve()
                                   for line in output.splitlines() if line.startswith(b"Note: including file:")}
    monkeypatch.setattr(P, "_opened_paths", opened)
    monkeypatch.setattr(P, "_object_evidence", lambda raw: deepcopy(case.objects[raw]))
    def unavailable(*args):
        raise P.InputRefused("diagnostic unavailable")
    monkeypatch.setattr(P, "_diagnostic_layouts", unavailable)
    return case


@pytest.mark.parametrize("wrapper", ["plain", "guard", "once", "once_guard"])
def test_literal_header_provenance_and_real_object_facts(case, wrapper):
    header = DECL
    if "guard" in wrapper:
        header = "#ifndef CANONICAL_H\n#define CANONICAL_H\n" + header + "#endif\n"
    if "once" in wrapper:
        header = "#pragma once\n" + header
    put(case.root, HEADER, header)
    source = case.source()
    got = case.capture(source)
    witness = got.witnesses[source]
    assert got.name == NAME and got.header == HEADER
    assert got.digest == hashlib.sha256((case.root / HEADER).read_bytes()).hexdigest()
    assert "Canonical(void *held)" in got.text and "void helper()" in got.text
    assert witness.source == source and witness.object_path == str(case.units[source]["object"])
    assert witness.object_digest == hashlib.sha256(case.units[source]["object"].read_bytes()).hexdigest()
    assert witness.facts == (frozenset({"real-owner"}), frozenset({"real-owner", TABLE}))
    assert witness.emitting is True and witness.header_bound is True
    assert witness.layout["fields"] == ((4, "value", "void*", 4),)
    assert got.profiles == {source: "command"}
    assert got.forced_inputs == {source: ()}
    assert got.search_inventories == {source: "inventory"}
    assert got.validate() is True


def test_nonconsumer_remains_real_source_witness_without_header_vote(case):
    a = case.source()
    b = case.source("Code/B.cpp", bound=False, emitting=False, record=False)
    got = case.capture(a, b)
    assert set(got.witnesses) == {a, b}
    assert got.witnesses[b].header_bound is False
    assert got.witnesses[b].emitting is False and got.witnesses[b].layout is None
    assert "real-owner" in got.witnesses[b].facts[0]


def test_only_actual_objects_receipts_and_diagnostics_are_rebuildable(case):
    source = case.source()
    got = case.capture(source)
    unit = case.units[source]
    assert got.rebuildable == frozenset({unit["object"].relative_to(case.root).as_posix(),
                                         unit["receipt"].relative_to(case.root).as_posix()})
    assert HEADER not in got.rebuildable and source not in got.rebuildable


def test_call_only_header_consumer_may_have_known_false_emission_and_no_record(case):
    source = case.source(emitting=False, record=False)
    emitter = case.source("Code/Emitter.cpp")
    got = case.capture(source, emitter)
    assert got.witnesses[source].header_bound is True
    assert got.witnesses[source].emitting is False
    assert got.witnesses[source].layout is None


def test_call_only_cohort_cannot_admit_a_declaration_without_native_layout(case):
    source = case.source(emitting=False, record=False)
    with pytest.raises(P.InputRefused, match="native layout witness"):
        case.capture(source)


@pytest.mark.parametrize("diagnostic", ["absent", "mismatch", "matching"])
def test_nonpolymorphic_consumer_requires_complete_native_layout_even_without_vtable(case, monkeypatch, diagnostic):
    declaration = "class Canonical { public: int value; };\n"
    put(case.root, HEADER, declaration)
    source = case.source(emitting=False, record=False)
    case.units[source]["stdout"] = f'#line 1 "{HEADER}"\n{declaration}'.encode()
    contract = {"class": NAME, "key": "class", "size": 4, "bases": [], "vslots": {},
                "fields": [{"offset": 0, "name": "value", "kind": "i4", "size": 4, "type": "int"}]}
    # Use the owning kind decoder, rather than inventing a fixture spelling.
    import class_contract
    contract["fields"][0]["kind"] = class_contract.kind("int")
    layout = {"fwd": False, "key": "class", "size": 4, "bases": [],
              "fields": [[0, "value", "int", 4]], "vslots": {}, "vfptr": False}
    if diagnostic == "mismatch":
        contract["size"] = 8
        contract["fields"].append({"offset": 4, "name": "invented", "kind": class_contract.kind("int"), "size": 4,
                                   "type": "int"})
    monkeypatch.setattr(P, "_diagnostic_layouts", lambda root, unit:
                        ({} if diagnostic == "absent" else {NAME: layout}, ()))
    if diagnostic == "matching":
        got = case.capture(source, contract=contract)
        assert got.witnesses[source].layout["size"] == 4
    else:
        with pytest.raises(P.InputRefused, match="layout|storage|record"):
            case.capture(source, contract=contract)


@pytest.mark.parametrize("recorded_type", ["void*", None, "int*"])
def test_pointer_width_does_not_authorize_changing_canonical_pointee_type(case, recorded_type):
    declaration = DECL.replace("void *value", "int *value")
    put(case.root, HEADER, declaration)
    source = case.source()
    case.units[source]["stdout"] = f'#line 1 "{HEADER}"\n{declaration}'.encode()
    raw = case.units[source]["object"].read_bytes()
    case.objects[raw][1][NAME]["fields"][0][2] = "int*"
    contract = deepcopy(CONTRACT)
    contract["fields"][1]["type"] = recorded_type
    if recorded_type == "int*":
        assert case.capture(source, contract=contract).witnesses[source].layout["fields"][0][2] == "int*"
    else:
        with pytest.raises(P.InputRefused, match="field type"):
            case.capture(source, contract=contract)


def test_compiler_binary_receipt_input_is_hashed_without_parsing_as_cpp(case):
    binary = put(case.root, "vendor/profile/compiler.exe", b"MZ\0binary\0profile")
    source = case.source(deps=(binary.relative_to(case.root).as_posix(),))
    # A profile executable is a compile input, not a /showIncludes text input.
    case.units[source]["stderr"] = b"Note: including file: " + str(case.root / HEADER).encode() + b"\n"
    got = case.capture()
    assert "vendor/profile/compiler.exe" in got.files
    with binary.open("ab") as stream:
        stream.write(b"changed")
    with pytest.raises(P.InputRefused):
        got.validate()


def test_missing_emitter_record_uses_fresh_layout_only_never_diagnostic_owner_facts(case, monkeypatch):
    source = case.source(record=False)
    diagnostic = put(case.root, "build/diagnostic.obj", b"fresh layout diagnostic", tracked=False)
    calls = []
    def measure(root, unit):
        calls.append((root, unit))
        return {NAME: deepcopy(LAYOUT)}, (diagnostic,)
    monkeypatch.setattr(P, "_diagnostic_layouts", measure)
    got = case.capture(source)
    assert calls == [(case.root, source)]
    assert got.witnesses[source].layout["size"] == 8
    assert got.witnesses[source].object_path == str(case.units[source]["object"])
    assert got.witnesses[source].facts[0] == frozenset({"real-owner"})
    assert "build/diagnostic.obj" in got.files


def test_unknown_emitter_layout_stays_closed(case):
    case.source(record=False)
    with pytest.raises(P.InputRefused, match="diagnostic unavailable"):
        case.capture()


@pytest.mark.parametrize("change", ["offset", "size", "field_name", "slots", "key", "bases", "unparsed"])
def test_header_bound_native_class_must_equal_complete_contract(case, change):
    source = case.source()
    raw = case.units[source]["object"].read_bytes()
    record = case.objects[raw][1][NAME]
    if change == "offset":
        record["fields"][0][0] = 0
    elif change == "size":
        record["size"] = 12
    elif change == "field_name":
        record["fields"][0][1] = "other"
    elif change == "slots":
        record["vslots"]["1"] = "helper()"
    elif change == "key":
        record["key"] = "struct"
    elif change == "bases":
        record["bases"] = [["Base", 0]]
    else:
        record["unparsed"] = "ambiguous record"
    with pytest.raises(P.InputRefused):
        case.capture()


@pytest.mark.parametrize("change", ["path", "source", "object", "stale", "profile", "missing", "deps"])
def test_current_source_object_receipt_profile_binding_is_required(case, change):
    source = case.source()
    unit = case.units[source]
    if change == "missing":
        unit["receipt"].unlink()
    elif change in ("stale", "profile"):
        unit["state"] = replace(unit["state"], reusable=False, fingerprint="changed profile")
    else:
        meta = json.loads(unit["receipt"].read_text())
        if change == "deps":
            meta["deps"][HEADER] = "0" * 32
        else:
            meta[change] = "another-source" if change == "path" else "0" * 32
        unit["receipt"].write_text(json.dumps(meta))
    with pytest.raises(P.InputRefused):
        case.capture()


@pytest.mark.parametrize("forgery", ["source", "included", "foreign_marker", "unopened_marker", "namespace", "duplicate", "backward", "missing_markers"])
def test_actual_complete_span_provenance_cannot_be_forged(case, forgery):
    deps = ()
    body = None
    if forgery == "source":
        body = '#line 1 "Code/Canonical.h"\n#include "Canonical.h"\n'
    if forgery == "included":
        put(case.root, "Code/Forgery.h", '#line 1 "Code/Canonical.h"\n')
        deps = ("Code/Forgery.h",)
    source = case.source(deps=deps, body=body)
    unit = case.units[source]
    if forgery == "foreign_marker":
        unit["stdout"] = unit["stdout"].replace(b" void helper();", b'#line 5 "Code/Foreign.h"\n void helper();')
    elif forgery == "unopened_marker":
        unit["stderr"] = b""
    elif forgery == "namespace":
        unit["stdout"] = unit["stdout"].replace(b"class Canonical", b"namespace Other { class Canonical") + b"}\n"
    elif forgery == "duplicate":
        unit["stdout"] += f'#line 1 "{HEADER}"\n'.encode() + DECL.encode()
    elif forgery == "backward":
        unit["stdout"] = unit["stdout"].replace(b" void helper();", f'#line 1 "{HEADER}"\n void helper();'.encode())
    elif forgery == "missing_markers":
        unit["stdout"] = DECL.encode()
    with pytest.raises(P.InputRefused):
        case.capture()


def test_opened_header_with_suppressed_guard_definition_is_refused(case):
    put(case.root, HEADER, "#ifndef CANONICAL_H\n#define CANONICAL_H\n" + DECL + "#endif\n")
    source = case.source(body='#define CANONICAL_H\n#include "Canonical.h"\n')
    case.units[source]["stdout"] = b'#line 1 "Code/A.cpp"\nvoid f() {}\n'
    with pytest.raises(P.InputRefused, match="guard suppression"):
        case.capture()


@pytest.mark.parametrize("mutation", [b"void *value", b"void helper()", b"virtual ~Canonical()"])
def test_same_layout_does_not_replace_raw_declaration_token_proof(case, mutation):
    source = case.source()
    case.units[source]["stdout"] = case.units[source]["stdout"].replace(mutation, mutation + b" const")
    with pytest.raises(P.InputRefused, match="raw class tokens differ"):
        case.capture()


@pytest.mark.parametrize("macro", ["#define helper renamed\n", "#define public private\n", "#define Canonical Other\n",
                                  "#de\\\nfine helper renamed\n", "%:define helper renamed\n"])
def test_source_and_include_macro_token_collisions_are_refused(case, macro):
    put(case.root, "Code/Macros.h", macro)
    case.source(deps=("Code/Macros.h",))
    with pytest.raises(P.InputRefused, match="macro"):
        case.capture()


@pytest.mark.parametrize("flags", [["/Dhelper=other"], ["-D", "public=private"], ["-FIPrelude.h"],
                                  ["-FI", "Prelude.h"], ["@arguments.rsp"], ["-YuPrecompiled.h"]])
def test_command_macro_forced_and_opaque_inputs_stay_closed(case, flags):
    source = case.source()
    case.units[source]["command"][1:1] = flags
    with pytest.raises(P.InputRefused):
        case.capture()


@pytest.mark.parametrize("header", [
    "#if SELECTED\n" + DECL + "#endif\n",
    "#ifndef GUARD\n#define GUARD\n#endif\n" + DECL,
    DECL.replace("public:", "public:\n#if SELECTED\n int extra;\n#endif"),
    "namespace Other {\n" + DECL + "}\n",
    DECL.replace("void *value;", "typedef int Alias; void *value;"),
    DECL.replace("void *value;", "struct Nested {}; void *value;"),
    DECL.replace("void *value;", "void *value[1];"),
    DECL.replace("Canonical", "Cano\\\nnical"),
    DECL.replace("Canonical", "\\u0043anonical"),
    "#pragma once\n#pragma once\n" + DECL,
])
def test_unsupported_header_syntax_is_never_admitted(case, header):
    put(case.root, HEADER, header)
    case.source()
    with pytest.raises(P.InputRefused):
        case.capture()


@pytest.mark.parametrize("failure", ["returncode", "empty", "unreceipted"])
def test_incomplete_preprocessor_input_is_refused(case, failure):
    source = case.source()
    unit = case.units[source]
    if failure == "returncode":
        unit["returncode"] = 1
    elif failure == "empty":
        unit["stdout"] = b""
    else:
        path = put(case.root, "Code/Unexpected.h", "int extra;\n")
        unit["stderr"] += b"Note: including file: " + str(path).encode() + b"\n"
    with pytest.raises(P.InputRefused):
        case.capture()


@pytest.mark.parametrize("drift", ["source", "header", "object", "receipt", "profile", "search", "new_tracked"])
def test_native_capture_validation_refuses_input_drift(case, drift):
    source = case.source()
    got = case.capture()
    unit = case.units[source]
    if drift == "profile":
        unit["state"] = replace(unit["state"], fingerprint="other profile")
    elif drift == "search":
        unit["state"] = replace(unit["state"], inventory="new earlier include")
    elif drift == "new_tracked":
        put(case.root, "Code/Shadow.h", "int shadow;\n")
    else:
        path = {"source": case.root / source, "header": case.root / HEADER,
                "object": unit["object"], "receipt": unit["receipt"]}[drift]
        with path.open("ab") as stream:
            stream.write(b"\nchanged\n")
    with pytest.raises(P.InputRefused):
        got.validate()


def test_no_header_owner_or_optional_mutation_admission_surface(case):
    source = case.source()
    got = case.capture()
    assert HEADER not in got.witnesses
    with pytest.raises(TypeError):
        got.witnesses[HEADER] = got.witnesses[source]
    with pytest.raises(TypeError):
        got.witnesses[source].layout["size"] = 1
    with pytest.raises(P.InputRefused, match=r"real tracked C/C\+\+ source"):
        P.capture(NAME, HEADER, CONTRACT, [HEADER], root=case.root)


def test_real_generator_output_admits_only_its_complete_assertion_suffix(case, monkeypatch):
    import header_adopt_lane as lane
    contract = deepcopy(CONTRACT)
    contract.update(size_by="bytes", key_by="bytes")
    contract["fields"][0]["type"] = "void*"
    contract["fields"][1]["type"] = "void*"
    monkeypatch.setattr(lane, "owner_strength", lambda *a, **k: None)
    monkeypatch.setattr(lane, "mangling_contradictions", lambda *a, **k: [])
    generated = lane.generate(contract, "data", {}, HEADER, (["virtual ~Canonical() {}"], []), [
        {"role": "ctor", "access": "public", "text": "Canonical(void *held);", "sig": ("ctor",)},
        {"role": "method", "access": "public", "text": "void helper();", "sig": ("helper",)},
    ])
    put(case.root, HEADER, generated)
    source = case.source()
    parsed, expected, words, guard = P._elide_header(generated.encode(), NAME, contract)
    assert "typedef" not in parsed and "_vprobe" not in parsed
    assert any(word.endswith("_vprobe") for word in words)
    # Use the real emitted target declaration, including actual method ordering.
    case.units[source]["stdout"] = (f'#line 1 "{HEADER}"\n' + parsed + "\n").encode()
    got = case.capture(source, contract=contract)
    assert got.witnesses[source].header_bound is True
    prefix = lane.assertion_prefix(NAME, parsed)
    case.units[source]["command"].insert(1, "-D" + prefix + "_sizeof=other")
    with pytest.raises(P.InputRefused, match="command macro"):
        case.capture(source, contract=contract)


@pytest.mark.parametrize("change", ["size", "probe", "field", "extra"])
def test_assertion_suffix_cannot_admit_modified_or_extra_typedefs(case, change):
    import header_adopt_lane as lane
    suffix = "\n".join(lane.size_assertions(CONTRACT, DECL))
    if change == "size":
        suffix = suffix.replace("== 8", "== 80")
    elif change == "probe":
        suffix = suffix.replace("virtual void", "void")
    elif change == "field":
        suffix = suffix.replace("->value", "->other")
    else:
        suffix += "\ntypedef int Alias;"
    put(case.root, HEADER, DECL + suffix + "\n")
    case.source()
    with pytest.raises(P.InputRefused, match="exact owning generator assertions"):
        case.capture()


def test_whole_coff_reader_refuses_truncated_bytes():
    with pytest.raises(P.InputRefused, match="whole COFF"):
        P._object_evidence(b"truncated object")


def test_preprocessing_command_cannot_diverge_from_current_object_profile(case, monkeypatch):
    case.source()
    monkeypatch.setattr(P, "_command_fingerprint", lambda *a: "other profile")
    with pytest.raises(P.InputRefused, match="command/profile differs"):
        case.capture()


@pytest.mark.parametrize("change", ["duplicate", "extent", "negative", "aggregate", "bool_size"])
def test_malformed_contract_cannot_be_declared_layout_equal(case, change):
    case.source()
    contract = deepcopy(CONTRACT)
    if change == "duplicate":
        contract["fields"].append(deepcopy(contract["fields"][-1]))
    elif change == "extent":
        contract["fields"][-1]["size"] = 8
    elif change == "negative":
        contract["fields"][-1]["offset"] = -4
    elif change == "aggregate":
        contract["fields"][-1]["kind"] = "S:Hidden"
    else:
        contract["size"] = True
    with pytest.raises(P.InputRefused):
        case.capture(contract=contract)


@pytest.mark.parametrize("kind", ["literal", "manufactured"])
def test_volatile_native_inputs_and_preprocessed_clock_output_refuse(case, kind):
    source = case.source(body='const char *clock = __TIME__;\n#include "Canonical.h"\n' if kind == "literal" else None)
    if kind == "manufactured":
        case.units[source]["stdout"] += b'const char *clock = "12:34:56";\n'
    with pytest.raises(P.InputRefused, match="volatile"):
        case.capture()


@pytest.mark.skipif(os.environ.get("BFME_NATIVE_HEADER_PROOF") != "1", reason="explicit isolated VC71 component probe")
def test_native_vc71_generated_declaration_components():
    """Real native components; full receipt/capture binding is tested separately.

    Original owner/emission facts come from the normal-command object. The
    separate fresh -Z7 diagnostic supplies layout only. All files are scratch.
    """
    import build
    import class_layouts
    import header_adopt_lane as lane
    root = P.ROOT
    scratch = root / "build" / "native-canonical-generation-proof"
    scratch.mkdir(parents=True, exist_ok=True)
    name = "NativeCanonicalGenerationProof"
    contract = deepcopy(CONTRACT)
    contract.update({"class": name, "size_by": "bytes", "key_by": "bytes", "vslots": {"0": "__vecDelDtor(uint)"}})
    for field in contract["fields"]:
        field["type"] = "void*"
    header = scratch / "canonical.h"
    rel_header = header.relative_to(root).as_posix()
    special = [{"role": "ctor", "access": "public", "text": name + "(void *held);", "sig": ("ctor",)},
               {"role": "method", "access": "public", "text": "void helper();", "sig": ("helper",)}]
    generated = lane.generate(contract, "data", {}, rel_header, (["virtual ~" + name + "() {}"], []), special)
    header.write_text(generated, encoding="ascii", newline="\n")
    source = scratch / "native_canonical.cpp"
    source.write_text('#include "canonical.h"\n' + name + "::" + name + "(void *held) : value(held) {}\n"
                      + "void " + name + "::helper() {}\n" + name + " *make(void *held) { return new " + name + "(held); }\n",
                      encoding="ascii", newline="\n")
    output = scratch / "original.obj"
    command, env = build.compiler_command(source, output)
    with (scratch / "compile.log").open("w+", encoding="latin-1") as log:
        done = build._run_compile(command, env, log, timeout=60)
        log.seek(0)
        diagnostic = log.read()
    assert done.returncode == 0, diagnostic
    original = output.read_bytes()
    facts, _original_layouts = P._object_evidence(original)
    assert "??0" + name + "@@QAE@PAX@Z" in facts[0]
    assert "?helper@" + name + "@@QAEXXZ" in facts[0]
    assert "??_7" + name + "@@6B@" in facts[1]
    layouts, paths = P._diagnostic_layouts(root, source.relative_to(root).as_posix())
    assert all(path.is_file() for path in paths)
    P._layout(name, contract, layouts[name])
    pp = [arg for arg in command if not arg.startswith(("-Fo", "/Fo"))]
    pp[pp.index("-c")] = "-E"
    expanded = P._preprocess(pp + ["-showIncludes"], env)
    assert expanded.returncode == 0, expanded.stderr.decode("latin-1")
    opened = P._opened_paths(source, expanded.stderr + b"\n" + expanded.stdout)
    assert header.resolve() in opened
    parsed, expected, words, _guard = P._elide_header(header.read_bytes(), name, contract)
    assert "typedef" not in parsed and any(word.endswith("_vprobe") for word in words)
    assert P._bound_span(P._expanded_tokens(expanded.stdout, root), name, rel_header, expected, True) is True
    assert output.read_bytes() == original
    (scratch / "preprocessed.txt").write_bytes(expanded.stdout)
    (scratch / "evidence.json").write_text(json.dumps({
        "scope": "native components only; no synthetic strict receipt or full capture admission",
        "source": str(source), "header": str(header), "normal_object": str(output),
        "normal_object_sha256": hashlib.sha256(original).hexdigest(),
        "exclusive": sorted(facts[0]), "defined": sorted(facts[1]), "layout": layouts[name],
        "diagnostic_paths": [str(path) for path in paths], "header_bound": True}, indent=2), encoding="utf-8")


# An owning generator can carry allocation methods and literal gap padding;
# neither grants array-data, operator-expression or changed-storage admission.
def allocation_gap_case(gap=True, member="static void *operator new(unsigned int size);"):
    import header_adopt_lane as lane
    contract = {"class": "AllocationRoundtrip", "key": "class", "key_by": "bytes",
                "size": 12 if gap else 4, "size_by": "bytes", "bases": [], "vslots": {},
                "fields": [{"offset": 0, "name": "value", "kind": "i4", "size": 4, "type": "uint"}]}
    carried, problems = lane.special_declarations("AllocationRoundtrip", ["unit.cpp"],
        read=lambda _: "class AllocationRoundtrip { public: unsigned int value; " + member + " };", index={})
    assert not problems
    header = lane.generate(contract, "data+methods", {}, "Code/AllocationRoundtrip.h", special=carried, owners={})
    return contract, header


@pytest.mark.parametrize("gap", [False, True])
@pytest.mark.parametrize("member", ["static void *operator new(unsigned int size);",
                                    "static void *operator new[](unsigned size);",
                                    "static void operator delete(void *block);",
                                    "static void operator delete[](void *block);"])
def test_owning_generator_allocation_method_roundtrip(gap, member):
    contract, header = allocation_gap_case(gap, member)
    parsed, tokens, words, guard = P._elide_header(header.encode(), "AllocationRoundtrip", contract)
    assert "operator" in words and member in parsed
    fields = [[0, "value", "uint", 4]] + ([[4, "m_pad4", "char[8]", 8]] if gap else [])
    native = {"fwd": False, "key": "class", "size": contract["size"], "bases": [],
              "fields": fields, "vfptr": False, "vslots": {}}
    assert P._layout("AllocationRoundtrip", contract, native) is native


@pytest.mark.parametrize("member", [
    "static int operator new(unsigned int size);", "static void *operator new(SizeAlias size);",
    "static void *operator new(unsigned int size=4);", "static void *operator new(unsigned int size, void *where);",
    "static void *operator new(unsigned int size) { return 0; }", "operator void *() const;",
    "bool operator<(const AllocationRoundtrip &) const;", "static void operator delete(void *p, unsigned int n);",
    "friend void operator delete(void *p);", "static void (*operator new)(unsigned int);",
])
def test_allocation_role_does_not_admit_unrelated_or_unsupported_declarations(member):
    contract, header = allocation_gap_case(False)
    header = header.replace("static void *operator new(unsigned int size);", member)
    with pytest.raises(P.InputRefused):
        P._elide_header(header.encode(), "AllocationRoundtrip", contract)


@pytest.mark.parametrize("replacement", ["char m_pad4[7];", "char m_pad4[9];", "unsigned char m_pad4[8];",
                                         "char other[8];", "char m_pad4[sizeof(int)*2];", "char m_pad4[0x8];",
                                         "char m_pad4[8] = {};", "static char m_pad4[8];", "char m_pad4[8][1];"])
def test_only_exact_owning_generator_gap_declaration_is_admitted(replacement):
    contract, header = allocation_gap_case()
    with pytest.raises(P.InputRefused):
        P._elide_header(header.replace("char m_pad4[8];", replacement).encode(), "AllocationRoundtrip", contract)


@pytest.mark.parametrize("mutation", ["offset", "width", "element", "missing", "extra", "overlap"])
def test_native_gap_extent_and_type_are_not_guessed(mutation):
    contract, header = allocation_gap_case()
    native = {"fwd": False, "key": "class", "size": 12, "bases": [], "vfptr": False, "vslots": {},
              "fields": [[0, "value", "uint", 4], [4, "m_pad4", "char[8]", 8]]}
    if mutation == "offset": native["fields"][1][0] = 3
    elif mutation == "width": native["fields"][1][3] = 7
    elif mutation == "element": native["fields"][1][2] = "int[2]"
    elif mutation == "missing": native["fields"].pop()
    elif mutation == "extra": native["fields"].append([8, "hidden", "int", 4])
    else: native["fields"].append([3, "overlap", "char", 1])
    with pytest.raises(P.InputRefused): P._layout("AllocationRoundtrip", contract, native)


def test_gap_does_not_accept_changed_contract_or_missing_owning_assertions():
    contract, header = allocation_gap_case()
    updated = deepcopy(contract)
    updated["fields"].append({"offset":4,"name":"invented","kind":"i4","size":4,"type":"uint"})
    with pytest.raises(P.InputRefused): P._elide_header(header.encode(), "AllocationRoundtrip", updated)
    plain = header[:header.index("typedef char canonical_")]
    plain += "\n#endif\n"
    with pytest.raises(P.InputRefused): P._elide_header(plain.encode(), "AllocationRoundtrip", contract)
    bad = deepcopy(contract);bad["fields"][0]["offset"] = 1
    with pytest.raises(P.InputRefused): P._elide_header(header.encode(), "AllocationRoundtrip", bad)


@pytest.mark.skipif(os.environ.get("BFME_NATIVE_HEADER_PROOF") != "1", reason="explicit isolated VC71 allocation/gap roundtrip")
def test_native_allocation_gap_roundtrip_preserves_storage_and_alignment(monkeypatch):
    import build, class_layouts
    import header_adopt_lane as lane
    root = P.ROOT
    scratch = root / "build" / "codex-thing-agent-20261120" / "roundtrip-native"
    scratch.mkdir(parents=True, exist_ok=True)
    monkeypatch.setattr(class_layouts, "CACHE", scratch / "cv")
    contract, header = allocation_gap_case()
    name = contract["class"]
    h = scratch / "allocation.h";h.write_text(header, encoding="ascii", newline="\n")
    source = scratch / "allocation.cpp"
    source.write_text('#include "allocation.h"\nvoid *' + name + '::operator new(unsigned int) { return 0; }\n'
        + 'struct NativeGapAlignment { char lead; ' + name + ' value; };\n'
        + 'NativeGapAlignment alignmentWitness;\n'
        + 'unsigned alignment() { return (unsigned)&((NativeGapAlignment *)0)->value; }\n'
        + 'unsigned width() { return sizeof(' + name + '); }\n', encoding="ascii", newline="\n")
    output = scratch / "ordinary.obj"
    command, env = build.compiler_command(source, output)
    with (scratch / "compile.log").open("w+", encoding="latin-1") as log:
        done = build._run_compile(command, env, log, timeout=60);log.seek(0);diagnostic=log.read()
    assert done.returncode == 0, diagnostic
    ordinary = output.read_bytes()
    facts, _ = P._object_evidence(ordinary)
    assert "??2" + name + "@@SAPAXI@Z" in facts[0]
    layouts, paths = P._diagnostic_layouts(root, source.relative_to(root).as_posix())
    P._layout(name, contract, layouts[name])
    assert layouts["NativeGapAlignment"]["fields"][1][0] == 4
    pp = [a for a in command if not a.startswith(("-Fo", "/Fo"))];pp[pp.index("-c")]="-E"
    expanded=P._preprocess(pp+["-showIncludes"],env)
    assert expanded.returncode == 0
    parsed, expected, words, guard=P._elide_header(h.read_bytes(),name,contract)
    assert P._bound_span(P._expanded_tokens(expanded.stdout,root),name,h.relative_to(root).as_posix(),expected,True)
    assert output.read_bytes() == ordinary

    # Valid native C++ with unchanged allocation/record size is still not
    # admitted when a method role, padding type or declared storage differs.
    ordinary_source = source.read_text(encoding="ascii")
    negative_source = ordinary_source.replace("void *" + name + "::operator new(unsigned int) { return 0; }\n", "")
    for label, changed in [
        ("body", header.replace("static void *operator new(unsigned int size);", "static void *operator new(unsigned int size) { return 0; }")),
        ("alias", header.replace("static void *operator new(unsigned int size);", "typedef unsigned int SizeAlias; static void *operator new(SizeAlias size);")),
        ("padding-type", header.replace("char m_pad4[8];", "unsigned char m_pad4[8];")),
        ("hidden-data", header.replace("char m_pad4[8];", "char m_pad4[4]; int hidden;")),
    ]:
        h.write_text(changed, encoding="ascii", newline="\n")
        candidate = scratch / ("negative-" + label + ".cpp")
        candidate.write_text(negative_source, encoding="ascii", newline="\n")
        bad_output = scratch / ("negative-" + label + ".obj")
        bad_command, bad_env = build.compiler_command(candidate, bad_output)
        with (scratch / ("negative-" + label + ".log")).open("w+", encoding="latin-1") as log:
            result = build._run_compile(bad_command, bad_env, log, timeout=60);log.seek(0);diagnostic=log.read()
        assert result.returncode == 0, (label, diagnostic)
        with pytest.raises(P.InputRefused): P._elide_header(h.read_bytes(), name, contract)
        if label in {"padding-type", "hidden-data"}:
            bad_layouts, _ = P._diagnostic_layouts(root, candidate.relative_to(root).as_posix())
            with pytest.raises(P.InputRefused): P._layout(name, contract, bad_layouts[name])
    h.write_text(header, encoding="ascii", newline="\n")
    assert output.read_bytes() == ordinary


@pytest.fixture
def raw_owner_world(case, monkeypatch):
    """Existing normal-command/object/PP fixture boundaries; no native processes."""
    from types import SimpleNamespace
    import build
    import header_adopt_lane as lane
    import tu_views
    name, source, header = "C", "Code/Owner.cpp", "Code/C.h"
    text = ('#include "foreign.h"\nclass C { public: int old; C(); int f(); };\n'
            'C::C() : old(0) {}\nint C::f() { return old; }\n')
    put(case.root, header, '#pragma once\nclass C { public: int canonical; C(); int f(); };\n')
    put(case.root, "Code/foreign.h", "/* ordinary actual input */\n")
    compiler = put(case.root, "cl.exe", "compiler fixture, never executed\n", tracked=False)
    original = P._preprocess
    state = SimpleNamespace(case=case, root=case.root, name=name, source=source, header=header,
                            text=text, calls=[], callback=None, mapping={"old": "canonical"})
    monkeypatch.setattr(build, "search_inventory", lambda *a, **kw: "inventory")
    monkeypatch.setattr(build, "compiler_command", lambda path, output:
        (case.units[path.relative_to(case.root).as_posix()]["command"],
         case.units[path.relative_to(case.root).as_posix()]["env"]))
    monkeypatch.setattr(lane, "ROOT", case.root)
    monkeypatch.setattr(lane, "FIELD_RENAMES", {})
    monkeypatch.setattr(tu_views, "ROOT", case.root)
    def unit(path, body, pp=None, opened=("Code/foreign.h",), *, tracked=True):
        case.source(path, bound=False, body=body, tracked=tracked)
        item = case.units[path]
        item["command"] = [str(compiler), "-c", "-Fo" + str(item["object"]), path]
        meta = json.loads(item["receipt"].read_text())
        meta["deps"] = {p: hashlib.md5((case.root / p).read_bytes()).hexdigest() for p in opened}
        item["receipt"].write_text(json.dumps(meta))
        item["stdout"] = pp if pp is not None else ('#line 2 "' + path + '"\n' + '\n'.join(body.splitlines()[1:]) + '\n').encode()
        item["stderr"] = b''.join(b'Note: including file: ' + str(case.root / p).encode() + b'\n' for p in opened)
        return item
    def pp(command, env):
        state.calls.append(tuple(command))
        if state.callback:
            state.callback(len(state.calls))
        return original(command, env)
    monkeypatch.setattr(P, "_preprocess", pp)
    state.unit = unit
    state.unit(source, text)
    def current():
        # A normal isolated fixture HEAD/index is a real input, just like Main.
        # Build fixture metadata is untracked and prospective .cpp is NEVER added.
        if git(case.root, "rev-list", "--all").stdout == b"":
            git(case.root, "-c", "user.name=Fixture", "-c", "user.email=fixture@example.invalid",
                "commit", "-qm", "native owner fixture inputs")
        return P.capture_owner_current(name, source, header, dict(state.mapping), root=case.root)
    def prospective(current, opened=("Code/foreign.h", header)):
        path = "Code/Prospective.cpp"
        body = current.plan_text()
        # The actual header definition and source have separate real markers.
        pp = (f'#line 2 "{header}"\n' + (case.root/header).read_text().splitlines()[1] + '\n'
              + f'#line 3 "{path}"\n' + '\n'.join(body.splitlines()[2:]) + '\n').encode()
        state.unit(path, body, pp=pp, opened=opened, tracked=False)
        return path
    state.current, state.prospective = current, prospective
    return state


def test_raw_owner_current_is_immutable_pure_planning_not_a_pair(raw_owner_world):
    w = raw_owner_world
    current = w.current()
    assert len(w.calls) == 2
    assert current._state.coverage[0] == 3
    assert current.plan_text().endswith('C::C() : canonical(0) {}\nint C::f() { return canonical; }\n')
    assert len(w.calls) == 2
    from dataclasses import FrozenInstanceError
    with pytest.raises(FrozenInstanceError): current.name = "Other"
    with pytest.raises(P.InputRefused): replace(current, name="Other")
    import header_adopt_lane as lane
    assert "paired" in lane.owner_witness_problem(current, w.source, w.text, {w.name:w.mapping}, w.root, (w.header,))
    assert len(w.calls) == 2


def test_raw_owner_real_pair_and_readers_revalidate_without_implicit_pp(raw_owner_world):
    w = raw_owner_world
    current = w.current(); path = w.prospective(current)
    pair = P.capture_owner_pair(current, path)
    assert len(w.calls) == 4
    assert pair.validate_for(w.source, w.text, {w.name:w.mapping}, w.root, (w.header,))
    import header_adopt_lane as lane
    import tu_views
    layout = {"key":"class", "fwd":False, "size":4, "bases":[], "fields":[[0,"old","int",4]],
              "methods":["C","f"], "statics":[], "virtual":[], "vslots":{}, "vfptr":False}
    view = tu_views.View(w.source,w.text,w.name,layout,{w.name:layout},source_root=w.root,
                        include_seeds=(w.header,),owner_witness=pair)
    assert tu_views.rename_problem(view,w.mapping) is None
    assert lane.initializer_context_problem(w.source,w.text,{w.name:w.mapping},w.root,(w.header,),pair) is None
    assert len(w.calls) == 4


@pytest.mark.parametrize("change", ["source","header","object","receipt","profile","inventory"])
def test_raw_owner_current_cannot_be_replayed_after_changed_inputs(raw_owner_world,monkeypatch,change):
    w=raw_owner_world; current=w.current()
    if change in ("source","header"):
        path=w.root/(w.source if change=="source" else w.header);path.write_bytes(path.read_bytes()+b'\n')
    elif change in ("object","receipt"):
        path=w.case.units[w.source][change];path.write_bytes(path.read_bytes()+b' ')
    elif change=="profile":w.case.units[w.source]["command"].append("-DOTHER")
    else:
        import build
        monkeypatch.setattr(build,"search_inventory",lambda *a,**kw:"changed")
    with pytest.raises(P.InputRefused):current.plan_text()
    assert len(w.calls)==2


@pytest.mark.parametrize("change",["class","field","receiver"])
def test_raw_owner_retains_source_header_and_flag_macro_name_refusals(raw_owner_world,change):
    w=raw_owner_world
    name={"class":"C","field":"old","receiver":"this"}[change]
    if change=="class":w.case.units[w.source]["command"].append("-DC=D")
    else:
        body='#define '+name+' hidden\n'
        put(w.root,"Code/foreign.h",body)
        w.unit(w.source,w.text)
    if change=="receiver":
        w.text=w.text.replace('return old','return this->old');w.unit(w.source,w.text)
    with pytest.raises(P.InputRefused):w.current()


@pytest.mark.parametrize("white",["\f","\v","\r"])
@pytest.mark.parametrize("where",["source","header","flag"])
def test_raw_owner_keeps_v3_unsupported_whitespace_refused(raw_owner_world,white,where):
    w=raw_owner_world
    if where=="source":w.text=white+w.text;w.unit(w.source,w.text)
    elif where=="header":
        put(w.root,"Code/foreign.h",white+'#define C D\n');w.unit(w.source,w.text)
    else:w.case.units[w.source]["command"].append('-D'+white+'C=D')
    with pytest.raises(P.InputRefused):w.current()


@pytest.mark.parametrize("kind",["hidden-union","inactive","namespace","forged-line","clock","double","header-change"])
def test_raw_owner_whole_scope_provenance_and_double_capture_refusals(raw_owner_world,kind):
    w=raw_owner_world; item=w.case.units[w.source]
    if kind=="hidden-union":
        w.text=w.text.replace('return old','LOCALS return old');w.unit(w.source,w.text)
        item=w.case.units[w.source]
        item["stdout"]=item["stdout"].replace(b'LOCALS',b'union {int old;int canonical;};')
    elif kind=="inactive":item["stdout"]=item["stdout"].replace(b'int C::f() { return old; }',b'')
    elif kind=="namespace":item["stdout"]=item["stdout"].replace(b'C::C()',b'namespace N { C::C()')+b'}\n'
    elif kind=="forged-line":
        put(w.root,"Code/foreign.h",'#line 2 "Code/Owner.cpp"\n');w.unit(w.source,w.text)
    elif kind=="clock":item["stdout"]+=b'"12:34:56"\n'
    elif kind=="double":
        w.callback=lambda n:item.update(stdout=item["stdout"]+b'\n') if n==2 else None
    else:
        w.callback=lambda n:put(w.root,"Code/foreign.h","/* changed */\n") if n==1 else None
    with pytest.raises(P.InputRefused):w.current()


@pytest.mark.parametrize("body",[
    'int C::f(){ int old=0; return old; }',
    'int use(C &c){ return c.old; }',
    'class Foreign; int C::f(){ Foreign *p=0; return p->old; }',
])
def test_raw_owner_does_not_replace_foreign_free_scope_or_local_shadow_guards(raw_owner_world,body):
    w=raw_owner_world;w.text=w.text.replace('int C::f() { return old; }',body);w.unit(w.source,w.text)
    with pytest.raises(P.InputRefused):w.current()


@pytest.mark.parametrize("change",["missing-open","wrong-header-tokens","changed-source","extra-input","changed-second"])
def test_raw_owner_prospective_context_needs_separate_complete_actual_proof(raw_owner_world,change):
    w=raw_owner_world;current=w.current()
    path=w.prospective(current,opened=("Code/foreign.h",) if change=="missing-open" else ("Code/foreign.h",w.header))
    item=w.case.units[path]
    if change=="wrong-header-tokens":item["stdout"]=item["stdout"].replace(b'int canonical;',b'long canonical;')
    elif change=="changed-source":(w.root/path).write_text((w.root/path).read_text()+'// unexpected\n')
    elif change=="extra-input":
        put(w.root,"Code/new.h","/* new actual input */\n")
        item["stderr"]+=b'Note: including file: '+str(w.root/'Code/new.h').encode()+b'\n'
    elif change=="changed-second":
        w.callback=lambda n:item.update(stdout=item["stdout"]+b'\n') if n==4 else None
    with pytest.raises(P.InputRefused):P.capture_owner_pair(current,path)


@pytest.mark.parametrize("change",["source","mapping","header","root","text"])
def test_raw_owner_pair_cannot_be_retargeted_by_the_reader(raw_owner_world,change,tmp_path):
    w=raw_owner_world;current=w.current();pair=P.capture_owner_pair(current,w.prospective(current))
    source,text,mappings,root,seeds=w.source,w.text,{w.name:w.mapping},w.root,(w.header,)
    if change=="source":source="Code/Other.cpp"
    elif change=="mapping":mappings={w.name:{"old":"different"}}
    elif change=="header":seeds=("Code/Other.h",)
    elif change=="root":root=tmp_path/'other'
    else:text+='\n'
    with pytest.raises(P.InputRefused):pair.validate_for(source,text,mappings,root,seeds)
    assert len(w.calls)==4


def test_raw_owner_pair_pure_normal_preparation_keeps_all_field_guards(raw_owner_world,monkeypatch):
    w=raw_owner_world;current=w.current();pair=P.capture_owner_pair(current,w.prospective(current))
    import header_adopt_lane as lane
    old={"fwd":False,"key":"class","size":4,"bases":[],"fields":[[0,"old","int",4]],
         "statics":[],"methods":["C","f"],"virtual":[],"vslots":{},"vfptr":False}
    new={**old,"fields":[[0,"canonical","int",4]]}
    seen=[]
    def layouts(source,**kwargs):
        seen.append(source)
        return {"C":old if source==w.source else new}
    monkeypatch.setattr(lane.class_layouts,"compile_layouts",layouts)
    result=lane.prepare_unit(w.source,[w.name],w.header,"class",owner_witness=pair)
    assert result[1] is None and result[2]==current.plan_text()
    assert len(seen)==2 and len(w.calls)==4
    assert (w.root/w.source).read_text()==w.text
    # Existing ABI/field matching remains a separate non-negotiable gate.
    bad={**new,"fields":[[0,"canonical","float",4]]}
    monkeypatch.setattr(lane.class_layouts,"compile_layouts",lambda source,**kw:{"C":old if source==w.source else bad})
    assert lane.prepare_unit(w.source,[w.name],w.header,"class",owner_witness=pair)[1]


@pytest.mark.parametrize("change",["duplicate-class","nonglobal-class","wrong-file","backward-ctor-line",
                                   "missing-ctor","inline-use","free-token"])
def test_raw_owner_all_raw_occurrences_need_unique_exact_global_provenance(raw_owner_world,change):
    w=raw_owner_world;item=w.case.units[w.source]
    if change=="duplicate-class":item["stdout"]+=b'class C { int another; };\n'
    elif change=="nonglobal-class":item["stdout"]=item["stdout"].replace(b'class C',b'namespace N { class C')+b'}\n'
    elif change=="wrong-file":item["stdout"]=item["stdout"].replace(b'Code/Owner.cpp',b'Code/foreign.h')
    elif change=="backward-ctor-line":
        item["stdout"]=item["stdout"].replace(b'C::C()',b'#line 1 "Code/Owner.cpp"\nC::C()')
    elif change=="missing-ctor":item["stdout"]=item["stdout"].replace(b'C::C() : old(0) {}',b'')
    else:
        w.text=w.text.replace('int f();','int f(){return old;}' if change=="inline-use" else 'int f();')
        if change=="free-token":w.text+='int outside(C &c){return c.old;}\n'
        w.unit(w.source,w.text)
    with pytest.raises(P.InputRefused):w.current()


@pytest.mark.parametrize("flag",['-FIforced.h','@options.rsp','-Yuheader.h','-DC=D'])
def test_raw_owner_has_no_forced_response_pch_or_class_flag_fallback(raw_owner_world,flag):
    w=raw_owner_world;w.case.units[w.source]["command"].append(flag)
    with pytest.raises(P.InputRefused):w.current()


def test_raw_owner_generation_change_and_lost_strict_currency_refuse_even_equal_bytes(raw_owner_world):
    w=raw_owner_world;current=w.current();path=w.root/"Code/foreign.h"
    stat=path.stat();os.utime(path,ns=(stat.st_atime_ns,stat.st_mtime_ns+1_000_000_000))
    with pytest.raises(P.InputRefused,match="generation"):current.plan_text()
    assert len(w.calls)==2


def test_raw_owner_pair_cannot_ignore_prospective_profile_changes(raw_owner_world):
    w=raw_owner_world;current=w.current();path=w.prospective(current)
    w.case.units[path]["command"].append('-DOTHER')
    with pytest.raises(P.InputRefused,match="profile"):P.capture_owner_pair(current,path)
    assert len(w.calls)==2


@pytest.fixture
def owner_gate_world(raw_owner_world,monkeypatch):
    w=raw_owner_world
    import header_adopt_lane as lane
    current=w.current();pair=P.capture_owner_pair(current,w.prospective(current))
    w.pair=pair;w.gates=0;w.after_gate=None;w.verdict=None
    def gate(sources):
        assert sources==[w.source]
        w.gates+=1
        actual=(w.root/w.source).read_bytes()
        assert actual==(w.root/pair.prospective).read_bytes()
        unit=w.case.units[w.source]
        unit["object"].write_bytes(b'ordinary gate output, not a real compiler fixture\n')
        meta=json.loads(unit["receipt"].read_text())
        meta.update(version=2,path=w.source,source=hashlib.md5(actual).hexdigest(),
                    object=hashlib.md5(unit["object"].read_bytes()).hexdigest(),cmd="command",inventory="inventory",
                    deps={p:hashlib.md5((w.root/p).read_bytes()).hexdigest() for p in ('Code/foreign.h',w.header)})
        unit["receipt"].write_text(json.dumps(meta))
        if w.after_gate:w.after_gate(meta,unit)
        return {w.source:w.verdict}
    monkeypatch.setattr(lane,"gate_many",gate)
    w.current_witness=current
    return w


def test_owned_gate_seals_only_two_verified_outputs_and_restores_before_apply(owner_gate_world):
    w=owner_gate_world
    token=P.verify_owner_trial(w.pair)
    assert (w.root/w.source).read_text()==w.text and len(token.outputs)==2 and w.gates==1
    with pytest.raises(P.InputRefused):w.current_witness.plan_text()
    with pytest.raises(P.InputRefused):P.verify_owner_trial(w.pair)
    assert token.apply()
    assert (w.root/w.source).read_bytes()==(w.root/w.pair.prospective).read_bytes()
    with pytest.raises(P.InputRefused):token.apply()
    with pytest.raises(P.InputRefused):replace(token,candidate=b'not the captured candidate')
    assert len(w.calls)==4 and w.gates==1


@pytest.mark.parametrize("part",["object","receipt","source","header"])
def test_owned_gate_does_not_mask_foreign_edits_after_pass(owner_gate_world,part):
    w=owner_gate_world;token=P.verify_owner_trial(w.pair)
    path=(w.case.units[w.source][part] if part in ('object','receipt') else w.root/(w.source if part=='source' else w.header))
    foreign=path.read_bytes()+b'\nforeign\n';path.write_bytes(foreign)
    with pytest.raises(P.InputRefused):token.apply()
    assert path.read_bytes()==foreign
    if part!='source':assert (w.root/w.source).read_text()==w.text


@pytest.mark.parametrize("field",["source","object","cmd","deps"])
def test_owned_gate_wrong_receipt_never_mints_a_pass(owner_gate_world,field):
    w=owner_gate_world
    def wrong(meta,unit):
        meta[field]={} if field=='deps' else 'wrong'
        unit['receipt'].write_text(json.dumps(meta))
    w.after_gate=wrong
    with pytest.raises(P.InputRefused):P.verify_owner_trial(w.pair)
    assert (w.root/w.source).read_text()==w.text


@pytest.mark.parametrize("kind",["failure","throw","foreign-source","foreign-header","lost-strict-currency"])
def test_owned_gate_failure_or_mutation_cannot_apply_or_clobber_foreign_source(owner_gate_world,kind):
    w=owner_gate_world
    if kind=='failure':w.verdict='native byte mismatch'
    elif kind=='throw':
        def stop(meta,unit):raise RuntimeError('ordinary gate raised')
        w.after_gate=stop
    elif kind=='foreign-source':w.after_gate=lambda meta,unit:(w.root/w.source).write_bytes(b'foreign source bytes\n')
    elif kind=='foreign-header':w.after_gate=lambda meta,unit:(w.root/w.header).write_bytes(b'foreign header bytes\n')
    else:w.after_gate=lambda meta,unit:unit.update(state=replace(unit['state'],reusable=False))
    with pytest.raises((P.InputRefused,RuntimeError)):P.verify_owner_trial(w.pair)
    assert (w.root/w.source).read_bytes()==(b'foreign source bytes\n' if kind=='foreign-source' else w.text.encode())
    with pytest.raises(P.InputRefused):w.current_witness.plan_text()


def test_owned_normal_adopt_uses_paired_layouts_and_unchanged_gate_then_cas_apply(owner_gate_world,monkeypatch):
    w=owner_gate_world
    import header_adopt_lane as lane
    old={"fwd":False,"key":"class","size":4,"bases":[],"fields":[[0,"old","int",4]],
         "statics":[],"methods":["C","f"],"virtual":[],"vslots":{},"vfptr":False}
    new={**old,"fields":[[0,"canonical","int",4]]}
    seen=[]
    def layouts(source,**kwargs):
        assert (w.root/w.source).read_text()==w.text
        seen.append(source);return {"C":old if source==w.source else new}
    monkeypatch.setattr(lane.class_layouts,"compile_layouts",layouts)
    monkeypatch.setattr(lane,"prospective_renames",lambda sources,*a:[(s,None,None,[]) for s in sources])
    monkeypatch.setattr(lane,"adoption_dependencies",lambda *a:{})
    monkeypatch.setattr(lane,"key_backref_blockers",lambda *a:{})
    monkeypatch.setattr(lane,"key_metadata_blockers",lambda *a:{})
    assert lane.adopt(w.name,w.header,[w.source],apply=True,owner_witness=w.pair)==0
    assert seen==[w.source,w.pair.prospective]
    assert (w.root/w.source).read_bytes()==(w.root/w.pair.prospective).read_bytes()
    assert w.gates==1 and len(w.calls)==4


def test_owned_route_refuses_multiple_sources_or_class_key_changes_before_any_gate(owner_gate_world,monkeypatch):
    w=owner_gate_world
    import header_adopt_lane as lane
    assert lane.adopt(w.name,w.header,[w.source,'Code/Other.cpp'],apply=True,owner_witness=w.pair)==2
    text=(w.root/w.header).read_text().replace('class C','struct C');put(w.root,w.header,text)
    assert lane.adopt(w.name,w.header,[w.source],apply=True,owner_witness=w.pair)==1
    assert w.gates==0 and (w.root/w.source).read_text()==w.text


@pytest.fixture
def metadata_owner_world(raw_owner_world, monkeypatch):
    """All native policy domains already exist BEFORE the immutable capture."""
    w = raw_owner_world
    w.controls = (
        'reverse/functions.csv', 'reverse/data_rows.csv', 'reverse/symbols.csv',
        'reverse/dir32_consistency_whitelist.txt', 'reverse/canonical_classes.csv',
        'reverse/header_queue.tsv', 'reverse/class_contracts/C.json',
        'reverse/body_owners.csv', 'reverse/data_converged.csv',
        'reverse/gate_baseline.txt', 'reverse/flag_overrides.csv',
        'baselines/retail/manifest.json', 'baselines/retail/files/game.dat',
        'tools/native_policy.py', '.githooks/pre-commit', '.github/workflows/gate.yml',
        'AGENTS.md')
    for path in w.controls:
        put(w.root, path, b'unchanged native policy fixture\n', tracked=False)
    git(w.root, 'add', '--', *w.controls)
    return owner_gate_world.__wrapped__(w, monkeypatch)


@pytest.mark.parametrize('path', [
    'reverse/functions.csv', 'reverse/data_rows.csv', 'reverse/symbols.csv',
    'reverse/dir32_consistency_whitelist.txt', 'reverse/canonical_classes.csv',
    'reverse/header_queue.tsv', 'reverse/class_contracts/C.json',
    'reverse/body_owners.csv', 'reverse/data_converged.csv',
    'reverse/gate_baseline.txt', 'reverse/flag_overrides.csv',
    'baselines/retail/manifest.json', 'baselines/retail/files/game.dat',
    'tools/native_policy.py', '.githooks/pre-commit', '.github/workflows/gate.yml',
    'AGENTS.md'])
def test_owner_current_binds_actual_metadata_baseline_policy_and_modules(metadata_owner_world, path):
    w = metadata_owner_world
    (w.root/path).write_bytes(b'changed verifier or ownership truth\n')
    with pytest.raises(P.InputRefused): w.current_witness.plan_text()
    assert w.gates == 0 and len(w.calls) == 4


@pytest.mark.parametrize('change', ['removed', 'new-file', 'new-domain', 'new-directory', 'same-bytes-generation'])
def test_owner_control_population_and_optional_absence_are_inputs(metadata_owner_world, change):
    w = metadata_owner_world
    if change == 'removed':
        (w.root/'reverse/data_converged.csv').unlink()
    elif change == 'new-file':
        put(w.root, 'reverse/previously-absent-policy.tsv', b'new policy', tracked=False)
    elif change == 'new-domain':
        # A previously absent control subdomain is not discoverable after capture.
        put(w.root, 'reverse/new_contracts/D.json', b'{}', tracked=False)
    elif change == 'new-directory':
        (w.root/'tools/new_policy_directory').mkdir()
    else:
        path = w.root/'reverse/functions.csv'; stamp = path.stat()
        os.utime(path, ns=(stamp.st_atime_ns, stamp.st_mtime_ns+1_000_000_000))
    with pytest.raises(P.InputRefused): w.current_witness.plan_text()


@pytest.mark.parametrize('domain', ['reverse', 'baselines', 'tools', '.githooks', '.github'])
def test_owner_missing_control_tree_cannot_appear_after_current(raw_owner_world, domain):
    w = raw_owner_world; current = w.current()
    assert not (w.root/domain).exists()
    put(w.root, domain+'/new-input.txt', b'new input', tracked=False)
    with pytest.raises(P.InputRefused): current.plan_text()


@pytest.mark.parametrize('stage', ['current', 'gate', 'after-pass'])
@pytest.mark.parametrize('change', ['ledger', 'contract', 'policy', 'module', 'absent-to-new', 'head', 'index'])
def test_owner_metadata_fence_survives_pair_gate_and_apply(metadata_owner_world, stage, change):
    w = metadata_owner_world
    def mutate():
        if change == 'head':
            git(w.root, '-c', 'user.name=Fixture', '-c', 'user.email=fixture@example.invalid',
                'commit', '--allow-empty', '-qm', 'independent new HEAD')
        elif change == 'index':
            put(w.root, 'Code/unrelated-new-input.h', b'// index changed\n')
        else:
            path = {'ledger':'reverse/functions.csv', 'contract':'reverse/class_contracts/C.json',
                    'policy':'reverse/dir32_consistency_whitelist.txt', 'module':'tools/native_policy.py',
                    'absent-to-new':'reverse/brand-new-native-rule.tsv'}[change]
            put(w.root, path, b'changed after immutable capture\n', tracked=False)
    if stage == 'current':
        mutate()
        with pytest.raises(P.InputRefused): w.current_witness.plan_text()
    elif stage == 'gate':
        w.after_gate = lambda meta, unit: mutate()
        with pytest.raises(P.InputRefused): P.verify_owner_trial(w.pair)
    else:
        token = P.verify_owner_trial(w.pair); mutate()
        with pytest.raises(P.InputRefused): token.apply()
    assert (w.root/w.source).read_text() == w.text
    assert len(w.calls) == 4


def test_owner_current_binds_complete_actual_environment(raw_owner_world):
    w = raw_owner_world; current = w.current()
    w.case.units[w.source]['env']['OTHER_COMPILER_POLICY'] = 'new context'
    with pytest.raises(P.InputRefused): current.plan_text()


@pytest.mark.parametrize('stage', ['trial', 'apply'])
@pytest.mark.parametrize('fault', ['read', 'before-write', 'after-write', 'interrupt', 'replace-after-write'])
def test_owner_all_own_write_and_first_read_failures_restore_generation(owner_gate_world, monkeypatch, stage, fault):
    import header_adopt_lane as lane
    w = owner_gate_world; source = (w.root/w.source).resolve()
    candidate = (w.root/w.pair.prospective).read_bytes()
    token = P.verify_owner_trial(w.pair) if stage == 'apply' else None
    failed = False
    if fault == 'read':
        original = P._owner_read
        def operation(path):
            nonlocal failed
            if not failed and Path(path).resolve() == source and source.read_bytes() == candidate:
                failed = True
                raise OSError('one transient first ownership read')
            return original(path)
        monkeypatch.setattr(P, '_owner_read', operation)
    elif fault == 'replace-after-write':
        original = lane.os.replace
        def operation(old, new):
            nonlocal failed
            result = original(old, new)
            if not failed and Path(new).resolve() == source:
                failed = True
                raise OSError('replace completed before its wrapper raised')
            return result
        monkeypatch.setattr(lane.os, 'replace', operation)
    else:
        original = lane.GenerationWrites.write
        def operation(self, path, data):
            nonlocal failed
            selected = not failed and Path(path).resolve() == source and data == candidate
            if selected and fault == 'before-write':
                failed = True
                raise OSError('failed before own write')
            result = original(self, path, data)
            if selected:
                failed = True
                if fault == 'interrupt': raise KeyboardInterrupt('interrupted after own write')
                raise OSError('own write completed before its wrapper raised')
            return result
        monkeypatch.setattr(lane.GenerationWrites, 'write', operation)
    with pytest.raises((OSError, KeyboardInterrupt)):
        token.apply() if token is not None else P.verify_owner_trial(w.pair)
    assert failed and source.read_bytes() == w.text.encode()
    assert not list(source.parent.glob('.header-generation-*'))


@pytest.mark.parametrize('stage', ['trial', 'apply'])
@pytest.mark.parametrize('same_bytes', [False, True])
def test_owner_cleanup_preserves_foreign_generation_even_when_candidate_bytes_equal(
        owner_gate_world, monkeypatch, stage, same_bytes):
    import header_adopt_lane as lane
    w = owner_gate_world; source = (w.root/w.source).resolve()
    candidate = (w.root/w.pair.prospective).read_bytes()
    foreign = candidate if same_bytes else b'foreign independent source bytes\n'
    token = P.verify_owner_trial(w.pair) if stage == 'apply' else None
    original = lane.GenerationWrites.write
    changed, foreign_record = False, None
    def operation(self, path, data):
        nonlocal changed, foreign_record
        result = original(self, path, data)
        if not changed and Path(path).resolve() == source and data == candidate:
            changed = True
            replacement = source.with_name('foreign-replacement.cpp')
            replacement.write_bytes(foreign)
            os.replace(replacement, source)
            foreign_record = P._owner_read(source)[0]
            raise OSError('foreign edit and then an interrupted owner write')
        return result
    monkeypatch.setattr(lane.GenerationWrites, 'write', operation)
    with pytest.raises(P.InputRefused):
        token.apply() if token is not None else P.verify_owner_trial(w.pair)
    assert changed and source.read_bytes() == foreign
    assert P._owner_read(source)[0] == foreign_record


def test_owner_unsupported_rename_generation_refuses_before_touching_original(owner_gate_world, monkeypatch):
    import header_adopt_lane as lane
    w = owner_gate_world; source = (w.root/w.source).resolve()
    before = P._owner_read(source)[0]
    original = lane.os.replace
    def changed_generation(old, new):
        result = original(old, new)
        if Path(new).name.startswith('.header-generation-'):
            stamp = Path(new).stat()
            os.utime(new, ns=(stamp.st_atime_ns, stamp.st_mtime_ns+1_000_000_000))
        return result
    monkeypatch.setattr(lane.os, 'replace', changed_generation)
    with pytest.raises(lane.GenerationRefused, match='preserve'):
        P.verify_owner_trial(w.pair)
    assert P._owner_read(source)[0] == before and w.gates == 0
    assert not list(source.parent.glob('.header-generation-*'))


@pytest.mark.parametrize('where', ['root', 'domain', 'tracked-child', 'untracked-child'])
@pytest.mark.parametrize('failure', [PermissionError, OSError, RuntimeError])
def test_owner_population_enumeration_errors_never_issue_partial_witness(
        raw_owner_world, monkeypatch, where, failure):
    w = raw_owner_world
    put(w.root, 'reverse/class_contracts/C.json', b'known contract\n')
    put(w.root, 'reverse/untracked-policy/new.txt', b'untracked policy\n', tracked=False)
    relative = {'root':'', 'domain':'reverse', 'tracked-child':'reverse/class_contracts',
                'untracked-child':'reverse/untracked-policy'}[where]
    target = w.root/relative
    if where == 'root':
        original = Path.iterdir
        def enumerate_paths(path):
            if path == target: raise failure('unproved root population')
            return original(path)
        monkeypatch.setattr(Path, 'iterdir', enumerate_paths)
    else:
        original = os.scandir
        def scandir(path):
            if Path(path) == target: raise failure('unproved control population')
            return original(path)
        monkeypatch.setattr(os, 'scandir', scandir)
    with pytest.raises(P.InputRefused): w.current()
    assert not w.calls


@pytest.mark.parametrize('relative', [
    'AGENTS.md', 'reverse', 'reverse/class_contracts',
    'reverse/class_contracts/C.json', 'reverse/untracked-policy.txt'])
@pytest.mark.parametrize('failure', [FileNotFoundError, PermissionError, OSError])
def test_owner_listed_control_classification_errors_never_mean_absence(
        raw_owner_world, monkeypatch, relative, failure):
    w = raw_owner_world
    put(w.root, 'AGENTS.md', b'known root control\n')
    put(w.root, 'reverse/class_contracts/C.json', b'known contract\n')
    put(w.root, 'reverse/untracked-policy.txt', b'new control\n', tracked=False)
    target = w.root/relative; original = Path.lstat
    def lstat(path, *args, **kwargs):
        if path == target: raise failure('classification I/O failure, not proven absence')
        return original(path, *args, **kwargs)
    monkeypatch.setattr(Path, 'lstat', lstat)
    with pytest.raises(P.InputRefused): w.current()
    assert not w.calls


@pytest.mark.parametrize('relative', [
    'AGENTS.md', 'reverse/class_contracts/C.json', 'tools/native-policy.py',
    '.githooks/pre-commit', '.github/workflows/gate.yml', 'baselines/retail/game.dat',
    'tools/__pycache__/tracked-policy.py'])
def test_owner_every_indexed_control_file_must_really_be_in_population(raw_owner_world, relative):
    w = raw_owner_world; path = put(w.root, relative, b'tracked before capture\n')
    path.unlink()
    with pytest.raises(P.InputRefused): w.current()
    assert not w.calls


@pytest.mark.parametrize('domain', ['reverse', 'baselines', 'tools', '.githooks', '.github'])
def test_owner_absent_domain_with_index_descendants_is_not_optional(raw_owner_world, domain):
    w = raw_owner_world; path = put(w.root, domain+'/known.txt', b'known tracked input\n')
    path.unlink(); (w.root/domain).rmdir()
    with pytest.raises(P.InputRefused): w.current()
    assert not w.calls


def test_owner_index_coverage_refuses_silently_omitted_tracked_file(raw_owner_world, monkeypatch):
    w = raw_owner_world
    put(w.root, 'reverse/class_contracts/C.json', b'known contract\n')
    original = os.walk
    def incomplete_walk(base, *args, **kwargs):
        for directory, subdirs, files in original(base, *args, **kwargs):
            yield directory, subdirs, [f for f in files if f != 'C.json']
    monkeypatch.setattr(os, 'walk', incomplete_walk)
    with pytest.raises(P.InputRefused, match='every indexed'): w.current()
    assert not w.calls


def test_owner_untracked_controls_are_observed_and_optional_domains_are_proven_absent(raw_owner_world):
    w = raw_owner_world
    put(w.root, 'reverse/untracked/authority.txt', b'untracked policy\n', tracked=False)
    population, paths = P._owner_policy_population(w.root)
    assert ('reverse/untracked/authority.txt', 'file') in population
    assert w.root/'reverse/untracked/authority.txt' in paths
    assert ('baselines', 'absent') in population and ('.github', 'absent') in population
    current = w.current()
    (w.root/'reverse/untracked/authority.txt').write_bytes(b'changed untracked policy\n')
    with pytest.raises(P.InputRefused): current.plan_text()


@pytest.mark.parametrize('relative', ['AGENTS.md', 'reverse/untracked-policy.txt'])
@pytest.mark.parametrize('unsupported', ['symlink', 'special'])
def test_owner_nonordinary_listed_control_input_is_never_silently_dropped(
        raw_owner_world, monkeypatch, relative, unsupported):
    import stat
    from types import SimpleNamespace
    w = raw_owner_world; target = put(w.root, relative, b'control bytes\n', tracked=False)
    original = Path.lstat
    def lstat(path, *args, **kwargs):
        if path == target:
            return SimpleNamespace(st_mode=stat.S_IFLNK if unsupported == 'symlink' else stat.S_IFIFO)
        return original(path, *args, **kwargs)
    monkeypatch.setattr(Path, 'lstat', lstat)
    with pytest.raises(P.InputRefused, match='unsupported type'): w.current()
    assert not w.calls


def test_owner_generated_cache_rule_cannot_hide_tracked_authority(raw_owner_world):
    w = raw_owner_world
    tracked = put(w.root, 'tools/__pycache__/tracked-policy.py', b'tracked authority\n')
    ordinary = put(w.root, 'tools/__pycache__/ordinary.cache', b'generated cache\n', tracked=False)
    population, paths = P._owner_policy_population(w.root)
    assert tracked in paths and ordinary in paths
    assert ('tools/__pycache__', 'directory') in population


def test_owner_existing_generated_untracked_cache_rule_is_unchanged(raw_owner_world):
    w = raw_owner_world
    generated = put(w.root, 'tools/__pycache__/ordinary.cache', b'generated cache\n', tracked=False)
    population, paths = P._owner_policy_population(w.root)
    assert generated not in paths
    assert ('tools/__pycache__', 'directory') not in population


def test_owner_policy_stream_stat_error_refuses_without_partial_generation(raw_owner_world, monkeypatch):
    w = raw_owner_world; path = put(w.root, 'reverse/untracked-policy.txt', b'policy', tracked=False)
    original = Path.stat
    def stat(q, *args, **kwargs):
        if q == path: raise PermissionError('one policy read classification failed')
        return original(q, *args, **kwargs)
    monkeypatch.setattr(Path, 'stat', stat)
    with pytest.raises(P.InputRefused): P._owner_policy_read(path)


@pytest.mark.parametrize('domain', ['reverse', 'baselines', 'tools', '.githooks', '.github'])
@pytest.mark.parametrize('missing', [False, True])
def test_owner_noncanonical_index_control_domain_refuses_without_path_alias(
        raw_owner_world, domain, missing):
    w = raw_owner_world
    # Refusal is explicit even on a case-sensitive host: it never treats two
    # differently spelled paths as the same physical file.
    path = put(w.root, domain.upper()+'/authority.txt', b'tracked authority\n')
    if missing: path.unlink()
    with pytest.raises(P.InputRefused, match='noncanonical'): w.current()
    assert not w.calls


def test_owner_case_adjacent_unrelated_index_directory_is_not_aliased(raw_owner_world):
    w = raw_owner_world
    put(w.root, 'ReverseTools/unrelated.txt', b'not a native control-domain prefix\n')
    current = w.current()
    assert current.plan_text() and len(w.calls) == 2


def test_owner_native_untracked_case_equivalent_control_still_observed(raw_owner_world):
    w = raw_owner_world
    path = put(w.root, 'Reverse/authority.txt', b'untracked native authority\n', tracked=False)
    # A case-sensitive host has a distinct unrelated directory. Do not join it.
    canonical = w.root/'reverse/authority.txt'
    current = w.current()
    observed = {Path(record[0]) for record in current._state.project.files}
    if canonical.exists():
        assert canonical.resolve() in observed
        path.write_bytes(b'changed native authority\n')
        with pytest.raises(P.InputRefused): current.plan_text()
    else:
        assert path.resolve() not in observed


@pytest.fixture
def ordered_owner_world(raw_owner_world):
    """Native region-vs-unrowed ordering, at the existing ordinary-command boundary."""
    w = raw_owner_world
    original = w.case.units[w.source]['command']
    w.case.units[w.source]['command'] = [original[0], '-nologo', '-c',
        '-O2', '-GR-', '-EHsc-', '-O1', '-arch:SSE', '-G7', '-Ireference/context',
        '-Ob1', '-EHsc', '-DNDEBUG', '-MD', *original[-2:]]
    current = w.current()
    path = w.prospective(current)
    physical = w.case.units[path]['command']
    w.case.units[path]['command'] = [physical[0], '-nologo', '-c',
        '-O2', '-GR-', '-EHsc-', '-Ireference/context', '-O1', '-Ob1', '-EHsc',
        '-DNDEBUG', '-MD', '-arch:SSE', '-G7', *physical[-2:]]
    w.current_witness, w.prospective_path = current, path
    return w


def test_owner_context_preserves_exact_origin_order_in_both_pp_and_layout(ordered_owner_world):
    w = ordered_owner_world
    before = (w.root/w.source).read_bytes()
    pair = P.capture_owner_pair(w.current_witness, w.prospective_path)
    origin = w.current_witness._state.profiles[0][2]
    expected_pp = [arg for arg in origin if not arg.startswith(('-Fo', '/Fo'))]
    expected_pp[expected_pp.index('-c')] = '-E'
    expected_pp[-1] = pair.prospective
    expected_pp.append('-showIncludes')
    assert w.calls[2:] == [tuple(expected_pp), tuple(expected_pp)]
    output = w.root/'build/context-layout.obj'
    original, original_env = P._normal_command(w.root, w.source, output)
    expected = list(original); expected[-1] = pair.prospective
    command, env = P._owner_layout_builder(pair).compiler_command(w.root/pair.prospective, output)
    assert command == expected and env == original_env
    assert (w.root/w.source).read_bytes() == before
    assert (w.root/pair.prospective).read_bytes() == w.current_witness.plan_text().encode()
    assert len(w.calls) == 4


@pytest.mark.parametrize('change', ['new', 'missing', 'duplicate', 'define', 'forced-include',
                                   'include', 'compiler', 'env', 'source-missing', 'source-duplicate',
                                   'source-wrong', 'source-not-final', 'fo-missing', 'fo-duplicate'])
def test_owner_context_refuses_any_nonpermutation_or_operand_drift(ordered_owner_world, change):
    w = ordered_owner_world; unit = w.case.units[w.prospective_path]
    command = unit['command']
    if change == 'new': command.insert(-2, '-G6')
    elif change == 'missing': command.remove('-G7')
    elif change == 'duplicate': command.insert(-2, '-G7')
    elif change == 'define': command.insert(-2, '-DOTHER')
    elif change == 'forced-include': command.insert(-2, '-FIunobserved.h')
    elif change == 'include': command[command.index('-Ireference/context')] = '-Ireference/other'
    elif change == 'compiler': command[0] = str(w.root/'another-cl.exe')
    elif change == 'env': unit['env'] = {'INCLUDE':'other-root'}
    elif change == 'source-missing': command.pop()
    elif change == 'source-duplicate': command.insert(-2, w.prospective_path)
    elif change == 'source-wrong': command[-1] = 'Code/Foreign.cpp'
    elif change == 'source-not-final': command.append('-DNDEBUG')
    elif change == 'fo-missing': command[:] = [a for a in command if not a.startswith('-Fo')]
    else: command.insert(-2, '-Foanother.obj')
    with pytest.raises(P.InputRefused): P.capture_owner_pair(w.current_witness, w.prospective_path)
    assert len(w.calls) == 2


@pytest.mark.parametrize('change', ['origin-profile', 'probe-profile', 'origin-env', 'probe-env',
                                   'inventory', 'source', 'header'])
def test_owner_context_revalidation_refuses_drift_after_pair(ordered_owner_world, monkeypatch, change):
    w = ordered_owner_world; pair = P.capture_owner_pair(w.current_witness, w.prospective_path)
    if change in ('origin-profile', 'probe-profile'):
        path = w.source if change.startswith('origin') else pair.prospective
        w.case.units[path]['command'].insert(-2, '-DOTHER')
    elif change in ('origin-env', 'probe-env'):
        path = w.source if change.startswith('origin') else pair.prospective
        w.case.units[path]['env'] = {'INCLUDE':'different'}
    elif change == 'inventory':
        import build
        monkeypatch.setattr(build, 'search_inventory', lambda *a, **kw:'different')
    else:
        path = w.root/(pair.prospective if change == 'source' else w.header)
        path.write_bytes(path.read_bytes()+b'\nchanged\n')
    with pytest.raises(P.InputRefused):
        P._owner_layout_builder(pair).compiler_command(w.root/pair.prospective, w.root/'build/context-layout.obj')
    assert len(w.calls) == 4


def test_owner_context_revalidates_between_actual_paired_pp_calls(ordered_owner_world):
    w = ordered_owner_world
    w.callback = lambda n:w.case.units[w.source]['command'].insert(-2, '-DOTHER') if n == 3 else None
    with pytest.raises(P.InputRefused): P.capture_owner_pair(w.current_witness, w.prospective_path)
    assert len(w.calls) == 3


@pytest.mark.parametrize('change', ['missing', 'duplicate', 'wrong', 'not-final', 'wrong-output'])
def test_owner_layout_context_rechecks_fresh_native_operand_shape(ordered_owner_world, monkeypatch, change):
    w = ordered_owner_world; pair = P.capture_owner_pair(w.current_witness, w.prospective_path)
    output = w.root/'build/context-layout.obj'; native = P._normal_command
    def corrupt(root, source, target):
        command, env = native(root, source, target)
        if Path(target) == output and source == w.source:
            if change == 'missing': command.pop()
            elif change == 'duplicate': command.insert(-2, source)
            elif change == 'wrong': command[-1] = 'Code/Other.cpp'
            elif change == 'not-final': command.append('-DNDEBUG')
            else: command[-2] = '-Fobuild/wrong-layout.obj'
        return command, env
    monkeypatch.setattr(P, '_normal_command', corrupt)
    with pytest.raises(P.InputRefused): P._owner_layout_builder(pair).compiler_command(w.root/pair.prospective, output)
    assert len(w.calls) == 4


def test_owner_layout_context_has_no_current_only_foreign_or_free_builder_rights(ordered_owner_world):
    w = ordered_owner_world; pair = P.capture_owner_pair(w.current_witness, w.prospective_path)
    with pytest.raises(P.InputRefused): P._owner_layout_builder(w.current_witness)
    with pytest.raises(P.InputRefused): P._OwnerLayoutBuilder(pair)
    with pytest.raises(P.InputRefused): P._OwnerSourceContext(w.current_witness, pair.prospective)
    with pytest.raises(P.InputRefused): replace(pair, current=replace(pair.current))
    with pytest.raises(P.InputRefused):
        P._owner_layout_builder(pair).compiler_command(w.root/w.source, w.root/'build/context-layout.obj')
    with pytest.raises(P.InputRefused):
        P._owner_profile(w.root, pair.prospective, w.root/'build/context-layout.obj', object())
    assert len(w.calls) == 4


@pytest.mark.parametrize('stage', ['during-gate', 'after-pass'])
@pytest.mark.parametrize('part', ['origin-profile', 'probe-profile', 'origin-env', 'probe-env'])
def test_owner_context_cannot_reuse_changed_profile_through_gate_restore_apply(owner_gate_world, stage, part):
    w = owner_gate_world
    def drift():
        source = w.source if part.startswith('origin') else w.pair.prospective
        if part.endswith('profile'): w.case.units[source]['command'].insert(-2, '-DOTHER')
        else: w.case.units[source]['env'] = {'INCLUDE':'different'}
    if stage == 'during-gate':
        w.after_gate = lambda meta, unit:drift()
        with pytest.raises(P.InputRefused): P.verify_owner_trial(w.pair)
    else:
        token = P.verify_owner_trial(w.pair); drift()
        with pytest.raises(P.InputRefused): token.apply()
    assert (w.root/w.source).read_text() == w.text

