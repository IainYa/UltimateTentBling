# UltimateTentBling
One Tent Bling to rule the world! - Using GPS to synchronise patterns across a site.

At our local hackspace (www.makerspace.org.uk), a few of us keep talking about having lights on our tents at Electromagnetic Field ([emfcamp.org](https://www.emfcamp.org/)) that are synchronised, with patterns flowing across them.  We dream of this happening across the entire site.

The intention of this project is to make an LED controller for individually addressable LED strings with syncronysed patterns that span the entire globe using GPS, making it usable for any event at any time, without the need for any site specific infrastructure.

Hopefully, this will even allow for lights to move around whilst remaining synchronised with the pattern.


## Hardware

Re-purposing a weather balloon RadioSonde or using a microcontroller and GPS module to control individually addressable LED strings.


## Patterns
The patterns are on a fixed schedule, based on UTC time and the GPS coordinates.  They repeat every 0.5 degrees of longitude and lattitude such that they should be seamless around the world.
Each pattern starts every 60 seconds and if it's a moving transition, it will take one hour to get to the other side of 0.5 degree area.  This works out approximately 15m/s.

### Transitions
- 0 - Instant change for all tents
- 1 - North to South
- 2 - South to North
- 3 - East to West
- 4 - West to East

### Effects
- 0 - 2 Colour Pattern
- 1 - Rainbow


#### Individual tent effects
- Single - Single colour
- Pulse - Fading back and forth between 2 colours.  Can also be used to fade a single colour on/off using black as one of the colours.  Globally this should look like a gentle wave of colour across the site.
- Strobe - Strobing a single colour at a fixed interval.  Globally this should look like a mexican wave.
- Random strobe - Strobing a single colour at a random interval.  Globally, this should look like a twinkling or shimmering pattern.
- Rainbow - Scrolling through rainbow colours.  Globally, this should look like a continuous rainbow moving across the site.
  

## Setup

### Hardware config file
  - GPS pins
  - LED output pin
  - LED String setup
    - LED Type
    - RGB/GRB order
  
### Patterns File
  - Start Minute
  - Transition
  - Tent Effect
  - Colour 1
  - Colour 2
  - Parameter 1 - e.g. delay time for Colour 1
  - Parameter 2 - e.g. fade time for Colour 1
  - Parameter 3 - e.g. delay time for Colour 2
  - Parameter 4 - e.g. fade time for Colour 2
