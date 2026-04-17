#include "client.h"
#include <readline/readline.h>
#include "utils.h"

int main(void)
{
	t_log* loggersito = log_create("tp0.log","Cliente", true,LOG_LEVEL_INFO);
	t_config* configsito = config_create ("cliente.config");
	char* clave = config_get_string_value(configsito,"CLAVE");
	char* ip = config_get_string_value(configsito,"IP");
	char* puerto = config_get_string_value(configsito,"PUERTO");

	int socket_cliente = crear_conexion(ip, puerto);
	enviar_mensaje(clave,socket_cliente);
	char* lectura;
	t_paquete* paquetito=crear_paquete();
	do
	{
		lectura=readline(">");
		
		if (!strcmp(lectura,"enviar"))
		{
			enviar_paquete(paquetito,socket_cliente);
			log_info(loggersito, "Envie el paquete");
		}else
		{
			agregar_a_paquete(paquetito,lectura,strlen(lectura)+1);
			log_info(loggersito, "Agrege al paquete");
		}
		
		
	} while (strcmp(lectura,"salir"));
	log_info(loggersito, "Sali del while");
	liberar_conexion(socket_cliente);
	eliminar_paquete(paquetito);
	log_destroy(loggersito);
	config_destroy(configsito);
}