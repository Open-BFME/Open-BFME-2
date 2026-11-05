# `reverse/string_xrefs.tsv` misses 64 of 173 retail `__FILE__` path strings (2026-11-05)

Target facts (retail image, scan below): the image holds 173 NUL-terminated
`<drive>:\...\Code\...\*.cpp|*.c` strings. 109 appear as a text column in
`reverse/string_xrefs.tsv` (Ghidra's `tools/ghidra/list_string_xrefs.java` output);
64 do not, and 56 of those 64 are pushed as a `push imm32` (`68 <VA>`) somewhere in
`.text` (count in the second column). `tools/tu_map.py` reads F (`file_strings`)
only from `string_xrefs.tsv`, so every body that pushes one of these strings has no
F anchor.

Example: `?attemptDamage@DetachableRiderBody@@UAEXPAVDamageInfo@@@Z` 0x004C1D49
pushes 0x00C5C118 (`...\GameLogic\Object\Body\DetachableRiderBody.cpp`) with line
94 for GetGameLogicRandomValueReal. Its tu_map row carries only N, the whole
0x004C1B80..0x004C1E8B run is proposed into ImmortalBody.cpp, and the in-memory map
`tu_skeleton.py` builds approved the run into
`Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DetachableRiderBody.cpp`,
a directory taken only from two misfiled donors (`ChinookAIUpdateBuildFieldParse.cpp`,
`ChinookAIUpdateModuleDataCtor.cpp`, both DetachableRiderBodyModuleData). The merge
was stopped before it wrote anything.

Next step (tooling seat, Verifier-Change): let `file_strings` also take `push imm32`
references to path strings found in the image (or regenerate `string_xrefs.tsv` with
these strings defined), run `tools/tu_map.py --validate`, and refresh the committed map
in the same change. Until then a TU whose bodies push one of the strings below can
carry a wrong or missing approval.

Scan: the script at the end (regex over the raw image, then a byte search
for `68 <VA>` in `.text`); the output is reproduced here.

```
path strings 173 in xrefs 109 missing 64 missing with push refs 56
0xbc4ce0 2 C:\projects\bfme2patch103\bfme2\Code\GameEngineDevice\Source\W3DDevice\GameClient\W3DFXParticleSystem.cpp
0xbc54c8 3 C:\projects\bfme2patch103\bfme2\Code\GameEngineDevice\Source\MilesAudioDevice\MilesAudioManager.cpp
0xbc6a00 1 C:\projects\bfme2patch103\bfme2\Code\GameEngineDevice\Source\W3DDevice\GameClient\Drawable\W3DHordeModelDraw.cpp
0xbc7488 1 C:\projects\bfme2patch103\bfme2\Code\GameEngineDevice\Source\W3DDevice\GameClient\W3DView.cpp
0xbc9c40 4 C:\projects\bfme2patch103\bfme2\Code\GameEngineDevice\Source\W3DDevice\GameClient\Drawable\W3DScriptedModelDraw.cpp
0xbcbe58 1 C:\projects\bfme2patch103\bfme2\Code\GameEngineDevice\Source\W3DDevice\GameClient\Drawable\W3DRopeDraw.cpp
0xbcf4b0 1 C:\projects\bfme2patch103\bfme2\Code\GameEngineDevice\Source\W3DDevice\GameClient\Water\W3DWaterTracks.cpp
0xbf9e60 1 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\Object\Update\AIUpdate.cpp
0xbfd2e0 1 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameClient\InGameUI.cpp
0xc1da70 3 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameClient\System\FXParticleSystem\fxpsstoragemodule.cpp
0xc38bc8 1 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\Object\CreateAHeroHero.cpp
0xc3ee08 1 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameNetwork\HeroTransfer.cpp
0xc3fc08 2 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\Object\Update\SpecialAbilityUpdate.cpp
0xc3fd10 1 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\Object\Behavior\AutoHealBehavior.cpp
0xc44b28 11 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\Object\Contain\HordeContain\HordeContain.cpp
0xc480e0 1 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\Object\Update\AIUpdate\AnimalAIUpdate.cpp
0xc484c8 3 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\Object\Update\CivilianSpawnUpdate.cpp
0xc4a068 1 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\Object\Behavior\ReplenishUnitsBehavior.cpp
0xc4ac68 1 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\Object\Die\CrushDie.cpp
0xc4b370 1 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\Object\Update\DeletionUpdate.cpp
0xc4d238 1 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\Object\Update\LargeGroupBonusUpdate.cpp
0xc4f0a0 1 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\Object\Update\AutoPickUpUpdate.cpp
0xc4f678 1 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\Object\Update\BoredUpdate.cpp
0xc51ff8 1 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\Object\Update\StealthDetectorUpdate.cpp
0xc566b0 1 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\Object\Update\EmotionTrackerUpdate.cpp
0xc56b48 1 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\Object\Update\EntEnraged.cpp
0xc599b8 1 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\Object\Damage\TransitionDamageFX.cpp
0xc5a9f8 2 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\Object\Collide\CrateCollide\SalvageCrateCollide.cpp
0xc5c118 1 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\Object\Body\DetachableRiderBody.cpp
0xc5cec8 1 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\Object\SpecialPower\ElvenWoodSpecialPower.cpp
0xc600b0 1 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\Object\Update\NotifyTargetsOfImminentProbableCrushingMux.cpp
0xc62808 2 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\SkirmishAI\AIWallBuilder\AIWallBuilder.cpp
0xc62c60 1 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\AI\AISkirmishPlayer.cpp
0xc63128 2 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\AI\AIPlayer.cpp
0xc632a8 1 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\System\LivingWorld\AutoResolve\LivingWorldAutoResolveBattle.cpp
0xc63468 1 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\System\LivingWorld\LivingWorldAISupport\LivingWorldAI.cpp
0xc63f18 4 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\SkirmishAI\AITacticalAI\AITacticsGenerator\AITacticsGenerator.cpp
0xc69ed8 1 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\Ai\AIGuardRetaliate.cpp
0xc6a0e8 2 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\AI\AITNGuard.cpp
0xc6e0c8 1 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\SkirmishAI\AITacticalAI\AITargetChooser\AITargetHeuristics\AITargetHeuristicExpansionBase.cpp
0xc6ff80 1 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\Object\Contain\HordeContain\HordeMeleeAmoeba.cpp
0xc70cc0 2 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\SkirmishAI\AIUnitBuilder\AIUnitBuilder.cpp
0xc70df0 1 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\SkirmishAI\AITeamBuilder\AITeamBuilder.cpp
0xc71d38 1 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\SkirmishAI\AITacticalAI\AITargetChooser\AIEnemyManager.cpp
0xc72020 1 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\SkirmishAI\AITacticalAI\AITacticsGenerator\ExpansionTactics\AISimpleExpansionTactic.cpp
0xc72180 2 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\SkirmishAI\AITacticalAI\AITacticsGenerator\TargetlessTactics\AIRoamingDefenseTactic.cpp
0xc72590 2 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\SkirmishAI\AITacticalAI\AITacticalNavy\AINavyUnitBattleShip.cpp
0xc72618 1 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\SkirmishAI\AIBaseBuilder\AIBase.cpp
0xc74188 1 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameClient\Gui\GUICallbacks\Apt\AptOnlineQuickMatch.cpp
0xc76340 1 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\SkirmishAI\AISpecialPowers\AISpecialPowerInstances\AISpecialPowerSelfAoEHealHeros.cpp
0xc76520 1 C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameLogic\SkirmishAI\AIUpgrade\AIUpgradeHeuristicFortress.cpp
0xceb438 1 C:\projects\bfme2patch103\bfme2\Code\Libraries\Source\Apt\AptMath.cpp
0xceced0 1 C:\projects\bfme2patch103\bfme2\Code\Libraries\Source\Apt\AptSound.cpp
0xcef348 1 C:\projects\bfme2patch103\bfme2\Code\Libraries\Source\Apt\AptObject\AptObject.cpp
0xcef3c0 2 C:\projects\bfme2patch103\bfme2\Code\Libraries\Source\Apt\AptObject\AptGlobalObject.cpp
0xcef948 2 C:\projects\bfme2patch103\bfme2\Code\Libraries\Source\Apt\AptTextFormat.cpp
```

Script (run from the repo root):

```python
import re, struct, sys
sys.path.insert(0, 'tools')
import callers_of as C
data, secs = C.load_image()
# map file offset -> rva
def off2rva(o):
    for va, vsz, raw in secs:
        if raw <= o < raw + vsz:
            return va + (o - raw)
known = set()
for line in open('reverse/string_xrefs.tsv', encoding='utf-8', errors='replace'):
    t, _, refs = line.rstrip('\n').rpartition('\t')
    known.add(t)
pat = re.compile(rb'[A-Za-z]:\\[ -~]{0,200}?\\Code\\[ -~]+?\.(?:cpp|c)\x00', re.I)
strs = {}
for m in pat.finditer(data):
    s = m.group(0)[:-1]
    # trim to start of drive spec
    rva = off2rva(m.start())
    if rva is not None:
        strs[rva] = s.decode('latin1')
# text section refs: push imm32 (68 xx xx xx xx)
text = [s for s in secs if s[0] == 0x1000][0]
va, vsz, raw = text
blob = data[raw:raw + vsz]
refs = {}
for rva, s in strs.items():
    needle = b'\x68' + struct.pack('<I', rva + 0x400000)
    i = blob.find(needle)
    n = 0
    while i >= 0:
        n += 1
        i = blob.find(needle, i + 1)
    refs[rva] = n
missing = [(rva, s, refs[rva]) for rva, s in strs.items() if s not in known]
print('path strings', len(strs), 'in xrefs', len(strs) - len(missing), 'missing', len(missing),
      'missing with push refs', sum(1 for m in missing if m[2]))
for rva, s, n in sorted(missing)[:400]:
    if n:
        print(hex(rva + 0x400000), n, s)
```
