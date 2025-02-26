#!/usr/bin/env bash
#
# Copyright (c) 2018-2020 The Californium Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.
#
# Check for shellcheck warnings in shell scripts.

export LC_ALL=C

# Disabled warnings:
disabled=(
    SC2046 # Quote this to prevent word splitting.
    SC2086 # Double quote to prevent globbing and word splitting.
    SC2162 # read without -r will mangle backslashes.
)
disabled_gitian=(
    SC2094 # Make sure not to read and write the same file in the same pipeline.
    SC2129 # Consider using { cmd1; cmd2; } >> file instead of individual redirects.
)

EXIT_CODE=0

if ! command -v shellcheck > /dev/null; then
    echo "Skipping shell linting since shellcheck is not installed."
    exit $EXIT_CODE
fi

SHELLCHECK_CMD=(shellcheck --external-sources --check-sourced)
EXCLUDE="--exclude=$(IFS=','; echo "${disabled[*]}")"
SOURCED_FILES=$(git ls-files | xargs gawk '/^# shellcheck shell=/ {print FILENAME} {nextfile}')  # Check shellcheck directive used for sourced files
if ! "${SHELLCHECK_CMD[@]}" "$EXCLUDE" $SOURCED_FILES $(git ls-files -- '*.sh' | grep -vE 'src/(leveldb|secp256k1|univalue)/'); then
    EXIT_CODE=1
fi

if ! command -v yq > /dev/null; then
    echo "Skipping Gitian descriptor scripts checking since yq is not installed."
    exit $EXIT_CODE
fi

EXCLUDE_GITIAN=${EXCLUDE}",$(IFS=','; echo "${disabled_gitian[*]}")"
for descriptor in $(git ls-files -- 'contrib/gitian-descriptors/*.yml')
do
    script=$(basename "$descriptor")
    # Use #!/bin/bash as gitian-builder/bin/gbuild does to complete a script.
    echo "#!/bin/bash" > $script
    yq -r .script "$descriptor" >> $script
    if ! "${SHELLCHECK_CMD[@]}" "$EXCLUDE_GITIAN" $script; then
        EXIT_CODE=1
    fi
    rm $script
done

exit $EXIT_CODE
