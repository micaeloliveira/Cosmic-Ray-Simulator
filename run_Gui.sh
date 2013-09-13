#!/usr/bin/env tcsh
echo "Running Simulation..."
make clean ; make -j libs ; make bin/ggui.exe ; bin/ggui.exe

