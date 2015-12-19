attribute vec4 a_position;
attribute vec2 a_texCoord;

#ifdef GL_ES										
	precision mediump float;
	varying mediump vec2 v_texCoord1;
	varying mediump vec2 v_texCoord2;
	varying mediump vec2 v_texCoord3;
#else
	varying vec2 v_texCoord1;
	varying vec2 v_texCoord2;
	varying vec2 v_texCoord3;
#endif

uniform float u_cloudSpeed;
const float layer1Speed = 0.1;
const float layer2Speed = 0.2;
const float layer3Speed = 0.05;



void main()											
{
	gl_Position = CC_PMatrix * a_position;				
	
	float time1 = mod(CC_Time.x * layer1Speed * u_cloudSpeed, 1.0);
	float time2 = mod(CC_Time.x * layer2Speed * u_cloudSpeed, 1.0);
	float time3 = mod(CC_Time.x * layer3Speed * u_cloudSpeed, 1.0);
	
	v_texCoord1 = a_texCoord;
	v_texCoord1.x += time1;
	
	v_texCoord2 = a_texCoord;			
	v_texCoord2.xy += time2;
	
	v_texCoord3 = a_texCoord;			
	v_texCoord3.xy += time3;
}


