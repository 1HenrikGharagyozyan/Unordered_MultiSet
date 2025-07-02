#pragma once

#include "HashTable.h"

template<typename Key, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>>
class Unordered_Multiset 
{
private:
	using Table = HashTable<Key, EmptyStruct, Hash, KeyEqual, true>;
	Table _table;

public:
	using key_type = Key;
	using value_type = Key;
	using hasher = Hash;
	using key_equal = KeyEqual;
	using size_type = typename Table::size_type;
	using difference_type = std::ptrdiff_t;

	using reference = const Key&;
	using const_reference = const Key&;
	using pointer = const Key*;
	using const_pointer = const Key*;

private:
	template<bool IsConst>
	class Iterator 
	{
		using TableIterator = std::conditional_t<IsConst, typename Table::const_iterator, typename Table::iterator>;
		TableIterator _it;

	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = Key;
		using reference = const Key&;
		using pointer = const Key*;
		using difference_type = std::ptrdiff_t;

		Iterator() = default;
		explicit Iterator(TableIterator it);

		reference operator*() const;
		pointer operator->() const;

		Iterator& operator++();
		Iterator operator++(int);

		bool operator==(const Iterator& other) const;
		bool operator!=(const Iterator& other) const;

		TableIterator base() const;
	};

public:
	using iterator = Iterator<false>;
	using const_iterator = Iterator<true>;

	Unordered_Multiset() = default;

	explicit Unordered_Multiset(size_type bucket_count, const hasher& hash = hasher(), const key_equal& equal = key_equal());

	template<typename InputIt>
	Unordered_Multiset(InputIt first, InputIt last,
		size_type bucket_count = 16, const hasher& hash = hasher(), const key_equal& equal = key_equal());

	Unordered_Multiset(std::initializer_list<value_type> init,
		size_type bucket_count = 16, const hasher& hash = hasher(), const key_equal& equal = key_equal());

	Unordered_Multiset(const Unordered_Multiset& other) = default;
	Unordered_Multiset(Unordered_Multiset&& other) noexcept = default;

	Unordered_Multiset& operator=(const Unordered_Multiset& other) = default;
	Unordered_Multiset& operator=(Unordered_Multiset&& other) noexcept = default;

	Unordered_Multiset& operator=(std::initializer_list<value_type> ilist);

	iterator begin() noexcept;
	iterator end() noexcept;
	const_iterator begin() const noexcept;
	const_iterator end() const noexcept;
	const_iterator cbegin() const noexcept;
	const_iterator cend() const noexcept;

	bool empty() const noexcept;
	size_type size() const noexcept;

	void clear() noexcept;

	iterator insert(const value_type& value);
	iterator insert(value_type&& value);

	template<typename InputIt>
	void insert(InputIt first, InputIt last);

	void insert(std::initializer_list<value_type> ilist);

	template<typename... Args>
	iterator emplace(Args&&... args);

	size_type erase(const key_type& key);

	void swap(Unordered_Multiset& other) noexcept;

	iterator find(const key_type& key);
	const_iterator find(const key_type& key) const;

	size_type count(const key_type& key) const;

	std::pair<iterator, iterator> equal_range(const key_type& key);
	std::pair<const_iterator, const_iterator> equal_range(const key_type& key) const;

	size_type bucket_count() const noexcept;
	size_type bucket_size(size_type index) const;
	size_type bucket(const key_type& key) const;

	float load_factor() const noexcept;
	float max_load_factor() const noexcept;
	void max_load_factor(float ml);

	void reserve(size_type count);
	void rehash(size_type count);

	bool operator==(const Unordered_Multiset& other) const;
	bool operator!=(const Unordered_Multiset& other) const;
};

template<typename Key, typename Hash, typename KeyEqual>
void swap(Unordered_Multiset<Key, Hash, KeyEqual>& lhs, Unordered_Multiset<Key, Hash, KeyEqual>& rhs) noexcept 
{
	lhs.swap(rhs);
}

template<typename Key, typename Hash, typename KeyEqual>
template<bool IsConst>
inline Unordered_Multiset<Key, Hash, KeyEqual>::Iterator<IsConst>::Iterator(TableIterator it)
	: _it(it) 
{
}

template<typename Key, typename Hash, typename KeyEqual>
template<bool IsConst>
typename Unordered_Multiset<Key, Hash, KeyEqual>::Iterator<IsConst>::reference 
		Unordered_Multiset<Key, Hash, KeyEqual>::Iterator<IsConst>::operator*() const
{
	return _it->first;
}

template<typename Key, typename Hash, typename KeyEqual>
template<bool IsConst>
typename Unordered_Multiset<Key, Hash, KeyEqual>::Iterator<IsConst>::pointer 
		Unordered_Multiset<Key, Hash, KeyEqual>::Iterator<IsConst>::operator->() const
{ 
	return &_it->first; 
}

template<typename Key, typename Hash, typename KeyEqual>
template<bool IsConst>
typename Unordered_Multiset<Key, Hash, KeyEqual>::Iterator<IsConst>&  
		Unordered_Multiset<Key, Hash, KeyEqual>::Iterator<IsConst>::operator++()
{
	++_it; 
	return *this;
}

template<typename Key, typename Hash, typename KeyEqual>
template<bool IsConst>
typename Unordered_Multiset<Key, Hash, KeyEqual>::Iterator<IsConst> 
		Unordered_Multiset<Key, Hash, KeyEqual>::Iterator<IsConst>::operator++(int)
{ 
	Iterator tmp = *this; 
	++_it;
	return tmp; 
}


template<typename Key, typename Hash, typename KeyEqual>
template<bool IsConst>
bool Unordered_Multiset<Key, Hash, KeyEqual>::Iterator<IsConst>::operator==(const Iterator& other) const
{
	return _it == other._it;
}

template<typename Key, typename Hash, typename KeyEqual>
template<bool IsConst>
bool Unordered_Multiset<Key, Hash, KeyEqual>::Iterator<IsConst>::operator!=(const Iterator& other) const
{
	return !(*this == other);
}

template<typename Key, typename Hash, typename KeyEqual>
template<bool IsConst>
typename Unordered_Multiset<Key, Hash, KeyEqual>::Iterator<IsConst>::TableIterator 
		Unordered_Multiset<Key, Hash, KeyEqual>::Iterator<IsConst>::base() const
{ 
	return _it;
}

template<typename Key, typename Hash, typename KeyEqual>
inline Unordered_Multiset<Key, Hash, KeyEqual>::Unordered_Multiset(size_type bucket_count, const hasher& hash, const key_equal& equal)
	: _table(bucket_count, hash, equal)
{
}

template<typename Key, typename Hash, typename KeyEqual>
inline Unordered_Multiset<Key, Hash, KeyEqual>::Unordered_Multiset(std::initializer_list<value_type> init, 
		size_type bucket_count, const hasher& hash, const key_equal& equal)
	: _table(bucket_count, hash, equal)
{
	for (const auto& elem : init)
		_table.insert(elem);
}

template<typename Key, typename Hash, typename KeyEqual>
template<typename InputIt>
inline Unordered_Multiset<Key, Hash, KeyEqual>::Unordered_Multiset(InputIt first, InputIt last, 
		size_type bucket_count, const hasher& hash, const key_equal& equal)
	: _table(bucket_count, hash, equal)
{
	insert(first, last);
}

template<typename Key, typename Hash, typename KeyEqual>
Unordered_Multiset<Key, Hash, KeyEqual>& Unordered_Multiset<Key, Hash, KeyEqual>::operator=(std::initializer_list<value_type> ilist)
{
	clear();
	insert(ilist.begin(), ilist.end());
	return *this;
}

template<typename Key, typename Hash, typename KeyEqual>
typename Unordered_Multiset<Key, Hash, KeyEqual>::iterator Unordered_Multiset<Key, Hash, KeyEqual>::begin() noexcept
{
	return iterator(_table.begin()); 
}

template<typename Key, typename Hash, typename KeyEqual>
typename Unordered_Multiset<Key, Hash, KeyEqual>::iterator Unordered_Multiset<Key, Hash, KeyEqual>::end() noexcept
{
	return iterator(_table.end());
}

template<typename Key, typename Hash, typename KeyEqual>
typename Unordered_Multiset<Key, Hash, KeyEqual>::const_iterator Unordered_Multiset<Key, Hash, KeyEqual>::begin() const noexcept
{
	return const_iterator(_table.begin()); 
}

template<typename Key, typename Hash, typename KeyEqual>
typename Unordered_Multiset<Key, Hash, KeyEqual>::const_iterator Unordered_Multiset<Key, Hash, KeyEqual>::end() const noexcept
{
	return const_iterator(_table.end());
}

template<typename Key, typename Hash, typename KeyEqual>
typename Unordered_Multiset<Key, Hash, KeyEqual>::const_iterator Unordered_Multiset<Key, Hash, KeyEqual>::cbegin() const noexcept
{
	return const_iterator(_table.cbegin());
}

template<typename Key, typename Hash, typename KeyEqual>
typename Unordered_Multiset<Key, Hash, KeyEqual>::const_iterator Unordered_Multiset<Key, Hash, KeyEqual>::cend() const noexcept
{
	return const_iterator(_table.cend()); 
}

template<typename Key, typename Hash, typename KeyEqual>
bool Unordered_Multiset<Key, Hash, KeyEqual>::empty() const noexcept
{
	return _table.empty(); 
}

template<typename Key, typename Hash, typename KeyEqual>
typename Unordered_Multiset<Key, Hash, KeyEqual>::size_type Unordered_Multiset<Key, Hash, KeyEqual>::size() const noexcept
{
	return _table.size();
}

template<typename Key, typename Hash, typename KeyEqual>
void Unordered_Multiset<Key, Hash, KeyEqual>::clear() noexcept
{
	_table.clear(); 
}

template<typename Key, typename Hash, typename KeyEqual>
typename Unordered_Multiset<Key, Hash, KeyEqual>::iterator Unordered_Multiset<Key, Hash, KeyEqual>::insert(const value_type& value)
{
	return iterator(_table.insert(value).first);
}

template<typename Key, typename Hash, typename KeyEqual>
typename Unordered_Multiset<Key, Hash, KeyEqual>::iterator Unordered_Multiset<Key, Hash, KeyEqual>::insert(value_type&& value)
{
	return iterator(_table.insert(std::move(value)).first);
}

template<typename Key, typename Hash, typename KeyEqual>
template<typename InputIt>
void Unordered_Multiset<Key, Hash, KeyEqual>::insert(InputIt first, InputIt last)
{
	for (; first != last; ++first)
		_table.insert(*first);
}

template<typename Key, typename Hash, typename KeyEqual>
void Unordered_Multiset<Key, Hash, KeyEqual>::insert(std::initializer_list<value_type> ilist)
{
	insert(ilist.begin(), ilist.end());
}

template<typename Key, typename Hash, typename KeyEqual>
template<typename... Args>
typename Unordered_Multiset<Key, Hash, KeyEqual>::iterator Unordered_Multiset<Key, Hash, KeyEqual>::emplace(Args&&... args)
{
	return iterator(_table.emplace(std::forward<Args>(args)...).first);
}

template<typename Key, typename Hash, typename KeyEqual>
typename Unordered_Multiset<Key, Hash, KeyEqual>::size_type Unordered_Multiset<Key, Hash, KeyEqual>::erase(const key_type& key)
{
	return _table.erase(key); 
}

template<typename Key, typename Hash, typename KeyEqual>
void Unordered_Multiset<Key, Hash, KeyEqual>::swap(Unordered_Multiset& other) noexcept
{
	_table.swap(other._table);
}

template<typename Key, typename Hash, typename KeyEqual>
typename Unordered_Multiset<Key, Hash, KeyEqual>::iterator Unordered_Multiset<Key, Hash, KeyEqual>::find(const key_type& key)
{
	return iterator(_table.find(key));
}

template<typename Key, typename Hash, typename KeyEqual>
typename Unordered_Multiset<Key, Hash, KeyEqual>::const_iterator
		Unordered_Multiset<Key, Hash, KeyEqual>::find(const key_type& key) const
{
	return const_iterator(_table.find(key));
}

template<typename Key, typename Hash, typename KeyEqual>
typename Unordered_Multiset<Key, Hash, KeyEqual>::size_type Unordered_Multiset<Key, Hash, KeyEqual>::count(const key_type& key) const
{
	return _table.count(key);
}

template<typename Key, typename Hash, typename KeyEqual>
std::pair<typename Unordered_Multiset<Key, Hash, KeyEqual>::iterator, typename Unordered_Multiset<Key, Hash, KeyEqual>::iterator>
		Unordered_Multiset<Key, Hash, KeyEqual>::equal_range(const key_type& key)
{
	auto [first, last] = _table.equal_range(key);
	return { iterator(first), iterator(last) };
}

template<typename Key, typename Hash, typename KeyEqual>
std::pair<typename Unordered_Multiset<Key, Hash, KeyEqual>::const_iterator, 
		typename Unordered_Multiset<Key, Hash, KeyEqual>::const_iterator> 
		Unordered_Multiset<Key, Hash, KeyEqual>::equal_range(const key_type& key) const
{
	auto [first, last] = _table.equal_range(key);
	return { const_iterator(first), const_iterator(last) };
}

template<typename Key, typename Hash, typename KeyEqual>
typename Unordered_Multiset<Key, Hash, KeyEqual>::size_type Unordered_Multiset<Key, Hash, KeyEqual>::bucket_count() const noexcept
{
	return _table.bucket_count(); 
}

template<typename Key, typename Hash, typename KeyEqual>
typename Unordered_Multiset<Key, Hash, KeyEqual>::size_type Unordered_Multiset<Key, Hash, KeyEqual>::bucket_size(size_type index) const
{
	return _table.bucket_size(index); 
}

template<typename Key, typename Hash, typename KeyEqual>
typename Unordered_Multiset<Key, Hash, KeyEqual>::size_type Unordered_Multiset<Key, Hash, KeyEqual>::bucket(const key_type& key) const
{
	return _table.bucket(key);
}

template<typename Key, typename Hash, typename KeyEqual>
float Unordered_Multiset<Key, Hash, KeyEqual>::load_factor() const noexcept
{
	return _table.load_factor(); 
}

template<typename Key, typename Hash, typename KeyEqual>
float Unordered_Multiset<Key, Hash, KeyEqual>::max_load_factor() const noexcept
{
	return _table.max_load_factor(); 
}

template<typename Key, typename Hash, typename KeyEqual>
void Unordered_Multiset<Key, Hash, KeyEqual>::max_load_factor(float ml)
{
	_table.max_load_factor(ml);
}

template<typename Key, typename Hash, typename KeyEqual>
void Unordered_Multiset<Key, Hash, KeyEqual>::reserve(size_type count)
{
	_table.reserve(count); 
}

template<typename Key, typename Hash, typename KeyEqual>
void Unordered_Multiset<Key, Hash, KeyEqual>::rehash(size_type count)
{
	_table.reserve(count);
}

template<typename Key, typename Hash, typename KeyEqual>
bool Unordered_Multiset<Key, Hash, KeyEqual>::operator==(const Unordered_Multiset& other) const
{
	return _table == other._table;
}

template<typename Key, typename Hash, typename KeyEqual>
bool Unordered_Multiset<Key, Hash, KeyEqual>::operator!=(const Unordered_Multiset& other) const
{
	return !(*this == other); 
}