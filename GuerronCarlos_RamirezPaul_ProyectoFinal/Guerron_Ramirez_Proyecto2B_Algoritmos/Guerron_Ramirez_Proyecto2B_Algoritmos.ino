
#include "DatosSensores.h"
#include <SoftwareSerial.h>
#include <ListLib.h>
//variables
// datos de prueba
//float datos_prueba [5]={6.2,2.9,4.3,1.3,2.0};
// crear una nueva lista (vector dinamico)
List <int> list; // listar, tipo de dato, el nombre de lista
int bayesiano(int etiquetas, int columnas, int filas, float r);
int respuesta;
int MQ135=0;
int MQ7=1;
int knn (int k, int etiquetas, int tam_col, int col_fil); // definir la funccion
int resultado2;
SoftwareSerial serial2(2,3); //llamamos al sofware serial 

void setup() {
Serial.begin(9600);
serial2.begin(9600);

}

void loop() {
  respuesta=knn(3,2,3,100);
   // llamada al metodo 
switch(respuesta){
  case 1:
    Serial.println(MQ135);
    Serial.println(MQ7);
    Serial.println("Prediccion KNN: Aire Limpio");
  break;
  case 2:
    Serial.println(MQ7);
    Serial.println(MQ135);
    Serial.println("Prediccion KNN: Aire Contaminado");
  break;
  }
  delay(1000);
  //resultado2=bayesiano(2,3,100,0.02); 
 //Serial.println(respuesta);
  switch(respuesta){
  case 1:
    Serial.println(MQ135);
    Serial.println(MQ7);
    Serial.println("Prediccion Bayes: Aire Limpio");

  break;
  case 2:
    Serial.println(MQ135);
    Serial.println(MQ7);
    Serial.println("Prediccion Bayes: Aire Contaminado");
  break;
  }  
  Serial.println(respuesta);
  //0Serial.write(respuesta);
}

int knn (int k, int etiquetas, int tam_col, int tam_fil){
MQ135=analogRead(0);
MQ7=analogRead(1);
int col;
int fil=0;
int i=0;
int j;
float aux;
float aux_etiqueta;
float potencia;
float raiz;
int label;
String salida="";
float datos_prueba[2]={MQ135,MQ7};
/*  
 *   matriz de k-vecinos
 *   |1   |2   |3  | -> # vecinos mas cercanos
 *   | 1  |   1| 2 | -> etiqueta correspondiente
 *   |0.12|0.18|025|-> valor de las k distancias menores
 */
 float matriz_k [3][k];
 for(;i<k;i++){
  matriz_k[0][i]=i+1.00;  //  |   1 |   2   |   3   |
  matriz_k[1][i]=0; //     |  0  |   0   |   0   |
  matriz_k[2][i]=2500.0+i;// |2500 | 25001 | 25002 | 
  }
  i=0;
 /*
  *  matriz de etiquetas
  *  |1  |2  |3  | -> # de etiquetas
  *  |2  |1  |0  | -> el conteo de cada una de ellas con respecto a matriz k_vecinos   
  */
  float matriz_eti[2][etiquetas];
  for(;i<etiquetas;i++){
      matriz_eti[0][i]=i+1.0; // |  1 |  2 |  3  |
      matriz_eti[1][i]=0.0;   // |  0 |  0 |  0  |
    }

   for(;fil<tam_fil;fil++){
      for(col=0;col<tam_col-1;col++){ // menos la ultima columna que corresponde a la etiqueta
          potencia=potencia+pow(matriz[fil][col]-datos_prueba[col],2);
        }
        raiz=sqrt(potencia);
        potencia=0;
        // comparacion de la nueva distancia con solo la mayor distancia almacenada en matriz_k
        if(raiz<matriz_k[2][k-1]){
          matriz_k[2][k-1]=raiz;
          matriz_k[1][k-1]=matriz[fil][tam_col-1]; 
          // ordenar matriz por metodo de burbuja
          for(i=0;i<k;i++){
             for(j=i+1;j<k;j++){
               if(matriz_k[2][i]>matriz_k[2][j]){
                 // distancia
                  aux=matriz_k[2][i];
                  matriz_k[2][i]=matriz_k[2][j];
                  matriz_k[2][j]=aux;
                  //etiqueta
                  aux_etiqueta=matriz_k[1][i];
                  matriz_k[1][i]=matriz_k[1][j];
                  matriz_k[1][j]=aux_etiqueta;
                }//end if
              } //end for j
            } // end for i
        } // end if
    } // end lectura matriz.h
    //buscar etiqueta con mayor repitencia
    for(i=0;i<etiquetas;i++){
      for(j=0;j<k;j++){
          if(matriz_eti[0][i]==matriz_k[1][j]){
            matriz_eti[1][i]++;
          }
        }
      }

    for(i=0;i<etiquetas-1;i++){
       if(matriz_eti[1][i]<matriz_eti[1][i+1]) // buscar el valor menor entre conteo de etiquetas
        label=(int)matriz_eti[0][i+1];    //asgina a label la etiqueta de mayor valor
        else 
        label=(int)matriz_eti[0][i];      //asgina a label la etiqueta de mayor valor
      }  

     
 return label;
};

int bayesiano(int etiquetas, int columnas, int filas, float r){
MQ135=analogRead(0);
MQ7=analogRead(1);
float datos_prueba[2]={MQ135,MQ7};
 int i=0; // variable de recorrido en matriz
 int j=0; // variable de recorrido en matriz
 int k=0; // variable de recorrido en matriz
 int t=0; // variable de recorrido en matriz
 float p_x=0.0; // probabilidad marginal
 float distancia=0.0; 
 float sumatoria=0.0;
 float normalizador=0.0;
 float dist_mayor=0.0001;
 int resultado; // resultado de etiqueta
 float aux=0; // auxiliar de cambio de variable
   float prob [4][etiquetas];
   //encerar matriz y asignar etiquetas a la fila 0
    for(i=0;i<4;i++){
       for(j=0;j<etiquetas;j++){  
          prob[i][j]=0;            
          if(i==0)                 
          prob[i][j]=j+1;        
        }
      }
    // sumar el valor del total por etiqueta en la matriz
    for(i=0;i<etiquetas;i++){              
        for(j=0;j<filas;j++){               
          if(matriz[j][columnas-1]==i+1)    
            prob[1][i]++;                   
          }
      }


    //encontrar la distancia mayor 
    for(i=0;i<filas;i++){
       for(j=0;j<columnas-1;j++){
         sumatoria=sumatoria+pow(matriz[i][j]-datos_prueba[j],2); // realizar la sumatoria de potencia
        }
        distancia=sqrt(sumatoria); // raiz cuadrada para distancia entre dos puntos
        sumatoria=0;
        if(distancia>dist_mayor)
          dist_mayor=distancia; // encuentro distancia mayor
      }
      distancia=0; 
    // normalizar la distancia en toda la matriz 
    for(i=0;i<filas;i++){
       for(j=0;j<columnas-1;j++){
         sumatoria=sumatoria+pow(matriz[i][j]-datos_prueba[j],2);// realizar la sumatoria de potencia
       }
        distancia=sqrt(sumatoria); // raiz cuadrada para distancia entre dos puntos
        sumatoria=0;
        normalizador=distancia/dist_mayor; // distancias entre 0 y 1
        if(normalizador<r)
            list.Add(i); // almancenar la fila de los datos que son parte de la circunferencia
    }
    // sumar por etiqueta a todos los datos que se encuentran en la circuferencia
    for(i=0;i<list.Count();i++){                          // |    1   |   2    |    3   |
      for(j=0;j<etiquetas;j++){                           // |   40   |   40   |   40   |
          if(matriz[list[i]][columnas-1]==prob[0][j])     // |    4   |   1    |    0   |
            prob[2][j]++;                                 // |    0   |   0    |    0   |
        }
      }
      // probabilidades por cada etiqueta
      p_x=float(list.Count())/float(filas); 
   for(k=0;k<etiquetas;k++){  // encontrar la probabilidad por etiqueta
      prob[3][k]=((prob[1][k]/filas)*(prob[2][k]/prob[1][k]))/p_x;
    }

      // busqueda de probabilidad por etiqueta
      for(k=0;k<etiquetas;k++){
         if(prob[3][k]>aux){
           resultado=int(prob[0][k]);
           aux=prob[3][k];
          }   
        }
    //retorna el resultado de etiqueta
    resultado=resultado2;
  
}
