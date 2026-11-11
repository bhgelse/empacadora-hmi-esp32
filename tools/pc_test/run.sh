#!/bin/sh
# Compila y ejecuta la prueba de lógica en el PC (requiere gcc).
cd "$(dirname "$0")" || exit 1
gcc -std=gnu11 -Wall -Wextra -Istubs -I../../firmware/src -o test_logica test_logica.c -lm 2>&1 | grep -E "error" ; ./test_logica
