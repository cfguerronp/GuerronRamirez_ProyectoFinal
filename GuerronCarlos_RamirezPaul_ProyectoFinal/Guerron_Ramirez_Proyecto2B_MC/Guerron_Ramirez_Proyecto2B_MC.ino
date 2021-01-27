/*
 * Guerron Carlos - Ramirez Paul
 * PROYECTO 2B
 * MATRIZ DE CONFUSION
 */
//Llamar datos
#include "DatosPrueba.h"
#include "DatosMatriz.h"
//variables para valores matriz
int vdP=0;
int vdN=0;
int fsP=0;
int fsN=0;

void setup() {
  Serial.begin(9600);
  //llamar al metodo
  algConfusionKNN();

}

void loop() {
  // put your main code here, to run repeatedly:
  //algConfusionKNN();
}
void algConfusionKNN(){//inicio algoritmo
//variables para calcular parametros de la matriz
float exactitud;
float precision;
float aux2;
float aux;
//recorrer matriz de datos y matriz de valores clasificados
    for(int i=0;i<45;i++){
      //comparar etiquetas de resultados obtenidos mediante la clasificacion
      if(datosPrueba[i][2]==matrizKNN[i][2] && datosPrueba[i][2]==1){
        vdP++;//verdaderos positivos
      }
      if(datosPrueba[i][2]==matrizKNN[i][2] && datosPrueba[i][2]==2){
        vdN++;//verdaderos negativos
      }
      if(datosPrueba[i][2]!=matrizKNN[i][2]==2){
        fsP++;//falsos positivos
      }
      if(datosPrueba[i][2]!=matrizKNN[i][2]==1){
        fsN++;//falsos negativos       
      }  
    }
  //impresion de datos en serial
  Serial.println("Matriz de Confusion KNN");
  Serial.println(String(vdP)+String(" ")+String(fsP));//matriz | vp | fp | 
  Serial.println(String(fsN)+String(" ")+String(vdN));//       | fn | vn |
  exactitud=(vdP+fsP+fsN+vdN);//calculo esactitud
  aux=(vdP+vdN)/exactitud;
  precision=vdP/(vdP+fsP);//caclculo precsisoin
  Serial.println(String("Exactitud: ")+String(aux*100)+String("%"));
  Serial.println(String("Precision: ")+String(precision*100)+String("%"));
  vdP=0;fsP=0;fsN=0;vdN=0;
  exactitud=0,aux=0;
  precision=0;//reinicio de variables
  //recorrido matriz de prueba y matriz bayes
 for(int i=0;i<45;i++){
      //evaluar etiquetas de clasificacion
      if(datosPrueba[i][2]==matrizBY[i][2] && datosPrueba[i][2]==1){
        vdP++;//verdaderos positivos
      }
      if(datosPrueba[i][2]==matrizBY[i][2] && datosPrueba[i][2]==2){
        vdN++;//verdaderos negativos
      }
      if(datosPrueba[i][2]!=matrizBY[i][2]==2){
        fsP++;//falsos positivos
      }
      if(datosPrueba[i][2]!=matrizBY[i][2]==1){
        fsN++;//falsos negativos   
      }  
    }
  //impresion
  Serial.println("Matriz de Confusion BAYES");
  Serial.println(String(vdP)+String(" ")+String(fsP));
  Serial.println(String(fsN)+String(" ")+String(vdN));
  exactitud=(vdP+fsP+fsN+vdN);//caclulo exactitud
  aux=(vdP+vdN)/exactitud;
  Serial.println(String("Exactitud: ")+String(aux*100)+String("%"));
  precision=vdP/(vdP+fsP);//caclulo precciison
  Serial.println(String("Precision: ")+String(precision*100)+String("%"));
vdP=0;fsP=0;fsN=0;vdN=0;
exactitud=0;
aux=0,precision=0;//reinicio variables
}
