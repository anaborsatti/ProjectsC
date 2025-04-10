int horizontalSize = 640;
int verticalSize = 480;
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

class Light {
  float x;
  float y;
  float r;
  color c;
  boolean on;
  float duration;
  float vx;
  float vy;
  
  Light (float x, float y, float r, color c, float duration){
    this.x = x;
    this.y = y;
    this.r = r;
    this.c = c;
    this.on = true;
    this.duration = duration;
    this.vx = 0;
    this.vy = 0;
  }
  
  void draw (){
    fill (on ? yellow : lightGrey);
    circle (x, y, 2*r);
    
  }
  
  boolean isOn (float t){
    return t%4 <= 2;
  }
  
  void move (){
    x += vx;
    y += vy;
  }
  
  void start (float vx, float vy){
    this.vx = vx;
    this.vy = vy; 
  }
  
}

Light myLight;

void settings (){
  size(horizontalSize, verticalSize);
}

void setup (){
  myLight = new Light(width/2, height/2, 50, yellow, 2);
  myLight.start (1, 0);
}

void update(){
  myLight.on = myLight.isOn (frameCount/60.0);
  if (myLight.x + myLight.r >= width)
    myLight.start (-1, 0);
   else if (myLight.x - myLight.r <= 0)
     myLight.start (1, 0);
   myLight.move ();
   
  
}

void draw(){
  update ();
  background (magenta);
  myLight.draw();
}
