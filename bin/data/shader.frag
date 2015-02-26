// fragment shader
#version 150

// this is how we receive the texture
uniform sampler2DRect tex0;
uniform float sides;

in vec2 varyingTexCoord;

out vec4 outputColor;

/*
float map(float x,float in_min,float in_max,float out_min,float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
*/

void main()
{
    vec2 iResolution = vec2(640,360);
    vec2 position = varyingTexCoord.xy;// iResolution.xy;
    // normalize to the center
    vec2 p = position - iResolution.xy/2.;
    
    // cartesian to polar coordinates
    float r = length(p)*.72;
    float a = atan(p.x, p.y);
    
    // kaleidoscope
    float tau = 3.1416;
    a = mod(a, tau/sides);
    a = abs(a - tau/sides/2.);
    
    // polar to cartesian coordinates
    p = r * vec2(cos(a), sin(a));
    
    // sample the webcam
    vec4 color = texture(tex0, p + iResolution.xy/2.);
    outputColor = color;
}