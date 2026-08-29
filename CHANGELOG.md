# Changelog

All notable changes made in this fork are documented here, compiled from the
dated modification notes left in the source (`ATEM_tally_light.cpp` /
`.hpp`, marked `TS <date>`). This fork has not yet cut a formal release tag,
so everything below is grouped under **Unreleased**.

Base: forked from [AronHetLam/ATEM_tally_light_with_ESP8266](https://github.com/AronHetLam/ATEM_tally_light_with_ESP8266).

## [Unreleased] — Relay Shield / On Air Light build

### Added
- **"On Air Light" mode (`MODE_ON_AIR_LIVE`)** — 2024-03-28. A new LED1/relay
  mode that combines the switcher's streaming state with a configurable list
  of "live" source numbers. The relay only energizes when the ATEM is
  streaming **and** one of the listed sources is currently on Program. This
  lets other sources — a "starting soon" slate, pre-recorded media, etc. —
  sit on Program without triggering the physical on-air light. The source
  list is entered on the setup page as a comma-separated string (e.g.
  `1,2,5`, the pre-filled default) in a new **Tally On Air Live Sources**
  field, supporting up to 30 characters and source numbers 1–40.
- **"LED Off" mode (`MODE_OFF`)** — 2024-03-27. Lets LED2 be explicitly
  disabled, since this build's relay output only uses LED1.
- **Default tally number fallback** — 2024-03-28. If the tally number stored
  in EEPROM is out of the valid range, it now resets to a safe default
  instead of leaving an invalid value in place.

### Changed
- **LED1 pin mapping for the relay shield** — 2024-03-27. `PIN_RED1` and
  `PIN_BLUE1` are swapped from upstream (Red → D1 / GPIO5, Blue → D0 /
  GPIO16) to line up with the relay shield's control input. Anyone building
  the original bare-RGB-LED version from the upstream DIY guide with this
  fork's firmware needs to know about the swap.
- **No false relay trigger while connecting** — 2024-03-28. When LED1 is set
  to `MODE_ON_AIR_LIVE`, the "Connecting to WiFi" and "Connecting to
  Switcher" states now force the relay off instead of showing their usual
  status color. Matters for a build like this one that's powered
  continuously — without this, a boot or WiFi reconnect while the ATEM
  switcher itself is powered off could briefly energize the relay/light.
- **Setup page relabeling** — display name changed from "Tally Light" to
  "Tally & On Air Light"; LED1's existing "On Air" option relabeled "On Air
  Streaming" to sit next to the new "On Air Light" option; added an on-page
  note that both "On Air Streaming" and "On Air Light" require a direct
  connection to the switcher (not another tally unit); accent color changed
  (grey → green) to visually tell this build's setup page apart from stock
  firmware; footer credit updated to include the relay-shield / live-source
  modifications alongside the original author's copyright.

### Removed
- **`TALLY_TEST_SERVER` code paths** — 2024-03-27. All compile-time branches
  for the local tally test-server mode were removed from
  `ATEM_tally_light.cpp`/`.hpp`; this fork's main sketch always builds
  against a live ATEM connection.
- **`*_test_server` PlatformIO environments** — 2026-08-29. Since the source
  no longer branches on `TALLY_TEST_SERVER`, the `ESP8266_test_server`,
  `ESP32_test_server`, `ESP32_C3_test_server`, `ESP32_S2_test_server`,
  `ESP32_S3_test_server`, and `ATOM_Matrix_test_server` environments in
  `platformio.ini` were building firmware identical to their non-test-server
  counterparts, so they've been pruned. `default_envs` was updated to match.

### Build / environment notes
- **macOS toolchain pin** — 2024-03-27. Build with **ESP8266 board package
  version 3.02** on macOS specifically; newer versions fail to compile due
  to a Python 3 tooling incompatibility in the board support package.

### Known divergence from upstream
- Upstream later shipped its own fix for IPAddress not loading correctly at
  boot (commit `0c900aa`). This fork's baseline predates that fix and
  carries a different-shaped fix for the same symptom (comparing the stored
  address against `IPADDR_NONE` instead of re-parsing all four octets after
  EEPROM read). If this fork is ever rebased on newer upstream code, this
  spot in `setup()` will need manual reconciliation.

### Hardware
- **Relay-shield enclosure**: 3D-printed two-piece case (`enclosure/`) sized
  for the D1 Mini + relay shield stack, with a cutout for the relay's screw
  terminal block and the D1 Mini's micro-USB port, plus a separate
  keyhole-slotted mounting bracket. See [`HARDWARE.md`](HARDWARE.md).
