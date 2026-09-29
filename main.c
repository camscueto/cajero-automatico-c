#include <stdio.h>
#include <stdbool.h>

#define PIN_CORRECTO 1234
#define MAX_INTENTOS 3
#define SALDO_INICIAL 500000.0
#define MAX_MOVIMIENTOS 5
#define MULTIPLO_RETIRO 10000

typedef struct {
    char tipo[15];
    double monto;
} Movimiento;

int main(void) {
    int pinIngresado;
    bool autenticado = false;

    for (int intento = 1; intento <= MAX_INTENTOS; intento++) {
        printf("Ingrese su PIN (%d de %d intentos): ", intento, MAX_INTENTOS);
        if (scanf("%d", &pinIngresado) != 1) {
            while (getchar() != '\n');
            printf("Entrada invalida. Por favor, ingrese numeros.\n\n");
            continue;
        }

        if (pinIngresado == PIN_CORRECTO) {
            autenticado = true;
            printf("\n¡Acceso concedido! Bienvenido al Cajero Automatico.\n\n");
            break;
        } else {
            printf("PIN incorrecto.\n\n");
        }
    }

    if (!autenticado) {
        printf("Ha superado el numero maximo de intentos. El programa se cerrara.\n");
        return 0;
    }

    double saldo = SALDO_INICIAL;
    Movimiento movimientos[MAX_MOVIMIENTOS];
    int totalMovimientos = 0;
    int opcion;

    do {
        printf("===================================\n");
        printf("         CAJERO AUTOMATICO         \n");
        printf("===================================\n");
        printf("1. Consultar saldo\n");
        printf("2. Depositar dinero\n");
        printf("3. Retirar dinero\n");
        printf("4. Ver ultimos movimientos\n");
        printf("5. Salir\n");
        printf("Elija una opcion: ");

        if (scanf("%d", &opcion) != 1) {
            while (getchar() != '\n');
            printf("\nOpcion invalida. Intente de nuevo.\n\n");
            continue;
        }

        switch (opcion) {
            case 1:
                printf("\n--- CONSULTA DE SALDO ---\n");
                printf("Su saldo actual es: $%.2f\n\n", saldo);
                break;

            case 2: {
                double montoDeposito = 0.0;
                printf("\n--- DEPOSITO DE DINERO ---\n");
                while (montoDeposito <= 0) {
                    printf("Ingrese el monto a depositar (mayor a $0): ");
                    if (scanf("%lf", &montoDeposito) != 1 || montoDeposito <= 0) {
                        while (getchar() != '\n');
                        printf("Error: El monto debe ser un numero mayor a 0.\n");
                        montoDeposito = 0;
                    }
                }

                saldo += montoDeposito;

                if (totalMovimientos < MAX_MOVIMIENTOS) {
                    snprintf(movimientos[totalMovimientos].tipo, sizeof(movimientos[totalMovimientos].tipo), "Deposito");
                    movimientos[totalMovimientos].monto = montoDeposito;
                    totalMovimientos++;
                } else {
                    for (int i = 0; i < MAX_MOVIMIENTOS - 1; i++) {
                        movimientos[i] = movimientos[i + 1];
                    }
                    snprintf(movimientos[MAX_MOVIMIENTOS - 1].tipo, sizeof(movimientos[MAX_MOVIMIENTOS - 1].tipo), "Deposito");
                    movimientos[MAX_MOVIMIENTOS - 1].monto = montoDeposito;
                }

                printf("Deposito exitoso. Nuevo saldo: $%.2f\n\n", saldo);
                break;
            }

            case 3: {
                double montoRetiro = 0.0;
                bool montoValido = false;
                printf("\n--- RETIRO DE DINERO ---\n");

                while (!montoValido) {
                    printf("Ingrese el monto a retirar (multiplo de $%d): ", MULTIPLO_RETIRO);
                    if (scanf("%lf", &montoRetiro) != 1) {
                        while (getchar() != '\n');
                        printf("Error: Entrada invalida. Ingrese un valor numerico.\n");
                        continue;
                    }

                    if (montoRetiro <= 0) {
                        printf("Error: El monto debe ser mayor a 0.\n");
                    } else if (montoRetiro > saldo) {
                        printf("Error: Saldo insuficiente. Su saldo actual es: $%.2f\n", saldo);
                    } else if ((long long)montoRetiro % MULTIPLO_RETIRO != 0) {
                        printf("Error: El monto debe ser multiplo de $%d.\n", MULTIPLO_RETIRO);
                    } else {
                        montoValido = true;
                    }

                    if (!montoValido) {
                        printf("Intentelo nuevamente.\n\n");
                    }
                }

                saldo -= montoRetiro;

                if (totalMovimientos < MAX_MOVIMIENTOS) {
                    snprintf(movimientos[totalMovimientos].tipo, sizeof(movimientos[totalMovimientos].tipo), "Retiro");
                    movimientos[totalMovimientos].monto = montoRetiro;
                    totalMovimientos++;
                } else {
                    for (int i = 0; i < MAX_MOVIMIENTOS - 1; i++) {
                        movimientos[i] = movimientos[i + 1];
                    }
                    snprintf(movimientos[MAX_MOVIMIENTOS - 1].tipo, sizeof(movimientos[MAX_MOVIMIENTOS - 1].tipo), "Retiro");
                    movimientos[MAX_MOVIMIENTOS - 1].monto = montoRetiro;
                }

                printf("Retiro exitoso. Por favor retire su dinero. Nuevo saldo: $%.2f\n\n", saldo);
                break;
            }

            case 4:
                printf("\n--- ULTIMOS MOVIMIENTOS ---\n");
                if (totalMovimientos == 0) {
                    printf("No hay movimientos registrados aun.\n\n");
                } else {
                    for (int i = 0; i < totalMovimientos; i++) {
                        printf("%d. %s: $%.2f\n", i + 1, movimientos[i].tipo, movimientos[i].monto);
                    }
                    printf("\n");
                }
                break;

            case 5:
                printf("\nGracias por usar el Cajero Automatico. ¡Hasta pronto!\n");
                break;

            default:
                printf("\nOpcion invalida. Elija un numero entre 1 y 5.\n\n");
                break;
        }

    } while (opcion != 5);

    return 0;
}
