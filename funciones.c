#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

void cargarDatos(Zona *zonas) {
    for (int i = 0; i < ZONAS; i++) {
        sprintf((zonas + i)->nombre, "Zona %d", i + 1);
        float temp = 25 + rand() % 10;
        float viento = 1 + rand() % 5;
        float humedad = 50 + rand() % 50;
        for (int j = 0; j < DIAS_HISTORICOS; j++) {
            // Aumentar la probabilidad de exceder el limite
            float r = (float)rand() / RAND_MAX;
            (zonas + i)->co2[j] = (r < 0.3) ? LIMITE_CO2 + (rand() % 3 + 1) : 5.0 + rand() % 5;
            r = (float)rand() / RAND_MAX;
            (zonas + i)->so2[j] = (r < 0.3) ? LIMITE_SO2 + ((float)(rand() % 10 + 1)) / 10 : 0.1 + ((float)(rand() % 5)) / 10;
            r = (float)rand() / RAND_MAX;
            (zonas + i)->no2[j] = (r < 0.3) ? LIMITE_NO2 + ((float)(rand() % 10 + 1)) / 100 : 0.1 + ((float)(rand() % 10)) / 100;
            r = (float)rand() / RAND_MAX;
            (zonas + i)->pm25[j] = (r < 0.3) ? LIMITE_PM25 + ((float)(rand() % 20 + 1)) / 1000 : 0.01 + ((float)(rand() % 20)) / 1000;
        }
        (zonas + i)->temp_actual = temp;
        (zonas + i)->viento_actual = viento;
        (zonas + i)->humedad_actual = humedad;
    }
}

void mostrarNivelesActuales(Zona *zonas) {
    for (int i = 0; i < ZONAS; i++) {
        printf("\n%s:\n", (zonas + i)->nombre);
        float co2 = (zonas + i)->co2[DIAS_HISTORICOS - 1];
        float so2 = (zonas + i)->so2[DIAS_HISTORICOS - 1];
        float no2 = (zonas + i)->no2[DIAS_HISTORICOS - 1];
        float pm25 = (zonas + i)->pm25[DIAS_HISTORICOS - 1];
        printf("CO2: %.2f (limite: %.2f)", co2, LIMITE_CO2);
        if (co2 == LIMITE_CO2)
            printf("En el limite");
        else if (co2 > LIMITE_CO2)
            printf("Excedido");
        printf("\n");
        printf("SO2: %.2f (limite: %.2f)", so2, LIMITE_SO2);
        if (so2 == LIMITE_SO2)
            printf("En el limite");
        else if (so2 > LIMITE_SO2)
            printf("Excedido");
        printf("\n");
        printf("NO2: %.2f (limite: %.2f)", no2, LIMITE_NO2);
        if (no2 == LIMITE_NO2)
            printf(" En el limite");
        else if (no2 > LIMITE_NO2)
            printf("Excedido");
        printf("\n");
        printf("PM2.5: %.4f (limite: %.4f)", pm25, LIMITE_PM25);
        if (pm25 == LIMITE_PM25)
            printf("En el limite");
        else if (pm25 > LIMITE_PM25)
            printf("Excedido");
        printf("\n");
        printf("Temperatura actual: %.2f °C\n", (zonas + i)->temp_actual);
        printf("Viento actual: %.2f m/s\n", (zonas + i)->viento_actual);
        printf("Humedad actual: %.2f %%\n", (zonas + i)->humedad_actual);
    }
}

float promedioPonderado(float *datos) {
    float suma = 0, peso_total = 0;
    for (int i = 0; i < DIAS_HISTORICOS; i++) {
        float peso = i + 1;
        suma += datos[i] * peso;
        peso_total += peso;
    }
    return suma / peso_total;
}

void predecirContaminacion(Zona *zonas) {
    for (int i = 0; i < ZONAS; i++) {
        printf("\nPrediccion para %s en 24h:\n", (zonas + i)->nombre);
        printf("CO2: %.2f\n", promedioPonderado((zonas + i)->co2));
        printf("SO2: %.2f\n", promedioPonderado((zonas + i)->so2));
        printf("NO2: %.2f\n", promedioPonderado((zonas + i)->no2));
        printf("PM2.5: %.4f\n", promedioPonderado((zonas + i)->pm25));
    }
}

void emitirAlertas(Zona *zonas) {
    for (int i = 0; i < ZONAS; i++) {
        float co2 = promedioPonderado((zonas + i)->co2);
        float so2 = promedioPonderado((zonas + i)->so2);
        float no2 = promedioPonderado((zonas + i)->no2);
        float pm25 = promedioPonderado((zonas + i)->pm25);
        int alerta = 0;
        if (co2 >= LIMITE_CO2 || so2 >= LIMITE_SO2 || no2 >= LIMITE_NO2 || pm25 >= LIMITE_PM25) {
            printf("\nAlertas para %s:\n", (zonas + i)->nombre);
            if (co2 == LIMITE_CO2)
                printf("Alerta: CO2 en el limite (%.2f)\n", co2);
            else if (co2 > LIMITE_CO2)
                printf("Alerta: CO2 excedido (%.2f)\n", co2);
            if (so2 == LIMITE_SO2)
                printf("Alerta: SO2 en el limite (%.2f)\n", so2);
            else if (so2 > LIMITE_SO2)
                printf("Alerta: SO2 excedido (%.2f)\n", so2);
            if (no2 == LIMITE_NO2)
                printf("Alerta: NO2 en el limite (%.2f)\n", no2);
            else if (no2 > LIMITE_NO2)
                printf("Alerta: NO2 excedido (%.2f)\n", no2);
            if (pm25 == LIMITE_PM25)
                printf("Alerta: PM2.5 en el limite (%.4f)\n", pm25);
            else if (pm25 > LIMITE_PM25)
                printf("Alerta: PM2.5 excedido (%.4f)\n", pm25);
        }
    }
}

void calcularPromedios(Zona *zonas) {
    for (int i = 0; i < ZONAS; i++) {
        float prom_co2 = promedioPonderado((zonas + i)->co2);
        float prom_so2 = promedioPonderado((zonas + i)->so2);
        float prom_no2 = promedioPonderado((zonas + i)->no2);
        float prom_pm25 = promedioPonderado((zonas + i)->pm25);
        printf("\nPromedios de %s (30 dias):\n", (zonas + i)->nombre);
        printf("CO2: %.2f | SO2: %.2f | NO2: %.2f | PM2.5: %.4f\n", prom_co2, prom_so2, prom_no2, prom_pm25);
    }
}

void generarRecomendaciones(Zona *zonas) {
    for (int i = 0; i < ZONAS; i++) {
        printf("\nRecomendaciones para %s:\n", (zonas + i)->nombre);
        float co2 = promedioPonderado((zonas + i)->co2);
        float so2 = promedioPonderado((zonas + i)->so2);
        float no2 = promedioPonderado((zonas + i)->no2);
        float pm25 = promedioPonderado((zonas + i)->pm25);
        int alerta = 0;
        if (co2 > LIMITE_CO2) {
            printf("- Reducir trafico vehicular (CO2 elevado, promover transporte publico y movilidad sostenible)\n");
            printf("- Fomentar el uso de energias limpias y renovables\n");
            alerta = 1;
        }
        if (so2 > LIMITE_SO2) {
            printf("- Cierre temporal de industrias (SO2 elevado, revisar regulaciones ambientales y promover tecnologia limpia)\n");
            printf("- Incentivar la responsabilidad social empresarial\n");
            alerta = 1;
        }
        if (no2 > LIMITE_NO2 || pm25 > LIMITE_PM25) {
            printf("- Suspender actividades al aire libre (NO2 o PM2.5 elevados, proteger poblacion vulnerable)\n");
            printf("- Promover campañas de concientizacion ambiental en escuelas y comunidades\n");
            alerta = 1;
        }
        if (!alerta) {
            printf("- Niveles aceptables. Continuar monitoreo.\n");
        }
        
    }
}

void exportarReporte(Zona *zonas) {
    FILE *archivo = fopen("reporte_contaminacion.txt", "w");
    if (!archivo) {
        printf("Error al crear el archivo.\n");
        return;
    }

    for (int i = 0; i < ZONAS; i++) {
        fprintf(archivo, "==================================================\n");
        fprintf(archivo, "Zona: %s\n", (zonas + i)->nombre);
        fprintf(archivo, "--------------------------------------------------\n");
        float co2 = (zonas + i)->co2[DIAS_HISTORICOS - 1];
        float so2 = (zonas + i)->so2[DIAS_HISTORICOS - 1];
        float no2 = (zonas + i)->no2[DIAS_HISTORICOS - 1];
        float pm25 = (zonas + i)->pm25[DIAS_HISTORICOS - 1];
        fprintf(archivo, "Monitoreo actual:\n");
        fprintf(archivo, "  CO2:    %7.2f (limite: %5.2f)", co2, LIMITE_CO2);
        if (co2 == LIMITE_CO2)
            fprintf(archivo, "  [En el limite]");
        else if (co2 > LIMITE_CO2)
            fprintf(archivo, "  [Excedido]");
        fprintf(archivo, "\n");
        fprintf(archivo, "  SO2:    %7.2f (limite: %5.2f)", so2, LIMITE_SO2);
        if (so2 == LIMITE_SO2)
            fprintf(archivo, "  [En el limite]");
        else if (so2 > LIMITE_SO2)
            fprintf(archivo, "  [Excedido]");
        fprintf(archivo, "\n");
        fprintf(archivo, "  NO2:    %7.2f (limite: %5.2f)", no2, LIMITE_NO2);
        if (no2 == LIMITE_NO2)
            fprintf(archivo, "  [En el limite]");
        else if (no2 > LIMITE_NO2)
            fprintf(archivo, "  [Excedido]");
        fprintf(archivo, "\n");
        fprintf(archivo, "  PM2.5:  %7.4f (limite: %7.4f)", pm25, LIMITE_PM25);
        if (pm25 == LIMITE_PM25)
            fprintf(archivo, "  [En el limite]");
        else if (pm25 > LIMITE_PM25)
            fprintf(archivo, "  [Excedido]");
        fprintf(archivo, "\n");
        fprintf(archivo, "  Temperatura: %.2f C\n", (zonas + i)->temp_actual);
        fprintf(archivo, "  Viento:      %.2f m/s\n", (zonas + i)->viento_actual);
        fprintf(archivo, "  Humedad:     %.2f %%\n", (zonas + i)->humedad_actual);
        fprintf(archivo, "--------------------------------------------------\n");
        // Promedios historicos (ultimos 30 dias)
        fprintf(archivo, "Promedios historicos (30 dias, incluye el actual):\n");
        float suma_co2 = 0, suma_so2 = 0, suma_no2 = 0, suma_pm25 = 0;
        for (int d = 0; d < DIAS_HISTORICOS; d++) {
            suma_co2 += (zonas + i)->co2[d];
            suma_so2 += (zonas + i)->so2[d];
            suma_no2 += (zonas + i)->no2[d];
            suma_pm25 += (zonas + i)->pm25[d];
        }
        fprintf(archivo, "  CO2:    %7.2f\n", suma_co2 / DIAS_HISTORICOS);
        fprintf(archivo, "  SO2:    %7.2f\n", suma_so2 / DIAS_HISTORICOS);
        fprintf(archivo, "  NO2:    %7.2f\n", suma_no2 / DIAS_HISTORICOS);
        fprintf(archivo, "  PM2.5:  %7.4f\n", suma_pm25 / DIAS_HISTORICOS);
        fprintf(archivo, "--------------------------------------------------\n");
        // Predicciones
        float pred_co2 = promedioPonderado((zonas + i)->co2);
        float pred_so2 = promedioPonderado((zonas + i)->so2);
        float pred_no2 = promedioPonderado((zonas + i)->no2);
        float pred_pm25 = promedioPonderado((zonas + i)->pm25);
        fprintf(archivo, "Prediccion en 24h:\n");
        fprintf(archivo, "  CO2:    %7.2f\n", pred_co2);
        fprintf(archivo, "  SO2:    %7.2f\n", pred_so2);
        fprintf(archivo, "  NO2:    %7.2f\n", pred_no2);
        fprintf(archivo, "  PM2.5:  %7.4f\n", pred_pm25);
        fprintf(archivo, "--------------------------------------------------\n");
        // Advertencias
        int hay_alerta = 0;
        fprintf(archivo, "Advertencias:\n");
        if (pred_co2 == LIMITE_CO2)
            { fprintf(archivo, "  - CO2 en el limite (%.2f)\n", pred_co2); hay_alerta = 1; }
        else if (pred_co2 > LIMITE_CO2)
            { fprintf(archivo, "  - CO2 excedido (%.2f)\n", pred_co2); hay_alerta = 1; }
        if (pred_so2 == LIMITE_SO2)
            { fprintf(archivo, "  - SO2 en el limite (%.2f)\n", pred_so2); hay_alerta = 1; }
        else if (pred_so2 > LIMITE_SO2)
            { fprintf(archivo, "  - SO2 excedido (%.2f)\n", pred_so2); hay_alerta = 1; }
        if (pred_no2 == LIMITE_NO2)
            { fprintf(archivo, "  - NO2 en el limite (%.2f)\n", pred_no2); hay_alerta = 1; }
        else if (pred_no2 > LIMITE_NO2)
            { fprintf(archivo, "  - NO2 excedido (%.2f)\n", pred_no2); hay_alerta = 1; }
        if (pred_pm25 == LIMITE_PM25)
            { fprintf(archivo, "  - PM2.5 en el limite (%.4f)\n", pred_pm25); hay_alerta = 1; }
        else if (pred_pm25 > LIMITE_PM25)
            { fprintf(archivo, "  - PM2.5 excedido (%.4f)\n", pred_pm25); hay_alerta = 1; }
        if (!hay_alerta) fprintf(archivo, "  - Sin advertencias\n");
        fprintf(archivo, "--------------------------------------------------\n");
        // Recomendaciones
        fprintf(archivo, "Recomendaciones:\n");
        int rec = 0;
        if (pred_co2 > LIMITE_CO2) {
            fprintf(archivo, "  - Reducir trafico vehicular (CO2 elevado, promover transporte publico y movilidad sostenible)\n");
            fprintf(archivo, "  - Fomentar el uso de energias limpias y renovables\n");
            rec = 1;
        }
        if (pred_so2 > LIMITE_SO2) {
            fprintf(archivo, "  - Cierre temporal de industrias (SO2 elevado, revisar regulaciones ambientales y promover tecnologia limpia)\n");
            fprintf(archivo, "  - Incentivar la responsabilidad social empresarial\n");
            rec = 1;
        }
        if (pred_no2 > LIMITE_NO2 || pred_pm25 > LIMITE_PM25) {
            fprintf(archivo, "  - Suspender actividades al aire libre (NO2 o PM2.5 elevados, proteger poblacion vulnerable)\n");
            fprintf(archivo, "  - Promover campanas de concientizacion ambiental en escuelas y comunidades\n");
            rec = 1;
        }
        if (!rec) {
            fprintf(archivo, "  - Niveles aceptables. Continuar monitoreo y educacion ambiental.\n");
        }
       
    }

    fclose(archivo);
    printf("Reporte exportado exitosamente.\n");
}

void guardarDatosBinarios(Zona *zonas) {
    FILE *archivo = fopen("datos_zonas.bin", "wb");
    if (!archivo) {
        printf("Error al guardar los datos en binario.\n");
        return;
    }
    fwrite(zonas, sizeof(Zona), ZONAS, archivo);
    fclose(archivo);
    printf("Datos guardados exitosamente en binario.\n");
}

void cargarDatosBinarios(Zona *zonas) {
    FILE *archivo = fopen("datos_zonas.bin", "rb");
    if (!archivo) {
        printf("No se encontro un archivo binario previo. Se generaran datos aleatorios.\n");
        cargarDatos(zonas);
        guardarDatosBinarios(zonas);
        return;
    }
    fread(zonas, sizeof(Zona), ZONAS, archivo);
    fclose(archivo);
    printf("Datos cargados exitosamente desde archivo binario.\n");
}