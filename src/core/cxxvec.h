#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <ostream>
#include <Windows.h>
/**
* @brief The main class in the cxxvec package. This 
* class allows you to manipulate dynamically allocated
* arrays. This container allows for any type to be used,
* because templates are used.
* @tparam TYPE    The type of the objects that will be used in
* this class.
*/

#define USEMALLOC

typedef long ssize;
enum class incexc { INCLUSIVE, EXCLUSIVE };
template <class TYPE> class cxxvec {
	struct vecimp;
	vecimp *imp;
public:
	/* constructors/destructor */
	/**
	* @brief Creates a blank cxxvec
	* object. Memory is allocated 
	* for the underlying buffer.
	*/
	cxxvec();
	/**
	* @brief Creates a cxxvec object
	* which is initialized to the array
	* pointed to by `arr`, with the size
	* of `n`.
	* @param[in] arr    A pointer to the first element
	* of the array.
	* @param[in] n      The number of elements in 
	* the array pointed to by `arr`.
	* @note If `arr` is NULL or an invalid pointer, or `n` is greater than the number of actual
	* elements pointed to by `arr`, the behavior is undefined.
	*/
	cxxvec(const TYPE *arr, size_t n);
	/**
	* @brief Creates a cxxvec object which is initialized to a C++ 
	* `std::initializer_list` object.
	* @param[in] initlist The sequence that will be used to initialize
	* this `cxxvec` object.
	*/
	cxxvec(const std::initializer_list<TYPE> &initlist);
	/**
	* @brief The copy constructor
	* @param[in] cv    The cxxvec object to copy.
	*/
	cxxvec(const cxxvec &cv);
	cxxvec(TYPE *start, incexc iestart, TYPE *end, incexc ieend);
	~cxxvec();

	/**
	* @brief Gets the first object in this `cxxvec` object
	*/
	TYPE &getfirst();
	/**
	* @brief Gets the last object in this `cxxvec` object
	*/
	TYPE &getlast();

	/* assignment */
	/**
	* @brief Assigns the `cv` object to thsi `cxxvec` object.
	* @return The assigned `cxxvec` object.
	*/
	cxxvec &operator=(const cxxvec &cv);
	/**
	* @brief Assigns a C++ `std::initializer_list` object
	* to this `cxxvec` object.
	* @param[in] initlist    The initializer list to use.
	* @return The result of the assignment.
	*/
	cxxvec &operator=(const std::initializer_list<TYPE> &initlist);

	/* comparison */
	/**
	* @name Comparison Function Documentation
	* In this group, `a` refers to this `cxxvec` object and
	* `b` refers to the other operand. `==` will mean "lexicographically
	*  equal to", `>` will mean "lexicographically greater than",
	* `<` will mean "lexicographically less than",
	* `!=` will mean "lexicographically not equal to",
	* `<=` will mean "lexicographically less than or equal to",
	* `>=` will mean "lexicographically less than" */
	///@{
	/**
	* @brief Compares two cxxvec objects. 
	* @param[in] b    The cxxvec object to compare to.
	* @return `true` if `a == b`, `false` otherwise.
	*/
	bool operator==(const cxxvec &b) const;
	/**
	* @brief Compares two cxxvec objects.
	* @param[in] b    The cxxvec object to compare to.
	* @return `true` if `a != b`, `false` otherwise.
	*/
	bool operator!=(const cxxvec &b) const;
	/**
	* @brief Compares two cxxvec objects.
	* @param[in] b    The cxxvec object to compare to.
	* @return `true` if `a > b`, `false` otherwise.
	*/
	bool operator>(const cxxvec &b) const;
	/**
	* @brief Compares two cxxvec objects.
	* @param[in] b    The cxxvec object to compare to.
	* @return `true` if `a <= b`, `false` otherwise.
	*/
	bool operator<=(const cxxvec &b) const;
	/**
	* @brief Compares two cxxvec objects.
	* @param[in] b    The cxxvec object to compare to.
	* @return `true` if `a >= b`, `false` otherwise.
	*/
	bool operator>=(const cxxvec &b) const;
	/**
	* @brief Compares two cxxvec objects.
	* @param[in] b    The cxxvec object to compare to.
	* @return `true` if `a < b`, `false` otherwise.
	*/
	bool operator<(const cxxvec &b) const;
	///@}

	/* pointer arith imitation */
	cxxvec &operator+=(size_t);
	cxxvec operator+(size_t);
	cxxvec &operator++();

	cxxvec &operator-=(size_t);
	cxxvec operator-(size_t);
	cxxvec &operator--();
	ptrdiff_t operator-(const cxxvec &);

	void *operator&();
	TYPE &operator*();

	/* misc */
	/**
	* @brief Writes each element of this `cxxvec` object to the standard output.
	* Each object will be written on its own line. The object's `operator<<` will be
	* called, so that it may be displayed.
	*/
	void print() const;
	/**
	* @brief Gets the `zbpos`-th zero-based element in the current `cxxvec` object.
	* @param[in] zbpos    The position whose value will be obtained.
	* @return The object located at the `zbpos`-th zero-based position.
	* @note If `zbpos` is out of range, the behavior is undefined.
	*/
	TYPE &operator[](size_t zbpos) const;
	/**
	* @brief Gets the `obpos`-th one-based element in the current `cxxvec` object.
	* @param[in] obpos The position whose value will be obtained.
	* @return The object located at the `obpos`-th one-based position.
	* @note If `obpos` is out of range, the behavior is undefined.
	*/
	TYPE &operator()(size_t obpos) const;
	/**
	* @brief Gets the `zbpos`-th zero-based element in the current `cxxvec` object.
	* @param[in] zbpos    The position whose value will be obtained.
	* @return The object located at the `zbpos`-th zero-based position.
	* @note This function throws a `const char *` containing the error message if 
	* the position is out of range.
	*/
	TYPE &at(size_t zbpos) const;
	/**
	* @brief Appends the object `o` to this cxxvec object.
	* @param[in] o    The object to append
	*/
	void append(const TYPE &o);
	/**
	* @brief Appends a C++ `initializer_list` to this cxxvec object.
	* @param[in] appendlist    The list of objects that will be appended.
	*/
	void append(const std::initializer_list<TYPE> &appendlist);
	/**
	* @brief Prepends the object `o` to this cxxvec object.
	* @param[in] o    The object that will be prepended.
	*/
	void prepend(const TYPE &o);
	/**
	* @brief Prepends a C++ `initializer_list` to this cxxvec object.
	* @param[in] prependlist    The list of objects that will be prepended.
	*/
	void prepend(const std::initializer_list<TYPE> &prependlist);
	/**
	* @brief Deletes the object at the zero-based position `zbpos`.
	* @param[in] zbpos    The zero-based position at which the object will be deleted
	* @note If `zbpos` is out of range, the behavior is undefined.
	*/
	void del(size_t zbpos);
	/**
	* @brief Inserts the object `o` directly **after** the zero-based position `zbpos`.
	* @param[in] zbpos    The zero-based position directly after which the object will be deleted.
	* @param[in] o        The object to insert.
	* @note If `zbpos` is out of range, the behavior is undefined.
	*/
	void ins(size_t zbpos, const TYPE &o);
	/**
	* @brief Determines if this cxxvec object starts with a given sequence.
	* @param[in] arrstart  A pointer to the first element of the array to find.
	* @param[in] n         The number of elements in the array pointed to by `arrstart`.
	* @return `true` if this cxxvec object starts with `arrstart`, false otherwise.
	* @note If `arrstart` is NULL or an invalid pointer, or `n` is greater than the number of actual elements 
	* pointed to by `arrstart`, the behavior is undefined.
	*/
	bool startswith(const TYPE *arrstart, size_t n) const;
	/**
	* @brief Determines if this cxxvec object starts with a given sequence.
	* @param[in] start  The `cxxvec` object to find.
	* @return `true` if this cxxvec object starts with `start`, false otherwise.
	*/
	bool startswith(const cxxvec &start) const;
	/**
	* @brief Determines if this cxxvec object starts with a C++ `initializer_list`.
	* @param[in] start  The list to find.
	* @return `true` if this cxxvec object starts with `start`, false otherwise.
	*/
	bool startswith(const std::initializer_list<TYPE> &start) const;
	/**
	* @brief Determines if this cxxvec object ends with a given sequence.
	* @param[in] arrend    A pointer to the first element of the array to find.
	* @param[in] n         The number of elements in the array pointed to by `arrend`.
	* @return `true` if this cxxvec object ends with `arrstart`, false otherwise.
	* @note If `arrend` is NULL or an invalid pointer, or `n` is greater than the number of actual elements
	* pointed to by `arrend`, the behavior is undefined.
	*/
	bool endswith(const TYPE *arrend, size_t n) const;
	/**
	* @brief Determines if this cxxvec object ends with a given sequence.
	* @param[in] end  The `cxxvec` object to find.
	* @return `true` if this cxxvec object end with `start`, false otherwise.
	*/
	bool endswith(const cxxvec &end) const;
	/**
	* @brief Determines if this cxxvec object ends with a C++ `initializer_list`.
	* @param[in] end  The list to find.
	* @return `true` if this cxxvec object end with `start`, false otherwise.
	*/
	bool endswith(const std::initializer_list<TYPE> &end) const;
	/**
	* @brief Fills the entire cxxvec object with the object `o`.
	* @param[in] o    The object to fill the array with
	*/
	void fill(const TYPE &o);
	/**
	* @brief Reverses the contents of this cxxvec object.
	*/
	void rev();
	/**
	* @brief Gets the number of elements in this cxxvec object's contents.
	*/
	size_t getn() const;
	/**
	* @brief Returns the underlying buffer in this cxxvec object. It must be
	* freed with `vecfree`.
	*/
	TYPE *getblk() const;
	/**
	* @brief Determines if at least one element in this `cxxvec` object satisfies
	* the condition given by the function pointer `cond`.
	* @param[in] cond A pointer to a function that will determine if the object satisfies
	* a condition. The argument to this function pointer is the object to evaluate. If 
	* the object satisfies your condition, return `true` from this function pointer. Otherwise, 
	* return `false`.
	* @return `true` if at least one object satsfies the condition, `false` otherwise.
	* @note If `cond` is NULL or an invalid pointer, the behavior is undefined.
	*/
	bool iscond(bool (*cond)(const TYPE &)) const;
	/**
	* @brief Determines whether this `cxxvec` object contains no elements.
	*/
	bool isempty() const;
	/**
	* @brief Retrieves the addresses of the first and last elements of this `cxxvec` object.
	* @param[out] start    When the function returns `*start` will contain the address of the 
	* first element.
	* @param[out] end      When the function returns, `*end` will contain the address of the 
	* last element.
	* @note If either `start` or `end` is NULL or an invalid pointer, the behavior is undefined.
	*/
	void getends(TYPE **start, TYPE **end);

	/**
	* @brief Gets the first `n` characters in this `cxxvec` object.
	* @param[in] n    The number of characters to get from the start
	* @return the `cxxvec` object containing the first `n` objects.
	*/
	cxxvec first(size_t n);
	/**
	* @brief Gets the last `n` characters in this `cxxvec` object.
	* @param[in] n    The number of characters to get from the end
	* @return the `cxxvec` object containing the last `n` objects.
	*/
	cxxvec last(size_t n);
	/**
	* @brief Gets the string in the specified range.
	* @param[in] lb    The zero-based lower bound of the range.
	* @param[in] ielb  Determines whether the range should start from `lb` (`INCLUSIVE`) or
	* from `lb + 1` (`EXCLUSIVE`).
	* @param[in] ub    The zero-based upper bound of the range.
	* @param[in] ieub  Determines whether the range should end at `ub` (`INCLUSIVE`) or
	* at `ub - 1` (`EXCLUSIVE`).
	* @return A `cxxvec` containing the new string.	*/
	cxxvec getrange(size_t lb, incexc ielb, size_t ub, incexc ieub);
};
/**
* @brief This function frees the memory returned by member functions of the `cxxvec` class.
* Nothing happens if `ptr` is NULL.
* @param[in] ptr    The block that will be freed.
*/
void vecfree(void *ptr);

typedef cxxvec<char> cxxstrv;