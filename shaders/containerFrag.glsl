#version 430 core

out vec4 FragColor;
in vec3 FragPos;
in vec3 Normal;
uniform vec3 light_pos;

void main() {

    // ambient light
    float ambient_strength = 0.1;
    vec3 light_color       = vec3(1.0, 1.0, 1.0);
    vec3 object_color      = vec3(1.0, 0.0, 0.0);
    vec3 ambient           = ambient_strength * light_color;

    // diffuse light
    float diffuse_strength = 0.6;
    vec3 norm      = normalize(Normal);
    vec3 light_dir = normalize(light_pos - FragPos);

    float diff     = max(dot(norm, light_dir), 0.0);
    vec3 diffuse   = diff * light_color * diffuse_strength;

    vec3 result    = (ambient + diffuse) * object_color;
    
    FragColor = vec4(result, 1.0);
}