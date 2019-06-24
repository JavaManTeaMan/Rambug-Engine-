#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <stdarg.h>
#include <regex>
#pragma warning(disable:4996)
enum class findstate { FOUND, END, NOTFOUND };
enum class incexc { INCLUSIVE, EXCLUSIVE };
typedef long ssize;
const int FMTSTR = 0;

/**
* @brief This is the main class in the CxxString package. It manages many aspects
* of string manipulation, like dynamic memory allocation, concatenation, simulating
* pointer arithmetic, and more.
*/
class cxxstr {
	struct imp;
	imp *i;
public:
	/* constructors/destructors */
	cxxstr() { }
	/**
	* @brief Creates a `cxxstr` object using a printf format string.
	* @param[in]  reserved    This argument is used to tell apart this
	* overload and the `(const char *, ssize)` constructor overload.
	* @param[in]  fmt         The printf format string. See the printf
	* man pages to see which specifiers and flags are allowed.
	* @param[in]  ...         The variable argument list. This list
	* depends on the string pointed to by `fmt`. 
	* @note If the variable argument list does not match `fmt`, or 
	* `fmt` is NULL the behavior is undefined.
	*/
	cxxstr(int reserved, const char *fmt, ...);
	/**
	* @brief Creates a `cxxstr` object.
	* @param[in]  startaddr   The address of the first character in the string.
	* @param[in]  len         The number of bytes that should be considered, using `startaddr` as the
	* starting address. If this argument is -1, `startadddr` must be null terminated.
	* @note The behavior is undefined if `startaddr` is `NULL`.
	*/
	cxxstr(const char *startaddr, ssize len = -1);
	/**
	* @brief Creates a `cxxstr` object.
	* @param[in]  s    The `std::string` that will be used to initialize
	* this `cxxstr` object.
	*/
	cxxstr(const std::string &s);
	/**
	* @brief Creates a `cxxstr` object between two addresses.
	* @param[in]  start     The address of the first character to consider.
	* @param[in]  iestart   Determines whether the range should start from `start` (`INCLUSIVE`) or if it should
	* start at `start + 1` (`EXCLUSIVE`).
	* @param[in]  end       The address of the last character to consider.
	* @param[in]  ieend     Determines whether the range should end at `end` (`INCLUSIVE`) or if it should end at
	* `end - 1` (`EXCLUSIVE`).
	* @note The behavior is undefined if either `start` or `end` is `NULL`.
	*/
	cxxstr(char *start, incexc iestart, char *end, incexc ieend);
	~cxxstr();

	/* assignment operators */
	/**
	* @brief Assigns a null terminated C style string to this `cxxstr` object.
	* @param[in]  str    A null terminated string containing the data to assign.
	* @return A reference to the modified `cxxstr` object.
	* @note The behavior is undefined if `str` is NULL.
	*/
	cxxstr &operator=(const char *str);
	/**
	* @brief Assigns a C++ `std::string` object to this `cxxstr` object.
	* @param[in] str    The `std::string` containing the data to copy.
	* @return the modified `cxxstr` object
	*/
	cxxstr &operator=(const std::string &str);
	/**
	* @brief Assigns a `cxxstr` object to this `cxxstr` object.
	* @param[in] str    The `cxxstr` containing the data to copy.
	* @return the modified `cxxstr` object
	*/
	cxxstr &operator=(const cxxstr &str);

	/* concatenation */
	/**
	* @brief Concatenates a null terminated string to this `cxxstr` object.
	* @param[in] str    The null terminated string containing the data to append.
	* @return the modified `cxxstr` object
	* @note The behavior is undefined if `str` is NULL.
	*/
	cxxstr &operator+=(const char *str);
	/**
	* @brief Concatenates a `cxxstr` object to this `cxxstr` object.
	* @param[in] str    The `cxxstr` object containing the data to append.
	* @return the modified `cxxstr` object
	*/
	cxxstr &operator+=(const cxxstr &str);
	/**
	* @brief Concatenates a single `char` to this `cxxstr` object.
	* @param[in] c     The `char` that will be added to the end of this `cxxstr` object.
	* @return The `cxxstr` object, but with `c` concatenated to it.
	*/
	cxxstr &operator+=(char c);
	/**
	* @brief Concatenates a single `char` to a `cxxstr` object.
	* @param[in] c     The `char` that will be added to the end of a `cxxstr` object.
	* @return A new `cxxstr` object, with `c` concatenated to it.
	*/
	cxxstr &operator+(char c);
	/**
	* @brief Concatenates a `cxxstr` object to this `cxxstr` object.
	* @param[in] str    The `cxxstr` object containing the data to append.
	* @return the `cxxstr` object with `str` appended to it.
	*/
	cxxstr &operator+(const cxxstr &str);
	/**
	* @brief Concatenates a null terminated string to this `cxxstr` object.
	* @param[in] str    The null terminated string containing the data to append.
	* @return the `cxxstr` object with `str` appended to it.
	* @note The behavior is undefined if `str` is NULL.
	*/
	cxxstr &operator+(const char *str);

	/* pointer arith imitation */
	/**
	* @brief Skips the next `i` characters in memory.
	* @param[in] i    The number of characters to skip.
	* @return The modified `cxxstr` object.
	* @note The behavior is undefined if the `cxxstr` object references memory
	* that is out of bounds.
	*/
	cxxstr &operator+=(size_t i);
	/**
	* @brief Returns a `cxxstr` that references memory `i` characters after
	* the current position.
	* @param[in] i    The number of characters to skip.
	* @return The `cxxstr` that references memory `i` characters after
	* the current position.
	* @note The behavior is undefined if the `cxxstr` object references memory
	* that is out of bounds.
	*/
	cxxstr &operator+(size_t i);
	/**
	* @brief Returns a `cxxstr` that references memory `i` before after
	* the current position.
	* @param[in] i    The number of characters to skip.
	* @return The `cxxstr` that references memory `i` characters after
	* the current position.
	* @note The behavior is undefined if the `cxxstr` object references memory
	* that is out of bounds.
	*/
	cxxstr &operator-(size_t i);
	/**
	* @brief Makes this `cxxstr` object reference the character immediately after the
	* current position.
	* @return The `cxxstr` that references memory 1 character after
	* the current position.
	* @note The behavior is undefined if the `cxxstr` object references memory
	* that is out of bounds.
	*/
	cxxstr &operator++();
	/**
	* @brief Returns a `cxxstr` that references memory 1 character before
	* the current position.
	* @return The `cxxstr` that references memory 1 character before
	* the current position.
	* @note The behavior is undefined if the `cxxstr` object references memory
	* that is out of bounds.
	*/
	cxxstr &operator--();
	/**
	* @brief Slices off the last `nshrink` characters of this `cxxstr` object.
	* @param[in] nshrink    The number of characters to slice off.
	* @return The modified `cxxstr`
	* @note The behavior is undefined if `nshrink` is greater than the current length.
	*/
	cxxstr &operator-=(size_t nshrink);
	/**
	* @brief Gets the number of addresses between two `cxxstr` objects. Note that 
	* this is different than subtraction two pointers to `cxxstr`, because this subtracts 
    * the addresses of the underlying buffers, whereas subtracting two pointers to `cxxstr`
	* subtracts the addresses of the `cxxstr`s themselves.
	* @param[in] right     The right-hand operand. 
	* @return The number of addresses between the two `cxxstr` objects. This value may be
	* negative.
	*/
	ptrdiff_t operator-(const cxxstr &right);

	/* comparison */
	/**
	* @name Comparison Function Documentation
	* In this group, `a` refers to this `cxxstr` object and
	* `b` refers to the other operand. `==` will mean "lexicographically
	*  equal to", `>` will mean "lexicographically greater than",
	* `<` will mean "lexicographically less than",
	* `!=` will mean "lexicographically not equal to",
	* `<=` will mean "lexicographically less than or equal to",
	* `>=` will mean "lexicographically less than" */
	///@{
	/**
	* @brief Performs a case-insensitive comparison of
	* `a` and `b`, a null terminated string.
	* @param[in] b    The null terminated string to compare to
	* @return See the `strcmp` man pages for information about
	* the meaning of the return value.
	*/
	int icmp(const char *b) const;
	/**
	* @brief Performs a case-insensitive comparison of 
	* `a` and b, both `cxxstr` objects.
	* @param[in] b     The `cxxstr` object to compare to
	* @return See the `strcmp` man pages for information about
	* the meaning of the return value.
	* @note The behavior is undefined if `b` is NULL.
	*/
	int icmp(const cxxstr &b) const;
	/**
	* @brief Tells whether two strings are equal.
	* @param[in] b The null terminated string to
	* compare to
	* @return true if `a == b`, false otherwise.
	*/
	bool operator==(const char *b) const;
	/**
	* @brief Tells whether two strings are equal.
	* @param[in] b    The `cxxstr` object to compare to
	* @return true if `a == b`, false otherwise.
	* @note The behavior is undefined if `b` is NULL.
	*/
	bool operator==(const cxxstr &b) const;
	/**
	* @param[in] b The null terminated string to
	* compare to.
	* @return true if `a != b`, false otherwise.
	*/
	bool operator!=(const char *b) const;
	/**
	* @param[in] b The `cxxstr` to
	* compare to.
	* @return true if `a != b`, false otherwise.
	* @note The behavior is undefined if `b` is NULL.
	*/
	bool operator!=(const cxxstr &b) const;
	/**
	* @param[in] b The null terminated string to
	* compare to.
	* @return true if `a > b`, false otherwise.
	*/
	bool operator>(const char *b) const;
	/**
	* @param[in] b The `cxxstr` to
	* compare to.
	* @return true if `a > b`, false otherwise.
	* @note The behavior is undefined if `b` is NULL.
	*/
	bool operator>(const cxxstr &b) const;
	/**
	* @param[in] b The null terminated string to
	* compare to.
	* @return true if `a >= b`, false otherwise.
	*/
	bool operator>=(const char *b) const;
	/**
	* @param[in] b The `cxxstr` to
	* compare to.
	* @return true if `a >= b`, false otherwise.
	* @note The behavior is undefined if `b` is NULL.
	*/
	bool operator>=(const cxxstr &b) const;
	/**
	* @param[in] b The null terminated string to
	* compare to.
	* @return true if `a < b`, false otherwise.
	*/
	bool operator<(const char *b) const;
	/**
	* @param[in] b The `cxxstr` to
	* compare to.
	* @return true if `a < b`, false otherwise.
	* @note The behavior is undefined if `b` is NULL.
	*/
	bool operator<(const cxxstr &b) const;
	/**
	* @param[in] b The null terminated string to
	* compare to.
	* @return true if `a <= b`, false otherwise.
	*/
	bool operator<=(const char *b) const;
	/**
	* @param[in] b The `cxxstr` to
	* compare to.
	* @return true if `a <= b`, false otherwise.
	* @note The behavior is undefined if `b` is NULL.
	*/
	bool operator<=(const cxxstr &b) const;
	///@}

	/* stream operations */
	/**
	* @brief Writes `s` onto the `std::ostream` `os`.
	* @param[in] os    The `std::ostream` that will be written to
	* @param[in] s     The `cxxstr` object that will be written
	* @return The modified `std::ostream`.
	*/
	friend std::ostream &operator<<(std::ostream &os, const cxxstr &s);
	/**
	* @brief Reads from the `std::istream` `is` into the `cxxstr` `s`.
	* @param[in]  is    The `std::istream` that will be read from.
	* @param[out] s     When the function returns, this will contain
	* the string that was just read.
	* @return The modified `std::istream`.
	*/
	friend std::istream &operator>>(std::istream &is, cxxstr &s);
	/**
	* @brief Writes this `cxxstr` onto the `FILE *` `fp`.
	* @param[in] fp    The `FILE *` that will be written to.
	* @note The behavior is undefined if `fp` is `NULL` or is an input stream.
	*/
	void write(FILE *fp = stdout);
	/**
	* @brief Writes this `cxxstr`, followed by a newline, onto the `FILE *` `fp`.
	* @param[in] fp    The `FILE *` that will be written to.
	* @note The behavior is undefined if `fp` is `NULL` or is an input stream.
	*/
	void writeln(FILE *fp = stdout);

	/* getters */
	/**
	* @brief Gets the number of characters in this `cxxstr`.
	* @return the number of characters in this `cxxstr`.
	*/
	size_t getn() const;
	/**
	* @brief Gets the null terminated string equivalent of this `cxxstr`.
	* @return the null terminated string equivalent of this `cxxstr`.
	*/
	char *getstr() const;

	/* misc*/
	/**
	* @brief Converts all lowercase characters to uppercase.
	*/
	void up();
	/**
	* @brief Converts all uppercase characters to lowercase.
	*/
	void dn();
	/**
	* @brief Gets the (zero-based) `zbpos`th character in this `cxxstr`.
	* @param[in] zbpos    The position from which the character is read.
	* @return the (zero-based) `zbpos`th character in this `cxxstr`.
	* @note The behavior is undefined if `zbpos` is out of bounds.
	*/
	char operator[](size_t zbpos) const;
	/**
	* @brief Gets the (zero-based) `zbpos`th character in this `cxxstr`.
	* @param[in] zbpos    The position from which the character is read.
	* @return the (zero-based) `zbpos`th character in this `cxxstr`.
	*/
	char at(size_t zbpos) const;
	/**
	* @brief Gets the first `n` characters of this `cxxstr` object.
	* @param[in] n    The number of initial characters to take
	* @return a pointer to the `cxxstr` that contains the first 
	* `n` characters. This pointer must be freed with `deallocblk`.
	*/
	cxxstr *first(size_t n);
	/**
	* @brief Gets the last `n` characters of this `cxxstr` object.
	* @param[in] n    The number of terminal characters to take
	* @return a pointer to the `cxxstr` that contains the last
	* `n` characters. This pointer must be freed with `deallocblk`.
	*/
	cxxstr *last(size_t n);
	/**
	* @brief Locates the first occurrence of the substring `substr` in this `cxxstr`. 
	* @param[in] substr    The substring that is to be found in this `cxxstr` object.
	* @return a pointer to the `cxxstr` that contains the substring `substr`. It must be
	* freed with `deallocblk`.
	* @note The behavior is undefined if `substr` is NULL.
	*/
	cxxstr *sub(const char *substr) const;
	/**
	* @brief Locates the first occurrence of the substring `substr` in this `cxxstr`.
	* @param[in] substr    The substring that is to be found in this `cxxstr` object.
	* @return a pointer to the `cxxstr` that contains the substring `substr`. It must be
	* freed using the `deallocblk` function.
	* @note The behavior is undefined if `substr` is NULL.
	*/
	cxxstr *sub(const cxxstr &substr) const;
	/**
	* @brief Fills this `cxxstr` with `c`.
	* @param[in] c      The character that will fill the entire `cxxstr`.
	*/
	void fill(char c = '\0');
	/**
	* @brief Finds the next occurrence of the character `c`. This function
	* may be called repeatedly to find occurrences after the first one.
	* @param[in] c      The character that will fill the entire `cxxstr`.
	* @return A pointer to a `cxxstr` containing the occurrence of the character `c`.
	* If NULL, no more occurrences were found. This pointer must be freed with
	* `deallocblk`.
	*/
	cxxstr *find(char c);
	/**
	* @brief Finds the next occurrence of the character `c`, **starting from the end**. This function
	* may be called repeatedly to find occurrences after the first one.
	* @param[in] c      The character that will fill the entire `cxxstr`.
	* @return A pointer to a `cxxstr` containing the occurrence of the character `c`.
	* If NULL, no more occurrences were found. This pointer must be freed with
	* `deallocblk`.
	*/
	cxxstr *findr(char c);
	/**
	* @brief breaks a string into a sequence of zero or more
    * nonempty tokens.
	* @param[in] delims     The delimiters by which to break up the string
	* into tokens.
	* @param[out] arrtoks   When the function returns, this will be an array
	* of pointers to `cxxstr` containing the tokens.
	* @return The number of tokens found.
	* @note The behavior is undefined if `delims` or `arrtoks` are NULL.
	*/
	size_t split(const char *delims, cxxstr **arrtoks);
	/**
	* @brief breaks a string into a sequence of zero or more
	* nonempty tokens.
	* @param[in] delims     The delimiters by which to break up the string
	* into tokens.
	* @param[out] arrtoks   When the function returns, this will be an array
	* of pointers to `cxxstr` containing the tokens.
	* @return The number of tokens found.
	* @note The behavior is undefined if  `arrtoks` is NULL.
	*/
	size_t split(const cxxstr &delims, cxxstr **arrtoks);
	/**
	* @brief Delets the character at the zero-based position `zbpos`. Characters to the right
	* will be shifted to the left.
	* @param[in] zbpos    The zero-based position at which the character will
	* be deleted.
	* @note The behavior is undefined if `zbpos` is out of bounds.
	*/
	void del(size_t zbpos);
	/**
	* @brief Inserts a character at the position **directly after** `zbpos`. Characters to the right
	* will be shifted to the right.
	* @param[in] zbpos    The zero-based position at which the character will
	* be inserted after.
	* @param[in] c        The character to insert
	* @note The behavior is undefined if `zbpos` is out of bounds.
	*/
	void ins(size_t zbpos, char c);
	/**
	* @brief Gets the string in the specified range.
	* @param[in] lb    The zero-based lower bound of the range.
	* @param[in] ielb  Determines whether the range should start from `lb` (`INCLUSIVE`) or
	* from `lb + 1` (`EXCLUSIVE`).
	* @param[in] ub    The zero-based upper bound of the range.
	* @param[in] ieub  Determines whether the range should end at `ub` (`INCLUSIVE`) or
	* at `ub - 1` (`EXCLUSIVE`).
	* @return A pointer to the `cxxstr` containing the new string. It must be freed using
	* `deallocblk`
	*/
	cxxstr *getrange(size_t lb, incexc ielb, size_t ub, incexc ieub);
	/**
	* @brief Determines if this `cxxstr` object ends with the `str` string.
	* @param[in] str    The string that will be checked for being at the end.
	* @return `true` if `str` is at the end, `false` otherwise.
	* @note The behavior is undefined if `str` is `NULL`.
	*/
	bool endswith(const char *str);
	/**
	* @brief Determines if this `cxxstr` object ends with the `str` string.
	* @param[in] str    The string that will be checked for being at the end.
	* @return `true` if `str` is at the end, `false` otherwise.
	*/
	bool endswith(const cxxstr &str);
	/**
	* @brief Determines if this `cxxstr` object starts with the `str` string.
	* @param[in] str    The string that will be checked for being at the start.
	* @return `true` if `str` is at the start, `false` otherwise.
	* @note The behavior is undefined if `str` is `NULL`.
	*/
	bool startswith(const char *str);
	/**
	* @brief Determines if this `cxxstr` object starts with the `str` string.
	* @param[in] str    The string that will be checked for being at the start.
	* @return `true` if `str` is at the start, `false` otherwise.
	*/
	bool startswith(const cxxstr &str);
	/**
	* @brief Determines if this `cxxstr` object matches the `ecmapattern` 
	* regex string.
	* @param[in] ecmapattern    The regex string. This string follows the
	* ECMAScript syntax.
	* @return `true` if a match was found; false otherwise.
	* @note The behavior is undefined if `ecmapattern` is `NULL`.
	*/
	bool regexmatch(const char *ecmapattern);
	/**
	* @brief Determines if this `cxxstr` object matches the `ecmapattern`
	* regex string.
	* @param[in] ecmapattern    The regex string. This string follows the
	* ECMAScript syntax.
	* @return `true` if a match was found; false otherwise.
	*/
	bool regexmatch(const cxxstr &ecmapattern);
	/**
	* @brief Trims all leading whitespace. Whitespace is
	* determined by the `<ctype.h>` function `isspace`.
	*/
	void trimleadwhite();
	/**
	* @brief Trims all trailing whitespace. Whitespace is 
	* determined by the `<ctype.h>` function `isspace`.
	*/
	void trimtrailwhite();
	/**
	* @brief Trims all leading and trailing whitespace. Whitespace
	* is determined by the `<ctype.h>` function `isspace`.
	*/
	void trim();
	/**
	* @brief Determines if at least one character in this `cxxstr` object
	* matches a condition
	* @param[in] cond    A pointer to a function that must have the following signature
	* <code>
	* bool cond(char c);
	* </code>
	* `c` is the character to be tested. If the character satisifies the condition, the function
	* returns `true`. Otherwise, it returns `false`.
	* @return `true` if at least one character satsifies the condition, `false` otherwise.
	*/
	bool iscond(bool (*cond)(char));
	/**
	* @brief Determines if at least one character in this `cxxstr` object
	* matches a condition
	* @param[in] cond    A pointer to a function that must have the following signature
	* <code>
	* int cond(int c);
	* </code>
	* `c` is the integer representation of the character to be tested. If the character satisifies the condition, the function
	* returns `true`. Otherwise, it returns `false`.
	* @return `true` if at least one character satsifies the condition, `false` otherwise.
	*/
	bool iscond(int (*cond)(int));
};
template <class T> void arrdealloc(T *);
template <class T> void blkdealloc(T *);
template <class T> void dealloc(T *);

#include "deallocators.tpp"