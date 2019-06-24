#include "cxxvec.h"
static const int ALLOCSTEP = 16;
static const int INITALLOC =  8;
template <class TYPE> static void cpy(TYPE **dest, const TYPE *src, size_t n)
{
	size_t i;

	for (i = 0; i < n; ++i)
		(*dest)[i] = src[i];
}

template <class TYPE> static void swap(TYPE *a, TYPE *b)
{
	TYPE tmp;
	
	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void *virtrealloc(void *origblk, size_t newsize, size_t typesize)
{
	throw "Not implemented";
}

template <class TYPE> static TYPE *chr(const TYPE *arr, const TYPE &t, size_t n)
{
	size_t i;

	for (i = 0; i < n; ++i)
		if (arr[i] == t)
			return (TYPE *) arr + i;
	return NULL;
}

template <class TYPE> struct cxxvec<TYPE>::vecimp {
	TYPE *arr;
	size_t n;
	size_t nalloced;
	int ninc;
	vecimp(const TYPE *arr, size_t n)
	{
#ifdef USEMALLOC
		this->arr = (TYPE *) malloc(n * sizeof(TYPE));
#endif
#ifdef USEVALLOC
		this->arr = (TYPE *) VirtualAlloc(NULL, n * sizeof(TYPE), MEM_COMMIT, PAGE_READWRITE);
#endif
		cpy<TYPE>(&this->arr, arr, n);
		this->n = this->nalloced = n;
		this->ninc = 0;
	}
	vecimp(const std::initializer_list<TYPE> &initlist) : arr((TYPE *) malloc(initlist.size() * sizeof(TYPE))), n(initlist.size())
	{
		std::copy(initlist.begin(), initlist.end(), this->arr);
		this->ninc = 0;
		this->nalloced = n;
	}
	vecimp()
	{
#ifdef USEMALLOC
		this->arr = (TYPE *) malloc(INITALLOC * sizeof(TYPE));
#endif
#ifdef USEVALLOC
		this->arr = (TYPE *) VirtualAlloc(NULL, INITALLOC * sizeof(TYPE), MEM_COMMIT, PAGE_READWRITE);
#endif
		this->nalloced = INITALLOC;
		this->n = this->ninc = 0;
	}
	~vecimp()
	{
		this->arr -= ninc;
#ifdef USEMALLOC
		free(this->arr);
#endif
#ifdef USEVALLOC
		VirtualFree(this->arr, 0, MEM_DECOMMIT);
#endif
		this->arr = NULL;
	}
};

template<class TYPE> cxxvec<TYPE>::cxxvec<TYPE>()
{
	this->imp = new vecimp();
}

template <class TYPE> cxxvec<TYPE>::cxxvec<TYPE>(const TYPE *arr, size_t n)
{
	this->imp = new vecimp(arr, n);
}

template <class TYPE> cxxvec<TYPE>::~cxxvec<TYPE>()
{
	delete this->imp;
	this->imp = NULL;
}

template<class TYPE>
TYPE & cxxvec<TYPE>::getfirst()
{
	return this->imp->arr[0];
}

/*
UNCOMMENT THIS:
template<class TYPE>
TYPE & cxxvec<TYPE>::getlast()
{
// 	return this->imp->arr(this->imp->n);
}
*/

template <class TYPE> void cxxvec<TYPE>::print() const
{
	size_t i;

	for (i = 0; i < this->imp->n; ++i)
		std::cout << this->imp->arr[i] << '\n';
}

template<class TYPE> TYPE &cxxvec<TYPE>::operator[](size_t zbpos) const
{
	return this->imp->arr[zbpos];
}

template<class TYPE> TYPE &cxxvec<TYPE>::operator()(size_t obpos) const
{
	return this->imp->arr[obpos - 1];
}

template<class TYPE> TYPE &cxxvec<TYPE>::at(size_t zbpos) const
{
	if (zbpos < 0 || zbpos >= this->imp->n)
		throw "Out of range";

	return this->imp->arr[zbpos];
}

template<class TYPE> cxxvec<TYPE> &cxxvec<TYPE>::operator=(const cxxvec<TYPE> &b)
{
	this->imp = new vecimp(b.imp->arr, b.imp->n);

	return *this;
}

template<class TYPE> cxxvec<TYPE> &cxxvec<TYPE>::operator=(const std::initializer_list<TYPE> &initlist)
{
	this->imp = new vecimp(initlist);
	return *this;
}

template <class TYPE> void cxxvec<TYPE>::append(const TYPE &t)
{
#ifdef USEMALLOC
	if (this->imp->n == this->imp->nalloced) {

		this->imp->arr = (TYPE *) realloc(this->imp->arr,
		    (this->imp->nalloced += ALLOCSTEP) * sizeof(TYPE));
	}
#endif
	this->imp->arr[this->imp->n++] = t;
}

template<class TYPE> void cxxvec<TYPE>::append(const std::initializer_list<TYPE> &appendlist)
{
	size_t i;
	TYPE *arr = new TYPE[appendlist.size()];
	std::copy(appendlist.begin(), appendlist.end(), arr);

	for (i = 0; i < appendlist.size(); ++i)
		this->append(arr[i]);

	delete []arr;
}

template<class TYPE> void cxxvec<TYPE>::prepend(const TYPE &o)
{
	int i;

#ifdef USEMALLOC
	if (this->imp->nalloced == this->imp->n)
		this->imp->arr = (TYPE *) realloc(this->imp->arr, 
							(this->imp->nalloced += ALLOCSTEP) * sizeof(TYPE));
#endif

	for (i = this->imp->n - 1; i >= 0; --i)
		this->imp->arr[i + 1] = this->imp->arr[i];

	*(this->imp->arr) = o;
	++this->imp->n;
}

template<class TYPE> void cxxvec<TYPE>::prepend(const std::initializer_list<TYPE> &prependlist)
{
	int i;

	TYPE *buf = new TYPE[prependlist.size()];

	std::copy(prependlist.begin(), prependlist.end(), buf);

	for (i = prependlist.size() - 1; i >= 0; --i)
		this->prepend(buf[i]);

	delete []buf;
}

template <class TYPE> void cxxvec<TYPE>::del(size_t zbpos)
{
	size_t i;

	for (i = zbpos + 1; i < this->imp->n; ++i)
		this->imp->arr[i - 1] = this->imp->arr[i];

	--this->imp->n;
}

template <class TYPE> void cxxvec<TYPE>::ins(size_t zbpos, const TYPE &t)
{
	size_t i;

#ifdef USEMALLOC
	if (this->imp->nalloced == this->imp->n)
		this->imp->arr = (TYPE *) realloc(this->imp->arr, 
							(this->imp->nalloced += ALLOCSTEP) * sizeof(TYPE));
#endif

	for (i = this->imp->n; i > zbpos; --i)
		this->imp->arr[i + 1] = this->imp->arr[i];
	this->imp->arr[zbpos + 1] = t;
	++this->imp->n;
}

template <class TYPE> bool cxxvec<TYPE>::startswith(const TYPE *arr, size_t n) const
{
	size_t i;

	for (i = 0; i < n; ++i)
		if (arr[i] != this->imp->arr[i])
			return false;
	return true;
}

template <class TYPE> bool cxxvec<TYPE>::startswith(const cxxvec<TYPE> &vecstart) const
{
	return this->startswith(vecstart.imp->arr, vecstart.imp->n);
}

template<class TYPE> bool cxxvec<TYPE>::startswith(const std::initializer_list<TYPE> &seqstart) const
{
	cxxvec<TYPE> arr(seqstart);
	return this->startswith(arr);
}

template <class TYPE> bool cxxvec<TYPE>::endswith(const TYPE *arr, size_t n) const
{
	size_t i = this->imp->n - n;
	if (memcmp(this->imp->arr + i, arr, n) == 0)
		return true;
	return false;
}

template<class TYPE> bool cxxvec<TYPE>::endswith(const cxxvec<TYPE> &vecend) const
{
	return this->endswith(vecend.imp->arr, vecend.imp->n);
}

template<class TYPE> bool cxxvec<TYPE>::endswith(const std::initializer_list<TYPE> &seqend) const
{
	cxxvec<TYPE> cv = seqend;
	return this->endswith(cv);
}

template<class TYPE> bool cxxvec<TYPE>::operator==(const cxxvec<TYPE> &b) const
{
	return memcmp(this->imp->arr, b.imp->arr, b.imp->n) == 0;
}

template <class TYPE> bool cxxvec<TYPE>::operator!=(const cxxvec<TYPE> &b) const
{
	return !(*this == b);
}

template <class TYPE> bool cxxvec<TYPE>::operator>(const cxxvec<TYPE> &b) const
{
	return memcmp(this->imp->arr, b.imp->arr, b.imp->n) > 0;
}

template <class TYPE> bool cxxvec<TYPE>::operator<=(const cxxvec<TYPE> &b) const
{
	return !(*this > b);
}

template <class TYPE> bool cxxvec<TYPE>::operator>=(const cxxvec<TYPE> &b) const
{
	return *this == b || *this > b;
}

template <class TYPE> bool cxxvec<TYPE>::operator<(const cxxvec<TYPE> &b) const
{
	return !(*this >= b);
}

template<class TYPE> void cxxvec<TYPE>::fill(const TYPE &t)
{
	size_t i;

	for (i = 0; i < this->imp->n; ++i)
		this->imp->arr[i] = t;
}

template<class TYPE> void cxxvec<TYPE>::rev()
{
	TYPE *start, *end;

	start = this->imp->arr;
	end = this->imp->arr + this->imp->n - 1;

	for (; end >= start; --end, ++start)
		swap(start, end);
}

template <class TYPE> size_t cxxvec<TYPE>::getn() const
{
	return this->imp->n;
}

template<class TYPE> TYPE *cxxvec<TYPE>::getblk() const
{
	return this->imp->arr;
}

template<class TYPE> bool cxxvec<TYPE>::iscond(bool (*cond)(const TYPE &)) const
{
	size_t i;

	for (i = 0; i < this->imp->n; ++i)
		if (cond(this->imp->arr[i]))
			return true;

	return false;
}

template<class TYPE> bool cxxvec<TYPE>::isempty() const
{
	return this->imp->n == 0;
}

template<class TYPE> void cxxvec<TYPE>::getends(TYPE **start, TYPE **end)
{
	*start = this->imp->arr;
	*end = this->imp->arr + this->imp->n;
}

template<class TYPE> cxxvec<TYPE> cxxvec<TYPE>::first(size_t n)
{
	cxxvec ret = *this;
	ret.imp->n = n;
	
	return ret;
}

template<class TYPE> cxxvec<TYPE> cxxvec<TYPE>::last(size_t n)
{
	cxxvec ret = *this;
	ret += this->imp->n - n;

	return ret;
}

template<class TYPE> cxxvec<TYPE> cxxvec<TYPE>::getrange(size_t lb, incexc ielb, size_t ub, incexc ieub)
{
	TYPE *start, *end;

	start = this->imp->arr + lb - 1;
	end = this->imp->arr + ub;

	return cxxvec(start, ielb, end, ieub);
}

template <class TYPE> cxxvec<TYPE>::cxxvec<TYPE>(const std::initializer_list<TYPE> &initlist)
{
	this->imp = new vecimp(initlist);
}

template<class TYPE> cxxvec<TYPE>::cxxvec<TYPE>(const cxxvec<TYPE> &b)
{
	this->imp = new vecimp(b.imp->arr, b.imp->n);
}

template<class TYPE> cxxvec<TYPE>::cxxvec(TYPE *start, incexc iestart, TYPE *end, incexc ieend)
{
	if (iestart == incexc::EXCLUSIVE)
		++start;
	if (ieend == incexc::EXCLUSIVE)
		--end;

	this->imp = new vecimp(start, end - start);
}

// ptrarith
template <class TYPE> cxxvec<TYPE> &cxxvec<TYPE>::operator+=(size_t i)
{
	this->imp->n -= i;
	this->imp->ninc += i;
	this->imp->arr += i;

	return *this;
}
template <class TYPE>cxxvec<TYPE> cxxvec<TYPE>::operator+(size_t i)
{
	cxxvec<TYPE> tmp = *this;

	tmp += i;

	return tmp;
}
template <class TYPE>cxxvec<TYPE> &cxxvec<TYPE>::operator++()
{
	return *this += (size_t) 1;
}
template <class TYPE>cxxvec<TYPE> &cxxvec<TYPE>::operator-=(size_t i)
{
	this->imp->n += i;
	this->imp->ninc -= i;
	this->imp->arr -= i;

	return *this;
}
template <class TYPE>cxxvec<TYPE> cxxvec<TYPE>::operator-(size_t i)
{
	cxxvec<TYPE> tmp = *this;

	tmp -= i;

	return tmp;
}
template <class TYPE>cxxvec<TYPE> &cxxvec<TYPE>::operator--()
{
	return *this -= (size_t) 1;
}
template <class TYPE>ptrdiff_t cxxvec<TYPE>::operator-(const cxxvec<TYPE> &rhs)
{
	return this->imp->arr - rhs.imp->arr;
}
template <class TYPE>void *cxxvec<TYPE>::operator&()
{
	return (void *) this->imp->arr;
}
template <class TYPE> TYPE &cxxvec<TYPE>::operator*()
{
	return *this->imp->arr;
}

void vecfree(void *arr)
{
#ifdef USEMALLOC
	free(arr);
#endif
#ifdef USEVALLOC
	VirtualFree(arr, 0, MEM_DECOMMIT);
#endif
}

template class cxxvec<int>;