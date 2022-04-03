#!/usr/bin/env python3

import sys
import time
from importlib import import_module
from lib import format_duration

if len(sys.argv) < 2:
    raise RuntimeError("Must provide path to input files")

start = time.time()
for i in range(1):
    day = import_module(f"day{i+1}")
    day_start = time.time()
    day.day(f"{sys.argv[1]}/{i+1}.txt")
    print(f"\tCompleted in {format_duration(time.time()-day_start)}")
print(f"All puzzles completed in {format_duration(time.time() - start)}")
