
| File                   | Purpose                                                                                                                                                          |
| ---------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `provecmm.c`           | Main CMM program. It launches the dummy and monitor workers using `cognew()`, reads their shared mailbox values, and prints the cog IDs reported by the workers. |
| `dummy.cogc`           | Minimal worker used as an additional-cog control. It records its own cog ID and runtime progress in shared hub memory.                                           |
| `provecmm.cogc`        | Monitor worker used for the worker-side `cogid()` check, debug-stage updates, and the Pin 20 LED runtime test described in the main article.                     |
| `provecmm.map`         | Linker map showing the separate `dummy.cog` and `provecmm.cog` load images, their sizes, and their load addresses in hub memory.                                 |
| `cog_state_check.txt`  | Complete SpinSim trace and cog-state output used to compare active Cogs 1 and 2 with inactive Cog 3.                                                             |
| `provecmm.binary`      | Compiled binary used for the SpinSim run, when included in the repository.                                                                                       |

