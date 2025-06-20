#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void agregarCliente(FILE *clientes); //Matias
void eliminarCliente(FILE *clientes);//Lucas
void buscarCliente(FILE *clientes);//Walter
void calcularGananciasTotales(FILE *clientes);//Maca
void modificarEstadoPedido(FILE *clientes);

struct cliente {
	char nombreApellido[50];
	int dni;
	short cantPedidos;
	char calle[20];
	short altura;
};

struct pedido {
	char talle[4];
	char prenda[20];
	int idPedido;
	float precio;
	char estado[2];
};

int main() {
	int opcion;

	do{
		printf("\n Ingrese una opcion: \n");
		printf("1. Agregar cliente\n");
		printf("2. Eliminar cliente\n");
		printf("3. Buscar cliente\n");
		printf("4. Calcular Ganancias totales\n");
		printf("5. Modificar estado de un pedido\n");
		printf("0. Salir\n");
		printf("Opcion seleccionada: ");
		scanf("%d", &opcion);
	
		switch(opcion) {
			case 1:	
				//agregarCliente();
				break;
			case 2:
				//eliminarCliente();
				break;
			case 3:
				//buscarCliente();
				break;
			case 4:
				//calcularGananciasTotales();
				break;
			case 5:
				//modificarEstadoPedido();
				break;
			case 0:
				printf("Saliendo del programa...\n");
				break;
			default:
				printf("Opcion invalida ingrese otra opcion\n");
		}
	} while(opcion != 0);
	
	return 0;
}