#include "cxxstr.h"

static const size_t INITALLOC = 16;
static const size_t ALLOCSTEP = 8;

void memcat(void *dest, const void *src, size_t ndest, size_t nsrc)
{
	unsigned char *bydest = (unsigned char *) dest;
	unsigned char *bysrc = (unsigned char *) src;
	size_t i;

	for (i = 0; i < ndest; ++i, ++bydest)
		;

	for (i = 0; i < nsrc; ++i)
		*bydest++ = *bysrc++;
}
unsigned char *memmem(const void *blk, const void *sub, size_t nblk, size_t nsub)
{
	unsigned char *byblk = (unsigned char *) blk;
	unsigned char *bysub = (unsigned char *) sub;
	size_t i;

	for (i = 0; i < nblk; ++i, ++byblk)
		if (memcmp(byblk, bysub, nsub) == 0)
			return byblk;
	return NULL;
}

struct cxxstr::imp {
	// non null terminated
	char *ptrmem;
	size_t n;
	int ninc;
	imp(const char *str)
	{
		this->n = strlen(str);
		this->ptrmem = strdup(str);

		ninc = 0;
	}
	imp(const char *str, size_t len)
	{
		this->n = len;
		this->ptrmem = (char *) malloc(len);
		memcpy(this->ptrmem, str, len);

		ninc = 0;
	}
	~imp()
	{
		this->ptrmem -= ninc;	// restore pointer returned by malloc
		free(this->ptrmem);
	}
};

cxxstr::cxxstr(int, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	this->i = new imp(fmt);
	vsprintf(this->i->ptrmem, fmt, ap);
	va_end(ap);
	this->i->n = strlen(this->i->ptrmem);
}

cxxstr::cxxstr(const char *str, ssize len)
{
	if (len != -1)
		this->i = new imp(str, len);
	else
		this->i = new imp(str);
}

cxxstr::cxxstr(const std::string &s) : cxxstr(s.c_str(), -1) { }

cxxstr::cxxstr(char *start, incexc iestart, char *end, incexc ieend)
{
	char *pend = end;
	if (ieend == incexc::EXCLUSIVE)
		--pend;

	*pend = '\0';

	this->i = new imp((iestart == incexc::INCLUSIVE) ? start : start + 1);
}

cxxstr &cxxstr::operator=(const char *str)
{
	//delete this->i;

	this->i = new imp(str);

	return *this;
}

cxxstr &cxxstr::operator=(const std::string &s)
{
	return *this = s.c_str();
}

cxxstr &cxxstr::operator=(const cxxstr &s)
{
	char c = s.i->ptrmem[s.i->n];
	s.i->ptrmem[s.i->n] = '\0';

	*this = s.i->ptrmem;

	s.i->ptrmem[s.i->n] = c;
	return *this;
}

cxxstr &cxxstr::operator+=(const char *src)
{
	size_t srclen = strlen(src);
	size_t newlen = this->i->n + srclen;

	this->i->ptrmem = (char *) realloc(this->i->ptrmem, newlen);
	memcat(this->i->ptrmem, src, this->i->n, srclen);

	this->i->n = newlen;
	return *this;
}

cxxstr &cxxstr::operator+=(const cxxstr &src)
{
	/* we don't need to remove this null terminater because it will be overwritten
	   by the operator+= call */
	src.i->ptrmem[src.i->n] = '\0';

	*this += src.i->ptrmem;

	return *this;
}

cxxstr &cxxstr::operator+=(char c)
{
	char append[2];
	*append = c;
	append[1] = '\0';

	return *this += append;
}

cxxstr &cxxstr::operator+(char c)
{
	char s[2];
	*s = c;
	s[1] = '\0';

	return *this + s;
}

cxxstr &cxxstr::operator+=(size_t i)
{
	this->i->ptrmem += i;
	this->i->n -= i;
	this->i->ninc += i;

	return *this;
}

cxxstr &cxxstr::operator+(size_t i)
{
	return *this + i;
}

cxxstr &cxxstr::operator+(const cxxstr &append)
{
	return *this += append;
}

cxxstr &cxxstr::operator+(const char *str)
{
	return *this + cxxstr(str);
}

cxxstr &cxxstr::operator-(size_t i)
{
	this->i->ninc -= i;
	this->i->ptrmem -= i;
	this->i->n += i;

	return *this;
}

cxxstr &cxxstr::operator-=(size_t nshrink)
{
	this->i->n -= nshrink;

	return *this;
}

ptrdiff_t cxxstr::operator-(const cxxstr &right)
{
	return this->i->ptrmem - right.i->ptrmem;
}

cxxstr &cxxstr::operator++()
{
	--this->i->n;
	++this->i->ptrmem;
	++this->i->ninc;

	return *this;
}

cxxstr &cxxstr::operator--()
{
	++this->i->n;
	--this->i->ptrmem;
	--this->i->ninc;

	return *this;
}

void cxxstr::up()
{
	char *str = this->i->ptrmem;
	size_t i;
	for (i = 0; i < this->i->n; ++i)
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 'a' - 'A';
}

void cxxstr::dn()
{
	char *str = this->i->ptrmem;
	size_t i;
	for (i = 0; i < this->i->n; ++i)
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 'a' - 'A';
}

bool cxxstr::operator==(const char *str) const
{
	return memcmp(this->i->ptrmem, str, this->i->n) == 0;
}

int cxxstr::icmp(const char *str) const
{
	char *a = (char *) str;
	char *b = this->i->ptrmem;

	for ( ; ; ++a, ++b) {
		int d = tolower(*a) - tolower(*b);
		if (d != 0 || !*a)
			return d;
	}
}

int cxxstr::icmp(const cxxstr &cs) const
{
	int ret;
	char c = cs.i->ptrmem[cs.i->n];
	cs.i->ptrmem[cs.i->n] = '\0';

	ret = this->icmp(cs.i->ptrmem);

	cs.i->ptrmem[cs.i->n] = c;

	return ret;
}

bool cxxstr::operator==(const cxxstr &cs) const
{
	return *this == cs.i->ptrmem;
}

bool cxxstr::operator!=(const char *str) const
{
	return !(*this == str);
}

bool cxxstr::operator!=(const cxxstr &cs) const
{
	return *this != cs.i->ptrmem;
}

bool cxxstr::operator>(const char *o) const
{
	return memcmp(this->i->ptrmem, o, this->i->n) > 0;
}

bool cxxstr::operator>(const cxxstr &cs) const
{
	return *this > cs.i->ptrmem;
}

bool cxxstr::operator>=(const char *str) const
{
	return memcmp(this->i->ptrmem, str, this->i->n) >= 0;
}

bool cxxstr::operator>=(const cxxstr &cs) const
{
	return *this >= cs.i->ptrmem;
}

bool cxxstr::operator<(const char *str) const
{
	return memcmp(this->i->ptrmem, str, this->i->n) < 0;
}

bool cxxstr::operator<(const cxxstr &cs) const
{
	return *this < cs.i->ptrmem;
}

bool cxxstr::operator<=(const char *str) const
{
	return memcmp(this->i->ptrmem, str, this->i->n) <= 0;
}

bool cxxstr::operator<=(const cxxstr &cs) const
{
	return *this <= cs.i->ptrmem;
}

char cxxstr::operator[](size_t zbpos) const
{
	return this->i->ptrmem[zbpos];
}

void cxxstr::write(FILE *fp)
{
	if (fp == NULL || fp == stdin)
		abort();
	fwrite(this->i->ptrmem, 1, this->i->n, fp);
}

void cxxstr::writeln(FILE *fp)
{
	this->write(fp);
	putchar('\n');
}

char cxxstr::at(size_t zbpos) const
{
	if (zbpos > this->i->n || zbpos < 0)
		throw "Index out of range";
	return this->i->ptrmem[zbpos];
}

cxxstr *cxxstr::sub(const char *sub) const
{
	char *ptr;
	if ((ptr = (char *) memmem(this->i->ptrmem, sub, this->i->n, strlen(sub))) == NULL)
		return NULL;
	return new cxxstr(ptr);
}

cxxstr *cxxstr::sub(const cxxstr &cs) const
{
	return NULL;
}

void cxxstr::fill(char c)
{
	memset(this->i->ptrmem, c, this->i->n);
}

cxxstr *cxxstr::first(size_t n)
{
	cxxstr *ret = new cxxstr(this->i->ptrmem);
	ret->i->n = n;

	return ret;
}

cxxstr *cxxstr::last(size_t n)
{
	cxxstr *ret;
	char *ptr;

	ptr = (this->i->ptrmem + this->i->n) - n;
	ret = new cxxstr(ptr);

	return ret;
}

cxxstr::~cxxstr()
{
	delete this->i;
}

size_t cxxstr::getn() const
{
	return this->i->n;
}

char *cxxstr::getstr() const
{
	return this->i->ptrmem;
}

cxxstr *cxxstr::find(char c)
{
	static void *cur = this->i->ptrmem;
	void *ptr;

	if ((ptr = memchr(cur, c, this->i->n)) == NULL) {
		// reset the pointer at the end of the search
		cur = this->i->ptrmem;
		return NULL;
	}
	cur = ((char *) ptr) + 1;
	return new cxxstr((char *) ptr, 0);
}

cxxstr *cxxstr::findr(char c)
{
	static char *ptr = this->i->ptrmem + this->i->n;

	for (; ptr >= this->i->ptrmem; --ptr)
		if (*ptr == c) {
			--ptr;
			return new cxxstr(ptr);
		}
	// reset the pointer at the end of the search
	ptr = this->i->ptrmem + this->i->n;
	return NULL;
}

size_t cxxstr::split(const char *delims, cxxstr **arr)
{
	char *ptr;
	size_t i = 0, nalloced;

	*arr = (cxxstr *) malloc(INITALLOC * sizeof(cxxstr));
	nalloced = INITALLOC;
	for (ptr = strtok(this->i->ptrmem, delims); ptr; ptr = strtok(NULL, delims), ++i) {
		if (i == nalloced)
			*arr = (cxxstr *) realloc(*arr, nalloced += ALLOCSTEP);
		(*arr)[i] = ptr;
	}
	return i;
}

size_t cxxstr::split(const cxxstr &delims, cxxstr **arrtoks)
{
	return this->split(delims.i->ptrmem, arrtoks);
}

void cxxstr::del(size_t zbpos)
{
	size_t i;
	for (i = zbpos + 1; i < this->i->n; ++i)
		this->i->ptrmem[i - 1] = this->i->ptrmem[i];
	this->i->n--;
}

void cxxstr::ins(size_t zbpos, char c)
{
	this->i->ptrmem = (char *) realloc(this->i->ptrmem, this->i->n + 1);
	size_t i;

	for (i = this->i->n; i > zbpos; --i)
		this->i->ptrmem[i + 1] = this->i->ptrmem[i];
	this->i->ptrmem[zbpos + 1] = c;
	++this->i->n;
}

cxxstr *cxxstr::getrange(size_t lb, incexc ielb, size_t ub, incexc ieub)
{
	char *start, *end;

	start = this->i->ptrmem + lb;
	end = this->i->ptrmem + ub + 1;

	return new cxxstr(start, ielb, end, ieub);
}

bool cxxstr::endswith(const char *str)
{
	size_t i = this->i->n - strlen(str);
	if (memcmp(this->i->ptrmem + i, str, 3) == 0)
		return true;
	return false;
}

bool cxxstr::endswith(const cxxstr &s)
{
	s.i->ptrmem[s.i->n] = '\0';
	return this->endswith(s.i->ptrmem);
}

bool cxxstr::startswith(const char *str)
{
	return memcmp(this->i->ptrmem, str, strlen(str)) == 0;
}

bool cxxstr::startswith(const cxxstr &str)
{
	str.i->ptrmem[str.i->n] = '\0';
	return this->startswith(str.i->ptrmem);
}

void cxxstr::trimleadwhite()
{
	size_t i = 0;

	while (isspace(this->i->ptrmem[i++]))
		;
	*this = *this + (i - 1);
}

void cxxstr::trimtrailwhite()
{
	size_t i;

	for (i = this->i->n - 1; isspace(this->i->ptrmem[i]); --i)
		;
	*this -= this->i->n - i;
}

void cxxstr::trim()
{
	trimtrailwhite();
	trimleadwhite();
}

bool cxxstr::iscond(bool (*cond)(char))
{
	size_t i;

	for (i = 0; i < this->i->n; ++i)
		if (cond(this->i->ptrmem[i]))
			return true;

	return false;
}

bool cxxstr::iscond(int (*cond)(int))
{
	size_t i;

	for (i = 0; i < this->i->n; ++i)
		if (cond(this->i->ptrmem[i]))
			return true;
	return false;
}

bool cxxstr::regexmatch(const char *ecmapattern)
{
	std::regex re(this->i->ptrmem);
	return std::regex_match(ecmapattern, re);
}

bool cxxstr::regexmatch(const cxxstr &ecmapattern)
{
	bool ret;
	char c = ecmapattern.i->ptrmem[ecmapattern.i->n];
	ecmapattern.i->ptrmem[ecmapattern.i->n] = '\0';

	ret = this->regexmatch(ecmapattern.i->ptrmem);
	ecmapattern.i->ptrmem[ecmapattern.i->n] = c;

	return ret;
}

std::ostream &operator<<(std::ostream &os, const cxxstr &cs)
{
	return os.write(cs.i->ptrmem, cs.i->n);
}

std::istream &operator>>(std::istream &is, cxxstr &cs)
{
	std::string s;
	std::getline(is, s);
	cs = s.c_str();

	return is;
}
