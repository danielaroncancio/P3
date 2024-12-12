#!/bin/bash

# Establecemos que el código de retorno de un pipeline sea el del último programa con código de retorno
# distinto de cero, o cero si todos devuelven cero.
set -o pipefail
<<<<<<< HEAD

LLINDAR_RMAX=${1:-0.5}

=======
LLINDAR_RMAX=${1:-0.5}
>>>>>>> e10b619e3c3aaa16934bfead1b59ed9fb6e2bb5d
# Put here the program (maybe with path)
GETF0="get_pitch --llindar-rmax $LLINDAR_RMAX"

for fwav in pitch_db/train/*.wav; do
    ff0=${fwav/.wav/.f0}
    echo "$GETF0 $fwav $ff0 ----"
	$GETF0 $fwav $ff0 > /dev/null || { echo -e "\nError in $GETF0 $fwav $ff0" && exit 1; }
done

pitch_evaluate pitch_db/train/*.f0ref

exit 0
