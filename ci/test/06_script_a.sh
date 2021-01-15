#!/usr/bin/env bash
#
# Copyright (c) 2018-2020 The Californium Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

export LC_ALL=C.UTF-8

CALIFORNIUM_CONFIG_ALL="--enable-suppress-external-warnings --disable-dependency-tracking --prefix=$DEPENDS_DIR/$HOST --bindir=$BASE_OUTDIR/bin --libdir=$BASE_OUTDIR/lib"
if [ -z "$NO_WERROR" ]; then
  CALIFORNIUM_CONFIG_ALL="${CALIFORNIUM_CONFIG_ALL} --enable-werror"
fi
DOCKER_EXEC "ccache --zero-stats --max-size=$CCACHE_SIZE"

if [ -n "$CONFIG_SHELL" ]; then
  DOCKER_EXEC "$CONFIG_SHELL" -c "./autogen.sh"
else
  DOCKER_EXEC ./autogen.sh
fi

DOCKER_EXEC mkdir -p "${BASE_BUILD_DIR}"
export P_CI_DIR="${BASE_BUILD_DIR}"

DOCKER_EXEC "${BASE_ROOT_DIR}/configure" --cache-file=config.cache $CALIFORNIUM_CONFIG_ALL $CALIFORNIUM_CONFIG || ( (DOCKER_EXEC cat config.log) && false)

DOCKER_EXEC make distdir VERSION=$HOST

export P_CI_DIR="${BASE_BUILD_DIR}/californium-$HOST"

DOCKER_EXEC ./configure --cache-file=../config.cache $CALIFORNIUM_CONFIG_ALL $CALIFORNIUM_CONFIG || ( (DOCKER_EXEC cat config.log) && false)

set -o errtrace
trap 'DOCKER_EXEC "cat ${BASE_SCRATCH_DIR}/sanitizer-output/* 2> /dev/null"' ERR

if [[ ${USE_MEMORY_SANITIZER} == "true" ]]; then
  # MemorySanitizer (MSAN) does not support tracking memory initialization done by
  # using the Linux getrandom syscall. Avoid using getrandom by undefining
  # HAVE_SYS_GETRANDOM. See https://github.com/google/sanitizers/issues/852 for
  # details.
  DOCKER_EXEC 'grep -v HAVE_SYS_GETRANDOM src/config/californium-config.h > src/config/californium-config.h.tmp && mv src/config/californium-config.h.tmp src/config/californium-config.h'
fi

DOCKER_EXEC make $MAKEJOBS $GOAL || ( echo "Build failure. Verbose build follows." && DOCKER_EXEC make $GOAL V=1 ; false )

DOCKER_EXEC "ccache --version | head -n 1 && ccache --show-stats"
DOCKER_EXEC du -sh "${DEPENDS_DIR}"/*/
DOCKER_EXEC du -sh "${PREVIOUS_RELEASES_DIR}"
