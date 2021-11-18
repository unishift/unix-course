#!/bin/bash

ESUB=./esub

regexp="$1"
substitution="$2"
string="$3"

diff <(echo "$string" | sed -E "s/${regexp}/${substitution}/") <(${ESUB} "${regexp}" "${substitution}" "${string}")