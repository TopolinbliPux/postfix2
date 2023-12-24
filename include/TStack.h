#ifndef _TSTACK_H_ 
#define _TSTACK_H_

#include <iostream>
using namespace std;

template <typename T>
class TStack
{
private:
	size_t lenSt;
	T* pMem;
	size_t top;
public:

	TStack() {
		top = -1;
		lenSt = 1;
		pMem = new T[1]();
	}

	~TStack() {
		delete [] pMem;
	}

	bool isEmpty() const {
		if (top == -1) { return true; }
		else return false;
	}

	void push(T value) {
		if (top == lenSt - 1)
		{
			T* tmp = new T[2 * lenSt];
			copy(pMem, pMem + lenSt, tmp);
			delete[] pMem;
			pMem = tmp;
			lenSt = 2 * lenSt;
		}
		top = top + 1;
		pMem[top] = value;
	}

	void pop() {//удаление элемента из вершины стека
		if (top == -1) {
			throw "out of range";
		}
		top--;
	}

	T pop() {//возвращение элемента из вершины стека
		if (!isEmpty()) return pMem[lenSt - 1];
		else throw "out of range";
	}

	TStack& operator=(TStack& st)//копирование стека
	{
		if (this != st) {
			delete[] pMem;
			lenSt = st.lenSt;
			top = st.top;
			pMem = new T[lenSt];
			for (size_t i = 0; i < top+1; i++) {
				pMem[i] = st.pMem[i];
			}
		}
	}

	TStack(TStack& st)
	{
		lenSt = st.lenSt;
		top = st.top;
		pMem = st.pMem;
		for (size_t i = 0; i < top+1; i++) 
		{
			pMem[i] = st.pMem[i];
		}
	}

	bool operator==(TStack& st)
	{
		if (top != st.top) return false;
		else {
			for (size_t i = 0; i < top + 1; i++)
			{
				if (pMem[i] != st.pMem[i])return false;
			}
		}
		return true;
	}

	T Top() {
		if (top == -1)
			throw "out of range";
		return (pMem[top]);
	}

	friend ostream& operator<<(ostream& ostr, const TStack& st) {
		for (size_t i = 0; i < st.top; i++)
			ostr << st.pMem[i] << ' ';
		return ostr;
	}
};
#endif