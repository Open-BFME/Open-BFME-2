# W3DMouse thread flag owner trial

The two existing providers bind to one native byte at 0x009E4B30. The trial moves the C-linkage definition and its data row into W3DMouse.cpp and leaves a declaration in W3DMouseInitW3DAssets.cpp. All six data rows pass in both units, including the moved byte. The transfer still fails the code gate for W3DMouse::init at 0x000990CF. The other 37 rows match in the ordinary and volatile-comparison trials.

With the owning definition beside init, the original C++ moves the flag clear before the redraw-mode comparison. Duplicating the clear in both arms with a volatile mode read restores the compare first, but moves the thread-address load ahead of the clear. Computing the condition into a bool before the clear grows the body and moves the final call past the 58-byte extent. Keeping the original owner and making the flag volatile also fails init. Neither owner placement nor a volatile read resolves the scheduling constraint.

Both sources and the data row were restored. The three tool-managed findings remain as before. LINK-244 still requires a shared file-static definition in an approved translation-unit merge or an exact external-flag source form.
