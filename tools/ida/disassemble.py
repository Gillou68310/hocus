from pathlib import Path
from splat.scripts import split
import ida_nalt
import idc

#TODO: Unhide all

import debugpy
debugpy.listen(("localhost", 5678),in_process_debug_adapter=True)
debugpy.wait_for_client()

path = ida_nalt.get_input_file_path()
exe = path.split("\\")[-1]
version = exe.split(".")[1]

path =  Path("versions") / version / "hocus.yaml"
config = split.conf.load([path])

if "jwasm" in split.options.opts.asm_path.as_posix():
    idc.set_target_assembler(0)
else:
    idc.set_target_assembler(1)

split.options.opts.base_path.mkdir(parents=True, exist_ok=True)
rom_bytes = split.options.opts.target_path.read_bytes()
stats = split.statistics.Statistics()
cache = split.cache_handler.Cache(config, False, False)
all_segments = split.initialize_segments(config["segments"])
split.do_split(all_segments, rom_bytes, stats, cache)
idc.set_target_assembler(0)