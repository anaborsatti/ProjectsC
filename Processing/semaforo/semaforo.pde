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
  float vx;
  float vy;
  float period;
  float start;
  float duration;
  
  Light (float x, float y, float r, color c, float period, float start, float duration){
    this.x = x;
    this.y = y;
    this.r = r;
    this.c = c;
    this.on = false;
    this.vx = 0;
    this.vy = 0;
    this.period = period;
    this.start = start;
    this.duration = duration;
  }
  
  void draw (){
    fill (on ? c : lightGrey);
    circle (x, y, 2*r);
    
  }
  
    void drawAt (float t){
    fill (isOn (t)? c : lightGrey);
    circle (x, y, 2*r);
    
  }
  
  boolean isOn (float t){
    float t1 = t%period;
    return start <= t1 && t1 < start + duration;
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

class TrafficLights {
  float x; //centro do retangulo
  float y;
  float w;
  float h; 
  color c; 
  float r;
  float a;
  float radius; // raio do semaforo
  Light[] lights;
  float vx;
  float vy;
  float va;
  float period;
  
  
  TrafficLights (float x, float y, float w, float h, color c, float r, float period, float[] starts, float[] durations){
    this.x = x;
    this.y = y;
    this.w = w;
    this.h = h;
    this.c = c;
    this.r = r;
    this.a = 0;
    this.radius = sqrt (w*w/4 + h*h/4);
    this.lights = new Light [3]; 
    this.lights[0] = new Light (0, 0 - h/3, r, red, period, starts[0], durations[0]);
    this.lights[1] = new Light (0, 0, r, yellow, period, starts [1], durations [1]);
    this.lights[2] = new Light (0, 0 + h/3, r, green, period, starts[2], durations[2]);
    this.vx = 0;
    this.vy = 0;
    this.va = 0;
  }
  
  void draw (){
    pushMatrix ();
    translate (x, y);
    rotate (a);
    fill (c);
    rectMode(CENTER);
    rect (0, 0, w, h);
    for (int i = 0; i < 3; i++)
      lights[i].drawAt(frameCount/60);
    noFill ();
    circle (0, 0, 2*radius);
    popMatrix();
  }
  
   void move (){
    x += vx;
    y += vy;
    a += va;
  }
  
  void start (float vx, float vy, float va){
    this.vx = vx;
    this.vy = vy; 
    this.va = va;
  }
  
  void acelerateRotation (float da){
    this.va += da;
  }
  
  boolean inside(){
  return x + radius <= width && x - radius >= 0 && y + radius <= height && y - radius >= 0;
  }
}

TrafficLights tl;

class Spinner {
  TrafficLights t1;
  TrafficLights t2;
  float[] durations = {5, 2, 3};
  float period = 10;
  float[] starts = {0, 5, 7};
  float x; //centro do retangulo
  float y;
  float w;
  float h; 
  color c; 
  float r;
  float a;
  float radius; // raio do semaforo
  float vx;
  float vy;
  float va;
  


  
  Spinner (float x, float y, float w, float h, color c, float r, float period, float[] starts, float[] durations){
    this.t1 = new TrafficLights (width/2, height/2, 100, 300, black, 40, period, starts, durations);
    this.t2 = new TrafficLights (width/2, height/2, 300, 100, black, 40, period, starts, durations);
    this.x = x;
    this.y = y;
    this.w = w;
    this.h = h;
    this.a = 0;
    this.c = c;
    this.radius = sqrt (w*w/4 + h*h/4);
    this.vx = 0;
    this.vy = 0;
    this.va = 0;
  }
  
  void draw (){
    pushMatrix ();
    pushMatrix();
    translate (x, y);
    t1.draw ();
    t2.draw();
    rotate (a);
    popMatrix();
    popMatrix();
  }
  
   void move (){
    x += vx;
    y += vy;
    a += va;
  }
  
  void start (float vx, float vy, float va){
    this.vx = vx;
    this.vy = vy; 
    this.va = va;
  }
  
  void acelerateRotation (float da){
    this.va += da;
  }
}

Spinner s;




void settings (){
  size(horizontalSize, verticalSize);
}

void setup (){
  float[] durations = {5, 2, 3};
  float period = 10;
  float[] starts = {0, 5, 7};
  s = new Spinner (width/2, height/2, 100, 300, black, 40, period, starts, durations);
  float vx0 = 1; //tornar aleatorio
  float vy0 =1;
  s.start (vx0, vy0, PI/180); 
  //tempo das luzes com novos arrays dutaion e start
}

void keyPressed (){
  if (key == 'a')
    s.start (s.vx, -s.vy, s.va + PI/180);  //alterar para as setas 
  else if (key == 'd')
    s.start (s.vx, -s.vy, s.va - PI/180);        
}

void update(){
  s.move ();
  if (s.x + s.radius >= width) 
    s.start (-s.vx, s.vy, s.va);
  else if (s.x - s.radius <= 0)
    s.start (s.vx, s.vy, s.va);   
  if (s.y + s.radius >= height) 
    s.start (s.vx, -s.vy, s.va);
  else if (s.y - s.radius <= 0)
    s.start (s.vx, s.vy, s.va);   
  
}

void draw(){
  update ();
  background (magenta);
  s.draw();

}
