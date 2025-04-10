class Faixa {
    
  float x;
  float y;
  float r;

  
  Faixa (float x, float y, float r){
    this.x = x;
    this.y = y;
    this.r = r;
  }
  
  void draw (){
    
  rectMode (CENTER);
  fill (blue);
  noStroke();
  
  circle (0, 0-55, 120);
  
  rect (0, 0, 100, 200, 70);
  
  circle (0, 0 - 55, 90);
  stroke (black); 
  strokeWeight (10);
  fill (white);
  circle (0, 0 - 55, r);

   }
   

    
 
}
