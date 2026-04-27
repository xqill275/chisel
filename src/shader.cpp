#include "chisel/shader.h"

#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace chisel {

// ── Helpers ───────────────────────────────────────────────────────────────────

static std::string readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("chisel::Shader: cannot open file: " + path);
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

// ── Constructor / destructor ──────────────────────────────────────────────────

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vertSrc = readFile(vertexPath);
    std::string fragSrc = readFile(fragmentPath);

    unsigned int vert = compile(GL_VERTEX_SHADER,   vertSrc);
    unsigned int frag = compile(GL_FRAGMENT_SHADER, fragSrc);

    m_id = glCreateProgram();
    glAttachShader(m_id, vert);
    glAttachShader(m_id, frag);
    glLinkProgram(m_id);

    // Check link errors
    int success;
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success) {
        char log[512];
        glGetProgramInfoLog(m_id, 512, nullptr, log);
        glDeleteShader(vert);
        glDeleteShader(frag);
        glDeleteProgram(m_id);
        throw std::runtime_error(std::string("chisel::Shader: link error:\n") + log);
    }

    // Shaders are linked into the program — no longer needed separately
    glDeleteShader(vert);
    glDeleteShader(frag);
}

Shader::~Shader() {
    if (m_id)
        glDeleteProgram(m_id);
}

Shader::Shader(Shader&& other) noexcept
    : m_id(other.m_id)
{
    other.m_id = 0;
}

Shader& Shader::operator=(Shader&& other) noexcept {
    if (this != &other) {
        if (m_id) glDeleteProgram(m_id);
        m_id       = other.m_id;
        other.m_id = 0;
    }
    return *this;
}

// ── Bind / unbind ─────────────────────────────────────────────────────────────

void Shader::bind()   const { glUseProgram(m_id); }
void Shader::unbind() const { glUseProgram(0);    }

// ── Uniform setters ───────────────────────────────────────────────────────────

int Shader::getUniformLocation(const std::string& name) const {
    return glGetUniformLocation(m_id, name.c_str());
}

void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(getUniformLocation(name), value);
}

void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(getUniformLocation(name), value);
}

void Shader::setVec2(const std::string& name, float x, float y) const {
    glUniform2f(getUniformLocation(name), x, y);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const {
    glUniform3f(getUniformLocation(name), x, y, z);
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const {
    glUniform4f(getUniformLocation(name), x, y, z, w);
}

void Shader::setMat4(const std::string& name, const float* matrix) const {
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix);
}

// ── Compile helper ────────────────────────────────────────────────────────────

unsigned int Shader::compile(unsigned int type, const std::string& source) const {
    unsigned int id = glCreateShader(type);
    const char*  src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(id, 512, nullptr, log);
        glDeleteShader(id);
        const std::string typeName = (type == GL_VERTEX_SHADER) ? "vertex" : "fragment";
        throw std::runtime_error("chisel::Shader: " + typeName + " compile error:\n" + log);
    }

    return id;
}

} // namespace chisel