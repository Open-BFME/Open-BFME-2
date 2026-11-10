# DefaultModuleKey and DefaultModuleName guard emission

Local MSVC 7.1 source trials based on 945334bfd0. The PE comparisons use repository baselines. They do not establish which original translation unit owned the game code.

BFME2 game.dat and WorldBuilder have precisely the same fourteen decorated guard exports (including the template argument and accessor name). In both, the .text scan finds literal references to the category-six S24/S28 and none to S22/S26. For example, WorldBuilder's S24 word has RVA 0x01E5F1F4; S22 is at 0x01E64188. The corresponding BFME1 WorldBuilder exports have different counters. BFME2 WorldBuilder includes source path literals for fxpswindmodule.cpp and fxpsdefaultdrawmodule.cpp. game.dat includes only the former path of those two. The retail image has no COFF symbol table. Its debug record identifies RTS.pdb, GUID 48032004-68c6-4583-8055-9be33978879d, age 4. The current tu_evidence.py --source for FXParticleSystemDefaults.cpp returned no evidence rows.

Experiments ran in scratch copies using the compiler command of FXParticleSystemFactories.cpp, with the existing Defaults accessor definitions and string shim. The instruction stream, initialization tables and winner of each COMDAT still require independent proof before any composition is kept. No TU move was attempted.

- Merely making the GetValue definitions visible where the factory instantiates its default tags emitted no GetValue guards. Its VALUE references stayed undefined.
- Explicit instantiation of the key and name classes emitted twelve guards. In a grouped trial with the real function-local instance inside ConcreteModuleClass::getInstance, the category-six in-class key/name pair was S30/S32. Marking the key/name and concrete classes dllexport preserved the counter sequence.
- Put the two GetValue bodies outside the class and mark them inline. The guards remain external (COFF class 2) and the key-to-name gap becomes four, the observed retail gap. The same definitions without inline give the same numbers but COFF class 3, so a numeric coincidence cannot satisfy an external export.
- Define getInstance out of class too, with the existing static ConcreteModuleClass instance. Group the existing default tag specializations and the key/name/concrete explicit instantiations by the category order observed in the BFME2 WorldBuilder code: 6, 1, 0, 3, 2, 7. MSVC emitted key/name pairs 30/34, 40/44, 50/54, 60/64, 70/74, 80/84. The corresponding live retail pairs are 24/28, 128/132, 142/146, 156/160, 170/174, 184/188. None of the ten missing export spellings is recovered by this trial.

This narrows the missing input to the surrounding source and instantiation sequence, including the large gap after category six. Repeating only the wrapper permutation, or padding a compiler counter, does not recover those inputs. Confirm the TU and additional live instantiations before changing production sources. The original Defaults TU and export registry are unchanged.

Both BFME2 images give the same additional ordering constraint. Following the exported code addresses (including jump thunks), between category 6 and category 1 there are seven getInstance bodies: the default and StreakDraw, QuadDraw, ButterflyDraw, RenderObjectDraw, LightningDraw and GpuDraw, in that order. Between each subsequent pair of default categories there is one getInstance. The WB function inventory has no file/line evidence in this window. In the scratch factory trial, placing the six existing draw wrappers in that order moves category 1 from 40/44 to 52/56; the remaining four key/name pairs become 62/66, 72/76, 82/86, 92/96. Class dllexport on the two default templates and the concrete module class emits twelve actual /EXPORT:,DATA directives for the guards, with those same numbers. Export visibility and the Key/Name spacing are therefore both reproducible from C++; the remaining counter sequence and object ownership are still open.

At 5c4cc57fb7, compared the COFF bodies against the retail accessors and
the checkout's verified FXParticleSystemDefaults object. In the draw-order
trial with class dllexport, all 12 accessors have retail's 127-byte extent
and instruction bytes outside relocation operands. All 192 relocations
retain their offsets, kinds and target spellings apart from the two guard
operands per accessor (+12 and +27). Each pair uses the same word. This
isolates a difference in compiler-generated guard identity; the trial still
does not produce the ten outstanding names or establish object ownership.

A separate scratch control used the actual Rva0055C8BCCtor.cpp flags and
source, including its real function-local publisher. Instantiating the two
category-six accessor classes before or after that source produced S3/S7
both times. With that TU's include search order the +111 relocation in each
body also names StringBase::str's TheNullChr instead of the empty string
literal in the verified Defaults object (retail operand VA 0x00BBAC1C).
The three draw-module file/line pairings in the TU map are useful for the
draw code, but the publisher alone does not explain the S22/S26 exports.
