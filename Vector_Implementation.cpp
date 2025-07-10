#include<iostream>
#include<vector>
using namespace std;

class Vector {
public:
	Vector();
	~Vector();
	Vector(const Vector& v);
	Vector& operator= (const Vector& v);
	void push_back(float f);
	void push_front(float value);
	void pop_back();
	void pop_front();
	float& at(int index);
	float& operator[](int index);
	float& front();
	float& back();
	int size() const;
	int capacity() const;
	bool empty() const;
	bool full() const;
	void resize(int num, float elem = 0);
	void clear();
	void insert(int index, float value);
	void erase(int index);
private:
	void resizeCapacity(int num);
	float* data;
	int Size, Capacity;
};

Vector::Vector()
{
	Capacity = 4;
	Size = 0;
	data = new float[Capacity];
}

Vector::Vector(const Vector& V)
{
	Capacity = V.Capacity;
	Size = V.Size;
	data = new float[Capacity];
}

Vector& Vector::operator=(const Vector& V)
{
	if (this == &V)
		return *this;
	Capacity = V.Capacity;
	Size = V.Size;
	delete[] data;
	data = new float[Capacity];
	for (int i = 0; i < Size; i++)
		data[i] = V.data[i];
	return *this;
}

Vector::~Vector()
{
	delete[] data;
}

void Vector::push_back(float V)
{
	if (full())
		resizeCapacity(Capacity * 2);
	data[Size] = V;
	Size++;
}

void Vector::push_front(float V)
{
	if (full())
		resizeCapacity(Capacity * 2);
	for (int i = Size; i < 0; i++)
		data[i] = data[i - 1];
	data[0] = V;
	Size++;
}

void Vector::pop_back()
{
	if (Size != 0)
		Size--;
}

void Vector::pop_front()
{
	if (!empty())
		for (int i = 0; i < Size - 1; i++)
			data[i] = data[i + 1];
	Size--;
}
float& Vector::at(int index)
{
	return data[index];
}

float& Vector::operator[](int index)
{
	return data[index];
}

float& Vector::front()
{
	return data[0];
}

float& Vector::back()
{
	return data[Size - 1];
}

void Vector::resizeCapacity(int num)
{
	Capacity = num;
	float* newData = new float[Capacity];

	if (Size > Capacity)
		Size = Capacity;

	for (int i = 0; i < Size; i++)
	{
		newData[i] = data[i];
	}
	delete[] data;
	data = newData;
}

void Vector::resize(int s, float V)
{
	resizeCapacity(s);
	if (Capacity > Size)
		for (int i = Size; i < Capacity; i++)
			data[i] = V;
	Size = s;
}

void Vector::insert(int index, float V)
{
	float* newData = new float[Capacity];
	if (full())
		resizeCapacity(Capacity * 2);
	for (int i = Size; i < index; i++)
		data[i] = data[i - 1];
	data[index] = V;
}

void Vector::erase(int index)
{
	for (int i = index; i < Size - 1; i++)
		data[i] = data[i + 1];
	Size--;
}
void Vector::clear()
{
	Size = 0;
}

bool Vector::empty() const
{
	return Size == 0 ? true : false;
}

int Vector::size() const
{
	return Size;
}

int Vector::capacity() const
{
	return Capacity;
}
bool Vector::full() const
{
	return Size == Capacity ? true : false;
}

void main()
{
	Vector v;
	v.push_back(2);
	v.push_back(10);
	v.push_back(5);
	v.push_back(3);
	v.pop_front();
	cout << v.front() << endl;
	v.front() = 2;
	cout << v.front() << endl;
}