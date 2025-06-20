#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void procesarClientesYPedidos();
void eliminarCliente(FILE *clientes);
void buscarCliente(FILE *clientes);
void calcularGananciasTotales(FILE *clientes);
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
	char estado[10];
};

int main() {
	int opcion;
    FILE *archivo = NULL;
	
    archivo = fopen("clientes.bin", "wb");
    if (archivo == NULL) {
        perror("Error al crear clientes.bin");
        return 1;
    }
		
	struct cliente ejemploCliente = {"Juan Perez", 12345678, 2, "Calle French", 123};
    struct pedido ejemploPedido[] = {
		{"m", "remera", 1, 111, "pendiente"},
		{"s", "pantalon", 2, 222, "pendiente"}
	};
		
    struct cliente ejemploCliente2 = {"Leandro Perez", 87654321, 3, "Calle San Martin", 321};
    struct pedido ejemploPedido2[] = {
		{"m", "buzo", 3, 111, "pendiente"},
		{"s", "pantalon", 4, 222, "pendiente"},
		{"xs", "remera", 5, 222, "pendiente"}
	};
		
	fwrite(&ejemploCliente, sizeof(struct cliente), 1, archivo);
	fwrite(&ejemploPedido, sizeof(struct pedido), ejemploCliente.cantPedidos, archivo);

	fwrite(&ejemploCliente2, sizeof(struct cliente), 1, archivo);
	fwrite(&ejemploPedido2, sizeof(struct pedido), ejemploCliente2.cantPedidos, archivo);
		
	fclose(archivo);

	do{
		printf("\n Ingrese una opcion: \n");
		printf("1. Agregar cliente\n");
		printf("2. Eliminar cliente\n");
		printf("3. Buscar cliente\n");
        printf("4. Mostrar clientes y crear txt\n");
		printf("5. Calcular Ganancias totales\n");
		printf("6. Modificar estado de un pedido\n");
		printf("0. Salir\n");
		printf("Opcion seleccionada: ");
		scanf("%d", &opcion);
	
		switch(opcion) {
			case 1:	
				//procesarClientesYPedidos();
				break;
			case 2:
				eliminarCliente(archivo);
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

void eliminarCliente(FILE *clientes) {
	FILE *temp = NULL;
	int clienteEliminar = 0;
	int i = 0;
	struct cliente clienteTemp;
	struct cliente *pedidoTemp;

	temp = fopen("temp.bin", "wb");
	if(temp == NULL) {
		perror("Error al abrir el archivo temp.bin\n");
	}

	clientes = fopen("clientes.bin", "rb");
	if(clientes == NULL) {
		perror("Error al abrir el archivo temp.bin\n");
	}

	printf("Ingrese el DNI del cliente a borrar: \n");
	scanf("%d", &clienteEliminar);

	while (fread(&clienteTemp, sizeof(struct cliente), 1, clientes) == 1) {
		pedidoTemp = malloc(sizeof(struct pedido) * clienteTemp.cantPedidos);
		fread(pedidoTemp, sizeof(struct pedido), clienteTemp.cantPedidos, clientes);
		
		if (clienteTemp.dni != clienteEliminar) {
			fwrite(&clienteTemp, sizeof(struct cliente), 1, temp);
			fwrite(pedidoTemp, sizeof(struct pedido), clienteTemp.cantPedidos, temp);

		} else {
			printf("Se borro el cliente correctamente\n");
		}

		free(pedidoTemp);
	}

	fclose(temp);
	fclose(clientes);	

	remove("clientes.bin");
	rename("temp.bin", "clientes.bin");
}