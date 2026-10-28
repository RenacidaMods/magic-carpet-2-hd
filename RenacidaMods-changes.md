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
| [Turning by parts of an angle step](#turning-by-parts-of-an-angle-step) | part of `renderFps` | [5d16e33](https://github.com/RenacidaMods/magic-carpet-2-hd/commit/5d16e3334) | EventsFunctions.cpp, GameRenderInterface.h, GameRenderNG.cpp/.h |
| [Smooth camera curve](#smooth-camera-curve) | `game.smoothCamera` (off) | [e8e3246](https://github.com/RenacidaMods/magic-carpet-2-hd/commit/e8e3246c5) | EventsFunctions.cpp, PlayerInput.cpp/.h, config files |
| [Computer wizards' possess fix](#computer-wizards-possess-fix) | `game.fixAiPossess` (off) | [1f35287](https://github.com/RenacidaMods/magic-carpet-2-hd/commit/1f35287b5) | EventsFunctions.cpp, config files |
| [Sprites at their intended shape](#sprites-at-their-intended-shape) | `graphics.gameDetail.spriteAspectFix` (off) | [8b17795](https://github.com/RenacidaMods/magic-carpet-2-hd/commit/8b177953af386332d8afe438c4d5d04e11ab35e7), [5727b8c](https://github.com/RenacidaMods/magic-carpet-2-hd/commit/5727b8c6e) | GameRenderNG.cpp/.h, config files |
| [Faster frame display](#faster-frame-display) | always on | [f14e19a](https://github.com/RenacidaMods/magic-carpet-2-hd/commit/f14e19a4b) | port_sdl_vga_mouse.cpp/.h |
| [Sprites drawn on the render threads](#sprites-drawn-on-the-render-threads) | always on (with render threads over 640x480) | [f4ad549](https://github.com/RenacidaMods/magic-carpet-2-hd/commit/f4ad549b9) | GameRenderNG.cpp/.h |
| [Choice of SDL render driver](#choice-of-sdl-render-driver) | `graphics.renderDriver` (SDL's choice) | [1204e0f](https://github.com/RenacidaMods/magic-carpet-2-hd/commit/1204e0f823c89ea916983f95fcfbf6b5eea5c56e) | port_sdl_vga_mouse.cpp, config files |
| [Wide screen view](#wide-screen-view) | `graphics.gameDetail.widescreenFov` (off) | [2f9f033](https://github.com/RenacidaMods/magic-carpet-2-hd/commit/2f9f0333aab8563ed58e7ee0d92549806d66260f) | GameRenderNG.cpp/.h, config files |
| [Bigger marks on the maps](#bigger-marks-on-the-maps) | `graphics.gameDetail.mapMarkSize`, `graphics.gameDetail.minimapMarkSize` (1, the original size) | [bcff28e](https://github.com/RenacidaMods/magic-carpet-2-hd/commit/bcff28e57), [599fa46](https://github.com/RenacidaMods/magic-carpet-2-hd/commit/599fa463a) | GameUI.cpp/.h, EventsFunctions.cpp, config files |
| [Draw at the screen's resolution](#draw-at-the-screens-resolution) | `graphics.gameDetail.gameResWidth` and `gameResHeight` 0 | [1698882](https://github.com/RenacidaMods/magic-carpet-2-hd/commit/1698882cd) | read_config.cpp |
| [Render threads picked automatically](#render-threads-picked-automatically) | `graphics.threading.numberOfRenderThreads` 0 | [18b5671](https://github.com/RenacidaMods/magic-carpet-2-hd/commit/18b56715e) | read_config.cpp |
| [Line clipping crash fix](#line-clipping-crash-fix) | always on | [8d44e19](https://github.com/RenacidaMods/magic-carpet-2-hd/commit/8d44e198ae8458b7b64534e72ebc104f59c77f18) | GameUI.cpp |
| [F12 asks to quit](#f12-asks-to-quit) | always on | [9c5a9d3](https://github.com/RenacidaMods/magic-carpet-2-hd/commit/9c5a9d303), [02a0239](https://github.com/RenacidaMods/magic-carpet-2-hd/commit/02a023922) | port_sdl_vga_mouse.cpp |
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

## Turning by parts of an angle step

**Setting:** part of `renderFps`.

**Why:** the game keeps yaw, pitch and roll in whole steps (2048 to a full turn for yaw and roll), and the renderer only took whole steps. At 640x480 a step was about a pixel; at 3840x2160 one yaw step moves the picture about 6 pixels and one pitch step about 15, so slow turns moved in visible jumps, like a mouse on a very low DPI.

**How:** `PlaceInBetweenCamera` keeps the part of a step and passes it to the renderer (`GameRenderInterface::SetAngleFractions`, ignored by the HD and Original renderers). `GameRenderNG` uses it for the terrain grid, entity positions, sky, horizon shift, tile rotation and billboard lines, reading `sin_DB750` between two entries (`FineSin`). The game logic and the turn's own camera stay in whole steps; with part 0 every value is the original table entry. Measured at 3840x2160 (the same moment drawn at parts of a step): yaw 0.25, 0.5, 0.75 and 1 step moved the picture 2, 3, 5 and 6 pixels, pitch 3, 7, 11 and 15.

## Smooth camera curve

**Setting:** `"smoothCamera": true` in `game` (needs `renderFps`).

**Why:** with `renderFps` the in-between frames joined the turns' cameras with straight lines, so the speed of turning, looking up and down and banking jumped 24 times a second. The game also halves the pitch with whole numbers (`sub_57B20`), so steady looking moved in uneven steps (2, 3, 2, 3, ...).

**How:** yaw, pitch and roll follow a cubic Hermite curve through the turns, starting each turn at the average speed of the steps around it. For the yaw, the speed at the end of the turn uses the step after next, predicted from the live mouse (`x_WORD_E3760_mouse`, updated at every blit) with one more turn of the game's own steering (`PlayerEvents_51BB0`, `sub_5D530`), so turning bends towards the mouse before the next turn reads it. Predicting pitch and roll the same way made them less smooth (the hand moves on before the next turn reads it), so they end at their own step. The pitch keeps the half step that the halving drops. The mouse formula of `ComputeMousePlayerMovement_17060` moved into `MouseRollPitch` for the prediction. Measured at 3840x2160 with the mouse moved in slow waves (RMS of the speed change from frame to frame, as a share of the speed): yaw 9.1% to 7.0-7.5%, pitch 9.4-9.7% to 6.1-6.4%, roll 9.2-9.4% to 7.7-7.9%. It smooths the speed; it doesn't make the view answer the mouse any sooner.

## Sprites at their intended shape

**Setting:** `"spriteAspectFix": true` in `graphics.gameDetail`.

**Why:** most sprite art was drawn for 320x200 on a 4:3 screen, where each pixel is 1.2 times taller than wide. On square pixels those sprites come out 1.2 times too wide (mana balls look oval).

**How:** `ChooseSprite` in GameRenderNG.cpp draws sprites at 5/6 of their width, keeping the height, which matches the world's scale. Measured on a mana ball at 3840x2160: 1.23 times wider than tall before, 1.02 after. The spells don't all follow that rule: a dump of all 347 sprite definitions (original and HD art, the same shapes) shows possession, speed up, duel, gravity well, cave in and whirlwind drawn wide, but fireball, lightning, meteor, rebound, teleport, shield, beyond sight, tremor, invisible, alliance and the shared sprite of castle, heal, metamorph, fool's mana and magic mine drawn square. So for spells (class 9) and their effects (class 10), `NarrowSprite` narrows only when the first picture of the sprite definition is wider than 11:10, remembered per definition so an animation keeps one width.

## Computer wizards' possess fix

**Setting:** `"fixAiPossess": true` in `game`. Off, the computer wizards play exactly as the original.

**Why:** two quirks in Bullfrog's original AI (both in turican0's first decompile, untouched since). Mana balls: just after casting possess, if the wizard faced the ball within about 5 degrees, the AI made the ball its own on the spot (AI task 6, `sub_135C0`). The missile then skipped the ball, as it was no longer someone else's, and flew past it, and the ball changed colour a moment later, so it looked like a miss followed by a possession from nowhere. Flying home hurt: below half health the AI flies back to its castle (task 11, `sub_133B0`) and casts possess whenever it can, without checking there's anything ahead, so it fired at nothing along the way.

**How:** for mana balls, the wizard faces the ball exactly as it casts and the instant grab is skipped, so the missile locks on and possesses the ball when it lands, with the normal sound; it also stops casting at a ball that's already its own (the original kept casting up to 4 times in 1.5 seconds). Flying home, possess is cast only if the missile's own target search (`sub_67CB0`) would find something from where it would leave (`PossessTargetAhead`). Casts 5 to 30 degrees off still leave along the carpet's heading, as in the original. Measured in quiet test games on level 8: off, every near-exact mana cast had a missile that didn't lock on, and a hurt wizard cast possess about every 0.4 seconds on the way home; on, balls change owner 0.04 to 0.17 seconds after the cast, and 4 hurt wizards flew home with no casts at nothing. Not tested in multiplayer.

## F12 asks to quit

**Why:** quitting quickly was awkward: Alt+F4 is one of the game's cheats, and the mouse is kept inside the window (`SDL_SetWindowMouseRect`, hidden cursor) even when windowed, so reaching the close button meant Alt+Tab and finding the pointer. F11 and F12 aren't keys of the game (Alt+F2 to F10 are cheats, Ctrl with F keys changes settings).

**How:** F12 shows a Windows message box, "Quit the game now? Anything not saved is lost.", with Quit (Return) and Keep playing (Escape). While it asks, the mouse is let go and placed in the middle of the window, near the box, and the game window doesn't minimise (`SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS`). Keep playing puts back the mouse rectangle, grab, hidden cursor and the pointer's position (the game steers by it). Quit leaves through the game's own clean exit, as the close button does.

## Faster frame display

**Why:** profiling at 3840x2160 showed that showing a finished frame cost more than drawing it. On the game thread, `VGA_Blit` copied the 8 MB frame (0.5 ms), `SDL_BlitSurface` turned its 256 colours into RGB888 (about 3 ms) and `SDL_UpdateTexture` uploaded it (about 2.5 ms): about 6 ms a frame, against about 3 ms for the ground on all cores and up to 2.4 ms for the sprites.

**How:** `ConvertFrameToTexture` locks the streaming texture and fills it by bands of rows on the render threads and the game thread together, through a 256-entry table made from the surface's palette, copying the frame into `m_gamePalletisedSurface` in the same pass (other code still draws on that surface). `SubBlit` then skips `SDL_BlitSurface` and `SDL_UpdateTexture`; if the texture can't be locked it falls back to them. Every row matched `SDL_BlitSurface` exactly at 640x480, 320x200 and 3840x2160. Showing a frame now takes about 1.7 ms. Quiet runs at 3840x2160 with `renderFps` 120: level 8 went from 46 to 65 fps to 97 to 116, level 2 from 71 to 84 to 106 to 120 (the cap), level 5 from 91 to 107 to 100 to 120.

## Sprites drawn on the render threads

**Why:** with render threads over 640x480 the terrain is queued and drawn by bands of rows, but every tile with sprites flushed the queue (all threads wait) and then drew its sprites on the game thread: up to about 100 flushes and 2.4 ms of sprites a frame at 3840x2160.

**How:** the sprites go into the queue too. `DrawSpriteSpan` records each span (texels, screen start, view-line steps, length, mode, light, color, first and last row) before the next queued triangle, and the sprite's column table is copied once (`QueueSpriteColumns`). `FlushQueue` draws triangles and spans in queue order by bands of rows; a span is a straight line, so a band's pixels are one run, found by halving (`DrawQueuedSpan`). The queue is still drawn first when a sprite must be loaded (loading can free other sprites) and before a wizard's name tag (drawn straight on the screen). A temporary comparison found 0 of 8,294,400 pixels different in 118 frames on levels 8, 2 and 5 at 3840x2160 while banking. Speed at 4K on level 8 with no fps cap: about 3% more on average (104 to 105 fps before, 103 to 109 after, 4 alternating rounds each).

## Choice of SDL render driver

**Setting:** `"renderDriver": "direct3d11"` in `graphics` (empty = SDL's choice).

**How:** sets `SDL_HINT_RENDER_DRIVER` before `SDL_CreateRenderer`. SDL falls back to another driver if the named one isn't available, and the driver in use is logged at start. Showing a 3840x2160 frame took about 11 ms with SDL's default Direct3D 9 on Windows, and about 5.5 ms with Direct3D 11 (about 48 fps against 90 to 95 fps with `renderFps` 120, on an RTX 3090 and Ryzen 9 5950X). Direct3D 12 was slower (about 18 ms), OpenGL the same as Direct3D 9.

## Wide screen view

**Setting:** `"widescreenFov": true` in `graphics.gameDetail`. Off in the RenacidaMods release.

**How:** the NG renderer scales its focal length, pitch shift and sky by the view width, which zooms a 16:9 view in by about 22% compared with 4:3. With this setting they use the width of a 4:3 view of the same height instead, so a wide screen keeps the 4:3 view top to bottom and shows more at the sides. It can look a bit fish-eyed, and undrawn land can show in the corners when turning, which is why the release leaves it off.

## Bigger marks on the maps

**Settings:** `"mapMarkSize": 3` (the large map) and `"minimapMarkSize": 2` (the in-flight minimap) in `graphics.gameDetail`, 1 to 8.

**Why:** `DrawMinimapEntities_B_61A00` draws each creature, spell and person as a square of 1 or 2 pixels times `gameUiScale`. At 3840x2160 with `gameUiScale` 2 that's 2 to 4 pixels across, easy to miss on a big screen. Wild creatures are black on day levels and white on night and cave levels.

**How:** the map screen and the minimap set `mapMarkSizeNow` around their `DrawMinimapEntites_61880` call, and the square marks are drawn that many times as big, centred on their place. Each row is cut to the map's own span (`x_WORD_F4960`), so marks stay inside the round minimap. Icon marks (castles, flags) are left at their size, as enlarging them makes them blocky.

## Draw at the screen's resolution

**Setting:** `"gameResWidth": 0` and `"gameResHeight": 0` in `graphics.gameDetail`. The RenacidaMods release uses this.

**How:** with both at 0, `SetConfig` asks SDL for the desktop mode of the display the game is shown on (`displayIndex`, else the first), in real pixels, and draws at that: 3840x2160 on a 4K screen, 1920x1080 on a 1080p one. If SDL can't tell, it uses 1920x1080. Any other values work as before. The start-up log gives the game resolution next to the SDL renderer.

## Render threads picked automatically

**Setting:** `"numberOfRenderThreads": 0` in `graphics.threading` (with `isActive` true). The RenacidaMods release uses this.

**How:** `SetConfig` uses one fewer than the processor's cores (leaving one for the game thread), at most 6. On Windows the cores come from `GetLogicalProcessorInformationEx`, elsewhere half of `std::thread::hardware_concurrency`. Before, 0 meant one thread. Measured on a Ryzen 9 5950X at 3840x2160: 6 threads about 70 fps, 4 about 68, 7 about 66, and 8 or more slower (more coordination, and the threads spread over its two 8-core halves).

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
