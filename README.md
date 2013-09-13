Cosmic-Ray-Simulator
====================

This code simulates an experimental setup that aims to measure the lifetime of the muon.
This project was developed using C++ and CERN's ROOT Framework.


This cosmic Ray physics simulator:
----------------------------------

  1. Simulates the flux of muons crossing the detector
  
  2. Develop methods to estimate the energy loss of the particles crossing the materials, due to physical phenomena like Cerenkov radiation or Scintillation emission
  
  3. Simulate the propagation of the muon through the detector ( Scintillators and Water Tank)
  
  4. Create methods that simulate the creation and propagation of secondary particles produced by the interaction of the muon with matter
  
  5. Create a graphical user interface
  
  6. Make a scalable and modular simulator that can be easily integrable with other simulators, using the Classes framework of C++ and ROOT


Classes Framework:
------------------
`LMCParticle` - Deals with the definition of the properties of the propagated particle. Each element of the class is a particle.

`LMCstep` - Stores all the relevant data after a step is performed., such as energy losses or particles created. Each element is a step.

`LMCGeomN` - The experimental detector setup is defined on this class, by calling the different detector elements defined (LMCscintillator, LMCCerenkovTank)

`LMCPropagator` - Deals with the propagation of the particle. It must implement all the interactions with the detector geometry

`LMCfunctor` - Functions repository

`LMCMaterials` - Contains the materials to be used in the definition of the detector

`LMCconstants` - Class to store fundamental constants

`LMCstack` - Class that creates a stack to store the list of particles to be propagated and those created during propagation

`LMCsimGui` - Generates the Graphical user interface


Screenshots:
------------

![alt text](https://raw.github.com/luisbatalha/Cosmic-Ray-Simulator/master/screenshots/scr1.png "Screenshot GUI 1")

![alt text](https://raw.github.com/luisbatalha/Cosmic-Ray-Simulator/master/screenshots/scr3.png "Screenshot GUI 2")




_Special thanks to F. Barao for making this work possible._

