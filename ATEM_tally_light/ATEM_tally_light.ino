/*
    ON MAC USE ESP8266 BOARD VERSION 3.02               (DO NOT UPDATE!) (TS 3-27-24)
    REMOVED ALL COMPILE MACRO REFERENCES / USE OF TALLY_TEST_SERVER CODE (TS 3-27-24)
    See Modification Notes at the top of ATEM_tally_light.cpp file.      (TS 4-10-24)
    
    This program makes an ESP8266 into a wireless tally light system for ATEM switchers,
    by using Kasper Skårhøj's (<https://skaarhoj.com>) ATEM client libraries for Arduino.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    Portions Copyright (C) 2023 Aron N. Het Lam, aronhetlam@gmail.com
    
*/

#include "ATEM_tally_light.hpp"

/*
    Where did all the code go?!

    It's all moved to "ATEM_tally_light.cpp" for better compatibility with PlatformIO.
    
    This .ino file is kept for compatibility with the Arduino IDE
*/