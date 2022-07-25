# TODO

## Resolutions and Scaling

> Let's get it rendering OK at *every* resolution

- [ ] Try just a box o' color (not for default, but folks can configure)
  - [ ] Add borders of a different color
- [x] Try partial alpha opacity, does it do anything? Or is it all or nothing?
  - > didn't show the image at all, could try again later tho?
- [ ] Grab a fun/funny background at 640 and use it as an example for fun
- [ ] Scales to a default screen percentage
- [ ] Scales to screen percentage defined in .ini
- [ ] Scales to screen percentage defined in .ini for specific resolution
- [ ] Scales to screen pixels defined in .ini
- [ ] Scales to screen pixels defined in .ini for specific resolution
- [ ] Console commands to scale art
- [ ] Console commands to swap art

## Unsorted

- [ ] Add Map names to Search index
- [ ] Update search to allow for "Categories": ["x", "y"] not just a single category (???) - less important

- [x] Update console command execution to work via global timers AND signals
      with the idea of turning off the global timers once sfall is fixed

- [ ] switch code back to Signals (using critical)

- [ ] selecttarget
- [ ] dude. or player. to set target to the dude
- [ ] cursor. for what's under the cursor
- [ ] critter. for critter under the cursor
- [ ] target. for the selected target
- [ ] allow third party X. prefix extensions
- [ ] events.h for signal names & send signals on console open, console close, and command execution
- [ ] scroll down when lines are too much to show in output
- [ ] pageup and pagedn
- [ ] left/right show cursor and allow delete in the command text
- [ ] some handy dandy standard terminal (emacs) shortcuts, e.g. ctrl-a ctrl-w
- [ ] .ini files with names of EVERYTHING extracted from files (NOT stored in memory)
- [ ] search command (need to get the PID for anything, like the hex in Skyrim)
- [ ] up and down go thru the command history

## More Informative Console

- [ ] show Obj ID
- [ ] show PID
- [ ] show just ID if it's a tile - oh, and elevation

## Commands

- [x] search
- [ ] get
- [ ] give
- [ ] view inventory

## Extra

At some point, consider `$` variables (_try not to tho lol, too much!_)
