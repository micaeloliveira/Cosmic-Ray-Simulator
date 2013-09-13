#!/usr/bin/env tcsh
echo "Running Simulation..."
make clean ; make -j libs ; make bin/tprop.exe ; bin/tprop.exe

