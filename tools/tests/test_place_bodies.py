"""Which emitted symbols place_bodies may try to place."""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

import place_bodies  # noqa: E402


@pytest.mark.parametrize("name", [
    "?push_back@?$vector@H@_STL@@QAEXABH@Z",   # C++
    "_auxsort",                                 # C, static (Lua lbaselib.c)
    "_luaB_call",
    "___mbtowc",                                # C function named __mbtowc
    "_WSAStartup@8",                            # stdcall
])
def test_function_names_are_placeable(name):
    assert place_bodies.placeable(name)


@pytest.mark.parametrize("name", [
    "__ehhandler$?f@@YAXXZ",                    # EH handler thunk
    "__unwindfunclet$?f@@YAXXZ$0",              # unwind funclet
    "_$E36",                                    # dynamic initializer
    "_name@x",                                  # not a stdcall suffix
    "name",                                     # no C decoration at all
])
def test_compiler_generated_symbols_are_not(name):
    assert not place_bodies.placeable(name)
