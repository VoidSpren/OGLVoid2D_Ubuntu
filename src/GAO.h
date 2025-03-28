#pragma once

#include <iostream>
#include <vector>
#include <numeric>
#include <glad/glad.h>
#include "Lineal.h"

#include "Pixel.h"

class GAO {

	const uint32_t COUNT;
	
	uint32_t *VAOs = new uint32_t[COUNT];
	uint32_t *VBOs = new uint32_t[COUNT];
	uint32_t *EBOs = new uint32_t[COUNT];

	struct BOsInfo {
		size_t capacity = 0;
		size_t size = 0;
		GLenum usage = GL_DYNAMIC_DRAW;
	};

	BOsInfo *VBOsInfo = new BOsInfo[COUNT];
	BOsInfo *EBOsInfo = new BOsInfo[COUNT];

public:
	GAO(uint32_t count): COUNT(count){

		glGenVertexArrays(COUNT, VAOs);
		glGenBuffers(COUNT, VBOs);
		glGenBuffers(COUNT, EBOs);
		for (int i = 0; i < COUNT; i++) {
			glBindVertexArray(VAOs[i]);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[i]);
		}
	}
	~GAO() {
		if (VAOs != nullptr) {
			glDeleteVertexArrays(COUNT, VAOs);
			delete[] VAOs;
		}
		if (VBOs != nullptr) {
			glDeleteBuffers(COUNT, VBOs);
			delete[] VBOs;
		}
		if (EBOs != nullptr) {
			glDeleteBuffers(COUNT, EBOs);
			delete[] EBOs;
		}

		if (VBOsInfo != nullptr) delete[] VBOsInfo;
		if (EBOsInfo != nullptr) delete[] EBOsInfo;
	}

	uint32_t getVAO(uint32_t i) {
		if (i < COUNT) {
			return VAOs[i];
		}
		return 0;
	}
	uint32_t getVBO(uint32_t i) {
		if (i < COUNT) {
			return VBOs[i];
		}
		return 0;
	}
	uint32_t getEBO(uint32_t i) {
		if (i < COUNT) {
			return EBOs[i];
		}
		return 0;
	}

	void bindVao(uint32_t i){
		if (i < COUNT) {
			glBindVertexArray(VAOs[i]);
		}
		else {
			throw "Outside of range Exception";
		}
	}
	void bindBuffer(uint32_t i) {
		if (i < COUNT) {
			glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
		}
		else {
			throw "Outside of range Exception";
		}
	}
	void bind(uint32_t i) {
		if (i < COUNT) {
			glBindVertexArray(VAOs[i]);
			glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
		}
		else {
			throw "Outside of range Exception";
		}
	}
	void enable(uint32_t i, const std::vector<uint32_t>& atrrs) {
		if (i < COUNT) {
			bindVao(i);
			for (auto n : atrrs) {
				glEnableVertexAttribArray(n);
			}
		}
		else {
			throw "Outside of range Exception";
		}
	}

	void setElBufferData(uint32_t i, const std::vector<uint32_t>& elData, GLenum usage, bool resize = false) {
		if (i < COUNT) {
			bindVao(i);

			const size_t prevCapacity = EBOsInfo[i].capacity;
			const size_t newSize = elData.size() * sizeof(uint32_t);

			if (resize || newSize != prevCapacity) {
				if (newSize < 1000 * sizeof(uint32_t)) {
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, 1000 * sizeof(uint32_t), elData.data(), EBOsInfo[i].usage);
					EBOsInfo[i].capacity = 1000 * sizeof(uint32_t);
					EBOsInfo[i].size = newSize;
				}
				else {
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, newSize, elData.data(), EBOsInfo[i].usage);
					EBOsInfo[i].capacity = newSize;
					EBOsInfo[i].size = newSize;
				}

			}
			else {
				glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, newSize, elData.data());
				EBOsInfo[i].size = newSize;
			}
		}
		else {
			throw "Outside of range Exception";
		}
	}

	void defineVerBufferData(uint32_t i, const std::vector<uint32_t>& attributes, GLenum usage = GL_DYNAMIC_DRAW, uint32_t size = 1000, const std::vector<float>& vertData = {}) {
		if (i < COUNT) {
			bind(i);

			uint32_t total = std::accumulate(attributes.begin(), attributes.end(), 0);
			uint32_t sum = 0;
			for (uint32_t i = 0; i < attributes.size(); i++) {
				glVertexAttribPointer(i, attributes[i], GL_FLOAT, GL_FALSE, total * sizeof(float), (void*)(sum * sizeof(float)));
				sum += attributes[i];

			}

			void *data;

			if (vertData.size() > 0) {
				const size_t newSize = vertData.size()* sizeof(float);
				VBOsInfo[i] = {
					newSize,
					newSize,
					usage
				};

				data = (void*)vertData.data();
			}
			else {
				VBOsInfo[i] = {
					size * total * sizeof(float),
					0,
					usage
				};

				data = NULL;
			}

			glBufferData(GL_ARRAY_BUFFER, VBOsInfo[i].capacity, data, usage);


		}
		else {
			throw "Outside of range Exception";
		}
	}

	void setVerBufferData(uint32_t i, const std::vector<float>& vertData, bool resize = false) {
		if (i < COUNT) {
			bindBuffer(i);

			const size_t prevCapacity = VBOsInfo[i].capacity;
			const size_t newSize = vertData.size() * sizeof(float);

			if (resize || newSize > prevCapacity) {
				glBufferData(GL_ARRAY_BUFFER, newSize, vertData.data(), VBOsInfo[i].usage);
				VBOsInfo[i].capacity = newSize;
				VBOsInfo[i].size = newSize;
			}
			else {
				glBufferSubData(GL_ARRAY_BUFFER, 0, newSize, vertData.data());
				VBOsInfo[i].size = newSize;
			}

		}
		else {
			throw "Outside of range Exception";
		}
	}

	void addVerBufferData(uint32_t i, const std::vector<float>& vertData) {
		if (i < COUNT) {
			bindBuffer(i);
			const size_t size = VBOsInfo[i].size;
			const size_t capacity = VBOsInfo[i].capacity;

			const size_t addedSize = vertData.size() * sizeof(float);
			if (size + addedSize <= capacity) {
				glBufferSubData(GL_ARRAY_BUFFER, size, addedSize, vertData.data());
				VBOsInfo[i].size = size + addedSize;
			}
			else {
				throw "Run out of allocated buffer capacity";
			}
		}
		else {
			throw "Outside of range Exception";
		}
	}

	void clearVerBufferData(uint32_t i) {
		if (i < COUNT) {
			VBOsInfo[i].size = 0;
		}
		else {
			throw "Outside of range Exception";
		}
	}

private:
};
