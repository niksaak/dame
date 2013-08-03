## This is a game about SPACEships

### Ship
Player ship is a conglomerate of **modules**, each with its' own purpose and
requirements.

### Module
Modules themself can wary by their sizes, each next size being two times bigger
than previous. Each module contains the **facility**, which defines what module
can do, and four **ports** through which facility can interact with surrounding
world.

### Facility
As stated above, facility defines what module can do. It can be *reactor*,
*engine*, *fuel tank*, *control core* or something with even cooler name.
Big modules can contain more than one smaller facility, but not all of them
are compatible.

### Port
Ports is the means for facility to physically interact with outside world. The
most common and basic kinds of ports are:
+ **Docking port**: Allows for two modules to be reversibly connected
  with eachother.
+ **Nozzle**: Allows engine modules to provide thrust.
+ **Shunting system**: Set of smaller nozzles providing attitude control.
+ **Armor plating**. Improves module hardiness.
*(TODO)*

