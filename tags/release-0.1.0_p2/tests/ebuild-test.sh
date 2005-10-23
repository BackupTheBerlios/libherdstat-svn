#!/bin/bash
source common.sh || exit 1
run_test "$(get_caller ${0})" "ebuild parsing" \
    "${srcdir}/src/ebuild-test" \
    "${PORTDIR}/sys-libs/libfoo/libfoo-1.9.ebuild" || exit 1
indent
