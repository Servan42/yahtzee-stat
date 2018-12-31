#!/bin/bash
if [[ -e Rplots.pdf ]]; then
	rm Rplots.pdf	
fi
if [[ ! -e yamsStat ]]; then
	echo "Compilation..."
	make
	echo	
fi
echo "Running the simulation..."
./yamsStat
echo
echo "Generating graphs..."
Rscript RCode.R
while [[ ! -e Rplots.pdf ]]; do
	sleep 1
	#Waiting for the file to be created
done
rm *.data
see Rplots.pdf &
