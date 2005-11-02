#!/bin/bash
source common.sh || exit 1
run_test "$(get_caller ${0})" "herds.xml parsing" \
    "${srcdir}/src/herds.xml-test" \
    "${TEST_DATA}/localstatedir/herds.xml" || exit 1
indent
