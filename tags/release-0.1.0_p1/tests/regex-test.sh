#!/bin/bash
source common.sh || exit 1
run_test "$(get_caller ${0})" "regular expressions" \
    "${srcdir}/src/regex-test" || exit 1
indent
