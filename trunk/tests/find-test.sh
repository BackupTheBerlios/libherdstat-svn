#!/bin/bash
source common.sh || exit 1
run_test "$(get_caller ${0})" "package search classes" \
"${srcdir}/src/find-test" "" || exit 1
indent
