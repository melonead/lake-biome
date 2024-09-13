void read_shader_code(char* res, const char* path);
unsigned int load_shaders(const char* vPath, const char* fPath);
void setBool(const char* name, bool value, unsigned int ID);

void setInt(const char* name, int value, unsigned int ID);

void setFloat(const char* name, float value, unsigned int ID);

void setMatrix4fv(const char* name, glm::mat4 value, unsigned int ID);