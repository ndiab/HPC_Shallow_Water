#include <stdlib.h>
#include <shalw.h>
#include <parse_args.hpp>
#include <init.h>
#include <mpi.h>
#include <share_lines.h>


void scat(void){
  /*Initialisation des indices*/
  /*int dec_t0 = rang*decalage; //decallage au temps t0.
  int dec_t1 = (size_x_base*size_y)+(rang*decalage); //décalage au temps 1
  int dec_rec_t0 = rang>0?size_y:0;//décalage dans le buffer de reception au temps 0
  int dec_rec_t1 = size_y*(rang==0?size_x_base:size_x) + (rang>0?size_y:0);//décalage dans le buffer de reception au temps 1
*/
  int dec_t0 = rang*decalage; //decallage au temps t0.
  int dec_t1 = (size_x_base*size_y)+(rang*decalage); //décalage au temps 1
  int dec_rec_t0 = rang>0?size_y:0;//décalage dans le buffer de reception au temps 0
  int dec_rec_t1 = size_y*size_x + (rang>0?size_y:0);//décalage dans le buffer de reception au temps 1

  /*Nous envoyons ensuite à tout nos processus leur part de données*/
  /*Scatter pour t=0*/
  MPI_Scatter(&hFil[dec_t0],decalage,MPI_DOUBLE,&hFil[dec_rec_t0],decalage,MPI_DOUBLE,0,MPI_COMM_WORLD);
  MPI_Scatter(&uFil[dec_t0],decalage,MPI_DOUBLE,&uFil[dec_rec_t0],decalage,MPI_DOUBLE,0,MPI_COMM_WORLD);
  MPI_Scatter(&vFil[dec_t0],decalage,MPI_DOUBLE,&vFil[dec_rec_t0],decalage,MPI_DOUBLE,0,MPI_COMM_WORLD);
  MPI_Scatter(&hPhy[dec_t0],decalage,MPI_DOUBLE,&hPhy[dec_rec_t0],decalage,MPI_DOUBLE,0,MPI_COMM_WORLD);
  MPI_Scatter(&uPhy[dec_t0],decalage,MPI_DOUBLE,&uPhy[dec_rec_t0],decalage,MPI_DOUBLE,0,MPI_COMM_WORLD);
  MPI_Scatter(&vPhy[dec_t0],decalage,MPI_DOUBLE,&vPhy[dec_rec_t0],decalage,MPI_DOUBLE,0,MPI_COMM_WORLD);
  /*Scatter pour t=1*/
  MPI_Scatter(&hFil[dec_t1],decalage,MPI_DOUBLE,&hFil[dec_rec_t1],decalage,MPI_DOUBLE,0,MPI_COMM_WORLD);
  MPI_Scatter(&uFil[dec_t1],decalage,MPI_DOUBLE,&uFil[dec_rec_t1],decalage,MPI_DOUBLE,0,MPI_COMM_WORLD);
  MPI_Scatter(&vFil[dec_t1],decalage,MPI_DOUBLE,&vFil[dec_rec_t1],decalage,MPI_DOUBLE,0,MPI_COMM_WORLD);
  MPI_Scatter(&hPhy[dec_t1],decalage,MPI_DOUBLE,&hPhy[dec_rec_t1],decalage,MPI_DOUBLE,0,MPI_COMM_WORLD);
  MPI_Scatter(&uPhy[dec_t1],decalage,MPI_DOUBLE,&uPhy[dec_rec_t1],decalage,MPI_DOUBLE,0,MPI_COMM_WORLD);
  MPI_Scatter(&vPhy[dec_t1],decalage,MPI_DOUBLE,&vPhy[dec_rec_t1],decalage,MPI_DOUBLE,0,MPI_COMM_WORLD);
}


void gat(void){
  
  /*t0*/
  MPI_Gather(&hFil[(rang>0?size_y:0)],decalage,MPI_DOUBLE,&hFil[rang*decalage],decalage,MPI_DOUBLE,0,MPI_COMM_WORLD); 
  MPI_Gather(&uFil[(rang>0?size_y:0)],decalage,MPI_DOUBLE,&uFil[rang*decalage],decalage,MPI_DOUBLE,0,MPI_COMM_WORLD);
  MPI_Gather(&vFil[(rang>0?size_y:0)],decalage,MPI_DOUBLE,&vFil[rang*decalage],decalage,MPI_DOUBLE,0,MPI_COMM_WORLD);
  MPI_Gather(&hPhy[(rang>0?size_y:0)],decalage,MPI_DOUBLE,&hPhy[rang*decalage],decalage,MPI_DOUBLE,0,MPI_COMM_WORLD);
  MPI_Gather(&uPhy[(rang>0?size_y:0)],decalage,MPI_DOUBLE,&uPhy[rang*decalage],decalage,MPI_DOUBLE,0,MPI_COMM_WORLD);
  MPI_Gather(&vPhy[(rang>0?size_y:0)],decalage,MPI_DOUBLE,&vPhy[rang*decalage],decalage,MPI_DOUBLE,0,MPI_COMM_WORLD);
  /*t1*/
  MPI_Gather(&hFil[(size_y*(rang==0?size_x_base:size_x))+(rang>0?size_y:0)],decalage,MPI_DOUBLE,&hFil[(size_x_base*size_y)+rang*decalage],decalage,MPI_DOUBLE,0,MPI_COMM_WORLD);
  MPI_Gather(&uFil[(size_y*(rang==0?size_x_base:size_x))+(rang>0?size_y:0)],decalage,MPI_DOUBLE,&uFil[(size_x_base*size_y)+rang*decalage],decalage,MPI_DOUBLE,0,MPI_COMM_WORLD);
  MPI_Gather(&vFil[(size_y*(rang==0?size_x_base:size_x))+(rang>0?size_y:0)],decalage,MPI_DOUBLE,&vFil[(size_x_base*size_y)+rang*decalage],decalage,MPI_DOUBLE,0,MPI_COMM_WORLD);
  MPI_Gather(&hPhy[(size_y*(rang==0?size_x_base:size_x))+(rang>0?size_y:0)],decalage,MPI_DOUBLE,&hPhy[(size_x_base*size_y)+rang*decalage],decalage,MPI_DOUBLE,0,MPI_COMM_WORLD);
  MPI_Gather(&uPhy[(size_y*(rang==0?size_x_base:size_x))+(rang>0?size_y:0)],decalage,MPI_DOUBLE,&uPhy[(size_x_base*size_y)+rang*decalage],decalage,MPI_DOUBLE,0,MPI_COMM_WORLD);
  MPI_Gather(&vPhy[(size_y*(rang==0?size_x_base:size_x))+(rang>0?size_y:0)],decalage,MPI_DOUBLE,&vPhy[(size_x_base*size_y)+rang*decalage],decalage,MPI_DOUBLE,0,MPI_COMM_WORLD);
}



void share_lines(void){
  MPI_Request req;
  if(rang>0){  
    	
    /*Envoi à p-1 la ligne locale 1 -- t0*/
    MPI_Isend(&hFil[size_y],size_y,MPI_DOUBLE,rang-1,TAG_hFil_L_t0,MPI_COMM_WORLD,&req);
    MPI_Isend(&uFil[size_y],size_y,MPI_DOUBLE,rang-1,TAG_uFil_L_t0,MPI_COMM_WORLD,&req);
    MPI_Isend(&vFil[size_y],size_y,MPI_DOUBLE,rang-1,TAG_vFil_L_t0,MPI_COMM_WORLD,&req);
    MPI_Isend(&hPhy[size_y],size_y,MPI_DOUBLE,rang-1,TAG_hPhy_L_t0,MPI_COMM_WORLD,&req);
    MPI_Isend(&uPhy[size_y],size_y,MPI_DOUBLE,rang-1,TAG_uPhy_L_t0,MPI_COMM_WORLD,&req);
    MPI_Isend(&vPhy[size_y],size_y,MPI_DOUBLE,rang-1,TAG_vPhy_L_t0,MPI_COMM_WORLD,&req);

    /*Envoi à p-1 la ligne locale 1 -- t1*/
    MPI_Isend(&hFil[(size_y*size_x)+size_y],size_y,MPI_DOUBLE,rang-1,TAG_hFil_L_t1,MPI_COMM_WORLD,&req);
    MPI_Isend(&uFil[(size_y*size_x)+size_y],size_y,MPI_DOUBLE,rang-1,TAG_uFil_L_t1,MPI_COMM_WORLD,&req);
    MPI_Isend(&vFil[(size_y*size_x)+size_y],size_y,MPI_DOUBLE,rang-1,TAG_vFil_L_t1,MPI_COMM_WORLD,&req);
    MPI_Isend(&hPhy[(size_y*size_x)+size_y],size_y,MPI_DOUBLE,rang-1,TAG_hPhy_L_t1,MPI_COMM_WORLD,&req);
    MPI_Isend(&uPhy[(size_y*size_x)+size_y],size_y,MPI_DOUBLE,rang-1,TAG_uPhy_L_t1,MPI_COMM_WORLD,&req);
    MPI_Isend(&vPhy[(size_y*size_x)+size_y],size_y,MPI_DOUBLE,rang-1,TAG_vPhy_L_t1,MPI_COMM_WORLD,&req);
  }
  if(rang<NP-1){
    /*Envoi à p+1 notre derniere ligne locale -- t0*/
    MPI_Isend(&hFil[(size_x-2)*size_y],size_y,MPI_DOUBLE,rang+1,TAG_hFil_H_t0,MPI_COMM_WORLD,&req);
    MPI_Isend(&uFil[(size_x-2)*size_y],size_y,MPI_DOUBLE,rang+1,TAG_uFil_H_t0,MPI_COMM_WORLD,&req);
    MPI_Isend(&vFil[(size_x-2)*size_y],size_y,MPI_DOUBLE,rang+1,TAG_vFil_H_t0,MPI_COMM_WORLD,&req);
    MPI_Isend(&hPhy[(size_x-2)*size_y],size_y,MPI_DOUBLE,rang+1,TAG_hPhy_H_t0,MPI_COMM_WORLD,&req);
    MPI_Isend(&uPhy[(size_x-2)*size_y],size_y,MPI_DOUBLE,rang+1,TAG_uPhy_H_t0,MPI_COMM_WORLD,&req);
    MPI_Isend(&vPhy[(size_x-2)*size_y],size_y,MPI_DOUBLE,rang+1,TAG_vPhy_H_t0,MPI_COMM_WORLD,&req);
     
    /*Envoi à p+1 notre derniere ligne locale -- t1*/
    /*MPI_Send(&hFil[(size_y*(rang==0?size_x_base:size_x))+(size_x-2)*size_y],size_y,MPI_DOUBLE,rang+1,TAG_hFil_H_t1,MPI_COMM_WORLD);
    MPI_Send(&uFil[(size_y*(rang==0?size_x_base:size_x))+(size_x-2)*size_y],size_y,MPI_DOUBLE,rang+1,TAG_uFil_H_t1,MPI_COMM_WORLD);
    MPI_Send(&vFil[(size_y*(rang==0?size_x_base:size_x))+(size_x-2)*size_y],size_y,MPI_DOUBLE,rang+1,TAG_vFil_H_t1,MPI_COMM_WORLD);
    MPI_Send(&hPhy[(size_y*(rang==0?size_x_base:size_x))+(size_x-2)*size_y],size_y,MPI_DOUBLE,rang+1,TAG_hPhy_H_t1,MPI_COMM_WORLD);
    MPI_Send(&uPhy[(size_y*(rang==0?size_x_base:size_x))+(size_x-2)*size_y],size_y,MPI_DOUBLE,rang+1,TAG_uPhy_H_t1,MPI_COMM_WORLD);
    MPI_Send(&vPhy[(size_y*(rang==0?size_x_base:size_x))+(size_x-2)*size_y],size_y,MPI_DOUBLE,rang+1,TAG_vPhy_H_t1,MPI_COMM_WORLD);
*/
    MPI_Isend(&hFil[(size_y*size_x)+(size_x-2)*size_y],size_y,MPI_DOUBLE,rang+1,TAG_hFil_H_t1,MPI_COMM_WORLD,&req);
    MPI_Isend(&uFil[(size_y*size_x)+(size_x-2)*size_y],size_y,MPI_DOUBLE,rang+1,TAG_uFil_H_t1,MPI_COMM_WORLD,&req);
    MPI_Isend(&vFil[(size_y*size_x)+(size_x-2)*size_y],size_y,MPI_DOUBLE,rang+1,TAG_vFil_H_t1,MPI_COMM_WORLD,&req);
    MPI_Isend(&hPhy[(size_y*size_x)+(size_x-2)*size_y],size_y,MPI_DOUBLE,rang+1,TAG_hPhy_H_t1,MPI_COMM_WORLD,&req);
    MPI_Isend(&uPhy[(size_y*size_x)+(size_x-2)*size_y],size_y,MPI_DOUBLE,rang+1,TAG_uPhy_H_t1,MPI_COMM_WORLD,&req);
    MPI_Isend(&vPhy[(size_y*size_x)+(size_x-2)*size_y],size_y,MPI_DOUBLE,rang+1,TAG_vPhy_H_t1,MPI_COMM_WORLD,&req);

    /*Réception de la dernière ligne locale de p+1 -- t0*/
    MPI_Recv(&hFil[(size_x-1)*size_y],size_y,MPI_DOUBLE,rang+1,TAG_hFil_L_t0,MPI_COMM_WORLD,&status);
    MPI_Recv(&uFil[(size_x-1)*size_y],size_y,MPI_DOUBLE,rang+1,TAG_uFil_L_t0,MPI_COMM_WORLD,&status);
    MPI_Recv(&vFil[(size_x-1)*size_y],size_y,MPI_DOUBLE,rang+1,TAG_vFil_L_t0,MPI_COMM_WORLD,&status);
    MPI_Recv(&hPhy[(size_x-1)*size_y],size_y,MPI_DOUBLE,rang+1,TAG_hPhy_L_t0,MPI_COMM_WORLD,&status);
    MPI_Recv(&uPhy[(size_x-1)*size_y],size_y,MPI_DOUBLE,rang+1,TAG_uPhy_L_t0,MPI_COMM_WORLD,&status);
    MPI_Recv(&vPhy[(size_x-1)*size_y],size_y,MPI_DOUBLE,rang+1,TAG_vPhy_L_t0,MPI_COMM_WORLD,&status);

    /*Réception de la dernière ligne locale de p+1 -- t1*/
    MPI_Recv(&hFil[(size_y*size_x)+(size_x-1)*size_y],size_y,MPI_DOUBLE,rang+1,TAG_hFil_L_t1,MPI_COMM_WORLD,&status);
    MPI_Recv(&uFil[(size_y*size_x)+(size_x-1)*size_y],size_y,MPI_DOUBLE,rang+1,TAG_uFil_L_t1,MPI_COMM_WORLD,&status);
    MPI_Recv(&vFil[(size_y*size_x)+(size_x-1)*size_y],size_y,MPI_DOUBLE,rang+1,TAG_vFil_L_t1,MPI_COMM_WORLD,&status);
    MPI_Recv(&hPhy[(size_y*size_x)+(size_x-1)*size_y],size_y,MPI_DOUBLE,rang+1,TAG_hPhy_L_t1,MPI_COMM_WORLD,&status);
    MPI_Recv(&uPhy[(size_y*size_x)+(size_x-1)*size_y],size_y,MPI_DOUBLE,rang+1,TAG_uPhy_L_t1,MPI_COMM_WORLD,&status);
    MPI_Recv(&vPhy[(size_y*size_x)+(size_x-1)*size_y],size_y,MPI_DOUBLE,rang+1,TAG_vPhy_L_t1,MPI_COMM_WORLD,&status);
  }
  
  if(rang>0){
    /*Réception de la ligne 0 de la part de p-1 -- t0*/
    MPI_Recv(&hFil[0],size_y,MPI_DOUBLE,rang-1,TAG_hFil_H_t0,MPI_COMM_WORLD,&status);
    MPI_Recv(&uFil[0],size_y,MPI_DOUBLE,rang-1,TAG_uFil_H_t0,MPI_COMM_WORLD,&status);
    MPI_Recv(&vFil[0],size_y,MPI_DOUBLE,rang-1,TAG_vFil_H_t0,MPI_COMM_WORLD,&status);
    MPI_Recv(&hPhy[0],size_y,MPI_DOUBLE,rang-1,TAG_hPhy_H_t0,MPI_COMM_WORLD,&status);
    MPI_Recv(&uPhy[0],size_y,MPI_DOUBLE,rang-1,TAG_uPhy_H_t0,MPI_COMM_WORLD,&status);
    MPI_Recv(&vPhy[0],size_y,MPI_DOUBLE,rang-1,TAG_vPhy_H_t0,MPI_COMM_WORLD,&status);

    /*Réception de la ligne 0 de la part de p-1 -- t1*/
    MPI_Recv(&hFil[size_y*size_x],size_y,MPI_DOUBLE,rang-1,TAG_hFil_H_t1,MPI_COMM_WORLD,&status);
    MPI_Recv(&uFil[size_y*size_x],size_y,MPI_DOUBLE,rang-1,TAG_uFil_H_t1,MPI_COMM_WORLD,&status);
    MPI_Recv(&vFil[size_y*size_x],size_y,MPI_DOUBLE,rang-1,TAG_vFil_H_t1,MPI_COMM_WORLD,&status);
    MPI_Recv(&hPhy[size_y*size_x],size_y,MPI_DOUBLE,rang-1,TAG_hPhy_H_t1,MPI_COMM_WORLD,&status);
    MPI_Recv(&uPhy[size_y*size_x],size_y,MPI_DOUBLE,rang-1,TAG_uPhy_H_t1,MPI_COMM_WORLD,&status);
    MPI_Recv(&vPhy[size_y*size_x],size_y,MPI_DOUBLE,rang-1,TAG_vPhy_H_t1,MPI_COMM_WORLD,&status);
    
  }

  MPI_Barrier(MPI_COMM_WORLD);
}
