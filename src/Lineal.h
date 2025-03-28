#pragma once

#define F_PI 3.1415927f
#define D_PI 3.141592653589793

#include <cmath>

namespace voi {

	void swap(int& n1, int& n2) { int t = n1; n1 = n2; n2 = t; };

	template<typename T>
	struct Vec2 {
		union {
			T n[2]{ 0 };
			struct {
				union { T x, r, s; };
				union { T y, g, t; };
			};
		};

		Vec2() : x(0), y(0) {}
		Vec2(T x, T y) : x(x), y(y) {}
		Vec2(const Vec2& other) : x(other.x), y(other.y) {}
		Vec2(Vec2 &&other) : x(other.x), y(other.y) {}

		inline T min() const { return x < y ? x : y; }
		inline T max() const { return x > y ? x : y; }
		inline static T dotProd(const Vec2& a, const Vec2& b) { return a.x * b.x + a.y * b.y; }
		static Vec2 unit(const Vec2& in) {
			float l = sqrtf(in.x * in.x + in.y * in.y);
			return { in.x / l, in.y / l };
		}

		void toUnit() {
			float l = sqrtf(x * x + y * y);
			x /= l; y /= l;
		}

		inline Vec2 operator + (const Vec2& o) { return { x + o.x, y + o.y }; }
		inline Vec2 operator - (const Vec2& o) { return { x - o.x, y - o.y }; }
		inline Vec2 operator * (const Vec2& o) { return { x * o.x, y * o.y }; }
		inline Vec2 operator * (const T s) { return { x * s, y * s }; }
		inline Vec2 operator += (const Vec2& o) { x += o.x; y += o.y; return *this; }
		inline Vec2 operator -= (const Vec2& o) { x -= o.x; y -= o.y; return *this; }
		inline Vec2 operator *= (const Vec2& o) { x *= o.x; y *= o.y; return *this; }
		inline Vec2 operator *= (const T& s) { x *= s; y *= s; return *this; }

		inline T operator [](const size_t i) { return n[i % 2]; }
	};

	template<typename T>
	inline Vec2<T>& operator * (const T s, const Vec2<T>& o) { return{ o.x * s, o.y * s }; }

	typedef Vec2<int> Vec2i;
	typedef Vec2<float> Vec2f;
	typedef Vec2<double> Vec2d;

	/* simple vector3 struct */
	template<typename T>
	struct Vec3 {
		union {
			T n[3]{ 0 };
			struct {
				union { T x, r, s; };
				union { T y, g, t; };
				union { T z, b, p; };
			};
		};

		Vec3() : x(0), y(0), z(0) {}
		Vec3(T x, T y, T z) : x(x), y(y), z(z) {}
		Vec3(const Vec3& other) : x(other.x), y(other.y), z(other.z) {}
		Vec3(Vec3 &&other) : x(other.x), y(other.y), z(other.z) {}

		inline T min() const {}

		inline static T dotProd(const Vec3& a, const Vec3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
		inline static Vec3 cross(const Vec3& a, const Vec3& b) { return { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x }; }
		static Vec3 unit(const Vec3& in) {
			float l = sqrtf(in.x * in.x + in.y * in.y + in.z * in.z);
			return { in.x / l, in.y / l,in.z / l };
		}

		void toUnit() {
			float l = sqrtf(x * x + y * y + z * z);
			x /= l; y /= l; z /= l;
		}

		inline Vec3 operator + (const Vec3& o) { return { x + o.x, y + o.y, z + o.z }; }
		inline Vec3 operator - (const Vec3& o) { return { x - o.x, y - o.y, z - o.z }; }
		inline Vec3 operator * (const Vec3& o) { return { x * o.x, y * o.y, z * o.z }; }
		inline Vec3 operator * (const T s) { return { x * s, y * s, z * s }; }
		inline Vec3 operator += (const Vec3& o) { x += o.x; y += o.y; z += o.z; return *this; }
		inline Vec3 operator -= (const Vec3& o) { x -= o.x; y -= o.y; z -= o.z; return *this; }
		inline Vec3 operator *= (const Vec3& o) { x *= o.x; y *= o.y; z *= o.z; return *this; }
		inline Vec3 operator *= (const T& s) { x *= s; y *= s; z *= s; return *this; }

		inline T& operator [] (const size_t i) { return n[i % 3]; }

	};

	template<typename T>
	inline Vec3<T>& operator * (const T s, const Vec3<T>& o) { return{ o.x * s, o.y * s, o.z * s }; }

	typedef Vec3<int> Vec3i;
	typedef Vec3<float> Vec3f;
	typedef Vec3<double> Vec3d;

	/*simple vector4 struct*/
	template<typename T>
	struct Vec4 {
		union {
			T n[4]{ 0 };
			struct {
				union { T x, r, s; };
				union { T y, g, t; };
				union { T z, b, p; };
				union { T w, a, q; };
			};
		};

		Vec4() : x(0), y(0), z(0), w((T)1) {}
		Vec4(T w) : x(0), y(0), z(0), w(w) {}
		Vec4(T x, T y, T z) : x(x), y(y), z(z), w((T)1) {}
		Vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
		Vec4(const Vec4& other) : x(other.x), y(other.y), z(other.z), w(other.w) {}
		Vec4(Vec4 &&other) : x(other.x), y(other.y), z(other.z), w(other.w) {}

		inline static T dotProd3D(const Vec4& a, const Vec4& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
		inline static T dotProd4D(const Vec4& a, const Vec4& b) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }
		inline static Vec4& cross3D(const Vec4& a, const Vec4& b) { return { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x }; }
		
		static Vec4& unit3D(const Vec4& in) {
			float l = sqrtf(in.x * in.x + in.y * in.y + in.z * in.z);
			if (l == 0) return { 0,0,0 };
			return { in.x / l, in.y / l,in.z / l };
		}
		static Vec4& unit4D(const Vec4& in) {
			float l = sqrtf(in.x * in.x + in.y * in.y + in.z * in.z + in.w * in.w);
			return { in.x / l, in.y / l, in.z / l, in.w / l };
		}

		void toUnit3D() {
			float l = sqrtf(x * x + y * y + z * z);
			if (l != 0) {
				x /= l; y /= l; z /= l;
			}
			else {
				x = 0; y = 0; z = 0;
			}
		}
		void toUnit4D() {
			float l = sqrtf(x * x + y * y + z * z + w * w);
			x /= l; y /= l; z /= l; w /= l;
		}

		inline const Vec4& operator + (const Vec4& o) { return { x + o.x, y + o.y, z + o.z, w + o.w}; }
		inline const Vec4& operator - (const Vec4& o) { return { x - o.x, y - o.y, z - o.z, w - o.w }; }
		inline const Vec4& operator * (const Vec4& o) { return { x * o.x, y * o.y, z * o.z, w * o.w }; }
		inline const Vec4& operator * (const T s) { return { x * s, y * s, z * s, w * s }; }
		inline const Vec4& operator / (const T s) { return { x / s, y / s, z / s, w / s }; }
		inline Vec4& operator += (const Vec4& o) { x += o.x; y += o.y; z += o.z; w += o.w; return *this; }
		inline Vec4& operator -= (const Vec4& o) { x -= o.x; y -= o.y; z -= o.z; w -= o.w; return *this; }
		inline Vec4& operator *= (const Vec4& o) { x *= o.x; y *= o.y; z *= o.z; w *= o.w; return *this; }
		inline Vec4& operator /= (const Vec4& o) { x /= o.x; y /= o.y; z /= o.z; w /= o.w; return *this; }
		inline Vec4& operator *= (const T s) { x *= s; y *= s; z *= s; w *= s; return *this; }

		inline Vec4& add3D(const Vec4& o) { x += o.x; y += o.y; z += o.z; return *this; }
		inline Vec4& mult3D(const Vec4& o) { x *= o.x;y *= o.y; z *= o.z; return *this; }
		inline Vec4& mult3D(const T s) { x *= s; y *= s; z *= s; return *this; }
		inline Vec4& div3D(const Vec4& o) { x /= o.x; y /= o.y; z /= o.z; return *this; }
		inline Vec4& div3D(const T s) { x /= s; y /= s; z /= s; return *this; }

		inline static const Vec4& add3D(const Vec4& a, const Vec4& b) { return{ a.x + b.x,a.y + b.y,a.z + b.z }; }
		inline static const Vec4& mult3D(const Vec4& a, const Vec4& b) { return{ a.x * b.x,a.y * b.y,a.z * b.z }; }
		inline static const Vec4& mult3D(const Vec4& a, const T s) { return{ a.x * s,a.y * s,a.z * s }; }
		inline static const Vec4& div3D(const Vec4& a, const Vec4& b) { return{ a.x / b.x,a.y / b.y,a.z / b.z }; }
		inline static const Vec4& div3D(const Vec4& a, const T s) { return{ a.x / s,a.y / s,a.z / s }; }

		inline T& operator [] (const size_t i) { return n[i % 4]; }
	};

	template<typename T>
	inline const Vec4<T>& operator * (const T s, const Vec4<T>& o) { return{ o.x * s, o.y * s, o.z * s, o.w * s }; }

	typedef Vec4<int> Vec4i;
	typedef Vec4<float> Vec4f;
	typedef Vec4<double> Vec4d;

	/*square mat4 struct*/
	template<typename T>
	struct Mat4 {
		Vec4<T> m[4]{ Vec4<T>(0) };

		Vec4<T>& operator [] (const size_t pos) { return m[pos]; }

		const Vec4<T>& row(size_t j) {
			return { m[0][j], m[1][j], m[2][j], m[3][j] };
		}

		void identity() {
			m[0] = { 1,0,0,0 };
			m[1] = { 0,1,0,0 };
			m[2] = { 0,0,1,0 };
			m[3] = { 0,0,0,1 };
		}



		Mat4 operator * (const Mat4& a) {
			Mat4 c;
			for (int i = 0; i < 4; i++) {
				c[i] = {
					Vec4<T>::dotProd4D(this->row(0), m[i]),
					Vec4<T>::dotProd4D(this->row(1), m[i]),
					Vec4<T>::dotProd4D(this->row(2), m[i]),
					Vec4<T>::dotProd4D(this->row(3), m[i])
				};
			}
			return c;
		}

		const Vec4<T>& operator * (const Vec4<T>& vec) {
			return{
				vec.x * m[0][0] + vec.y * m[1][0] + vec.z * m[2][0] + vec.w * m[3][0],
				vec.x * m[0][1] + vec.y * m[1][1] + vec.z * m[2][1] + vec.w * m[3][1],
				vec.x * m[0][2] + vec.y * m[1][2] + vec.z * m[2][2] + vec.w * m[3][2],
				vec.x * m[0][3] + vec.y * m[1][3] + vec.z * m[2][3] + vec.w * m[3][3]
			};
		}
		Mat4 operator * (const T s) {
			return {
				{m[0].x * s, m[0].y * s, m[0].z * s, m[0].w * s},
				{m[1].x * s, m[1].y * s, m[1].z * s, m[1].w * s},
				{m[2].x * s, m[2].y * s, m[2].z * s, m[2].w * s},
				{m[3].x * s, m[3].y * s, m[3].z * s, m[3].w * s}
			};
		}
	};

	template<typename T>
	const Vec4<T>& operator * (const Vec4<T>& vec, const Mat4<T>& mat) {
		return{
			vec.x * mat[0][0] + vec.y * mat[1][0] + vec.z * mat[2][0] + vec.w * mat[3][0],
			vec.x * mat[0][1] + vec.y * mat[1][1] + vec.z * mat[2][1] + vec.w * mat[3][1],
			vec.x * mat[0][2] + vec.y * mat[1][2] + vec.z * mat[2][2] + vec.w * mat[3][2],
			vec.x * mat[0][3] + vec.y * mat[1][3] + vec.z * mat[2][3] + vec.w * mat[3][3]
		};
	}

	typedef Mat4<int> Mat4i;
	typedef Mat4<float> Mat4f;
	typedef Mat4<double> Mat4d;
}