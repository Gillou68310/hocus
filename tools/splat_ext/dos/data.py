#!/usr/bin/env python3

from splat.segtypes.common.data import CommonSegData
from splat.util import options
from pathlib import Path
import sys
sys.path.insert(0, str(Path(__file__).parent))
from disassembler import disassemble_data

class DOSSegData(CommonSegData):
    def split(self, rom_bytes: bytes):
        disassemble_data(self)

    def asm_out_path(self) -> Path:
        return options.opts.data_path / self.dir / f"{self.name}.asm"
    
    def should_split(self) -> bool:
        return self.extract