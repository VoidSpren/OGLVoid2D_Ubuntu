#pragma once
#include "GAO.h"
#include "Shader.h"

class RenderBatch {
	GAO *gao;
	Shader program;
	std::vector<ui32> elementVec;

	ui32 vaoIndex = 0;
	ui32 elementCount = 0;

	ui32 attribCount = 0;

	std::vector<i32> textureIds	;

public:
	RenderBatch(GAO *_gao, ui32 _vaoIndex, const std::string& vertStr, const std::string&fragstr, bool path = true):
		gao(_gao), program(vertStr, fragstr, path), vaoIndex(_vaoIndex) {}

	RenderBatch(GAO* _gao, ui32 _vaoIndex, ui32 _programId) : gao(_gao), program(_programId), vaoIndex(_vaoIndex) {}

	void defineVertBufferData(const std::vector<ui32>& attributes, GLenum usage = GL_DYNAMIC_DRAW, ui32 size = 1000, const std::vector<float>& vertData = {}) {
		gao->defineVerBufferData(vaoIndex, attributes, usage, size, vertData);
		attribCount = attributes.size();
	}

	/*(VAA) VertexAttributeArray*/
	void enableVAA(const std::vector<ui32>& attrs) {
		gao->enable(vaoIndex, attrs);
	}
	
	void enableVAA() {
		std::vector<ui32> attrs(attribCount);
		for (int i = 0; i < attribCount; i++) {
			attrs[i] = i;
		}

		gao->enable(vaoIndex, attrs);
	}


	void clearBatch() {
		gao->clearVerBufferData(vaoIndex);
		elementVec.clear();

		elementCount = 0;
	}

	void addVertices(const std::vector<float>& vertData, const std::vector<ui32>& newElems) {
		gao->addVerBufferData(vaoIndex, vertData);

		ui32 gt = 0;
		for (auto elem : newElems) {
			ui32 nElem = elementCount + elem;

			gt = nElem > gt ? nElem : gt;

			elementVec.push_back(nElem);
		}
		elementCount = gt + 1;
	}

	i32 addTexture(ui32 id, i32 unit = -1) {
		if (unit >= 0 && unit < textureIds.size()) {
			textureIds[unit] = id;
			return unit;
		}
		else if (textureIds.size() < 32) {
			textureIds.push_back(id);
			return textureIds.size() - 1;
		}
		return -1;
	}

	void DrawBatch(GLenum mode = GL_TRIANGLES, bool redraw = false) {
		program.use();
		if (!redraw) gao->setElBufferData(vaoIndex, elementVec, GL_DYNAMIC_DRAW);
		else gao->bindVao(vaoIndex);

		for (int i = 0; i < textureIds.size(); i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, textureIds[i]);
		}

		glDrawElements(mode, elementVec.size(), GL_UNSIGNED_INT, 0);
	}
	void ReDrawBatch() {
		gao->bindVao(vaoIndex);
		glDrawElements(GL_TRIANGLES, elementVec.size(), GL_UNSIGNED_INT, 0);
	}
};