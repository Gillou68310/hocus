#!/usr/bin/env python3

from splat.segtypes.common.asm import CommonSegAsm
from splat.util import options
from pathlib import Path
import sys
sys.path.insert(0, str(Path(__file__).parent))
from disassembler import disassemble_code

class DOSSegAsm(CommonSegAsm):
    def split(self, rom_bytes: bytes):
        disassemble_code(self)

    def asm_out_path(self) -> Path:
        return options.opts.asm_path / self.dir / f"{self.name}.asm"