#include <stdio.h>

long int myhash(float valores[4]){
    long int hash2=0;
    int inicial=(int)valores[0];
    int destino=(int)valores[1];
    int hora=(int)valores[2];


  if(inicial==0 ){
    inicial=1;
  }
  if(destino==0){
    destino=1;
  }

  int top=inicial*230400;
  int down=(inicial-1)*230400;
  int topdes=destino+1*192;
  int downdes=destino*192;
  int tophora=hora*8;

  int diff=top-down;

  hash2= hash2 % 144;
  int hash=down+downdes+tophora;


//  printf("el hash es---------------------------> %li\n",hash);

  return hash;

}
