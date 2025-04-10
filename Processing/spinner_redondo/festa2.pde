int horizontalSize = 860;
int verticalSize = 860;
final color white = color (255, 255, 255);
final color black = color (0, 0, 0);
final color red = color (255, 0, 0);
final color green = color (0, 255, 0);
final color blue = color (0, 0, 255);
final color yellow = color (255, 255, 0);
final color magenta = color (255, 0, 255);
final color cyan = color (0, 255, 255);
final color darkGrey = color (100);
final color lightGrey = color (200);

Faixa MyFaixa;
Spin spinner;


void setup (){
  size (600, 600);
  spinner = new Spin (300, 300, 70);

  
}


void draw (){
  background (white);
  spinner.draw ();

  


}
