#include <stdio.h>
#include "funciones.h"

int main() {
    Zona zonas[ZONAS];
    int opcion;

    cargarDatosBinarios(zonas);

    do {
        printf("\n=== Sistema de Gestion de Contaminacion del Aire ===\n");
        printf("1. Monitorear niveles actuales\n");
        printf("2. Predecir niveles futuros\n");
        printf("3. Calcular promedios historicos\n");
        printf("4. Generar recomendaciones\n");
        printf("5. Exportar reporte\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: mostrarNivelesActuales(zonas); break;
            case 2: predecirContaminacion(zonas); break;
            case 3: calcularPromedios(zonas); break;
            case 4: generarRecomendaciones(zonas); break;
            case 5: exportarReporte(zonas); break;
            case 0: printf("Saliendo del sistema...\n"); break;
            default: printf("Opcion invalida.\n");
        }
    } while (opcion != 0);

    return 0;
}