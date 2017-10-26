
#version 150

in vec4 position;
uniform mat4 modelViewProjectionMatrix;
uniform float timeValX;
uniform float timeValY;
uniform vec2 mouse;
uniform float drag;
uniform vec3 center;


//generate a random value from four points
vec4 rand(vec2 A,vec2 B,vec2 C,vec2 D){

	vec2 s=vec2(12.9898,78.233);
	vec4 tmp=vec4(dot(A,s),dot(B,s),dot(C,s),dot(D,s));

	return fract(sin(tmp) * 43758.5453)* 2.0 - 1.0;
}

//this is similar to a perlin noise function
float noise(vec2 coord,float d){

	vec2 C[4];

	float d1 = 1.0/d;

	C[0]=floor(coord*d)*d1;

	C[1]=C[0]+vec2(d1,0.0);

	C[2]=C[0]+vec2(d1,d1);

	C[3]=C[0]+vec2(0.0,d1);


	vec2 p=fract(coord*d);

	vec2 q=1.0-p;

	vec4 w=vec4(q.x*q.y,p.x*q.y,p.x*p.y,q.x*p.y);

	return dot(vec4(rand(C[0],C[1],C[2],C[3])),w);
}


void main(){

	//get our current vertex position so we can modify it
	vec4 pos = modelViewProjectionMatrix * position;



	//generate some noise values based on vertex position and the time value which comes in from our OF app
	float noiseAmntX = noise( vec2(-timeValX + pos.x / 1000.0, 100.0), 27.0 );
	float noiseAmntY = noise( vec2(timeValY + pos.y / 1000.0, pos.x / 2000.0), 27.0 );



	//modify our position with the smooth noise
	pos.x += noiseAmntX * 20.0;
	pos.y += noiseAmntY * 10.0;

	mat4 rotateZ = mat4(cos(radians(timeValX)), sin(radians(timeValY)),0.0,0.0,
	                        -sin(radians(timeValX)), cos(radians(timeValY)), 0.0, 0.0,
	                        0.0, 0.0, 1.0, 0.0,
	                        0.0,0.0,0.0,1.0);
	mat4 rotateX = mat4(1.0, 0.0,0.0,0.0,
                        0.0, cos(radians(timeValX)), sin(radians(timeValX)), 0.0,
                        0.0, -sin(radians(timeValY)), cos(radians(timeValY)), 0.0,
                        0.0,0.0,0.0,1.0);

    mat4 rotateY = mat4(cos(radians(timeValY)), 0.0,-sin(radians(timeValY)),0.0,
                        0.0, 1.0, 0.0, 0.0,
                        sin(radians(timeValX)), 0.0, cos(radians(timeValX)), 0.0,
                        0.0,0.0,0.0,1.0);

	//scaling math with vectors, shudders.
	vec3 fakeMouse = vec3(mouse.x,mouse.y,0);
	vec3 unit = fakeMouse/(sqrt((fakeMouse.x*fakeMouse.x) + (fakeMouse.y*fakeMouse.y)));
	float dot = (pos.x*unit.x) + (pos.y*unit.y) +(pos.z*unit.z);
	vec3 projection = dot*unit;
	vec3 d = vec3(center.x, center.y,center.z) - fakeMouse;
	if(abs(d.x) < 1){
	if(abs(d.x)!= d.x){
		d.x = -1;
	}
	else{
		d.x = 1;
	}
	}
	if(abs(d.x) > 250){
			if(abs(d.x)!= d.x){
				d.x = -250;
			}
			else{
				d.x = 250;
			}
	}

	if(abs(d.y) < 1){
	if(abs(d.y)!= d.y){
		d.y = -1;
	}
	else{
		d.y = 1;
	}
	}
	if(abs(d.y) > 250){
			if(abs(d.y)!= d.y){
				d.y = -250;
			}
			else{
				d.y = 250;
			}
	}

	if(abs(d.z) < 1){
	if(abs(d.z)!= d.z){
		d.z = -1;
	}
	else{
		d.z = 1;
	}
	}
	if(abs(d.z) > 250){
			if(abs(d.z)!= d.z){
				d.z = -250;
			}
			else{
				d.z = 250;
			}
	}
	if( abs(d.x) > 20 || abs(d.y) >20 || abs(d.z)>20){
		vec3 scale = (d*.0025);
		pos += (scale*projection);
	}

	pos = rotateX*rotateY*rotateZ*pos;


	pos *= drag;
	//finally set the pos to be that actual position rendered

	gl_Position = pos;
}
