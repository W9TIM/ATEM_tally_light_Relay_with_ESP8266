# ATEM-tally-light — Relay Shield / On Air Light fork

[![License](https://img.shields.io/github/license/W9TIM/ATEM_tally_light_Relay_with_ESP8266)](LICENSE)

This is a fork of [AronHetLam/ATEM_tally_light_with_ESP8266](https://github.com/AronHetLam/ATEM_tally_light_with_ESP8266),
modified to drive a **relay-controlled USB tally/on-air light** from a Wemos
D1 Mini + relay shield, instead of an RGB LED. All credit for the original
wireless tally light design, the web setup UI, and the ATEM connection
libraries goes to Aron N. Het Lam — see [Credits](#credits).

**What's different here, in short:**
- Drives a relay (via a relay shield on the D1 Mini's headers) that switches
  power to a USB light, instead of an RGB LED.
- Adds an **On Air Light** mode: the relay only turns on when the switcher
  is streaming *and* one of a configurable list of sources is on Program —
  so a pre-roll/slate source can sit on Program without lighting the sign.
- Includes a 3D-printed enclosure for the D1 Mini + relay shield stack.

Full details: [`CHANGELOG.md`](CHANGELOG.md) for everything that changed and
why, [`HARDWARE.md`](HARDWARE.md) for pin mapping, relay/power wiring, and
the enclosure.

Everything below is the original project description, updated where this
fork's behavior differs.

---

Wireless tally light and 'On Air' sign for use with ATEM switchers. Connects
over WiFi using a D1 mini board (ESP8266 WiFi module). This solution is
__not__ limited by the ATEM switchers' connection limit, making it possible
to connect as many as you need.

__DIY guide__ for the base project (WiFi setup, general web UI) is available
in [upstream's wiki](https://github.com/AronHetLam/ATEM_tally_light_with_ESP8266/wiki/DIY-guide).
For this fork's relay-specific build (parts, pin mapping, power wiring,
enclosure), see [`HARDWARE.md`](HARDWARE.md).

# What does it do?
Once set up, it connects to an ATEM switcher over WiFi and functions as a
tally light or 'On Air' sign — in this fork's case, by switching a relay
that controls power to a USB light.

When the program is uploaded to the ESP8266, setup is done through a
webpage it serves over WiFi, where you can see status details and perform
the basic setup. Depending on whether it's connected to a known network, it
serves the webpage on its assigned IP, or on
[192.168.4.1](http://192.168.4.1) (default) over a softAP named "Tally & On
Air Light Setup".

As ATEM switchers only allow 5–8 simultaneous clients (model-dependent),
Tally Server functionality lets the system retransmit tally data to other
tally units, so only one connection from the switcher is needed. NOTE: the
ESP8266 isn't very powerful and is limited to 5 clients each (in some cases
even 5 might be too many).

## Connection and tally state indication
The different states of connection are signalled with LED/relay colors.

Color | Description
------|--------
BLUE | Connecting to WiFi
WHITE | Unable to connect to WiFi — serves softAP "Tally & On Air Light Setup", while still trying to connect.
PINK | Connecting to ATEM Switcher (connected to WiFi).
RED | Tally program
GREEN | Tally preview
OFF | Tally neither live nor preview (or no power).
ORANGE | Connected and running (status LED on addressable LED strip only).

> **This fork:** when LED1 is set to **On Air Light** mode, the relay is
> forced off (instead of showing BLUE/WHITE/PINK) during the WiFi- and
> switcher-connecting states, so it can't falsely energize the light while
> booting or reconnecting on a continuously-powered install. See
> [`CHANGELOG.md`](CHANGELOG.md).

## Modes of operation
By default the tally light works as a normal tally light would in a
professional environment, but other modes are available.

Mode | Description
-----|------------
Normal | As described in the table above.
Preview stay on | Tally will be green whenever not in program.
Program only | Tally will be off whenever not in program.
On Air Streaming | Red (relay on) when the switcher is streaming, off otherwise. Needs a direct connection to the switcher.
**On Air Light** *(this fork)* | Relay on only when the switcher is streaming **and** one of a configurable list of sources is on Program; off otherwise. Configured via the **Tally On Air Live Sources** field on the setup page (e.g. `1,2,5`). Needs a direct connection to the switcher. See [`CHANGELOG.md`](CHANGELOG.md).
**LED Off** *(this fork, LED2 only)* | Disables the second LED output entirely — used here since the relay build only has one physical output.

Note: only some ATEM models support streaming, so the On Air modes only
work with those models.

# Use Arduino IDE with ESP8266 module
See details at [ESP8266](https://github.com/esp8266/Arduino) on how to set
up and use ESP8266 modules like a regular Arduino board.

**macOS builders:** use ESP8266 board package **version 3.02** — newer
versions fail to compile on macOS due to a Python 3 tooling incompatibility.
See [`CHANGELOG.md`](CHANGELOG.md).

# Hardware
See [`HARDWARE.md`](HARDWARE.md) for the relay shield pin mapping, relay and
power wiring (including how to run the D1 Mini and the light off a single
5V supply instead of two separate power cables), and the 3D-printed
enclosure.

# Credits
Based on ATEM libraries for Arduino by [SKAARHOJ](https://www.skaarhoj.com/),
available at Git repo: [SKAARHOJ-Open-Engineering](https://github.com/kasperskaarhoj/SKAARHOJ-Open-Engineering)

Wireless tally light design, web setup UI, and Tally Server by
[Aron N. Het Lam](https://aronhetlam.github.io/) — original project:
[ATEM_tally_light_with_ESP8266](https://github.com/AronHetLam/ATEM_tally_light_with_ESP8266)

Relay shield support, On Air Light (live source) mode, and enclosure by
Tim Smith, 2024.

# License
GPL-3.0, inherited from the upstream project — see [`LICENSE`](LICENSE).
