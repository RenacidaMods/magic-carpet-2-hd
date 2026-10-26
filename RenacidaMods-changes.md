# RenacidaMods changes

What this fork changes in Magic Carpet 2 HD, and how each change works.

- Built on the `development` branch of [Magic Carpet 2 HD](https://github.com/thobbsinteractive/magic-carpet-2-hd) at commit `a1049b9b8`.
- Every change is its own commit, so it can be read, tested or taken on its own (for example with `git cherry-pick <commit>`).
- Most changes sit behind a setting that defaults to off, so the game behaves as before unless the setting is turned on. The [RenacidaMods release](https://github.com/RenacidaMods/magic-carpet-2-hd/releases) turns them on in its config.json.
- Each commit's description has the full detail, including what was measured and tested.

## Summary

| Change | Setting (default) | Commits | Files |
| --- | --- | --- | --- |
| [Smooth frames between game turns](#smooth-frames-between-game-turns) | `game.renderFps` (off) | [9bf62ed](https://github.com/RenacidaMods/magic-carpet-2-hd/commit/9bf62ed6d2b0137ae7b213d8fbde3c58b4f754e6), [b7a9658](https://github.com/RenacidaMods/magic-carpet-2-hd/commit/b7a965887bac008c049b3db85fd290c0df0d259a) | EventsFunctions.cpp, config files |
| [Smooth creatures and spells](#smooth-creatures-and-spells) | `game.smoothEntities` (off) | [d184e8f](https://github.com/RenacidaMods/magic-carpet-2-hd/commit/d184e8f13cc4b0325c9d8608461c56c16ee8e7d4) | EventsFunctions.cpp, config files |
| [Camera one turn sooner](#camera-one-turn-sooner) | part of `renderFps` | [021bc74](https://github.com/RenacidaMods/magic-carpet-2-hd/commit/021bc74425afd35ffc161f6b033b9fe55081203e) | EventsFunctions.cpp |
| [Sprites at their intended shape](#sprites-at-their-intended-shape) | `graphics.gameDetail.spriteAspectFix` (off) | [8b17795](https://github.com/RenacidaMods/magic-carpet-2-hd/commit/8b177953af386332d8afe438c4d5d04e11ab35e7) | GameRenderNG.cpp, config files |
| [Choice of SDL render driver](#choice-of-sdl-render-driver) | `graphics.renderDriver` (SDL's choice) | [1204e0f](https://github.com/RenacidaMods/magic-carpet-2-hd/commit/1204e0f823c89ea916983f95fcfbf6b5eea5c56e) | port_sdl_vga_mouse.cpp, config files |
| [Wide screen view](#wide-screen-view) | `graphics.gameDetail.widescreenFov` (off) | [2f9f033](https://github.com/RenacidaMods/magic-carpet-2-hd/commit/2f9f0333aab8563ed58e7ee0d92549806d66260f) | GameRenderNG.cpp/.h, config files |
| [Line clipping crash fix](#line-clipping-crash-fix) | always on | [8d44e19](https://github.com/RenacidaMods/magic-carpet-2-hd/commit/8d44e198ae8458b7b64534e72ebc104f59c77f18) | GameUI.cpp |
| [Close button quits](#close-button-quits) | always on | [c279b5d](https://github.com/RenacidaMods/magic-carpet-2-hd/commit/c279b5d1daea583cbf0599a8f0455e7e26119f2e), [8afc6fd](https://github.com/RenacidaMods/magic-carpet-2-hd/commit/8afc6fd76fafa555ed0d69277f2f18f40dc2497b) | port_sdl_vga_mouse.cpp |
| [Mouse left alone when the window isn't active](#mouse-left-alone-when-the-window-isnt-active) | always on | [5adbc12](https://github.com/RenacidaMods/magic-carpet-2-hd/commit/5adbc12d324927bdbdef24f23daf6fa28c48db02) | port_sdl_vga_mouse.cpp |
| [Start straight into a save](#start-straight-into-a-save) | `--load_save` command line option | [7c49bbb](https://github.com/RenacidaMods/magic-carpet-2-hd/commit/7c49bbbe013416013ecf3e2f668e24ef8911f28a) | EventsFunctions.cpp, Level.cpp/.h, CommandLineParser.cpp/.h |

"Config files" means the usual four places a setting is added: Config.h/.cpp and read_config.h/.cpp.

## Smooth frames between game turns

**Setting:** `"renderFps": 120` in `game` (0 or missing = off). Keep `maxGameFps` at 24.

**Why:** the game runs one turn per frame, so raising `maxGameFps` speeds the whole game up.

**How:** `DrawAndEventsInGame_47560` keeps one game turn every 1/`maxGameFps` second on a fixed timetable (`InBetweenTurnStart`) and draws extra frames between turns. Each frame moves the camera (position, yaw, pitch, roll) part of the way between turns, by the time the frame will be shown (`InBetweenPart`). The camera is put back before the game logic runs, so the game never sees the in-between values. Frames are left out when there's no time for them, so a slow PC keeps the normal game speed. Jumps over 0x800 (a new level or life) aren't smoothed. `BlendAndBlit_40F80` takes the frame limit as a parameter, so in-between frames skip `LockFps`. With `--log_level debug`, the frame rate, turns a second and frame times are logged every second.

## Smooth creatures and spells

**Setting:** `"smoothEntities": true` in `game` (needs `renderFps`).

**How:** at the start of each turn every entity's position is noted (`Entities_EA3E4`), and each frame places it part of the way to its new position, by the same part as the camera. Positions are put back before the game logic runs. An entity is left alone if its slot no longer holds the same id, class and model, or if it moved more than 0x800 (new, removed, reused or teleported). Animation frames and facing still change once a turn. No renderer change is needed: `GameRenderNG` already draws entities from `position_0x4C_76`.

## Camera one turn sooner

**Setting:** part of `renderFps`.

**Why:** `PlayerEvents_51BB0` copies the player's entity into the camera (`sub_57B20`) before `UpdateEntities_57730` moves the entity, so the camera is a turn behind, and interpolating from the last turn added another turn of lag.

**How:** `NextTurnCamera` works out the camera the next turn will copy (the same formula as `sub_57B20`, with no side effects), and frames move from this turn's camera towards it. That removes about 42 ms of steering lag and keeps the camera in step with smooth entities. It falls back to the old interpolation while paused, during the barrel roll, when the player is dead, or when another camera is in use.

## Sprites at their intended shape

**Setting:** `"spriteAspectFix": true` in `graphics.gameDetail`.

**Why:** the sprite art was drawn for 320x200 on a 4:3 screen, where each pixel is 1.2 times taller than wide. On square pixels every sprite comes out 1.2 times too wide (mana balls look oval).

**How:** `ChooseSprite` in GameRenderNG.cpp draws sprites at 5/6 of their width, keeping the height, which matches the world's scale. Measured on a mana ball at 3840x2160: 1.23 times wider than tall before, 1.02 after.

## Choice of SDL render driver

**Setting:** `"renderDriver": "direct3d11"` in `graphics` (empty = SDL's choice).

**How:** sets `SDL_HINT_RENDER_DRIVER` before `SDL_CreateRenderer`. SDL falls back to another driver if the named one isn't available, and the driver in use is logged at start. Showing a 3840x2160 frame took about 11 ms with SDL's default Direct3D 9 on Windows, and about 5.5 ms with Direct3D 11 (about 48 fps against 90 to 95 fps with `renderFps` 120, on an RTX 3090 and Ryzen 9 5950X). Direct3D 12 was slower (about 18 ms), OpenGL the same as Direct3D 9.

## Wide screen view

**Setting:** `"widescreenFov": true` in `graphics.gameDetail`. Off in the RenacidaMods release.

**How:** the NG renderer scales its focal length, pitch shift and sky by the view width, which zooms a 16:9 view in by about 22% compared with 4:3. With this setting they use the width of a 4:3 view of the same height instead, so a wide screen keeps the 4:3 view top to bottom and shows more at the sides. It can look a bit fish-eyed, and undrawn land can show in the corners when turning, which is why the release leaves it off.

## Line clipping crash fix

**Seen:** once, in a test at 3840x2160 with this fork's `widescreenFov` turned on (an access violation at `DrawLine_BD542+0x484`, found with a linker map). It hasn't been reproduced without this fork's changes, so it may not affect the main project.

**How:** `DrawLine_BD542` clips with 16-bit sums, so a line with far-apart ends, such as a help label's line to an entity far outside the view, can overflow them and write outside the screen buffer. `DrawLine_2BD10` now cuts the line to the drawing area in floating point (Liang-Barsky) first, and skips lines with no part on screen. The 320x200 path is unchanged.

## Close button quits

**How:** `PollSdlEvents` returned 0 on `SDL_QUIT`, which its caller ignores, so the window's close button did nothing. `SDL_QUIT` now throws `thread_exit_exception`, as `Exit_thread` does. Alt+F4 is left to the game (it's a cheat that destroys all the castles, as turican0 pointed out): `SDL_HINT_WINDOWS_NO_CLOSE_ON_ALT_F4` stops Windows turning it into a close.

## Mouse left alone when the window isn't active

**How:** `VGA_Set_mouse` warped the system cursor into the game window every frame, even when the window wasn't active, taking the mouse from whatever the player was using. The warp now only happens while the window has `SDL_WINDOW_INPUT_FOCUS`. Steering in play is unchanged.

## Start straight into a save

**Option:** `--load_save latest`, `--load_save 1` (the pause menu's save) or `--load_save 2` (the automatic save at the start of a level). `latest` picks the newer of the two by file time.

**How:** the level is read from `SVERn.DAT` and started as with `--set_level`. Because `LoadLevel_555D0` only overlays a level that's already set up, and loading too early left the screen at a low resolution, the save is loaded ten turns after the palette is set up, the same way the pause menu loads in play. The automatic level-start save is held back until then, so losing a life returns to the loaded game. `LoadLevel_555D0` gets `keepSavedSpells`, so the save's own spells and experience are kept. The campaign file (`SAVEn.GAM`) isn't loaded, so after the level the map screen shows default campaign progress.

## Credits

Magic Carpet 2 HD is by Tim Hobbs (thobbsinteractive), Tomáš Veselý (turican0) and its contributors, building on Tomáš's reverse engineering of the original game. These changes were made by RenacidaMods with Claude Code, and are under the same GNU General Public License version 3.
