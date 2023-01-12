#include <stdio.h>
#include <stdlib.h>
extern socket_cliente();
struct PDU
{
    char cabeza;
    char mensaje[2000];
};
main()
{
    char dato[255];
    int conexion;
    struct PDU peticion, respuesta;
    printf("--------- INICIO DE CLIENTE --------\n");
    while (1)
    {
        printf("Ingrese dato a enviar: ");
        fgets(dato, 255, stdin);
        conexion = socket_cliente("DESKTOP-KV4C0UB", 55055);
        strcpy(peticion.mensaje, dato);
        write(conexion, &peticion, sizeof(peticion));
        read(conexion, &respuesta, sizeof(respuesta));
        printf("RESPUESTA DE SERVIDOR: %s", respuesta.mensaje);
        close(conexion);
    }
}