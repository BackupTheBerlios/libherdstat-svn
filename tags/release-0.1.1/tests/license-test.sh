#!/bin/bash
source common.sh || exit 1
run_test "$(get_caller ${0})" "LICENSE parsing" \
    "${srcdir}/src/license-test" \
    "${PORTDIR}/sys-libs/libfoo/libfoo-1.9.ebuild"
indent
