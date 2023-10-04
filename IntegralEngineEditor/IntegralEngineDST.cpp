#include <math.h>

template <typename T>
class LinkedList {
public:
	LinkedList* right;
	LinkedList* left;
	T value;
	LinkedList() {
		this->value = nullptr;
		this->left = nullptr;
		this->right = nullptr;
	}
};

struct Vector3 {
public:
	float x, y, z;
	Vector3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	float Magnitude() {
		return (float)sqrt(x*x + y*y + z*z);
	}

	void Translate(Vector3 v){
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;
	}
	void Translate(float x, float y, float z){
		this->x += x;
		this->y += y;
		this->z += z;
	}
};
struct Quaternion {
public:
	float x, y, z, w;
	Quaternion(float x, float y, float z, float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
};