## GarbageBoy
Work in progress.

A garbage (haha) Gameboy emulator written in C++.

### Building

#### Install Dependencies
##### Debian Linux
```bash
sudo apt install libboost-all-dev
```

##### OSX
```bash
brew install boost
```

#### Compile
You can just run `make`.

### State
All the tests (except for interrupts and "cpu_instrs") pass. Interrupts need to be implemented.

