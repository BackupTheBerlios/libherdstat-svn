#!/bin/bash
source common.sh || exit 1
run_test "$(get_caller ${0})" "keyword sorting" \
    "${srcdir}/src/keyword-test" \
    "${TEST_DATA}/portdir/sys-libs/libfoo/libfoo-1.9.ebuild" || exit 1
indent
