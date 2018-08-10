attribute vec3 position;
uniform mat4 ModelMatrix;
varying vec2 V_Texcoord;
void main(){
    V_Texcoord=vec2(0.5)+position.xy;
    gl_Position=ModelMatrix*vec4(position*2.0,1.0);
}
