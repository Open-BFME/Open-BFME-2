"""Same-named COFF copies must retain their bytes AND relocation evidence."""
import argparse
import collections
import contextlib
import csv
import io
import struct
import sys
import tempfile
import types
import unittest
from pathlib import Path
from unittest import mock

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import obj_sweep as S

SOURCE = "Code/Variant.cpp"
NAME = "?body@@YAXXZ"
GLOBAL = "?global@@3HA"
RVA, TARGET = 0x1000, 0x2000
BASE = 0x800000
PREFIX = bytes.fromhex("558bec33c040405dc3")
TAIL = bytes.fromhex("0102030405060708")


class Image:
    def __init__(self, bodies):
        self.bodies = bodies

    def body(self, rva, size):
        for start, body in self.bodies.items():
            if start <= rva and rva + size <= start + len(body):
                return body[rva - start:rva - start + size]
        raise AssertionError(f"outside fixture: {rva:x}+{size}")


def row(size=len(PREFIX), name=NAME):
    return dict(name=name, rva=RVA, size=size, source=SOURCE, notes="", lane="authored")


def universe(held, dump=()):
    return types.SimpleNamespace(
        dump=set(dump), unclaimed={}, naked_symbols=set(), symbol_addresses={},
        held_rows={SOURCE: held}, rows={(RVA, r["size"]): [r] for r in held},
        text_end=0x3000, overlaps_matched=lambda rva, size: False)


class ObjectVariants(unittest.TestCase):
    def test_later_byte_and_relocation_variants_survive(self):
        copies = [(NAME, PREFIX, []), (NAME, PREFIX + TAIL, []),
                  (NAME, PREFIX, [(1, S.DIR32, GLOBAL)]),
                  (NAME, PREFIX, [(2, S.DIR32, GLOBAL)]),
                  (NAME, PREFIX, [(1, S.REL32, GLOBAL)]),
                  (NAME, PREFIX, [(1, S.DIR32, GLOBAL + "other")])]
        self.assertEqual(len(S.object_variants(copies)[NAME]), 6)

    def test_exact_repeats_dedup_and_relocation_order_does_not_matter(self):
        relocs = [(1, S.DIR32, GLOBAL), (5, S.REL32, NAME)]
        copies = [(NAME, PREFIX, relocs), (NAME, PREFIX, list(reversed(relocs)))]
        self.assertEqual(S.object_variants(copies)[NAME], [(PREFIX, relocs)])

    def test_different_names_remain_distinct(self):
        self.assertEqual(len(S.object_variants([(NAME, PREFIX, []),
                                               (NAME + "other", PREFIX, [])])), 2)


class HeldVariantControls(unittest.TestCase):
    def test_tiny_verified_control_can_still_prove_its_pointer(self):
        body = b"\xb8" + b"\0" * 4 + b"\xc3"
        retail = b"\xb8" + struct.pack("<I", BASE) + b"\xc3"
        self.assertTrue(S.held_variant_matches(
            body, [(1, S.DIR32, GLOBAL)], Path("fixture.obj"), row(len(body)),
            Image({RVA: retail}), universe([]), collections.Counter()))

    def test_control_relocation_cannot_straddle_held_boundary(self):
        self.assertFalse(S.held_variant_matches(
            PREFIX, [(len(PREFIX) - 2, S.DIR32, GLOBAL)], Path("fixture.obj"), row(),
            Image({RVA: PREFIX}), universe([]), collections.Counter()))


class SweepVariants(unittest.TestCase):
    def sweep(self, copies, held=(), image=None, naked=False):
        uni = universe(held, [(TARGET, len(copies[-1][1]))])
        if naked:
            uni.naked_symbols.add((SOURCE, NAME))
        image = image or Image({TARGET: copies[-1][1]})
        with mock.patch.object(S.locate, "object_functions", return_value=iter(copies)), \
             mock.patch.object(S.NakedBytes, "__call__", return_value=False):
            return S.sweep(uni, image, {SOURCE: Path("fixture.obj")})

    def test_later_body_places_and_duplicate_copy_is_not_an_extra_owner(self):
        good = (NAME, PREFIX, [])
        matches, stats = self.sweep([(NAME, b"badbytes!", []), good, good])
        self.assertEqual(len(matches[("dump", TARGET, len(PREFIX))]["owners"]), 1)
        self.assertEqual(stats["spans"], 2)

    def test_later_matching_copy_supplies_dir32_base(self):
        # The first copy has a different instruction and pointer addend. Its
        # inferred base must not mask out the later, retail-compatible copy.
        good_body = PREFIX + b"\0" * 4
        bad_body = b"X" + PREFIX[1:] + struct.pack("<I", 4)
        relocs = [(len(PREFIX), S.DIR32, GLOBAL)]
        retail = PREFIX + struct.pack("<I", BASE)
        matches, _ = self.sweep([(NAME, bad_body, relocs), (NAME, good_body, relocs)],
                               [row(len(good_body))], Image({RVA: retail, TARGET: retail}))
        self.assertIn(("dump", TARGET, len(retail)), matches)
        self.assertEqual(matches[("dump", TARGET, len(retail))]["owners"][0].sites,
                         ((GLOBAL, BASE),))

    def test_nonmatching_held_copy_cannot_prove_a_global_base(self):
        body = PREFIX + b"\0" * 4
        relocs = [(len(PREFIX), S.DIR32, GLOBAL)]
        retail = PREFIX + struct.pack("<I", BASE)
        matches, _ = self.sweep([(NAME, body, relocs)], [row(len(body))],
                               Image({RVA: b"X" + retail[1:], TARGET: retail}))
        self.assertFalse(matches)

    def test_masked_addend_ambiguity_does_not_invent_two_proven_bases(self):
        relocs = [(len(PREFIX), S.DIR32, GLOBAL)]
        retail = PREFIX + struct.pack("<I", BASE)
        matches, _ = self.sweep([
            (NAME, PREFIX + b"\0" * 4, relocs),
            (NAME, PREFIX + struct.pack("<I", 4), relocs)],
            [row(len(retail))], Image({RVA: retail, TARGET: retail}))
        self.assertFalse(matches)

    def test_same_bytes_with_later_callee_relocation_can_place(self):
        body = PREFIX + b"\0" * 4
        site = len(PREFIX)
        uni = universe([], [(TARGET, len(body))])
        uni.symbol_addresses = {"?right": {TARGET + site + 4}}
        copies = [(NAME, body, [(site, S.REL32, "?wrong")]),
                  (NAME, body, [(site, S.REL32, "?right")])]
        with mock.patch.object(S.locate, "object_functions", return_value=iter(copies)):
            matches, stats = S.sweep(uni, Image({TARGET: body}), {SOURCE: Path("fixture.obj")})
        self.assertEqual(len(matches[("dump", TARGET, len(body))]["owners"]), 1)
        self.assertEqual(stats["skip_rel32_callee_unplaced"], 1)

    def test_later_naked_symbol_is_still_excluded(self):
        matches, _ = self.sweep([(NAME, b"badbytes!", []), (NAME, PREFIX, [])], naked=True)
        self.assertFalse(matches)

    def test_later_copy_cannot_mask_an_unplaced_callee(self):
        body = PREFIX + b"\0" * 4
        matches, stats = self.sweep([(NAME, b"badbytes!", []),
                                    (NAME, body, [(len(PREFIX), S.REL32, "?missing")])])
        self.assertFalse(matches)
        self.assertEqual(stats["skip_rel32_callee_unplaced"], 1)


class ExtendVariants(unittest.TestCase):
    def extend(self, copies, *, starts=(), overlap=False, name=NAME):
        uni = universe([row(name=name)])
        uni.overlaps_matched = lambda rva, size: overlap
        scratch = S.ROOT / "build" / "capability_pilot"
        scratch.mkdir(parents=True, exist_ok=True)
        with tempfile.TemporaryDirectory(dir=scratch) as tmp:
            root = Path(tmp)
            (root / "reverse").mkdir()
            (root / "reverse" / "ghidra_functions.csv").write_text(
                "rva,size\n" + "".join(f"0x{x:X},1\n" for x in starts))
            out = root / "extension.csv"
            with mock.patch.object(S, "ROOT", root), \
                 mock.patch.object(S, "load", return_value=(
                     uni, Image({RVA: PREFIX + TAIL}), {SOURCE: Path("fixture.obj")}, {})), \
                 mock.patch.object(S.locate, "object_functions", return_value=iter(copies)), \
                 contextlib.redirect_stdout(io.StringIO()):
                try:
                    S.cmd_extend(argparse.Namespace(out=str(out)))
                except SystemExit:
                    return []
            with out.open(newline="") as handle:
                return list(csv.DictReader(handle))

    def test_later_longer_copy_retained_and_exact_duplicates_deduped(self):
        good = (NAME, PREFIX + TAIL, [])
        rows = self.extend([(NAME, PREFIX, []), good, good])
        self.assertEqual(len(rows), 1)
        self.assertEqual(int(rows[0]["new_size"]), len(PREFIX + TAIL))

    def test_matching_tail_cannot_rescue_wrong_prefix(self):
        self.assertFalse(self.extend([(NAME, b"X" + PREFIX[1:] + TAIL, [])]))

    def test_later_variant_still_refuses_boundary_inside_tail(self):
        self.assertFalse(self.extend([(NAME, PREFIX, []), (NAME, PREFIX + TAIL, [])],
                                     starts=[RVA + len(PREFIX)]))

    def test_later_variant_still_refuses_claimed_tail(self):
        self.assertFalse(self.extend([(NAME, PREFIX, []), (NAME, PREFIX + TAIL, [])],
                                     overlap=True))

    def test_rehashed_name_counts_names_instead_of_copies(self):
        actual, ledger = "?body@?A0x11111111@@YAXXZ", "?body@?A0x22222222@@YAXXZ"
        rows = self.extend([(actual, PREFIX, []), (actual, PREFIX + TAIL, [])], name=ledger)
        self.assertEqual(len(rows), 1)
        self.assertEqual(rows[0]["symbol"], actual)

    def test_two_rehashed_names_remain_ambiguous(self):
        self.assertFalse(self.extend([
            ("?body@?A0x11111111@@YAXXZ", PREFIX + TAIL, []),
            ("?body@?A0x33333333@@YAXXZ", PREFIX + TAIL, [])],
            name="?body@?A0x22222222@@YAXXZ"))


if __name__ == "__main__":
    unittest.main()
