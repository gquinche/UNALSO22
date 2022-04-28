#include <stdio.h>
#include "hashs.c"
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
# include <stdlib.h>


struct buscador{
    float id;
    float tiempo;

};
struct mistru{
  float origen;
  float destino;
  float hora;
} ;

int main()
{

  // todo este proceso esta bloqueado hasta que se escriba en el pipe

  FILE *fp;
  int pipeIn,pipeOut; // variables para fifo descriptors input y output
  float * array = malloc(4 * sizeof(float));
  struct buscador miBuscador;
  struct mistru Lector;
  char * nombreFifo1 = "fifoInput";
  char * nombreFifo2 = "fifoOutput";
  // O_NONBLOCK
  //incializa fifos
  mkfifo(nombreFifo1,0666);
  mkfifo(nombreFifo2,0666);

  pipeIn = open(nombreFifo1, O_RDONLY); // el open es donde se traba el proceso


  //lee y procesa solicitud

  // printf("%li bits read \n",read(pipeIn, &Lector, sizeof(struct mistru)));
  read(pipeIn, &Lector, sizeof(struct mistru));
  do{
  array[0]= Lector.origen;
  array[1]= Lector.destino;
  array[2]= Lector.hora;
  int id=myhash(array);
  //busca en archivo bin
  fp=fopen("tabla_datos.bin","rb");
  fseek(fp,id,SEEK_SET); //se ubica en la linea que el hash apunta
  fread(&miBuscador,sizeof(miBuscador),1,fp);  // lee en fp el tiempo correspondiente
  //respuesta a solicitud
  if(miBuscador.id==Lector.origen && Lector.origen != 0){
    pipeOut = open(nombreFifo2,O_WRONLY);
    write(pipeOut,&miBuscador.tiempo,sizeof(float));
  }
  else{
    pipeOut = open(nombreFifo2,O_WRONLY);
    miBuscador.tiempo = -1.0f;
    // printf("N/A \n");
    write(pipeOut,&miBuscador.tiempo,sizeof(float));
      }
  while( 0 == read(pipeIn, &Lector, sizeof(struct mistru))){continue;}
  }while(Lector.origen > 0);
fclose(fp);
free(array);
close(pipeIn);
close(pipeOut);

return 0;
}
