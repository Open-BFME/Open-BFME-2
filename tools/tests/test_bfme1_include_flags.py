"""BFME1 donor include paths must resolve from BFME2's working directory."""
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

import build  # noqa: E402


def test_current_layout_donor_flags_are_rooted_at_the_submodule(tmp_path, monkeypatch):
    monkeypatch.setattr(build, "BFME1_ROOT", tmp_path)
    (tmp_path / "game").mkdir()
    (tmp_path / "inputs" / "reference").mkdir(parents=True)
    source = tmp_path / "game" / "Libraries" / "sample.cpp"

    assert build._current_bfme1_include_flag(
        "-Igame/Libraries/Include", source) == (
            "-Ireference/open-bfme-1/game/Libraries/Include")
    assert build._current_bfme1_include_flag(
        "-Iinputs/reference/shims/sweep", source) == (
            "-Ireference/open-bfme-1/inputs/reference/shims/sweep")
    assert build._current_bfme1_include_flag(
        "-IC:/SDK/include", source) == "-IC:/SDK/include"
    assert build._current_bfme1_include_flag(
        "-I\\SDK\\include", source) == "-I\\SDK\\include"


def test_legacy_layout_donor_flags_resolve_against_the_legacy_tree(tmp_path, monkeypatch):
    monkeypatch.setattr(build, "BFME1_ROOT", tmp_path)
    (tmp_path / "Code").mkdir()
    source = tmp_path / "Code" / "Libraries" / "sample.cpp"

    assert build._current_bfme1_include_flag("-ICode/Libraries/Include", source) == (
        "-Ireference/open-bfme-1/Code/Libraries/Include")


def test_donor_under_symlinked_subtree_maps_include_flags(tmp_path, monkeypatch):
    # Seats keep reference/open-bfme-1 as a real directory whose game/ subtree
    # is a symlink into the main checkout, so the donor's realpath lands outside
    # BFME1_ROOT even though the source is a genuine descendant of it.
    main_checkout = tmp_path / "main" / "reference" / "open-bfme-1"
    (main_checkout / "game" / "Libraries").mkdir(parents=True)
    seat_root = tmp_path / "seat" / "reference" / "open-bfme-1"
    seat_root.mkdir(parents=True)
    (seat_root / "game").symlink_to(main_checkout / "game", target_is_directory=True)
    monkeypatch.setattr(build, "BFME1_ROOT", seat_root)
    source = seat_root / "game" / "Libraries" / "sample.cpp"
    source.write_text("// cl: /I game/Libraries/Include\n")

    assert build._is_bfme1_donor(source)
    assert build._current_bfme1_include_flag(
        "-Igame/Libraries/Include", source) == (
            "-Ireference/open-bfme-1/game/Libraries/Include")


def test_donor_detection_is_lexical_and_rejects_outside_paths(tmp_path, monkeypatch):
    main_checkout = tmp_path / "main" / "reference" / "open-bfme-1"
    (main_checkout / "game").mkdir(parents=True)
    seat_root = tmp_path / "seat" / "reference" / "open-bfme-1"
    seat_root.mkdir(parents=True)
    (seat_root / "game").symlink_to(main_checkout / "game", target_is_directory=True)
    monkeypatch.setattr(build, "BFME1_ROOT", seat_root)
    bfme2_source = tmp_path / "seat" / "Code" / "sample.cpp"
    bfme2_source.parent.mkdir(parents=True)

    # The other checkout's copy of a donor is not this seat's donor.
    assert not build._is_bfme1_donor(main_checkout / "game" / "sample.cpp")
    # A BFME2 source keeps its flags even when it sits beside the donor tree.
    assert not build._is_bfme1_donor(bfme2_source)
    # Lexical traversal out of the donor root is not a donor descendant.
    assert not build._is_bfme1_donor(seat_root / ".." / ".." / "escape.cpp")
    assert build._current_bfme1_include_flag(
        "-Igame/Libraries/Include", bfme2_source) == "-Igame/Libraries/Include"


def test_bfme2_local_game_include_is_not_rewritten():
    source = build.ROOT / "Code" / "Libraries" / "sample.cpp"
    assert build._current_bfme1_include_flag("-Igame/local/include", source) == (
        "-Igame/local/include")


def test_explicit_submodule_legacy_include_still_maps_to_current_layout():
    assert build._current_bfme1_include_flag(
        "-Ireference/open-bfme-1/Code/Libraries/Include") == (
            "-Ireference/open-bfme-1/game/Libraries/Include")


def test_rootless_cnc_reference_flag_resolves_to_physical_current_reference(
        tmp_path, monkeypatch):
    repo = tmp_path / "bfme2"
    donor = repo / "reference/open-bfme-1"
    physical = (donor / "inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/"
                "Code/Libraries/Source/WWVegas/WWDebug")
    physical.mkdir(parents=True)
    monkeypatch.setattr(build, "ROOT", repo)
    monkeypatch.setattr(build, "BFME1_ROOT", donor)
    source = repo / "Code" / "sample.cpp"

    assert build._current_bfme1_include_flag(
        "-Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/"
        "Libraries/Source/WWVegas/WWDebug", source) == (
            "-Ireference/open-bfme-1/inputs/reference/"
            "CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/"
            "WWVegas/WWDebug")


def test_bfme2_legacy_cnc_code_root_prefers_verified_migrated_game_directory(
        tmp_path, monkeypatch):
    repo = tmp_path / "bfme2"
    donor = repo / "reference/open-bfme-1"
    legacy = (donor / "inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/"
              "Code/Libraries/Source/WWVegas/WW3D2")
    migrated = donor / "game/Libraries/Source/WWVegas/WW3D2"
    legacy.mkdir(parents=True)
    migrated.mkdir(parents=True)
    monkeypatch.setattr(build, "ROOT", repo)
    monkeypatch.setattr(build, "BFME1_ROOT", donor)
    source = repo / "Code" / "sample.cpp"

    assert build._current_bfme1_include_flag(
        "-Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/"
        "Libraries/Source/WWVegas/WW3D2", source, "GeneralsMD") == (
            "-Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2")


def test_legacy_cnc_library_family_moves_under_wwvegas_only_when_present(
        tmp_path, monkeypatch):
    repo = tmp_path / "bfme2"
    donor = repo / "reference/open-bfme-1"
    physical = (donor / "inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/"
                "Code/Libraries/Source/WWVegas/WWSaveLoad")
    physical.mkdir(parents=True)
    monkeypatch.setattr(build, "ROOT", repo)
    monkeypatch.setattr(build, "BFME1_ROOT", donor)
    source = donor / "game" / "sample.cpp"

    assert build._current_bfme1_include_flag(
        "-Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/"
        "Libraries/Source/WWSaveLoad", source) == (
            "-Ireference/open-bfme-1/inputs/reference/"
            "CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/"
            "WWVegas/WWSaveLoad")


@pytest.mark.parametrize("old,new", [
    ("GeneralsMD/Code/Compression",
     "GeneralsMD/Code/Libraries/Source/Compression"),
    ("GeneralsMD/Code/WWDebug",
     "GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug"),
    ("GeneralsMD/GeneralsMD/Code/GameEngine/Source",
     "GeneralsMD/Code/GameEngine/Source"),
])
def test_verified_cnc_directory_moves_use_existing_physical_target(
        tmp_path, monkeypatch, old, new):
    repo = tmp_path / "bfme2"
    donor = repo / "reference/open-bfme-1"
    physical = (donor / "inputs/reference/CnC_Generals_Zero_Hour" / new)
    physical.mkdir(parents=True)
    monkeypatch.setattr(build, "ROOT", repo)
    monkeypatch.setattr(build, "BFME1_ROOT", donor)
    source = donor / "game" / "sample.cpp"

    assert build._current_bfme1_include_flag("-Iinputs/reference/"
        "CnC_Generals_Zero_Hour/" + old, source) == (
            "-Ireference/open-bfme-1/inputs/reference/"
            "CnC_Generals_Zero_Hour/" + new)


def test_legacy_toolchain_alias_resolves_only_to_packaged_tree(tmp_path, monkeypatch):
    repo = tmp_path / "bfme2"
    donor = repo / "reference/open-bfme-1"
    physical = (donor / "inputs/toolchains/vs2003/Program Files/"
                "Microsoft Visual Studio .NET 2003/Vc7/PlatformSDK/Include")
    physical.mkdir(parents=True)
    monkeypatch.setattr(build, "ROOT", repo)
    monkeypatch.setattr(build, "BFME1_ROOT", donor)
    source = donor / "game" / "sample.cpp"

    assert build._current_bfme1_include_flag(
        "-Iinputs/toolchains/vs2003/PROG~FBU/MICR~2RR.NET/"
        "Vc7/PLAT~MIB/Include", source) == (
            "-Ireference/open-bfme-1/inputs/toolchains/vs2003/Program Files/"
            "Microsoft Visual Studio .NET 2003/Vc7/PlatformSDK/Include")


def test_bfme2_code_path_stays_local_when_present_and_unknown_paths_stay_visible(
        tmp_path, monkeypatch):
    repo = tmp_path / "bfme2"
    donor = repo / "reference/open-bfme-1"
    (repo / "Code/GameEngine/Include/Precompiled").mkdir(parents=True)
    (donor / "game/GameEngine/Include/Precompiled").mkdir(parents=True)
    monkeypatch.setattr(build, "ROOT", repo)
    monkeypatch.setattr(build, "BFME1_ROOT", donor)
    source = repo / "Code" / "sample.cpp"

    assert build._current_bfme1_include_flag(
        "-ICode/GameEngine/Include/Precompiled", source) == (
            "-ICode/GameEngine/Include/Precompiled")
    assert build._current_bfme1_include_flag(
        "-Ireference/unknown/include", source) == "-Ireference/unknown/include"


def test_missing_legacy_code_path_maps_only_to_existing_bfme1_directory(
        tmp_path, monkeypatch):
    repo = tmp_path / "bfme2"
    donor = repo / "reference/open-bfme-1"
    (donor / "game/GameEngine/Include/Precompiled").mkdir(parents=True)
    monkeypatch.setattr(build, "ROOT", repo)
    monkeypatch.setattr(build, "BFME1_ROOT", donor)
    source = repo / "Code" / "sample.cpp"

    assert build._current_bfme1_include_flag(
        "-ICode/GameEngine/Include/Precompiled", source) == (
            "-Ireference/open-bfme-1/game/GameEngine/Include/Precompiled")
    assert build._current_bfme1_include_flag(
        "-ICode/NoSuchDirectory", source) == "-ICode/NoSuchDirectory"


def test_unqualified_cnc_code_root_uses_one_sibling_variant_from_cl_flags(
        tmp_path, monkeypatch):
    repo = tmp_path / "bfme2"
    donor = repo / "reference/open-bfme-1"
    for variant in ("Generals", "GeneralsMD"):
        (donor / "inputs/reference/CnC_Generals_Zero_Hour" / variant /
         "Code/Libraries/Source/WWVegas/WWMath").mkdir(parents=True)
        (donor / "inputs/reference/CnC_Generals_Zero_Hour" / variant /
         "Code/GameEngine/Include").mkdir(parents=True)
    monkeypatch.setattr(build, "ROOT", repo)
    monkeypatch.setattr(build, "BFME1_ROOT", donor)
    source = repo / "Code" / "sample.cpp"
    source.parent.mkdir(parents=True)
    source.write_text(
        "// cl: /Ireference/open-bfme-1/inputs/reference/"
        "CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include "
        "/Ireference/open-bfme-1/inputs/reference/"
        "CnC_Generals_Zero_Hour/Code/Libraries/Source/WWVegas/WWMath\n")

    flags = build.source_extra_flags(source)
    assert ("-Ireference/open-bfme-1/inputs/reference/"
            "CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath") in flags


def test_unqualified_cnc_code_root_stays_unresolved_when_variant_is_ambiguous(
        tmp_path, monkeypatch):
    repo = tmp_path / "bfme2"
    donor = repo / "reference/open-bfme-1"
    monkeypatch.setattr(build, "ROOT", repo)
    monkeypatch.setattr(build, "BFME1_ROOT", donor)
    source = repo / "Code" / "sample.cpp"

    assert build._current_bfme1_include_flag(
        "-Ireference/open-bfme-1/inputs/reference/"
        "CnC_Generals_Zero_Hour/Code/Libraries/Source/WWVegas/WWMath",
        source) == (
            "-Ireference/open-bfme-1/inputs/reference/"
            "CnC_Generals_Zero_Hour/Code/Libraries/Source/WWVegas/WWMath")


def test_source_flag_tokens_preserve_existing_bare_flags():
    flags = " /O2\t/MD /Ireference/shims/sweep -IC:\\SDK\\include /DVALUE=1 "
    assert build._source_flag_tokens(flags) == flags.split()


def test_quoted_include_paths_preserve_spaces_and_backslashes():
    flags = r'/O2 /I"C:\Program Files\SDK\Include" -I "another include directory" /MD'
    assert build._source_flag_tokens(flags) == [
        '/O2', r'/IC:\Program Files\SDK\Include',
        '-Ianother include directory', '/MD']


def test_quoted_sdk_flag_is_one_resolved_repository_relative_operand(tmp_path):
    source = tmp_path / 'sample.cpp'
    include = ('reference/open-bfme-1/inputs/toolchains/vs2003/Program Files/'
               'Microsoft Visual Studio .NET 2003/Vc7/PlatformSDK/Include')
    source.write_text('// cl: /MD /I"' + include + '" /EHsc\n')
    assert build.source_extra_flags(source) == ['-MD', '-I' + include, '-EHsc']


def test_malformed_quoted_include_paths_are_refused():
    import pytest
    for flags in ('/I"unfinished path', '/I""', '/I"path"suffix', '/Ipath"bad'):
        with pytest.raises(SystemExit, match='quoted /I include path'):
            build._source_flag_tokens(flags)
