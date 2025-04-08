#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <commons/log.h>
#include <commons/config.h>
#include <commons/string.h>
#include "utils.h"

t_log* iniciar_logger(char* archivo, char* nombre, bool mostrar_consola, t_log_level nivel);
t_config* iniciar_config(char* path);
void leer_consola(t_log* logger);
void paquete(int conexion);
void terminar_programa(int conexion, t_log* logger, t_config* config);

#endif