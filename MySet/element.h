#ifndef elementH
#define elementH
using namespace std;
template <typename T>
class IElement
{

private:
	T value;
	IElement <T> *left;
	IElement <T> *right;
	template <typename T>
	friend class ISet;
public:
	T get_value() const { return value; };
	IElement<T> * get_left() const { return left; };
	IElement<T> * get_right() const { return right; };
	IElement(T avalue = 0, IElement <T> *aleft = NULL, IElement <T> *aright = NULL) : value(avalue), left(aleft), right(aright) {};
	bool operator == (IElement<T> const &el) { return value == el.value; };
	bool operator != (IElement<T> const &el) { return !(*this == el); };

	~IElement() {};
};


#endif