#pragma once

#include "utilDefs.h"

namespace voi {
	struct Pixel{
		union {
			float p[4];
			struct {
				float r;
				float g;
				float b;
				float a;
			};
		};

		static Pixel lerp(Pixel a, Pixel b, float t) {
			return {
				a.r + (b.r - a.r) * t,
				a.g + (b.g - a.g) * t,
				a.b + (b.b - a.b) * t,
				a.a + (b.a - a.a) * t
			};
		}
	};
}
