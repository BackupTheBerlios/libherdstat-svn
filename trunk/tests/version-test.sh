#!/bin/bash
source common.sh || exit 1
run_test "$(get_caller ${0})" "version sorting" \
    "${srcdir}/src/version-test" \
    "${PORTDIR}/app-misc/foo" || exit 1
indent
