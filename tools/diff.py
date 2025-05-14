from pathlib import Path
import sys
sys.path.insert(0, str(Path(__file__).parent / "tdinfo-parser"))
import tdinfo_structs

if len(sys.argv) != 3:
    print("Usage: python diff.py <base_exe> <dos_exe>")
    sys.exit(1)

base_exe = tdinfo_structs.DOS_MZ_EXE_STRUCT.parse_file(sys.argv[1])
dos_exe = tdinfo_structs.DOS_MZ_EXE_STRUCT.parse_file(sys.argv[2])

if base_exe.wReloCnt != dos_exe.wReloCnt:
    print("Relocation count mismatch")
    sys.exit(1)

#Sort relocations
base_exe.alReloTbl.sort(key=lambda x: (x.segment *65536 + x.offset))
dos_exe.alReloTbl.sort(key=lambda x: (x.segment *65536 + x.offset))

if base_exe.alReloTbl != dos_exe.alReloTbl:
    print("Relocation table mismatch")
    sys.exit(1)

if base_exe.abImage != dos_exe.abImage:
    print("Program image mismatch")
    sys.exit(1)

print("OK")
sys.exit(0)