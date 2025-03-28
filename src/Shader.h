#pragma once

#include <glad/glad.h>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

class Shader {
	uint32_t id;
public:
	Shader(const std::string& vertexStr, const std::string& fragmentStr, bool path = true) {
		std::string vertexCode = vertexStr, fragmentCode = fragmentStr;

		if (path) {
			std::ifstream vertexFile(vertexStr), fragmentFile(fragmentStr);
			std::stringstream vertexStream, fragmentStream;

			vertexStream << vertexFile.rdbuf();
			fragmentStream << fragmentFile.rdbuf();

			vertexCode = vertexStream.str(); fragmentCode = fragmentStream.str();

			vertexFile.close(); fragmentFile.close();
		}

		id = programLinking(vertexCode, fragmentCode);
	}

	Shader(uint32_t _id) {
		if (glIsProgram(_id)) {
			id = _id;
		}
		else {
			id = 0;
			std::cout << "ERROR::PROGRAM::NAME_NOT_FOUND\n" << std::endl;
		}
	}

	void use() { glUseProgram(id); }

	void setBool(const std::string& name, bool val) {
		glUniform1i(
			glGetUniformLocation(id, name.c_str()),
			(int)val
		);
	}
	void setInt(const std::string& name, int val) {
		glUniform1i(
			glGetUniformLocation(id, name.c_str()),
			val
		);
	}
	void setUInt(const std::string& name, uint32_t val) {
		glUniform1ui(
			glGetUniformLocation(id, name.c_str()),
			val
		);
	}
	void setFloat(const std::string& name, float val) {
		glUniform1f(
			glGetUniformLocation(id, name.c_str()),
			val
		);
	}
	void setVec2(const std::string& name, float x, float y) {
		glUniform2f(
			glGetUniformLocation(id, name.c_str()),
			x, y
		);
	}
	void setVec3(const std::string& name, float x, float y, float z) {
		glUniform3f(
			glGetUniformLocation(id, name.c_str()),
			x, y, z
		);
	}
	void setVec4(const std::string& name, float x, float y, float z, float w) {
		glUniform4f(
			glGetUniformLocation(id, name.c_str()),
			x, y, z, w
		);
	}

	static uint32_t shaderCompilation(const char* shaderSource, GLenum type) {
		uint32_t shader;
		shader = glCreateShader(type);

		glShaderSource(shader, 1, &shaderSource, NULL);
		glCompileShader(shader);

		shaderErrorPrint(shader, type);

		return shader;
	}

	static bool shaderErrorPrint(uint32_t shader, GLenum type) {
		int success;

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (!success) {
			char infolog[512];
			glGetShaderInfoLog(shader, 512, NULL, infolog);
			std::cout << "ERROR::SHADER::" << type << "COMPILATION_FAILED\n" << infolog << std::endl;
		}

		return success;
	}

	static uint32_t programLinking(const std::string& vertexCode,const std::string& fragmentCode) {
		uint32_t linkId = glCreateProgram();

		/*compile shaders*/
		uint32_t vertex = shaderCompilation(vertexCode.c_str(), GL_VERTEX_SHADER);
		uint32_t fragment = shaderCompilation(fragmentCode.c_str(), GL_FRAGMENT_SHADER);
		/*attaching the vertex and fragment shader to the program*/
		glAttachShader(linkId, vertex);
		glAttachShader(linkId, fragment);
		/*linking program to opengl*/
		glLinkProgram(linkId);
		/*check for errors*/
		LINKLOG(linkId);

		glDeleteShader(vertex); glDeleteShader(fragment);

		return linkId;
	}

	static void LINKLOG(uint32_t linkId) {
		int success;

		glGetProgramiv(linkId, GL_LINK_STATUS, &success);

		if (!success) {
			char infolog[512];
			glGetProgramInfoLog(linkId, 512, NULL, infolog);
			std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infolog << std::endl;
		}
	}
};
