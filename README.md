# Shelly EM3 Battery Charger

## Why this project

This arduino project runs on a SONOFF S26 hardware in combination with the shelly EM3 power emeter and a Bluetti EB3A portable power station.

The system looks like this:
- A solar panel feeds electricity into a residential power grid
- The shelly EM3 power meter measures the power of the three power lines
- The SONOFF S26 device is connected to one power line
- The Bluetti EB3A portable power station 230V input is connected to the SONOFF S26 output

The aim of this project is to charge the battery in the portable power station when the solar panel feeds electricity into the power grid.
If the solar panel does not feed enough energy into the power grid, then the portable power station will be switched off.

