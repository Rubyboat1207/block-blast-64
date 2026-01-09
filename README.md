# Block Blast 64

This is a for-fun project made by Rubyboat to learn how to develop games for the Nintendo 64. This project uses libdragon, so to build just follow the normal build instructions for libdragon games on linux, I'm pretty sure that this build only works on linux, I use wsl2 and it works just fine. It has been tested on the ares emulator and on real console using an EverDrive64 X5. If you have any issues, feel free to write an issue or make a pull request.

If you want to use this project as reference or just look through it, the project is licensed under GPL 3. This means it will be open source and free forever.

## Build instructions

Clone the repository with submodules:

```sh
git clone git@github.com:Rubyboat1207/block-blast-64.git --recurse-submodules
```

Install the libdragon toolchain, go to their repository for up to date instructions, but this command should work as of 2026
```sh
npm i -g libdragon
```

Then cd into the project and initalize the libdragon project.
```sh
libdragon init
```

It should then be as simple as making the project
```sh
libdragon make
```

I've only ever tried building this on linux, so you'll probably need to use WSL2 for this if you're on windows.

## Assets

Every asset was made by Rubyboat1207 except for hand.png which is from Kenny Assets.