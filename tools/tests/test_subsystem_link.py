"""subsystem_link: which decorated names belong to the subsystem.

The own-symbol rules are the tool's teeth: the harness's extern file may not
define a subsystem symbol, and the library may not leave one undefined. Both
rest on owns(); the end-to-end controls (pre-pilot profile tree fails with 20
undefined own symbols, old+new files together fail with 6 LNK2005, the pilot
tree links) are recorded in docs/subsystem_template.md's worked example."""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import subsystem_link as sl

OWN = ["Profile", "ProfileId", "ProfileFuncLevel"]


def test_members_and_statics_are_owned():
    assert sl.owns("?StartRange@Profile@@SAXPBD@Z", OWN)
    assert sl.owns("?first@ProfileId@@0PAV1@A", OWN)
    assert sl.owns("??0ProfileId@@QAE@PBD00HH@Z", OWN)
    assert sl.owns("??_7Profile@@6B@", OWN)
    assert not sl.owns("??0ProfileResultFileCSV@@QAE@PBD@Z", OWN)


def test_nested_class_members_are_owned():
    assert sl.owns("?Enum@IdList@ProfileFuncLevel@@QBE_NIAAVId@2@PAI@Z", OWN)
    assert sl.owns("?GetCalls@Id@ProfileFuncLevel@@QBE_KI@Z", OWN)


def test_external_and_prefix_names_are_not_owned():
    assert not sl.owns("?SimpleMatch@Debug@@SA_NPBD0@Z", OWN)
    assert not sl.owns("?theDebug@@3PAVDebug@@A", OWN)
    assert not sl.owns("__imp__GlobalAlloc@8", OWN)
    # a class whose name merely starts with an owned one
    assert not sl.owns("?Create@ProfileResultFileCSV@@SAPAVProfileResultInterface@@HPBQBD@Z", ["Profile"])
