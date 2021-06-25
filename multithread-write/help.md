# multithread-write
three parameters: num_threads, block_size, output_dir

default: 48, 1MB, .(current directory)

use `write` system call to write data.

## normal

with page cache.

## direct

without page cache

block_size must can be divided by 4096.

## sync

with page cache, sync mode on.
