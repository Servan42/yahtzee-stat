# Yams/Yahtzee Statistical Study

## Description

This software is a personnal project that performs a statistical study on every lower section categorie of the Yams/Yahtzee dice game. It starts with a C simulation to record how many tosses are needed to score each categories. Then a R program generates histograms from the data.

## Requirements

You need to have at least the C compiler GCC, and have R installed on your computer to use the `Rscript` command.

## How to use

You can choose to run the [shell](run.sh) from a Unix terminal that will do everything or you. Or you can manually compile with the [Makefile](Makefile), run the simulation with `./yamsStat` and generate the graphs with `Rscript Rcode.R`.

## License and Maintainers

This software is a free software that is under the [MIT license](LICENSE) and is 
maintained by Servan CHARLOT.
