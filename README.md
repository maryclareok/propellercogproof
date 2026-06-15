•	README.md — start here for the project overview, repository layout, and build notes.
•	provecmm.c — the main CMM program. It launches the dummy and monitor workers with cognew(), receives their mailbox values, and prints the returned cog IDs.
•	dummy.cogc — the minimal dummy worker used as an additional-cog control. It records its own cog ID and runtime progress in shared hub memory.
•	provecmm.cogc — the monitor worker used for the worker-side cogid() check, debug-stage updates, and the Pin 20 LED runtime test described in the main article.
•	pressure_reader.cogc — the separate Pin 2 HIGH-LOW test used for the oscilloscope appendix. This is not the same build as the Pin 20 LED test.
•	provecmm.map — the linker-map evidence showing the separate dummy.cog and provecmm.cog load images, their sizes, and their hub load addresses.
•	cog_state_check.txt — the complete SpinSim trace and state output used to compare active Cogs 1 and 2 with inactive Cog 3.
•	provecmm.binary — the compiled binary used for the SpinSim run, when included in the repository.
Reader note: The Pin 20 LED code is in provecmm.cogc. The separate Pin 2 oscilloscope code is in pressure_reader.cogc. Keeping these files separate prevents the two physical tests from being mistaken for the same build.
