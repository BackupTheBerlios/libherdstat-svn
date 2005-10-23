#!/bin/bash
source common.sh || exit 1
run_test "$(get_caller ${0})" "metadata.xml parsing" \
    "${srcdir}/src/metadata.xml-test" \
    "${PORTDIR}/app-misc/foo/metadata.xml" || exit 1
indent
