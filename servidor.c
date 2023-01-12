#include <stdio.h>
#include <string.h>
#include <stdlib.h>
extern acepta_conexion();
extern call_on_sock();
struct PDU
{
    char cabeza;
    char mensaje[2000];
};
main()
{
    FILE *fp;
    char comando[128];
    char response[1000];
    int dirlisten, conexion;
    struct PDU peticion, respuesta;
    dirlisten = socket_servidor(55055);
    printf("--------- INICIO DEL SERVIDOR ----------\n");
    while (1)
    {
        while ((conexion = acepta_conexion(dirlisten)) < 0)
            ;
        read(conexion, &peticion, sizeof(peticion));
        memset(response,0,sizeof response);
        fp = popen(peticion.mensaje, "r");
        //system(peticion.mensaje);
        if (fp == NULL)
        {
            strcpy(respuesta.mensaje, "Comando desconocido");
            exit(1);
        }

        while (fgets(comando, 128, fp) != NULL)
        {
            strcat(response, comando);
        }
        strcpy(respuesta.mensaje, response);
        printf("STRING FINAL: %s", respuesta.mensaje);
        write(conexion, &respuesta.mensaje, sizeof(respuesta.mensaje));
        //strcpy(respuesta.mensaje, "Mensaje recibido");
        pclose(fp);
        close(conexion);
    }
}
