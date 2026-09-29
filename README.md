# Simulador de Cajero Automático en C

Aplicación de consola en C que simula las operaciones básicas de un cajero automático mediante un menú interactivo.

## Descripción
El programa autentica al usuario mediante un PIN de seguridad (máximo 3 intentos). Una vez iniciada la sesión, permite realizar las siguientes operaciones:
- Consultar saldo disponible ($500.000 iniciales).
- Depositar dinero.
- Retirar dinero (en múltiplos de $10.000).
- Ver los últimos 5 movimientos.

## Compilación y Ejecución
Para compilar:
```bash
gcc -std=c99 -Wall main.c -o cajero
