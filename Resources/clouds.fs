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

uniform float u_amount;


void main(void)
{
	vec4 col = texture2D(CC_Texture0, v_texCoord1) * texture2D(CC_Texture1, v_texCoord2) * texture2D(CC_Texture2, v_texCoord3);		
	
	col.a = col.r;
	col -= 1.0 - u_amount;
	col = max(col, 0.0);
	col *= (1.0 / u_amount);
	
	col.r = 1.0 - col.r;
	col.g = 1.0 - col.g;
	col.b = 1.0 - col.b;
	
	gl_FragColor = col;
	
}																						
