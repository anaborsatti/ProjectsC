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
      if (w >= h) { // Se o retângulo estiver na horizontal
      this.lights[0] = new Light(-w / 3, 0, r, red, period, starts[0], durations[0]); // Luz vermelha
      this.lights[1] = new Light(0, 0, r, yellow, period, starts[1], durations[1]); // Luz amarela
      this.lights[2] = new Light(w / 3, 0, r, green, period, starts[2], durations[2]); // Luz verde
    } else { // Se o retângulo estiver na vertical
      this.lights[0] = new Light(0, -h / 3, r, red, period, starts[0], durations[0]); // Luz vermelha
      this.lights[1] = new Light(0, 0, r, yellow, period, starts[1], durations[1]); // Luz amarela
      this.lights[2] = new Light(0, h / 3, r, green, period, starts[2], durations[2]); // Luz verde
    this.vx = 0;
    this.vy = 0;
    this.va = 0; 
  }
  }
  
  void draw (){
    pushMatrix ();
    translate (this.x, this.y);
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
  float[] durations1;
  float period1;
  float[] starts1;
  float[] durations2;
  float period2;
  float[] starts2 ;
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
  


  
  Spinner (float x, float y, float w, float h, color c, float r, float period1, float[] starts1, float[] durations1, float period2, float[] starts2, float[] durations2){
    this.t1 = new TrafficLights (0, 0, 28, 86, black, r, period1, starts1, durations1); // Semáforo vertical
    this.t2 = new TrafficLights (0, 0, 86, 28, black, r, period2, starts2, durations2);
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
    pushMatrix();
    translate(x, y);
    rotate(a);
    t1.draw();
    t2.draw();
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
    this.va += 2*da;
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
  float[] durations2 = {3, 4, 2};
  float period2 = 9;
  float[] starts2 = {0, 3, 5};
  s = new Spinner (width/2, height/2, 28, 86, black, 8, period, starts, durations, period2, starts2,  durations2);
  float vx0 = random(1, 10); 
  float vy0 = random(1, 10);
  s.start (vx0, vy0, PI/180); 
}

void keyPressed (){
  if (keyCode == RIGHT)
    s.start (s.vx, -s.vy, s.va + PI/180);  
  else if (keyCode == LEFT)
    s.start (s.vx, -s.vy, s.va - PI/180);        
}

void update(){
  if (s.x + s.radius >= width) 
    s.start (-s.vx, s.vy, s.va);
  else if (s.x - s.radius <= 0)
    s.start (-s.vx, s.vy, s.va);   
  if (s.y + s.radius >= height) 
    s.start (s.vx, -s.vy, s.va);
  else if (s.y - s.radius <= 0)
    s.start (s.vx, -s.vy, s.va);   
  s.move ();
  
}

void draw(){
  update ();
  background (white);
  s.draw();

}
