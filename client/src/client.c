#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger ("tp0.log", "CLIENT_H_", true, LOG_LEVEL_INFO);
	
	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"

	log_info (logger, "Hola! Soy un log");


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config ("cliente.config");

	if (config == NULL){
	abort();}

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value(config, "PUERTO");
	valor = config_get_string_value(config, "VALOR");

	// Loggeamos el valor de config

	log_info(logger, "IP: %s", ip);
	log_info(logger, "PUERTO: %s", puerto);
	log_info(logger, "CLAVE: %s", valor);

	if (!ip) puts("ip es NULL");
	if (!puerto) puts("puerto es NULL");
	if (!valor) puts("valor es NULL");

	printf("IP: %s\nPUERTO: %s\nCLAVE: %s\n", ip, puerto, valor);

	if (ip == NULL || puerto == NULL || valor == NULL) {
		log_error(logger, "Algún valor del config es NULL");
		abort();
	}


	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor, conexion);
	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(char* archivo, char* nombre, bool mostrar_consola, t_log_level nivel)
{
    return log_create(archivo, nombre, mostrar_consola, nivel);
}

t_config* iniciar_config(char* path)
{
    return config_create(path);
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	leido = readline("> ");

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío

    while (leido != NULL && strlen(leido) > 0) {
        log_info(logger, "%s", leido);
        free(leido);
        leido = readline("> ");
    }

    free(leido);

	// ¡No te olvides de liberar las lineas antes de regresar!

}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete = crear_paquete();

	// Leemos y esta vez agregamos las lineas al paquete

	leido = readline("> ");
    while (leido != NULL && strlen(leido) > 0) {
        agregar_a_paquete(paquete, leido, strlen(leido) + 1);
        free(leido);
        leido = readline("> ");
    }

	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!

	free(leido);

    enviar_paquete(paquete, conexion);
    eliminar_paquete(paquete);
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */

	if (conexion >= 0) {
        close(conexion);
    }

    if (logger != NULL) {
        log_info(logger, "Finalizando programa...");
        log_destroy(logger);
    }

    if (config != NULL) {
        config_destroy(config);
		config = NULL;
    }
}
