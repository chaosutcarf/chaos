#!/usr/bin/env bash

DEPS_DIR="$(dirname $(realpath $0))"

# find additional deps to be installed.
pattern=$(mktemp)
to_install=$(mktemp)
echo "^$|^[ ]*#" > ${pattern}
apt list --installed | sed -r "s=([^/]+)/.*=(^|[ ])\1($|[ ])=g">>${pattern}
grep -Evf ${pattern} ${DEPS_DIR}/deps.apt > ${to_install}
rm ${pattern}

# install additional apt deps.
for dep in $(cat ${to_install}); do
    echo "install ${dep}"
    sudo apt-get install ${dep} -y
done
rm ${to_install}
