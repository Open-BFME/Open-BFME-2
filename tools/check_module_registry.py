#!/usr/bin/env python3
"""Check recovered module-factory names against retail registrations.

Requires GNU objdump or Capstone for x86 instruction boundaries.
Use --check for the gate; --write-baseline may only shrink existing debt.
"""
import argparse
import bisect
import csv
import os
import re
import shutil
import struct
import subprocess
import sys
import tempfile
from typing import NamedTuple
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build  # noqa: E402

ROOT = build.ROOT
ALLOWLIST = ROOT / "reverse" / "module_registry_allowlist.txt"
BASELINE = ROOT / "reverse" / "module_registry_baseline.txt"
IMAGE_BASE = 0x400000
# ModuleFactory::addModuleInternal in the target image.
ADD_MODULE_RVA = 0x002573EE
EXPECTED_REGISTRATIONS = 329

DATA_RE = re.compile(r"\?friend_newModuleData@([A-Za-z0-9_]+)@@")
INST_RE = re.compile(r"\?friend_newModuleInstance@([A-Za-z0-9_]+)@@")
CTOR_RE = re.compile(r"\?\?0([A-Za-z0-9_]+)@@QAE@XZ$")
PROC_RE = re.compile(r"\?buildFieldParse@([A-Za-z0-9_]+)@@")
INSTRUCTION_RE = re.compile(
    r"^\s*([0-9a-f]+):\s*((?:[0-9a-f]{2}\s+)+)\s*([a-z][a-z0-9.]*)\s*(.*?)\s*$",
    re.IGNORECASE,
)
IMMEDIATE_RE = re.compile(r"^0x([0-9a-f]+)(?:\s+<[^>]+>)?$", re.IGNORECASE)


class Instruction(NamedTuple):
    address: int
    size: int
    mnemonic: str
    operands: str


def parse_objdump_output(output):
    """Parse instruction rows from objdump's raw i386 disassembly."""
    instructions = []
    for line in output.splitlines():
        match = INSTRUCTION_RE.match(line)
        if match:
            raw = bytes.fromhex(match.group(2))
            instructions.append(Instruction(
                int(match.group(1), 16), len(raw), match.group(3).lower(),
                match.group(4).strip(),
            ))
    return instructions


def immediate_operand(instruction):
    """Return a direct hexadecimal operand, or None for register/memory ops."""
    match = IMMEDIATE_RE.fullmatch(instruction.operands.strip())
    return int(match.group(1), 16) if match else None


def validate_instructions(instructions, start, size):
    end = start + size
    for instruction in instructions:
        if (instruction.address != start or instruction.size <= 0
                or instruction.mnemonic in ("bad", ".byte")):
            raise ValueError(f"incomplete disassembly at 0x{start:08X}")
        start += instruction.size
    if start != end:
        raise ValueError(f"incomplete disassembly at 0x{start:08X}")


def direct_call_target(instruction):
    return immediate_operand(instruction) if instruction.mnemonic == "call" else None


def data_class(module):
    """The conventional data-class name for a module."""
    return module + ("Data" if module.endswith("Module") else "ModuleData")


def module_of(token):
    """Strip a data-class suffix back to the module name it stands for."""
    if token.endswith("ModuleData"):
        return token[: -len("ModuleData")]
    return token


def names_module(token, modules):
    """True when a class token spells one of the registered modules."""
    return token in modules or module_of(token) in modules or any(
        token == data_class(m) for m in modules)


class Image:
    def __init__(self):
        self.data, self.sections = build.exe_image()
        text = next(s for s in self.sections if s["name"] == ".text")
        self.text_rva = text["rva"]
        self.text = self.data[text["raw_pointer"]: text["raw_pointer"] + text["raw_size"]]
        with build.GHIDRA_FUNCTIONS.open("r", encoding="utf-8", newline="") as handle:
            self.function_sizes = {
                int(row["rva"], 16): int(row["size"])
                for row in csv.DictReader(handle)
            }
        # Some verified factories were recovered outside Ghidra's function list.
        for row in build.load_all_function_rows():
            if row["status"] == "matched":
                self.function_sizes.setdefault(int(row["target_rva"], 16), int(row["target_size"]))
        self.function_starts = sorted(self.function_sizes)
        self.disassembly = {}

    def text_at(self, rva, size):
        off = rva - self.text_rva
        if off < 0 or off + size > len(self.text):
            raise ValueError(f"0x{rva:08X}+{size} is outside .text")
        return self.text[off: off + size]

    def string(self, va):
        rva = va - IMAGE_BASE
        try:
            off = build.rva_to_file_offset(self.sections, rva)
        except ValueError:
            return None
        raw = self.data[off: off + 64].split(b"\0")[0]
        if len(raw) < 3 or not all(32 < c < 127 for c in raw):
            return None
        return raw.decode()

    def is_code(self, va):
        return self.text_rva <= va - IMAGE_BASE < self.text_rva + len(self.text)

    def candidate_callers(self, target):
        """Return raw E8 matches; callers must confirm them by disassembly."""
        out = []
        t = self.text
        for i in range(len(t) - 4):
            if t[i] == 0xE8 and self.text_rva + i + 5 + struct.unpack_from("<i", t, i + 1)[0] == target:
                out.append(self.text_rva + i)
        return out

    def function_containing(self, rva):
        index = bisect.bisect_right(self.function_starts, rva) - 1
        while index >= 0:
            start = self.function_starts[index]
            size = self.function_sizes[start]
            if start <= rva < start + size:
                return start, size
            index -= 1
        return None

    def instructions(self, start):
        if start in self.disassembly:
            return self.disassembly[start]
        size = self.function_sizes.get(start)
        if size is None:
            raise ValueError(f"no function boundary at 0x{start:08X}")
        data = self.text_at(start, size)
        objdump = shutil.which("objdump")
        if objdump:
            fd, path = tempfile.mkstemp(prefix="bfme-module-registry-")
            try:
                with os.fdopen(fd, "wb") as handle:
                    handle.write(data)
                result = subprocess.run(
                    [objdump, "-D", "-b", "binary", "-m", "i386", "-M", "intel",
                     "--insn-width=16", "--disassemble-zeroes",
                     f"--adjust-vma=0x{start + IMAGE_BASE:X}", path],
                    capture_output=True, text=True, check=True,
                )
                decoded = parse_objdump_output(result.stdout)
            finally:
                os.unlink(path)
        else:
            try:
                import capstone
            except ImportError as exc:
                raise SystemExit("Module registry: install GNU objdump or Capstone") from exc
            decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
            decoded = [Instruction(insn.address, insn.size, insn.mnemonic.lower(), insn.op_str)
                       for insn in decoder.disasm(data, start + IMAGE_BASE)]
        validate_instructions(decoded, start + IMAGE_BASE, size)
        self.disassembly[start] = decoded
        return decoded


def decode_registrations(img):
    """[(module, data_factory_rva, instance_factory_rva)] from every addModule call."""
    functions = {}
    for site in img.candidate_callers(ADD_MODULE_RVA):
        bounds = img.function_containing(site)
        if bounds:
            functions.setdefault(bounds[0], set()).add(site)
    regs = []
    for start, sites in sorted(functions.items()):
        instructions = img.instructions(start)
        for index, instruction in enumerate(instructions):
            site = instruction.address - IMAGE_BASE
            if (site not in sites
                    or direct_call_target(instruction) != ADD_MODULE_RVA + IMAGE_BASE):
                continue
            # Retail pushes the name, then the two factories, within 70 bytes.
            pushes = [immediate_operand(ins) for ins in instructions[:index]
                      if ins.address >= instruction.address - 70 and ins.mnemonic == "push"]
            pushes = [value for value in pushes if value is not None]
            names = [s for s in (img.string(v) for v in pushes) if s]
            code = [v - IMAGE_BASE for v in pushes if img.is_code(v)]
            if not names or len(code) < 2:
                raise SystemExit(f"Module registry: unrecognized registration at 0x{site:08X}")
            regs.append((names[-1], code[-2], code[-1]))
    if len(regs) != EXPECTED_REGISTRATIONS:
        raise SystemExit(f"Module registry: decoded {len(regs)} registrations at "
                         f"0x{ADD_MODULE_RVA:08X}; the decoder no longer fits retail")
    return regs


def factory_callees(img, factory, skip):
    """(first call target not in skip, first code-pointer push) of a data factory."""
    call = proc = None
    for instruction in img.instructions(factory):
        if instruction.mnemonic in ("ret", "retf", "iret", "iretd"):
            break
        value = immediate_operand(instruction)
        if instruction.mnemonic == "push" and value is not None:
            if proc is None and img.is_code(value):
                proc = value - IMAGE_BASE
        target = direct_call_target(instruction)
        if target is not None and call is None and target - IMAGE_BASE not in skip:
            call = target - IMAGE_BASE
    return call, proc


def load_names():
    """rva -> [names] from matched rows and pins."""
    names = {}
    with open(ROOT / "reverse" / "functions.csv", newline="") as f:
        for row in csv.DictReader(f):
            if row["status"] == "matched":
                names.setdefault(int(row["target_rva"], 16), []).append(row["name"])
    with open(ROOT / "reverse" / "symbols.csv", newline="") as f:
        for row in csv.DictReader(f):
            try:
                names.setdefault(int(row["address"], 16), []).append(row["name"])
            except ValueError:
                pass
    return names


def read_keys(path):
    """Set of 'kind rva name' keys; '#' comments and anything after ' #' ignored."""
    if not path.exists():
        return set()
    keys = set()
    for line in path.read_text().splitlines():
        line = line.split(" #", 1)[0].strip()
        if line and not line.startswith("#"):
            keys.add(line)
    return keys


def scan():
    img = Image()
    regs = decode_registrations(img)
    names = load_names()
    skip = {rva for rva, ns in names.items()
            if any(n in ("__EH_prolog", "??2@YAPAXI@Z") for n in ns)}
    by_data, by_inst = {}, {}
    for module, dfac, ifac in regs:
        by_data.setdefault(dfac, set()).add(module)
        by_inst.setdefault(ifac, set()).add(module)

    # A trivial data ctor can be folded across classes, so a ctor/proc address
    # may legitimately carry the class of every factory that calls it.
    callee_classes = {}
    for dfac, modules in by_data.items():
        rows = [n for n in names.get(dfac, []) if DATA_RE.match(n)]
        if not rows:
            continue
        tokens = {DATA_RE.match(row).group(1) for row in rows}
        tokens = {token for token in tokens if names_module(token, modules)}
        call, proc = factory_callees(img, dfac, skip)
        for addr in (call, proc):
            if addr is not None:
                callee_classes.setdefault(addr, set()).update(tokens)

    violations = []
    for dfac, modules in sorted(by_data.items()):
        rows = [n for n in names.get(dfac, []) if DATA_RE.match(n)]
        for name in rows:
            token = DATA_RE.match(name).group(1)
            if not names_module(token, modules):
                violations.append(("data", dfac, name, sorted(modules)))
                continue
            call, proc = factory_callees(img, dfac, skip)
            for addr, regex, kind in ((call, CTOR_RE, "ctor"), (proc, PROC_RE, "proc")):
                for other in names.get(addr, []) if addr is not None else []:
                    m = regex.match(other)
                    allowed = {module_of(t) for t in callee_classes.get(addr, {token})}
                    if m and module_of(m.group(1)) not in allowed:
                        violations.append((kind, addr, other, [token]))
    for ifac, modules in sorted(by_inst.items()):
        for name in names.get(ifac, []):
            m = INST_RE.match(name)
            if m and m.group(1) not in modules:
                violations.append(("instance", ifac, name, sorted(modules)))
    return violations, len(regs)


def key(v):
    return f"{v[0]} 0x{v[1]:08X} {v[2]}"


def verify(allowlist=ALLOWLIST, baseline=BASELINE):
    """Gate entry point: prints a verdict, raises SystemExit on failure."""
    violations, count = scan()
    allowed = read_keys(allowlist)
    known = read_keys(baseline)
    live = [v for v in violations if key(v) not in allowed]
    new = [v for v in live if key(v) not in known]
    current = {key(v) for v in live}
    stale = sorted(k for k in known if k not in current)
    if new:
        print(f"Module registry: FAIL {len(new)} factory/ctor/proc row(s) disagree with "
              "ModuleFactory's registration")
        for v in new[:12]:
            print(f"    {key(v)}  (registered: {', '.join(v[3])})")
        print("    Rename the row to the registered module. Do NOT add it to "
              f"{BASELINE.relative_to(ROOT)} to get green.")
        raise SystemExit(1)
    if stale:
        print(f"Module registry: FAIL {len(stale)} baseline line(s) no longer describe a "
              "violation -- delete them in the commit that fixed the row")
        for k in stale[:12]:
            print(f"    {k}")
        raise SystemExit(1)
    print(f"Module registry: OK ({count} registrations; {len(allowed)} allowlisted, "
          f"{len(live)} baselined, 0 new, 0 stale)")


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--check", action="store_true", help="gate mode")
    parser.add_argument("--write-baseline", action="store_true",
                        help="rewrite the baseline; refused if it would grow")
    args = parser.parse_args(argv)
    if args.check:
        verify()
        return
    violations, count = scan()
    allowed = read_keys(ALLOWLIST)
    live = [v for v in violations if key(v) not in allowed]
    if args.write_baseline:
        known = read_keys(BASELINE)
        grown = [key(v) for v in live if key(v) not in known]
        if BASELINE.exists() and grown:
            raise SystemExit(f"refusing to grow {BASELINE.name}: {len(grown)} new line(s)")
        lines = ["# Known module-registry violations still to fix. May only shrink.",
                 "# Generated by tools/check_module_registry.py --write-baseline."]
        lines += sorted(key(v) for v in live)
        BASELINE.write_text("\n".join(lines) + "\n")
        print(f"wrote {len(live)} line(s) to {BASELINE.relative_to(ROOT)}")
        return
    for v in violations:
        tag = "allowlisted" if key(v) in allowed else "violation"
        print(f"{tag:<12} {key(v)}  (registered: {', '.join(v[3])})")
    print(f"{count} registrations, {len(live)} violation(s), "
          f"{len(violations) - len(live)} allowlisted")


if __name__ == "__main__":
    main()
