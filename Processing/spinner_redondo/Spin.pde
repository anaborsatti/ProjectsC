class Spin {
    float x;
    float y;
    float r;
    Faixa f1;
    Faixa f2;
    Faixa f3;
    
    Spin (float x, float y, float r) {
    this.x = x;
    this.y = y;
    this.r = r;
    this.f1 = new Faixa (300, 300, 70);
    this.f2 = new Faixa (300, 300, 70);
    this.f3 = new Faixa (300, 300, 70);
  }
 
    void draw (){
    pushMatrix();
    translate (x, y);
    f1.draw();
    popMatrix();
    
    pushMatrix();
    translate(x-50, y+70);
    rotate (-TWO_PI/3);
    f2.draw();
    popMatrix();
    
    pushMatrix();
    translate(x+50, y+70);
    rotate(-2*TWO_PI/3);
    f3.draw();
    popMatrix();
    
    fill (blue);
    strokeWeight(1);
    circle (x, y+45, 70);
    
    }
  
}
