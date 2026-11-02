# Remove the redundant allocation declaration in HLodModelNodeVectorResize: bounded unsuccessful adoption trial

Source `Code/Libraries/Source/WWVegas/WW3D2/HLodModelNodeVectorResize.cpp`, existing parent `?Resize@?$VectorClass@VModelNodeClass@HLodClass@@@@UAE_NHPBVModelNodeClass@HLodClass@@@Z` at
0x0019E700/588B. The standard new header preserves external code but changes .drectve by selecting an additional C++ runtime library; the source was restored. Removing the local nonthrowing declaration alone instead changes VectorClass<ModelNodeClass>::Resize. Preserve the established native exception and linker contracts; a wider allocation-header strategy remains a prerequisite.

The private candidate does not replace the committed source. No new native
row, completed adoption or runtime improvement is claimed. The existing
source remains byte-verified. Diagnostic sources and comparisons are retained
in ignored build/up-to-eighteen-each-20261103-0008/b2-10-*. The adjacent patch preserves the latest
private trial. Other trial variants, if performed, remain in the diagnostic controls.
No shared header, compiler flag, pin, alias or gate change is attempted.
