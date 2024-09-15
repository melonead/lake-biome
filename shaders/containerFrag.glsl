#version 430 core

out vec4 FragColor;
in vec3 FragPos;
in vec3 Normal;
uniform vec3 light_pos;
uniform vec3 view_pos;

void main() {

    // ambient light
    float ambient_strength = 0.3;
    vec3 light_color       = vec3(1.0, 1.0, 1.0);
    vec3 object_color      = vec3(1.0, 0.0, 0.0);
    vec3 ambient           = ambient_strength * light_color;

    // diffuse light
    float diffuse_strength = 0.7;
    vec3 norm      = normalize(Normal);
    vec3 light_dir = normalize(light_pos - FragPos);

    float diff     = max(dot(norm, light_dir), 0.0);
    vec3 diffuse   = diff * light_color * diffuse_strength;


    // specular light
    float specular_strength = 0.8;
    vec3 view_dir = normalize(view_pos - FragPos);
    vec3 reflect_dir = reflect(-light_dir, norm);

    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 32);
    vec3 specular = specular_strength * spec * light_color;
    vec3 result    = (ambient + diffuse + specular) * object_color;
    
    FragColor = vec4(result, 1.0);
}