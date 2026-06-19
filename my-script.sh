#!/usr/bin/env bash
set -e -o pipefail -u

apt update && apt install -y wget

OPENFOAM_VERSION=2506

 # Add the signing key, add the repository, update (check this):
 wget -q -O - https://dl.openfoam.com/add-debian-repo.sh | bash
 # Install OpenFOAM:
 apt update && apt install -y "openfoam$OPENFOAM_VERSION-dev"
 # Enable OpenFOAM by default in your system and apply now:
 echo alias openfoam="'source /usr/lib/openfoam/openfoam$OPENFOAM_VERSION/etc/bashrc'" >> ~/.bashrc