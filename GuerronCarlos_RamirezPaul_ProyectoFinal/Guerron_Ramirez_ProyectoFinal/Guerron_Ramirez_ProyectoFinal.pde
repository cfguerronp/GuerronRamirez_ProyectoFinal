//import grafica.*;
import processing.serial.*;
import controlP5.*;
//objetos cp5
ControlP5 cp5;
//Comunicacion serial
Serial Port; // objeto Serial
//variables
int al=170;
int r;
int r2,r3,r4=255;
int aux=0;
float x,y;
//objeto imagenes
PImage aireLImg;
PImage aireSImg;
PImage utnImg;
PImage protImg;
int resultado=0;

void setup(){
  size(1200,800);
  background(#EBEBF7);
  cp5=new ControlP5(this);
  aireLImg=loadImage("airelimpio.jpg");//carga de imagenes
  aireSImg=loadImage("airesucio.jpg");
  utnImg=loadImage("UTN.png");
  protImg=loadImage("prot.jpg");
  
  ///ejemplo
  background(#EBEBF7);
  //print(Serial.list());//Cambia el indice [1] por el que indique la consola
  ////puertoArduino = new Serial(this, Serial.list()[1], 9600);
  
  //botones
  cp5.addButton("ACTIVAR")
    .setPosition(75,390)
    .setSize(150,50)
    .setColorBackground(#87E375)
    .setColorActive(#E8F53E)
    .setColorForeground(#E8F53E)
    .getCaptionLabel()
    .setFont(createFont("Arial",15))
    .toUpperCase(false)
    .setText("ACTIVAR")
    .align(ControlP5.CENTER,ControlP5.CENTER).setPaddingX(0)
    ;
    
    cp5.addButton("DETENER")
    .setPosition(75,590)
    .setSize(150,50)
    .setColorBackground(#FA0F13)
    .setColorActive(#E8F53E)
    .setColorForeground(#E8F53E)
    .getCaptionLabel()
    .setFont(createFont("Arial",15))
    .toUpperCase(false)
    .setText("DETENER")
    .align(ControlP5.CENTER,ControlP5.CENTER).setPaddingX(0)
    ;   
}

void draw(){
  background(#EBEBF7);
  fill(0,0,255);
  textSize(45);
  text("Sistemas Embebidos - Proyecto Final 2B",180,60);
  fill(0);
  textSize(35);
  text("Guerrón Carlos - Ramirez Paul",350,120);
  fill(0);
  textSize(38);
  text("Sensores MQ135 - MQ7",380,180);
  //imagen utn
  imageMode(CORNER);
  image(utnImg, 50,50 ,150,150);
  //imagen siste
  imageMode(CORNER);
  image(protImg, 950,70 ,190,140);
  //linea de separacion
  strokeWeight(3);
  stroke(#DBD9D9);
  line(0,220,1200,220);
  
  //rectangulo 1
  fill(#266483);
  rect(50,250,200,500);
  fill(0);
  text(r,500,600);
  //texto rect1
  fill(255);
  textSize(20);
  text("BOTONES",105,300);
  //rectangulo 2
  fill(#266483);
  rect(350,250,500,500);
  //fill(0);
  //text(r,500,600);
  //rectangulo 3
  fill(#266483);
  rect(900,250,250,500);
  //fill(0);
  //text(r,500,600);
  
  if(r==1){
    imageMode(CORNER);
    image(aireLImg, 429,340 ,350,350);
    fill(255);
  textSize(20);
  text("AIRE LIMPIO",600,300);
  }else if(r==2){
    imageMode(CORNER);
    image(aireSImg,429,340 ,350,350);
    fill(255);
  textSize(20);
  text("AIRE CONTAMINADO",600,300);
  }
  fill(255);
  textSize(20);
  text("CALIDAD DEL AIRE:",400,300);
  fill(255);
  textSize(20);
  text("DATOS SENSORES",940,290);
  text("MQ135: "+r2+" ppm",940,350);
  text("MQ7: "+r3+" ppm",940,400);

MATRIZ();

}

public void MATRIZ(){
  //////////////matriz////////////////////
//fill(#266483);
  //rect(900,250,250,500);
  fill(0,255,0);
  rect(965,500,60,60);
  fill(255,0,0);
  rect(965+60,500,60,60);
  fill(0,255,0);
  rect(965+60,500+60,60,60);
  fill(255,0,0);
  rect(965,500+60,60,60);
  //tecto matriz
  fill(255);
  textSize(20);
  text("MATRIZ KNN",960,480);
  fill(255);
  textSize(20);
  text("Exactitud: 97.78%",978-38,537+120);
  text("Precisión: 100%",978-38,537+120+30);
  fill(0);
  textSize(20);
  text("24",982,537);
  text("0",982+68,537);
  text("20",1043,537+60);
  text(" 1",982,537+60);

  
}

public void ACTIVAR() {
  Port =new Serial(this,"COM3",9600);
  //background(255);
  //fill(0,255,0);
  //ellipse(255,255,100,100);
  //resultado++;
  //if(resultado==1){
  //  imageMode(CORNER);
  //  image(aireLImg, 500,300,400,400);
  //}else{
  //  background(255);
  //  resultado=0;
  //} 
}
void serialEvent(Serial port){
  if(aux==0){
      r=port.read();
      println(r);
      aux++;
    }
    else if(aux==1){
      r2=port.read();
      println(r2);      
      aux++;
    }else if(aux==2){
      r3=port.read();
      println(r3);
      aux=0;
    }
}




public void DETENER(){
  Port.stop();
  r=0;
}
