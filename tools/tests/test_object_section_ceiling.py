"""A COFF section number is int16, and the gate has to say so when it bites.

A 250-instantiation generated TU needs 44,768 COMDATs. Every symbol past section
0x7FFF then reads back negative, so `section > 0` rejects it as undefined and 56
verified rows died as "symbol not found in object" — a message that points at the
symbol when the fault is the size of the batch. The wave was re-cut by hand after
the cause was found by reading the COFF spec; the next one reads it here.
"""
import struct
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build


def object_with_sections(path, count):
    """A COFF object carrying `count` empty sections and no symbols at all."""
    header = struct.pack("<HHIIIHH", 0x014C, count, 0, 20 + count * 40, 0, 0, 0)
    section = struct.pack("<8sIIIIIIHHI", b".text\0\0\0", 0, 0, 0, 0, 0, 0, 0, 0, 0)
    path.write_bytes(header + section * count + b"\0\0\0\0")
    return path


def test_an_object_past_the_ceiling_names_the_ceiling(tmp_path):
    obj = object_with_sections(tmp_path / "fam_017.obj", build.COFF_SECTION_CEILING + 1)

    with pytest.raises(ValueError) as exc:
        build.read_object_symbol_bytes(obj, "?missing@@YAXXZ")

    message = str(exc.value)
    assert "?missing@@YAXXZ" in message, "the symbol is still named"
    assert "fam_017.obj" in message, "and so is the object that cannot hold it"
    assert str(build.COFF_SECTION_CEILING) in message
    assert "section budget" in message, "the batch limit is the thing to change"


def test_an_object_under_the_ceiling_blames_the_symbol_alone(tmp_path):
    """A missing symbol in a normal object is a missing symbol, not a budget."""
    obj = object_with_sections(tmp_path / "small.obj", 4)

    with pytest.raises(ValueError) as exc:
        build.read_object_symbol_bytes(obj, "?missing@@YAXXZ")

    assert str(exc.value) == "symbol not found in object: ?missing@@YAXXZ"
