#version 150
in vec4 position;
uniform mat4 modelViewProjectionMatrix;
uniform vec2 mouse;

void main(){
  vec4 pos = modelViewProjectionMatrix * position;
  vec2 d = vec2(pos.x, pos.y) - mouse;
  float len =  sqrt(d.x*d.x + d.y*d.y);

  float multX = 0;
  float multY = 0;

  if(abs(mouse.x - pos.x) > abs(mouse.y - pos.y)){
      multX = 120;
      multY = 90;
  }
  else{
      multX = 90;
      multY = 120;
  }
  //lets get the distance into 0-1 ranges
  float pct = len / 300.0;

  //this turns our linear 0-1 value into a curved 0-1 value
  pct *= pct;


  //normalize our repulsion vector
  d /= len;

  //apply the repulsion to our position
  pos.x += d.x * pct * multX;
  pos.y += d.y * pct * multY;

  gl_Position = pos;
}
