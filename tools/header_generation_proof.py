"""Fail-closed native provenance for one narrow canonical declaration input.

No header is an object owner. Facts and emission below always come from each
real source's current match object; diagnostic CodeView supplies layout only.
"""
from dataclasses import dataclass, field
import hashlib
import json
from pathlib import Path
import re
import struct
from types import MappingProxyType
from typing import Mapping

import header_generation_inputs as I


ROOT = Path(__file__).resolve().parents[1]
InputRefused = I.InputRefused
_COMMENT = re.compile(r'//[^\n]*|/\*.*?\*/', re.S)
_TOKEN = re.compile(r'\s+|[A-Za-z_][A-Za-z_0-9]*|(?:[0-9][A-Za-z_0-9.]*)|"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'|::|->\*|->|\.\*|\.\.\.|<<=?|>>=?|[+*/%&|^!=<>-]=|&&|\|\||\+\+|--|[{}()[\];,:~?=.+*/%&|^!<>-]')
_MARKER = re.compile(r'^[ \t]*#[ \t]*line[ \t]+([0-9]+)[ \t]+"((?:[^"\\]|\\.)*)"[ \t]*$')
_FORBIDDEN = re.compile(r"\b(?:namespace|template|typedef|using|union|enum|friend|operator|alignas|__declspec|__attribute__|__pragma|__identifier)\b")


def _freeze(value):
    if isinstance(value, dict):
        return MappingProxyType({k: _freeze(v) for k, v in value.items()})
    if isinstance(value, (list, tuple)):
        return tuple(_freeze(v) for v in value)
    if isinstance(value, set):
        return frozenset(value)
    return value


def _comments(text):
    # This first admission deliberately has no literals in the declaration.
    return _COMMENT.sub(lambda m: re.sub(r"[^\n]", " ", m[0]), text)


def _tokens(text):
    out, pos = [], 0
    while pos < len(text):
        match = _TOKEN.match(text, pos)
        if not match:
            raise InputRefused(f"unsupported token at declaration offset {pos}")
        if not match[0].isspace():
            out.append((match[0], pos, match.end()))
        pos = match.end()
    return out


def _generator_padding(contract):
    """Only the owning layout planner's literal gap arrays, never array fields."""
    import header_adopt_lane as lane
    try:
        plan, problems = lane.layout_plan(contract)
        if problems:
            raise InputRefused("canonical padding layout is unproved: " + "; ".join(problems))
        fields = [f for f in contract["fields"] if f.get("kind") != "VPTR"]
        polymorphic = bool(contract.get("vslots")) or any(f.get("kind") == "VPTR" for f in contract["fields"])
        cursor = max(4, max((lane.field_alignment(f) or 1 for f in fields), default=1)) if polymorphic else 0
        pads = {}
        for entry in plan:
            if entry[0] == "field":
                cursor = entry[1]["offset"] + entry[1]["size"]
            else:
                _, name, size = entry
                if type(size) is not int or size <= 0 or name in pads:
                    raise InputRefused("canonical generator padding is ambiguous")
                pads[name] = (cursor, size)
                cursor += size
        return pads
    except (KeyError, TypeError, ValueError) as exc:
        raise InputRefused("canonical padding layout cannot be proved: " + str(exc)) from exc


def _role_checked_syntax(text, name, contract):
    """Mask only verified allocation declarations and exact generated gap storage.

    The original complete tokens still bind native preprocessor provenance;
    method selection and ownership are still judged by RegisteredGeneration.
    """
    import header_adopt_lane as lane
    pads, seen = _generator_padding(contract), set()
    members = lane.class_members(text, name)
    if members is None:
        raise InputRefused("canonical member roles cannot be read")
    result, position = text, 0
    for _access, member in members:
        at = text.find(member, position)
        if at < 0:
            raise InputRefused("canonical member role has no unique lexical span")
        position = at + len(member)
        special = None
        if re.search(r"\boperator\b", member):
            records = lane.declaration_records("class " + name + " { public: " + member + " };", name)
            allocation = re.fullmatch(
                r"static\s+void\s*\*\s*operator\s+new\s*(?:\[\s*\])?\s*"
                r"\(\s*unsigned(?:\s+int)?(?:\s+[A-Za-z_][A-Za-z_0-9]*)?\s*\)\s*;", member)
            deallocation = re.fullmatch(
                r"static\s+void\s+operator\s+delete\s*(?:\[\s*\])?\s*"
                r"\(\s*void\s*\*(?:\s*[A-Za-z_][A-Za-z_0-9]*)?\s*\)\s*;", member)
            if (not allocation and not deallocation or not records or len(records) != 1
                    or records[0]["role"] != "method" or records[0]["inline"]):
                raise InputRefused("canonical operator is not a supported allocation method declaration")
            special = member
        elif "[" in member or "]" in member:
            found = re.fullmatch(r"char\s+([A-Za-z_][A-Za-z_0-9]*)\[([1-9][0-9]*)\]\s*;", member)
            if (found is None or lane.member_role(member, name) is not None
                    or found[1] not in pads or str(pads[found[1]][1]) != found[2] or found[1] in seen):
                raise InputRefused("canonical array is not exact owning-generator gap padding")
            seen.add(found[1])
            special = member
        if special is not None:
            result = result[:at] + re.sub(r"[^\n]", " ", special) + result[at + len(special):]
    if seen != set(pads):
        raise InputRefused("canonical generator gap padding is missing or ambiguous")
    return result, bool(seen)


def _elide_header(raw, name, contract):
    """Only a literal global class with a real whole-file guard/once wrapper."""
    if not re.fullmatch(r"[A-Za-z_][A-Za-z_0-9]*", name):
        raise InputRefused("qualified or ambiguous canonical class name is unsupported")
    if not raw.isascii() or b"\0" in raw or b"\\" in raw or b"??" in raw or b"%:" in raw:
        raise InputRefused("canonical header has encoding, splice, UCN or alternative-token ambiguity")
    text = raw.decode("ascii")
    if "/*" in text and "*/" not in text[text.find("/*") + 2:]:
        raise InputRefused("canonical header has an unterminated comment")
    code = _comments(text)
    if '"' in code or "'" in code:
        raise InputRefused("canonical declaration literals need a broader lexical proof")
    lines = code.splitlines(keepends=True)
    active = [i for i, line in enumerate(lines) if line.strip()]
    elided, guard = set(), None
    once = [i for i in active if re.fullmatch(r"[ \t]*#[ \t]*pragma[ \t]+once[ \t]*(?:\r?\n)?", lines[i])]
    if len(once) > 1:
        raise InputRefused("canonical header has repeated pragma once")
    if once:
        # A pragma inside the class is not an outer wrapper.
        if once[0] not in active[:1]:
            raise InputRefused("pragma once is not the canonical header's outer wrapper")
        elided.update(once)
        active = [i for i in active if i not in elided]
    if active and lines[active[0]].lstrip().startswith("#"):
        first = re.fullmatch(r"[ \t]*#[ \t]*ifndef[ \t]+([A-Za-z_][A-Za-z_0-9]*)[ \t]*(?:\r?\n)?", lines[active[0]])
        if first is None or len(active) < 4:
            raise InputRefused("canonical header has no proven literal whole-file guard")
        guard = first[1]
        define = re.fullmatch(r"[ \t]*#[ \t]*define[ \t]+" + re.escape(guard) + r"[ \t]*(?:\r?\n)?", lines[active[1]])
        closing = re.fullmatch(r"[ \t]*#[ \t]*endif[ \t]*(?:\r?\n)?", lines[active[-1]])
        if define is None or closing is None:
            raise InputRefused("canonical header guard does not wrap its whole file")
        elided.update((active[0], active[1], active[-1]))
    parsed = "".join(re.sub(r"[^\n]", " ", line) if i in elided else line for i, line in enumerate(lines))
    if "#" in parsed:
        raise InputRefused("canonical declaration has conditional, macro or other directives")
    tokens = _tokens(parsed)
    if len(tokens) < 5 or tokens[0][0] not in ("class", "struct") or tokens[1][0] != name or tokens[2][0] != "{":
        raise InputRefused("canonical declaration is not exactly one literal global baseless class")
    if (contract.get("class") != name or contract.get("key") != tokens[0][0] or contract.get("bases") != []
            or type(contract.get("size")) is not int or contract["size"] <= 0
            or not isinstance(contract.get("fields"), list) or not isinstance(contract.get("vslots"), dict)):
        raise InputRefused("canonical declaration identity/key/bases disagree with its contract")
    depth, end = 0, None
    for i, (token, _start, _end) in enumerate(tokens[2:], 2):
        if token in ("class", "struct"):
            raise InputRefused("nested or elaborated aggregate declarations are unsupported")
        if token == "{":
            depth += 1
        elif token == "}":
            depth -= 1
            if depth == 0:
                end = i
                break
        if depth < 0:
            break
    if end is None or end + 1 >= len(tokens) or tokens[end + 1][0] != ";":
        raise InputRefused("canonical declaration has extra text or an unbalanced class body")
    class_tokens = tokens[:end + 2]
    class_text = parsed[:class_tokens[-1][2]]
    checked, padding = _role_checked_syntax(class_text, name, contract)
    if _FORBIDDEN.search(checked) or re.search(r"\b__(?!int(?:8|16|32|64)\b)\w+", checked):
        raise InputRefused("canonical declaration has an unsupported scope, alias, intrinsic or type role")
    suffix = tokens[end + 2:]
    if padding and not suffix:
        raise InputRefused("canonical generated padding lacks its owning assertion suffix")
    if suffix:
        import header_adopt_lane as lane
        asserted = "\n".join(lane.size_assertions(contract, class_text))
        if tuple(t[0] for t in suffix) != tuple(t[0] for t in _tokens(asserted)):
            raise InputRefused("canonical trailing declarations are not the exact owning generator assertions")
    # Native layout admission below supports primitive/pointer storage only.
    # Ban declarator/type machinery whose interpretation this input model lacks.
    if any(t[0] in ("[", "]", "...", "::") for t in _tokens(checked)):
        raise InputRefused("canonical declaration has unsupported array, variadic or qualified syntax")
    words = {t[0] for t in tokens if re.fullmatch(r"[A-Za-z_][A-Za-z_0-9]*", t[0])}
    return class_text, tuple(t[0] for t in class_tokens), words, guard


def _normal_command(root, source, output):
    import build
    if Path(build.ROOT).resolve() != root:
        raise InputRefused("native command belongs to another checkout")
    return build.compiler_command(root / source, output)


def _command_fingerprint(command, env):
    import build
    return build._cmd_fingerprint(command, env)


def _preprocess(command, env):
    import census_receipts
    return census_receipts.capture_preprocessor(command, env)


def _opened_paths(source, output):
    import census_receipts
    return {Path(p).resolve() for p in census_receipts.opened_paths(source, output)}


def _marker_path(raw, root):
    import rename
    return rename._marker_path(raw, root)


def _line_directive(raw):
    import rename
    return rename.source_line_directive(raw)


def _expanded_tokens(output, root):
    """Tokens carry actual compiler-marker file and line provenance."""
    try:
        text = output.decode("ascii")
    except UnicodeError as exc:
        raise InputRefused("preprocessor output is not unambiguous ASCII") from exc
    file, line, out, marked = None, 0, [], False
    for physical in text.splitlines():
        marker = _MARKER.fullmatch(physical)
        if marker:
            file, line, marked = _marker_path(marker[2], root), int(marker[1]), True
            continue
        if physical.lstrip().startswith("#"):
            if re.match(r"\s*#\s*line\b", physical):
                raise InputRefused("malformed preprocessor provenance marker")
            # Pragmas outside the declaration can be emitted by normal headers.
            out.append(("#directive", file, line))
        else:
            out.extend((token, file, line) for token, _start, _end in _tokens(physical))
        line += 1
    if not marked:
        raise InputRefused("preprocessor omitted compiler line provenance")
    return out


def _bound_span(tokens, name, header, expected, opened):
    """At most one definition, with its entire token span at global header scope."""
    depth, definitions = 0, []
    index = 0
    while index < len(tokens):
        token = tokens[index][0]
        if (token in ("class", "struct") and index + 2 < len(tokens)
                and tokens[index + 1][0] == name and tokens[index + 2][0] == "{"):
            local, end = 1, index + 3
            while end < len(tokens) and local:
                local += (tokens[end][0] == "{") - (tokens[end][0] == "}")
                end += 1
            if local or end == len(tokens) or tokens[end][0] != ";":
                raise InputRefused("preprocessor class definition has no complete closing span")
            definitions.append((depth, tokens[index:end + 1]))
        depth += (token == "{") - (token == "}")
        if depth < 0:
            raise InputRefused("preprocessor scope cannot be proven")
        index += 1
    if depth:
        raise InputRefused("preprocessor has an incomplete global scope")
    target = header.lower()
    attributed = [span for scope, span in definitions if any(t[1] == target for t in span)]
    if not opened:
        if attributed:
            raise InputRefused("canonical marker names a header the compiler did not open")
        return False
    if len(definitions) != 1 or len(attributed) != 1:
        raise InputRefused("opened canonical header does not supply exactly one class definition (guard suppression or duplicate)")
    scope, span = definitions[0]
    if scope != 0 or any(t[1] != target for t in span):
        raise InputRefused("canonical class span has foreign file or nonglobal scope provenance")
    if tuple(t[0] for t in span) != expected:
        raise InputRefused("canonical raw class tokens differ from the preprocessor's actual class")
    if any(t[2] <= 0 for t in span) or any(a[2] > b[2] for a, b in zip(span, span[1:])):
        raise InputRefused("canonical class has invalid or backward line provenance")
    return True


def _macro_collisions(raw, words, guard=None):
    if re.search(rb"\b__(?:TIME|DATE|TIMESTAMP)__\b", re.sub(rb"\\\r?\n", b"", raw)):
        raise InputRefused("volatile predefined macro cannot bind a separate native/preprocessor invocation")
    logical = I._logical_text(raw).replace("%:", "#")
    names = re.findall(r"(?m)^[ \t]*#[ \t]*(?:define|undef)[ \t]+([A-Za-z_][A-Za-z_0-9]*)", logical)
    hits = sorted(set(names) & words)
    if hits:
        raise InputRefused("canonical tokens collide with a source/include macro: " + ", ".join(hits[:3]))


def _command_collisions(command, env, words, guard):
    if env.get("CL") or env.get("_CL_"):
        raise InputRefused("implicit compiler options have no canonical token proof")
    check = set(words) | ({guard} if guard else set())
    index = 0
    while index < len(command):
        token = command[index]
        if token.startswith(("-FI", "/FI", "-Yu", "/Yu", "-Yc", "/Yc", "@")):
            raise InputRefused("forced/PCH/response inputs need a broader canonical proof")
        if token.startswith(("-D", "/D", "-U", "/U")):
            arg = token[2:]
            if not arg:
                index += 1
                arg = command[index] if index < len(command) else ""
            name = re.split(r"[=#]", arg, maxsplit=1)[0]
            if not re.fullmatch(r"[A-Za-z_][A-Za-z_0-9]*", name) or name in check:
                raise InputRefused("command macro is ambiguous or collides with canonical tokens/guard")
        index += 1


def _object_evidence(data):
    import rename
    import header_adopt_lane as lane
    import class_layouts
    problem = rename.coff_layout_problem(data)
    if problem:
        raise InputRefused("native object is not whole COFF: " + problem)
    facts = lane.exclusive_definitions(data)
    stream = class_layouts.type_stream(data)
    layouts = {}
    if stream:
        if not class_layouts.REVERSED_GROUPS or len(stream) < 4:
            raise InputRefused("native type stream/virtual overload decoder is unavailable")
        pos = 4
        while pos < len(stream):
            if pos + 4 > len(stream):
                raise InputRefused("truncated CodeView record")
            length = struct.unpack_from("<H", stream, pos)[0]
            if length < 2 or pos + 2 + length > len(stream):
                raise InputRefused("invalid CodeView record extent")
            pos += 2 + length
        layouts = class_layouts.TypeStream(stream).classes()
    return (frozenset(facts[0]), frozenset(facts[1])), layouts


def _diagnostic_layouts(root, source):
    """Fresh source/profile diagnostic; its object never supplies ownership facts."""
    import class_layouts
    if Path(class_layouts.ROOT).resolve() != root:
        raise InputRefused("layout diagnostic belongs to another checkout")
    measured = class_layouts.compile_layouts(source, use_cache=False)
    stem = re.sub(r"[^\w.-]", "_", source)
    output = class_layouts.CACHE / (stem + ".obj")
    meta = class_layouts.CACHE / (stem + ".json")
    _facts, actual = _object_evidence(output.read_bytes())
    if measured != actual:
        raise InputRefused("diagnostic layout result differs from its actual fresh object")
    return actual, (output, meta)


def _layout(name, contract, record):
    import class_contract
    if (not isinstance(record, dict) or record.get("fwd") is not False or "unparsed" in record
            or record.get("bases") != [] or record.get("key") != contract.get("key")
            or type(record.get("size")) is not int or record["size"] != contract.get("size")
            or type(record.get("vfptr")) is not bool or not isinstance(record.get("fields"), list)
            or not isinstance(record.get("vslots"), dict)):
        raise InputRefused(f"{name}: no complete matching baseless native class record")
    allowed = set(class_contract.PRIMK.values()) | {"P", "VPTR"}
    wanted, got, expected_names, declared_types = set(), set(), set(), {}
    for entry in contract.get("fields", []):
        if (not isinstance(entry, dict) or entry.get("kind") not in allowed or entry.get("members")
                or type(entry.get("offset")) is not int or type(entry.get("size")) is not int
                or not isinstance(entry.get("name"), str) or entry["name"] in expected_names
                or entry["offset"] < 0 or entry["size"] <= 0
                or entry["offset"] + entry["size"] > contract["size"]):
            raise InputRefused("canonical layout proof supports only complete primitive/pointer fields")
        width = 4 if entry["kind"] in ("P", "VPTR") else int(entry["kind"][1:])
        if entry["size"] != width:
            raise InputRefused("canonical primitive/pointer extent is not its type width")
        expected_names.add(entry["name"])
        wanted.add((entry["offset"], entry["name"], entry["kind"], entry["size"]))
        if entry["kind"] != "VPTR":
            if not isinstance(entry.get("type"), str) or not entry["type"].strip():
                raise InputRefused("canonical storage lacks an explicit recorded field type")
            declared_types[entry["name"]] = re.sub(r"\s+", "", entry["type"])
    padding, seen_padding = _generator_padding(contract), set()
    if record["vfptr"]:
        got.add((0, "__vfptr", "VPTR", 4))
    regions = [(0, 4)] if record["vfptr"] else []
    names = set()
    for field in record["fields"]:
        if not isinstance(field, (list, tuple)) or len(field) != 4:
            raise InputRefused("native field record is incomplete")
        offset, member, type_name, size = field
        if isinstance(member, str) and member in padding:
            expected_offset, expected_size = padding[member]
            if (type(offset) is not int or type(size) is not int or member in names
                    or (offset, size) != (expected_offset, expected_size)
                    or type_name != f"char[{expected_size}]"):
                raise InputRefused("native generator padding offset/type/extent differs from contract")
            names.add(member)
            seen_padding.add(member)
            regions.append((offset, offset + size))
            continue
        kind = class_contract.kind(type_name) if isinstance(type_name, str) else None
        if (type(offset) is not int or type(size) is not int or size <= 0 or offset < 0
                or offset + size > record["size"] or not isinstance(member, str) or member in names
                or kind not in allowed - {"VPTR"}):
            raise InputRefused("native primitive/pointer field span is unsupported or ambiguous")
        names.add(member)
        if re.sub(r"\s+", "", type_name) != declared_types.get(member):
            raise InputRefused("native canonical field type differs from its explicit recorded declaration")
        got.add((offset, member, kind, size))
        regions.append((offset, offset + size))
    if seen_padding != set(padding):
        raise InputRefused("native generator padding is missing")
    regions.sort()
    if any(a[1] > b[0] for a, b in zip(regions, regions[1:])) or wanted != got:
        raise InputRefused("native canonical storage differs from contract")
    slots = {str(k): (v.get("member") if isinstance(v, dict) else v) for k, v in (contract.get("vslots") or {}).items()}
    if record["vslots"] != slots:
        raise InputRefused("native canonical virtual slots differ from contract")
    return record


@dataclass(frozen=True)
class Witness:
    source: str
    object_path: str
    object_digest: str
    facts: tuple[frozenset[str], frozenset[str]]
    emitting: bool
    layout: Mapping | None
    header_bound: bool


@dataclass(frozen=True)
class CanonicalInput:
    name: str
    header: str
    text: str
    digest: str
    witnesses: Mapping[str, Witness]
    files: Mapping[str, str]
    _snapshot: I.Snapshot = field(repr=False)
    rebuildable: frozenset[str] = field(default_factory=frozenset)

    def __post_init__(self):
        object.__setattr__(self, "witnesses", MappingProxyType(dict(self.witnesses)))
        object.__setattr__(self, "files", MappingProxyType(dict(self.files)))
        object.__setattr__(self, "rebuildable", frozenset(self.rebuildable))

    def validate(self):
        return self._snapshot.revalidate()

    @property
    def profiles(self):
        return MappingProxyType({source: state.fingerprint for source, (_path, state) in self._snapshot._compiler.items()})

    @property
    def forced_inputs(self):
        return MappingProxyType({source: state.forced for source, (_path, state) in self._snapshot._compiler.items()})

    @property
    def search_inventories(self):
        return MappingProxyType({source: state.inventory for source, (_path, state) in self._snapshot._compiler.items()})


def capture(name, header, contract, sources, root=ROOT):
    """Require a current real object for every source; refuse all unknown proof."""
    root, header = Path(root).resolve(), I._relative(header)
    tracked = I._tracked(root)
    if tracked.get(header) not in ("100644", "100755"):
        raise InputRefused("canonical header is not a tracked ordinary file")
    files, md5s, compiler, witnesses, rebuildable = {}, {}, {}, {}, set()

    def observe(path, retain=False):
        sha, md5, raw = I._hash(Path(path), retain=retain)
        key = I._key(root, Path(path))
        if key in files and files[key] != sha:
            raise InputRefused(f"native input changed during capture: {key}")
        files[key], md5s[key] = sha, md5
        return raw

    raw = observe(root / header, retain=True)
    text, expected, words, guard = _elide_header(raw, name, contract)
    units = tuple(sorted(set(sources)))
    if not units:
        raise InputRefused("canonical declaration has no actual source witnesses")
    inventory_cache = {}
    table = "??_7" + name + "@@6B"
    for source in units:
        source = I._relative(source)
        if tracked.get(source) not in ("100644", "100755") or not source.lower().endswith(I.H.SOURCE_SUFFIXES):
            raise InputRefused(f"native witness is not a real tracked C/C++ source: {source}")
        source_raw = observe(root / source, retain=True)
        receipt = I._receipt_path(root, source)
        try:
            meta = json.loads(observe(receipt, retain=True))
            if not isinstance(meta, dict) or meta.get("path") != source or not isinstance(meta.get("deps"), dict):
                raise InputRefused("receipt source/dependency binding is absent")
            output = receipt.with_name(receipt.name[:-len(".deps.json")] + ".obj")
            rebuildable.update((I._key(root, receipt), I._key(root, output)))
            object_raw = observe(output, retain=True)
            if meta.get("source") != md5s[source] or meta.get("object") != md5s[I._key(root, output)]:
                raise InputRefused("receipt does not bind the actual source and object bytes")
            state = I._compiler_inputs(root, source, output, inventory_cache)
            if not state.reusable:
                raise InputRefused("object is not strictly current for its compiler/profile/search inputs")
            command, env = _normal_command(root, source, output)
            if _command_fingerprint(command, env) != state.fingerprint:
                raise InputRefused("actual preprocessing command/profile differs from the current object command")
            _command_collisions(command, env, words, guard)
            compiler[source] = (str(output), state)
            deps = {}
            for path, digest in meta["deps"].items():
                if not isinstance(path, str) or not path or "\0" in path:
                    raise InputRefused("invalid native dependency path")
                host = Path(path) if Path(path).is_absolute() else root / path
                deps[host.resolve()] = observe(host, retain=True)
                if not isinstance(digest, str) or md5s[I._key(root, host)] != digest:
                    raise InputRefused("native receipt dependency bytes differ")
            # Receipts also bind compiler-profile executables/archives. Their
            # hashes matter, but only actual preprocessor-opened files are C++
            # text whose directives and macros can affect this declaration.
            if _line_directive(source_raw):
                raise InputRefused(f"user line provenance directive in {source}")
            _macro_collisions(source_raw, words, guard)
            pp = [arg for arg in command if not arg.startswith(("-Fo", "/Fo"))]
            if pp.count("-c") != 1:
                raise InputRefused("normal native command cannot be transformed exactly to -E")
            pp[pp.index("-c")] = "-E"
            done = _preprocess(pp + ["-showIncludes"], env)
            if done.returncode or not done.stdout:
                raise InputRefused("native preprocessor failed or returned empty output")
            import census_receipts
            if census_receipts._CLOCK_OUTPUT.search(done.stdout):
                raise InputRefused("volatile date/time preprocessor output cannot bind the actual object")
            opened = _opened_paths(root / source, done.stderr + b"\n" + done.stdout)
            if root / source not in opened:
                raise InputRefused("native preprocessor did not identify its source")
            for path in opened - {root / source}:
                if path not in deps:
                    raise InputRefused("preprocessor opened an input absent from the current object receipt")
                body = observe(path, retain=True)
                if _line_directive(body):
                    raise InputRefused("opened preprocessor input has forged line provenance")
                _macro_collisions(body, words, guard)
            bound = _bound_span(_expanded_tokens(done.stdout, root), name, header, expected,
                                (root / header).resolve() in opened)
            facts, layouts = _object_evidence(object_raw)
            emitting = any(symbol.startswith(table) for symbol in facts[1])
            record = layouts.get(name)
            diagnostic_paths = ()
            needs_layout = emitting or bound and not contract.get("vslots")
            if needs_layout and (record is None or record.get("fwd")):
                layouts, diagnostic_paths = _diagnostic_layouts(root, source)
                record = layouts.get(name)
                for path in diagnostic_paths:
                    observe(path)
                    rebuildable.add(I._key(root, path))
            if needs_layout and (record is None or record.get("fwd")):
                raise InputRefused("actual emitting/nonpolymorphic consumer has no complete bound class layout")
            if record is not None and not record.get("fwd"):
                if "unparsed" in record:
                    raise InputRefused("native class record is ambiguous or incompletely decoded")
                if bound:
                    _layout(name, contract, record)
            else:
                record = None
            witnesses[source] = Witness(source, str(output), files[I._key(root, output)], facts,
                                        emitting, _freeze(record) if record is not None else None, bound)
        except (Exception, SystemExit) as exc:
            raise InputRefused(f"{source}: canonical native proof refused: {exc}") from exc
    if not any(w.header_bound for w in witnesses.values()):
        raise InputRefused("no actual source binds the canonical declaration")
    if not any(w.header_bound and w.layout is not None for w in witnesses.values()):
        raise InputRefused("canonical declaration has no complete matching native layout witness")
    if contract.get("vslots") and not any(w.header_bound and w.emitting and w.layout is not None
                                          for w in witnesses.values()):
        raise InputRefused("canonical virtual declaration has no matching native emitting layout witness")
    snapshot = I.Snapshot(root, files, tuple(sorted(tracked)), compiler)
    snapshot.revalidate()
    return CanonicalInput(name, header, text, hashlib.sha256(raw).hexdigest(), witnesses, files, snapshot,
                          frozenset(rebuildable))


# Raw-owner witnesses grant no generator, object-provider or layout admission.
# Capture is an explicit frontdoor; readers below never start a preprocessor.
_OWNER_SEAL = object()


def _owner_mapping(name, mapping):
    import tu_views
    if not re.fullmatch(r"[A-Za-z_]\w*", name) or not isinstance(mapping, dict) or not mapping:
        raise InputRefused("raw owner needs one literal class and a nonempty field mapping")
    pairs = tuple(sorted(mapping.items()))
    if any(not isinstance(a, str) or not isinstance(b, str)
           or not re.fullmatch(r"[A-Za-z_]\w*", a) or not re.fullmatch(r"[A-Za-z_]\w*", b)
           or a == b or a in tu_views.KEYWORDS or b in tu_views.KEYWORDS for a, b in pairs) \
            or len({b for a, b in pairs}) != len(pairs) or set(mapping) & set(mapping.values()):
        raise InputRefused("raw owner mapping is ambiguous or not a field rename")
    return pairs


def _owner_read(path):
    path = Path(path).absolute()
    before = I._stamp(path.stat())
    digest, md5, raw = I._hash(path, retain=True)
    after = I._stamp(path.stat())
    if before != after:
        raise InputRefused(f"raw owner input changed while reading: {path}")
    return (str(path.resolve()), digest, tuple(after)), md5, raw


def _owner_profile(root, source, output):
    import build
    import header_adopt_lane as lane
    command, env = _normal_command(root, source, output)
    if not command or any(lane.unproven_pp_whitespace(arg) or "\n" in arg or "\r" in arg for arg in command):
        raise InputRefused("raw owner command has unsupported preprocessing whitespace")
    inventory = build.search_inventory(root / source, command, env)
    if inventory is None:
        raise InputRefused("raw owner compiler search inventory is unknown")
    return tuple(command), tuple(sorted(env.items())), inventory, env


def _owner_project_git(root):
    """RegisteredGeneration's HEAD and complete staged-index identity, read only."""
    import subprocess
    values = []
    for arguments in (("rev-parse", "HEAD"), ("ls-files", "--stage", "-z")):
        done = subprocess.run(["git", "-C", str(root), *arguments], capture_output=True)
        if done.returncode or not done.stdout:
            raise InputRefused("raw owner cannot freeze HEAD and the complete index")
        values.append(done.stdout)
    return tuple(values)


def _owner_policy_population(root):
    """Conservative authoritative input domains, not a metadata filename allowlist.

    This includes absence/new directories and untracked policy/module files.
    Only the build's existing generated-Python-cache rule is reused; a tracked
    file is never dropped by that rule. No verification metadata is an output.
    """
    import os
    import stat
    import build
    modes = I._tracked(root)
    domains = ("reverse", "baselines", "tools", ".githooks", ".github")
    for path in modes:
        prefix = path.split("/", 1)[0]
        if prefix not in domains and prefix.casefold() in domains:
            # Refuse this unsupported spelling; do NOT equate distinct POSIX
            # files or silently omit a native Windows case-equivalent control.
            raise InputRefused("raw owner indexed control domain spelling is noncanonical")
    # The index is an independent lower bound on the control population.
    # Root gitlinks are directories outside these domains, not root files.
    known = {p: mode for p, mode in modes.items()
             if p.split("/", 1)[0] in domains or ("/" not in p and mode != "160000")}
    if any(mode not in ("100644", "100755") for mode in known.values()):
        raise InputRefused("raw owner indexed control input is not an ordinary file")

    def kind(path, *, absent=False):
        try:
            mode = path.lstat().st_mode
        except FileNotFoundError as exc:
            if absent:
                return None
            raise InputRefused("raw owner listed/indexed control input is missing: " + str(path)) from exc
        except OSError as exc:
            raise InputRefused("raw owner cannot classify control input: " + str(path)) from exc
        if stat.S_ISREG(mode):
            return "file"
        if stat.S_ISDIR(mode):
            return "directory"
        raise InputRefused("raw owner control input is a symlink or unsupported type: " + str(path))

    def enumeration_error(exc):
        raise InputRefused("raw owner cannot completely enumerate control inputs: " + str(exc)) from exc

    population, files = [], set()
    try:
        roots = tuple(root.iterdir())
        listed = {path.name for path in roots}
        for path in roots:
            if kind(path) == "file":
                population.append((path.name, "file"))
                files.add(path)
        for name in domains:
            base = root / name
            required = name in listed or any(p == name or p.startswith(name + "/") for p in known)
            classification = kind(base, absent=not required)
            if classification is None:
                population.append((name, "absent"))
                continue
            if classification != "directory":
                raise InputRefused("raw owner control domain is not an ordinary directory")
            population.append((name, "directory"))
            for directory, subdirs, names in os.walk(base, onerror=enumeration_error, followlinks=False):
                directory = Path(directory)
                if kind(directory) != "directory":
                    raise InputRefused("raw owner enumerated control directory changed type")
                for child in list(subdirs):
                    path = directory / child
                    if kind(path) != "directory":
                        raise InputRefused("raw owner listed control subdirectory changed type")
                    relative = path.relative_to(root).as_posix()
                    if (name in {"tools", ".githooks"} and build._in_generated_dir((child,))
                            and not any(p.startswith(relative + "/") for p in modes)):
                        subdirs.remove(child)
                        continue
                    population.append((relative, "directory"))
                for filename in names:
                    path = directory / filename
                    if kind(path) != "file":
                        raise InputRefused("raw owner listed control file changed type")
                    population.append((path.relative_to(root).as_posix(), "file"))
                    files.add(path)
    except InputRefused:
        raise
    except Exception as exc:
        enumeration_error(exc)
    if not set(known) <= {p.relative_to(root).as_posix() for p in files}:
        raise InputRefused("raw owner population does not cover every indexed control input")
    return tuple(sorted(population)), tuple(sorted(files))


def _owner_policy_read(path):
    """Hash large ledgers as streams; never load/parse them wholesale."""
    try:
        before = I._stamp(path.stat())
        digest, _md5, _raw = I._hash(path)
        after = I._stamp(path.stat())
    except OSError as exc:
        raise InputRefused("raw owner cannot read a complete policy generation: " + str(path)) from exc
    if before != after:
        raise InputRefused("raw owner policy generation changed while reading")
    return str(path.resolve()), digest, tuple(after)


@dataclass(frozen=True)
class _OwnerProjectInputs:
    root: Path
    git: tuple
    population: tuple
    files: tuple

    def validate(self):
        if _owner_project_git(self.root) != self.git:
            raise InputRefused("raw owner HEAD or complete index changed")
        population, paths = _owner_policy_population(self.root)
        if population != self.population or tuple(str(p.resolve()) for p in paths) != tuple(p[0] for p in self.files):
            raise InputRefused("raw owner metadata/module/policy input population changed")
        for expected in self.files:
            if _owner_policy_read(Path(expected[0])) != expected:
                raise InputRefused("raw owner verification/ownership/policy input changed: " + expected[0])
        if _owner_project_git(self.root) != self.git:
            raise InputRefused("raw owner HEAD/index changed during policy validation")
        return True


def _capture_owner_project(root):
    before = _owner_project_git(root)
    population, paths = _owner_policy_population(root)
    observed = tuple(_owner_policy_read(path) for path in paths)
    result = _OwnerProjectInputs(root, before, population, observed)
    result.validate()
    return result


def _owner_spans(text, stream, name, source, declaration, declaration_source, words):
    """Every changed raw token belongs to a complete exact global declaration/member."""
    import header_adopt_lane as lane
    import tu_views
    code = lane.masked(text)
    span = lane.body_span(declaration, name)
    if span is None:
        raise InputRefused("raw owner class has no existing-reader declaration span")
    expected = tuple(t for t, a, b in _tokens(_comments(declaration[span[0]:span[1]])))
    _bound_span(stream, name, declaration_source, expected, True)
    depths, depth = [], 0
    for token, _file, _line in stream:
        depths.append(depth)
        depth += (token == "{") - (token == "}")
        if depth < 0:
            raise InputRefused("raw owner has an invalid expanded scope")
    if depth:
        raise InputRefused("raw owner has an incomplete expanded scope")
    classes = set(lane.class_layouts.class_bodies(text)) | {name}
    members = []
    for start, end, owner in lane.member_spans(code, sorted(classes)):
        head = text.rfind("\n", 0, start) + 1
        before = max(code.rfind(ch, 0, head) for ch in ";{}") + 1
        prefix = re.sub(r"(?m)^[ \t]*#[^\n]*", "", code[before:head])
        if prefix.strip():
            continue                         # no multi-line/omitted head inference
        members.append((head, end, owner))
    local_class = span if declaration_source == source else None
    raw_class = tu_views.no_comments(declaration[span[0]:span[1]])
    shape = lane.masked(raw_class)
    parsed = tu_views.members(raw_class[shape.index("{") + 1:shape.rindex("}")],
                              name, tu_views.file_typedefs(declaration))
    fields = {m.name for m in parsed if m.kind == "data"}
    used, total = set(), 0
    pattern = re.compile(r"\b(?:" + "|".join(re.escape(w) for w in sorted(words)) + r")\b")
    for found in pattern.finditer(code):
        total += 1
        if local_class and local_class[0] <= found.start() < local_class[1]:
            count = len(re.findall(r"\b" + re.escape(found[0]) + r"\b", code[span[0]:span[1]]))
            if count == 1 and found[0] in fields:
                continue
            raise InputRefused("raw owner has an inline or non-data class occurrence")
        owned = [m for m in members if m[0] <= found.start() < m[1]]
        if len(owned) != 1:
            raise InputRefused("raw owner changed token has no unique complete member scope")
        used.add(owned[0])
    if not total:
        raise InputRefused("raw owner mapping has no actual source occurrences")
    for start, end, owner in sorted(used):
        expected = [(t, text[:start + a].count("\n") + 1)
                    for t, a, b in _tokens(_comments(text[start:end]))]
        matches = []
        for index, (token, file, line) in enumerate(stream):
            if not expected or (token, line) != expected[0] or file != source.lower():
                continue
            part = stream[index:index + len(expected)]
            if len(part) == len(expected) and all(t == want and f == source.lower() and line == want_line
                 for (t, f, line), (want, want_line) in zip(part, expected)):
                matches.append(index)
        if len(matches) != 1 or depths[matches[0]] != 0:
            raise InputRefused("raw owner whole member tokens/file/lines/global scope are unproved")
        owner_text, owner_path = (declaration, declaration_source) if owner == name else (text, source)
        owner_span = lane.body_span(owner_text, owner)
        if owner_span is None:
            raise InputRefused("raw owner member has no complete declaring class")
        owner_tokens = tuple(t for t, a, b in _tokens(_comments(owner_text[owner_span[0]:owner_span[1]])))
        _bound_span(stream, owner, owner_path, owner_tokens, True)
    return total, tuple(sorted(used))


@dataclass(frozen=True)
class _OwnerState:
    root: Path
    identity: tuple
    files: tuple
    profiles: tuple
    tracked: tuple
    source_state: tuple
    coverage: tuple
    opened: tuple
    normal_deps: tuple
    project: _OwnerProjectInputs

    def anchor_paths(self):
        return {str(Path(self.source_state[1]).resolve()),
                str(I._receipt_path(self.root, self.source_state[0]).resolve())}

    def source_record(self):
        path = str((self.root / self.source_state[0]).resolve())
        return next(record for record in self.files if record[0] == path)

    def _validate_inputs(self, source_record=None):
        """Only a sealed owned transaction may supply its exact current source generation."""
        self.project.validate()
        source_path = self.source_record()[0]
        for expected in self.files:
            if expected[0] in self.anchor_paths():
                continue                     # anchors have a separate, exact output witness
            if expected[0] == source_path and source_record is not None:
                expected = source_record
            if _owner_read(expected[0])[0] != expected:
                raise InputRefused(f"raw owner input generation changed: {expected[0]}")
        modes = I._tracked(self.root)
        if any(modes.get(path) != mode for path, mode in self.tracked):
            raise InputRefused("raw owner tracked source/header mode changed")
        for source, output, command, env, inventory in self.profiles:
            now = _owner_profile(self.root, source, Path(output))
            if now[:3] != (command, env, inventory):
                raise InputRefused("raw owner command/profile/search inventory changed")
        return True

    def validate(self):
        self._validate_inputs()
        for expected in self.files:
            if expected[0] in self.anchor_paths() and _owner_read(expected[0])[0] != expected:
                raise InputRefused("raw owner original object/receipt anchor changed")
        source, output, expected = self.source_state
        if I._compiler_inputs(self.root, source, Path(output)) != expected:
            raise InputRefused("raw owner normal source/object receipt is no longer current")
        return True


@dataclass(frozen=True)
class CurrentOwnerWitness:
    name: str
    source: str
    header: str
    mapping: tuple
    _state: _OwnerState = field(repr=False)
    _seal: object = field(default=None, repr=False)

    def __post_init__(self):
        if self._seal is not _OWNER_SEAL or self._state.identity != (self.name, self.source, self.header, self.mapping):
            raise InputRefused("raw owner witness was not issued for this source/mapping")

    def validate(self):
        return self._state.validate()

    def plan_text(self):
        """Pure proposal only: no layout, gate, preprocessor or source write."""
        import os
        import header_adopt_lane as lane
        self.validate()
        text = (self._state.root / self.source).read_bytes().decode("latin-1")
        include = os.path.relpath(self._state.root / self.header,
                                 (self._state.root / self.source).parent).replace("\\", "/")
        swapped = lane.swap(text, [self.name], include)
        if swapped is None:
            raise InputRefused("raw owner class cannot be swapped by the normal reader")
        planned, why = lane.scoped_rename(swapped, {self.name: dict(self.mapping)})
        if why:
            raise InputRefused("raw owner scoped proposal refused: " + why)
        return planned


@dataclass(frozen=True)
class PairedOwnerWitness:
    current: CurrentOwnerWitness
    prospective: str
    _state: _OwnerState = field(repr=False)
    _seal: object = field(default=None, repr=False)

    def __post_init__(self):
        if (type(self.current) is not CurrentOwnerWitness or self._seal is not _OWNER_SEAL
                or self._state.identity != (self.current.name, self.current.source, self.current.header,
                                            self.current.mapping, self.prospective)):
            raise InputRefused("raw owner pair was not issued for these actual contexts")

    def validate_for(self, source, text, mappings, root, seeds):
        current = self.current
        if (Path(root).resolve() != current._state.root or source != current.source
                or mappings != {current.name: dict(current.mapping)} or tuple(seeds) != (current.header,)
                or text.encode("latin-1") != (current._state.root / source).read_bytes()):
            raise InputRefused("raw owner pair does not match this source/class/header/mapping")
        current.validate()
        self._state.validate()
        if (self._state.root / self.prospective).read_bytes() != current.plan_text().encode("latin-1"):
            raise InputRefused("raw owner prospective bytes no longer equal the pure proposal")
        return True


def _capture_owner_context(root, name, source, header, mapping, known, source_state, identity,
                           declaration_source, source_profile, normal_deps, project):
    import census_receipts
    import header_adopt_lane as lane
    command, env_keys, inventory, env = source_profile
    words = {name, *dict(mapping), *dict(mapping).values()}
    _command_collisions(command, env, words, None)
    if command.count("-c") != 1:
        raise InputRefused("raw owner normal command cannot be transformed exactly to -E")
    pp = [arg for arg in command if not arg.startswith(("-Fo", "/Fo"))]
    pp[pp.index("-c")] = "-E"
    pp.append("-showIncludes")
    outputs, corpus = [], []
    frozen = {Path(p).resolve(): record for p, record in known.items()}
    def revalidate():
        project.validate()
        for path, expected in frozen.items():
            if _owner_read(path)[0] != expected:
                raise InputRefused(f"raw owner input changed during capture: {path}")
        output = source_state[1] if source == source_state[0] else str(root / source) + ".command-only.obj"
        if _owner_profile(root, source, Path(output))[:3] != (command, env_keys, inventory):
            raise InputRefused("raw owner profile/search inputs changed during capture")
        if I._compiler_inputs(root, source_state[0], Path(source_state[1])) != source_state[2]:
            raise InputRefused("raw owner current normal object lost currency during capture")
    for _ in range(2):
        revalidate()
        done = _preprocess(pp, env)        # explicit frontdoor only, never called by a reader
        if done.returncode or not done.stdout or census_receipts._CLOCK_OUTPUT.search(done.stdout):
            raise InputRefused("raw owner native preprocessor failed or produced volatile output")
        opened = _opened_paths(root / source, done.stderr + b"\n" + done.stdout)
        if (root / source).resolve() not in opened or not opened <= set(frozen):
            raise InputRefused("raw owner native opened input was absent from the prebound inputs")
        if (root / declaration_source).resolve() not in opened:
            raise InputRefused("raw owner declaring source/header was not actually opened")
        if len(opened) == 1 and re.search(r"(?m)^\s*#\s*include\b", (root / source).read_text(encoding="latin-1")):
            raise InputRefused("raw owner native actual include trace is missing")
        current_corpus = []
        for path in sorted(opened):
            _record, _md5, raw = _owner_read(path)
            if _line_directive(raw) or lane.unproven_pp_whitespace(raw.decode("latin-1")):
                raise InputRefused("raw owner opened input has forged line/unsupported whitespace provenance")
            if census_receipts._VOLATILE.search(re.sub(rb"\\\r?\n", b"", raw)):
                raise InputRefused("raw owner opened input has a volatile predefined macro")
            current_corpus.append((str(path), raw.decode("latin-1")))
        outputs.append((done.stdout, done.stderr, tuple(sorted(map(str, opened)))))
        corpus = current_corpus
        revalidate()
    if outputs[0] != outputs[1]:
        raise InputRefused("raw owner repeated native output/include inputs differ")
    text = (root / source).read_bytes().decode("latin-1")
    macros, why = lane.storage_command_macros(source, command)
    if why:
        raise InputRefused(why)
    corpus += [(source + ".compiler-macros", macros)]
    why = lane.name_shadow(corpus, name) or lane.macro_shadow(corpus, {name: dict(mapping)}, text)
    if why:
        raise InputRefused("raw owner name/macro ownership: " + why)
    declaration = (root / declaration_source).read_bytes().decode("latin-1")
    stream = _expanded_tokens(outputs[0][0], root)
    changed = set(dict(mapping)) if declaration_source == source else set(dict(mapping).values())
    coverage = _owner_spans(text, stream, name, source, declaration, declaration_source, changed)
    if declaration_source == source:
        import tu_views
        span = lane.body_span(text, name)
        outside = text[:span[0]] + re.sub(r"[^\r\n]", " ", text[span[0]:span[1]]) + text[span[1]:]
        scoped, why = lane.scoped_rename(outside, {name: dict(mapping)})
        if why or scoped != tu_views.rename(outside, dict(mapping)):
            raise InputRefused("raw owner scoped rename does not equal all changed tokens")
    tracked = I._tracked(root)
    required = (source_state[0], header)
    if any(tracked.get(p) not in ("100644", "100755") for p in required):
        raise InputRefused("raw owner source/header is not a tracked ordinary file")
    output = source_state[1] if source == source_state[0] else str(root / source) + ".command-only.obj"
    state = _OwnerState(root, identity, tuple(sorted(frozen.values())),
             ((source, output, command, env_keys, inventory),),
             tuple((p, tracked[p]) for p in required), source_state, coverage,
             outputs[0][2], normal_deps, project)
    state.validate()
    return state


def capture_owner_current(name, source, header, mapping, root=ROOT):
    """Explicit two-PP current owner capture; it grants pure planning only."""
    import build
    import sys
    import header_adopt_lane as lane
    import tu_views
    root = Path(root).resolve()
    source, header = I._relative(source), I._relative(header)
    mapping = _owner_mapping(name, mapping)
    if not source.endswith(".cpp"):
        raise InputRefused("raw owner needs an ordinary C++ source")
    modes = I._tracked(root)
    if any(modes.get(p) not in ("100644", "100755") for p in (source, header)):
        raise InputRefused("raw owner source/header is not a tracked ordinary file")
    project = _capture_owner_project(root)
    receipt = I._receipt_path(root, source)
    output = receipt.with_name(receipt.name[:-len(".deps.json")] + ".obj")
    files = {}
    def observe(path):
        record, md5, raw = _owner_read(path)
        if record[0] in files and files[record[0]] != record:
            raise InputRefused("raw owner input changed before capture")
        files[record[0]] = record
        return md5, raw
    source_md5, source_raw = observe(root / source)
    observe(root / header)
    _md5, raw = observe(receipt)
    meta = json.loads(raw)
    object_md5, _raw = observe(output)
    state = I._compiler_inputs(root, source, output)
    if (not state.reusable or state.inventory is None or state.forced
            or meta.get("path") != source or meta.get("source") != source_md5
            or meta.get("object") != object_md5 or not isinstance(meta.get("deps"), dict)):
        raise InputRefused("raw owner needs a strictly current bound normal source/object receipt")
    for path, digest in meta["deps"].items():
        if observe(Path(path) if Path(path).is_absolute() else root / path)[0] != digest:
            raise InputRefused("raw owner normal dependency bytes differ")
    profile = _owner_profile(root, source, output)
    if _command_fingerprint(profile[0], profile[3]) != state.fingerprint:
        raise InputRefused("raw owner actual normal command differs from its object receipt")
    observe(Path(profile[0][0]))
    for module in (sys.modules[__name__], I, lane, tu_views, build, lane.class_layouts):
        observe(Path(module.__file__))
    if any(re.search(r"\b" + re.escape(new) + r"\b", lane.masked(source_raw.decode("latin-1"))) for old, new in mapping):
        raise InputRefused("raw owner destination already occurs in the source")
    identity = (name, source, header, mapping)
    result = _capture_owner_context(root, name, source, header, mapping, files,
        (source, str(output), state), identity, source, profile,
        tuple(sorted(str((Path(p) if Path(p).is_absolute() else root / p).resolve()) for p in meta['deps'])), project)
    return CurrentOwnerWitness(name, source, header, mapping, result, _OWNER_SEAL)


def capture_owner_pair(current, prospective):
    """Explicit two further PP calls of a real adjacent prospective source; no writes."""
    if type(current) is not CurrentOwnerWitness:
        raise InputRefused("raw owner pair needs a real current owner witness")
    current.validate()
    prospective = I._relative(prospective)
    root = current._state.root
    if (Path(prospective).parent != Path(current.source).parent or prospective == current.source
            or not prospective.endswith(".cpp")):
        raise InputRefused("raw owner prospective source must be a different real adjacent C++ file")
    record, _md5, raw = _owner_read(root / prospective)
    if raw != current.plan_text().encode("latin-1"):
        raise InputRefused("raw owner prospective source differs from the exact pure proposal")
    profile = _owner_profile(root, prospective, Path(str(root / prospective) + ".command-only.obj"))
    original = current._state.profiles[0]
    def normalized(command, source):
        return tuple(a for a in command if not a.startswith(("-Fo", "/Fo")) and a != source)
    if (normalized(profile[0], prospective) != normalized(original[2], current.source)
            or profile[1:3] != original[3:5]):
        raise InputRefused("raw owner prospective ordinary profile/search inventory differs")
    files = {p: value for value in current._state.files for p in (value[0],)}
    files[record[0]] = record
    identity = (current.name, current.source, current.header, current.mapping, prospective)
    state = _capture_owner_context(root, current.name, prospective, current.header, current.mapping,
        files, current._state.source_state, identity, current.header, profile,
        current._state.normal_deps, current._state.project)
    current.validate()
    return PairedOwnerWitness(current, prospective, state, _OWNER_SEAL)


def _owner_pair_inputs(pair, source_record, expected_source):
    if type(pair) is not PairedOwnerWitness:
        raise InputRefused("owned trial needs an issued paired owner witness")
    original = pair.current._state.source_record()
    if source_record[0] != original[0] or source_record[1] != hashlib.sha256(expected_source).hexdigest():
        raise InputRefused("owned source transition is not the exact original/candidate image")
    pair.current._state._validate_inputs(source_record)
    pair._state._validate_inputs(source_record)


def _owner_output_records(pair):
    return tuple(_owner_read(path)[0] for path in sorted(pair.current._state.anchor_paths()))


def _owner_written_record(writes, path, candidate):
    generation = writes.generations.get(path)
    if generation is None:
        raise InputRefused("owned source write has no pre-replacement generation")
    return str(path.resolve()), hashlib.sha256(candidate).hexdigest(), generation


def _owner_restore(writes, path, original_record):
    # The writer already knows its exact generation BEFORE replacement. Never
    # substitute a byte-only cleanup when a subsequent ownership read failed.
    actual = _owner_read(path)[0]
    if actual == original_record:
        return actual
    if actual != _owner_written_record(writes, path, writes.written.get(path, b"")):
        raise InputRefused("foreign source generation preserved; no owner output token")
    writes.restore()
    restored = _owner_written_record(writes, path, writes.before[path])
    if _owner_read(path)[0] != restored:
        raise InputRefused("foreign generation after owned restoration; no owner output token")
    return restored


def _owner_candidate_cache(pair, source_record, candidate):
    """Require the ordinary strict current check while the real candidate is on disk."""
    _owner_pair_inputs(pair, source_record, candidate)
    anchors = _owner_output_records(pair)
    state = pair.current._state
    source, output, expected = state.source_state
    # This existing API calls normal build.compile_is_current(..., strict=True).
    current = I._compiler_inputs(state.root, source, Path(output))
    if not current.reusable or current != expected:
        raise InputRefused("owned byte gate did not leave an ordinary strictly current candidate object")
    receipt = I._receipt_path(state.root, source)
    _record, _md5, raw = _owner_read(receipt)
    meta = json.loads(raw)
    object_md5 = _owner_read(output)[1]
    if (not isinstance(meta, dict) or meta.get("version") != 2 or meta.get("path") != source
            or meta.get("source") != hashlib.md5(candidate).hexdigest()
            or meta.get("object") != object_md5 or meta.get("cmd") != expected.fingerprint
            or not isinstance(meta.get("deps"), dict)):
        raise InputRefused("owned gate receipt does not bind the actual source/object/profile")
    profile_only = {p.casefold() for p in state.normal_deps} - {p.casefold() for p in state.opened}
    needed = ({p.casefold() for p in pair._state.opened}
              - {str((state.root / pair.prospective).resolve()).casefold()}) | profile_only
    actual = set()
    for path, digest in meta["deps"].items():
        record, md5, _raw = _owner_read(Path(path) if Path(path).is_absolute() else state.root / path)
        if digest != md5:
            raise InputRefused("owned gate dependency digest differs from its actual input")
        actual.add(record[0].casefold())
    if actual != needed:
        raise InputRefused("owned gate receipt does not cover exactly the native prospective inputs")
    _owner_pair_inputs(pair, source_record, candidate)
    if _owner_output_records(pair) != anchors:
        raise InputRefused("owned gate object/receipt changed during strict output validation")
    return anchors


@dataclass(frozen=True)
class OwnerGateOutputWitness:
    pair: PairedOwnerWitness
    outputs: tuple
    restored_source: tuple
    candidate: bytes = field(repr=False)
    _seal: object = field(default=None, repr=False)

    def __post_init__(self):
        prospective_path = str((self.pair._state.root / self.pair.prospective).resolve()) \
            if type(self.pair) is PairedOwnerWitness else ""
        expected_candidate = next((r[1] for r in self.pair._state.files if r[0] == prospective_path), None) \
            if type(self.pair) is PairedOwnerWitness else None
        if (self._seal is not _OWNER_SEAL or type(self.pair) is not PairedOwnerWitness
                or len(self.outputs) != 2
                or {record[0] for record in self.outputs} != self.pair.current._state.anchor_paths()
                or self.restored_source[:2] != self.pair.current._state.source_record()[:2]
                or hashlib.sha256(self.candidate).hexdigest() != expected_candidate):
            raise InputRefused("owned gate output was not issued for these two anchors and restored source")

    def _before_apply(self):
        original = (self.pair.current._state.root / self.pair.current.source).read_bytes()
        _owner_pair_inputs(self.pair, self.restored_source, original)
        if self.restored_source[1] != self.pair.current._state.source_record()[1]:
            raise InputRefused("owned gate source is no longer the original image")
        if _owner_output_records(self.pair) != self.outputs:
            raise InputRefused("owned gate object/receipt changed after PASS")

    def apply(self):
        """CAS the exact gate-verified candidate; no compiler/preprocessor or ledger write."""
        import header_adopt_lane as lane
        self._before_apply()
        path = self.pair.current._state.root / self.pair.current.source
        original = path.read_bytes()
        writes = lane.GenerationWrites({path: self.restored_source[1]},
                                      owned_generations={path: self.restored_source[2]})
        if _owner_read(path)[0] != self.restored_source:
            raise InputRefused("foreign source generation changed before final apply")
        success = False
        try:
            writes.write(path, self.candidate)
            owned = _owner_written_record(writes, path, self.candidate)
            if _owner_read(path)[0] != owned:
                raise InputRefused("foreign source generation changed after final write")
            if _owner_candidate_cache(self.pair, owned, self.candidate) != self.outputs:
                raise InputRefused("owned gate outputs changed during final apply")
            success = True
            return True
        finally:
            if not success:
                _owner_restore(writes, path, self.restored_source)


def verify_owner_trial(pair):
    """One explicit ordinary source byte-gate transaction; never a capture reader."""
    import header_adopt_lane as lane
    if type(pair) is not PairedOwnerWitness:
        raise InputRefused("owned trial requires the paired stage, never a current-only proof")
    current = pair.current
    path = current._state.root / current.source
    original = path.read_bytes()
    pair.validate_for(current.source, original.decode("latin-1"),
                      {current.name: dict(current.mapping)}, current._state.root, (current.header,))
    candidate = current.plan_text().encode("latin-1")
    before = _owner_read(path)[0]
    if before != current._state.source_record():
        raise InputRefused("foreign source generation changed before owned trial")
    writes = lane.GenerationWrites({path: before[1]}, owned_generations={path: before[2]})
    owned, outputs = None, None
    try:
        writes.write(path, candidate)
        owned = _owner_written_record(writes, path, candidate)
        if _owner_read(path)[0] != owned:
            raise InputRefused("foreign source generation changed after trial write")
        _owner_pair_inputs(pair, owned, candidate)
        verdict = lane.gate_many([current.source])       # unchanged normal byte gate
        if not isinstance(verdict, dict) or verdict.get(current.source, "missing byte verdict") is not None:
            raise InputRefused("owned ordinary byte gate did not PASS")
        outputs = _owner_candidate_cache(pair, owned, candidate)
    finally:
        restored_record = _owner_restore(writes, path, before)
    restored = _owner_read(path)[0]
    if restored != restored_record:
        raise InputRefused("foreign source generation changed after trial restoration")
    _owner_pair_inputs(pair, restored, original)
    if outputs is None or _owner_output_records(pair) != outputs:
        raise InputRefused("owned gate object/receipt changed before trial restoration completed")
    return OwnerGateOutputWitness(pair, outputs, restored, candidate, _OWNER_SEAL)
