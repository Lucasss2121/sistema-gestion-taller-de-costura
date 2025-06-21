#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void procesarClientesYPedidos();
void eliminarCliente(FILE *clientes);
void buscarCliente(FILE *clientes);
int ingresarDni();
void mostrarCliente(FILE *clientes);
void modificarEstadoPedido(FILE *clientes);
void calcularGananciasTotales(FILE *clientes);

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
		printf("5. Modificar estado de un pedido\n");
		printf("6. Calcular Ganancias totales\n");
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
				buscarCliente(archivo);
				break;
            case 4:
				//mostrarClientes();
				break;
			case 5:
				//calcularGananciasTotales();
				break;
			case 6:
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

void buscarCliente(FILE *clientes) {
	int dniBuscado;
	struct cliente clienteTemp;
	struct pedido *pedidos;
	int i,e;
	char nombreArchivo[30];
    int banderaEncontrado = 0; //Bandera de validacion de cliente encontrado

	clientes = fopen("clientes.bin", "rb");
	if (clientes == NULL) {
		perror("No se pudo abrir el archivo de clientes.");
		return;
	}

	dniBuscado = ingresarDni(); //Valido que el DNI tenga 8 dijitos numericos

	while (fread(&clienteTemp, sizeof(struct cliente), 1, clientes) == 1) {
		pedidos = malloc(sizeof(struct pedido) * clienteTemp.cantPedidos);
		fread(pedidos, sizeof(struct pedido), clienteTemp.cantPedidos, clientes);


        if (clienteTemp.dni == dniBuscado) {// Si el DNI es valido y corresponde a un DNI de un cliente Asigno la bandera
            banderaEncontrado = 1;


			printf("\nCliente encontrado:\n");
			printf("Nombre y Apellido: %s\n", clienteTemp.nombreApellido);
			printf("DNI: %d\n", clienteTemp.dni);
			printf("Domicilio: %s %d\n", clienteTemp.calle, clienteTemp.altura);
			printf("Cantidad de pedidos: %d\n", clienteTemp.cantPedidos);

			for (i = 0; i < clienteTemp.cantPedidos; i++) {
				printf("\nPedido #%d:\n", i + 1);
				printf("  Prenda: %s\n", pedidos[i].prenda);
				printf("  Talle: %s\n", pedidos[i].talle);
				printf("  ID: %d\n", pedidos[i].idPedido);
				printf("  Precio: %.2f\n", pedidos[i].precio);
				printf("  Estado: %s\n", pedidos[i].estado);
			}

			free(pedidos);
		}
        
		free(pedidos);

	    if (!banderaEncontrado) {
            printf("\nEl cliente DNI %d no encontrado\n", dniBuscado);
        }
    }

	fclose(clientes);
}

int ingresarDni() { //Apunte flisol uso de scanf ingreso dni como char para validar la cantidad de caracteres y despues lo convierto en entero
    char dni[16];
    while (getchar() != '\n'); //Limpio el bufer

        while (1) {// Bucle infinito
                printf("Ingrese DNI del cliente a buscar: ");

                if (fgets(dni, sizeof(dni), stdin)){// Leo la linea del completa

                    dni[strcspn(dni, "\n")] = '\0'; // Quitar salto de l�nea

                if (strlen(dni) == 8 && strspn(dni, "0123456789") == 8) // Verifico que los dijitos ingresados sean numeros

                    return atoi(dni);//La funci�n atoi() lee la representaci�n de un n�mero entero de una cadena y devuelve su valor
                }
                    printf("DNI invalido. Intente de nuevo.\n");
                }
}