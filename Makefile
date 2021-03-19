BUILD_DIR := build

default: clox

repl-debug:
	@ $(MAKE) debug \
		&& build/cloxd

repl:
	@ $(MAKE) clox \
		&& clox

# Compile a debug build of clox
debug:
	@ $(MAKE) -f util/c.make NAME=cloxd MODE=debug SOURCE_DIR=src

# Compile clox
clox:
	@ $(MAKE) -f util/c.make NAME=clox MODE=release SOURCE_DIR=src
	@ cp build/clox clox # Copy the compiled interpreter to the top level
