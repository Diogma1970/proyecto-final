#ifndef FUNCIONES_H
#define FUNCIONES_H

#define ZONAS 5
#define DIAS_HISTORICOS 30
#define LIMITE_CO2 9.0
#define LIMITE_SO2 0.5
#define LIMITE_NO2 0.2
#define LIMITE_PM25 0.025

typedef struct {
    char nombre[30];
    float co2[DIAS_HISTORICOS];
    float so2[DIAS_HISTORICOS];
    float no2[DIAS_HISTORICOS];
    float pm25[DIAS_HISTORICOS];
    float temp_actual;
    float viento_actual;
    float humedad_actual;
} Zona;

void cargarDatos(Zona *zonas);
void mostrarNivelesActuales(Zona *zonas);
void predecirContaminacion(Zona *zonas);
void emitirAlertas(Zona *zonas);
void calcularPromedios(Zona *zonas);
void generarRecomendaciones(Zona *zonas);
void exportarReporte(Zona *zonas);

#endif

void guardarDatosBinarios(Zona *zonas);
void cargarDatosBinarios(Zona *zonas);
